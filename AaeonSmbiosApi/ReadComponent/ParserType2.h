#pragma once
#include "Parser.h"
#include "SmbiosStructure.h"

class ParserType2 : public Parser
{
	SmbiosTable Parse(void* p, Json::Value& json_object)
	{
		PBoardInfo pBIOS = (PBoardInfo)p;
		SmbiosTable smbios_table(pBIOS->Header.Type, pBIOS->Header.Handle);
		smbios_table.Add(ToLowerCase("Manufacturer"), SmbiosData(true, GetString(p, pBIOS->Manufacturer)));
		//DebugVectorString(GetString(p, pBIOS->Manufacturer));
		smbios_table.Add(ToLowerCase("ProductName"), SmbiosData(true, GetString(p, pBIOS->Product)));
		//DebugVectorString(GetString(p, pBIOS->Product));
		smbios_table.Add(ToLowerCase("Version"), SmbiosData(true, GetString(p, pBIOS->Version)));
		//DebugVectorByte(GetString(p, pBIOS->Version));
		smbios_table.Add(ToLowerCase("SerialNumber"), SmbiosData(true, GetString(p, pBIOS->SN)));
		//DebugVectorString(GetString(p, pBIOS->SN));
		smbios_table.Add(ToLowerCase("AssetTag"), SmbiosData(true, GetString(p, pBIOS->AssetTag)));
		//DebugVectorByte(GetString(p, pBIOS->AssetTag));
		smbios_table.Add(ToLowerCase("FeatureFlag"), SmbiosData(false, ToVector(pBIOS->FeatureFlags, 1)));
		//DebugVectorByte(ToVector(pBIOS->FeatureFlags, 1));
		smbios_table.Add(ToLowerCase("LocationInChassis"), SmbiosData(true, GetString(p, pBIOS->LocationInChassis)));
		//DebugVectorByte(GetString(p, pBIOS->LocationInChassis));
		smbios_table.Add(ToLowerCase("ChassisHandle"), SmbiosData(false, ToVector(pBIOS->ChassisHandle, 2)));
		//DebugVectorByte(ToVector(pBIOS->ChassisHandle, 2));
		smbios_table.Add(ToLowerCase("BoardType"), SmbiosData(false, ToVector(pBIOS->Type, 1)));
		//DebugVectorByte(ToVector(pBIOS->Type, 1));
		smbios_table.Add(ToLowerCase("NumberOfContainedObjectHandles"), SmbiosData(false, ToVector(pBIOS->NumObjHandle, 1)));
		//DebugVectorByte(ToVector(pBIOS->NumObjHandle, 1));

		// To add "ContainedObjectHandles" this member, need to check "NumberOfContainedObjectHandles"
		if ( smbios_table.Query(ToLowerCase("NumberOfContainedObjectHandles")).Data()[0] )
		{
			smbios_table.Add(ToLowerCase("ContainedObjectHandles"), SmbiosData(false, ToVector(pBIOS->pObjHandle, 2)));
			//DebugVectorByte(ToVector(pBIOS->pObjHandle, 2));
		}

		return smbios_table;
	}
};

