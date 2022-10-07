#pragma once
#include "Parser.h"

class ParserType12 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PSMBIOSHEADER pBIOS = (PSMBIOSHEADER)p;
		SmbiosTable smbios_table(pBIOS->Type, pBIOS->Handle);

		UpdateJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p);

		/*if ( pBIOS->count)
		{
			UpdateJsonObject(json_object, pBIOS->Type, pBIOS->Handle, GetJsonOEMString(p));
		}*/

		return smbios_table;
	}
};