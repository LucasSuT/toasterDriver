#pragma once
#include "Smbios.h"
#include "stdafx.h"

#ifdef _WIN64
#define CONVERTPTRTONUM(X) ((ULONGLONG)(X))
#else
#define CONVERTPTRTONUM(X) ((ULONG)(X))
#endif

const char* toPointString(const void* p)
{
	return (char*)p + ((PSMBIOSHEADER)p)->Length;
}

const char* toTypePoint(void* Addr, int type)
{
	char* str = Addr;
	PSMBIOSHEADER p = (PSMBIOSHEADER)str;
	while (p->Type != type)
	{
		str = (char*)toPointString(str); // point to struct end
		while (0 != (*((char*)str) | *((char*)str + 1))) (char*)str++; // skip string area
		(char*)str += 2;// skip the last two nulls of the type
		p = (PSMBIOSHEADER)str;
	}
	//DbgPrint("AAEON Framework - SMBIOS get end Type =%d\n", p->Type);
	return (const char*)str;
}

const char* toHandlePoint(void* Addr, int handle)
{
	char* str = Addr;
	PSMBIOSHEADER p = (PSMBIOSHEADER)str;
	while (p->Handle != handle)
	{
		str = (char*)toPointString(str); // point to struct end
		while (0 != (*((char*)str) | *((char*)str + 1))) (char*)str++; // skip string area
		(char*)str += 2;// skip the last two nulls of the type
		p = (PSMBIOSHEADER)str;
	}
	//DbgPrint("AAEON Framework - SMBIOS get end Type =%d\n", p->Type);
	return (const char*)str;
}

const char* LocateStringA(const char* str, UINT32 i)
{
	static const char strNull[] = "Null String";
	if (0 == i || 0 == *str) return strNull;
	while (--i)
	{
		str += strlen((char*)str) + 1;
	}
	return str;
}

const char* ProcString(const void * p, UINT32 StringNumber)
{
	const char* str = toPointString(p);
	return LocateStringA(str, StringNumber);
}

PUCHAR FindTypeHandle(PVOID virtualDataEntryPoint, int Type, int Handle)
{
	const PUCHAR typeStart = (PUCHAR)toTypePoint(virtualDataEntryPoint, Type);
	const PUCHAR handleStart = (PUCHAR)toHandlePoint(typeStart, Handle);
	return handleStart;
}

void setStringData(void* VirtualEntryPoint, int Type, int Handle, int StringIndex, PUCHAR InputData, int DataSize)
{
	PENTRYPOINT SMBIOSEntryPoint = (PENTRYPOINT)VirtualEntryPoint;
	ULONG DataEntryPoint = (ULONG)SMBIOSEntryPoint->TableAddress;
	int DataEntrySize = (int)SMBIOSEntryPoint->TableMaxSize;
	PVOID virtualDataEntryPoint = GetDataTempStorage(DataEntryPoint, DataEntrySize);

	const PUCHAR TypeHandleStart = FindTypeHandle(virtualDataEntryPoint, Type, Handle);

	UINT32 stringNumber = (UINT32)*(TypeHandleStart + StringIndex);
	const PUCHAR dataStart = (const PUCHAR)ProcString(TypeHandleStart, stringNumber);
	const PUCHAR nextDataStart = (const PUCHAR)ProcString(TypeHandleStart, stringNumber + 1);
	
	int entryToNextDataSize = (int)(CONVERTPTRTONUM(nextDataStart) - CONVERTPTRTONUM(virtualDataEntryPoint));
	int NextDataToEndSize = DataEntrySize - (int)(CONVERTPTRTONUM(nextDataStart) - CONVERTPTRTONUM(virtualDataEntryPoint));
	PVOID virtualNextData = GetDataTempStorage((ULONG)(DataEntryPoint + entryToNextDataSize), NextDataToEndSize);

	int rawDataSize = (int)((ULONGLONG)nextDataStart - (ULONGLONG)dataStart);

	// process rawData
	// data small than rawData
	if (DataSize <= rawDataSize)
	{
		WRITE_REGISTER_BUFFER_UCHAR((PUCHAR)(dataStart + DataSize),
			(PUCHAR)virtualNextData, NextDataToEndSize);
	}
	else /// data bigger than rawData, must to allocate space to save data, avoid data be modified
	{
		PVOID saveData = ExAllocatePoolWithTag(NonPagedPool, NextDataToEndSize, 'TAG1');
		RtlCopyMemory(saveData, (const void*)virtualNextData, NextDataToEndSize);

		WRITE_REGISTER_BUFFER_UCHAR((PUCHAR)(dataStart + DataSize),
			(PUCHAR)saveData, NextDataToEndSize);
		ExFreePoolWithTag(saveData, 'TAG1');
	}
	//write input data
	WRITE_REGISTER_BUFFER_UCHAR(dataStart,
		InputData, DataSize);
	
	FreeDataTempStorage(virtualNextData, NextDataToEndSize);
	FreeDataTempStorage(virtualDataEntryPoint, DataEntrySize);
	
	//write data length
	DataEntrySize = DataEntrySize + DataSize - rawDataSize;
	WRITE_REGISTER_BUFFER_UCHAR( &(UCHAR)(SMBIOSEntryPoint->TableMaxSize),
		&((UCHAR)DataEntrySize), sizeof(DWORD));

}

void setData(void* VirtualEntryPoint, int Type, int Handle, int StringIndex, PUCHAR InputData, int DataSize)
{
	PENTRYPOINT SMBIOSEntryPoint = (PENTRYPOINT)VirtualEntryPoint;
	ULONG DataEntryPoint = (ULONG)SMBIOSEntryPoint->TableAddress;
	int DataEntrySize = (int)SMBIOSEntryPoint->TableMaxSize;

	//Calculate the memory location of the be modified data and the next data
	PVOID virtualDataEntryPoint = GetDataTempStorage(DataEntryPoint, DataEntrySize);
	const PUCHAR TypeHandleStart = FindTypeHandle(virtualDataEntryPoint, Type, Handle);

	WRITE_REGISTER_BUFFER_UCHAR(TypeHandleStart,
		InputData, DataSize);

	FreeDataTempStorage(virtualDataEntryPoint, DataEntrySize);
}

BOOL ProcBIOSInfo(const void* p)
{
	PBIOSInfo pBIOS = (PBIOSInfo)p;
	DbgPrint("Toaster: Type0 Vendor : %s\n", ProcString(p, pBIOS->Vendor));
	DbgPrint("Toaster: Type0 Version : %s\n", ProcString(p, pBIOS->Version));
	DbgPrint("Toaster: Type0 StartingAddrSeg : 0x%x\n", pBIOS->StartingAddrSeg);
	DbgPrint("Toaster: Type0 ReleaseDate : %s\n", ProcString(p, pBIOS->ReleaseDate));
	DbgPrint("Toaster: Type0 ROMSize : %d\n", (pBIOS->ROMSize + 1) * 64);
	if (pBIOS->Header.Length > 0x14)
	{   // for spec v2.4 and later
		DbgPrint("Toaster: Type0 System BIOS version: %d.%d\n", pBIOS->MajorRelease, pBIOS->MinorRelease);
		DbgPrint("Toaster: Type0 EC Firmware version: %d.%d\n", pBIOS->ECFirmwareMajor, pBIOS->ECFirmwareMinor);
	}
	return TRUE;
}

BOOL ProcSysInfo(const void* p)
{
	PSystemInfo pSystem = (PSystemInfo)p;

	DbgPrint("Toaster: Type1 Manufacturer : %s\n", ProcString(p, pSystem->Manufacturer));
	DbgPrint("Toaster: Type1 Product Name : %s\n", ProcString(p, pSystem->ProductName));
	DbgPrint("Toaster: Type1 Version : 0x%x\n", pSystem->Version);
	DbgPrint("Toaster: Type1 Serial Number : %s\n", ProcString(p, pSystem->SN));
	if (pSystem->Header.Length > 0x08)
	{   // for spec v2.1 and later
		DbgPrint("Toaster: Type1 UUID:");
		for (int i = 0; i < 16; ++i)
			DbgPrint("%02X", pSystem->UUID[i]);
		DbgPrint("\n");
	}

	//if (pSystem->Header.Length > 0x19)
	//{
	//	// fileds for spec. 2.4
	//	_tprintf(TEXT("SKU Number: %s\n"), LocateString(str, pSystem->SKUNumber));
	//	_tprintf(TEXT("Family: %s\n"), LocateString(str, pSystem->Family));
	//}
	return TRUE;
}

BOOL ProcBoardInfo(const void* p)
{
	UNREFERENCED_PARAMETER(p);
	/*PBoardInfo pBoard = (PBoardInfo)p;
	const char* str = toPointString(p);*/

	/*_tprintf(TEXT("%s\n"), getHeaderString(2));
	_tprintf(TEXT("Length: 0x%X\n"), pBoard->Header.Length);
	_tprintf(TEXT("Manufacturer: %s\n"), LocateString(str, pBoard->Manufacturer));
	_tprintf(TEXT("Product Name: %s\n"), LocateString(str, pBoard->Product));
	_tprintf(TEXT("Version: %s\n"), LocateString(str, pBoard->Version));
	_tprintf(TEXT("Serial Number: %s\n"), LocateString(str, pBoard->SN));
	_tprintf(TEXT("Asset Tag Number: %s\n"), LocateString(str, pBoard->AssetTag));
	if (pBoard->Header.Length > 0x08)
	{
		_tprintf(TEXT("Location in Chassis: %s\n"), LocateString(str, pBoard->LocationInChassis));
	}*/

	return TRUE;
}