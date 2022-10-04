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
		{"vendor",                                      MemberProp(STR_TYPE, 0x4, 1, true)},
		{"bios_version",                                MemberProp(STR_TYPE, 0x5, 1, true)},
		{"bios_segment",                                MemberProp(VAL_TYPE, 0x6, 2, false)},
		{"bios_release_date",                           MemberProp(STR_TYPE, 0x8, 1, true)},
		{"bios_size",                                    MemberProp(VAL_TYPE, 0x9, 1, false)},
		{"bios_characteristics",                        MemberProp(VAL_TYPE, 0xA, 8, false)},
		{"bios_characteristics_extension_bytes",        MemberProp(VAL_TYPE, 0x12, 2, false)},
		{"system_bios_major_release",                   MemberProp(VAL_TYPE, 0x14, 1, false)},
		{"system_bios_minor_release",                   MemberProp(VAL_TYPE, 0x15, 1, false)},
		{"embedded_controller_firmware_major_release",  MemberProp(VAL_TYPE, 0x16, 1, false)},
		{"embedded_controller_firmware_minor_release",  MemberProp(VAL_TYPE, 0x17, 1, false)},
		// Add for smbus 3.1.0
		{"extended_bios_size",                          MemberProp(VAL_TYPE, 0x18, 2, false)}
	};
}

void SmbiosMember::InitialType1Table()
{
	type1_table =
	{
		{"manufacturer",    MemberProp(STR_TYPE, 0x4, 1, true)},
		{"product_name",    MemberProp(STR_TYPE, 0x5, 1, true)},
		{"version",         MemberProp(STR_TYPE, 0x6, 1, true)},
		{"serial_number",   MemberProp(STR_TYPE, 0x7, 1, true)},
		{"uuid",            MemberProp(VAL_TYPE, 0x8, 16, true)},
		{"wake_up_type",    MemberProp(VAL_TYPE, 0x18, 1, false)},
		{"sku_number",      MemberProp(STR_TYPE, 0x19, 1, true)},
		{"family",          MemberProp(STR_TYPE, 0x1A, 1, true)}
	};
}

void SmbiosMember::InitialType2Table()
{
	type2_table =
	{
		{"manufacturer",                        MemberProp(STR_TYPE, 0x4, 1, true)},
		{"product_name",                        MemberProp(STR_TYPE, 0x5, 1, true)},
		{"version",                             MemberProp(STR_TYPE, 0x6, 1, true)},
		{"serial_number",                       MemberProp(STR_TYPE, 0x7, 1, true)},
		{"asset_tag",                           MemberProp(STR_TYPE, 0x8, 1, true)},
		{"feature_flag",                        MemberProp(VAL_TYPE, 0x9, 1, false)},
		{"location_in_chassis",                 MemberProp(STR_TYPE, 0xA, 1, true)},
		{"chassis_handle",                      MemberProp(VAL_TYPE, 0xB, 2, false)},
		{"board_type",                          MemberProp(VAL_TYPE, 0xD, 1, false)},
		{"number_of_contained_object_handles",  MemberProp(VAL_TYPE, 0xE, 1, false)},
		{"contained_object_handles",            MemberProp(VAL_TYPE, 0xF, 2, false)}
	};
}

void SmbiosMember::InitialType3Table()
{
	type3_table =
	{
		{"manufacturer",                    MemberProp(STR_TYPE, 0x4, 1, true)},
		{"type",                            MemberProp(VAL_TYPE, 0x5, 1, true)},
		{"version",                         MemberProp(STR_TYPE, 0x6, 1, true)},
		{"serial_number",                   MemberProp(STR_TYPE, 0x7, 1, true)},
		{"asset_tag",                       MemberProp(STR_TYPE, 0x8, 1, true)},
		{"bootup_state",                    MemberProp(VAL_TYPE, 0x9, 1, false)},
		{"power_supply_state",              MemberProp(VAL_TYPE, 0xA, 1, false)},
		{"thermal_state",                   MemberProp(VAL_TYPE, 0xB, 1, false)},
		{"security_status",                 MemberProp(VAL_TYPE, 0xC, 1, false)},
		{"oem_defined",                     MemberProp(VAL_TYPE, 0xD, 4, true)},
		{"height",                          MemberProp(VAL_TYPE, 0x11, 1, true)},
		{"number_of_power_cords",           MemberProp(VAL_TYPE, 0x12, 1, true)},
		{"contained_element_count",         MemberProp(VAL_TYPE, 0x13, 1, false)},
		{"contained_element_record_length", MemberProp(VAL_TYPE, 0x14, 1, false)},
		{"contained_elements",              MemberProp(VAL_TYPE, 0x15, 1, false)}
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
		{"count", MemberProp(VAL_TYPE, 0x04, 1, false)},
		{"string", MemberProp(NUM_STR_TYPE, 0x00, 1, true)}
	};
}

void SmbiosMember::InitialType12Table()
{
	type12_table =
	{

	};
}
void SmbiosMember::InitialType13Table()
{
	type13_table =
	{

	};
}
void SmbiosMember::InitialType14Table()
{
	type14_table =
	{

	};
}
void SmbiosMember::InitialType15Table()
{
	type15_table =
	{

	};
}
void SmbiosMember::InitialType16Table()
{
	type16_table =
	{
		{"location",                        MemberProp(VAL_TYPE, 0x4, 1, false)},
		{"use",                             MemberProp(VAL_TYPE, 0x5, 1, false)},
		{"memory_error_correction",         MemberProp(VAL_TYPE, 0x6, 1, false)},
		{"maximum_capacity",                MemberProp(VAL_TYPE, 0x7, 4, false)},
		{"memory_error_information_handle", MemberProp(VAL_TYPE, 0xB, 2, false)},
		{"number_of_memory_devices",        MemberProp(VAL_TYPE, 0xD, 2, false)},
		{"extended_maximum_capacity",       MemberProp(VAL_TYPE, 0xF, 4, false)}
	};
}
void SmbiosMember::InitialType17Table()
{
	type17_table =
	{
		{"physical_memory_array_handle",                MemberProp(VAL_TYPE, 0x4, 1, false)},
		{"memory_error_information_handle",             MemberProp(VAL_TYPE, 0x6, 2, false)},
		{"total_width",                                 MemberProp(VAL_TYPE, 0x8, 2, false)},
		{"data_width",                                  MemberProp(VAL_TYPE, 0xA, 1, false)},
		{"size",                                        MemberProp(VAL_TYPE, 0xC, 2, false)},
		{"form_factor",                                 MemberProp(VAL_TYPE, 0xE, 2, false)},
		{"device_set",                                  MemberProp(VAL_TYPE, 0xF, 1, false)},
		{"device_locator",                              MemberProp(STR_TYPE, 0x10, 1, false)},
		{"bank_locator",                                MemberProp(STR_TYPE, 0x11, 1, false)},
		{"memory_type",                                 MemberProp(VAL_TYPE, 0x12, 1, false)},
		{"type_detail",                                 MemberProp(VAL_TYPE, 0x13, 2, false)},
		{"speed",                                       MemberProp(VAL_TYPE, 0x15, 2, false)},
		{"manufacturer",                                MemberProp(STR_TYPE, 0x17, 1, false)},
		{"serial_number",                               MemberProp(STR_TYPE, 0x18, 1, false)},
		{"asset_tag",                                   MemberProp(STR_TYPE, 0x19, 1, false)},
		{"part_number",                                 MemberProp(STR_TYPE, 0x1A, 1, false)},
		{"attributes",                                  MemberProp(VAL_TYPE, 0x1B, 1, false)},
		{"extended_size",                               MemberProp(VAL_TYPE, 0x1C, 4, false)},
		{"configured_memory_speed",                     MemberProp(VAL_TYPE, 0x20, 2, false)},
		{"minimum_voltage",                             MemberProp(VAL_TYPE, 0x22, 2, false)},
		{"maximum_voltage",                             MemberProp(VAL_TYPE, 0x24, 2, false)},
		{"configured_voltage",                          MemberProp(VAL_TYPE, 0x26, 2, false)},
		//3.6
		/*{"Memory_Technology",                           MemberProp(VAL_TYPE, 0x28, 1, false)},
		{"Memory_Operating_Mode_Capability",            MemberProp(VAL_TYPE, 0x29, 2, false)},
		{"Firmware_Version",                            MemberProp(STR_TYPE, 0x2B, 1, false)},
		{"Module_Manufacturer_ID",                      MemberProp(VAL_TYPE, 0x2C, 2, false)},
		{"Module_Product_ID",                           MemberProp(VAL_TYPE, 0x2E, 2, false)},
		{"Memory_Subsystem_Controller_Manufacturer_ID", MemberProp(VAL_TYPE, 0x30, 2, false)},
		{"Memory_Subsystem_Controller_Product_ID",      MemberProp(VAL_TYPE, 0x32, 2, false)},
		{"Non_volatile_Size",                           MemberProp(VAL_TYPE, 0x34, 8, false)},
		{"Volatile_Size",                               MemberProp(VAL_TYPE, 0x3C, 8, false)},
		{"Cache_Size",                                  MemberProp(VAL_TYPE, 0x44, 8, false)},
		{"Logical_Size",                                MemberProp(VAL_TYPE, 0x4C, 8, false)},
		{"Extended_Speed",                              MemberProp(VAL_TYPE, 0x54, 4, false)},
		{"Extended_Configured_Memory_Speed",            MemberProp(VAL_TYPE, 0x58, 4, false)},*/
	};
}