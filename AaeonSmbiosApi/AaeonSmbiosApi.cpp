#include "pch.h"
#include "AaeonSmbiosApi.h"

AAEONSMBIOS_API void AaeonSmbiosTest()
{
	MemberProp smbios_member_object;
	try
	{
		smbios_member_object = smbios_member->smbios_tables[SMBIOS_TYPE_BIOS_INFORMATION].at("Vendor");
		std::cout << smbios_member_object.type_ << std::endl;
	}
	catch (const std::exception&)
	{
		std::cout << "Can't find selected key in type table!\n";
	}
}

AAEONSMBIOS_API void AaeonSmbiosInitial()
{
	std::cout << "Hello World\n";

	smbios_member = new SmbiosMember();

	return;
}

AAEONSMBIOS_API void AaeonSmbiosUninitial()
{
	delete smbios_member;
	return;
}
