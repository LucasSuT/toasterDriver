#pragma once
#include "AaeonSmbiosApi.h"
#include "SmbiosTable.h"
#include "SmbiosStructure.h"
#include "nlohmann/json.hpp"
#include <sstream>

class Parser {
public:
	virtual SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object) = 0;
	string ToLowerCase(string s)
	{
		for (int i = 0; i < s.size(); i++)
			s[i] = (char)tolower(s[i]);
		return s;
	}
	vector<BYTE> ToVector(string s)
	{
		vector<BYTE> data;
		for (BYTE byte : s)
			data.push_back(byte);
		return data;
	}
	vector<BYTE> ToVector(UCHAR *s, int size)
	{
		vector<BYTE> data;
		for (int i = 0; i < size; i++)
		{
			data.push_back(*(s+i));
		}
		return data;
	}
	vector<BYTE> ToVector(ULONG64 s,int size)
	{
		vector<BYTE> data;
		for (int i = 0; i < size; i++)
		{
			data.push_back((BYTE)s);
			s = s >> 8;
		}
		return data;
	}
	vector<BYTE> GetString(void* p, UINT offset)
	{
		const char* str = toPointString(p);
		const string s = LocateStringA(str, offset);
		return ToVector(s);
	}
	vector<BYTE> GetOEMString(void* p)
	{
		vector<BYTE> data;
		const char* str = toPointString(p);
		const int counts_string = *((char*)p + 4);

		for (int i = 1; i <= counts_string; ++i)
		{
			vector<BYTE> each_string = ToVector(LocateStringA(str, i));
			data.insert(data.end(), each_string.begin(), each_string.end());
			data.push_back(',');
		}

		return data;
	}
	void DebugVectorString(vector<BYTE> vec)
	{
		cout << "======================================\n";
		for (char c : vec)
			cout << c; 
		cout << "\n";
		cout << "======================================\n";
	}
	void DebugVectorByte(vector<BYTE> vec)
	{
		cout << "======================================\n";
		for (BYTE b : vec)
			printf("%2X ", b);
		cout << "\n";
		cout << "======================================\n";
	}
	string GetJsonString(void* p, UINT offset)
	{
		const char* str = toPointString(p);
		return LocateStringA(str, offset);
	}
	/*string GetJsonString(UCHAR* s, int size)
	{
		stringstream ss;
		string json_string;

		for (int i = 0; i < size; ++i)
		{
			char low = s[i] & 0x0F;
			char high = (s[i] & 0xF0) >> 4;

			ss << "0x" << hex << (high & 0x0F) << (low & 0x0F) << " ";
		}

		json_string = ss.str();
		json_string.pop_back();

		return json_string;
	}
	string GetJsonString(ULONG64 s, int size)
	{
		stringstream ss;
		ss << "0x" << hex << s;

		return ss.str();
	}*/
	string GetJsonString(UCHAR* s, int size)
	{
		stringstream ss;
		string json_string = "0x";

		for (int i = size - 1; i >= 0; --i)
		{
			char low = s[i] & 0x0F;
			char high = (s[i] & 0xF0) >> 4;
			ss << hex << (high & 0x0F) << (low & 0x0F);
		}
		json_string += ss.str();
		return json_string;
	}
	nlohmann::ordered_json GetJsonOEMString(void* p)
	{
		const char* str = toPointString(p);
		const int counts_string = *((char*)p + 4);

		nlohmann::ordered_json oem_string;
		for (int i = 1; i <= counts_string; ++i)
		{
			string index = "string_" + to_string(i);
			oem_string[index] = LocateStringA(str, i);
		}

		return oem_string;
	}
	void UpdateJsonObject(nlohmann::ordered_json& json_object, BYTE type, WORD handle, UCHAR* p)
	{
		SmbiosMember* smbios_member = &SmbiosMember::GetInstance();
		SmbiosDictionary smbios_tables = smbios_member->smbios_tables[type];
		MemberName member_name = "";
		MemberProp member_prop;
		string json_type = "Table_" + to_string(type);
		string json_handle = "Handle_" + to_string(handle);
		BYTE length = ((PSMBIOSHEADER)p)->Length;
		for (const auto& s : smbios_tables)
		{	
			member_name = s.first;
			member_prop = s.second;
			if (length <= member_prop.offset_ || member_prop.is_extra_processing_ == true)
				return;
			if (s.second.data_type_ == VAL_TYPE)
				json_object[json_type][json_handle][member_name] = PackageMemberObject(GetJsonString(&(p[member_prop.offset_]), member_prop.length_), member_prop);
			else if(s.second.data_type_ == STR_TYPE)
				json_object[json_type][json_handle][member_name] = PackageMemberObject(GetJsonString((void*)p, p[member_prop.offset_]), member_prop);
		}
	}
	void UpdateNewLengthJsonObject(nlohmann::ordered_json& json_object, BYTE type, WORD handle, UCHAR* p, int index, int new_length)
	{
		SmbiosMember* smbios_member = &SmbiosMember::GetInstance();
		SmbiosDictionary smbios_tables = smbios_member->smbios_tables[type];
		MemberName member_name = "";
		MemberProp member_prop;
		string json_type = "Table_" + to_string(type);
		string json_handle = "Handle_" + to_string(handle);
		BYTE length = ((PSMBIOSHEADER)p)->Length;

		member_name = smbios_tables[index].first;
		member_prop = smbios_tables[index].second;
		member_prop.length_ = new_length;
		if (length <= member_prop.offset_)
			return;
		if (member_prop.data_type_ == VAL_TYPE)
			json_object[json_type][json_handle][member_name] = PackageMemberObject(GetJsonString(&(p[member_prop.offset_]), member_prop.length_), member_prop);
		else if (member_prop.data_type_ == STR_TYPE)
			json_object[json_type][json_handle][member_name] = PackageMemberObject(GetJsonString((void*)p, p[member_prop.offset_]), member_prop);
		
	}
	void UpdateNewOffsetJsonObject(nlohmann::ordered_json& json_object, BYTE type, WORD handle, UCHAR* p, int index, int add_offset)
	{
		SmbiosMember* smbios_member = &SmbiosMember::GetInstance();
		SmbiosDictionary smbios_tables = smbios_member->smbios_tables[type];
		MemberName member_name = "";
		MemberProp member_prop;
		string json_type = "Table_" + to_string(type);
		string json_handle = "Handle_" + to_string(handle);
		BYTE length = ((PSMBIOSHEADER)p)->Length, smbios_tables_size = (BYTE)smbios_tables.size();
		for (SmbiosDictionary::iterator iter = smbios_tables.begin() + index; iter != smbios_tables.end(); iter++)
		{
			member_name = iter->first;
			member_prop = iter->second;
			member_prop.offset_ += add_offset;
			if (length <= member_prop.offset_ || member_prop.is_extra_processing_ == true)
				return;
			if (member_prop.data_type_ == VAL_TYPE)
				json_object[json_type][json_handle][member_name] = PackageMemberObject(GetJsonString(&(p[member_prop.offset_]), member_prop.length_), member_prop);
			else if (member_prop.data_type_ == STR_TYPE)
				json_object[json_type][json_handle][member_name] = PackageMemberObject(GetJsonString((void*)p, p[member_prop.offset_]), member_prop);
		}
	}
	void UpdateNewNameJsonObject(nlohmann::ordered_json& json_object, BYTE type, WORD handle, UCHAR* p, int index, int name_number, int add_offset)
	{
		SmbiosMember* smbios_member = &SmbiosMember::GetInstance();
		SmbiosDictionary smbios_tables = smbios_member->smbios_tables[type];
		MemberName member_name = "";
		MemberProp member_prop;
		string json_type = "Table_" + to_string(type);
		string json_handle = "Handle_" + to_string(handle);
		BYTE length = ((PSMBIOSHEADER)p)->Length;

		member_name = smbios_tables[index].first + "_" + to_string(name_number);
		member_prop = smbios_tables[index].second;
		member_prop.offset_ += add_offset;
		if (length <= member_prop.offset_)
			return;
		if (member_prop.data_type_ == VAL_TYPE)
		{
			json_object[json_type][json_handle][member_name] = PackageMemberObject(GetJsonString(&(p[member_prop.offset_]), member_prop.length_), member_prop);
		}
		else if (member_prop.data_type_ == STR_TYPE)
		{
			json_object[json_type][json_handle][member_name] = PackageMemberObject(GetJsonString((void*)p, p[member_prop.offset_]), member_prop);
		}

	}
	void UpdateJsonObject(nlohmann::ordered_json& json_object, BYTE type, WORD handle, nlohmann::ordered_json json_value)
	{
		string json_type = "Table_" + to_string(type);
		string json_handle = "Handle_" + to_string(handle);

		auto package = PackageOemMemberObject(type, json_value);
		json_object[json_type][json_handle].insert(package.begin(), package.end());
	}

private:
	const string LocateStringA(const char* str, UINT i)
	{
		static const char strNull[] = "";

		if (0 == i || 0 == *str) return strNull;

		while (--i)
		{
			str += strlen((char*)str) + 1;
		}
		return str;
	}
	const char* toPointString(void* p)
	{
		return (char*)p + ((PSMBIOSHEADER)p)->Length;
	}
	nlohmann::ordered_json PackageMemberObject(string value, MemberProp prop)
	{
		nlohmann::ordered_json root;
		root = nlohmann::ordered_json::object(
			{
				{"value", value},
				{"data_type", prop.data_type_},
				{"offset", prop.offset_},
				{"length", prop.length_},
				{"can_be_modified", prop.can_be_modified_}
			}
		);
		
		return root;
	}
	nlohmann::ordered_json PackageOemMemberObject(BYTE type, nlohmann::ordered_json oem_json_value)
	{
		nlohmann::ordered_json root;
		SmbiosMember* smbios_member = &SmbiosMember::GetInstance();
		SmbiosDictionary smbios_tables = smbios_member->smbios_tables[type];
		//Get string member Prop
		MemberProp member_prop = smbios_tables[1].second;
		for (auto itr = oem_json_value.begin(); itr != oem_json_value.end(); ++itr)
		{
			nlohmann::ordered_json each_string_object = nlohmann::ordered_json::object(
				{
					{"value", *itr},
					{"data_type", member_prop.data_type_},
					{"offset", member_prop.offset_++},
					{"length", member_prop.length_},
					{"can_be_modified", member_prop.can_be_modified_}
				}
			);
			root[itr.key()] = each_string_object;
		}

		return root;
	}
};

