#pragma once
#include "Parser.h"

class ParserType14 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PSMBIOSHEADER pBIOS = (PSMBIOSHEADER)p;
		SmbiosTable smbios_table(pBIOS->Type, pBIOS->Handle);

		UpdateJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p);
		//(Length - Header(size:4) - Group Name(size:1)) / (Item Type + Item Handle)(size:3)
		int number_of_items = (pBIOS->Length - sizeof(SMBIOSHEADER) - 1) / 3;
		for (int i = 0; i < number_of_items; i++)
		{
			//item_type: vector index = 1, item_handle: vector index = 2
			UpdateNewNameJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p, 1, i + 1, i * 3);
			UpdateNewNameJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p, 2, i + 1, i * 3);
		}
		return smbios_table;
	}
};

