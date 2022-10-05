#pragma once
#include "Parser.h"

class ParserType9 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PSystemSlots pBIOS = (PSystemSlots)p;
		SmbiosTable smbios_table(pBIOS->Header.Type, pBIOS->Header.Handle);

		// Json Test
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("slot_designation"),       GetJsonString(p, pBIOS->slot_designation));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("slot_type"),              GetJsonString(pBIOS->slot_type, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("slot_data_bus_width"),    GetJsonString(pBIOS->slot_data_bus_width, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("current_usage"),          GetJsonString(pBIOS->current_usage, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("slot_length"),            GetJsonString(pBIOS->slot_length, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("slot_id"),                GetJsonString(pBIOS->slot_id, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("slot_characteristics_1"), GetJsonString(pBIOS->slot_characteristics_1, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("slot_characteristics_2"), GetJsonString(pBIOS->slot_characteristics_2, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("segment_group_number"),   GetJsonString(pBIOS->segment_group_number, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("bus_number"),             GetJsonString(pBIOS->bus_number, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("device_function_number"), GetJsonString(pBIOS->device_function_number, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("data_bus_width"),         GetJsonString(pBIOS->data_bus_width, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("peer_grouping_count"),    GetJsonString(pBIOS->peer_grouping_count, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("peer_groups"),            GetJsonString(pBIOS->peer_groups, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("slot_information"),       GetJsonString(pBIOS->slot_information, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("slot_physical_width"),    GetJsonString(pBIOS->slot_physical_width, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("slot_pitch"),             GetJsonString(pBIOS->slot_pitch, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("slot_height"),            GetJsonString(pBIOS->slot_height, 1));
		
		return smbios_table;																				             
	}
};

