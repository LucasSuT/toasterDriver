#pragma once
#include "Parser.h"

class ParserType3 : public Parser
{
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PSMBIOSHEADER pBIOS = (PSMBIOSHEADER)p;
		SmbiosTable smbios_table(pBIOS->Type, pBIOS->Handle);

		//Stop after ContainedElementRecordLength offset: 0x14
		UpdateJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p);
		string json_type = "Table_" + to_string(pBIOS->Type);
		string json_handle = "Handle_" + to_string(pBIOS->Handle);
		//ContainedElementCount: value
		string ContainedElementCount = json_object[json_type][json_handle]["contained_element_count"]["value"];
		//ContainedElementRecordLength: value
		string ContainedElementRecordLength = json_object[json_type][json_handle]["contained_element_record_length"]["value"];
		unsigned int n = 0, m = 0;
		std::istringstream istr1(ContainedElementCount);
		istr1 >> std::hex >> n;
		std::istringstream istr2(ContainedElementRecordLength);
		istr2 >> std::hex >> m;
		// Deal with contained elements
		// Can have 0 to (ContainedElementCount * ContainedElementRecordLength) contained elements
		int contained_elements_bytes = n * m;
		if ( contained_elements_bytes != 0 )
		{
			//contained_elements_bytes: vector index = 14
			UpdateNewLengthJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p, 14, contained_elements_bytes);
		}
		UpdateNewOffsetJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p, 15, contained_elements_bytes);

		return smbios_table;
	}
};

