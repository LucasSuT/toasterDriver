#pragma once
#include "Parser.h"

class ParserType10 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		POnBoardDevicesInfo pBIOS = (POnBoardDevicesInfo)p;
		SmbiosTable smbios_table(pBIOS->Header.Type, pBIOS->Header.Handle);

		// Json Test
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("devicen_type"),       GetJsonString(pBIOS->devicen_type, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("description_string"), GetJsonString(p, pBIOS->description_string));
		
		return smbios_table;																				             
	}
};

