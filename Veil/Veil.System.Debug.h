/*
 * PROJECT:   Veil
 * FILE:      Veil.System.Debug.h
 * PURPOSE:   This file is part of Veil.
 *
 * LICENSE:   MIT License
 *
 * DEVELOPER: MeeSong (meesong@outlook.com)
 */

#pragma once
#ifndef _KERNEL_MODE
#include <dpfilter.h>
#endif

// Warnings which disabled for compiling
#if _MSC_VER >= 1200
#pragma warning(push)
// nonstandard extension used : nameless struct/union
#pragma warning(disable:4201)
// nonstandard extension used : bit field types other than int
#pragma warning(disable:4214)
// 'struct_name' : structure was padded due to __declspec(align())
#pragma warning(disable:4324)
// 'enumeration': a forward declaration of an unscoped enumeration must have an
// underlying type (int assumed)
#pragma warning(disable:4471)
#endif

VEIL_BEGIN()

#if (_MSC_FULL_VER >= 150030729) && !defined(IMPORT_NATIVE_DBG_BREAK)

#define DbgBreakPoint __debugbreak

#else

__analysis_noreturn
VOID
NTAPI
DbgBreakPoint(
    VOID
);
#endif

#ifndef _KERNEL_MODE
/**
 * Causes a user-mode breakpoint to occur.
 */
NTSYSAPI
VOID
NTAPI
DbgUserBreakPoint(
    VOID
);
#endif // !_KERNEL_MODE

#define DBG_BUFFER_MAX_LENGTH       512u

#define DBG_STATUS_CONTROL_C        1
#define DBG_STATUS_SYSRQ            2
#define DBG_STATUS_BUGCHECK_FIRST   3
#define DBG_STATUS_BUGCHECK_SECOND  4
#define DBG_STATUS_FATAL            5
#define DBG_STATUS_DEBUG_CONTROL    6
#define DBG_STATUS_WORKER           7

/**
 * Sends a message to the kernel debugger.
 *
 * \param Format A pointer to a printf-style format string.
 * \param ... Arguments for the format string.
 * \return ULONG The number of characters printed.
 */
ULONG
__cdecl
DbgPrint(
    _In_z_ _Printf_format_string_ PCSTR Format,
    ...
);

/**
 * Sends a message to the kernel debugger with a component ID and level.
 *
 * \param ComponentId The ID of the component that is sending the message.
 * \param Level The importance level of the message.
 * \param Format A pointer to a printf-style format string.
 * \param ... Arguments for the format string.
 * \return ULONG The number of characters printed.
 */
NTSYSAPI
ULONG
__cdecl
DbgPrintEx(
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_z_ _Printf_format_string_ PCSTR Format,
    ...
);

/**
 * Sends a message to the kernel debugger with a component ID and level (va_list version).
 *
 * \param ComponentId The ID of the component that is sending the message.
 * \param Level The importance level of the message.
 * \param Format A pointer to a printf-style format string.
 * \param arglist A list of arguments for the format string.
 * \return ULONG The number of characters printed.
 */
NTSYSAPI
ULONG
NTAPI
vDbgPrintEx(
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_z_ PCCH Format,
    _In_ va_list arglist
);

/**
 * Sends a message to the kernel debugger with a prefix, component ID, and level.
 *
 * \param Prefix A pointer to a string to be prefixed to the message.
 * \param ComponentId The ID of the component that is sending the message.
 * \param Level The importance level of the message.
 * \param Format A pointer to a printf-style format string.
 * \param arglist A list of arguments for the format string.
 * \return ULONG The number of characters printed.
 */
NTSYSAPI
ULONG
NTAPI
vDbgPrintExWithPrefix(
    _In_z_ PCCH Prefix,
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_z_ PCCH Format,
    _In_ va_list arglist
);

/**
 * Sends a message to the kernel debugger and returns Control-C status.
 *
 * \param Format A pointer to a printf-style format string.
 * \param ... Arguments for the format string.
 * \return ULONG The number of characters printed.
 */
NTSYSAPI
ULONG
__cdecl
DbgPrintReturnControlC(
    _In_z_ _Printf_format_string_ PCCH Format,
    ...
);

/**
 * Queries the debug filter state for a component.
 *
 * \param ComponentId The ID of the component.
 * \param Level The importance level.
 * \return NTSTATUS Successful or errant status.
 */
NTSYSAPI
NTSTATUS
NTAPI
DbgQueryDebugFilterState(
    _In_ ULONG ComponentId,
    _In_ ULONG Level
);

/**
 * Sets the debug filter state for a component.
 *
 * \param ComponentId The ID of the component.
 * \param Level The importance level.
 * \param State The new state for the filter.
 * \return NTSTATUS Successful or errant status.
 */
NTSYSAPI
NTSTATUS
NTAPI
DbgSetDebugFilterState(
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_ BOOLEAN State
);

/**
 * Prompts the user for input through the kernel debugger.
 *
 * \param Prompt A pointer to a string to be displayed as the prompt.
 * \param Response A pointer to a buffer that receives the user's response.
 * \param Length The size of the response buffer, in bytes.
 * \return ULONG The number of characters read.
 */
NTSYSAPI
ULONG
NTAPI
DbgPrompt(
    _In_z_ PCCH Prompt,
    _Out_writes_bytes_(Length) PCH Response,
    _In_ ULONG Length
);

//
// System Debug
//

/**
 * The SYSDBG_COMMAND enumeration specifies the type of system debugger
 * operation requested through NtSystemDebugControl.
 */
typedef enum _SYSDBG_COMMAND
{
    SysDbgQueryModuleInformation,       // q: DBGKD_DEBUG_DATA_HEADER64
    SysDbgQueryTraceInformation,        // q: DBGKD_TRACE_DATA
    SysDbgSetTracepoint,                // s: PVOID
    SysDbgSetSpecialCall,               // s: PVOID
    SysDbgClearSpecialCalls,            // s: void
    SysDbgQuerySpecialCalls,            // q: PVOID[]
    SysDbgBreakPoint,                   // s: void
    SysDbgQueryVersion,                 // q: DBGKD_GET_VERSION64
    SysDbgReadVirtual,                  // q: SYSDBG_VIRTUAL
    SysDbgWriteVirtual,                 // s: SYSDBG_VIRTUAL
    SysDbgReadPhysical,                 // q: SYSDBG_PHYSICAL // 10
    SysDbgWritePhysical,                // s: SYSDBG_PHYSICAL
    SysDbgReadControlSpace,             // q: SYSDBG_CONTROL_SPACE
    SysDbgWriteControlSpace,            // s: SYSDBG_CONTROL_SPACE
    SysDbgReadIoSpace,                  // q: SYSDBG_IO_SPACE
    SysDbgWriteIoSpace,                 // s: SYSDBG_IO_SPACE
    SysDbgReadMsr,                      // q: SYSDBG_MSR
    SysDbgWriteMsr,                     // s: SYSDBG_MSR
    SysDbgReadBusData,                  // q: SYSDBG_BUS_DATA
    SysDbgWriteBusData,                 // s: SYSDBG_BUS_DATA
    SysDbgCheckLowMemory,               // q: ULONG // 20
    SysDbgEnableKernelDebugger,         // s: void
    SysDbgDisableKernelDebugger,        // s: void
    SysDbgGetAutoKdEnable,              // q: ULONG
    SysDbgSetAutoKdEnable,              // s: ULONG
    SysDbgGetPrintBufferSize,           // q: ULONG
    SysDbgSetPrintBufferSize,           // s: ULONG
    SysDbgGetKdUmExceptionEnable,       // q: ULONG
    SysDbgSetKdUmExceptionEnable,       // s: ULONG
    SysDbgGetTriageDump,                // q: SYSDBG_TRIAGE_DUMP
    SysDbgGetKdBlockEnable,             // q: ULONG // 30
    SysDbgSetKdBlockEnable,             // s: ULONG
    SysDbgRegisterForUmBreakInfo,       // s: HANDLE
    SysDbgGetUmBreakPid,                // q: ULONG
    SysDbgClearUmBreakPid,              // s: void
    SysDbgGetUmAttachPid,               // q: ULONG
    SysDbgClearUmAttachPid,             // s: void
    SysDbgGetLiveKernelDump,            // q: SYSDBG_LIVEDUMP_CONTROL
    SysDbgKdPullRemoteFile,             // q: SYSDBG_KD_PULL_REMOTE_FILE
    SysDbgMaxInfoClass
} SYSDBG_COMMAND, * PSYSDBG_COMMAND;

/**
 * The SYSDBG_VIRTUAL structure describes a request to read or write virtual
 * memory through the system debugger interface.
 */
typedef struct _SYSDBG_VIRTUAL
{
    PVOID Address;
    PVOID Buffer;
    ULONG Request;
} SYSDBG_VIRTUAL, * PSYSDBG_VIRTUAL;

/**
 * The SYSDBG_PHYSICAL structure describes a request to read or write physical
 * memory through the system debugger interface.
 */
typedef struct _SYSDBG_PHYSICAL
{
    PHYSICAL_ADDRESS Address;
    PVOID Buffer;
    ULONG Request;
} SYSDBG_PHYSICAL, * PSYSDBG_PHYSICAL;

/**
 * The SYSDBG_CONTROL_SPACE structure describes a request to access processor
 * control space through the system debugger interface.
 */
typedef struct _SYSDBG_CONTROL_SPACE
{
    ULONG64 Address;
    PVOID Buffer;
    ULONG Request;
    ULONG Processor;
} SYSDBG_CONTROL_SPACE, * PSYSDBG_CONTROL_SPACE;

typedef enum _INTERFACE_TYPE INTERFACE_TYPE;

/**
 * The SYSDBG_IO_SPACE structure describes a request to access I/O space
 * through the system debugger interface.
 */
typedef struct _SYSDBG_IO_SPACE
{
    ULONG64 Address;
    PVOID Buffer;
    ULONG Request;
    INTERFACE_TYPE InterfaceType;
    ULONG BusNumber;
    ULONG AddressSpace;
} SYSDBG_IO_SPACE, * PSYSDBG_IO_SPACE;

/**
 * The SYSDBG_MSR structure describes a request to read or write a model-specific
 * register (MSR) through the system debugger interface.
 */
typedef struct _SYSDBG_MSR
{
    ULONG Msr;
    ULONG64 Data;
} SYSDBG_MSR, * PSYSDBG_MSR;

typedef enum _BUS_DATA_TYPE BUS_DATA_TYPE;

/**
 * The SYSDBG_BUS_DATA structure describes a request to access bus-specific
 * configuration data through the system debugger interface.
 */
typedef struct _SYSDBG_BUS_DATA
{
    ULONG Address;
    PVOID Buffer;
    ULONG Request;
    BUS_DATA_TYPE BusDataType;
    ULONG BusNumber;
    ULONG SlotNumber;
} SYSDBG_BUS_DATA, * PSYSDBG_BUS_DATA;

/**
 * The SYSDBG_TRIAGE_DUMP structure describes parameters used when generating
 * a triage dump through the system debugger interface.
 */
typedef struct _SYSDBG_TRIAGE_DUMP
{
    ULONG Flags;
    ULONG BugCheckCode;
    ULONG_PTR BugCheckParam1;
    ULONG_PTR BugCheckParam2;
    ULONG_PTR BugCheckParam3;
    ULONG_PTR BugCheckParam4;
    ULONG ProcessHandles;
    ULONG ThreadHandles;
    PHANDLE Handles;
} SYSDBG_TRIAGE_DUMP, * PSYSDBG_TRIAGE_DUMP;

/**
 * The SYSDBG_LIVEDUMP_CONTROL_FLAGS union specifies control flags used when
 * generating a live kernel dump.
 */
typedef union _SYSDBG_LIVEDUMP_CONTROL_FLAGS
{
    struct
    {
        ULONG UseDumpStorageStack : 1;
        ULONG CompressMemoryPagesData : 1;
        ULONG IncludeUserSpaceMemoryPages : 1;
        ULONG AbortIfMemoryPressure : 1; // REDSTONE4
        ULONG SelectiveDump : 1; // WIN11
        ULONG Reserved : 27;
    };
    ULONG AsUlong;
} SYSDBG_LIVEDUMP_CONTROL_FLAGS, * PSYSDBG_LIVEDUMP_CONTROL_FLAGS;

/**
 * The SYSDBG_LIVEDUMP_CONTROL_ADDPAGES union specifies additional page
 * categories to include when generating a live kernel dump.
 */
typedef union _SYSDBG_LIVEDUMP_CONTROL_ADDPAGES
{
    struct
    {
        ULONG HypervisorPages : 1;
        ULONG NonEssentialHypervisorPages : 1; // since WIN11
        ULONG Reserved : 30;
    };
    ULONG AsUlong;
} SYSDBG_LIVEDUMP_CONTROL_ADDPAGES, * PSYSDBG_LIVEDUMP_CONTROL_ADDPAGES;

#define SYSDBG_LIVEDUMP_SELECTIVE_CONTROL_VERSION 1

/**
 * The SYSDBG_LIVEDUMP_SELECTIVE_CONTROL structure specifies selective dump
 * options for live kernel dump generation.
 */
typedef struct _SYSDBG_LIVEDUMP_SELECTIVE_CONTROL
{
    ULONG Version;
    ULONG Size;
    union
    {
        ULONGLONG Flags;
        struct
        {
            ULONGLONG ThreadKernelStacks : 1;
            ULONGLONG ReservedFlags : 63;
        };
    };
    ULONGLONG Reserved[4];
} SYSDBG_LIVEDUMP_SELECTIVE_CONTROL, * PSYSDBG_LIVEDUMP_SELECTIVE_CONTROL;

#define SYSDBG_LIVEDUMP_CONTROL_VERSION_1 1
#define SYSDBG_LIVEDUMP_CONTROL_VERSION_2 2
#define SYSDBG_LIVEDUMP_CONTROL_VERSION SYSDBG_LIVEDUMP_CONTROL_VERSION_2

/**
 * The SYSDBG_LIVEDUMP_CONTROL_V1 structure describes parameters used when
 * generating a live kernel dump (version 1).
 */
typedef struct _SYSDBG_LIVEDUMP_CONTROL_V1
{
    ULONG Version;
    ULONG BugCheckCode;
    ULONG_PTR BugCheckParam1;
    ULONG_PTR BugCheckParam2;
    ULONG_PTR BugCheckParam3;
    ULONG_PTR BugCheckParam4;
    HANDLE DumpFileHandle;
    HANDLE CancelEventHandle;
    SYSDBG_LIVEDUMP_CONTROL_FLAGS Flags;
    SYSDBG_LIVEDUMP_CONTROL_ADDPAGES AddPagesControl;
} SYSDBG_LIVEDUMP_CONTROL_V1, * PSYSDBG_LIVEDUMP_CONTROL_V1;

/**
 * The SYSDBG_LIVEDUMP_CONTROL structure describes parameters used when
 * generating a live kernel dump (current version).
 */
typedef struct _SYSDBG_LIVEDUMP_CONTROL
{
    ULONG Version;
    ULONG BugCheckCode;
    ULONG_PTR BugCheckParam1;
    ULONG_PTR BugCheckParam2;
    ULONG_PTR BugCheckParam3;
    ULONG_PTR BugCheckParam4;
    HANDLE DumpFileHandle;
    HANDLE CancelEventHandle;
    SYSDBG_LIVEDUMP_CONTROL_FLAGS Flags;
    SYSDBG_LIVEDUMP_CONTROL_ADDPAGES AddPagesControl;
    PSYSDBG_LIVEDUMP_SELECTIVE_CONTROL SelectiveControl; // since WIN11
} SYSDBG_LIVEDUMP_CONTROL, * PSYSDBG_LIVEDUMP_CONTROL;

/**
 * The SYSDBG_KD_PULL_REMOTE_FILE structure describes a request to retrieve
 * a remote file through the kernel debugger transport.
 */
typedef struct _SYSDBG_KD_PULL_REMOTE_FILE
{
    UNICODE_STRING ImageFileName;
} SYSDBG_KD_PULL_REMOTE_FILE, * PSYSDBG_KD_PULL_REMOTE_FILE;

/**
 * The NtSystemDebugControl routine provides system debugging and diagnostic control of the system.
 *
 * \param[in] Command The debug control command to execute (of type SYSDBG_COMMAND).
 * \param[in] InputBuffer Optional pointer to a buffer containing input data for the command.
 * \param[in] InputBufferLength Length, in bytes, of the input buffer.
 * \param[out] OutputBuffer Optional pointer to a buffer that receives output data from the command.
 * \param[in] OutputBufferLength Length, in bytes, of the output buffer.
 * \param[out] ReturnLength Optional pointer to a variable that receives the number of bytes returned in the output buffer.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSystemDebugControl(
    _In_ SYSDBG_COMMAND Command,
    _Inout_updates_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength,
    _Out_opt_ PULONG ReturnLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSystemDebugControl(
    _In_ SYSDBG_COMMAND Command,
    _Inout_updates_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength,
    _Out_opt_ PULONG ReturnLength
);

//
// Hard errors
//

/**
 * The HARDERROR_RESPONSE_OPTION enumeration specifies the type of user
 * interface prompt that may be displayed when a hard error occurs.
 */
typedef enum _HARDERROR_RESPONSE_OPTION
{
    OptionAbortRetryIgnore,
    OptionOk,
    OptionOkCancel,
    OptionRetryCancel,
    OptionYesNo,
    OptionYesNoCancel,
    OptionShutdownSystem,
    OptionOkNoWait,
    OptionCancelTryContinue
} HARDERROR_RESPONSE_OPTION;

/**
 * The HARDERROR_RESPONSE enumeration specifies the response returned by the
 * caller or user when handling a hard error condition.
 */
typedef enum _HARDERROR_RESPONSE
{
    ResponseReturnToCaller,
    ResponseNotHandled,
    ResponseAbort,
    ResponseCancel,
    ResponseIgnore,
    ResponseNo,
    ResponseOk,
    ResponseRetry,
    ResponseYes,
    ResponseTryAgain,
    ResponseContinue
} HARDERROR_RESPONSE;

/**
 * HARDERROR_OVERRIDE_ERRORMODE indicates that the system should ignore the
 * calling process's error mode when processing a hard error.
 */
#define HARDERROR_OVERRIDE_ERRORMODE 0x10000000

/**
 * The NtRaiseHardError routine raises a hard error or serious error dialog box being displayed to the user.
 *
 * \param[in] ErrorStatus The NTSTATUS code that describes the error condition.
 * \param[in] NumberOfParameters The number of parameters in the Parameters array.
 * \param[in] UnicodeStringParameterMask A bitmask indicating which entries in the Parameters array are Unicode strings.
 * \param[in] Parameters An array of parameters to be used in the error message.
 * \param[in] ValidResponseOptions Specifies the valid responses that the user can select in the error dialog.
 * \param[out] Response Receives the user's response to the error dialog.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtRaiseHardError(
    _In_ NTSTATUS ErrorStatus,
    _In_ ULONG NumberOfParameters,
    _In_ ULONG UnicodeStringParameterMask,
    _In_reads_(NumberOfParameters) PULONG_PTR Parameters,
    _In_ ULONG ValidResponseOptions,
    _Out_ PULONG Response
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwRaiseHardError(
    _In_ NTSTATUS ErrorStatus,
    _In_ ULONG NumberOfParameters,
    _In_ ULONG UnicodeStringParameterMask,
    _In_reads_(NumberOfParameters) PULONG_PTR Parameters,
    _In_ ULONG ValidResponseOptions,
    _Out_ PULONG Response
);

//
// Exception
//

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtRaiseException(
    _In_ PEXCEPTION_RECORD ExceptionRecord,
    _In_ PCONTEXT ContextRecord,
    _In_ BOOLEAN FirstChance
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwRaiseException(
    _In_ PEXCEPTION_RECORD ExceptionRecord,
    _In_ PCONTEXT ContextRecord,
    _In_ BOOLEAN FirstChance
);

//
// Debug Filter
//

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryDebugFilterState(
    _In_ ULONG ComponentId,
    _In_ ULONG Level
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwQueryDebugFilterState(
    _In_ ULONG ComponentId,
    _In_ ULONG Level
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetDebugFilterState(
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_ BOOLEAN State
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSetDebugFilterState(
    _In_ ULONG ComponentId,
    _In_ ULONG Level,
    _In_ BOOLEAN State
);

//
// Debug Object
//

typedef struct _DBGKM_EXCEPTION
{
    EXCEPTION_RECORD ExceptionRecord;
    ULONG FirstChance;
} DBGKM_EXCEPTION, * PDBGKM_EXCEPTION;

typedef struct _DBGKM_CREATE_THREAD
{
    ULONG SubSystemKey;
    PVOID StartAddress;
} DBGKM_CREATE_THREAD, * PDBGKM_CREATE_THREAD;

typedef struct _DBGKM_CREATE_PROCESS
{
    ULONG SubSystemKey;
    HANDLE FileHandle;
    PVOID BaseOfImage;
    ULONG DebugInfoFileOffset;
    ULONG DebugInfoSize;
    DBGKM_CREATE_THREAD InitialThread;
} DBGKM_CREATE_PROCESS, * PDBGKM_CREATE_PROCESS;

typedef struct _DBGKM_EXIT_THREAD
{
    NTSTATUS ExitStatus;
} DBGKM_EXIT_THREAD, * PDBGKM_EXIT_THREAD;

typedef struct _DBGKM_EXIT_PROCESS
{
    NTSTATUS ExitStatus;
} DBGKM_EXIT_PROCESS, * PDBGKM_EXIT_PROCESS;

typedef struct _DBGKM_LOAD_DLL
{
    HANDLE FileHandle;
    PVOID BaseOfDll;
    ULONG DebugInfoFileOffset;
    ULONG DebugInfoSize;
    PVOID NamePointer;
} DBGKM_LOAD_DLL, * PDBGKM_LOAD_DLL;

typedef struct _DBGKM_UNLOAD_DLL
{
    PVOID BaseAddress;
} DBGKM_UNLOAD_DLL, * PDBGKM_UNLOAD_DLL;

typedef enum _DBG_STATE
{
    DbgIdle,
    DbgReplyPending,
    DbgCreateThreadStateChange,
    DbgCreateProcessStateChange,
    DbgExitThreadStateChange,
    DbgExitProcessStateChange,
    DbgExceptionStateChange,
    DbgBreakpointStateChange,
    DbgSingleStepStateChange,
    DbgLoadDllStateChange,
    DbgUnloadDllStateChange
} DBG_STATE, * PDBG_STATE;

typedef struct _DBGUI_CREATE_THREAD
{
    HANDLE HandleToThread;
    DBGKM_CREATE_THREAD NewThread;
} DBGUI_CREATE_THREAD, * PDBGUI_CREATE_THREAD;

typedef struct _DBGUI_CREATE_PROCESS
{
    HANDLE HandleToProcess;
    HANDLE HandleToThread;
    DBGKM_CREATE_PROCESS NewProcess;
} DBGUI_CREATE_PROCESS, * PDBGUI_CREATE_PROCESS;

typedef struct _DBGUI_WAIT_STATE_CHANGE
{
    DBG_STATE NewState;
    CLIENT_ID AppClientId;
    union
    {
        DBGKM_EXCEPTION Exception;
        DBGUI_CREATE_THREAD CreateThread;
        DBGUI_CREATE_PROCESS CreateProcessInfo;
        DBGKM_EXIT_THREAD ExitThread;
        DBGKM_EXIT_PROCESS ExitProcess;
        DBGKM_LOAD_DLL LoadDll;
        DBGKM_UNLOAD_DLL UnloadDll;
    } StateInfo;
} DBGUI_WAIT_STATE_CHANGE, * PDBGUI_WAIT_STATE_CHANGE;

#define DEBUG_READ_EVENT        0x0001
#define DEBUG_PROCESS_ASSIGN    0x0002
#define DEBUG_SET_INFORMATION   0x0004
#define DEBUG_QUERY_INFORMATION 0x0008
#define DEBUG_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | \
    DEBUG_READ_EVENT | DEBUG_PROCESS_ASSIGN | DEBUG_SET_INFORMATION | \
    DEBUG_QUERY_INFORMATION)

#define DEBUG_KILL_ON_CLOSE 0x1

typedef enum _DEBUGOBJECTINFOCLASS
{
    DebugObjectUnusedInformation,
    DebugObjectKillProcessOnExitInformation, // s: ULONG
    MaxDebugObjectInfoClass
} DEBUGOBJECTINFOCLASS, * PDEBUGOBJECTINFOCLASS;

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateDebugObject(
    _Out_ PHANDLE DebugObjectHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG Flags
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateDebugObject(
    _Out_ PHANDLE DebugObjectHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG Flags
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtDebugActiveProcess(
    _In_ HANDLE ProcessHandle,
    _In_ HANDLE DebugObjectHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwDebugActiveProcess(
    _In_ HANDLE ProcessHandle,
    _In_ HANDLE DebugObjectHandle
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtDebugContinue(
    _In_ HANDLE DebugObjectHandle,
    _In_ PCLIENT_ID ClientId,
    _In_ NTSTATUS ContinueStatus
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwDebugContinue(
    _In_ HANDLE DebugObjectHandle,
    _In_ PCLIENT_ID ClientId,
    _In_ NTSTATUS ContinueStatus
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtRemoveProcessDebug(
    _In_ HANDLE ProcessHandle,
    _In_ HANDLE DebugObjectHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwRemoveProcessDebug(
    _In_ HANDLE ProcessHandle,
    _In_ HANDLE DebugObjectHandle
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationDebugObject(
    _In_ HANDLE DebugObjectHandle,
    _In_ DEBUGOBJECTINFOCLASS DebugObjectInformationClass,
    _In_reads_bytes_(DebugInformationLength) PVOID DebugInformation,
    _In_ ULONG DebugInformationLength,
    _Out_opt_ PULONG ReturnLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSetInformationDebugObject(
    _In_ HANDLE DebugObjectHandle,
    _In_ DEBUGOBJECTINFOCLASS DebugObjectInformationClass,
    _In_ PVOID DebugInformation,
    _In_ ULONG DebugInformationLength,
    _Out_opt_ PULONG ReturnLength
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtWaitForDebugEvent(
    _In_ HANDLE DebugObjectHandle,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout,
    _Out_ PDBGUI_WAIT_STATE_CHANGE WaitStateChange
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwWaitForDebugEvent(
    _In_ HANDLE DebugObjectHandle,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout,
    _Out_ PDBGUI_WAIT_STATE_CHANGE WaitStateChange
);

//
// Debugging UI
//

#ifndef _KERNEL_MODE
NTSYSAPI
NTSTATUS
NTAPI
DbgUiConnectToDbg(
    VOID
);

NTSYSAPI
HANDLE
NTAPI
DbgUiGetThreadDebugObject(
    VOID
);

NTSYSAPI
VOID
NTAPI
DbgUiSetThreadDebugObject(
    _In_ HANDLE DebugObject
);

NTSYSAPI
NTSTATUS
NTAPI
DbgUiWaitStateChange(
    _Out_ PDBGUI_WAIT_STATE_CHANGE StateChange,
    _In_opt_ PLARGE_INTEGER Timeout
);

NTSYSAPI
NTSTATUS
NTAPI
DbgUiContinue(
    _In_ PCLIENT_ID AppClientId,
    _In_ NTSTATUS ContinueStatus
);

NTSYSAPI
NTSTATUS
NTAPI
DbgUiStopDebugging(
    _In_ HANDLE Process
);

NTSYSAPI
NTSTATUS
NTAPI
DbgUiDebugActiveProcess(
    _In_ HANDLE Process
);

NTSYSAPI
VOID
NTAPI
DbgUiRemoteBreakin(
    _In_ PVOID Context
);

NTSYSAPI
NTSTATUS
NTAPI
DbgUiIssueRemoteBreakin(
    _In_ HANDLE Process
);

NTSYSAPI
NTSTATUS
NTAPI
DbgUiConvertStateChangeStructure(
    _In_ PDBGUI_WAIT_STATE_CHANGE StateChange,
    _Out_ LPDEBUG_EVENT DebugEvent
);

NTSYSAPI
NTSTATUS
NTAPI
DbgUiConvertStateChangeStructureEx(
    _In_ PDBGUI_WAIT_STATE_CHANGE StateChange,
    _Out_ LPDEBUG_EVENT DebugEvent
);
#endif // !_KERNEL_MODE

VEIL_END()

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
