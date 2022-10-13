#include "pch.h"
#include "SmbiosMember.h"

SmbiosMember& SmbiosMember::GetInstance()
{
	static SmbiosMember smbios_member;
	return smbios_member;
}

SmbiosMember::SmbiosMember()
{
#pragma region Intial Each Type Table
	InitialType0Table();
	InitialType1Table();
	InitialType2Table();
	InitialType3Table();
	InitialType4Table();
	InitialType7Table();
	InitialType8Table();
	InitialType9Table();
	InitialType10Table();
	InitialType11Table();
	InitialType12Table();
	InitialType13Table();
	InitialType14Table();
	InitialType16Table();
	InitialType17Table();
	InitialType19Table();
	InitialType20Table();
	InitialType26Table();
	InitialType27Table();
	InitialType28Table();
	InitialType29Table();
	InitialType32Table();
	InitialType34Table();
	InitialType35Table();
	InitialType36Table();
	InitialType39Table();
	InitialType41Table();
#pragma endregion

#pragma region Push Each Type Table To Container
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
	smbios_tables.push_back(type12_table);
	smbios_tables.push_back(type13_table);
	smbios_tables.push_back(type14_table);
	smbios_tables.push_back(type15_table);
	smbios_tables.push_back(type16_table);
	smbios_tables.push_back(type17_table);
	smbios_tables.push_back(type18_table);
	smbios_tables.push_back(type19_table);
	smbios_tables.push_back(type20_table);
	smbios_tables.push_back(type21_table);
	smbios_tables.push_back(type22_table);
	smbios_tables.push_back(type23_table);
	smbios_tables.push_back(type24_table);
	smbios_tables.push_back(type25_table);
	smbios_tables.push_back(type26_table);
	smbios_tables.push_back(type27_table);
	smbios_tables.push_back(type28_table);
	smbios_tables.push_back(type29_table);
	smbios_tables.push_back(type30_table);
	smbios_tables.push_back(type31_table);
	smbios_tables.push_back(type32_table);
	smbios_tables.push_back(type33_table);
	smbios_tables.push_back(type34_table);
	smbios_tables.push_back(type35_table);
	smbios_tables.push_back(type36_table);
	smbios_tables.push_back(type37_table);
	smbios_tables.push_back(type38_table);
	smbios_tables.push_back(type39_table);
	smbios_tables.push_back(type40_table);
	smbios_tables.push_back(type41_table);
#pragma endregion
}

void SmbiosMember::InitialType0Table()
{
	type0_table =
	{
		{"vendor",                                      MemberProp(STR_TYPE, 0x4, 1, true)},
		{"bios_version",                                MemberProp(STR_TYPE, 0x5, 1, true)},
		{"bios_segment",                                MemberProp(VAL_TYPE, 0x6, 2, false)},
		{"bios_release_date",                           MemberProp(STR_TYPE, 0x8, 1, true)},
		{"bios_size",                                   MemberProp(VAL_TYPE, 0x9, 1, false)},
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
		// Below these two properties, please refer to the datasheet.
		// Because these two properties some info is dynamic.
		{"contained_elements",              MemberProp(VAL_TYPE, 0x15, 1, false, true)},
		{"sku_number",                      MemberProp(STR_TYPE, 0x15, 1, true)}
	};
}

void SmbiosMember::InitialType4Table()
{
	type4_table =
	{
		{"socket_designation",        MemberProp(STR_TYPE, 0x4,  1, false)},
		{"processor_type",            MemberProp(VAL_TYPE, 0x5,  1, false)},
		{"processor_family",          MemberProp(VAL_TYPE, 0x6,  1, false)},
		{"processor_manufacturer",    MemberProp(STR_TYPE, 0x7,  1, false)},
		{"processor_id",              MemberProp(VAL_TYPE, 0x8,  8, false)},
		{"processor_version",         MemberProp(STR_TYPE, 0x10, 1, false)},
		{"voltage",                   MemberProp(VAL_TYPE, 0x11, 1, false)},
		{"external_clock",            MemberProp(VAL_TYPE, 0x12, 2, false)},
		{"max_speed",                 MemberProp(VAL_TYPE, 0x14, 2, false)},
		{"current_speed",             MemberProp(VAL_TYPE, 0x16, 2, false)},
		{"status",                    MemberProp(VAL_TYPE, 0x18, 1, false)},
		{"processor_upgrade",         MemberProp(VAL_TYPE, 0x19, 1, false)},
		{"l1_cache_handle",           MemberProp(VAL_TYPE, 0x1A, 2, false)},
		{"l2_cache_handle",           MemberProp(VAL_TYPE, 0x1C, 2, false)},
		{"l3_cache_handle",           MemberProp(VAL_TYPE, 0x1E, 2, false)},
		{"serial_number",             MemberProp(STR_TYPE, 0x20, 1, true)},
		{"asset_tag",                 MemberProp(STR_TYPE, 0x21, 1, true)},
		{"part_number",               MemberProp(STR_TYPE, 0x22, 1, true)},
		{"core_count",                MemberProp(VAL_TYPE, 0x23, 1, false)},
		{"core_enabled",              MemberProp(VAL_TYPE, 0x24, 1, false)},
		{"thread_count",              MemberProp(VAL_TYPE, 0x25, 1, false)},
		{"processor_characteristics", MemberProp(VAL_TYPE, 0x26, 2, false)},
		{"processor_family_2",        MemberProp(VAL_TYPE, 0x28, 2, false)},
		{"core_count_2",              MemberProp(VAL_TYPE, 0x2A, 2, false)},
		{"core_enabled_2",            MemberProp(VAL_TYPE, 0x2C, 2, false)},
		{"thread_count_2",            MemberProp(VAL_TYPE, 0x2E, 2, false)},
		{"thread_enabled",            MemberProp(VAL_TYPE, 0x30, 2, false)}
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
		{"socket_designation",     MemberProp(STR_TYPE, 0x4,  1, false)},
		{"cache_configuration",    MemberProp(VAL_TYPE, 0x5,  2, false)},
		{"maximum_cache_size",     MemberProp(VAL_TYPE, 0x7,  2, false)},
		{"installed_size",         MemberProp(VAL_TYPE, 0x9,  2, false)},
		{"supported_sram_type",    MemberProp(VAL_TYPE, 0xB,  2, false)},
		{"current_sram_type",      MemberProp(VAL_TYPE, 0xD,  2, false)},
		{"cache_speed",            MemberProp(VAL_TYPE, 0xF,  1, false)},
		{"error_correction_type",  MemberProp(VAL_TYPE, 0x10, 1, false)},
		{"system_cache_type",      MemberProp(VAL_TYPE, 0x11, 1, false)},
		{"associativity",          MemberProp(VAL_TYPE, 0x12, 1, false)},
		{"maximum_cache_size_2",   MemberProp(VAL_TYPE, 0x13, 4, false)},
		{"installed_cache_size_2", MemberProp(VAL_TYPE, 0x17, 4, false)}
	};
}

void SmbiosMember::InitialType8Table()
{
	type8_table =
	{
		{"internal_reference_designator", MemberProp(STR_TYPE, 0x4, 1, false)},
		{"internal_connector_type",       MemberProp(VAL_TYPE, 0x5, 1, false)},
		{"external_reference_designator", MemberProp(STR_TYPE, 0x6, 1, false)},
		{"external_connector_type",       MemberProp(VAL_TYPE, 0x7, 1, false)},
		{"port_type",                     MemberProp(VAL_TYPE, 0x8, 1, false)},
		
	};
}

void SmbiosMember::InitialType9Table()
{
	type9_table =
	{
		{"slot_designation",       MemberProp(STR_TYPE, 0x4,  1, false)},
		{"slot_type",              MemberProp(VAL_TYPE, 0x5,  1, false)},
		{"slot_data_bus_width",    MemberProp(VAL_TYPE, 0x6,  1, false)},
		{"current_usage",          MemberProp(VAL_TYPE, 0x7,  1, false)},
		{"slot_length",            MemberProp(VAL_TYPE, 0x8,  1, false)},
		{"slot_id",                MemberProp(VAL_TYPE, 0x9,  2, false)},
		{"slot_characteristics_1", MemberProp(VAL_TYPE, 0xB,  1, false)},
		{"slot_characteristics_2", MemberProp(VAL_TYPE, 0xC,  1, false)},
		{"segment_group_number",   MemberProp(VAL_TYPE, 0xD,  2, false)},
		{"bus_number",             MemberProp(VAL_TYPE, 0xF,  1, false)},
		{"device_function_number", MemberProp(VAL_TYPE, 0x10, 1, false)},
		{"data_bus_width",         MemberProp(VAL_TYPE, 0x11, 1, false)},
		{"peer_grouping_count",    MemberProp(VAL_TYPE, 0x12, 1, false)},
		{"peer_groups",            MemberProp(VAL_TYPE, 0x13, 1, false, true)},
		{"slot_information",       MemberProp(VAL_TYPE, 0x13, 1, false)},
		{"slot_physical_width",    MemberProp(VAL_TYPE, 0x14, 1, false)},
		{"slot_pitch",             MemberProp(VAL_TYPE, 0x15, 2, false)},
		{"slot_height",            MemberProp(VAL_TYPE, 0x17, 1, false)},
	};
}

void SmbiosMember::InitialType10Table()
{
	type10_table =
	{
		{"devicen_type",             MemberProp(VAL_TYPE, 0x4,  1, false)},
		{"description_string",       MemberProp(STR_TYPE, 0x5,  1, false)},
	};
}

void SmbiosMember::InitialType11Table()
{
	type11_table =
	{
		{"count",  MemberProp(VAL_TYPE,     0x04, 1, false)},
		{"string", MemberProp(NUM_STR_TYPE, 0x00, 1, true, true)}
	};
}

void SmbiosMember::InitialType12Table()
{
	type12_table =
	{
		{"count",  MemberProp(VAL_TYPE,     0x04, 1, false)},
		{"string", MemberProp(NUM_STR_TYPE, 0x00, 1, true, true)}
	};
}
void SmbiosMember::InitialType13Table()
{
	type13_table =
	{
		{"installable_languages", MemberProp(VAL_TYPE, 0x4,  1, false)},
		{"flags",                 MemberProp(VAL_TYPE, 0x5,  1, false)},
		{"reserved",              MemberProp(VAL_TYPE, 0x6,  15, false)},
		{"current_language",      MemberProp(STR_TYPE, 0x15, 1, false)}
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
		{"extended_maximum_capacity",       MemberProp(VAL_TYPE, 0xF, 8, false)}
	};
}
void SmbiosMember::InitialType17Table()
{
	type17_table =
	{
		{"physical_memory_array_handle",                MemberProp(VAL_TYPE, 0x4,  2, false)},
		{"memory_error_information_handle",             MemberProp(VAL_TYPE, 0x6,  2, false)},
		{"total_width",                                 MemberProp(VAL_TYPE, 0x8,  2, false)},
		{"data_width",                                  MemberProp(VAL_TYPE, 0xA,  2, false)},
		{"size",                                        MemberProp(VAL_TYPE, 0xC,  2, false)},
		{"form_factor",                                 MemberProp(VAL_TYPE, 0xE,  1, false)},
		{"device_set",                                  MemberProp(VAL_TYPE, 0xF,  1, false)},
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
		{"Memory_Technology",                           MemberProp(VAL_TYPE, 0x28, 1, false)},
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
		{"Extended_Configured_Memory_Speed",            MemberProp(VAL_TYPE, 0x58, 4, false)},
	};
}

void SmbiosMember::InitialType18Table()
{
	type18_table =
	{

	};
}

void SmbiosMember::InitialType19Table()
{
	type19_table =
	{

	};
}

void SmbiosMember::InitialType20Table()
{
	type20_table =
	{

	};
}

void SmbiosMember::InitialType21Table()
{
	type21_table =
	{

	};
}

void SmbiosMember::InitialType22Table()
{
	type22_table =
	{

	};
}

void SmbiosMember::InitialType23Table()
{
	type23_table =
	{

	};
}

void SmbiosMember::InitialType24Table()
{
	type24_table =
	{

	};
}

void SmbiosMember::InitialType25Table()
{
	type25_table =
	{

	};
}

void SmbiosMember::InitialType26Table()
{
	type26_table =
	{

	};
}

void SmbiosMember::InitialType27Table()
{
	type27_table =
	{

	};
}

void SmbiosMember::InitialType28Table()
{
	type28_table =
	{

	};
}

void SmbiosMember::InitialType29Table()
{
	type29_table =
	{
		{"description",         MemberProp(STR_TYPE, 0x4,  1, false)},
		{"location_and_status", MemberProp(VAL_TYPE, 0x5,  1, false)},
		{"maximum_value",       MemberProp(VAL_TYPE, 0x6,  2, false)},
		{"minimum_value",       MemberProp(VAL_TYPE, 0x8,  2, false)},
		{"resolution",          MemberProp(VAL_TYPE, 0xA,  2, false)},
		{"tolerance",           MemberProp(VAL_TYPE, 0xC,  2, false)},
		{"accuracy",            MemberProp(VAL_TYPE, 0xE,  2, false)},
		{"oem_defined",         MemberProp(VAL_TYPE, 0x10, 4, false)},
		{"nominal_value",       MemberProp(VAL_TYPE, 0x14, 2, false)},
	};
}

void SmbiosMember::InitialType30Table()
{
	type30_table =
	{

	};
}

void SmbiosMember::InitialType31Table()
{
	type31_table =
	{

	};
}

void SmbiosMember::InitialType32Table()
{
	type32_table =
	{
		{"reserved",    MemberProp(VAL_TYPE, 0x4,  6, false)},
		{"boot_status", MemberProp(VAL_TYPE, 0xA,  1, false, true)},
	};
}

void SmbiosMember::InitialType33Table()
{
	type33_table =
	{

	};
}

void SmbiosMember::InitialType34Table()
{
	type34_table =
	{
		{"description",  MemberProp(STR_TYPE, 0x4,  1, false)},
		{"type",         MemberProp(VAL_TYPE, 0x5,  1, false)},
		{"address",      MemberProp(VAL_TYPE, 0x6,  4, false)},
		{"address_type", MemberProp(VAL_TYPE, 0xA,  1, false)},
	};
}

void SmbiosMember::InitialType35Table()
{
	type35_table =
	{
		{"description",              MemberProp(STR_TYPE, 0x4,  1, false)},
		{"management_device_handle", MemberProp(VAL_TYPE, 0x5,  2, false)},
		{"component_handle",         MemberProp(VAL_TYPE, 0x7,  2, false)},
		{"threshold_handle",         MemberProp(VAL_TYPE, 0x9,  2, false)},
	};
}

void SmbiosMember::InitialType36Table()
{
	type36_table =
	{
		{"lower_threshold_non_critical",   MemberProp(VAL_TYPE, 0x4,  2, false)},
		{"upper_threshold_non_critical",   MemberProp(VAL_TYPE, 0x6,  2, false)},
		{"lower_threshold_critical",       MemberProp(VAL_TYPE, 0x8,  2, false)},
		{"upper_threshold_critical",       MemberProp(VAL_TYPE, 0xA,  2, false)},
		{"lower_threshold_nonrecoverable", MemberProp(VAL_TYPE, 0xC,  2, false)},
		{"upper_threshold_nonrecoverable", MemberProp(VAL_TYPE, 0xE,  2, false)},
	};
}

void SmbiosMember::InitialType37Table()
{
	type37_table =
	{

	};
}

void SmbiosMember::InitialType38Table()
{
	type38_table =
	{

	};
}

void SmbiosMember::InitialType39Table()
{
	type39_table =
	{

	};
}

void SmbiosMember::InitialType40Table()
{
	type40_table =
	{

	};
}

void SmbiosMember::InitialType41Table()
{
	type41_table =
	{

	};
}
