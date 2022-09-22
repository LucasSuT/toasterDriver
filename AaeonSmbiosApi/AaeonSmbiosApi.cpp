#include "pch.h"
#include "AaeonSmbiosApi.h"

#define AAEON_SMBIOS_DEVICE L"\\\\.\\Aaeon_SmbiosMemoryLink"
#define IOCONTROL_SUCCESS 0
typedef struct
{
	DWORD addr_low_part;
	DWORD addr_high_part; // Currently, address won't use high part address.
}SmbiosV3EntryPointTable, * PSmbiosV3EntryPointTable;

AAEONSMBIOS_API void AaeonSmbiosInitial()
{
	return;
}

AAEONSMBIOS_API void AaeonSmbiosUninitial()
{
	return;
}

int ParsingStringNumber(const string& str)
{
	int idx = str.size() - 1;
	while (idx)
	{
		if (str[idx] <= '9' && str[idx] >= '0')
			idx--;
		else
			break;
	}

	return stoi(str.substr(idx + 1));
}

AAEONSMBIOS_API bool AaeonSmbiosGetMemInfo(SmbiosType smbios_table_number, const char* member_name, SmbiosMemberInfo* member_info)
{
	SmbiosMember* smbios_member = &SmbiosMember::GetInstance();
	MemberProp smbios_member_object;
	string str_member_name(member_name);
	try
	{
		if ( !member_info ) throw std::invalid_argument("member_info pointer is null");
		if ( str_member_name.empty() ) throw std::invalid_argument("member_name is empty");
		if ( smbios_table_number >= smbios_member->smbios_tables.size() ) throw std::invalid_argument("Not support selected table number");

		if ( (smbios_table_number == kSmbiosTypeOemStrings || smbios_table_number == kSmbiosTypeSystemConfigurationOptions) && str_member_name != "Count" )
		{
			member_info->type = NUM_STR_TYPE;
			member_info->offset = ParsingStringNumber(str_member_name) - 1; // Refer to DmiVar naming rule.
			member_info->length = 1;
			member_info->can_be_modified = true;
		}
		else
		{
			smbios_member_object = smbios_member->smbios_tables[smbios_table_number].at(str_member_name);
			member_info->type = smbios_member_object.type_;
			member_info->offset = smbios_member_object.offset_;
			member_info->length = smbios_member_object.length_;
			member_info->can_be_modified = smbios_member_object.can_be_modified_;
		}

		return true;
	}
	catch (const std::exception& e)
	{
		printf("Failed when retrieve SMBios Table [%d] - [%s] information.\n", smbios_table_number, str_member_name.c_str());
		printf("[%s]: %s\n", typeid(e).name(), e.what());
		return false;
	}
}

void RaisePrivileges()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp = { 0 };

	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
		&hToken)) {
		//printf("Failed OpenProcessToken\r\n");
		return;
	}

	LookupPrivilegeValue(NULL, SE_SYSTEM_ENVIRONMENT_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	DWORD len;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, &len);

	if (GetLastError() != ERROR_SUCCESS) {
		//printf("Failed RasiePrivileges()\r\n");
		return;
	}
}

AAEONSMBIOS_API DWORD AaeonSmbiosGetEntryPoint()
{
	unsigned long dwLen = 0;
	wchar_t name[256] = L"SmbiosV3EntryPointTable";
	TCHAR guid[256] = L"{4b3082a3-80c6-4d7e-9cd0-583917265df1}";
	unsigned int query_buffer_size = 8;
	PVOID pBuffer = malloc(query_buffer_size * sizeof(char));

	// Need to raise privilege then could use GetFirmwareEnvironmentVariable().
	RaisePrivileges();

	dwLen = GetFirmwareEnvironmentVariable(name, guid, pBuffer, query_buffer_size);
	PSmbiosV3EntryPointTable PEntryPoint = (PSmbiosV3EntryPointTable)pBuffer;
	if ( 0 == dwLen || PEntryPoint == nullptr )
	{
		printf("ErrCode = %ld.\n", GetLastError());
	}
	else
	{
		printf("Variable size: %d.\n", dwLen);
		printf("0x%lx\n", PEntryPoint->addr_low_part);
	}
	DWORD SMBIOSEntryPoint = PEntryPoint->addr_low_part;
	free(pBuffer);
	return SMBIOSEntryPoint ? SMBIOSEntryPoint : NULL;
}

void AaeonSmbiosWriteMemory(int is_string, int type, int handle, int offset, UCHAR data[], int data_size)
{
	HANDLE hDevice = NULL;
	BOOL result;
	DWORD dwOutput;
	int buff[5] = { 0 };
	AAEON_SMBIOS bAAEON_SMBIOS;
	// Create device handler to driver
	hDevice = CreateFile(AAEON_SMBIOS_DEVICE,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hDevice == INVALID_HANDLE_VALUE)
	{
		std::cout << "Open IOCTL Failed." << std::endl;
		return;
	}
	bAAEON_SMBIOS.bEntryPoint = AaeonSmbiosGetEntryPoint();
	bAAEON_SMBIOS.bType = (UINT8)type;
	bAAEON_SMBIOS.bHandle = (UINT16)handle;
	bAAEON_SMBIOS.bOffset = (UINT8)offset;
	bAAEON_SMBIOS.bDataSize = (UCHAR)data_size;
	bAAEON_SMBIOS.bIsString = (UCHAR)is_string;

	for (int i = 0; i < data_size; ++i)
	{
		bAAEON_SMBIOS.bData[i] = data[i];
		std::cout << data[i] << " | ";
	}
	printf("CallSMBIOS Entry Point: 0x%lx\n", bAAEON_SMBIOS.bEntryPoint);
	// Entry Drive IO Control
	result = DeviceIoControl(hDevice,
		IOCTL_AAEON_WRITE_SMBIOS,
		&bAAEON_SMBIOS,
		sizeof(AAEON_SMBIOS),
		&bAAEON_SMBIOS,
		sizeof(AAEON_SMBIOS),
		&dwOutput,
		NULL);

	if (result != IOCONTROL_SUCCESS) {
		std::cout << "Last Error: " << GetLastError() << std::endl;
	}
}

AAEONSMBIOS_API void AaeonSmbiosWrite(int type, int handle, const char* member_name, UCHAR input_data[], int data_length)
{
	SmbiosMemberInfo* member_info = new SmbiosMemberInfo();
	if (AaeonSmbiosGetMemInfo((SmbiosType)type, member_name, member_info))
	{
		// If input data is string, must add 0x00 at the end, so calloc initial (size + 1) space for string data.
		int raw_data_length = data_length;
		if (member_info->type != VAL_TYPE)
			data_length++;
		PUCHAR data = (PUCHAR)calloc(data_length, sizeof(UCHAR));
		memcpy_s(data, data_length, input_data, raw_data_length);

		// Call UEFI Variable to write NVRAM data
		vector<UINT8> vectorData(data, data + data_length);
		SmbiosEditor* smbios_editor = &SmbiosEditor::getInstance();
		smbios_editor->SetSMBIOS((UINT8)type, (UINT16)handle, (UINT8)member_info->offset, 0, vectorData);

		// If set data is NUM_STR_TYPE, offset need to add 1, the starting number is 1 (String1).
		UCHAR offset = member_info->offset;
		if (member_info->type == NUM_STR_TYPE)
			++offset;
		// Call driver write SMBIOS memory data
		AaeonSmbiosWriteMemory(member_info->type, type, handle, offset, data, data_length);

		free(data);
	}
	else
	{
		cout << "Failed retrieve Smbios Member Information!\n";
	}
}

AAEONSMBIOS_API vector<SmbiosTable> AaeonSmbiosGetAllSmbiosTables()
{
	SMBIOS* Smbios = SMBIOS::getInstance();

	return Smbios->GetAllSmbiosTables();
}

AAEONSMBIOS_API bool AaeonSmbiosGetSmbiosTable(int type, WORD handle, SmbiosTable& smbios_table)
{
	SMBIOS* Smbios = SMBIOS::getInstance();

	return Smbios->GetSmbiosTable(type, handle, smbios_table);
}

AAEONSMBIOS_API bool AaeonSmbiosUpdateSmbiosTableData(int type, WORD handle, string& key, vector<BYTE> data)
{
	SMBIOS* Smbios = SMBIOS::getInstance();

	return Smbios->UpdateTableData(type, handle, key, data);
}


