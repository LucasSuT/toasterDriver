// AaeonSmbiosApi.h - Contains declarations of smbios feature functions
#pragma once
#include <iostream>
#include <string>
#include "SmbiosMember.h"

#ifdef AAEONSMBIOSAPI_EXPORTS
#define AAEONSMBIOS_API __declspec(dllexport)
#else
#define AAEONSMBIOS_API __declspec(dllimport)
#endif

// SMBIOS type macros which is according to SMBIOS 2.7 specification.
enum SmbiosType
{
	kSmbiosTypeBiosInformation = 0,
	kSmbiosTypeSystemInformation,
	kSmbiosTypeBaseboardInformation,
	kSmbiosTypeSystemEnclosure,
	kSmbiosTypeProcessorInformation,
	kSmbiosTypeMemoryControllerInformation,
	kSmbiosTypeMemoryModuleInformaton,
	kSmbiosTypeCacheInformation,
	kSmbiosTypePortConnectorInformation,
	kSmbiosTypeSystemSlots,
	kSmbiosTypeOnboardDeviceInformation,
	kSmbiosTypeOemStrings,
	kSmbiosTypeSystemConfigurationOptions,
	kSmbiosTypeBiosLanguageInformation,
	kSmbiosTypeGroupAssociations,
	kSmbiosTypeSystemEventLog,
	kSmbiosTypePhysicalMemoryArray,
	kSmbiosTypeMemoryDevice,
	kSmbiosType32bitMemoryErrorInformation,
	kSmbiosTypeMemoryArrayMappedAddress,
	kSmbiosTypeMemoryDeviceMappedAddress,
	kSmbiosTypeBuiltInPointingDevice,
	kSmbiosTypePortableBattery,
	kSmbiosTypeSystemReset,
	kSmbiosTypeHardwareSecurity,
	kSmbiosTypeSystemPowerControls,
	kSmbiosTypeVoltageProbe,
	kSmbiosTypeCoolingDevice,
	kSmbiosTypeTemperatureProbe,
	kSmbiosTypeElectricalCurrentProbe,
	kSmbiosTypeOutOfBandRemoteAccess,
	kSmbiosTypeBootIntegrityService,
	kSmbiosTypeSystemBootInformation,
	kSmbiosType64bitMemoryErrorInformation,
	kSmbiosTypeManagementDevice,
	kSmbiosTypeManagementDeviceComponent,
	kSmbiosTypeManagementDeviceThresholdData,
	kSmbiosTypeMemoryChannel,
	kSmbiosTypeIpmiDeviceInformation,
	kSmbiosTypeSystemPowerSupply,
	kSmbiosTypeAdditionalInformation,
	kSmbiosTypeOnboardDevicesExtendedInformation,
	kSmbiosTypeManagementControllerHostInterface,
	kSmbiosTypeTpmDevice
};

struct SmbiosMemberInfo
{
	unsigned char type;
	unsigned char offset;
	unsigned char length;
	bool can_be_modified;
};


extern "C"
{
	AAEONSMBIOS_API void AaeonSmbiosInitial();
	AAEONSMBIOS_API void AaeonSmbiosUninitial();

	AAEONSMBIOS_API bool AaeonSmbiosGetMemInfo(SmbiosType smbios_table_number, const string& member_name, SmbiosMemberInfo* member_info);
}