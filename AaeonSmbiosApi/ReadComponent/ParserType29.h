#pragma once
#include "Parser.h"

class ParserType29 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PElectricalCurrentProbe pBIOS = (PElectricalCurrentProbe)p;
		SmbiosTable smbios_table(pBIOS->Header.Type, pBIOS->Header.Handle);

		// Json Test
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("description"),         GetJsonString(p, pBIOS->description));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("location_and_status"), GetJsonString(pBIOS->location_and_status, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("maximum_value"),       GetJsonString(pBIOS->maximum_value, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("minimum_value"),       GetJsonString(pBIOS->minimum_value, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("resolution"),          GetJsonString(pBIOS->resolution, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("tolerance"),           GetJsonString(pBIOS->tolerance, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("accuracy"),            GetJsonString(pBIOS->accuracy, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("oem_defined"),         GetJsonString(pBIOS->oem_defined, 4));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("nominal_value"),       GetJsonString(pBIOS->nominal_value, 2));

		return smbios_table;
	}
};

