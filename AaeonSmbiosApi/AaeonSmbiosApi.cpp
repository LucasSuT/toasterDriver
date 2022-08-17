#include "pch.h"
#include "AaeonSmbiosApi.h"

AAEONSMBIOS_API void AaeonSmbiosInitial()
{
	return;
}

AAEONSMBIOS_API void AaeonSmbiosUninitial()
{
	return;
}

AAEONSMBIOS_API bool AaeonSmbiosGetMemInfo(SmbiosType smbios_table_number, const string& member_name, SmbiosMemberInfo* member_info)
{
	SmbiosMember* smbios_member = &SmbiosMember::GetInstance();
	MemberProp smbios_member_object;
	try
	{
		if ( !member_info ) throw std::invalid_argument("member_info pointer is null");
		if ( member_name.empty() ) throw std::invalid_argument("member_name is empty");
		if ( smbios_table_number >= smbios_member->smbios_tables.size() ) throw std::invalid_argument("Not support selected table number");

		smbios_member_object = smbios_member->smbios_tables[smbios_table_number].at(member_name);
		member_info->type = smbios_member_object.type_;
		member_info->offset = smbios_member_object.offset_;
		member_info->length = smbios_member_object.length_;

		return true;
	}
	catch (const std::exception& e)
	{
		printf("Failed when retrieve SMBios Table [%d] - [%s] information.\n", smbios_table_number, member_name.c_str());
		printf("[%s]: %s\n", typeid(e).name(), e.what());
		return false;
	}
}
