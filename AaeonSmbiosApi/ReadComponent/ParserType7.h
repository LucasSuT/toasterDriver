#pragma once
#include "Parser.h"

class ParserType7 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PCacheInfo pBIOS = (PCacheInfo)p;
		SmbiosTable smbios_table(pBIOS->Header.Type, pBIOS->Header.Handle);

		// Json Test
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("socket_designation"),     GetJsonString(p, pBIOS->socket_designation));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("cache_configuration"),    GetJsonString(pBIOS->cache_configuration, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("maximum_cache_size"),     GetJsonString(pBIOS->maximum_cache_size, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("installed_size"),         GetJsonString(pBIOS->installed_size, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("supported_sram_type"),    GetJsonString(pBIOS->supported_sram_type, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("current_sram_type"),      GetJsonString(pBIOS->current_sram_type, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("cache_speed"),            GetJsonString(pBIOS->cache_speed, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("error_correction_type"),  GetJsonString(pBIOS->error_correction_type, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("system_cache_type"),      GetJsonString(pBIOS->system_cache_type, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("associativity"),          GetJsonString(pBIOS->associativity, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("maximum_cache_size_2"),   GetJsonString(pBIOS->maximum_cache_size_2, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("installed_cache_size_2"), GetJsonString(pBIOS->installed_cache_size_2, 2));
		
		return smbios_table;																				             
	}
};

