#pragma once

#include "ReClass.h"

/*
	Device specific
*/
#define RECLASS_FILE_DEVICE_ID 0x8011
#define RECLASS_FUNCTION_INDEX 0x940

#define RECLASS_REGISTER_IOCTL(index) (ULONG)CTL_CODE(RECLASS_FILE_DEVICE_ID, RECLASS_FUNCTION_INDEX + index, METHOD_BUFFERED, FILE_ANY_ACCESS)

/*
	IOCTL Codes
*/
#define RECLASS_KERNEL_IOCTL_READ_VIRTUAL_MEMORY		RECLASS_REGISTER_IOCTL(1)
#define RECLASS_KERNEL_IOCTL_WRITE_VIRTUAL_MEMORY		RECLASS_REGISTER_IOCTL(2)
#define RECLASS_KERNEL_IOCTL_PROCESS_INFORMATION		RECLASS_REGISTER_IOCTL(3)
#define RECLASS_KERNEL_IOCTL_QUERY_VIRTUAL_MEMORY		RECLASS_REGISTER_IOCTL(4)
#define RECLASS_KERNEL_IOCTL_SUSPEND_PROCESS			RECLASS_REGISTER_IOCTL(5)
#define RECLASS_KERNEL_IOCTL_RESUME_PROCESS				RECLASS_REGISTER_IOCTL(6)
#define RECLASS_KERNEL_IOCTL_TERMINATE_PROCESS			RECLASS_REGISTER_IOCTL(7)

/*
	IOCTL Structures
*/
typedef struct _RC_PROCESS_VIRTUAL_MEMORY
{
	ULONG ProcessId;
	ULONGLONG Address;
	ULONGLONG Buffer;
	ULONGLONG Size;
} RC_PROCESS_VIRTUAL_MEMORY, *PRC_PROCESS_VIRTUAL_MEMORY;

typedef struct _RC_PROCESS_INFORMATION
{
	BOOLEAN IsWow64;
	ULONGLONG ImageBase;
	ULONGLONG PebAddress;
	ULONGLONG Eprocess;
	WCHAR ImagePath[260];
} RC_PROCESS_INFORMATION, *PRC_PROCESS_INFORMATION;

typedef struct _RC_QUERY_VIRTUAL_MEMORY
{
	ULONG ProcessId;
	ULONGLONG BaseAddress;
	ULONGLONG AllocationBase;
	ULONG AllocationProtect;
	ULONGLONG RegionSize;
	ULONG State;
	ULONG Protect;
	ULONG Type;
} RC_QUERY_VIRTUAL_MEMORY, *PRC_QUERY_VIRTUAL_MEMORY;

/*
	Dispatch Handler
*/
NTSTATUS ReClassHandleDispatch(HANDLE calllerProcessId, ULONG ioctlCode, PVOID paramBuffer, ULONG paramSizeIn, ULONG paramSizeOut, BOOLEAN kernelRequest);

/*
	Kernel Functions
*/
NTSTATUS ReClassReadVirtualMemory(HANDLE processId, PVOID virtualAddress, PVOID bufferPtr, SIZE_T bufferSize);
NTSTATUS ReClassWriteVirtualMemory(HANDLE processId, PVOID virtualAddress, PVOID bufferPtr, SIZE_T bufferSize);
NTSTATUS ReClassGetProcessInformation(HANDLE processId, PRC_PROCESS_INFORMATION information);
NTSTATUS ReClassQueryVirtualMemory(HANDLE processId, PVOID baseAddress, PMEMORY_BASIC_INFORMATION memoryInfo);
NTSTATUS ReClassSuspendProcess(HANDLE processId);
NTSTATUS ReClassResumeProcess(HANDLE processId);
NTSTATUS ReClassTerminateProcess(HANDLE processId, NTSTATUS exitStatus);