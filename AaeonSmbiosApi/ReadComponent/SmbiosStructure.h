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

//typedef struct _TYPE_0_ {
//	SMBIOSHEADER	Header;
//	UCHAR	Vendor;
//	UCHAR	Version;
//	UINT16	StartingAddrSeg;
//	UCHAR	ReleaseDate;
//	UCHAR	ROMSize;
//	ULONG64 Characteristics;
//	UCHAR	Extension[2]; // spec. 2.3
//	UCHAR	MajorRelease;
//	UCHAR	MinorRelease;
//	UCHAR	ECFirmwareMajor;
//	UCHAR	ECFirmwareMinor;
//	UINT16	ExtendedBiosSize;
//} BIOSInfo, * PBIOSInfo;
//
//
//typedef struct _TYPE_1_ {
//	SMBIOSHEADER	Header;
//	UCHAR	Manufacturer;
//	UCHAR	ProductName;
//	UCHAR	Version;
//	UCHAR	SN;
//	UCHAR	UUID[16];
//	UCHAR	WakeUpType;
//	UCHAR	SKUNumber;
//	UCHAR	Family;
//} SystemInfo, * PSystemInfo;
//
//typedef struct _TYPE_2_ {
//	SMBIOSHEADER	Header;
//	UCHAR	Manufacturer;
//	UCHAR	Product;
//	UCHAR	Version;
//	UCHAR	SN;
//	UCHAR	AssetTag;
//	UCHAR	FeatureFlags;
//	UCHAR	LocationInChassis;
//	UINT16	ChassisHandle;
//	UCHAR	Type;
//	UCHAR	NumObjHandle;
//	UINT16  pObjHandle;
//} BoardInfo, * PBoardInfo;
//
//typedef struct _TYPE_3_ {
//	SMBIOSHEADER Header;
//	UCHAR	Manufacturer;
//	UCHAR	Type;
//	UCHAR	Version;
//	UCHAR	SN;
//	UCHAR	AssetTag;
//	UCHAR	BootupState;
//	UCHAR	PowerSupplyState;
//	UCHAR	ThermalState;
//	UCHAR	SecurityStatus;
//	ULONG32	OEMDefine;
//	UCHAR	Height;
//	UCHAR	NumPowerCord;
//	UCHAR	ElementCount;
//	UCHAR	ElementRecordLength;
//	UCHAR	pElements;
//} SystemEnclosure, * PSystemEnclosure;
//
//typedef struct _TYPE_4_ {
//	SMBIOSHEADER Header;
//	UCHAR	socket_designation;
//	UCHAR	processor_type;
//	UCHAR	processor_family;
//	UCHAR	processor_manufacturer;
//	ULONG64 processor_id;
//	UCHAR	processor_version;
//	UCHAR	voltage;
//	UINT16	external_clock;
//	UINT16	max_speed;
//	UINT16	current_speed;
//	UCHAR   status;
//	UCHAR   processor_upgrade;
//	UINT16  l1_cache_handle;
//	UINT16  l2_cache_handle;
//	UINT16  l3_cache_handle;
//	UCHAR   serial_number;
//	UCHAR   asset_tag;
//	UCHAR   part_number;
//	UCHAR   core_count;
//	UCHAR   core_enabled;
//	UCHAR   thread_count;
//	UINT16  processor_characteristics;
//	UINT16  processor_family_2;
//	UINT16  core_count_2;
//	UINT16  core_enabled_2;
//	UINT16  thread_count_2;
//	UINT16  thread_enabled;
//
//} ProcessorInfo, * PProcessorInfo;
//
//typedef struct _TYPE_5_ {
//	SMBIOSHEADER Header;
//	// Todo, Here
//
//} MemCtrlInfo, * PMemCtrlInfo;
//
//typedef struct _TYPE_6_ {
//	SMBIOSHEADER Header;
//	UCHAR	SocketDesignation;
//	UCHAR	BankConnections;
//	UCHAR	CurrentSpeed;
//	// Todo, Here
//} MemModuleInfo, * PMemModuleInfo;
//
//typedef struct _TYPE_7_ {
//	SMBIOSHEADER Header;
//	UCHAR	socket_designation;
//	UINT16	cache_configuration;
//	UINT16	maximum_cache_size;
//	UINT16	installed_size;
//	UINT16	supported_sram_type;
//	UINT16	current_sram_type;
//	UCHAR	cache_speed;
//	UCHAR	error_correction_type;
//	UCHAR	system_cache_type;
//	UCHAR	associativity;
//	ULONG32	maximum_cache_size_2;
//	ULONG32	installed_cache_size_2;
//} CacheInfo, * PCacheInfo;
//
//typedef struct _TYPE_8_ {
//	SMBIOSHEADER Header;
//	UCHAR	internal_reference_designator;
//	UCHAR	internal_connector_type;
//	UCHAR	external_reference_designator;
//	UCHAR	external_connector_type;
//	UCHAR	port_type;
//} PortConnectorInfo, * PPortConnectorInfo;
//
//typedef struct _TYPE_9_ {
//	SMBIOSHEADER Header;
//	UCHAR	slot_designation;
//	UCHAR	slot_type;
//	UCHAR	slot_data_bus_width;
//	UCHAR	current_usage;
//	UCHAR	slot_length;
//	UINT16	slot_id;
//	UCHAR	slot_characteristics_1;
//	UCHAR	slot_characteristics_2;
//	UINT16	segment_group_number;
//	UCHAR	bus_number;
//	UCHAR	device_function_number;
//	UCHAR	data_bus_width;
//	UCHAR   peer_grouping_count;
//	UCHAR   peer_groups;
//	UCHAR   slot_information;
//	UCHAR   slot_physical_width;
//	UINT16  slot_pitch;
//	UCHAR   slot_height;
//} SystemSlots, * PSystemSlots;
//
//typedef struct _TYPE_10_ {
//	SMBIOSHEADER Header;
//	UCHAR	devicen_type;
//	UCHAR	description_string;
//} OnBoardDevicesInfo, * POnBoardDevicesInfo;
//
//typedef struct _TYPE_11_ {
//	SMBIOSHEADER Header;
//	UCHAR	count;
//} OemString, * POemString;
//
//typedef struct _TYPE_12_ {
//	SMBIOSHEADER Header;
//	UCHAR	count;
//} SystemConfigurationOptions, * PSystemConfigurationOptions;
//
//typedef struct _TYPE_13_ {
//	SMBIOSHEADER Header;
//	UCHAR	installable_languages;
//	UCHAR	flags;
//	UCHAR	reserved[15];
//	UCHAR	current_language;
//} BIOSLanguageInfo, * PBIOSLanguageInfo;
//
//typedef struct _TYPE_16_ {
//	SMBIOSHEADER Header;
//	UINT8   Location;
//	UINT8   Use;
//	UINT8   MemoryErrorCorrection;
//	UINT32  MaximumCapacity;
//	UINT16  MemoryErrorInformationHandle;
//	UINT16  NumberOfMemoryDevices;
//	UINT64  ExtendedMaximumCapacity;
//} PhysicalMemoryArray, * PPhysicalMemoryArray;
//
//typedef struct _TYPE_17_ {
//	SMBIOSHEADER Header;
//	UINT16	PhysicalArrayHandle;
//	UINT16	ErrorInformationHandle;
//	UINT16	TotalWidth;
//	UINT16	DataWidth;
//	UINT16	Size;
//	UCHAR	FormFactor;
//	UCHAR	DeviceSet;
//	UCHAR	DeviceLocator;
//	UCHAR	BankLocator;
//	UCHAR	MemoryType;
//	UINT16	TypeDetail;
//	UINT16	Speed;
//	UCHAR	Manufacturer;
//	UCHAR	SN;
//	UCHAR	AssetTag;
//	UCHAR	PN;
//	UCHAR	Attributes;
//	UINT32  ExtendedSize;
//	UINT16  ConfiguredMemoryClockSpeed;
//	UINT16  MinimumVoltage;
//	UINT16  MaximumVoltage;
//	UINT16  ConfiguredVoltage;
//} MemoryDevice, * PMemoryDevice;
//
//typedef struct _TYPE_19_ {
//	SMBIOSHEADER Header;
//	ULONG32	Starting;
//	ULONG32	Ending;
//	UINT16	Handle;
//	UCHAR	PartitionWidth;
//} MemoryArrayMappedAddress, * PMemoryArrayMappedAddress;
//
//typedef struct _TYPE_21_ {
//	SMBIOSHEADER Header;
//	UCHAR Type;
//	UCHAR Interface;
//	UCHAR NumOfButton;
//} BuiltinPointDevice, * PBuiltinPointDevice;
//
//typedef struct _TYPE_22_ {
//	SMBIOSHEADER Header;
//	UCHAR	Location;
//	UCHAR	Manufacturer;
//	UCHAR	Date;
//	UCHAR	SN;
//	UCHAR	DeviceName;
//	UCHAR   Chemistry;
//	UINT16  DesignCapacity;
//	UINT16  DesignVoltage;
//	UCHAR   SBDSVersionNumber;
//	UCHAR   MaximumErrorInBatteryData;
//	UINT16  SBDSSerialNumber;
//	UINT16	SBDSManufactureDate;
//	UCHAR   SBDSDeviceChemistry;
//	UCHAR   DesignCapacityMultiplie;
//	UINT32  OEM;
//} PortableBattery, * PPortableBattery;
#pragma pack(pop)