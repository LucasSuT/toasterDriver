#include <ntddk.h>
#include <stddef.h>
#include <intrin.h>
#include <wdf.h>
#include <ntstrsafe.h>
#include <wmidata.h>
#include <wmistr.h>

#include "AonSimpleAPIs.h"

NTSTATUS
ReadMemory(void* lpInBuffer,
	ULONG	nInBufferSize,
	void* lpOutBuffer,
	ULONG	nOutBufferSize,
	ULONG* lpBytesReturned)
{
	SVCIO_READ_MEMORY_INPUT* param;
	ULONG	size;
	PHYSICAL_ADDRESS address = { 0 };
	PVOID	maped;
	BOOLEAN	error;

	if (nInBufferSize != sizeof(SVCIO_READ_MEMORY_INPUT))
	{
		return STATUS_INVALID_PARAMETER;
	}

	param = (SVCIO_READ_MEMORY_INPUT*)lpInBuffer;
	size = param->UnitSize * param->Count;

	if (nOutBufferSize < size)
	{
		return STATUS_INVALID_PARAMETER;
	}

	//address.QuadPart = param->Address.QuadPart;

	address.HighPart = param->Address >> 32;
	address.LowPart = param->Address & 0xFFFFFFFF;

	maped = MmMapIoSpace(address, size, FALSE);

	error = FALSE;
	switch (param->UnitSize)
	{
	case 1:
		READ_REGISTER_BUFFER_UCHAR(maped, lpOutBuffer, param->Count);
		break;
	case 2:
		READ_REGISTER_BUFFER_USHORT(maped, lpOutBuffer, param->Count);
		break;
	case 4:
		READ_REGISTER_BUFFER_ULONG(maped, lpOutBuffer, param->Count);
		break;
	default:
		error = TRUE;
		break;
	}

	MmUnmapIoSpace(maped, size);

	if (error)
	{
		return STATUS_INVALID_PARAMETER;
	}

	*lpBytesReturned = nOutBufferSize;

	return STATUS_SUCCESS;
}

NTSTATUS
WriteMemory(void* lpInBuffer,
	ULONG	nInBufferSize,
	void* lpOutBuffer,
	ULONG	nOutBufferSize,
	ULONG* lpBytesReturned)
{
	UNREFERENCED_PARAMETER(lpOutBuffer);
	UNREFERENCED_PARAMETER(nOutBufferSize);

	SVCIO_WRITE_MEMORY_INPUT* param;
	ULONG size;
	PHYSICAL_ADDRESS address = { 0 };
	PVOID	maped;
	BOOLEAN	error;

	if (nInBufferSize < offsetof(SVCIO_WRITE_MEMORY_INPUT, Data))
	{
		return STATUS_INVALID_PARAMETER;
	}

	param = (SVCIO_WRITE_MEMORY_INPUT*)lpInBuffer;

	size = param->UnitSize * param->Count;
	if (nInBufferSize < size + offsetof(SVCIO_WRITE_MEMORY_INPUT, Data))
	{
		return STATUS_INVALID_PARAMETER;
	}

	//address.QuadPart = param->Address.QuadPart;
	address.HighPart = param->Address >> 32;
	address.LowPart = param->Address & 0xFFFFFFFF;


	maped = MmMapIoSpace(address, size, FALSE);

	error = FALSE;
	switch (param->UnitSize)
	{
	case 1:
		WRITE_REGISTER_BUFFER_UCHAR(maped,
			(UCHAR*)&param->Data, param->Count);
		break;
	case 2:
		WRITE_REGISTER_BUFFER_USHORT(maped,
			(USHORT*)&param->Data, param->Count);
		break;
	case 4:
		WRITE_REGISTER_BUFFER_ULONG(maped,
			(ULONG*)&param->Data, param->Count);
		break;
	default:
		error = TRUE;
		break;
	}

	MmUnmapIoSpace(maped, size);

	if (error)
	{
		return STATUS_INVALID_PARAMETER;
	}

	*lpBytesReturned = 0;

	return STATUS_SUCCESS;
}

UCHAR ReadMemByte(ULONG uAddr)
{
	UCHAR bData = 0x00;
	SVCIO_READ_MEMORY_INPUT param = { 0 };
	ULONG uSize = 0;
	ULONG uBytesReturned = 0;

	param.Address = uAddr;
	param.Count = 1;
	param.UnitSize = 1;
	uSize = param.Count * param.UnitSize;

	ReadMemory(&param, sizeof(SVCIO_READ_MEMORY_INPUT), &bData, uSize, &uBytesReturned);

	return bData;
}

VOID WriteMemByte(ULONG uAddr, UCHAR bData)
{
	SVCIO_WRITE_MEMORY_INPUT param = { 0 };
	ULONG uSize = 0;
	ULONG uBytesReturned = 0;

	param.Address = uAddr;
	param.Count = 1;
	param.UnitSize = 1;
	memcpy(&(param.Data), &bData, (ULONGLONG)(param.Count * param.UnitSize));

	uSize = (ULONG)offsetof(SVCIO_WRITE_MEMORY_INPUT, Data) + param.Count * param.UnitSize;

	WriteMemory(&param, sizeof(SVCIO_WRITE_MEMORY_INPUT), NULL, 0, &uBytesReturned);
}

USHORT ReadMemWord(ULONG uAddr)
{
	USHORT wData = 0x0000;
	SVCIO_READ_MEMORY_INPUT param = { 0 };
	ULONG uSize = 0;
	ULONG uBytesReturned = 0;

	param.Address = uAddr;
	param.Count = 1;
	param.UnitSize = 2;
	uSize = param.Count * param.UnitSize;

	ReadMemory(&param, sizeof(SVCIO_READ_MEMORY_INPUT), &wData, uSize, &uBytesReturned);

	return wData;
}
ULONG ReadMemDWord(ULONGLONG uAddr)
{
	ULONG dwData = 0x00000000;
	SVCIO_READ_MEMORY_INPUT param = { 0 };
	ULONG uSize = 0;
	ULONG uBytesReturned = 0;

	param.Address = uAddr;
	param.Count = 1;
	param.UnitSize = 4;
	uSize = param.Count * param.UnitSize;

	ReadMemory(&param, sizeof(SVCIO_READ_MEMORY_INPUT), &dwData, uSize, &uBytesReturned);

	return dwData;
}