// ConsoleApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <winioctl.h>

#include "IOCTLValue.h"

#define AAEON_DEVICE L"\\\\.\\Aaeon_BFPIToolLink"

using namespace std;

DWORD CallBFPI(PDWORD buff, DWORD buffSize, PDWORD out, DWORD* poutSize);
DWORD CallBFPIDataBuffer(PDWORD buff, DWORD buffSize, PDWORD out, DWORD* poutSize);

void print_help(void) {
	cout << "BFPIExec by OSAP, " << __DATE__ << endl;
	cout << "\tBFPIExec methodId arg0 [arg1]" << endl;
}

typedef struct {
	DWORD methodId;
	DWORD arg0;
	DWORD arg1;
} BFPI_ARG;

int main(int argc, char* argv[])
{
	BFPI_ARG bfpi = { 0 };
	DWORD buff[3] = { 0 };
	DWORD outBuff[4] = { 0 };
	DWORD outSize = sizeof(outBuff);
	DWORD ret = 0xFFFFFFFF;

	if (argc < 3 && _stricmp(argv[argc - 1], "-buff")) {
		print_help();
		return -1;
	}

	// Brian Test For DataBuffer --------------------------------------------------------------------------
	if (!_stricmp(argv[argc - 1], "-buff"))
	{
		DWORD databuffer[256] = { 0 };
		DWORD databufferSize = sizeof(databuffer);

		if (argc > 3)
		{
			bfpi.methodId = buff[0] = strtol(argv[1], NULL, 0);
			bfpi.arg0 = buff[1] = strtol(argv[2], NULL, 0);

			if (argc > 4)
				bfpi.arg1 = buff[2] = strtol(argv[3], NULL, 0);

			// Print outvalue first
			ret = CallBFPI(buff, sizeof(buff), outBuff, &outSize);
			cout << "Output:" << endl;
			for (int i = 0; i < (outSize / sizeof(DWORD)); i++)
				cout << "0x" << hex << outBuff[i] << endl;

			// Print databuffer later
			ret = CallBFPIDataBuffer(buff, sizeof(buff), databuffer, &databufferSize);
			cout << "\nData Buffer: " << endl;
			cout << (PUCHAR)databuffer << endl;
		}
		else
		{
			// Print databuffer
			ret = CallBFPIDataBuffer(buff, sizeof(buff), databuffer, &databufferSize);
			cout << (PUCHAR)databuffer << endl;
		}
	}
	else
	{
		bfpi.methodId = buff[0] = strtol(argv[1], NULL, 0);
		bfpi.arg0 = buff[1] = strtol(argv[2], NULL, 0);

		if (argc > 3)
			bfpi.arg1 = buff[2] = strtol(argv[3], NULL, 0);

		ret = CallBFPI(buff, sizeof(buff), outBuff, &outSize);
		cout << "Output:" << endl;
		for (int i = 0; i < (outSize / sizeof(DWORD)); i++)
			cout << "0x" << hex << outBuff[i] << endl;
	}
	// ----------------------------------------------------------------------------------------------------
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

DWORD CallBFPIDataBuffer(PDWORD buff, DWORD buffSize, PDWORD out, DWORD* poutSize)
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

	// Entry Drive IO Control
	result = DeviceIoControl(hDevice,
		IOCTL_AAEON_CALL_BFPI_METHOD_BUFF,
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