#pragma once
#include "Parser.h"

class ParserType10 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PSMBIOSHEADER pBIOS = (PSMBIOSHEADER)p;
		SmbiosTable smbios_table(pBIOS->Type, pBIOS->Handle);

		int number_of_onboard_device = (pBIOS->Length - sizeof(PSMBIOSHEADER)) / 2;

		for (int i = 0; i < number_of_onboard_device; i++)
		{
			UpdateNewOffsetJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p, 1, i*2);
		}
		
		
		return smbios_table;																				             
	}
};

