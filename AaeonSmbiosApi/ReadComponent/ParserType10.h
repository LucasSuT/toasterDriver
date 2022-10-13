#pragma once
#include "Parser.h"

class ParserType10 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PSMBIOSHEADER pBIOS = (PSMBIOSHEADER)p;
		SmbiosTable smbios_table(pBIOS->Type, pBIOS->Handle);
		int number_of_onboard_device = (pBIOS->Length - sizeof(SMBIOSHEADER)) / 2;
		
		json_object["Table_10"]["name"] = "On Board Devices Information";
		for (int i = 0; i < number_of_onboard_device; i++)
		{
			UpdateNewNameJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p, 0, i + 1, i * 2);
			UpdateNewNameJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p, 1, i + 1, i * 2);
		}
		return smbios_table;																				             
	}
};

