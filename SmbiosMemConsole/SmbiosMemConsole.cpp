// SmbiosMemConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <Windows.h>
#include <winioctl.h>
#include "../ConsoleApp/IOCTLValue.h"

#define AAEON_DEVICE L"\\\\.\\Aaeon_SmbiosMemoryLink"

using namespace std;

void CallIOCTL()
{
    HANDLE hDevice = NULL;
    BOOL result;
	DWORD dwOutput;
	DWORD32 buff= 0x8CAC8000;

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
		NULL,
		0,
		&dwOutput,
		NULL);

	if (result == FALSE) {
		cout << "Last Error: " << GetLastError() << endl;
	}
}

int main()
{
	cout << "Hello Test!\n";
	CallIOCTL();
	system("pause");

    return 0;
}
