#pragma once
#include "Parser.h"

class ParserType9 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PSMBIOSHEADER pBIOS = (PSMBIOSHEADER)p;
		SmbiosTable smbios_table(pBIOS->Type, pBIOS->Handle);
		string json_type = "Table_" + to_string(pBIOS->Type);
		string json_handle = "Handle_" + to_string(pBIOS->Handle);

		UpdateJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p);
		//If peer_grouping_count does not exist
		if (!json_object[json_type][json_handle].contains("peer_grouping_count"))
			return smbios_table;
		else
		{
			string s_peer_grouping_count = json_object[json_type][json_handle]["peer_grouping_count"]["value"].get<std::string>();
			unsigned int n = 0;
			std::istringstream istr1(s_peer_grouping_count);
			istr1 >> std::hex >> n;
			// If n == 0, peer_groups does not exist
			if (n != 0)
			{
				//peer_groups: vector index = 13
				UpdateNewLengthJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p, 13, 5 * n);
			}
			UpdateNewOffsetJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p, 14, 5 * n);
		}

		return smbios_table;																				             
	}
};

