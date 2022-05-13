/*++

Copyright (c) Microsoft Corporation.  All rights reserved.

    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
    KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
    PURPOSE.

Module Name:

    Toaster.c

Abstract:

    This is a simple form of function driver for toaster device. The driver
    doesn't handle any PnP and Power events because the framework provides
    default behavior for those events. This driver has enough support to
    allow an user application (toast/notify.exe) to open the device
    interface registered by the driver and send read, write or ioctl requests.

Environment:

    Kernel mode

--*/
#include "toaster.h"
#include "AonSimpleAPIs.h"
#include "Smbios.h"

#define AAEON_WDFDEVICE L"\\Device\\Aaeon_Smbios"
#define AAEON_WDFLINKNAME L"\\DosDevices\\Aaeon_SmbiosMemoryLink"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (INIT, DriverEntry)
#pragma alloc_text (PAGE, ToasterEvtDeviceAdd)
#pragma alloc_text (PAGE, ToasterEvtIoRead)
#pragma alloc_text (PAGE, ToasterEvtIoWrite)
#pragma alloc_text (PAGE, ToasterEvtIoDeviceControl)
#endif

NTSTATUS
DriverEntry(
    IN PDRIVER_OBJECT  DriverObject,
    IN PUNICODE_STRING RegistryPath
    )
/*++

Routine Description:
    DriverEntry initializes the driver and is the first routine called by the
    system after the driver is loaded. DriverEntry configures and creates a WDF driver
    object.
    .
Parameters Description:

    DriverObject - represents the instance of the function driver that is loaded
    into memory. DriverObject is allocated by the system before the
    driver is loaded, and it is released by the system after the system unloads
    the function driver from memory.

    RegistryPath - represents the driver specific path in the Registry.
    The function driver can use the path to store driver related data between
    reboots. The path does not store hardware instance specific data.

Return Value:

    STATUS_SUCCESS if successful,
    STATUS_UNSUCCESSFUL otherwise.

--*/
{
    NTSTATUS            status = STATUS_SUCCESS;
    WDF_DRIVER_CONFIG   config;

    KdPrint(("Toaster: Function Driver Sample - Driver Framework Edition.\n"));

    //
    // Initiialize driver config to control the attributes that
    // are global to the driver. Note that framework by default
    // provides a driver unload routine. If DriverEntry creates any resources
    // that require clean-up in driver unload,
    // you can manually override the default by supplying a pointer to the EvtDriverUnload
    // callback in the config structure. In general xxx_CONFIG_INIT macros are provided to
    // initialize most commonly used members.
    //

    WDF_DRIVER_CONFIG_INIT(
        &config,
        ToasterEvtDeviceAdd
        );


    //
    // Create a framework driver object to represent our driver.
    //
    status = WdfDriverCreate(
        DriverObject,
        RegistryPath,
        WDF_NO_OBJECT_ATTRIBUTES, // Driver Attributes
        &config,          // Driver Config Info
        WDF_NO_HANDLE
        );

    if (!NT_SUCCESS(status)) {
        KdPrint( ("Toaster: WdfDriverCreate failed with status 0x%x\n", status));
    }

    return status;
}


NTSTATUS
ToasterEvtDeviceAdd(
    IN WDFDRIVER       Driver,
    IN PWDFDEVICE_INIT DeviceInit
    )
/*++
Routine Description:

    ToasterEvtDeviceAdd is called by the framework in response to AddDevice
    call from the PnP manager. We create and initialize a WDF device object to
    represent a new instance of toaster device.

Arguments:

    Driver - Handle to a framework driver object created in DriverEntry

    DeviceInit - Pointer to a framework-allocated WDFDEVICE_INIT structure.

Return Value:

    NTSTATUS

--*/
{
    NTSTATUS               status = STATUS_SUCCESS;
    PFDO_DATA              fdoData;
    WDF_IO_QUEUE_CONFIG    queueConfig;
    WDF_OBJECT_ATTRIBUTES  fdoAttributes;
    WDFDEVICE              hDevice;
    WDFQUEUE               queue;

	// Brian: Use for old convention need
	UNICODE_STRING uString;

    UNREFERENCED_PARAMETER(Driver);

    PAGED_CODE();

    KdPrint(("Toaster: ToasterEvtDeviceAdd called\n"));

    //
    // Initialize attributes and a context area for the device object.
    //
    //
    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&fdoAttributes, FDO_DATA);

	// Brian: Use old convention ---------------------------------------------------------------
	RtlInitUnicodeString(&uString, AAEON_WDFDEVICE);
	status = WdfDeviceInitAssignName(DeviceInit, &uString);
	if (!NT_SUCCESS(status))
	{
		KdPrint(("Toaster: WdfDeviceInitAssignName failed 0x%x\n", status));

		return status;
	}
	KdPrint(("Toaster: WdfDeviceInitAssignName Success\n"));

	// -----------------------------------------------------------------------------------------

    //
    // Create a framework device object.This call will in turn create
    // a WDM device object, attach to the lower stack, and set the
    // appropriate flags and attributes.
    //
    status = WdfDeviceCreate(&DeviceInit, &fdoAttributes, &hDevice);
    if (!NT_SUCCESS(status)) {
        KdPrint( ("Toaster: WdfDeviceCreate failed with status code 0x%x\n", status));
        return status;
    }
	KdPrint(("Toaster: WdfDeviceCreate Success\n"));

    //
    // Get the device context by using the accessor function specified in
    // the WDF_DECLARE_CONTEXT_TYPE_WITH_NAME macro for FDO_DATA.
    //
    fdoData = ToasterFdoGetData(hDevice);

    //
    // Tell the Framework that this device will need an interface
    //
    status = WdfDeviceCreateDeviceInterface(
                 hDevice,
                 (LPGUID) &GUID_DEVINTERFACE_TOASTER,
                 NULL // ReferenceString
             );

    if (!NT_SUCCESS (status)) {
        KdPrint( ("Toaster: WdfDeviceCreateDeviceInterface failed 0x%x\n", status));
        return status;
    }

	// Brian: Use SymbolicLink function ---------------------------------------------------------
	RtlInitUnicodeString(&uString, AAEON_WDFLINKNAME);
	status = WdfDeviceCreateSymbolicLink(hDevice, &uString);
	if (!NT_SUCCESS(status))
	{
		KdPrint(("Toaster: WdfDeviceCreateSymbolicLink failed 0x%x\n", status));
		return status;
	}
	KdPrint(("Toaster: WdfDeviceCreateSymbolicLink Success\n"));
	// ------------------------------------------------------------------------------------------

    //
    // Register I/O callbacks to tell the framework that you are interested
    // in handling IRP_MJ_READ, IRP_MJ_WRITE, and IRP_MJ_DEVICE_CONTROL requests.
    // If a specific callback function is not specified for one ofthese,
    // the request will be dispatched to the EvtIoDefault handler, if any.
    // If there is no EvtIoDefault handler, the request will be failed with
    // STATUS_INVALID_DEVICE_REQUEST.
    // WdfIoQueueDispatchParallel means that we are capable of handling
    // all the I/O requests simultaneously and we are responsible for protecting
    // data that could be accessed by these callbacks simultaneously.
    // A default queue gets all the requests that are not
    // configured for forwarding using WdfDeviceConfigureRequestDispatching.
    //
    WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(&queueConfig,  WdfIoQueueDispatchParallel);

    queueConfig.EvtIoRead = ToasterEvtIoRead;
    queueConfig.EvtIoWrite = ToasterEvtIoWrite;
    queueConfig.EvtIoDeviceControl = ToasterEvtIoDeviceControl;

    //
    // By default, Static Driver Verifier (SDV) displays a warning if it 
    // doesn't find the EvtIoStop callback on a power-managed queue. 
    // The 'assume' below causes SDV to suppress this warning. If the driver 
    // has not explicitly set PowerManaged to WdfFalse, the framework creates
    // power-managed queues when the device is not a filter driver.  Normally 
    // the EvtIoStop is required for power-managed queues, but for this driver
    // it is not needed b/c the driver doesn't hold on to the requests or 
    // forward them to other drivers. This driver completes the requests 
    // directly in the queue's handlers. If the EvtIoStop callback is not 
    // implemented, the framework waits for all driver-owned requests to be
    // done before moving in the Dx/sleep states or before removing the 
    // device, which is the correct behavior for this type of driver.
    // If the requests were taking an indeterminate amount of time to complete,
    // or if the driver forwarded the requests to a lower driver/another stack,
    // the queue should have an EvtIoStop/EvtIoResume.
    //
    __analysis_assume(queueConfig.EvtIoStop != 0);
    status = WdfIoQueueCreate(
        hDevice,
        &queueConfig,
        WDF_NO_OBJECT_ATTRIBUTES,
        &queue
        );
    __analysis_assume(queueConfig.EvtIoStop == 0);

    if (!NT_SUCCESS (status)) {

        KdPrint( ("Toaster: WdfIoQueueCreate failed 0x%x\n", status));
        return status;
    }


#if 0
    DWORD *pB = (DWORD *)buff;
    ULONG outSize = sizeof(buff);
    //UNICODE_STRING nullInstance;
    //RtlInitUnicodeString(&nullInstance, L"ACPI\\PNP0C14\\BFPI_0");
    *pB = 0; // DIO1, Output
    // for setting DIO direction
    status = IoWMIExecuteMethod(fdoData->BfpiMethodDataObject, &fdoData->wmiInstanceName, BFPI_DIO_SETDIR, 8, &outSize, buff);
    if (!NT_SUCCESS(status)) {
        KdPrint(("Toaster: IoWMIExecuteMethod failed 0x%x\n", status));
        return status;
    }

    // for setting DIO Level
    pB = (DWORD *)buff;
    PUINT16 pU16 = (PUINT16)&buff[0];
    pU16[0] = 0;  //DIO1,
    pU16[1] = 1;  // level 1
    outSize = sizeof(buff);
    status = IoWMIExecuteMethod(fdoData->BfpiMethodDataObject, &fdoData->wmiInstanceName, BFPI_DIO_SETLV, 8, &outSize, buff);
    if (!NT_SUCCESS(status)) {
        KdPrint(("Toaster: IoWMIExecuteMethod failed 0x%x\n", status));
        return status;
    }
    // for setting DIO Level
    pB = (DWORD *)buff;
    pU16[0] = 0;  //DIO1,
    pU16[1] &= (~1);  // level 0
    outSize = sizeof(buff);
    status = IoWMIExecuteMethod(fdoData->BfpiMethodDataObject, &fdoData->wmiInstanceName, BFPI_DIO_SETLV, 8, &outSize, buff);
    if (!NT_SUCCESS(status)) {
        KdPrint(("Toaster: IoWMIExecuteMethod failed 0x%x\n", status));
        return status;
    }
#endif
    return status;
}

VOID
ToasterEvtIoRead (
    WDFQUEUE      Queue,
    WDFREQUEST    Request,
    size_t        Length
    )
/*++

Routine Description:

    Performs read from the toaster device. This event is called when the
    framework receives IRP_MJ_READ requests.

Arguments:

    Queue -  Handle to the framework queue object that is associated with the
             I/O request.
    Request - Handle to a framework request object.

    Lenght - Length of the data buffer associated with the request.
                 By default, the queue does not dispatch
                 zero length read & write requests to the driver and instead to
                 complete such requests with status success. So we will never get
                 a zero length request.

Return Value:

  None.

--*/
{
    NTSTATUS    status;
    ULONG_PTR bytesCopied =0;
    WDFMEMORY memory;

    UNREFERENCED_PARAMETER(Queue);
    UNREFERENCED_PARAMETER(Length);

    PAGED_CODE();

    KdPrint(( "Toaster: ToasterEvtIoRead: Request: 0x%p, Queue: 0x%p\n",
                                    Request, Queue));

    //
    // Get the request memory and perform read operation here
    //
    status = WdfRequestRetrieveOutputMemory(Request, &memory);
    if(NT_SUCCESS(status) ) {
        //
        // Copy data into the memory buffer using WdfMemoryCopyFromBuffer
        //
    }

    WdfRequestCompleteWithInformation(Request, status, bytesCopied);
}

VOID
ToasterEvtIoWrite (
    WDFQUEUE      Queue,
    WDFREQUEST    Request,
    size_t        Length
    )
/*++

Routine Description:

    Performs write to the toaster device. This event is called when the
    framework receives IRP_MJ_WRITE requests.

Arguments:

    Queue -  Handle to the framework queue object that is associated with the
            I/O request.
    Request - Handle to a framework request object.

    Lenght - Length of the data buffer associated with the request.
                 The default property of the queue is to not dispatch
                 zero lenght read & write requests to the driver and
                 complete is with status success. So we will never get
                 a zero length request.

Return Value:

   None
--*/

{
    NTSTATUS    status;
    ULONG_PTR bytesWritten =0;
    WDFMEMORY memory;

    UNREFERENCED_PARAMETER(Queue);
    UNREFERENCED_PARAMETER(Length);

    KdPrint(("Toaster: ToasterEvtIoWrite. Request: 0x%p, Queue: 0x%p\n",
                                Request, Queue));

    PAGED_CODE();

    //
    // Get the request buffer and perform write operation here
    //
    status = WdfRequestRetrieveInputMemory(Request, &memory);
    if(NT_SUCCESS(status) ) {
        //
        // 1) Use WdfMemoryCopyToBuffer to copy data from the request
        // to driver buffer.
        // 2) Or get the buffer pointer from the request by calling
        // WdfRequestRetrieveInputBuffer
        // 3) Or you can get the buffer pointer from the memory handle
        // by calling WdfMemoryGetBuffer.
        //
        bytesWritten = Length;
    }

    WdfRequestCompleteWithInformation(Request, status, bytesWritten);

}


VOID
ToasterEvtIoDeviceControl(
    IN WDFQUEUE     Queue,
    IN WDFREQUEST   Request,
    IN size_t       OutputBufferLength,
    IN size_t       InputBufferLength,
    IN ULONG        IoControlCode
    )
/*++
Routine Description:

    This event is called when the framework receives IRP_MJ_DEVICE_CONTROL
    requests from the system.

Arguments:

    Queue - Handle to the framework queue object that is associated
            with the I/O request.
    Request - Handle to a framework request object.

    OutputBufferLength - length of the request's output buffer,
                        if an output buffer is available.
    InputBufferLength - length of the request's input buffer,
                        if an input buffer is available.

    IoControlCode - the driver-defined or system-defined I/O control code
                    (IOCTL) that is associated with the request.

Return Value:

   VOID

--*/
{
    NTSTATUS  status= STATUS_SUCCESS;

	PFDO_DATA fdoData;
	WDFDEVICE device;
	device = WdfIoQueueGetDevice(Queue);
	fdoData = ToasterFdoGetData(device);
	PDWORD32 inBuf = NULL;
	PDWORD32 outBuf = NULL;

	size_t inbufSize;
	size_t outbufSize;
    KdPrint(("Toaster: ToasterEvtIoDeviceControl called\n"));
	KdPrint(("Toaster: OutputBufferLength: %d\n", OutputBufferLength));
	

    PAGED_CODE();
	/*if (!OutputBufferLength || !InputBufferLength)
	{
		WdfRequestComplete(Request, STATUS_INVALID_PARAMETER);
		return;
	}*/

	switch (IoControlCode) {
	/*------------------------------------------------------------------------ AAEON GPIO Function-*/
	case IOCTL_AAEON_CALL_BFPI_METHOD:
	{
		KdPrint(("Toaster: IOCTL_AAEON_CALL_BFPI_METHOD Enter\n"));
		//
		// Get the device context by using the accessor function specified in
		// the WDF_DECLARE_CONTEXT_TYPE_WITH_NAME macro for FDO_DATA.
		//
		// Add by Kunyi -----------------------------------------------------------------------
		GUID BfpiMethod = AAEON_BFPI_METHOD;
		status = IoWMIOpenBlock(&BfpiMethod,
			WMIGUID_EXECUTE,
			&fdoData->BfpiMethodDataObject);
		if (!NT_SUCCESS(status)) {
			KdPrint(("Toaster: IoWMIOpenBlock failed 0x%x\n", status));
			status = STATUS_INSUFFICIENT_RESOURCES;
			break;
		}

        UCHAR buff[512] = { 0 };
		ULONG buffSize = sizeof(buff);
		status = IoWMIQueryAllData(fdoData->BfpiMethodDataObject, &buffSize, buff);
		if (!NT_SUCCESS(status)) {
			KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL,
				"Toaster: Failed, execute IoWMIQueryAllData(), return %d\n",
				status));
			status = STATUS_INSUFFICIENT_RESOURCES;
			break;
		}

		// store instance
		WNODE_ALL_DATA *pWNode = (WNODE_ALL_DATA *)buff;
		ULONG offset = *((PULONG)(buff + pWNode->OffsetInstanceNameOffsets));
		RtlStringCbCopyW(fdoData->InstanceNameBuff,
			sizeof(fdoData->InstanceNameBuff), (PCWSTR)(buff + offset + 2));
		RtlInitUnicodeString(&fdoData->wmiInstanceName, fdoData->InstanceNameBuff);

		status = WdfRequestRetrieveInputBuffer(Request, 0, &inBuf, &inbufSize);
		if (!NT_SUCCESS(status)) {
			status = STATUS_INSUFFICIENT_RESOURCES;
			break;
		}

		ASSERT(inbufSize == InputBufferLength);
		KdPrint(("Toaster: BFPI_METHOD_ID = 0x%x\n", inBuf[0]));
		KdPrint(("Toaster: Input = %d\n", inBuf[1]));
		KdPrint(("Toaster: Input Address = %p\n", &inBuf[1]));


		ASSERT(OutputBufferLength >= inbufSize);
#if 1
		// execute BFPI WMI
		DWORD32 wmiOutBuff[8] = { 0 };
		ULONG wmiOutSize = sizeof(wmiOutBuff);
		RtlCopyMemory(wmiOutBuff, &inBuf[1], sizeof(DWORD) * 2);
		status = IoWMIExecuteMethod(fdoData->BfpiMethodDataObject, &fdoData->wmiInstanceName, inBuf[0], 8,(PULONG)&wmiOutSize,(PUCHAR)wmiOutBuff);
		if (!NT_SUCCESS(status)) {
			KdPrint(("Toaster: IoWMIExecuteMethod failed 0x%x\n", status));
		}
		else
		{
			KdPrint(("Toaster: IoWMIExecuteMethod Success\n"));
			for (UINT i = 0; i < (wmiOutSize / sizeof(DWORD32)); i++)
				KdPrint(("Toaster: 0x%X\n", wmiOutBuff[i]));
		}

		status = WdfRequestRetrieveOutputBuffer(Request, 0, &outBuf, &outbufSize);
		if (!NT_SUCCESS(status)) {
			status = STATUS_INSUFFICIENT_RESOURCES;
			break;
		}

		ASSERT(outbufSize == OutputBufferLength);
		ASSERT(wmiOutSize <= outbufSize);

		KdPrint(("Toaster: OutputBufferLength = %d\n", wmiOutSize));
		RtlCopyMemory(outBuf, wmiOutBuff, wmiOutSize);
		WdfRequestSetInformation(Request, OutputBufferLength < wmiOutSize ? OutputBufferLength : wmiOutSize);
#endif	
		break;
	}
    case IOCTL_AAEON_SMBIOS_READ_MEMORY:
    {
        KdPrint(("Toaster: IOCTL_AAEON_SMBIOS_READ_MEMORY Enter\n"));

        KdPrint(("Toaster: Now IRQL is: %d\n", KeGetCurrentIrql()));

        status = WdfRequestRetrieveInputBuffer(Request, 0, &inBuf, &inbufSize);
        if (!NT_SUCCESS(status)) {
            status = STATUS_INSUFFICIENT_RESOURCES;
            break;
        }
        //// Test Read memory
        //KdPrint(("Toaster: Check 1st byte: %c \n", ReadMemByte(0x8CAC8063)));
        //KdPrint(("Toaster: Check 2nd byte: %c \n", ReadMemByte(0x8CAC8064)));
        //KdPrint(("Toaster: Check 3rd byte: %c \n", ReadMemByte(0x8CAC8065)));
        //KdPrint(("Toaster: Check 4th byte: %c \n", ReadMemByte(0x8CAC8066)));
        //KdPrint(("Toaster: Check 5th byte: %c \n", ReadMemByte(0x8CAC8067)));

        //WriteMemByte(0x8CAC8065, 'B');

        //// Test Read memory
        //KdPrint(("Toaster: Check 1st byte: %c \n", ReadMemByte(0x8CAC8063)));
        //KdPrint(("Toaster: Check 2nd byte: %c \n", ReadMemByte(0x8CAC8064)));
        //KdPrint(("Toaster: Check 3rd byte: %c \n", ReadMemByte(0x8CAC8065)));
        //KdPrint(("Toaster: Check 4th byte: %c \n", ReadMemByte(0x8CAC8066)));
        //KdPrint(("Toaster: Check 5th byte: %c \n", ReadMemByte(0x8CAC8067)));

        break;
    }
    case IOCTL_AAEON_READ_SMBIOS:
    {
        DWORD bEntryPoint = 0, bDataLength = 0;
        LONGLONG bDataEntryAddr = 0;
        status = WdfRequestRetrieveInputBuffer(Request, sizeof(AAEON_SMBIOS), &inBuf, &inbufSize);
        if (NT_SUCCESS(status))
        {
            bEntryPoint = ((PAAEON_SMBIOS)inBuf)->bEntryPoint;
        }
        else
        {
            DbgPrint("Toaster: WdfRequestRetrieveInputBuffer Error\n");
            WdfRequestComplete(Request, status);
            break;
        }
        
        PVOID VirtualEntryPoint = GetDataTempStorage(bEntryPoint, sizeof(PENTRYPOINT));

        KdPrint(("Toaster: BASE address: 0x%lx \n", bEntryPoint));
        PENTRYPOINT SMBIOSEntryPoint = (PENTRYPOINT)VirtualEntryPoint;
        KdPrint(("Toaster: Data Length: 0x%lx \n", SMBIOSEntryPoint->TableMaxSize));
        KdPrint(("Toaster: DataEntryPoint: 0x%llx \n", SMBIOSEntryPoint->TableAddress));
        bDataLength = SMBIOSEntryPoint->TableMaxSize;
        bDataEntryAddr = SMBIOSEntryPoint->TableAddress;

        UCHAR a[8] = "FREDFRE";
        setDataString(VirtualEntryPoint, 1, 1, &a[0], sizeof(a));
        
        /*KdPrint(("Toaster: ProcBIOSInfo: %d \n", ProcBIOSInfo(pVirtualDataAddr)));
        const char* a = toTypePoint(pVirtualDataAddr, 1);
        KdPrint(("Toaster: ProcSysInfo: %d \n", ProcSysInfo(a)));*/

        FreeDataTempStorage(VirtualEntryPoint, sizeof(PENTRYPOINT));
        break;
    }
    default:
        status = STATUS_INVALID_DEVICE_REQUEST;
    }
	
    //
    // Complete the Request.
    //
	WdfRequestComplete(Request, status);
}

VOID
	PrintChars(
		_In_reads_(CountChars) PCHAR BufferAddress,
		_In_ size_t CountChars
	)
{
	if (CountChars) {

		while (CountChars--) {

			if (*BufferAddress > 31
				&& *BufferAddress != 127) {

				KdPrint(("%c", *BufferAddress));

			}
			else {

				KdPrint(("."));

			}
			BufferAddress++;
		}
		KdPrint(("\n"));
	}
	return;
}

