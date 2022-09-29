#pragma once
#include "Parser.h"
#include "SmbiosStructure.h"

class ParserType0 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PBIOSInfo pBIOS = (PBIOSInfo)p;
		SmbiosTable smbios_table(pBIOS->Header.Type, pBIOS->Header.Handle);
		SmbiosMemberInfo *member_info = new SmbiosMemberInfo();

		smbios_table.Add(ToLowerCase("Vendor"),                                 SmbiosData(true, GetString(p, pBIOS->Vendor)));
		//DebugVectorString(GetString(p, pBIOS->Vendor));
		smbios_table.Add(ToLowerCase("BiosVersion"),                            SmbiosData(true, GetString(p, pBIOS->Version)));
		//DebugVectorString(GetString(p, pBIOS->Version));
		smbios_table.Add(ToLowerCase("BiosSegment"),                            SmbiosData(false, ToVector(pBIOS->StartingAddrSeg,2)));
		//DebugVectorByte(ToVector(pBIOS->StartingAddrSeg, 2));
		smbios_table.Add(ToLowerCase("BiosReleaseDate"),                        SmbiosData(true, GetString(p, pBIOS->ReleaseDate)));
		//DebugVectorString(GetString(p, pBIOS->ReleaseDate));
		smbios_table.Add(ToLowerCase("BiosSize"),                               SmbiosData(false, ToVector(pBIOS->ROMSize,1)));
		//DebugVectorByte(ToVector(pBIOS->ROMSize, 1));
		smbios_table.Add(ToLowerCase("BiosCharacteristics"),                    SmbiosData(false, ToVector(pBIOS->Characteristics,8)));
		//DebugVectorByte(ToVector(pBIOS->Characteristics, 8));
		smbios_table.Add(ToLowerCase("BIOSCharacteristicsExtensionBytes"),      SmbiosData(false, ToVector(pBIOS->Extension, 2)));
		//DebugVectorByte(ToVector(pBIOS->Extension, 2));
		smbios_table.Add(ToLowerCase("SystemBiosMajorRelease"),                 SmbiosData(false, ToVector(pBIOS->MajorRelease, 1)));
		//DebugVectorByte(ToVector(pBIOS->MajorRelease, 1));
		smbios_table.Add(ToLowerCase("SystemBiosMinorRelease"),                 SmbiosData(false, ToVector(pBIOS->MinorRelease, 1)));
		//DebugVectorByte(ToVector(pBIOS->MinorRelease, 1));
		smbios_table.Add(ToLowerCase("EmbeddedControllerFirmwareMajorRelease"), SmbiosData(false, ToVector(pBIOS->ECFirmwareMajor, 1)));
		//DebugVectorByte(ToVector(pBIOS->ECFirmwareMajor, 1));
		smbios_table.Add(ToLowerCase("EmbeddedControllerFirmwareMinorRelease"), SmbiosData(false, ToVector(pBIOS->ECFirmwareMinor, 1)));
		//DebugVectorByte(ToVector(pBIOS->ECFirmwareMinor, 1));
		smbios_table.Add(ToLowerCase("ExtendedBiosSize"),                       SmbiosData(false, ToVector(pBIOS->ExtendedBiosSize, 2)));
		//DebugVectorByte(ToVector(pBIOS->ExtendedBiosSize, 2));

		// Json Test
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "vendor", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("vendor"),                                     GetJsonString(p, pBIOS->Vendor),           member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "bios_version", member_info);																							  
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("bios_version"),                               GetJsonString(p, pBIOS->Version),          member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "bios_segment", member_info);																							  
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("bios_segment"),                               GetJsonString(pBIOS->StartingAddrSeg, 2),  member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "bios_release_date", member_info);																					  
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("bios_release_date"),                          GetJsonString(p, pBIOS->ReleaseDate),      member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "bios_size", member_info);																							  
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("bios_size"),                                  GetJsonString(pBIOS->ROMSize, 1),          member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "bios_characteristics", member_info);																					  
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("bios_characteristics"),                       GetJsonString(pBIOS->Characteristics, 8),  member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "bios_characteristics_extension_bytes", member_info);																	  
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("bios_characteristics_extension_bytes"),       GetJsonString(pBIOS->Extension, 2),        member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "system_bios_major_release", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("system_bios_major_release"),                  GetJsonString(pBIOS->MajorRelease, 1),     member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "system_bios_minor_release", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("system_bios_minor_release"),                  GetJsonString(pBIOS->MinorRelease, 1),     member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "embedded_controller_firmware_major_release", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("embedded_controller_firmware_major_release"), GetJsonString(pBIOS->ECFirmwareMajor, 1),  member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "embedded_controller_firmware_minor_release", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("embedded_controller_firmware_minor_release"), GetJsonString(pBIOS->ECFirmwareMinor, 1),  member_info);
		AaeonSmbiosGetMemInfo((SmbiosType)pBIOS->Header.Type, "extended_bios_size", member_info);
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("extended_bios_size"),                         GetJsonString(pBIOS->ExtendedBiosSize, 2), member_info);

		delete member_info;
		return smbios_table;
	}
};

