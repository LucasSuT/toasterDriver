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
		{"vendor",                                      MemberProp(STR_TYPE, 0x4, 1)},
		{"bios_version",                                MemberProp(STR_TYPE, 0x5, 1)},
		{"bios_segment",                                MemberProp(VAL_TYPE, 0x6, 2)},
		{"bios_release_date",                           MemberProp(STR_TYPE, 0x8, 1)},
		{"biossize",                                    MemberProp(VAL_TYPE, 0x9, 1)},
		{"bios_characteristics",                        MemberProp(VAL_TYPE, 0xA, 8)},
		{"bios_characteristics_extension_bytes",        MemberProp(VAL_TYPE, 0x12, 2)},
		{"system_bios_major_release",                   MemberProp(VAL_TYPE, 0x14, 1)},
		{"system_bios_minor_release",                   MemberProp(VAL_TYPE, 0x15, 1)},
		{"embedded_controller_firmware_major_release",  MemberProp(VAL_TYPE, 0x16, 1)},
		{"embedded_controller_firmware_minor_release",  MemberProp(VAL_TYPE, 0x17, 1)},
		// Add for smbus 3.1.0
		{"extended_bios_size",                          MemberProp(VAL_TYPE, 0x18, 2)}
	};
}

void SmbiosMember::InitialType1Table()
{
	type1_table =
	{
		{"manufacturer",    MemberProp(STR_TYPE, 0x4, 1)},
		{"product_name",    MemberProp(STR_TYPE, 0x5, 1)},
		{"version",         MemberProp(STR_TYPE, 0x6, 1)},
		{"serial_number",   MemberProp(STR_TYPE, 0x7, 1)},
		{"uuid",            MemberProp(VAL_TYPE, 0x8, 16)},
		{"wake_up_type",    MemberProp(VAL_TYPE, 0x18, 1)},
		{"sku_number",      MemberProp(STR_TYPE, 0x19, 1)},
		{"family",          MemberProp(STR_TYPE, 0x1A, 1)}
	};
}

void SmbiosMember::InitialType2Table()
{
	type2_table =
	{
		{"manufacturer",                        MemberProp(STR_TYPE, 0x4, 1)},
		{"product_name",                        MemberProp(STR_TYPE, 0x5, 1)},
		{"version",                             MemberProp(STR_TYPE, 0x6, 1)},
		{"serial_number",                       MemberProp(STR_TYPE, 0x7, 1)},
		{"asset_tag",                           MemberProp(STR_TYPE, 0x8, 1)},
		{"feature_flag",                        MemberProp(VAL_TYPE, 0x9, 1)},
		{"location_in_chassis",                 MemberProp(STR_TYPE, 0xA, 1)},
		{"chassis_handle",                      MemberProp(VAL_TYPE, 0xB, 2)},
		{"board_type",                          MemberProp(VAL_TYPE, 0xD, 1)},
		{"number_of_contained_object_handles",  MemberProp(VAL_TYPE, 0xE, 1)},
		{"contained_object_handles",            MemberProp(VAL_TYPE, 0xF, 2)}
	};
}

void SmbiosMember::InitialType3Table()
{
	type3_table =
	{
		{"manufacturer",                    MemberProp(STR_TYPE, 0x4, 1)},
		{"type",                            MemberProp(VAL_TYPE, 0x5, 1)},
		{"version",                         MemberProp(STR_TYPE, 0x6, 1)},
		{"serial_number",                   MemberProp(STR_TYPE, 0x7, 1)},
		{"asset_tag",                       MemberProp(STR_TYPE, 0x8, 1)},
		{"bootup_state",                    MemberProp(VAL_TYPE, 0x9, 1)},
		{"power_supply_state",              MemberProp(VAL_TYPE, 0xA, 1)},
		{"thermal_state",                   MemberProp(VAL_TYPE, 0xB, 1)},
		{"security_status",                 MemberProp(VAL_TYPE, 0xC, 1)},
		{"oem_defined",                     MemberProp(VAL_TYPE, 0xD, 4)},
		{"height",                          MemberProp(VAL_TYPE, 0x11, 1)},
		{"number_of_power_cords",           MemberProp(VAL_TYPE, 0x12, 1)},
		{"contained_element_count",         MemberProp(VAL_TYPE, 0x13, 1)},
		{"contained_element_record_length", MemberProp(VAL_TYPE, 0x14, 1)},
		{"contained_elements",              MemberProp(VAL_TYPE, 0x15, 1)}
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
		{"count", MemberProp(VAL_TYPE, 0x04, 1)}
	};
}
