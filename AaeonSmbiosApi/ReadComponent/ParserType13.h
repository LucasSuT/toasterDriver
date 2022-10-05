#pragma once
#include "Parser.h"

class ParserType13 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PBIOSLanguageInfo pBIOS = (PBIOSLanguageInfo)p;
		SmbiosTable smbios_table(pBIOS->Header.Type, pBIOS->Header.Handle);

		// Json Test
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("installable_languages"), GetJsonString(pBIOS->installable_languages, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("flags"),                 GetJsonString(pBIOS->flags, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("reserved"),              GetJsonString(pBIOS->reserved, 15));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("current_language"),      GetJsonString(p, pBIOS->current_language));
		
		return smbios_table;																				             
	}
};

