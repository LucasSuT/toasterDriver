#pragma once
#include "UEFIController.h"

class SmbiosEditor
{
public:
	void SetSMBIOS(UINT8 Type, UINT16 Handle, UINT8 Offset, UINT8 Flag, vector<UINT8> data);
	static SmbiosEditor& getInstance();

private:
	UEFIContorller uefi_contorller;

	void Update(vector<UINT8>& data, const SMBIOSELEMENT& element);
	void Add(vector<UINT8>& data, const SMBIOSELEMENT& element);
	bool isExistDmiArray(const SMBIOSELEMENT& element);
	SmbiosEditor() {}
	SmbiosEditor(SmbiosEditor const&) = delete;
	void operator=(SmbiosEditor const&) = delete;
};