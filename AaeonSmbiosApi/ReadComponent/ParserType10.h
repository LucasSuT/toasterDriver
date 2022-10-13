#pragma once
#include "Parser.h"

class ParserType10 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PSMBIOSHEADER pBIOS = (PSMBIOSHEADER)p;
		SmbiosTable smbios_table(pBIOS->Type, pBIOS->Handle);
		//(Length - Header(size:4)) / (devicen_type + description_string)(size:2)
		int number_of_onboard_device = (pBIOS->Length - sizeof(SMBIOSHEADER)) / 2;
		
		for (int i = 0; i < number_of_onboard_device; i++)
		{
			//devicen_type: vector index = 0, description_string: vector index = 1
			UpdateNewNameJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p, 0, i + 1, i * 2);
			UpdateNewNameJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p, 1, i + 1, i * 2);
		}
		return smbios_table;																				             
	}
};

