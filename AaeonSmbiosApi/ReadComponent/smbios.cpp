#include "pch.h"
#include "smbios.h"

#include <wbemidl.h>
#include <sstream>
#include <fstream>
#include <comdef.h>
#include "Factory.h"
#include "SmbiosStructure.h"
#pragma comment(lib, "Wbemuuid.lib")

typedef UINT(WINAPI *GET_SYSTEM_FIRMWARE_TABLE) (DWORD, DWORD, PVOID, DWORD);

void SMBIOS::Decode(void* Addr, UINT Len)
{
	LPBYTE p = (LPBYTE)(Addr);
	const LPBYTE lastAddress = p + Len;
	PSMBIOSHEADER pHeader;
	Factory factory;
	Parser* parser;
	SmbiosTable smbios_table;
	Json::Value smbios_json_object;

	for (;;) {
		pHeader = (PSMBIOSHEADER)p;
		if (pHeader->Type == 127 && pHeader->Length == 4)
			break; // last avaiable table
		parser = factory.GetParser(pHeader->Type);
		if (parser)
		{
			smbios_table = parser->Parse(p, smbios_json_object);
			smbios_table.DebugMap();
			vec.push_back(smbios_table);
		}
		//vec.push_back(smbios_table);
		LPBYTE nt = p + pHeader->Length; // point to struct end
		while (0 != (*nt | *(nt + 1))) {
			nt++;  // skip string area
			if (nt >= lastAddress) break; // avoid infinite loop when got bad structure of SMBIOS
		}
		nt += 2;
		if (nt >= lastAddress)
			break;
		p = nt;
	}

	WriteJsonToFile(smbios_json_object);
}

void SMBIOS::WriteJsonToFile(Json::Value& json_object)
{
	Json::FastWriter fast_writer;
	string res = fast_writer.write(json_object);
	ofstream out("SmbiosTable.txt");
	out << res;
	out.close();
}

vector<SmbiosTable> SMBIOS::GetAllSmbiosTables(void) const
{
	return vec;
}

bool SMBIOS::GetSmbiosTable(int type, WORD handle, SmbiosTable& smbios_table) const
{
	for (SmbiosTable table : vec)
	{
		if (table.Type() == type && table.Handle() == handle)
		{
			smbios_table = table;
			return true;
		}
	}
	return false;
}

bool SMBIOS::UpdateTableData(int type, WORD handle, string key, vector<BYTE> data)
{
	for (SmbiosTable& table : vec)
	{
		if (table.Type() == type && table.Handle() == handle)
		{
			map<string, SmbiosData>::iterator it;
			it = table.Map().find(key);
			if (it != table.Map().end())
			{
				it->second.SetData(data);
			}
			return true;
		}
	}
	return false;
}

bool SMBIOS::GetData(int type, WORD handle, string key, vector<BYTE>& data)
{
	SmbiosTable st;
	if (!GetSmbiosTable(type, handle, st))return false;
	SmbiosData sd = st.Query(key);
	data = sd.Data();
	return true;
}

SMBIOS* SMBIOS::getInstance(void)
{
	static SMBIOS* pInstance = NULL;
	if (pInstance == NULL)
	{
		// need entry a mutex for thread safe
		if (pInstance == NULL)
		{
			pInstance = new SMBIOS();
			pInstance->initialization();
		}
	}
	const SMBIOS& ref = (*pInstance);
	return pInstance;
}

void SMBIOS::initialization(void)
{
	GET_SYSTEM_FIRMWARE_TABLE pGetSystemFirmwareTable = (GET_SYSTEM_FIRMWARE_TABLE)GetProcAddress(GetModuleHandle(L"kernel32"), "GetSystemFirmwareTable");

	LPBYTE pBuff = NULL;

	PBYTE tableStart = nullptr;
	UINT nTableLength = 0;
	DWORD needBufferSize = 0;

	if (pGetSystemFirmwareTable)
	{
		const DWORD Signature = 'RSMB';
		#if 0
		DWORD Signature = 'R';
		Signature = (Signature << 8) + 'S';
		Signature = (Signature << 8) + 'M';
		Signature = (Signature << 8) + 'B';
		#endif

		needBufferSize = pGetSystemFirmwareTable(Signature, 0, NULL, 0);
		pBuff = new BYTE[needBufferSize];

		needBufferSize = pGetSystemFirmwareTable(Signature, 0,
			pBuff,needBufferSize);
		if (needBufferSize > 0) {
			const PRawSMBIOSData pDMIData = (PRawSMBIOSData)pBuff;
			MajorVersion = pDMIData->SMBIOSMajorVersion;
			MinorVersion = pDMIData->SMBIOSMinorVersion;
			DMIRevision = pDMIData->DmiRevision;

			tableStart = (PBYTE) & (pDMIData->SMBIOSTableData);
			nTableLength = pDMIData->Length;
		}
	}

	if ((0 == needBufferSize) || (nTableLength > needBufferSize))
	{
		if (getWmiSmbios(&pBuff, &nTableLength))
			tableStart = pBuff;
	}

	if (tableStart)
	{
		Decode(tableStart, nTableLength);
	}

	if (pBuff)
		delete[] pBuff;
}

bool SMBIOS::getWmiSmbios(BYTE ** data, UINT * length)
{
	IWbemServices *  pSvc = NULL;
	IWbemServices *  pSvcSmbios = NULL;
	IWbemLocator *   pLoc = NULL;
	HRESULT            result;
	IEnumWbemClassObject *  pEnumerator = NULL;
	std::wostringstream     query;
	std::wstring            q;
	IWbemClassObject *      pInstance = NULL;
	VARIANT                 vtProp;
	ULONG                   uReturn = 0;
	CIMTYPE                 pvtType;

	result = CoInitialize(NULL);

	if (!SUCCEEDED(result))
		return false;

	result = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
	if (!SUCCEEDED(result)) {
		CoUninitialize();
		return false;
	}

	result = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID *)&pLoc);
	if (!SUCCEEDED(result)) {
		CoUninitialize();
		return false;
	}

	result = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);
	if (!SUCCEEDED(result)) {
		pLoc->Release();
		CoUninitialize();
		return false;
	}

	result = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
	if (!SUCCEEDED(result)) {
		pLoc->Release();
		CoUninitialize();
		return false;
	}

	result = pLoc->ConnectServer(_bstr_t(L"ROOT\\WMI"), NULL, NULL, 0, NULL, 0, 0, &pSvcSmbios);
	if (!SUCCEEDED(result)) {
		pLoc->Release();
		CoUninitialize();
		return false;
	}

	result = CoSetProxyBlanket(pSvcSmbios, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
	if (!SUCCEEDED(result)) {
		pSvcSmbios->Release();
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
	}
	
	result = pSvcSmbios->CreateInstanceEnum((BSTR)L"MSSMBios_RawSMBiosTables", 0, NULL, &pEnumerator);
	if (SUCCEEDED(result)) {
		while (pEnumerator) {
			result = pEnumerator->Next(WBEM_INFINITE, 1, &pInstance, &uReturn);

			if (!uReturn) {
				break;
			}

			VariantInit(&vtProp);

			result = pInstance->Get(bstr_t("SMBiosData"), 0, &vtProp, &pvtType, NULL);
			if (SUCCEEDED(result)) {
				SAFEARRAY * array = V_ARRAY(&vtProp);

				*length = array->rgsabound[0].cElements;
				*data = new BYTE[*length];
				memcpy(*data, (BYTE*)array->pvData, *length);
				VariantClear(&vtProp);
			}
		}
		pEnumerator->Release();
		if (pInstance)
			pInstance->Release();
	}

	if (pSvcSmbios)
		pSvcSmbios->Release();
	if (pSvc)
		pSvc->Release();
	if (pLoc)
		pLoc->Release();

	CoUninitialize();
	return true;
}

