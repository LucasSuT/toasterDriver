#pragma once
// ----------------------------------------------------------------- Brian: IOCTL_CODE
// Values of 0x8000 and higher can be used by vendors while less than 0x8000 are reserved for Microsoft.
#define FILE_DEVICE_AAEON 0x00008010
// Values of 0x800 and higher can be used by vendors while less than 0x800 are reserved for Microsoft.
#define AAEON_FUNC_BASE 0x801

// AAEON EAPI Initialization Function
#define AAEON_FUNC_INIT				AAEON_FUNC_BASE

// AAEON BFPI Test Tool Function
#define AAEON_BFPI_TEST_TOOL		AAEON_FUNC_BASE + 0xB0

// IOCTL code implement
//#define IOCTL_AAEON_BFPI_INIT	CTL_CODE(FILE_DEVICE_AAEON, AAEON_FUNC_INIT, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_AAEON_CALL_BFPI_METHOD CTL_CODE\
		(FILE_DEVICE_AAEON, AAEON_BFPI_TEST_TOOL + 0x00, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_AAEON_CALL_BFPI_METHOD_BUFF CTL_CODE\
		(FILE_DEVICE_AAEON, AAEON_BFPI_TEST_TOOL + 0x01, METHOD_BUFFERED, FILE_ANY_ACCESS)
