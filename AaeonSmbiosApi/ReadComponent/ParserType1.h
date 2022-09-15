#pragma once
#include "Parser.h"
#include "SmbiosStructure.h"

class ParserType1 : public Parser
{
public:
	SmbiosTable Parse(void* p)
	{
		PSystemInfo pBIOS = (PSystemInfo)p;
		SmbiosTable smbios_table(pBIOS->Header.Type, pBIOS->Header.Handle);
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

		return smbios_table;
	}
};