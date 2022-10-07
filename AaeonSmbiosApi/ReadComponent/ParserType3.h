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
		//ContainedElementCount: 0x13 value
		//int n = json_object[pBIOS->Type][pBIOS->Handle]["contained_element_count"]["value"];
		//ContainedElementRecordLength: 0x14 value
		//int m = json_object[pBIOS->Type][pBIOS->Handle]["contained_element_record_length"]["value"];

		// Deal with contained elements
		// Can have 0 to (ContainedElementCount * ContainedElementRecordLength) contained elements
		//int contained_elements_bytes = n * m;
		//int sku_number_offset = 0x15 + contained_elements_bytes;
		/*if ( contained_elements_bytes != 0 )
		{
			UCHAR* contained_element_offset = (UCHAR*)p + 0x15;
			UpdateJsonObject(json_object, pBIOS->Type, pBIOS->Handle, ToLowerCase("contained_elements"), GetJsonString(contained_element_offset, contained_elements_bytes));
		}

		UpdateJsonObject(json_object, pBIOS->Type, pBIOS->Handle, ToLowerCase("sku_number"), GetJsonString(p, *((char*)p + sku_number_offset)));*/

		return smbios_table;
	}
};

