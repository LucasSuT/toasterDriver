#include <iostream>
#include "AaeonSmbiosApi.h"

using namespace std;

int main()
{
    AaeonSmbiosInitial();

    SmbiosMemberInfo* member_info = new SmbiosMemberInfo();
    if ( AaeonSmbiosGetMemInfo(kSmbiosTypeBiosInformation, "Vendor", member_info) )
    {
        printf("SmbiosMember   Type: %s\n", member_info->type);
        printf("SmbiosMember offset: %d\n", member_info->offset);
        printf("SmbiosMember length: %d\n", member_info->length);
    }
    else
    {
        cout << "Failed retrieve Smbios Member Information!\n";
    }

    delete member_info;

    AaeonSmbiosUninitial();

    return 0;
}
