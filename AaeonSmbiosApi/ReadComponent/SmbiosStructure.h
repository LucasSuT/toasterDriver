#include "pch.h"
#include <iostream>

#pragma once
#pragma pack(push)
#pragma pack(1)
typedef struct _RawSMBIOSData
{
	BYTE	Used20CallingMethod;
	BYTE	SMBIOSMajorVersion;
	BYTE	SMBIOSMinorVersion;
	BYTE	DmiRevision;
	DWORD	Length;
	PBYTE	SMBIOSTableData;
} RawSMBIOSData, * PRawSMBIOSData;

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
	UINT16	ExtendedBiosSize;
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
	UINT16  pObjHandle;
} BoardInfo, * PBoardInfo;

typedef struct _TYPE_3_ {
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
} SystemEnclosure, * PSystemEnclosure;

typedef struct _TYPE_4_ {
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
	// Todo, Here

} ProcessorInfo, * PProcessorInfo;

typedef struct _TYPE_5_ {
	SMBIOSHEADER Header;
	// Todo, Here

} MemCtrlInfo, * PMemCtrlInfo;

typedef struct _TYPE_6_ {
	SMBIOSHEADER Header;
	UCHAR	SocketDesignation;
	UCHAR	BankConnections;
	UCHAR	CurrentSpeed;
	// Todo, Here
} MemModuleInfo, * PMemModuleInfo;

typedef struct _TYPE_7_ {
	SMBIOSHEADER Header;
	UCHAR	SocketDesignation;
	UINT16	Configuration;
	UINT16	MaxSize;
	UINT16	InstalledSize;
	UINT16	SupportSRAMType;
	UINT16	CurrentSRAMType;
	UCHAR	Speed;
	UCHAR	ErrorCorrectionType;
	UCHAR	SystemCacheType;
	UCHAR	Associativity;
} CacheInfo, * PCacheInfo;

typedef struct _TYPE_11_ {
	SMBIOSHEADER Header;
	UCHAR	Count;
} OemString, * POemString;

typedef struct _TYPE_16_ {
	SMBIOSHEADER Header;
	UINT8   Location;
	UINT8   Use;
	UINT8   MemoryErrorCorrection;
	UINT32  MaximumCapacity;
	UINT16  MemoryErrorInformationHandle;
	UINT16  NumberOfMemoryDevices;
	UINT64  ExtendedMaximumCapacity;
} PhysicalMemoryArray, * PPhysicalMemoryArray;

typedef struct _TYPE_17_ {
	SMBIOSHEADER Header;
	UINT16	PhysicalArrayHandle;
	UINT16	ErrorInformationHandle;
	UINT16	TotalWidth;
	UINT16	DataWidth;
	UINT16	Size;
	UCHAR	FormFactor;
	UCHAR	DeviceSet;
	UCHAR	DeviceLocator;
	UCHAR	BankLocator;
	UCHAR	MemoryType;
	UINT16	TypeDetail;
	UINT16	Speed;
	UCHAR	Manufacturer;
	UCHAR	SN;
	UCHAR	AssetTag;
	UCHAR	PN;
	UCHAR	Attributes;
} MemoryDevice, * PMemoryDevice;

typedef struct _TYPE_19_ {
	SMBIOSHEADER Header;
	ULONG32	Starting;
	ULONG32	Ending;
	UINT16	Handle;
	UCHAR	PartitionWidth;
} MemoryArrayMappedAddress, * PMemoryArrayMappedAddress;

typedef struct _TYPE_21_ {
	SMBIOSHEADER Header;
	UCHAR Type;
	UCHAR Interface;
	UCHAR NumOfButton;
} BuiltinPointDevice, * PBuiltinPointDevice;

typedef struct _TYPE_22_ {
	SMBIOSHEADER Header;
	UCHAR	Location;
	UCHAR	Manufacturer;
	UCHAR	Date;
	UCHAR	SN;
	UCHAR	DeviceName;
	UCHAR   Chemistry;
	UINT16  DesignCapacity;
	UINT16  DesignVoltage;
	UCHAR   SBDSVersionNumber;
	UCHAR   MaximumErrorInBatteryData;
	UINT16  SBDSSerialNumber;
	UINT16	SBDSManufactureDate;
	UCHAR   SBDSDeviceChemistry;
	UCHAR   DesignCapacityMultiplie;
	UINT32  OEM;
} PortableBattery, * PPortableBattery;
#pragma pack(pop)