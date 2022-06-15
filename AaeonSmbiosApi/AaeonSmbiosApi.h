// AaeonSmbiosApi.h - Contains declarations of smbios feature functions
#pragma once
#include <iostream>
#include "SmbiosMember.h"

#ifdef AAEONSMBIOSAPI_EXPORTS
#define AAEONSMBIOS_API __declspec(dllexport)
#else
#define AAEONSMBIOS_API __declspec(dllimport)
#endif

SmbiosMember* smbios_member;

extern "C"
{
	AAEONSMBIOS_API void AaeonSmbiosTest();
	AAEONSMBIOS_API void AaeonSmbiosInitial();
	AAEONSMBIOS_API void AaeonSmbiosUninitial();
}