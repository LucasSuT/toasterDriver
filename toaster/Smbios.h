#pragma once
#include <ntddk.h>
#include <stddef.h>
#include <intrin.h>
#include <wdf.h>
#include <ntstrsafe.h>
#include <wmidata.h>
#include <wmistr.h>
#include <minwindef.h>
#include "AonSimpleAPIs.h"

#pragma pack(push) 
#pragma pack(1)
typedef struct _ENTRYPOINT
{
	BYTE	AnchorString[5];
	BYTE	EntryPointStructChecksum;
	BYTE	EntryPointLength;
	BYTE	SMBIOSMajorVersion;
	BYTE	SMBIOSMinorVersion;
	BYTE	SMBIOSDocrev;
	BYTE	EntryPointRevision;
	BYTE	Reserved;
	DWORD	TableMaxSize;
	LONGLONG	TableAddress;
} ENTRYPOINT, * PENTRYPOINT;

typedef struct _SMBIOSHEADER_
{
	BYTE Type;
	BYTE Length;
	WORD Handle;
} SMBIOSHEADER, * PSMBIOSHEADER;

typedef struct _TYPE_0_ {
	SMBIOSHEADER	Header;
	UCHAR	Vendor;
	UCHAR	Version;
	UINT16	StartingAddrSeg;
	UCHAR	ReleaseDate;
	UCHAR	ROMSize;
	ULONG64 Characteristics;
	UCHAR	Extension[2]; // spec. 2.3
	UCHAR	MajorRelease;
	UCHAR	MinorRelease;
	UCHAR	ECFirmwareMajor;
	UCHAR	ECFirmwareMinor;
} BIOSInfo, * PBIOSInfo;

typedef struct _TYPE_1_ {
	SMBIOSHEADER	Header;
	UCHAR	Manufacturer;
	UCHAR	ProductName;
	UCHAR	Version;
	UCHAR	SN;
	UCHAR	UUID[16];
	UCHAR	WakeUpType;
	UCHAR	SKUNumber;
	UCHAR	Family;
} SystemInfo, * PSystemInfo;

typedef struct _TYPE_2_ {
	SMBIOSHEADER	Header;
	UCHAR	Manufacturer;
	UCHAR	Product;
	UCHAR	Version;
	UCHAR	SN;
	UCHAR	AssetTag;
	UCHAR	FeatureFlags;
	UCHAR	LocationInChassis;
	UINT16	ChassisHandle;
	UCHAR	Type;
	UCHAR	NumObjHandle;
	UINT16* pObjHandle;
} BoardInfo, * PBoardInfo;
#pragma pack(pop)
const char* toTypePoint(void* Addr, int type);
void setDataString(void* VirtualEntryPoint, int Type, int DataIndex, PUCHAR InputData, int DataSize);
BOOL ProcBIOSInfo(void* p);
BOOL ProcSysInfo(const void* p);
