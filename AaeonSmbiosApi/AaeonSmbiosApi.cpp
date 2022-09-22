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

int ParsingStringNumber(const string& str)
{
	int idx = str.size() - 1;
	while (idx)
	{
		if (str[idx] <= '9' && str[idx] >= '0')
			idx--;
		else
			break;
	}

	return stoi(str.substr(idx + 1));
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

		if ( (smbios_table_number == kSmbiosTypeOemStrings || smbios_table_number == kSmbiosTypeSystemConfigurationOptions) && member_name != "Count" )
		{
			member_info->type = NUM_STR_TYPE;
			member_info->offset = ParsingStringNumber(member_name) - 1; // Refer to DmiVar naming rule.
			member_info->length = 1;
			member_info->can_be_modified = true;
		}
		else
		{
			smbios_member_object = smbios_member->smbios_tables[smbios_table_number].at(member_name);
			member_info->type = smbios_member_object.type_;
			member_info->offset = smbios_member_object.offset_;
			member_info->length = smbios_member_object.length_;
			member_info->can_be_modified = smbios_member_object.can_be_modified_;
		}

		return true;
	}
	catch (const std::exception& e)
	{
		printf("Failed when retrieve SMBios Table [%d] - [%s] information.\n", smbios_table_number, member_name.c_str());
		printf("[%s]: %s\n", typeid(e).name(), e.what());
		return false;
	}
}
