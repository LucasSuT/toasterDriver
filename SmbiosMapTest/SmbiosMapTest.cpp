#include <iostream>
#include "AaeonSmbiosApi.h"

using namespace std;

#define MAPPING_TABLE_TEST 0
#define READ_SMBIOS_API_TEST 1

int main()
{
    AaeonSmbiosInitial();

#if MAPPING_TABLE_TEST
    // Mapping Table Test
    SmbiosMemberInfo* member_info = new SmbiosMemberInfo();
    if ( AaeonSmbiosGetMemInfo(kSmbiosTypeBiosInformation, "vendor", member_info) )
    {
        printf("SmbiosMember Type         : %s\n", (member_info->type == 1 ? "String" : (member_info->type == 2 ? "NumberOfStrings" : "Value")));
        printf("SmbiosMember offset       : %d\n", member_info->offset);
        printf("SmbiosMember length       : %d\n", member_info->length);
        printf("SmbiosMember CanBeModified: %s\n", ( member_info->can_be_modified == 1 ? "Yes" : "No"));
    }
    else
    {
        cout << "Failed retrieve Smbios Member Information!\n";
    }

    delete member_info;
#endif

#if READ_SMBIOS_API_TEST
    AaeonSmbiosGenerateJson();
#endif

    AaeonSmbiosUninitial();

    return 0;
}
