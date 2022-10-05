#pragma once
#include "Parser.h"

class ParserType12 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PSystemConfigurationOptions pBIOS = (PSystemConfigurationOptions)p;
		SmbiosTable smbios_table(pBIOS->Header.Type, pBIOS->Header.Handle);

		smbios_table.Add(ToLowerCase("Count"), SmbiosData(true, GetOEMString(p)));

		// Json Test
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("count"), GetJsonString(pBIOS->count, 1));

		if ( pBIOS->count)
		{
			UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, GetJsonOEMString(p));
		}

		return smbios_table;
	}
};