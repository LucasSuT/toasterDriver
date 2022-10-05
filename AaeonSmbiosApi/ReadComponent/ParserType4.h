#pragma once
#include "Parser.h"

class ParserType4 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PProcessorInfo pBIOS = (PProcessorInfo)p;
		SmbiosTable smbios_table(pBIOS->Header.Type, pBIOS->Header.Handle);

		// Json Test
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("socket_designation"),        GetJsonString(p, pBIOS->socket_designation));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("processor_type"),            GetJsonString(pBIOS->processor_type, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("processor_family"),          GetJsonString(pBIOS->processor_family, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("processor_manufacturer"),    GetJsonString(p, pBIOS->processor_manufacturer));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("processor_id"),              GetJsonString(pBIOS->processor_id, 8));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("processor_version"),         GetJsonString(p, pBIOS->processor_version));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("voltage"),                   GetJsonString(pBIOS->voltage, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("external_clock"),            GetJsonString(pBIOS->external_clock, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("max_speed"),                 GetJsonString(pBIOS->max_speed, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("current_speed"),             GetJsonString(pBIOS->current_speed, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("status"),                    GetJsonString(pBIOS->status, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("processor_upgrade"),         GetJsonString(pBIOS->processor_upgrade, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("l1_cache_handle"),           GetJsonString(pBIOS->l1_cache_handle, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("l2_cache_handle"),           GetJsonString(pBIOS->l2_cache_handle, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("l3_cache_handle"),           GetJsonString(pBIOS->l3_cache_handle, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("serial_number"),             GetJsonString(p, pBIOS->serial_number));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("asset_tag"),                 GetJsonString(p, pBIOS->asset_tag));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("part_number"),               GetJsonString(p, pBIOS->part_number));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("core_count"),                GetJsonString(pBIOS->core_count, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("core_enabled"),              GetJsonString(pBIOS->core_enabled, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("thread_count"),              GetJsonString(pBIOS->thread_count, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("processor_characteristics"), GetJsonString(pBIOS->processor_characteristics, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("processor_family_2"),        GetJsonString(pBIOS->processor_family_2, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("core_count_2"),              GetJsonString(pBIOS->core_count_2, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("core_enabled_2"),            GetJsonString(pBIOS->core_enabled_2, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("thread_count_2"),            GetJsonString(pBIOS->thread_count_2, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("thread_enabled"),            GetJsonString(pBIOS->thread_enabled, 2));

		return smbios_table;																				             
	}
};

