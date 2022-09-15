#include "pch.h"
#include "UEFIController.h"

UEFIContorller::UEFIContorller()
{
	Initial();
}

void UEFIContorller::WriteDmiArray(const SMBIOSELEMENT& element)
{
	unsigned long dwLen = 0;
	unsigned int query_buffer_size = 0;
	PVOID p_query_buffer = NULL;

	p_query_buffer = &_aaeon_smbios;
	query_buffer_size = sizeof(AAEONSMBIOS);

	_aaeon_smbios.Element[_aaeon_smbios.Length] = element;
	_aaeon_smbios.Length++;
	RasiePrivileges();
	cout << hex << "Type = " << (UINT16)element.Type << " Handle = " << element.Handle << " Offset = " << (UINT16)element.Offset << " Flag = " << (UINT16)element.Flag << "\n";
	dwLen = SetFirmwareEnvironmentVariableEx(
		name, guid, p_query_buffer, query_buffer_size, dwAttributes);

	ErrorHandle(dwLen);
}

void UEFIContorller::WriteDmiVariable(vector<UINT8>& data, const SMBIOSELEMENT& element)
{
	wchar_t name[256] = L"";
	unsigned long dwLen = 0;
	PVOID p_query_buffer;

	p_query_buffer = data.data();
	wmemcpy_s(&name[0], sizeof(name), ConvertWString(ElementToName(element)).c_str(), sizeof(L"DmiVar0000000000"));
	RasiePrivileges();
	dwLen = SetFirmwareEnvironmentVariableEx(
		name, guid, p_query_buffer, data.size(), dwAttributes);

	ErrorHandle(dwLen);
}

void  UEFIContorller::Initial()
{
	GetDmiArray();
}

AAEONSMBIOS UEFIContorller::GetDmiArray()
{
	unsigned long dwLen = 0;
	unsigned int query_buffer_size = 0;
	PVOID p_query_buffer = NULL;

	p_query_buffer = &_aaeon_smbios;
	query_buffer_size = sizeof(AAEONSMBIOS);

	RasiePrivileges();
	dwLen = GetFirmwareEnvironmentVariable(
		name, guid, p_query_buffer, query_buffer_size);

	ErrorHandle(dwLen);

	return _aaeon_smbios;
}

void UEFIContorller::DebugPrintDmiArray()
{
	cout << "Length = " << hex << (UINT16)_aaeon_smbios.Length << "\n";
	for (int i = 0; i < _aaeon_smbios.Length; i++)
	{
		cout << hex << "Type = " << (UINT16)_aaeon_smbios.Element[i].Type << " Handle = " << _aaeon_smbios.Element[i].Handle << " Offset = " << (UINT16)_aaeon_smbios.Element[i].Offset << " Flag = " << (UINT16)_aaeon_smbios.Element[i].Flag << "\n";
		cout << ElementToName(_aaeon_smbios.Element[i]) << endl;
		DebugPrintDmiVar(_aaeon_smbios.Element[i]);
	}
}

void UEFIContorller::DebugPrintDmiVar(const SMBIOSELEMENT& Element)
{
	DWORD  dwLen = 0;
	wchar_t name[256] = L"";
	unsigned int query_buffer_size = 0;
	PVOID p_query_buffer = NULL;

	p_query_buffer = &_aaeon_smbios;
	query_buffer_size = sizeof(AAEONSMBIOS);

	wmemcpy_s(&name[0], sizeof(name), ConvertWString(ElementToName(Element)).c_str(), sizeof(L"DmiVar0000000000"));
	/*vector<UINT8> VarData(255,0);
	p_query_buffer = &VarData;
	query_buffer_size = sizeof(VarData);*/
	PVOID  pBuffer = malloc(255);
	RasiePrivileges();
	dwLen = GetFirmwareEnvironmentVariableEx(
		name, guid, pBuffer, query_buffer_size, &dwAttributes);
	if (0 == dwLen)
	{
		printf("ErrCode = %ld.\n", GetLastError());
	}
	else
	{
		printf("Variable size: %d.\n", dwLen);
		std::stringstream stream;
		string s1 = "", s2 = "";
		for (int index = 0; index < dwLen; index++)
		{
			stream << std::hex << (char)*((BYTE*)pBuffer + index);
			stream >> s1;
			s2 += s1;
			stream.str("");
			stream.clear();
		}
		cout << s2 << endl;
	}
	free(pBuffer);
	cout << "============================================\n";
}

bool UEFIContorller::ErrorHandle(ULONG dwLen)
{
	if (dwLen == 0)
	{
		DWORD dwErr = GetLastError();
		switch (dwErr)
		{
		case ERROR_INVALID_FUNCTION:
			cout << "This function is not support on a legacy BIOS-based system!\n";
			break;
		case ERROR_NOACCESS:
			cout << "The GUID namespace maybe not exist!\n";
			break;
		case ERROR_ENVVAR_NOT_FOUND:
			cout << "The system could not find the environment option that was entered\n";
			break;
		case ERROR_INVALID_PARAMETER:
			cout << "The parameter is incorrect\n";
			break;
		default:
			cout << "Error Code is {" << dwErr << "} \n"; //0x%08x
			break;
		}
		return false;
	}
	else
	{
		cout << "Success! The number of read bytes: {" << dwLen << "} \n";
		return true;
	}
}

void UEFIContorller::RasiePrivileges(void)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;

	if (!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
		&hToken)) {
		//printf("Failed OpenProcessToken\r\n");
		return;
	}

	LookupPrivilegeValue(NULL, SE_SYSTEM_ENVIRONMENT_NAME,
		&tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	DWORD len;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, &len);

	if (GetLastError() != ERROR_SUCCESS) {
		//printf("Failed RasiePrivileges()\r\n");
		return;
	}
}

wstring UEFIContorller::ConvertWString(const string& str)
{
	return wstring(str.begin(), str.end());
}

string UEFIContorller::ElementToName(const SMBIOSELEMENT& element)
{
	std::stringstream stream;
	string s = "DmiVar", s1 = "";
	stream << std::hex << (UINT16)element.Type;
	stream >> s1;
	while (s1.length() < 2)
		s1 = "0" + s1;
	s += s1;
	stream.str("");
	stream.clear();

	stream << std::hex << (UINT16)element.Handle;
	stream >> s1;
	while (s1.length() < 4)
		s1 = "0" + s1;
	s += s1;
	stream.str("");
	stream.clear();

	stream << std::hex << (UINT16)element.Offset;
	stream >> s1;
	while (s1.length() < 2)
		s1 = "0" + s1;
	s += s1;
	stream.str("");
	stream.clear();

	stream << std::hex << (UINT16)element.Flag;
	stream >> s1;
	while (s1.length() < 2)
		s1 = "0" + s1;
	s += s1;
	stream.str("");
	stream.clear();

	return s;
}