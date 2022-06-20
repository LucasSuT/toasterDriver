#include "pch.h"
#include "SmbiosMember.h"

SmbiosMember::SmbiosMember()
{
	InitialType0Table();
	InitialType1Table();

	smbios_tables.push_back(type0_table);
	smbios_tables.push_back(type1_table);
}

void SmbiosMember::InitialType0Table()
{
	type0_table =
	{
		{"Vendor",                                 MemberProp(IS_STR_TYPE, 0x4, 1)},
		{"BiosVersion",                            MemberProp(IS_STR_TYPE, 0x5, 1)},
		{"BiosSegment",                            MemberProp(IS_VAL_TYPE, 0x6, 2)},
		{"BiosReleaseDate",                        MemberProp(IS_STR_TYPE, 0x8, 1)},
		{"BiosSize",                               MemberProp(IS_VAL_TYPE, 0x9, 1)},
		{"BiosCharacteristics",                    MemberProp(IS_VAL_TYPE, 0xA, 8)},
		{"BIOSCharacteristicsExtensionBytes",      MemberProp(IS_VAL_TYPE, 0x12, 2)},
		{"SystemBiosMajorRelease",                 MemberProp(IS_VAL_TYPE, 0x14, 1)},
		{"SystemBiosMinorRelease",                 MemberProp(IS_VAL_TYPE, 0x15, 1)},
		{"EmbeddedControllerFirmwareMajorRelease", MemberProp(IS_VAL_TYPE, 0x16, 1)},
		{"EmbeddedControllerFirmwareMinorRelease", MemberProp(IS_VAL_TYPE, 0x17, 1)},
		// Add for smbus 3.1.0
		{"ExtendedBiosSize",                       MemberProp(IS_VAL_TYPE, 0x18, 2)}
	};
}

void SmbiosMember::InitialType1Table()
{
	type1_table =
	{
		{"Manufacturer", MemberProp(IS_STR_TYPE, 0x4, 1)},
		{"ProductName",  MemberProp(IS_STR_TYPE, 0x5, 1)},
		{"Version",      MemberProp(IS_STR_TYPE, 0x6, 1)},
		{"SerialNumber", MemberProp(IS_STR_TYPE, 0x7, 1)},
		{"Uuid",         MemberProp(IS_VAL_TYPE, 0x8, 16)},
		{"WakeUpType",   MemberProp(IS_VAL_TYPE, 0x18, 1)},
		{"SKUNumber",    MemberProp(IS_STR_TYPE, 0x19, 1)},
		{"Family",       MemberProp(IS_STR_TYPE, 0x1A, 1)}
	};
}

void SmbiosMember::InitialType2Table()
{
	type2_table =
	{
		{"Manufacturer",                   MemberProp(IS_STR_TYPE, 0x4, 1)},
		{"ProductName",                    MemberProp(IS_STR_TYPE, 0x5, 1)},
		{"Version",                        MemberProp(IS_STR_TYPE, 0x6, 1)},
		{"SerialNumber",                   MemberProp(IS_STR_TYPE, 0x7, 1)},
		{"AssetTag",                       MemberProp(IS_STR_TYPE, 0x8, 1)},
		{"FeatureFlag",                    MemberProp(IS_VAL_TYPE, 0x9, 1)},
		{"LocationInChassis",              MemberProp(IS_STR_TYPE, 0xA, 1)},
		{"ChassisHandle",                  MemberProp(IS_VAL_TYPE, 0xB, 2)},
		{"BoardType",                      MemberProp(IS_VAL_TYPE, 0xD, 1)},
		{"NumberOfContainedObjectHandles", MemberProp(IS_VAL_TYPE, 0xE, 1)},
		{"ContainedObjectHandles",         MemberProp(IS_VAL_TYPE, 0xF, 2)}
	};
}

void SmbiosMember::InitialType3Table()
{
	type3_table =
	{
		{"Manufacturer",                 MemberProp(IS_STR_TYPE, 0x4, 1)},
		{"Type",                         MemberProp(IS_VAL_TYPE, 0x5, 1)},
		{"Version",                      MemberProp(IS_STR_TYPE, 0x6, 1)},
		{"SerialNumber",                 MemberProp(IS_STR_TYPE, 0x7, 1)},
		{"AssetTag",                     MemberProp(IS_STR_TYPE, 0x8, 1)},
		{"BootupState",                  MemberProp(IS_VAL_TYPE, 0x9, 1)},
		{"PowerSupplyState",             MemberProp(IS_VAL_TYPE, 0xA, 1)},
		{"ThermalState",                 MemberProp(IS_VAL_TYPE, 0xB, 1)},
		{"SecurityStatus",               MemberProp(IS_VAL_TYPE, 0xC, 1)},
		{"OemDefined",                   MemberProp(IS_VAL_TYPE, 0xD, 4)},
		{"Height",                       MemberProp(IS_VAL_TYPE, 0x11, 1)},
		{"NumberofPowerCords",           MemberProp(IS_VAL_TYPE, 0x12, 1)},
		{"ContainedElementCount",        MemberProp(IS_VAL_TYPE, 0x13, 1)},
		{"ContainedElementRecordLength", MemberProp(IS_VAL_TYPE, 0x14, 1)},
		{"ContainedElements",            MemberProp(IS_VAL_TYPE, 0x15, 1)}
		//{"SKUNumber",                    MemberProp(IS_VAL_TYPE, 0x16, 1)}
	};
}
