#pragma once
#include "Parser.h"
#include "SmbiosStructure.h"

class ParserType2 : public Parser
{
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PBoardInfo pBIOS = (PBoardInfo)p;
		SmbiosTable smbios_table(pBIOS->Header.Type, pBIOS->Header.Handle);
		smbios_table.Add(ToLowerCase("Manufacturer"),                   SmbiosData(true, GetString(p, pBIOS->Manufacturer)));
		//DebugVectorString(GetString(p, pBIOS->Manufacturer));
		smbios_table.Add(ToLowerCase("ProductName"),                    SmbiosData(true, GetString(p, pBIOS->Product)));
		//DebugVectorString(GetString(p, pBIOS->Product));
		smbios_table.Add(ToLowerCase("Version"),                        SmbiosData(true, GetString(p, pBIOS->Version)));
		//DebugVectorByte(GetString(p, pBIOS->Version));
		smbios_table.Add(ToLowerCase("SerialNumber"),                   SmbiosData(true, GetString(p, pBIOS->SN)));
		//DebugVectorString(GetString(p, pBIOS->SN));
		smbios_table.Add(ToLowerCase("AssetTag"),                       SmbiosData(true, GetString(p, pBIOS->AssetTag)));
		//DebugVectorByte(GetString(p, pBIOS->AssetTag));
		smbios_table.Add(ToLowerCase("FeatureFlag"),                    SmbiosData(false, ToVector(pBIOS->FeatureFlags, 1)));
		//DebugVectorByte(ToVector(pBIOS->FeatureFlags, 1));
		smbios_table.Add(ToLowerCase("LocationInChassis"),              SmbiosData(true, GetString(p, pBIOS->LocationInChassis)));
		//DebugVectorByte(GetString(p, pBIOS->LocationInChassis));
		smbios_table.Add(ToLowerCase("ChassisHandle"),                  SmbiosData(false, ToVector(pBIOS->ChassisHandle, 2)));
		//DebugVectorByte(ToVector(pBIOS->ChassisHandle, 2));
		smbios_table.Add(ToLowerCase("BoardType"),                      SmbiosData(false, ToVector(pBIOS->Type, 1)));
		//DebugVectorByte(ToVector(pBIOS->Type, 1));
		smbios_table.Add(ToLowerCase("NumberOfContainedObjectHandles"), SmbiosData(false, ToVector(pBIOS->NumObjHandle, 1)));
		//DebugVectorByte(ToVector(pBIOS->NumObjHandle, 1));

		// To add "ContainedObjectHandles" this member, need to check "NumberOfContainedObjectHandles"
		if ( smbios_table.Query(ToLowerCase("NumberOfContainedObjectHandles")).Data()[0] )
		{
			smbios_table.Add(ToLowerCase("ContainedObjectHandles"), SmbiosData(false, ToVector(pBIOS->pObjHandle, 2)));
			//DebugVectorByte(ToVector(pBIOS->pObjHandle, 2));
		}

		// Json Test
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("manufacturer"),                       GetJsonString(p, pBIOS->Manufacturer));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("product_name"),                       GetJsonString(p, pBIOS->Product));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("version"),                            GetJsonString(p, pBIOS->Version));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("serial_number"),                      GetJsonString(p, pBIOS->SN));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("asset_tag"),                          GetJsonString(p, pBIOS->AssetTag));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("feature_flag"),                       GetJsonString(pBIOS->FeatureFlags, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("location_in_chassis"),                GetJsonString(p, pBIOS->LocationInChassis));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("chassis_handle"),                     GetJsonString(pBIOS->ChassisHandle, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("board_type"),                         GetJsonString(p, pBIOS->Type));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("number_of_contained_object_handles"), GetJsonString(pBIOS->NumObjHandle, 1));

		// To add "ContainedObjectHandles" this member, need to check "NumberOfContainedObjectHandles"
		vector<BYTE> data = ToVector(pBIOS->NumObjHandle, 1);
		if ( data.size() && data[0] )
		{
			UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("contained_object_handles"), GetJsonString(pBIOS->pObjHandle, 2));
		}

		return smbios_table;
	}
};

