#pragma once

typedef struct _SVCIO_READ_MEMORY_INPUT
{
	ULONGLONG Address;
	ULONG UnitSize;
	ULONG Count;
} SVCIO_READ_MEMORY_INPUT, * PSVCIO_READ_MEMORY_INPUT;

typedef struct _SVCIO_WRITE_MEMORY_INPUT
{
	ULONGLONG Address;
	ULONG UnitSize;
	ULONG Count;
	UCHAR Data[1];
} SVCIO_WRITE_MEMORY_INPUT, * PSVCIO_WRITE_MEMORY_INPUT;

typedef struct _POWER_MANAGEMENT_DATA
{
	WCHAR DeviceId[22];
	BOOLEAN Enable;
} POWER_MANAGEMENT_DATA, * PPOWER_MANAGEMENT_DATA;

VOID Sleep(LONG msec);
VOID Sleep_MICROSECOND(LONG umsec);


UCHAR ReadMemByte(ULONG uAddr);
VOID WriteMemByte(ULONG uAddr, UCHAR bData);
USHORT ReadMemWord(ULONG uAddr);
VOID WriteMemWord(ULONG uAddr, USHORT wData);
ULONG ReadMemDWord(ULONGLONG uAddr);
VOID WriteMemDWord(ULONGLONG uAddr, ULONG dwData);

NTSTATUS ReadCPUMsr(ULONG dwAddress, PULONG dwLowDword, PULONG dwHighDword);
CHAR ReadCPUMsrTemperature();

ULONG MsgBusRead(UCHAR bPort, USHORT wOffset);
VOID MsgBusWrite(UCHAR bPort, USHORT wOffset, ULONG dwData);
NTSTATUS aaeonPowerManagementControl(BOOLEAN bIsRestore, BOOLEAN bEnable, PPOWER_MANAGEMENT_DATA pData, PULONG pDataCnt);

PVOID GetDataTempStorage(ULONG targetAddr, int size);
VOID FreeDataTempStorage(PVOID virtualAddr, int size);