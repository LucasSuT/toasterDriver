#include <ntddk.h>
#include <wdf.h>
#include <wdm.h>
#include "SmbiosStruct.h"
#pragma once

SIZE_T GetStructureSize(volatile UCHAR* pVirtualAddr)
{
	ULONGLONG base=(ULONGLONG)pVirtualAddr;
	pVirtualAddr += *(pVirtualAddr + 1); // point to struct end
	while ((*pVirtualAddr | *(pVirtualAddr + 1)) != 0x0)pVirtualAddr++; // skip string area
	pVirtualAddr += 2; //skip end of strcut
	DbgPrint("Toaster structur start: %2X structure end: %2X\n", base, pVirtualAddr);
	return (ULONGLONG)pVirtualAddr-base;
}

void DumpSmbiosTable(volatile UCHAR** pVirtualAddr, const UCHAR type)
{
	static int unknow_count=0;
	switch (type)
	{
		case 0x0:
		{
			READ_REGISTER_BUFFER_UCHAR(*pVirtualAddr, (PUCHAR)&BIOSInfo, sizeof(BIOSInfo));
			BIOSInfo.Size = GetStructureSize(*pVirtualAddr);
			*pVirtualAddr += BIOSInfo.Size;
			break;
		}
		case 0x1:
		{
			READ_REGISTER_BUFFER_UCHAR(*pVirtualAddr, (PUCHAR)&SystemInfo, sizeof(SystemInfo));
			SystemInfo.Size = GetStructureSize(*pVirtualAddr);
			*pVirtualAddr += SystemInfo.Size;
			break;
		}
		case 0x2:
		{
			READ_REGISTER_BUFFER_UCHAR(*pVirtualAddr, (PUCHAR)&BoardInfo, sizeof(BoardInfo));
			BoardInfo.Size = GetStructureSize(*pVirtualAddr);
			*pVirtualAddr += BoardInfo.Size;
			break;
		}
		case 0x3:
		{
			READ_REGISTER_BUFFER_UCHAR(*pVirtualAddr, (PUCHAR)&SystemEnclosure, sizeof(SystemEnclosure));
			SystemEnclosure.Size = GetStructureSize(*pVirtualAddr);
			*pVirtualAddr += SystemEnclosure.Size;
			break;
		}
		default:
		{
			READ_REGISTER_BUFFER_UCHAR(*pVirtualAddr, (PUCHAR)&UnKnow[unknow_count], sizeof(UnKnow[unknow_count]));
			UnKnow[unknow_count].Size = GetStructureSize(*pVirtualAddr);
			*pVirtualAddr += UnKnow[unknow_count].Size;
			break;
		}
	}
}


void ParsingSmbiosStructure(volatile UCHAR* pVirtualAddr,const DWORD32 length)
{
	ULONGLONG last_address = (ULONGLONG)pVirtualAddr + length;
	UCHAR type = *pVirtualAddr;
	DbgPrint("Toaster parsing start: %2X end: %2X\n", pVirtualAddr, last_address);
	while (type != 0x7F && (ULONGLONG)pVirtualAddr< last_address)
	{
		DbgPrint("Toaster in loop base: %2X base-value: %2X\n", pVirtualAddr, *pVirtualAddr);
		DumpSmbiosTable(&pVirtualAddr, *pVirtualAddr);
		DbgPrint("Toaster in loop after dump base: %2X base-value: %2X\n", pVirtualAddr, *pVirtualAddr);
		type = *pVirtualAddr;
	}
}

