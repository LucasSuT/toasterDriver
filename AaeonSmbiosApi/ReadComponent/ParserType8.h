#pragma once
#include "Parser.h"

class ParserType8 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PPortConnectorInfo pBIOS = (PPortConnectorInfo)p;
		SmbiosTable smbios_table(pBIOS->Header.Type, pBIOS->Header.Handle);

		// Json Test
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("internal_reference_designator"), GetJsonString(p, pBIOS->internal_reference_designator));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("internal_connector_type"),       GetJsonString(pBIOS->internal_connector_type, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("external_reference_designator"), GetJsonString(p, pBIOS->external_reference_designator));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("external_connector_type"),       GetJsonString(pBIOS->external_connector_type, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("port_type"),                     GetJsonString(pBIOS->port_type, 1));
		
		return smbios_table;																				             
	}
};

