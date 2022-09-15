#pragma once
#include "SmbiosTable.h"
#include "SmbiosStructure.h"
class Parser {
public:
	virtual SmbiosTable Parse(void* p) = 0;
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

