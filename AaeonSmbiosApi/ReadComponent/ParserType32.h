#pragma once
#include "Parser.h"

class ParserType32 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PSMBIOSHEADER pBIOS = (PSMBIOSHEADER)p;
		SmbiosTable smbios_table(pBIOS->Type, pBIOS->Handle);

		UpdateJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p);

		// boot_status: vector index = 1
		// The length of boot_status is this type's total length - 10 bytes
		UpdateNewLengthJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p, 1, pBIOS->Length - 10);

		return smbios_table;
	}
};

