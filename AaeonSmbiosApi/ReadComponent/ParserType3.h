#pragma once
#include "Parser.h"

class ParserType3 : public Parser
{
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PSMBIOSHEADER pBIOS = (PSMBIOSHEADER)p;
		SmbiosTable smbios_table(pBIOS->Type, pBIOS->Handle);
		string json_handle = "Handle_" + to_string(pBIOS->Handle);

		json_object["Table_3"]["name"] = "System Enclosure or Chassis";
		//Stop after ContainedElementRecordLength offset: 0x14
		UpdateJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p);

		//ContainedElementCount: value
		string ContainedElementCount = json_object["Table_3"][json_handle]["contained_element_count"]["value"].get<std::string>();
		//ContainedElementRecordLength: value
		string ContainedElementRecordLength = json_object["Table_3"][json_handle]["contained_element_record_length"]["value"].get<std::string>();
		unsigned int n = 0, m = 0;
		std::istringstream istr1(ContainedElementCount);
		istr1 >> std::hex >> n;
		std::istringstream istr2(ContainedElementRecordLength);
		istr2 >> std::hex >> m;
		// Deal with contained elements
		// Can have 0 to (ContainedElementCount * ContainedElementRecordLength) contained elements
		int contained_elements_bytes = n * m;
		// If contained_elements_bytes == 0, contained_elements does not exist
		if ( contained_elements_bytes != 0 )
		{
			//contained_elements: vector index = 14
			UpdateNewLengthJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p, 14, contained_elements_bytes);
		}
		UpdateNewOffsetJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p, 15, contained_elements_bytes);

		return smbios_table;
	}
};

