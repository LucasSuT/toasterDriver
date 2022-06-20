#pragma once
#include <unordered_map>
#include <vector>
#include "MemberProp.h"

using std::string;
using std::unordered_map;
using std::vector;

// SMBIOS Member may be only string or value type.
#define IS_VAL_TYPE 0
#define IS_STR_TYPE 1

typedef string MemberName;
typedef unordered_map<MemberName, MemberProp> SmbiosDictionary;

class SmbiosMember
{
public:
	vector<SmbiosDictionary> smbios_tables;
	SmbiosMember();

private:
	SmbiosDictionary type0_table, type1_table, type2_table;
	void InitialType0Table();
	void InitialType1Table();
	void InitialType2Table();
};

