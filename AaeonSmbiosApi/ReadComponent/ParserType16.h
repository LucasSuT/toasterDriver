#pragma once
#include "Parser.h"

class ParserType16 : public Parser
{
public:
	SmbiosTable Parse(void* p, nlohmann::ordered_json& json_object)
	{
		PPhysicalMemoryArray pBIOS = (PPhysicalMemoryArray)p;
		SmbiosTable smbios_table(pBIOS->Header.Type, pBIOS->Header.Handle);

		// Json Test
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("location"),                        GetJsonString(pBIOS->Location, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("use"),                             GetJsonString(pBIOS->Use, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("memory_error_correction"),         GetJsonString(pBIOS->MemoryErrorCorrection, 1));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("maximum_capacity"),                GetJsonString(pBIOS->MaximumCapacity, 4));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("memory_error_information_handle"), GetJsonString(pBIOS->MemoryErrorInformationHandle, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("number_of_memory_devices"),        GetJsonString(pBIOS->NumberOfMemoryDevices, 2));
		UpdateJsonObject(json_object, pBIOS->Header.Type, pBIOS->Header.Handle, ToLowerCase("extended_maximum_capacity"),       GetJsonString(pBIOS->ExtendedMaximumCapacity, 4));

		return smbios_table;
	}
};

