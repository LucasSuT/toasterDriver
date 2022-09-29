#pragma once
#include "Parser.h"

class ParserType1 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PSystemInfo pBIOS = (PSystemInfo)p;
		SmbiosTable smbios_table(pBIOS->Header.Type, pBIOS->Header.Handle);
		SmbiosMemberInfo* member_info = new SmbiosMemberInfo();

		smbios_table.Add(ToLowerCase("Manufacturer"), SmbiosData(true, GetString(p, pBIOS->Manufacturer)));
		//DebugVectorString(GetString(p, pBIOS->Manufacturer));
		smbios_table.Add(ToLowerCase("ProductName"),  SmbiosData(true, GetString(p, pBIOS->ProductName)));
		//DebugVectorString(GetString(p, pBIOS->ProductName));
		smbios_table.Add(ToLowerCase("Version"),      SmbiosData(true, GetString(p, pBIOS->Version)));
		//DebugVectorByte(GetString(p, pBIOS->Version));
		smbios_table.Add(ToLowerCase("SerialNumber"), SmbiosData(true, GetString(p, pBIOS->SN)));
		//DebugVectorString(GetString(p, pBIOS->SN));
		smbios_table.Add(ToLowerCase("Uuid"),         SmbiosData(false, ToVector(pBIOS->UUID, 16)));
		//DebugVectorByte(ToVector(pBIOS->UUID, 16));
		smbios_table.Add(ToLowerCase("WakeUpType"),   SmbiosData(false, ToVector(pBIOS->WakeUpType, 1)));
		//DebugVectorByte(ToVector(pBIOS->WakeUpType, 1));
		smbios_table.Add(ToLowerCase("SKUNumber"),    SmbiosData(true, GetString(p, pBIOS->SKUNumber)));
		//DebugVectorByte(GetString(p, pBIOS->SKUNumber));
		smbios_table.Add(ToLowerCase("Family"),       SmbiosData(true, GetString(p, pBIOS->Family)));
		//DebugVectorByte(GetString(p, pBIOS->Family));

		// Json Test
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "manufacturer", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("manufacturer"),  GetJsonString(p, pBIOS->Manufacturer), member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "product_name", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("product_name"),  GetJsonString(p, pBIOS->ProductName),  member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "version", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("version"),       GetJsonString(p, pBIOS->Version),      member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "serial_number", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("serial_number"), GetJsonString(p, pBIOS->SN),           member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "uuid", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("uuid"),          GetJsonString(pBIOS->UUID, 16),        member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "wake_up_type", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("wake_up_type"),  GetJsonString(pBIOS->WakeUpType, 1),   member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "sku_number", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("sku_number"),    GetJsonString(p, pBIOS->SKUNumber),    member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "family", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("family"),        GetJsonString(p, pBIOS->Family),       member_info);

		delete member_info;
		return smbios_table;
	}
};