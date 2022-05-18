// SmbiosMemConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <Windows.h>
#include <winioctl.h>
#include "../ConsoleApp/IOCTLValue.h"
#include "../toaster/SmbiosStruct.h"

#define AAEON_DEVICE L"\\\\.\\Aaeon_SmbiosMemoryLink"

using namespace std;

void CallIOCTL()
{
    HANDLE hDevice = NULL;
    BOOL result;
	DWORD dwOutput;
	//DWORD32 buff= 0x8CAC8000;
	DWORD32 buff = 0x8CACA000;
	SmbiosTable sambios_table;

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

	// Entry Drive IO Control
	result = DeviceIoControl(hDevice,
		IOCTL_AAEON_SMBIOS_READ_MEMORY,
		&buff,
		sizeof(buff),
		&sambios_table,
		sizeof(sambios_table),
		&dwOutput,
		NULL);

	if (result == FALSE) {
		cout << "Last Error: " << GetLastError() << endl;
	}
	else
	{
		printf("%2X\n", sambios_table._BIOSInfo.Header.Length);
		printf("%2X\n", sambios_table._SystemInfo.Header.Length);
	}
}

int main()
{
	cout << "Hello Test!\n";
	CallIOCTL();
	system("pause");

    return 0;
}
