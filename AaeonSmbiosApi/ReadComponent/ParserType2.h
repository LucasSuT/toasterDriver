#pragma once
#include "Parser.h"

class ParserType2 : public Parser
{
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PSMBIOSHEADER pBIOS = (PSMBIOSHEADER)p;
		SmbiosTable smbios_table(pBIOS->Type, pBIOS->Handle);

		UpdateJsonObject(json_object, pBIOS->Type, pBIOS->Handle, (UCHAR*)p);

		// To add "ContainedObjectHandles" this member, need to check "NumberOfContainedObjectHandles"
		/*vector<BYTE> data = ToVector(pBIOS->NumObjHandle, 1);
		if ( data.size() && data[0] )
		{
			UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("contained_object_handles"), GetJsonString(pBIOS->pObjHandle, 2));
		}*/

		return smbios_table;
	}
};

