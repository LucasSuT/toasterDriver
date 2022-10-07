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

DWORD AaeonSmbiosGetEntryPoint()
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

AAEONSMBIOS_API void AaeonSmbiosWrite(WriteSmbiosMember *member_info, UCHAR input_data[])
{
	// If input data is string, must add 0x00 at the end, so calloc initial (size + 1) space for string data.
	int raw_data_length = member_info->length;
	if (member_info->data_type != VAL_TYPE)
		member_info->length++;
	PUCHAR data = (PUCHAR)calloc(member_info->length, sizeof(UCHAR));
	memcpy_s(data, member_info->length, input_data, raw_data_length);

	// Call UEFI Variable to write NVRAM data
	vector<UINT8> vectorData(data, data + member_info->length);
	SmbiosEditor* smbios_editor = &SmbiosEditor::getInstance();
	smbios_editor->SetSMBIOS((UINT8)member_info->type, (UINT16)member_info->handle, (UINT8)member_info->offset, 0, vectorData);

	// If set data is NUM_STR_TYPE, offset need to add 1, the starting number is 1 (String1).
	UCHAR offset = member_info->offset;
	if (member_info->data_type == NUM_STR_TYPE)
		++offset;
	// Call driver write SMBIOS memory data
	AaeonSmbiosWriteMemory(member_info->data_type, member_info->type, member_info->handle, offset, data, member_info->length);
	free(data);
}

AAEONSMBIOS_API void AaeonSmbiosRead()
{
	SMBIOS* Smbios = SMBIOS::getInstance();

	return;
}


