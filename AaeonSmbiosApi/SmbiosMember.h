#pragma once
#include <unordered_map>
#include <vector>
#include "MemberProp.h"

using std::string;
using std::unordered_map;
using std::vector;

// SMBIOS Member may be only string or value type.
#define VAL_TYPE 0
#define STR_TYPE 1
#define NUM_STR_TYPE 2

typedef string MemberName;
typedef unordered_map<MemberName, MemberProp> SmbiosDictionary;

class SmbiosMember
{
public:
	vector<SmbiosDictionary> smbios_tables;
	SmbiosMember();

private:
	SmbiosDictionary type0_table, type1_table, type2_table, type3_table, type4_table, 
					 type5_table, type6_table, type7_table, type8_table, type9_table,
					 type10_table, type11_table;

	void InitialType0Table();
	void InitialType1Table();
	void InitialType2Table();
	void InitialType3Table();
	void InitialType4Table();
	void InitialType5Table();
	void InitialType6Table();
	void InitialType7Table();
	void InitialType8Table();
	void InitialType9Table();
	void InitialType10Table();
	void InitialType11Table();
};

