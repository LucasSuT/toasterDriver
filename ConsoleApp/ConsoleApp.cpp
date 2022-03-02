// ConsoleApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <winioctl.h>

#include "IOCTLValue.h"

#define AAEON_DEVICE L"\\\\.\\Aaeon_WdfLink"

using namespace std;

DWORD CallBFPI(PDWORD buff, DWORD buffSize, PDWORD out, DWORD* poutSize);

void print_help(void) {
	cout << "BFPIExec by OSAP, " << __DATE__ << endl;
	cout << "\tBFPIExec methodId arg0 [arg1]" << endl;
}

int main(int argc, char *argv[])
{
	DWORD buff[3] = { 0 };
	DWORD outBuff[4] = { 0 };
	DWORD outSize = sizeof(outBuff);
	DWORD ret = 0xFFFFFFFF;

	if (argc < 3) {
		print_help();
		return -1;
	}
	
	buff[0] = strtol(argv[1], NULL, 0);
	buff[1] = strtol(argv[2], NULL, 0);
	if (argc > 3)
		buff[2] = strtol(argv[3], NULL, 0);

	ret = CallBFPI(buff, sizeof(buff), outBuff, &outSize);
	cout << "output:" << endl;
	for (int i = 0; i < (outSize / sizeof(DWORD)); i++)
		cout << "0x" << hex << outBuff[i] << endl;

	return 0;
}

DWORD CallBFPI(PDWORD buff, DWORD buffSize, PDWORD out, DWORD* poutSize)
{
	string Value;
	HANDLE hDevice = NULL;
	BOOL result;
	DWORD dwOutput;

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
		cout << "Failed. Open BFPI Device Interface" << endl;
		return 0xFFFFFFFF;
	}
	// cout << "CreateFile Succes" << endl;

	// Entry Drive IO Control
	result = DeviceIoControl(hDevice,
		IOCTL_AAEON_CALL_BFPI_METHOD,
		buff,
		buffSize,
		out,
		*poutSize,
		&dwOutput,
		NULL);

	if (result == FALSE) {
		return GetLastError();
	}

	*poutSize = dwOutput;
	return 0;
}
