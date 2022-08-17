#pragma once
#include <iostream>
#include "Windows.h"
#include <wchar.h>
#include <math.h>
#include <vector>
#include <string>
#include < sstream >

using namespace std;

#define STATUS int
#define STATUS_FAIL 0xFF
#define STATUS_SUCCESS 0x00

#pragma pack(1)
typedef struct _SMBIOSELEMENT {
	UINT8 Type;
	UINT16 Handle;
	UINT8 Offset;
	UINT8 Flag;
} SMBIOSELEMENT;

typedef struct _AAEONSMBIOS {
	UINT8 Length = 0;
	UINT8 DontCar[4] = { 0 };
	SMBIOSELEMENT Element[255] = { 0 };
} AAEONSMBIOS, * PAAEONSMBIOS;

class UEFIContorller {
public:
	UEFIContorller();
	
	void WriteDmiArray(const SMBIOSELEMENT& element);

	void WriteDmiVariable(vector<UINT8>& data, const SMBIOSELEMENT& element);
	
	void Initial();

	AAEONSMBIOS GetDmiArray();

	void DebugPrintDmiArray();
	
	void DebugPrintDmiVar(const SMBIOSELEMENT& Element);
	
private:
	AAEONSMBIOS _aaeon_smbios;
	wchar_t name[256] = L"DmiArray";
	TCHAR guid[256] = L"{4b3082a3-80c6-4d7e-9cd0-583917265df1}";
	DWORD dwAttributes = 0x00000001 | 0x00000002 | 0x00000004; /*VARIABLE_ATTRIBUTE_NON_VOLATILE*/

	bool ErrorHandle(ULONG dwLen);

	void RasiePrivileges(void);

	wstring ConvertWString(const string& str);

	string ElementToName(const SMBIOSELEMENT& element);
};