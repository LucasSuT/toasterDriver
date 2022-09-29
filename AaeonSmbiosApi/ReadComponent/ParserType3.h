#pragma once
#include "Parser.h"

class ParserType3 : public Parser
{
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PSystemEnclosure pBIOS = (PSystemEnclosure)p;
		SmbiosTable smbios_table(pBIOS->Header.Type, pBIOS->Header.Handle);
		SmbiosMemberInfo* member_info = new SmbiosMemberInfo();

		smbios_table.Add(ToLowerCase("Manufacturer"),                 SmbiosData(true, GetString(p, pBIOS->Manufacturer)));
		smbios_table.Add(ToLowerCase("Type"),                         SmbiosData(false, ToVector(pBIOS->Type, 1)));
		smbios_table.Add(ToLowerCase("Version"),                      SmbiosData(true, GetString(p, pBIOS->Version)));
		smbios_table.Add(ToLowerCase("SerialNumber"),                 SmbiosData(true, GetString(p, pBIOS->SN)));
		smbios_table.Add(ToLowerCase("AssetTag"),                     SmbiosData(true, GetString(p, pBIOS->AssetTag)));
		smbios_table.Add(ToLowerCase("BootupState"),                  SmbiosData(false, ToVector(pBIOS->BootupState, 1)));
		smbios_table.Add(ToLowerCase("PowerSupplyState"),             SmbiosData(false, ToVector(pBIOS->PowerSupplyState, 1)));
		smbios_table.Add(ToLowerCase("ThermalState"),                 SmbiosData(false, ToVector(pBIOS->ThermalState, 1)));
		smbios_table.Add(ToLowerCase("SecurityStatus"),               SmbiosData(false, ToVector(pBIOS->SecurityStatus, 1)));
		smbios_table.Add(ToLowerCase("OemDefined"),                   SmbiosData(false, ToVector(pBIOS->OEMDefine, 4)));
		smbios_table.Add(ToLowerCase("Height"),                       SmbiosData(false, ToVector(pBIOS->Height, 1)));
		smbios_table.Add(ToLowerCase("NumberofPowerCords"),           SmbiosData(false, ToVector(pBIOS->NumPowerCord, 1)));
		smbios_table.Add(ToLowerCase("ContainedElementCount"),        SmbiosData(false, ToVector(pBIOS->ElementCount, 1)));
		smbios_table.Add(ToLowerCase("ContainedElementRecordLength"), SmbiosData(false, ToVector(pBIOS->ElementRecordLength, 1)));
		smbios_table.Add(ToLowerCase("ContainedElements"),            SmbiosData(false, ToVector(pBIOS->pElements, 1)));

		// Json Test
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "contained_object_handles", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("manufacturer"),                    GetJsonString(p, pBIOS->Manufacturer),        member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "contained_object_handles", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("type"),                            GetJsonString(pBIOS->Type, 1),                member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "contained_object_handles", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("version"),                         GetJsonString(p, pBIOS->Version),             member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "contained_object_handles", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("serial_number"),                   GetJsonString(p, pBIOS->SN),                  member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "contained_object_handles", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("asset_tag"),                       GetJsonString(p, pBIOS->AssetTag),            member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "contained_object_handles", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("bootup_state"),                    GetJsonString(pBIOS->BootupState, 1),         member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "contained_object_handles", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("power_supply_state"),              GetJsonString(pBIOS->PowerSupplyState, 1),    member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "contained_object_handles", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("thermal_state"),                   GetJsonString(pBIOS->ThermalState, 1),        member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "contained_object_handles", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("security_status"),                 GetJsonString(pBIOS->SecurityStatus, 1),      member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "contained_object_handles", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("oem_defined"),                     GetJsonString(pBIOS->OEMDefine, 4),           member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "contained_object_handles", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("height"),                          GetJsonString(pBIOS->Height, 1),              member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "contained_object_handles", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("numberof_power_cords"),            GetJsonString(pBIOS->NumPowerCord, 1),        member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "contained_object_handles", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("contained_element_count"),         GetJsonString(pBIOS->ElementCount, 1),        member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "contained_object_handles", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("contained_element_record_length"), GetJsonString(pBIOS->ElementRecordLength, 1), member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "contained_object_handles", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("contained_elements"),              GetJsonString(pBIOS->pElements, 1),           member_info);
		
		delete member_info;
		return smbios_table;
	}
};

