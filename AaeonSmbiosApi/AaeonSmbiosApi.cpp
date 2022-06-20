#include "pch.h"
#include "AaeonSmbiosApi.h"

AAEONSMBIOS_API void AaeonSmbiosInitial()
{
	smbios_member = new SmbiosMember();
	return;
}

AAEONSMBIOS_API void AaeonSmbiosUninitial()
{
	delete smbios_member;
	return;
}

AAEONSMBIOS_API bool AaeonSmbiosGetMemInfo(SmbiosType smbios_table_number, string member_name, SmbiosMemberInfo* member_info)
{
	MemberProp smbios_member_object;
	try
	{
		smbios_member_object = smbios_member->smbios_tables[smbios_table_number].at(member_name);
		strncpy_s(member_info->type, smbios_member_object.type_.c_str(), smbios_member_object.type_.length());
		member_info->offset = smbios_member_object.offset_;
		member_info->length = smbios_member_object.length_;

		return true;
	}
	catch (const std::exception&)
	{
		std::cout << "Can't find " << member_name << " in SMBios Type " << smbios_table_number << " Table!\n";
		return false;
	}
}
