#pragma once
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
	string GetJsonString(UCHAR* s, int size)
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
	void UpdateJsonObject(nlohmann::ordered_json& json_object, BYTE type, WORD handle, string key, string value)
	{
		string json_type = "Table_" + to_string(type);
		string json_handle = "Handle_" + to_string(handle);

		json_object[json_type][json_handle][key] = value;
	}
	void UpdateJsonObject(nlohmann::ordered_json& json_object, BYTE type, WORD handle, nlohmann::ordered_json json_value)
	{
		string json_type = "Table_" + to_string(type);
		string json_handle = "Handle_" + to_string(handle);

		for (auto itr = json_value.begin(); itr != json_value.end(); ++itr)
			json_object[json_type][json_handle][itr.key()] = *itr;
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
};

