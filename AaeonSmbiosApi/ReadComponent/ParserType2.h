#pragma once
#include "Parser.h"

class ParserType2 : public Parser
{
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PSMBIOSHEADER pBIOS = (PSMBIOSHEADER)p;
		SmbiosTable smbios_table(pBIOS->Type, pBIOS->Handle);
		string json_type = "Table_" + to_string(pBIOS->Type);
		string json_handle = "Handle_" + to_string(pBIOS->Handle);

		UpdateJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p);

		string number_of_contained_object_handles = json_object[json_type][json_handle]["number_of_contained_object_handles"]["value"].get<std::string>();
		unsigned int n = 0;
		std::istringstream istr1(number_of_contained_object_handles);
		istr1 >> std::hex >> n;
		//if number_of_contained_object_handles > 0, contained_object_handles is exist.
		if (n > 0)
		{
			//contained_object_handles length = number_of_contained_object_handles * WORD
			//contained_object_handles: vector index = 10
			UpdateNewLengthJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p, 10, 2 * n);
		}

		return smbios_table;
	}
};

