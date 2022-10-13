#pragma once
#include "Parser.h"

class ParserType12 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PSMBIOSHEADER pBIOS = (PSMBIOSHEADER)p;
		SmbiosTable smbios_table(pBIOS->Type, pBIOS->Handle);

		UpdateJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p);
		string json_type = "Table_" + to_string(pBIOS->Type);
		string json_handle = "Handle_" + to_string(pBIOS->Handle);
		//Get Json count value
		string count = json_object[json_type][json_handle]["count"]["value"];
		unsigned int n = 0;
		std::istringstream istr1(count);
		istr1 >> std::hex >> n;
		if (n)
		{
			UpdateJsonObject(json_object, pBIOS->Type, pBIOS->Handle, GetJsonOEMString(p));
		}

		return smbios_table;
	}
};