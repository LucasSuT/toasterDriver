#pragma once

#include "pch.h"
#include <vector>
#include "SmbiosTable.h"
#include "nlohmann/json.hpp"

class SMBIOS {
private:
	SMBIOS() {}
	void initialization(void);
	UINT MajorVersion;
	UINT MinorVersion;
	DWORD DMIRevision;
	vector<SmbiosTable> vec;
	nlohmann::ordered_json json_object;

public:
	virtual ~SMBIOS() {}
	static SMBIOS* getInstance(void);

private:
	// helper function
	void ParseSMBIOSStruct(void* Addr, UINT Len);
	bool getWmiSmbios(BYTE ** data, UINT * length);
	void Decode(void* Addr, UINT Len);
	void GenerateJson();
};
