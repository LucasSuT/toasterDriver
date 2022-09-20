#pragma once
#include "Parser.h"
class ParserType3 : public Parser
{
	SmbiosTable Parse(void* p, Json::Value& json_object)
	{
		PSystemEnclosure pBIOS = (PSystemEnclosure)p;
		SmbiosTable smbios_table(pBIOS->Header.Type, pBIOS->Header.Handle);
		smbios_table.Add(ToLowerCase("Manufacturer"), SmbiosData(true, GetString(p, pBIOS->Manufacturer)));
		smbios_table.Add(ToLowerCase("Type"), SmbiosData(false, ToVector(pBIOS->Type, 1)));
		smbios_table.Add(ToLowerCase("Version"), SmbiosData(true, GetString(p, pBIOS->Version)));
		smbios_table.Add(ToLowerCase("SerialNumber"), SmbiosData(true, GetString(p, pBIOS->SN)));
		smbios_table.Add(ToLowerCase("AssetTag"), SmbiosData(true, GetString(p, pBIOS->AssetTag)));
		smbios_table.Add(ToLowerCase("BootupState"), SmbiosData(false, ToVector(pBIOS->BootupState, 1)));
		smbios_table.Add(ToLowerCase("PowerSupplyState"), SmbiosData(false, ToVector(pBIOS->PowerSupplyState, 1)));
		smbios_table.Add(ToLowerCase("ThermalState"), SmbiosData(false, ToVector(pBIOS->ThermalState, 1)));
		smbios_table.Add(ToLowerCase("SecurityStatus"), SmbiosData(false, ToVector(pBIOS->SecurityStatus, 1)));
		smbios_table.Add(ToLowerCase("OemDefined"), SmbiosData(false, ToVector(pBIOS->OEMDefine, 4)));
		smbios_table.Add(ToLowerCase("Height"), SmbiosData(false, ToVector(pBIOS->Height, 1)));
		smbios_table.Add(ToLowerCase("NumberofPowerCords"), SmbiosData(false, ToVector(pBIOS->NumPowerCord, 1)));
		smbios_table.Add(ToLowerCase("ContainedElementCount"), SmbiosData(false, ToVector(pBIOS->ElementCount, 1)));
		smbios_table.Add(ToLowerCase("ContainedElementRecordLength"), SmbiosData(false, ToVector(pBIOS->ElementRecordLength, 1)));
		smbios_table.Add(ToLowerCase("ContainedElements"), SmbiosData(false, ToVector(pBIOS->pElements, 1)));
		return smbios_table;
	}
};

