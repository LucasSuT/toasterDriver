#pragma once
#include <vector>
#include "MemberProp.h"
#include <utility>
#include <String>
using std::string;
using std::vector;
using std::pair;
// SMBIOS Member may be string, value or NUM_STR(Type11,Type12) type.
#define VAL_TYPE 0
#define STR_TYPE 1
#define NUM_STR_TYPE 2

typedef string MemberName;
typedef vector< pair<MemberName, MemberProp> > SmbiosDictionary;

class SmbiosMember
{
public:
	vector<SmbiosDictionary> smbios_tables;
	static SmbiosMember& GetInstance();

private:
	SmbiosDictionary type0_table,  type1_table,  type2_table,  type3_table,  type4_table, 
					 type5_table,  type6_table,  type7_table,  type8_table,  type9_table,
					 type10_table, type11_table, type12_table, type13_table, type14_table, 
                     type15_table, type16_table, type17_table, type18_table, type19_table,
		             type20_table, type21_table, type22_table, type23_table, type24_table,
		             type25_table, type26_table, type27_table, type28_table, type29_table,
		             type30_table, type31_table, type32_table, type33_table, type34_table,
		             type35_table, type36_table, type37_table, type38_table, type39_table,
		             type40_table, type41_table;

	SmbiosMember();
	SmbiosMember(SmbiosMember const&) = delete;
	void operator=(SmbiosMember const&) = delete;

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
	void InitialType12Table();
	void InitialType13Table();
	void InitialType14Table();
	void InitialType15Table();
	void InitialType16Table();
	void InitialType17Table();
	void InitialType18Table();
	void InitialType19Table();
	void InitialType20Table();
	void InitialType21Table();
	void InitialType22Table();
	void InitialType23Table();
	void InitialType24Table();
	void InitialType25Table();
	void InitialType26Table();
	void InitialType27Table();
	void InitialType28Table();
	void InitialType29Table();
	void InitialType30Table();
	void InitialType31Table();
	void InitialType32Table();
	void InitialType33Table();
	void InitialType34Table();
	void InitialType35Table();
	void InitialType36Table();
	void InitialType37Table();
	void InitialType38Table();
	void InitialType39Table();
	void InitialType40Table();
	void InitialType41Table();
};

