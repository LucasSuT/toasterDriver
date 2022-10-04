#pragma once
#include "Parser.h"

class ParserType11 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		POemString pBIOS = (POemString)p;
		SmbiosTable smbios_table(pBIOS->Header.Type, pBIOS->Header.Handle);

		smbios_table.Add(ToLowerCase("Count"), SmbiosData(true, GetOEMString(p)));

		// Json Test
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("count"), GetJsonString(pBIOS->Count, 1));

		if ( pBIOS->Count )
		{
			UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, GetJsonOEMString(p));
		}

		return smbios_table;
	}
};