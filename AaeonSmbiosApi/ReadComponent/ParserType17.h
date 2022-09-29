#pragma once
#include "Parser.h"
#include "SmbiosStructure.h"

class ParserType17 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PMemoryDevice pBIOS = (PMemoryDevice)p;
		SmbiosTable smbios_table(pBIOS->Header.Type, pBIOS->Header.Handle);

		// Json Test
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("physical_memory_array_handle"),    GetJsonString(pBIOS->PhysicalArrayHandle, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("memory_error_information_handle"), GetJsonString(pBIOS->ErrorInformationHandle, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("total_width"),                     GetJsonString(pBIOS->TotalWidth, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("data_width"),                      GetJsonString(pBIOS->DataWidth, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("size"),                            GetJsonString(pBIOS->Size, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("form_factor"),                     GetJsonString(pBIOS->FormFactor, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("device_set"),                      GetJsonString(pBIOS->DeviceSet, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("device_locator"),                  GetJsonString(p, pBIOS->DeviceLocator));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("bank_locator"),                    GetJsonString(p, pBIOS->BankLocator));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("memory_type"),                     GetJsonString(pBIOS->MemoryType, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("type_detail"),                     GetJsonString(pBIOS->TypeDetail, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("speed"),                           GetJsonString(pBIOS->Speed, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("manufacturer"),                    GetJsonString(p, pBIOS->Manufacturer));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("serial_number"),                   GetJsonString(p, pBIOS->SN));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("asset_tag"),                       GetJsonString(p, pBIOS->AssetTag));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("part_number"),                     GetJsonString(p, pBIOS->PN));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("attributes"),                      GetJsonString(pBIOS->Attributes, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("extended_size"),                   GetJsonString(pBIOS->ExtendedSize, 4));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("configured_memory_speed"),         GetJsonString(pBIOS->ConfiguredMemoryClockSpeed, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("minimum_voltage"),                 GetJsonString(pBIOS->MinimumVoltage, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("maximum_voltage"),                 GetJsonString(pBIOS->MaximumVoltage, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("configured_voltage"),              GetJsonString(pBIOS->ConfiguredVoltage, 2));

		return smbios_table;
	}
};

