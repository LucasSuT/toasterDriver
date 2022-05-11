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
	int buff[5] = { 0 };

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
		buff,
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
#pragma pack(1)
	struct test {
		UCHAR a;
		UCHAR b;
		UCHAR c;
	}t;
	cout << "Hello Test!\n";
	/*CallIOCTL();*/
	printf("%x\n", &t);
	printf("%x\n", &t.a);
	printf("%x\n", &t.b);
	printf("%x\n", &t.c);
	system("pause");

    return 0;
}
