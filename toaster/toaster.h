/*++

Copyright (c) 1990-2000 Microsoft Corporation All Rights Reserved

Module Name:

    Toaster.h

Abstract:

    Header file for the toaster driver modules.

Environment:

    Kernel mode

--*/


#if !defined(_TOASTER_H_)
#define _TOASTER_H_

#include <ntddk.h>
#include <wdf.h>
#include <wdm.h>

#define NTSTRSAFE_LIB
#include <ntstrsafe.h>
#include <wmistr.h>
#include "wmilib.h"
#include <initguid.h>
#include "driver.h"
#include "public.h"
#include "IOCTLValue.h"


// For Featured driver only
#ifdef TOASTER_FUNC_FEATURED
#include <wpprecorder.h>
#endif // TOASTER_FUNC_FEATURED

#define TOASTER_POOL_TAG (ULONG) 'saoT'

#define MOFRESOURCENAME L"ToasterWMI"

#define TOASTER_FUNC_DEVICE_LOG_ID "ToasterDevice"

//
// Define a WMI GUID to represent BFPI WMIMethod class.
//
DEFINE_GUID(AAEON_BFPI_METHOD,
    0x97845ED0, 0x4E6D, 0x11DE, 0x8A, 0x39, 0x08, 0x00, 0x20, 0x0C, 0x9A, 0x66);
// {97845ED0-4E6D-11DE-8A39-0800200C9A66}
//
// Define a WMI GUID to represent BFPI notification WMIEvent class.
//
DEFINE_GUID(AAEON_BFPI_NOTIFY,
    0x0B3CBB35, 0xE3C2, 0x45ED, 0x91, 0xC2, 0x4C, 0x5A, 0x6D, 0x19, 0x5D, 0x1C);
// {0B3CBB35-E3C2-45ED-91C2-4C5A6D195D1C}

//
// BFPI Method ID
//
#define BFPI_GLC_METHOD 0x00000000
#define BFPI_DIO_METHOD 0x00010000
#define BFPI_DIO_GETLV  0x00010001 // Brian add
#define BFPI_DIO_SETLV  0x00010002
#define BFPI_DIO_GETDIR 0x00010003 // Brian add
#define BFPI_DIO_SETDIR 0x00010004

#define BFPI_WDG_METHOD 0x00020000
#define BFPI_HWM_METHOD 0x00030000
#define BFPI_BKL_METHOD 0x00040000


//
// The device extension for the device object
//
typedef struct _FDO_DATA
{

    WDFWMIINSTANCE WmiDeviceArrivalEvent;

    BOOLEAN     WmiPowerDeviceEnableRegistered;

    TOASTER_INTERFACE_STANDARD BusInterface;

// For Featured driver only
#ifdef TOASTER_FUNC_FEATURED
    RECORDER_LOG    WppRecorderLog;
#endif // TOASTER_FUNC_FEATURED

    // for BFPI WMI Method & Notification
    PVOID     BfpiMethodDataObject;
    PVOID     BfpiNotifyDataObject;
    WCHAR     InstanceNameBuff[260];
    UNICODE_STRING wmiInstanceName;
}  FDO_DATA, *PFDO_DATA;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(FDO_DATA, ToasterFdoGetData)


//
// Connector Types
//

#define TOASTER_WMI_STD_I8042 0
#define TOASTER_WMI_STD_SERIAL 1
#define TOASTER_WMI_STD_PARALEL 2
#define TOASTER_WMI_STD_USB 3

DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_UNLOAD ToasterEvtDriverUnload;

EVT_WDF_DRIVER_DEVICE_ADD ToasterEvtDeviceAdd;

EVT_WDF_DEVICE_CONTEXT_CLEANUP ToasterEvtDeviceContextCleanup;
EVT_WDF_DEVICE_D0_ENTRY ToasterEvtDeviceD0Entry;
EVT_WDF_DEVICE_D0_EXIT ToasterEvtDeviceD0Exit;
EVT_WDF_DEVICE_PREPARE_HARDWARE ToasterEvtDevicePrepareHardware;
EVT_WDF_DEVICE_RELEASE_HARDWARE ToasterEvtDeviceReleaseHardware;

EVT_WDF_DEVICE_SELF_MANAGED_IO_INIT ToasterEvtDeviceSelfManagedIoInit;

//
// Io events callbacks.
//
EVT_WDF_IO_QUEUE_IO_READ ToasterEvtIoRead;
EVT_WDF_IO_QUEUE_IO_WRITE ToasterEvtIoWrite;
EVT_WDF_IO_QUEUE_IO_DEVICE_CONTROL ToasterEvtIoDeviceControl;
EVT_WDF_DEVICE_FILE_CREATE ToasterEvtDeviceFileCreate;
EVT_WDF_FILE_CLOSE ToasterEvtFileClose;

NTSTATUS
ToasterWmiRegistration(
    _In_ WDFDEVICE Device
    );

//
// Power events callbacks
//
EVT_WDF_DEVICE_ARM_WAKE_FROM_S0 ToasterEvtDeviceArmWakeFromS0;
EVT_WDF_DEVICE_ARM_WAKE_FROM_SX ToasterEvtDeviceArmWakeFromSx;
EVT_WDF_DEVICE_DISARM_WAKE_FROM_S0 ToasterEvtDeviceDisarmWakeFromS0;
EVT_WDF_DEVICE_DISARM_WAKE_FROM_SX ToasterEvtDeviceDisarmWakeFromSx;
EVT_WDF_DEVICE_WAKE_FROM_S0_TRIGGERED ToasterEvtDeviceWakeFromS0Triggered;
EVT_WDF_DEVICE_WAKE_FROM_SX_TRIGGERED ToasterEvtDeviceWakeFromSxTriggered;

PCHAR
DbgDevicePowerString(
    IN WDF_POWER_DEVICE_STATE Type
    );

//
// WMI event callbacks
//
EVT_WDF_WMI_INSTANCE_QUERY_INSTANCE EvtWmiInstanceStdDeviceDataQueryInstance;
EVT_WDF_WMI_INSTANCE_QUERY_INSTANCE EvtWmiInstanceToasterControlQueryInstance;
EVT_WDF_WMI_INSTANCE_SET_INSTANCE EvtWmiInstanceStdDeviceDataSetInstance;
EVT_WDF_WMI_INSTANCE_SET_INSTANCE EvtWmiInstanceToasterControlSetInstance;
EVT_WDF_WMI_INSTANCE_SET_ITEM EvtWmiInstanceToasterControlSetItem;
EVT_WDF_WMI_INSTANCE_SET_ITEM EvtWmiInstanceStdDeviceDataSetItem;
EVT_WDF_WMI_INSTANCE_EXECUTE_METHOD EvtWmiInstanceToasterControlExecuteMethod;

NTSTATUS
ToasterFireArrivalEvent(
    _In_ WDFDEVICE  Device
    );

#endif  // _TOASTER_H_

VOID PrintChars(PCHAR BufferAddress, size_t CountChars);
