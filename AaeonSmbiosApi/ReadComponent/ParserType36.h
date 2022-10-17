#pragma once
#include "Parser.h"

class ParserType36 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PSMBIOSHEADER pBIOS = (PSMBIOSHEADER)p;
		SmbiosTable smbios_table(pBIOS->Type, pBIOS->Handle);

		json_object["Table_36"]["name"] = "Management Device Threshold Data";
		UpdateJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p);

		return smbios_table;
	}
};
