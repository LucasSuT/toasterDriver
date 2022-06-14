// SmbiosMemConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <Windows.h>
#include <winioctl.h>
#include < sstream >
#include "IOCTLValue.h"

#define AAEON_DEVICE L"\\\\.\\Aaeon_SmbiosMemoryLink"
DWORD SMBIOSEntryPoint = 0;
DWORD SMBIOSSize = 0;
using namespace std;
void RasiePrivileges(void)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp = { 0 };

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

DWORD getEntryPoint()
{
	typedef struct
	{
		DWORD SMBIOSAdr;
		DWORD DontCare;
	}*PSMBIOS;
	
	unsigned long dwLen = 0;
	wchar_t name[256] = L"SmbiosV3EntryPointTable";
	PVOID p_query_buffer = NULL;
	TCHAR guid[256] = L"{4b3082a3-80c6-4d7e-9cd0-583917265df1}";
	unsigned int query_buffer_size = 8;
	PVOID  pBuffer = malloc(255);
	DWORD dwAttributes = 0x00000001 | 0x00000002 | 0x00000004; /*VARIABLE_ATTRIBUTE_NON_VOLATILE*/
	RasiePrivileges();
	dwLen = GetFirmwareEnvironmentVariable(
		name, guid, pBuffer, query_buffer_size);

	PSMBIOS PEntryPoint = (PSMBIOS)pBuffer;
	if (0 == dwLen)
	{
		printf("ErrCode = %ld.\n", GetLastError());
	}
	else
	{
		printf("Variable size: %d.\n", dwLen);
		printf("0x%lx\n", PEntryPoint->SMBIOSAdr);
		SMBIOSSize = 
		SMBIOSEntryPoint = PEntryPoint->SMBIOSAdr;
	}
	free(pBuffer);
	return SMBIOSEntryPoint;
}

void WriteSMBIOS(int type, int dataIndex, int DataSize, string data)
{
	HANDLE hDevice = NULL;
	BOOL result;
	DWORD dwOutput;
	int buff[5] = { 0 };
	AAEON_SMBIOS bAAEON_SMBIOS;
	// Create device handler to driver
	hDevice = CreateFile(AAEON_DEVICE,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hDevice == INVALID_HANDLE_VALUE)
	{
		cout << "Open IOCTL Failed." << endl;
		return;
	}
	bAAEON_SMBIOS.bEntryPoint = SMBIOSEntryPoint;
	bAAEON_SMBIOS.bType = type;
	bAAEON_SMBIOS.bDataIndex = dataIndex;
	bAAEON_SMBIOS.bDataSize = DataSize;
	int i;
	for ( i = 0; i < DataSize; ++i)
	{
		bAAEON_SMBIOS.bData[i] = data[i];
	}
	bAAEON_SMBIOS.bData[i] = '\0';
	
	printf("CallSMBIOS Entry Point: 0x%lx", bAAEON_SMBIOS.bEntryPoint);
	// Entry Drive IO Control
	result = DeviceIoControl(hDevice,
		IOCTL_AAEON_WRITE_SMBIOS,
		&bAAEON_SMBIOS,
		sizeof(AAEON_SMBIOS),
		&bAAEON_SMBIOS,
		sizeof(AAEON_SMBIOS),
		&dwOutput,
		NULL);

	if (result == FALSE) {
		cout << "Last Error: " << GetLastError() << endl;
	}
}

//void CallIOCTL()
//{
//    HANDLE hDevice = NULL;
//    BOOL result;
//	DWORD dwOutput;
//	int buff[5] = { 0 };
//
//    // Create device handler to driver
//	hDevice = CreateFile(AAEON_DEVICE,
//		GENERIC_READ | GENERIC_WRITE,
//		0,
//		NULL,
//		OPEN_EXISTING,
//		FILE_ATTRIBUTE_NORMAL,
//		NULL);
//	
//	if (hDevice == INVALID_HANDLE_VALUE)
//	{
//		cout << "Open IOCTL Failed." << endl;
//		return;
//	}
//
//	// Entry Drive IO Control
//	result = DeviceIoControl(hDevice,
//		IOCTL_AAEON_SMBIOS_READ_MEMORY,
//		buff,
//		sizeof(buff),
//		NULL,
//		0,
//		&dwOutput,
//		NULL);
//
//	if (result == FALSE) {
//		cout << "Last Error: " << GetLastError() << endl;
//	}
//}

int main()
{
	printf("Entry Point: 0x%lx\n", getEntryPoint());
	cout << "Input hax formate Smbios parameter \"Type, Data Index\"\n";
	int a, b;
	string str;
	cin >> hex >> a >> b;
	cout << "Input Var  \"Data\"\n";
	cin >> str;
	WriteSMBIOS(a, b, str.length()+1, str);
	//CallIOCTL();

    return 0;
}
