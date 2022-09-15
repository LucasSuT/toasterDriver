#include "pch.h"
#include "SmbiosMember.h"

SmbiosMember& SmbiosMember::GetInstance()
{
	static SmbiosMember smbios_member;
	return smbios_member;
}

SmbiosMember::SmbiosMember()
{
	InitialType0Table();
	InitialType1Table();
	InitialType2Table();
	InitialType3Table();
	InitialType11Table();

	smbios_tables.push_back(type0_table);
	smbios_tables.push_back(type1_table);
	smbios_tables.push_back(type2_table);
	smbios_tables.push_back(type3_table);
	smbios_tables.push_back(type4_table);
	smbios_tables.push_back(type5_table);
	smbios_tables.push_back(type6_table);
	smbios_tables.push_back(type7_table);
	smbios_tables.push_back(type8_table);
	smbios_tables.push_back(type9_table);
	smbios_tables.push_back(type10_table);
	smbios_tables.push_back(type11_table);
}

void SmbiosMember::InitialType0Table()
{
	type0_table =
	{
		{"Vendor",                                 MemberProp(STR_TYPE, 0x4, 1)},
		{"BiosVersion",                            MemberProp(STR_TYPE, 0x5, 1)},
		{"BiosSegment",                            MemberProp(VAL_TYPE, 0x6, 2)},
		{"BiosReleaseDate",                        MemberProp(STR_TYPE, 0x8, 1)},
		{"BiosSize",                               MemberProp(VAL_TYPE, 0x9, 1)},
		{"BiosCharacteristics",                    MemberProp(VAL_TYPE, 0xA, 8)},
		{"BIOSCharacteristicsExtensionBytes",      MemberProp(VAL_TYPE, 0x12, 2)},
		{"SystemBiosMajorRelease",                 MemberProp(VAL_TYPE, 0x14, 1)},
		{"SystemBiosMinorRelease",                 MemberProp(VAL_TYPE, 0x15, 1)},
		{"EmbeddedControllerFirmwareMajorRelease", MemberProp(VAL_TYPE, 0x16, 1)},
		{"EmbeddedControllerFirmwareMinorRelease", MemberProp(VAL_TYPE, 0x17, 1)},
		// Add for smbus 3.1.0
		{"ExtendedBiosSize",                       MemberProp(VAL_TYPE, 0x18, 2)}
	};
}

void SmbiosMember::InitialType1Table()
{
	type1_table =
	{
		{"Manufacturer", MemberProp(STR_TYPE, 0x4, 1)},
		{"ProductName",  MemberProp(STR_TYPE, 0x5, 1)},
		{"Version",      MemberProp(STR_TYPE, 0x6, 1)},
		{"SerialNumber", MemberProp(STR_TYPE, 0x7, 1)},
		{"Uuid",         MemberProp(VAL_TYPE, 0x8, 16)},
		{"WakeUpType",   MemberProp(VAL_TYPE, 0x18, 1)},
		{"SKUNumber",    MemberProp(STR_TYPE, 0x19, 1)},
		{"Family",       MemberProp(STR_TYPE, 0x1A, 1)}
	};
}

void SmbiosMember::InitialType2Table()
{
	type2_table =
	{
		{"Manufacturer",                   MemberProp(STR_TYPE, 0x4, 1)},
		{"ProductName",                    MemberProp(STR_TYPE, 0x5, 1)},
		{"Version",                        MemberProp(STR_TYPE, 0x6, 1)},
		{"SerialNumber",                   MemberProp(STR_TYPE, 0x7, 1)},
		{"AssetTag",                       MemberProp(STR_TYPE, 0x8, 1)},
		{"FeatureFlag",                    MemberProp(VAL_TYPE, 0x9, 1)},
		{"LocationInChassis",              MemberProp(STR_TYPE, 0xA, 1)},
		{"ChassisHandle",                  MemberProp(VAL_TYPE, 0xB, 2)},
		{"BoardType",                      MemberProp(VAL_TYPE, 0xD, 1)},
		{"NumberOfContainedObjectHandles", MemberProp(VAL_TYPE, 0xE, 1)},
		{"ContainedObjectHandles",         MemberProp(VAL_TYPE, 0xF, 2)}
	};
}

void SmbiosMember::InitialType3Table()
{
	type3_table =
	{
		{"Manufacturer",                 MemberProp(STR_TYPE, 0x4, 1)},
		{"Type",                         MemberProp(VAL_TYPE, 0x5, 1)},
		{"Version",                      MemberProp(STR_TYPE, 0x6, 1)},
		{"SerialNumber",                 MemberProp(STR_TYPE, 0x7, 1)},
		{"AssetTag",                     MemberProp(STR_TYPE, 0x8, 1)},
		{"BootupState",                  MemberProp(VAL_TYPE, 0x9, 1)},
		{"PowerSupplyState",             MemberProp(VAL_TYPE, 0xA, 1)},
		{"ThermalState",                 MemberProp(VAL_TYPE, 0xB, 1)},
		{"SecurityStatus",               MemberProp(VAL_TYPE, 0xC, 1)},
		{"OemDefined",                   MemberProp(VAL_TYPE, 0xD, 4)},
		{"Height",                       MemberProp(VAL_TYPE, 0x11, 1)},
		{"NumberofPowerCords",           MemberProp(VAL_TYPE, 0x12, 1)},
		{"ContainedElementCount",        MemberProp(VAL_TYPE, 0x13, 1)},
		{"ContainedElementRecordLength", MemberProp(VAL_TYPE, 0x14, 1)},
		{"ContainedElements",            MemberProp(VAL_TYPE, 0x15, 1)}
		//{"SKUNumber",                    MemberProp(VAL_TYPE, 0x16, 1)}
	};
}

void SmbiosMember::InitialType4Table()
{
	type4_table =
	{

	};
}

void SmbiosMember::InitialType5Table()
{
	type5_table =
	{

	};
}

void SmbiosMember::InitialType6Table()
{
	type6_table =
	{

	};
}

void SmbiosMember::InitialType7Table()
{
	type7_table =
	{

	};
}

void SmbiosMember::InitialType8Table()
{
	type8_table =
	{

	};
}

void SmbiosMember::InitialType9Table()
{
	type9_table =
	{

	};
}

void SmbiosMember::InitialType10Table()
{
	type10_table =
	{

	};
}

void SmbiosMember::InitialType11Table()
{
	type11_table =
	{
		{"Count", MemberProp(VAL_TYPE, 0x04, 1)}
	};
}
