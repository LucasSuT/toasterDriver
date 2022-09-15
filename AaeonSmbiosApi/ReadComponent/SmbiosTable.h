#pragma once
#include <string>
#include <map>
#include "SmbiosData.h"
#include <iostream>
using namespace std;

class SmbiosTable
{
public:
	SmbiosTable() {}
	SmbiosTable(BYTE type, WORD handle) :_type(type), _handle(handle) {}
	SmbiosData Query(string key)
	{
		map<string, SmbiosData>::iterator it;
		it = data_map.find(key);
		if (it != data_map.end())
		{
			return it->second;
		}
		return SmbiosData();
	}
	void Add(string key, SmbiosData data)
	{
		data_map.insert(pair<string, SmbiosData>( key, data ));
	}
	void DebugMap()
	{
		cout << "=================debug map key=====================\nmap size = ";
		cout << data_map.size()<<"\n";
		/*for (auto data : data_map)
		{
			cout << data.first<<"\n";
		}*/
		for (auto pair : data_map)
		{
			cout << pair.first << ": ";
			DebugData(pair.second);
		}
		cout << "=================debug key done=====================\n";
	}
	void DebugData(SmbiosData& data)
	{
		for (BYTE b : data.Data())
		{
			if (data.IsString())
				printf("%c", b);
			else
				printf("0x%X ", b);
		}
		cout << "\n";
	}
	BYTE Type()
	{
		return _type;
	}
	WORD Handle()
	{
		return _handle;
	}
	map<string, SmbiosData>& Map() { return data_map; }
private:
	BYTE _type;
	WORD _handle;
	map<string, SmbiosData> data_map;
};

