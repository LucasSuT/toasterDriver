#include "pch.h"
#include "SmbiosEditor.h"

SmbiosEditor& SmbiosEditor::getInstance()
{
	static SmbiosEditor smbios_editor;
	return smbios_editor;
}

void SmbiosEditor::SetSMBIOS(UINT8 Type, UINT16 Handle, UINT8 Offset, UINT8 Flag, vector<UINT8> data)
{
	SMBIOSELEMENT element{ Type,Handle,Offset ,Flag };
	if (isExistDmiArray(element))
		Update(data, element);
	else
		Add(data, element);
}

void SmbiosEditor::Update(vector<UINT8>& data, const SMBIOSELEMENT& element)
{
	uefi_contorller.WriteDmiVariable(data, element);
}

void SmbiosEditor::Add(vector<UINT8>& data, const SMBIOSELEMENT& element)
{
	uefi_contorller.WriteDmiArray(element);
	uefi_contorller.WriteDmiVariable(data, element);
}


bool SmbiosEditor::isExistDmiArray(const SMBIOSELEMENT& element)
{
	AAEONSMBIOS _aaeon_smbios = uefi_contorller.GetDmiArray();
	for (auto& it : _aaeon_smbios.Element)
	{
		if (it.Type == element.Type && it.Handle == element.Handle && it.Offset == element.Offset && it.Flag == element.Flag)
			return true;
	}
	return false;
}