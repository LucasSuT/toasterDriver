#pragma once
#include "Parser.h"

class ParserType11 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		POemString pBIOS = (POemString)p;
		SmbiosTable smbios_table(pBIOS->Header.Type, pBIOS->Header.Handle);
		SmbiosMemberInfo* member_info = new SmbiosMemberInfo();

		smbios_table.Add(ToLowerCase("Count"), SmbiosData(true, GetOEMString(p)));

		// Json Test
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "count", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("count"), GetJsonString(pBIOS->Count, 1), member_info);

		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "string", member_info);
		if ( pBIOS->Count )
		{
			UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, GetJsonOEMString(p), member_info);
		}

		delete member_info;
		return smbios_table;
	}
};