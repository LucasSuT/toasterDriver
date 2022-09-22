#include <iostream>
#include "AaeonSmbiosApi.h"

using namespace std;

int main()
{
    AaeonSmbiosInitial();

    SmbiosMemberInfo* member_info = new SmbiosMemberInfo();
    if ( AaeonSmbiosGetMemInfo(kSmbiosTypeBiosInformation, "bios_segment", member_info) )
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

    AaeonSmbiosUninitial();

    return 0;
}
