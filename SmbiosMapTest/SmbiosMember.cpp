#include "SmbiosMember.h"

SmbiosMember::SmbiosMember()
{
	
}

void SmbiosMember::InitialType0Table()
{
	type0_table =
	{
		{"Vendor",								   MemberProp("string", 0x4, 1)},
		{"BiosVersion",							   MemberProp("string", 0x5, 1)},
		{"BiosSegment",							   MemberProp("value",  0x6, 2)},
		{"BiosReleaseDate",						   MemberProp("string", 0x8, 1)},
		{"BiosSize",							   MemberProp("value",  0x9, 1)},
		{"BiosCharacteristics",					   MemberProp("value",  0xA, 8)},
		{"BIOSCharacteristicsExtensionBytes",	   MemberProp("value",  0x12, 2)},
		{"SystemBiosMajorRelease",				   MemberProp("value",  0x14, 1)},
		{"SystemBiosMinorRelease",				   MemberProp("value",  0x15, 1)},
		{"EmbeddedControllerFirmwareMajorRelease", MemberProp("value",  0x16, 1)},
		{"EmbeddedControllerFirmwareMinorRelease", MemberProp("value",  0x17, 1)},
		// Add for smbus 3.1.0
		{"ExtendedBiosSize",					   MemberProp("value",  0x18, 2)}
	};
}
