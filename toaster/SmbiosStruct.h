#pragma once
#pragma pack(push) 
#pragma pack(1)

typedef struct _SMBIOSHEADER_
{
    BYTE Type;
    BYTE Length;
    UINT16 Handle;
} SMBIOSHEADER, * PSMBIOSHEADER;

struct _TYPE_0_ {
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
	UCHAR	Str[1000];
	SIZE_T	Size;
} BIOSInfo = { 0 }, * PBIOSInfo;

struct _TYPE_1_ {
	SMBIOSHEADER	Header;
	UCHAR	Manufacturer;
	UCHAR	ProductName;
	UCHAR	Version;
	UCHAR	SN;
	UCHAR	UUID[16];
	UCHAR	WakeUpType;
	UCHAR	SKUNumber;
	UCHAR	Family;
	UCHAR	Str[1000];
	SIZE_T	Size;
} SystemInfo = { 0 }, * PSystemInfo;

struct _TYPE_2_ {
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
	UCHAR	Str[1000];
	SIZE_T	Size;
} BoardInfo = { 0 }, * PBoardInfo;

struct _TYPE_3_ {
	SMBIOSHEADER Header;
	UCHAR	Manufacturer;
	UCHAR	Type;
	UCHAR	Version;
	UCHAR	SN;
	UCHAR	AssetTag;
	UCHAR	BootupState;
	UCHAR	PowerSupplyState;
	UCHAR	ThermalState;
	UCHAR	SecurityStatus;
	ULONG32	OEMDefine;
	UCHAR	Height;
	UCHAR	NumPowerCord;
	UCHAR	ElementCount;
	UCHAR	ElementRecordLength;
	UCHAR	pElements;
	UCHAR	Str[1000];
	SIZE_T	Size;
} SystemEnclosure = { 0 }, * PSystemEnclosure;

struct _TYPE_4_ {
	SMBIOSHEADER Header;
	UCHAR	SocketDesignation;
	UCHAR	Type;
	UCHAR	Family;
	UCHAR	Manufacturer;
	ULONG64 ID;
	UCHAR	Version;
	UCHAR	Voltage;
	UINT16	ExtClock;
	UINT16	MaxSpeed;
	UINT16	CurrentSpeed;
	UCHAR	Str[1000];
	SIZE_T	Size;
	// Todo, Here
} ProcessorInfo = { 0 }, * PProcessorInfo;

struct _UNKNOW_ {
	SMBIOSHEADER	Header;
	UCHAR	Str[1000];
	SIZE_T	Size;
}UnKnow[100] = { 0 };

typedef struct _SMBIOSTABLE_
{
	struct _TYPE_0_ _BIOSInfo;
	struct _TYPE_1_ _SystemInfo;
	struct _TYPE_2_ _BoardInfo;
	struct _TYPE_3_ _SystemEnclosure;
	struct _TYPE_4_ _ProcessorInfo;
	struct _UNKNOW_ _UnKnow[100];
}SmbiosTable,*PSmbiosTable;
#pragma pack(pop) 