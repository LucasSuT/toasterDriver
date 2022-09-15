#pragma once
#include <string>
#include <vector>
using namespace std;

class SmbiosData {
public:
	SmbiosData() {}
	SmbiosData(bool isString, vector<BYTE> data) :_isString(isString), _data(data) {}
	vector<BYTE> Data()
	{
		return _data;
	}
	bool IsString()
	{
		return _isString;
	}
	void SetData(vector<BYTE> data)
	{
		_data = data;
	}
private:
	bool _isString;
	vector<BYTE> _data;
};