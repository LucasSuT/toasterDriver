#pragma once

#include "pch.h"
#include <vector>
#include "SmbiosTable.h"

class SMBIOS {
private:
	SMBIOS() {}
	void initialization(void);
	UINT MajorVersion;
	UINT MinorVersion;
	DWORD DMIRevision;
	vector<SmbiosTable> vec;
public:
	virtual ~SMBIOS() {}
	static SMBIOS* getInstance(void);
public:
	bool GetSmbiosTable(int type, WORD handle, SmbiosTable&) const;
	vector<SmbiosTable> GetAllSmbiosTables(void) const;
	bool UpdateTableData(int type, WORD handle, string key, vector<BYTE> data);
	bool GetData(int type, WORD handle, string key, vector<BYTE>& data);

private:
	// helper function
	void ParseSMBIOSStruct(void* Addr, UINT Len);
	bool getWmiSmbios(BYTE ** data, UINT * length);
	void Decode(void* Addr, UINT Len);
};
