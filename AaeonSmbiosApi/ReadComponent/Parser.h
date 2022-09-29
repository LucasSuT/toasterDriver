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
	void UpdateJsonObject(nlohmann::ordered_json& json_object, BYTE type, WORD handle, string key, string value)
	{
		string json_type = "Table_" + to_string(type);
		string json_handle = "Handle_" + to_string(handle);

		json_object[json_type][json_handle][key] = value;
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

