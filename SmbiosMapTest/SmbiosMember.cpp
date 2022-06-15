#include "SmbiosMember.h"

SmbiosMember::SmbiosMember()
{
	
}

void SmbiosMember::InitialType0Table()
{
	type0_table =
	{
		{"Vendor", MemberProp("string", 4, 1)},
		{"BiosVersion", MemberProp("string", 4, 1)}
	};
}
