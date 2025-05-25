/*
 * PROJECT:   Veil
 * FILE:      Veil.System.Process.h
 * PURPOSE:   This file is part of Veil.
 *
 * LICENSE:   MIT License
 *
 * DEVELOPER: MeeSong (meesong@outlook.com)
 */

#pragma once
#include "Veil.System.SxS.h"

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

//
// Process Specific Access Rights
//

#define PROCESS_TERMINATE                  (0x0001)  
#define PROCESS_CREATE_THREAD              (0x0002)  
#define PROCESS_SET_SESSIONID              (0x0004)  
#define PROCESS_VM_OPERATION               (0x0008)  
#define PROCESS_VM_READ                    (0x0010)  
#define PROCESS_VM_WRITE                   (0x0020)  
#define PROCESS_DUP_HANDLE                 (0x0040)  
#define PROCESS_CREATE_PROCESS             (0x0080)  
#define PROCESS_SET_QUOTA                  (0x0100)  
#define PROCESS_SET_INFORMATION            (0x0200)  
#define PROCESS_QUERY_INFORMATION          (0x0400)  
#define PROCESS_SUSPEND_RESUME             (0x0800)  
#define PROCESS_SET_PORT                   (0x0800)  
#define PROCESS_QUERY_LIMITED_INFORMATION  (0x1000)  
#define PROCESS_SET_LIMITED_INFORMATION    (0x2000)  
#define PROCESS_ALL_ACCESS          (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0xFFFF)

//
// Thread Specific Access Rights
//

#define THREAD_TERMINATE                    (0x0001)  
#define THREAD_SUSPEND_RESUME               (0x0002)  
#define THREAD_ALERT                        (0x0004)  
#define THREAD_GET_CONTEXT                  (0x0008)  
#define THREAD_SET_CONTEXT                  (0x0010)  
#define THREAD_SET_INFORMATION              (0x0020)  
#define THREAD_QUERY_INFORMATION            (0x0040)  
#define THREAD_SET_THREAD_TOKEN             (0x0080)  
#define THREAD_IMPERSONATE                  (0x0100)  
#define THREAD_DIRECT_IMPERSONATION         (0x0200)  
#define THREAD_SET_LIMITED_INFORMATION      (0x0400)  
#define THREAD_QUERY_LIMITED_INFORMATION    (0x0800)  
#define THREAD_RESUME                       (0x1000)  
#define THREAD_ALL_ACCESS           (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0xFFFF)


//
// Job Object Specific Access Rights
//

#define JOB_OBJECT_ASSIGN_PROCESS           (0x0001)
#define JOB_OBJECT_SET_ATTRIBUTES           (0x0002)
#define JOB_OBJECT_QUERY                    (0x0004)
#define JOB_OBJECT_TERMINATE                (0x0008)
#define JOB_OBJECT_SET_SECURITY_ATTRIBUTES  (0x0010)
#define JOB_OBJECT_IMPERSONATE              (0x0020)
#define JOB_OBJECT_ALL_ACCESS       (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x3F )

//
// PEB
// Process information structures
//

#define GDI_HANDLE_BUFFER_SIZE32 34
#define GDI_HANDLE_BUFFER_SIZE64 60

#ifndef _WIN64
#define GDI_HANDLE_BUFFER_SIZE GDI_HANDLE_BUFFER_SIZE32
#else
#define GDI_HANDLE_BUFFER_SIZE GDI_HANDLE_BUFFER_SIZE64
#endif

typedef ULONG GDI_HANDLE_BUFFER[GDI_HANDLE_BUFFER_SIZE];

typedef ULONG GDI_HANDLE_BUFFER32[GDI_HANDLE_BUFFER_SIZE32];
typedef ULONG GDI_HANDLE_BUFFER64[GDI_HANDLE_BUFFER_SIZE64];

typedef _Function_class_(PS_POST_PROCESS_INIT_ROUTINE)
VOID NTAPI PS_POST_PROCESS_INIT_ROUTINE(
    VOID
);
typedef PS_POST_PROCESS_INIT_ROUTINE* PPS_POST_PROCESS_INIT_ROUTINE;

#ifndef FLS_MAXIMUM_AVAILABLE
#define FLS_MAXIMUM_AVAILABLE 128
#endif
#ifndef TLS_MINIMUM_AVAILABLE
#define TLS_MINIMUM_AVAILABLE 64
#endif
#ifndef TLS_EXPANSION_SLOTS
#define TLS_EXPANSION_SLOTS 1024
#endif

/**
 * The PEB_LDR_DATA structure contains information about the loaded modules for the process.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winternl/ns-winternl-peb_ldr_data
 */
typedef struct _PEB_LDR_DATA
{
    ULONG Length;
    BOOLEAN Initialized;
    HANDLE SsHandle;
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
    PVOID EntryInProgress;
    BOOLEAN ShutdownInProgress;
    HANDLE ShutdownThreadId;
} PEB_LDR_DATA, * PPEB_LDR_DATA;

typedef struct _PEB_LDR_DATA32
{
    ULONG Length;
    BOOLEAN Initialized;
    HANDLE32 SsHandle;
    LIST_ENTRY32 InLoadOrderModuleList;
    LIST_ENTRY32 InMemoryOrderModuleList;
    LIST_ENTRY32 InInitializationOrderModuleList;
    PVOID32 EntryInProgress;
    BOOLEAN ShutdownInProgress;
    HANDLE32 ShutdownThreadId;
} PEB_LDR_DATA32, * POINTER_32 PPEB_LDR_DATA32;

STATIC_ASSERT(sizeof(PEB_LDR_DATA32) == 48);

typedef struct _INITIAL_TEB
{
    struct
    {
        PVOID OldStackBase;
        PVOID OldStackLimit;
    } OldInitialTeb;
    PVOID StackBase;
    PVOID StackLimit;
    PVOID StackAllocationBase;
} INITIAL_TEB, * PINITIAL_TEB;

typedef struct _RTL_USER_PROCESS_PARAMETERS* PRTL_USER_PROCESS_PARAMETERS;
typedef struct _RTL_CRITICAL_SECTION* PRTL_CRITICAL_SECTION;

// private
#define KACF_OLDGETSHORTPATHNAME                        0x00000001
#define KACF_VERSIONLIE_NOT_USED                        0x00000002
#define KACF_GETTEMPPATH_NOT_USED                       0x00000004
#define KACF_GETDISKFREESPACE                           0x00000008
#define KACF_FTMFROMCURRENTAPT                          0x00000020
#define KACF_DISALLOWORBINDINGCHANGES                   0x00000040
#define KACF_OLE32VALIDATEPTRS                          0x00000080
#define KACF_DISABLECICERO                              0x00000100
#define KACF_OLE32ENABLEASYNCDOCFILE                    0x00000200
#define KACF_OLE32ENABLELEGACYEXCEPTIONHANDLING         0x00000400
#define KACF_RPCDISABLENDRCLIENTHARDENING               0x00000800
#define KACF_RPCDISABLENDRMAYBENULL_SIZEIS              0x00001000
#define KACF_DISABLEALLDDEHACK_NOT_USED                 0x00002000
#define KACF_RPCDISABLENDR61_RANGE                      0x00004000
#define KACF_RPC32ENABLELEGACYEXCEPTIONHANDLING         0x00008000
#define KACF_OLE32DOCFILEUSELEGACYNTFSFLAGS             0x00010000
#define KACF_RPCDISABLENDRCONSTIIDCHECK                 0x00020000
#define KACF_USERDISABLEFORWARDERPATCH                  0x00040000
#define KACF_OLE32DISABLENEW_WMPAINT_DISPATCH           0x00100000
#define KACF_ADDRESTRICTEDSIDINCOINITIALIZESECURITY     0x00200000
#define KACF_ALLOCDEBUGINFOFORCRITSECTIONS              0x00400000
#define KACF_OLEAUT32ENABLEUNSAFELOADTYPELIBRELATIVE    0x00800000
#define KACF_ALLOWMAXIMIZEDWINDOWGAMMA                  0x01000000
#define KACF_DONOTADDTOCACHE                            0x80000000

// private
#define API_SET_SECTION_NAME ".apiset"

// private
#define API_SET_SCHEMA_VERSION_V2 0x00000002 // WIN7, WIN8
#define API_SET_SCHEMA_VERSION_V4 0x00000004 // WINBLUE
#define API_SET_SCHEMA_VERSION_V6 0x00000006 // since THRESHOLD
#define API_SET_SCHEMA_VERSION API_SET_SCHEMA_VERSION_V6

// private
#define API_SET_SCHEMA_FLAGS_SEALED 0x00000001
#define API_SET_SCHEMA_FLAGS_HOST_EXTENSION 0x00000002

// private
#define API_SET_SCHEMA_ENTRY_FLAGS_SEALED 0x00000001
#define API_SET_SCHEMA_ENTRY_FLAGS_EXTENSION 0x00000002

// private
typedef struct _API_SET_VALUE_ENTRY_V2
{
    ULONG NameOffset;   // to WCHAR[NameLength / sizeof(WCHAR)], from schema base
    ULONG NameLength;
    ULONG ValueOffset;  // to WCHAR[ValueLength / sizeof(WCHAR)], from schema base
    ULONG ValueLength;
} API_SET_VALUE_ENTRY_V2, *PAPI_SET_VALUE_ENTRY_V2;

// private
typedef struct _API_SET_VALUE_ARRAY_V2
{
    ULONG Count;
    _Field_size_full_(Count) API_SET_VALUE_ENTRY_V2 Array[ANYSIZE_ARRAY];
} API_SET_VALUE_ARRAY_V2, *PAPI_SET_VALUE_ARRAY_V2;

// private
typedef struct _API_SET_NAMESPACE_ENTRY_V2
{
    ULONG NameOffset; // to WCHAR[NameLength / sizeof(WCHAR)], from schema base
    ULONG NameLength;
    ULONG DataOffset; // to API_SET_VALUE_ARRAY_V2, from schema base
} API_SET_NAMESPACE_ENTRY_V2, *PAPI_SET_NAMESPACE_ENTRY_V2;

// private // PEB->ApiSetMap on WIN7, WIN8
typedef struct _API_SET_NAMESPACE_ARRAY_V2
{
    ULONG Version; // API_SET_SCHEMA_VERSION_V2
    ULONG Count;
    _Field_size_full_(Count) API_SET_NAMESPACE_ENTRY_V2 Array[ANYSIZE_ARRAY];
} API_SET_NAMESPACE_ARRAY_V2, *PAPI_SET_NAMESPACE_ARRAY_V2;

// private
typedef struct _API_SET_VALUE_ENTRY_V4
{
    ULONG Flags;
    ULONG NameOffset;  // to WCHAR[NameLength / sizeof(WCHAR)], from schema base
    ULONG NameLength;
    ULONG ValueOffset; // to WCHAR[ValueLength / sizeof(WCHAR)], from schema base
    ULONG ValueLength;
} API_SET_VALUE_ENTRY_V4, *PAPI_SET_VALUE_ENTRY_V4;

// private
typedef struct _API_SET_VALUE_ARRAY_V4
{
    ULONG Flags;
    ULONG Count;
    _Field_size_full_(Count) API_SET_VALUE_ENTRY_V4 Array[ANYSIZE_ARRAY];
} API_SET_VALUE_ARRAY_V4, *PAPI_SET_VALUE_ARRAY_V4;

// private
typedef struct _API_SET_NAMESPACE_ENTRY_V4
{
    ULONG Flags;        // API_SET_SCHEMA_ENTRY_FLAGS_*
    ULONG NameOffset;   // to WCHAR[NameLength / sizeof(WCHAR)], from schema base
    ULONG NameLength;
    ULONG AliasOffset;  // to WCHAR[AliasLength / sizeof(WCHAR)], from schema base
    ULONG AliasLength;
    ULONG DataOffset;   // to API_SET_VALUE_ARRAY_V4, from schema base
} API_SET_NAMESPACE_ENTRY_V4, *PAPI_SET_NAMESPACE_ENTRY_V4;

// private // PEB->ApiSetMap on WINBLUE
typedef struct _API_SET_NAMESPACE_ARRAY_V4
{
    ULONG Version; // API_SET_SCHEMA_VERSION_V4
    ULONG Size;
    ULONG Flags; // API_SET_SCHEMA_FLAGS_*
    ULONG Count;
    _Field_size_full_(Count) API_SET_NAMESPACE_ENTRY_V4 Array[ANYSIZE_ARRAY];
} API_SET_NAMESPACE_ARRAY_V4, *PAPI_SET_NAMESPACE_ARRAY_V4;

// private
typedef struct _API_SET_VALUE_ENTRY
{
    ULONG Flags;
    ULONG NameOffset;  // to WCHAR[NameLength / sizeof(WCHAR)], from schema base
    ULONG NameLength;
    ULONG ValueOffset; // to WCHAR[ValueLength / sizeof(WCHAR)], from schema base
    ULONG ValueLength;
} API_SET_VALUE_ENTRY, *PAPI_SET_VALUE_ENTRY;

// private
typedef struct _API_SET_NAMESPACE_ENTRY
{
    ULONG Flags;      // API_SET_SCHEMA_ENTRY_FLAGS_*
    ULONG NameOffset; // to WCHAR[NameLength / sizeof(WCHAR)], from schema base
    ULONG NameLength;
    ULONG HashedLength;
    ULONG ValueOffset; // to API_SET_VALUE_ENTRY[ValueCount], from schema base
    ULONG ValueCount;
} API_SET_NAMESPACE_ENTRY, *PAPI_SET_NAMESPACE_ENTRY;

// private
typedef struct _API_SET_HASH_ENTRY
{
    ULONG Hash;
    ULONG Index;
} API_SET_HASH_ENTRY, *PAPI_SET_HASH_ENTRY;

// private // PEB->ApiSetMap since THRESHOLD
typedef struct _API_SET_NAMESPACE
{
    ULONG Version;      // API_SET_SCHEMA_VERSION_V6
    ULONG Size;
    ULONG Flags;        // API_SET_SCHEMA_FLAGS_*
    ULONG Count;
    ULONG EntryOffset;  // to API_SET_NAMESPACE_ENTRY[Count], from this struct base
    ULONG HashOffset;   // to API_SET_HASH_ENTRY[Count], from this struct base
    ULONG HashFactor;
} API_SET_NAMESPACE, *PAPI_SET_NAMESPACE;

// PEB->TelemetryCoverageHeader
typedef struct _TELEMETRY_COVERAGE_HEADER
{
    UCHAR MajorVersion;
    UCHAR MinorVersion;
    struct
    {
        USHORT TracingEnabled : 1;
        USHORT Reserved1 : 15;
    };
    ULONG HashTableEntries;
    ULONG HashIndexMask;
    ULONG TableUpdateVersion;
    ULONG TableSizeInBytes;
    ULONG LastResetTick;
    ULONG ResetRound;
    ULONG Reserved2;
    ULONG RecordedCount;
    ULONG Reserved3[4];
    ULONG HashTable[ANYSIZE_ARRAY];
} TELEMETRY_COVERAGE_HEADER, * PTELEMETRY_COVERAGE_HEADER;

typedef struct _WER_RECOVERY_INFO
{
    ULONG Length;
    PVOID Callback;
    PVOID Parameter;
    HANDLE Started;
    HANDLE Finished;
    HANDLE InProgress;
    LONG LastError;
    BOOL Successful;
    ULONG PingInterval;
    ULONG Flags;
} WER_RECOVERY_INFO, * PWER_RECOVERY_INFO;

typedef struct _WER_FILE
{
    USHORT Flags;
    WCHAR Path[MAX_PATH];
} WER_FILE, * PWER_FILE;

typedef struct _WER_MEMORY
{
    PVOID Address;
    ULONG Size;
} WER_MEMORY, * PWER_MEMORY;

typedef struct _WER_GATHER
{
    PVOID Next;
    USHORT Flags;
    union
    {
        WER_FILE File;
        WER_MEMORY Memory;
    } v;
} WER_GATHER, * PWER_GATHER;

typedef struct _WER_METADATA
{
    PVOID Next;
    WCHAR Key[64];
    WCHAR Value[128];
} WER_METADATA, * PWER_METADATA;

typedef struct _WER_RUNTIME_DLL
{
    PVOID Next;
    ULONG Length;
    PVOID Context;
    WCHAR CallbackDllPath[MAX_PATH];
} WER_RUNTIME_DLL, * PWER_RUNTIME_DLL;

typedef struct _WER_DUMP_COLLECTION
{
    PVOID Next;
    ULONG ProcessId;
    ULONG ThreadId;
} WER_DUMP_COLLECTION, * PWER_DUMP_COLLECTION;

typedef struct _WER_HEAP_MAIN_HEADER
{
    WCHAR Signature[16];
    LIST_ENTRY Links;
    HANDLE Mutex;
    PVOID FreeHeap;
    ULONG FreeCount;
} WER_HEAP_MAIN_HEADER, * PWER_HEAP_MAIN_HEADER;

#ifndef RESTART_MAX_CMD_LINE
#define RESTART_MAX_CMD_LINE 1024
#endif

typedef struct _WER_PEB_HEADER_BLOCK
{
    LONG Length;
    WCHAR Signature[16];
    WCHAR AppDataRelativePath[64];
    WCHAR RestartCommandLine[RESTART_MAX_CMD_LINE];
    WER_RECOVERY_INFO RecoveryInfo;
    PWER_GATHER Gather;
    PWER_METADATA MetaData;
    PWER_RUNTIME_DLL RuntimeDll;
    PWER_DUMP_COLLECTION DumpCollection;
    LONG GatherCount;
    LONG MetaDataCount;
    LONG DumpCount;
    LONG Flags;
    WER_HEAP_MAIN_HEADER MainHeader;
    PVOID Reserved;
} WER_PEB_HEADER_BLOCK, * PWER_PEB_HEADER_BLOCK;

// symbols
typedef struct _RTL_BITMAP* PRTL_BITMAP;

/**
 * Process Environment Block (PEB) structure.
 *
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winternl/ns-winternl-peb
 */
typedef struct _PEB
{
    //
    // The process was cloned with an inherited address space.
    //
    BOOLEAN InheritedAddressSpace;

    //
    // The process has image file execution options (IFEO).
    //
    BOOLEAN ReadImageFileExecOptions;

    //
    // The process has a debugger attached.
    //
    BOOLEAN BeingDebugged;
    union
    {
        BOOLEAN BitField;
        struct
        {
            BOOLEAN ImageUsesLargePages : 1;            // The process uses large image regions (4 MB).  
            BOOLEAN IsProtectedProcess : 1;             // The process is a protected process.
            BOOLEAN IsImageDynamicallyRelocated : 1;    // The process image base address was relocated.         
            BOOLEAN SkipPatchingUser32Forwarders : 1;   // The process skipped forwarders for User32.dll functions. 1 for 64-bit, 0 for 32-bit.            
            BOOLEAN IsPackagedProcess : 1;              // The process is a packaged store process (APPX/MSIX).
            BOOLEAN IsAppContainer : 1;                 // The process has an AppContainer token.      
            BOOLEAN IsProtectedProcessLight : 1;        // The process is a protected process (light).            
            BOOLEAN IsLongPathAwareProcess : 1;         // The process is long path aware.
        };
    };

    //
    // Handle to a mutex for synchronization.
    //
    HANDLE Mutant;

    //
    // Pointer to the base address of the process image.
    //
    PVOID ImageBaseAddress;

    //
    // Pointer to the process loader data.
    //
    PPEB_LDR_DATA Ldr;

    //
    // Pointer to the process parameters.
    //
    PRTL_USER_PROCESS_PARAMETERS ProcessParameters;

    //
    // Reserved.
    //
    PVOID SubSystemData;

    //
    // Pointer to the process default heap.
    //
    PVOID ProcessHeap;

    //
    // Pointer to a critical section used to synchronize access to the PEB.
    //
    PRTL_CRITICAL_SECTION FastPebLock;

    //
    // Pointer to a singly linked list used by ATL.
    //
    PSLIST_HEADER AtlThunkSListPtr;

    //
    // Pointer to the Image File Execution Options key.
    //
    PVOID IFEOKey;

    //
    // Cross process flags.
    //
    union
    {
        ULONG CrossProcessFlags;
        struct
        {
            ULONG ProcessInJob : 1;                 // The process is part of a job.
            ULONG ProcessInitializing : 1;          // The process is initializing. 
            ULONG ProcessUsingVEH : 1;              // The process is using VEH.
            ULONG ProcessUsingVCH : 1;              // The process is using VCH.
            ULONG ProcessUsingFTH : 1;              // The process is using FTH.
            ULONG ProcessPreviouslyThrottled : 1;   // The process was previously throttled.
            ULONG ProcessCurrentlyThrottled : 1;    // The process is currently throttled.
            ULONG ProcessImagesHotPatched : 1;      // The process images are hot patched. // RS5
            ULONG ReservedBits0 : 24;
        };
    };

    //
    // User32 KERNEL_CALLBACK_TABLE (ntuser.h)
    //
    union
    {
        PVOID KernelCallbackTable;
        PVOID UserSharedInfoPtr;
    };

    //
    // Reserved.
    //
    ULONG SystemReserved;

    //
    // Pointer to the Active Template Library (ATL) singly linked list (32-bit)
    //
    ULONG AtlThunkSListPtr32;

    //
    // Pointer to the API Set Schema.
    //
    PAPI_SET_NAMESPACE ApiSetMap;

    //
    // Counter for TLS expansion.
    //
    ULONG TlsExpansionCounter;

    //
    // Pointer to the TLS bitmap.
    //
    PRTL_BITMAP TlsBitmap;

    //
    // Bits for the TLS bitmap.
    //
    ULONG TlsBitmapBits[2]; // TLS_MINIMUM_AVAILABLE

    //
    // Reserved for CSRSS.
    //
    PVOID ReadOnlySharedMemoryBase;

    //
    // Pointer to the USER_SHARED_DATA for the current SILO.
    //
    struct _SILO_USER_SHARED_DATA* SharedData; // HotpatchInformation

    //
    // Reserved for CSRSS.
    //
    PVOID* ReadOnlyStaticServerData;

    //
    // Pointer to the ANSI code page data. (PCPTABLEINFO)
    //
    PVOID AnsiCodePageData;

    //
    // Pointer to the OEM code page data. (PCPTABLEINFO)
    //
    PVOID OemCodePageData;

    //
    // Pointer to the Unicode case table data. (PNLSTABLEINFO)
    //
    PVOID UnicodeCaseTableData;

    //
    // The total number of system processors.
    //
    ULONG NumberOfProcessors;

    //
    // Global flags for the system.
    //
    union
    {
        ULONG NtGlobalFlag;
        struct
        {
            ULONG StopOnException : 1;          // FLG_STOP_ON_EXCEPTION
            ULONG ShowLoaderSnaps : 1;          // FLG_SHOW_LDR_SNAPS
            ULONG DebugInitialCommand : 1;      // FLG_DEBUG_INITIAL_COMMAND
            ULONG StopOnHungGUI : 1;            // FLG_STOP_ON_HUNG_GUI
            ULONG HeapEnableTailCheck : 1;      // FLG_HEAP_ENABLE_TAIL_CHECK
            ULONG HeapEnableFreeCheck : 1;      // FLG_HEAP_ENABLE_FREE_CHECK
            ULONG HeapValidateParameters : 1;   // FLG_HEAP_VALIDATE_PARAMETERS
            ULONG HeapValidateAll : 1;          // FLG_HEAP_VALIDATE_ALL
            ULONG ApplicationVerifier : 1;      // FLG_APPLICATION_VERIFIER
            ULONG MonitorSilentProcessExit : 1; // FLG_MONITOR_SILENT_PROCESS_EXIT
            ULONG PoolEnableTagging : 1;        // FLG_POOL_ENABLE_TAGGING
            ULONG HeapEnableTagging : 1;        // FLG_HEAP_ENABLE_TAGGING
            ULONG UserStackTraceDb : 1;         // FLG_USER_STACK_TRACE_DB
            ULONG KernelStackTraceDb : 1;       // FLG_KERNEL_STACK_TRACE_DB
            ULONG MaintainObjectTypeList : 1;   // FLG_MAINTAIN_OBJECT_TYPELIST
            ULONG HeapEnableTagByDll : 1;       // FLG_HEAP_ENABLE_TAG_BY_DLL
            ULONG DisableStackExtension : 1;    // FLG_DISABLE_STACK_EXTENSION
            ULONG EnableCsrDebug : 1;           // FLG_ENABLE_CSRDEBUG
            ULONG EnableKDebugSymbolLoad : 1;   // FLG_ENABLE_KDEBUG_SYMBOL_LOAD
            ULONG DisablePageKernelStacks : 1;  // FLG_DISABLE_PAGE_KERNEL_STACKS
            ULONG EnableSystemCritBreaks : 1;   // FLG_ENABLE_SYSTEM_CRIT_BREAKS
            ULONG HeapDisableCoalescing : 1;    // FLG_HEAP_DISABLE_COALESCING
            ULONG EnableCloseExceptions : 1;    // FLG_ENABLE_CLOSE_EXCEPTIONS
            ULONG EnableExceptionLogging : 1;   // FLG_ENABLE_EXCEPTION_LOGGING
            ULONG EnableHandleTypeTagging : 1;  // FLG_ENABLE_HANDLE_TYPE_TAGGING
            ULONG HeapPageAllocs : 1;           // FLG_HEAP_PAGE_ALLOCS
            ULONG DebugInitialCommandEx : 1;    // FLG_DEBUG_INITIAL_COMMAND_EX
            ULONG DisableDbgPrint : 1;          // FLG_DISABLE_DBGPRINT
            ULONG CritSecEventCreation : 1;     // FLG_CRITSEC_EVENT_CREATION
            ULONG LdrTopDown : 1;               // FLG_LDR_TOP_DOWN
            ULONG EnableHandleExceptions : 1;   // FLG_ENABLE_HANDLE_EXCEPTIONS
            ULONG DisableProtDlls : 1;          // FLG_DISABLE_PROTDLLS
        } NtGlobalFlags;
    };


    //
    // Timeout for critical sections.
    //
    LARGE_INTEGER CriticalSectionTimeout;

    //
    // Reserved size for heap segments.
    //
    SIZE_T HeapSegmentReserve;

    //
    // Committed size for heap segments.
    //
    SIZE_T HeapSegmentCommit;

    //
    // Threshold for decommitting total free heap.
    //
    SIZE_T HeapDeCommitTotalFreeThreshold;

    //
    // Threshold for decommitting free heap blocks.
    //
    SIZE_T HeapDeCommitFreeBlockThreshold;

    //
    // Number of process heaps.
    //
    ULONG NumberOfHeaps;

    //
    // Maximum number of process heaps.
    //
    ULONG MaximumNumberOfHeaps;

    //
    // Pointer to an array of process heaps. ProcessHeaps is initialized
    // to point to the first free byte after the PEB and MaximumNumberOfHeaps
    // is computed from the page size used to hold the PEB, less the fixed
    // size of this data structure.
    //
    PVOID* ProcessHeaps; // PHEAP

    //
    // Pointer to the system GDI shared handle table.
    //
    PVOID GdiSharedHandleTable; // PGDI_SHARED_MEMORY

    //
    // Pointer to the process starter helper.
    //
    PVOID ProcessStarterHelper;

    //
    // The maximum number of GDI function calls during batch operations (GdiSetBatchLimit)
    //
    ULONG GdiDCAttributeList;

    //
    // Pointer to the loader lock critical section.
    //
    PRTL_CRITICAL_SECTION LoaderLock;

    //
    // Major version of the operating system.
    //
    ULONG OSMajorVersion;

    //
    // Minor version of the operating system.
    //
    ULONG OSMinorVersion;

    //
    // Build number of the operating system.
    //
    USHORT OSBuildNumber;

    //
    // CSD version of the operating system.
    //
    USHORT OSCSDVersion;

    //
    // Platform ID of the operating system.
    //
    ULONG OSPlatformId;

    //
    // Subsystem version of the current process image (PE Headers).
    //
    ULONG ImageSubsystem;

    //
    // Major version of the current process image subsystem (PE Headers).
    //
    ULONG ImageSubsystemMajorVersion;

    //
    // Minor version of the current process image subsystem (PE Headers).
    //
    ULONG ImageSubsystemMinorVersion;

    //
    // Affinity mask for the current process.
    //
    KAFFINITY ActiveProcessAffinityMask;

    //
    // Temporary buffer for GDI handles accumulated in the current batch.
    //
    GDI_HANDLE_BUFFER GdiHandleBuffer;

    //
    // Pointer to the post-process initialization routine available for use by the application.
    //
    PPS_POST_PROCESS_INIT_ROUTINE PostProcessInitRoutine;

    //
    // Pointer to the TLS expansion bitmap.
    //
    PRTL_BITMAP TlsExpansionBitmap;

    //
    // Bits for the TLS expansion bitmap. TLS_EXPANSION_SLOTS
    //
    ULONG TlsExpansionBitmapBits[32];

    //
    // Session ID of the current process.
    //
    ULONG SessionId;

    //
    // Application compatibility flags. KACF_*
    //
    ULARGE_INTEGER AppCompatFlags;

    //
    // Application compatibility flags. KACF_*
    //
    ULARGE_INTEGER AppCompatFlagsUser;

    //
    // Pointer to the Application SwitchBack Compatibility Engine.
    //
    PVOID pShimData;

    //
    // Pointer to the Application Compatibility Engine. // APPCOMPAT_EXE_DATA
    //
    PVOID AppCompatInfo;

    //
    // CSD version string of the operating system.
    //
    UNICODE_STRING CSDVersion;

    //
    // Pointer to the process activation context.
    //
    PACTIVATION_CONTEXT_DATA ActivationContextData;

    //
    // Pointer to the process assembly storage map.
    //
    PASSEMBLY_STORAGE_MAP ProcessAssemblyStorageMap;

    //
    // Pointer to the system default activation context.
    //
    PACTIVATION_CONTEXT_DATA SystemDefaultActivationContextData;

    //
    // Pointer to the system assembly storage map.
    //
    PASSEMBLY_STORAGE_MAP SystemAssemblyStorageMap;

    //
    // Minimum stack commit size.
    //
    SIZE_T MinimumStackCommit;

    //
    // since 19H1 (previously FlsCallback to FlsHighIndex)
    //
    PVOID SparePointers[2];

    //
    // Pointer to the patch loader data.
    //
    PVOID PatchLoaderData;

    //
    // Pointer to the CHPE V2 process information. CHPEV2_PROCESS_INFO
    //
    PVOID ChpeV2ProcessInfo;

    //
    // Packaged process feature state.
    // 
    union
    {
        ULONG AppModelFeatureState;
        struct
        {
            ULONG ForegroundBoostProcesses : 1;
            ULONG AppModelFeatureStateReserved : 31;
        };
    };

    //
    // SpareUlongs
    // 
    ULONG SpareUlongs[2];

    //
    // Active code page.
    //
    USHORT ActiveCodePage;

    //
    // OEM code page.
    //
    USHORT OemCodePage;

    //
    // Code page case mapping.
    //
    USHORT UseCaseMapping;

    //
    // Unused NLS field.
    //
    USHORT UnusedNlsField;

    //
    // Pointer to the application WER registration data.
    //
    PWER_PEB_HEADER_BLOCK WerRegistrationData;

    //
    // Pointer to the application WER assert pointer.
    //
    PVOID WerShipAssertPtr;

    //
    // Pointer to the EC bitmap on ARM64. (Windows 11 and above)
    //
    union
    {
        PVOID pContextData; // Pointer to the switchback compatibility engine (Windows 7 and below)
        PVOID EcCodeBitMap; // Pointer to the EC bitmap on ARM64 (Windows 11 and above) // since WIN11
    };

    //
    // Reserved.
    //
    PVOID pImageHeaderHash;

    //
    // ETW tracing flags.
    //
    union
    {
        ULONG TracingFlags;
        struct
        {
            ULONG HeapTracingEnabled : 1;       // ETW heap tracing enabled.
            ULONG CritSecTracingEnabled : 1;    // ETW lock tracing enabled.
            ULONG LibLoaderTracingEnabled : 1;  // ETW loader tracing enabled.
            ULONG SpareTracingBits : 29;
        };
    };

    //
    // Reserved for CSRSS.
    //
    ULONGLONG CsrServerReadOnlySharedMemoryBase;

    //
    // Pointer to the thread pool worker list lock.
    //
    PRTL_CRITICAL_SECTION TppWorkerpListLock;

    //
    // Pointer to the thread pool worker list.
    //
    LIST_ENTRY TppWorkerpList;

    //
    // Wait on address hash table. (RtlWaitOnAddress)
    //
    PVOID WaitOnAddressHashTable[128];

    //
    // Pointer to the telemetry coverage header. // since RS3
    //
    PTELEMETRY_COVERAGE_HEADER TelemetryCoverageHeader;

    //
    // Cloud file flags. (ProjFs and Cloud Files) // since RS4
    //
    ULONG CloudFileFlags;

    //
    // Cloud file diagnostic flags.
    //
    ULONG CloudFileDiagFlags;

    //
    // Placeholder compatibility mode. (ProjFs and Cloud Files)
    //
    CHAR PlaceholderCompatibilityMode;

    //
    // Reserved for placeholder compatibility mode.
    //
    CHAR PlaceholderCompatibilityModeReserved[7];

    //
    // Pointer to leap second data. // since RS5
    //
    struct _LEAP_SECOND_DATA* LeapSecondData;

    //
    // Leap second flags.
    //
    union
    {
        ULONG LeapSecondFlags;
        struct
        {
            ULONG SixtySecondEnabled : 1; // Leap seconds enabled.
            ULONG Reserved : 31;
        };
    };

    //
    // Global flags for the process.
    //
    ULONG NtGlobalFlag2;

    //
    // Extended feature disable mask (AVX). // since WIN11
    //
    ULONGLONG ExtendedFeatureDisableMask;

} PEB, * PPEB;

#ifdef _WIN64
STATIC_ASSERT(FIELD_OFFSET(PEB, SessionId) == 0x2C0, "FIELD_OFFSET(PEB, SessionId) is incorrect");
//STATIC_ASSERT(sizeof(PEB) == 0x7B0, "Size of PEB is incorrect"); // REDSTONE3
//STATIC_ASSERT(sizeof(PEB) == 0x7B8, "Size of PEB is incorrect"); // REDSTONE4
//STATIC_ASSERT(sizeof(PEB) == 0x7C8, "Size of PEB is incorrect"); // REDSTONE5 // 19H1
STATIC_ASSERT(sizeof(PEB) == 0x7d0, "Size of PEB is incorrect"); // WIN11
#else
STATIC_ASSERT(FIELD_OFFSET(PEB, SessionId) == 0x1D4, "FIELD_OFFSET(PEB, SessionId) is incorrect");
//STATIC_ASSERT(sizeof(PEB) == 0x468, "Size of PEB is incorrect"); // REDSTONE3
//STATIC_ASSERT(sizeof(PEB) == 0x470, "Size of PEB is incorrect"); // REDSTONE4
//STATIC_ASSERT(sizeof(PEB) == 0x480, "Size of PEB is incorrect"); // REDSTONE5 // 19H1
STATIC_ASSERT(sizeof(PEB) == 0x488, "Size of PEB is incorrect"); // WIN11
#endif

typedef struct _PEB32
{
    BOOLEAN InheritedAddressSpace;
    BOOLEAN ReadImageFileExecOptions;
    BOOLEAN BeingDebugged;
    union
    {
        BOOLEAN BitField;
        struct
        {
            BOOLEAN ImageUsesLargePages : 1;
            BOOLEAN IsProtectedProcess : 1;
            BOOLEAN IsImageDynamicallyRelocated : 1;
            BOOLEAN SkipPatchingUser32Forwarders : 1;
            BOOLEAN IsPackagedProcess : 1;
            BOOLEAN IsAppContainer : 1;
            BOOLEAN IsProtectedProcessLight : 1;
            BOOLEAN IsLongPathAwareProcess : 1;
        };
    };

    HANDLE32 Mutant;

    PVOID32 ImageBaseAddress;
    PPEB_LDR_DATA32 Ldr;
    struct _RTL_USER_PROCESS_PARAMETERS32* POINTER_32 ProcessParameters;
    PVOID32 SubSystemData;
    PVOID32 ProcessHeap;
    struct _RTL_CRITICAL_SECTION32* POINTER_32 FastPebLock;
    union _SLIST_HEADER* POINTER_32 AtlThunkSListPtr;
    PVOID32 IFEOKey;

    union
    {
        ULONG CrossProcessFlags;
        struct
        {
            ULONG ProcessInJob : 1;
            ULONG ProcessInitializing : 1;
            ULONG ProcessUsingVEH : 1;
            ULONG ProcessUsingVCH : 1;
            ULONG ProcessUsingFTH : 1;
            ULONG ProcessPreviouslyThrottled : 1;
            ULONG ProcessCurrentlyThrottled : 1;
            ULONG ProcessImagesHotPatched : 1; // REDSTONE5
            ULONG ReservedBits0 : 24;
        };
    };
    union
    {
        PVOID32 KernelCallbackTable;
        PVOID32 UserSharedInfoPtr;
    };
    ULONG SystemReserved;
    ULONG AtlThunkSListPtr32;
    struct _API_SET_NAMESPACE* POINTER_32 ApiSetMap;
    ULONG TlsExpansionCounter;
    struct _RTL_BITMAP* POINTER_32 TlsBitmap;
    ULONG TlsBitmapBits[2];

    PVOID32 ReadOnlySharedMemoryBase;
    struct _SILO_USER_SHARED_DATA* POINTER_32 SharedData; // HotpatchInformation
    PVOID32* POINTER_32 ReadOnlyStaticServerData;

    PVOID32 AnsiCodePageData; // PCPTABLEINFO
    PVOID32 OemCodePageData; // PCPTABLEINFO
    PVOID32 UnicodeCaseTableData; // PNLSTABLEINFO

    ULONG NumberOfProcessors;
    ULONG NtGlobalFlag;

    ULARGE_INTEGER CriticalSectionTimeout;
    SIZE_T32 HeapSegmentReserve;
    SIZE_T32 HeapSegmentCommit;
    SIZE_T32 HeapDeCommitTotalFreeThreshold;
    SIZE_T32 HeapDeCommitFreeBlockThreshold;

    ULONG NumberOfHeaps;
    ULONG MaximumNumberOfHeaps;
    PVOID32* POINTER_32 ProcessHeaps; // PHEAP

    PVOID32 GdiSharedHandleTable; // PGDI_SHARED_MEMORY
    PVOID32 ProcessStarterHelper;
    ULONG GdiDCAttributeList;

    struct _RTL_CRITICAL_SECTION32* POINTER_32 LoaderLock;

    ULONG OSMajorVersion;
    ULONG OSMinorVersion;
    USHORT OSBuildNumber;
    USHORT OSCSDVersion;
    ULONG OSPlatformId;
    ULONG ImageSubsystem;
    ULONG ImageSubsystemMajorVersion;
    ULONG ImageSubsystemMinorVersion;
    KAFFINITY32 ActiveProcessAffinityMask;
    GDI_HANDLE_BUFFER32 GdiHandleBuffer;
    PVOID32 PostProcessInitRoutine;

    PVOID32 TlsExpansionBitmap;
    ULONG TlsExpansionBitmapBits[32];

    ULONG SessionId;

    ULARGE_INTEGER AppCompatFlags;
    ULARGE_INTEGER AppCompatFlagsUser;
    PVOID32 pShimData;
    PVOID32 AppCompatInfo; // APPCOMPAT_EXE_DATA

    UNICODE_STRING32 CSDVersion;

    struct _ACTIVATION_CONTEXT_DATA* POINTER_32 ActivationContextData;
    struct _ASSEMBLY_STORAGE_MAP32* POINTER_32 ProcessAssemblyStorageMap;
    struct _ACTIVATION_CONTEXT_DATA* POINTER_32 SystemDefaultActivationContextData;
    struct _ASSEMBLY_STORAGE_MAP32* POINTER_32 SystemAssemblyStorageMap;

    SIZE_T32 MinimumStackCommit;

    PVOID32 SparePointers[2]; // 19H1 (previously FlsCallback to FlsHighIndex)
    PVOID32 PatchLoaderData;
    PVOID32 ChpeV2ProcessInfo; // _CHPEV2_PROCESS_INFO

    ULONG AppModelFeatureState;
    ULONG SpareUlongs[2];

    USHORT ActiveCodePage;
    USHORT OemCodePage;
    USHORT UseCaseMapping;
    USHORT UnusedNlsField;

    PVOID32 WerRegistrationData;
    PVOID32 WerShipAssertPtr;

    union
    {
        PVOID32 pContextData; // WIN7
        PVOID32 pUnused; // WIN10
        PVOID32 EcCodeBitMap; // WIN11
    };

    PVOID32 pImageHeaderHash;
    union
    {
        ULONG TracingFlags;
        struct
        {
            ULONG HeapTracingEnabled : 1;
            ULONG CritSecTracingEnabled : 1;
            ULONG LibLoaderTracingEnabled : 1;
            ULONG SpareTracingBits : 29;
        };
    };
    ULONGLONG CsrServerReadOnlySharedMemoryBase;
    struct _RTL_CRITICAL_SECTION32* POINTER_32 TppWorkerpListLock;
    LIST_ENTRY32 TppWorkerpList;
    PVOID32 WaitOnAddressHashTable[128];
    struct _PTELEMETRY_COVERAGE_HEADER* POINTER_32 TelemetryCoverageHeader; // REDSTONE3
    ULONG CloudFileFlags;
    ULONG CloudFileDiagFlags; // REDSTONE4
    CHAR PlaceholderCompatibilityMode;
    CHAR PlaceholderCompatibilityModeReserved[7];
    struct _LEAP_SECOND_DATA* POINTER_32 LeapSecondData; // REDSTONE5
    union
    {
        ULONG LeapSecondFlags;
        struct
        {
            ULONG SixtySecondEnabled : 1;
            ULONG Reserved : 31;
        };
    };
    ULONG NtGlobalFlag2;
    ULONGLONG ExtendedFeatureDisableMask; // since WIN11

} PEB32, * POINTER_32 PPEB32;

STATIC_ASSERT(sizeof(PEB32) == 0x488, "sizeof(PEB32) is incorrect"); // WIN11

#define GDI_BATCH_BUFFER_SIZE 310

/**
 * The GDI_TEB_BATCH structure is used to store information about GDI batch operations.
 */
typedef struct _GDI_TEB_BATCH
{
    ULONG Offset;
    ULONG_PTR HDC;
    ULONG Buffer[GDI_BATCH_BUFFER_SIZE];
} GDI_TEB_BATCH, * PGDI_TEB_BATCH;

typedef struct _GDI_TEB_BATCH32
{
    ULONG Offset;
    ULONG_PTR32 HDC;
    ULONG Buffer[GDI_BATCH_BUFFER_SIZE];
} GDI_TEB_BATCH32, * POINTER_32 PGDI_TEB_BATCH32;

STATIC_ASSERT(sizeof(GDI_TEB_BATCH32) == 1248, "sizeof(GDI_TEB_BATCH32) is incorrect");

/**
 * The TEB_ACTIVE_FRAME_CONTEXT structure is used to store information about an active frame context.
 */
typedef struct _TEB_ACTIVE_FRAME_CONTEXT
{
    ULONG Flags;
    PCSTR FrameName;
} TEB_ACTIVE_FRAME_CONTEXT, * PTEB_ACTIVE_FRAME_CONTEXT;

#define TEB_ACTIVE_FRAME_CONTEXT_FLAG_EXTENDED (0x00000001)

typedef struct _TEB_ACTIVE_FRAME_CONTEXT32
{
    ULONG Flags;
    const char * POINTER_32 FrameName;
} TEB_ACTIVE_FRAME_CONTEXT32, * POINTER_32 PTEB_ACTIVE_FRAME_CONTEXT32;

/**
 * The TEB_ACTIVE_FRAME_CONTEXT_EX structure extends TEB_ACTIVE_FRAME_CONTEXT with additional information.
 */
typedef struct _TEB_ACTIVE_FRAME_CONTEXT_EX
{
    TEB_ACTIVE_FRAME_CONTEXT BasicContext;
    PCSTR SourceLocation;
} TEB_ACTIVE_FRAME_CONTEXT_EX, * PTEB_ACTIVE_FRAME_CONTEXT_EX;

typedef struct _TEB_ACTIVE_FRAME_CONTEXT_EX32
{
    TEB_ACTIVE_FRAME_CONTEXT32 BasicContext;
    const char* POINTER_32 SourceLocation;
} TEB_ACTIVE_FRAME_CONTEXT_EX32, * PTEB_ACTIVE_FRAME_CONTEXT_EX32;

/**
 * The TEB_ACTIVE_FRAME structure is used to store information about an active frame.
 */
typedef struct _TEB_ACTIVE_FRAME
{
    ULONG Flags;
    struct _TEB_ACTIVE_FRAME* Previous;
    PTEB_ACTIVE_FRAME_CONTEXT Context;
} TEB_ACTIVE_FRAME, * PTEB_ACTIVE_FRAME;

typedef struct _TEB_ACTIVE_FRAME32
{
    ULONG Flags;
    struct _TEB_ACTIVE_FRAME* POINTER_32 Previous;
    PTEB_ACTIVE_FRAME_CONTEXT32 Context;
} TEB_ACTIVE_FRAME32, * POINTER_32 PTEB_ACTIVE_FRAME32;

/**
 * The TEB_ACTIVE_FRAME_EX structure extends TEB_ACTIVE_FRAME with additional information.
 */
typedef struct _TEB_ACTIVE_FRAME_EX
{
    TEB_ACTIVE_FRAME BasicFrame;
    PVOID ExtensionIdentifier;
} TEB_ACTIVE_FRAME_EX, * PTEB_ACTIVE_FRAME_EX;

typedef struct _TEB_ACTIVE_FRAME_EX32
{
    TEB_ACTIVE_FRAME32 BasicFrame;
    PVOID32 ExtensionIdentifier;
} TEB_ACTIVE_FRAME_EX32, * PTEB_ACTIVE_FRAME_EX32;

typedef struct _FLS_DATA
{
    LIST_ENTRY  Entry;
    PVOID       Slots[FLS_MAXIMUM_AVAILABLE];
} FLS_DATA, * PFLS_DATA;

typedef struct _FLS_DATA32
{
    LIST_ENTRY32  Entry;
    PVOID32       Slots[FLS_MAXIMUM_AVAILABLE];
} FLS_DATA32, * POINTER_32 PFLS_DATA32;

#define STATIC_UNICODE_BUFFER_LENGTH 261
#define WIN32_CLIENT_INFO_LENGTH 62

// private
typedef enum tagOLETLSFLAGS
{
    OLETLS_LOCALTID                  = 0x01,    // This TID is in the current process.
    OLETLS_UUIDINITIALIZED           = 0x02,    // This Logical thread is init'd.
    OLETLS_INTHREADDETACH            = 0x04,    // This is in thread detach.
    OLETLS_CHANNELTHREADINITIALZED   = 0x08,    // This channel has been init'd
    OLETLS_WOWTHREAD                 = 0x10,    // This thread is a 16-bit WOW thread.
    OLETLS_THREADUNINITIALIZING      = 0x20,    // This thread is in CoUninitialize.
    OLETLS_DISABLE_OLE1DDE           = 0x40,    // This thread can't use a DDE window.
    OLETLS_APARTMENTTHREADED         = 0x80,    // This is an STA apartment thread
    OLETLS_MULTITHREADED             = 0x100,   // This is an MTA apartment thread
    OLETLS_IMPERSONATING             = 0x200,   // This thread is impersonating
    OLETLS_DISABLE_EVENTLOGGER       = 0x400,   // Prevent recursion in event logger
    OLETLS_INNEUTRALAPT              = 0x800,   // This thread is in the NTA
    OLETLS_DISPATCHTHREAD            = 0x1000,  // This is a dispatch thread
    OLETLS_HOSTTHREAD                = 0x2000,  // This is a host thread
    OLETLS_ALLOWCOINIT               = 0x4000,  // This thread allows inits
    OLETLS_PENDINGUNINIT             = 0x8000,  // This thread has pending uninit
    OLETLS_FIRSTMTAINIT              = 0x10000, // First thread to attempt an MTA init
    OLETLS_FIRSTNTAINIT              = 0x20000, // First thread to attempt an NTA init
    OLETLS_APTINITIALIZING           = 0x40000, // Apartment Object is initializing
    OLETLS_UIMSGSINMODALLOOP         = 0x80000,
    OLETLS_MARSHALING_ERROR_OBJECT   = 0x100000, // since WIN8
    OLETLS_WINRT_INITIALIZE          = 0x200000, // This thread called RoInitialize
    OLETLS_APPLICATION_STA           = 0x400000,
    OLETLS_IN_SHUTDOWN_CALLBACKS     = 0x800000,
    OLETLS_POINTER_INPUT_BLOCKED     = 0x1000000,
    OLETLS_IN_ACTIVATION_FILTER      = 0x2000000, // since WINBLUE
    OLETLS_ASTATOASTAEXEMPT_QUIRK    = 0x4000000,
    OLETLS_ASTATOASTAEXEMPT_PROXY    = 0x8000000,
    OLETLS_ASTATOASTAEXEMPT_INDOUBT  = 0x10000000,
    OLETLS_DETECTED_USER_INITIALIZED = 0x20000000,  // since RS3
    OLETLS_BRIDGE_STA                = 0x40000000,  // since RS5
    OLETLS_NAINITIALIZING            = 0x80000000UL // since 19H1
} OLETLSFLAGS, *POLETLSFLAGS;

// private
typedef struct tagSOleTlsData
{
    PVOID       ThreadBase;
    PVOID       SmAllocator;
    ULONG       ApartmentID;
    OLETLSFLAGS Flags;
    LONG        TlsMapIndex;
    PVOID*      TlsSlot;
    ULONG       ComInits;
    ULONG       OleInits;
    ULONG       Calls;
    PVOID       ServerCall;      // previously CallInfo (before TH1)
    PVOID       CallObjectCache; // previously FreeAsyncCall (before TH1)
    PVOID       ContextStack;    // previously FreeClientCall (before TH1)
    PVOID       ObjServer;
    ULONG       TIDCaller;
    // ... (other fields are version-dependant)
} SOleTlsData, *PSOleTlsData;

typedef struct tagSOleTlsData32
{
    PVOID32     ThreadBase;
    PVOID32     SmAllocator;
    ULONG       ApartmentID;
    OLETLSFLAGS Flags;
    LONG        TlsMapIndex;
    PVOID32     TlsSlot; // PVOID*
    ULONG       ComInits;
    ULONG       OleInits;
    ULONG       Calls;
    PVOID32     ServerCall;      // previously CallInfo (before TH1)
    PVOID32     CallObjectCache; // previously FreeAsyncCall (before TH1)
    PVOID32     ContextStack;    // previously FreeClientCall (before TH1)
    PVOID32     ObjServer;
    ULONG       TIDCaller;
    // ... (other fields are version-dependant)
} SOleTlsData32, *PSOleTlsData32;

/**
 * Thread Environment Block (TEB) structure.
 *
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winternl/ns-winternl-teb
 */
typedef struct _TEB
{
    //
    // Thread Information Block (TIB) contains the thread's stack, base and limit addresses, the current stack pointer, and the exception list.
    //

    NT_TIB NtTib;

    //
    // Reserved
    //

    PVOID EnvironmentPointer;

    //
    // Client ID for this thread.
    //

    CLIENT_ID ClientId;

    //
    // A handle to an active Remote Procedure Call (RPC) if the thread is currently involved in an RPC operation.
    //

    PVOID ActiveRpcHandle;

    //
    // A pointer to the __declspec(thread) local storage array.
    //

    PVOID ThreadLocalStoragePointer;

    //
    // A pointer to the Process Environment Block (PEB), which contains information about the process.
    //

    PPEB ProcessEnvironmentBlock;

    //
    // The previous Win32 error value for this thread.
    //
    ULONG LastErrorValue;

    //
    // The number of critical sections currently owned by this thread.
    //
    ULONG CountOfOwnedCriticalSections;

    //
    // Reserved.
    //
    PVOID CsrClientThread;

    //
    // Reserved.
    //
    PVOID Win32ThreadInfo;

    //
    // Reserved.
    //
    ULONG User32Reserved[26];

    //
    // Reserved.
    //
    ULONG UserReserved[5];

    //
    // Reserved.
    //
    PVOID WOW32Reserved;

    //
    // The LCID of the current thread. (Kernel32!GetThreadLocale)
    //
    LCID CurrentLocale;

    //
    // Reserved.
    //
    ULONG FpSoftwareStatusRegister;

    //
    // Reserved.
    //
    PVOID ReservedForDebuggerInstrumentation[16];

#ifdef _WIN64
    //
    // Reserved.
    //
    PVOID SystemReserved1[25];

    //
    // Per-thread fiber local storage. (Teb->HasFiberData)
    //
    PVOID HeapFlsData;

    //
    // Reserved.
    //
    ULONG_PTR RngState[4];
#else
    //
    // Reserved.
    //
    PVOID SystemReserved1[26];
#endif

    //
    // Placeholder compatibility mode. (ProjFs and Cloud Files)
    //
    CHAR PlaceholderCompatibilityMode;

    //
    // Indicates whether placeholder hydration is always explicit.
    //
    BOOLEAN PlaceholderHydrationAlwaysExplicit;

    //
    // Reserved.
    //
    CHAR PlaceholderReserved[10];

    //
    // The process ID (PID) that the current COM server thread is acting on behalf of.
    //
    ULONG ProxiedProcessId;

    //
    // Pointer to the activation context stack for the current thread.
    //
    ACTIVATION_CONTEXT_STACK ActivationStack;

    //
    // Opaque operation on behalf of another user or process.
    //
    UCHAR WorkingOnBehalfTicket[8];

    //
    // The last exception status for the current thread.
    //
    NTSTATUS ExceptionCode;

    //
    // Pointer to the activation context stack for the current thread.
    //
    PACTIVATION_CONTEXT_STACK ActivationContextStackPointer;

    //
    // The stack pointer (SP) of the current system call or exception during instrumentation.
    //
    ULONG_PTR InstrumentationCallbackSp;

    //
    // The program counter (PC) of the previous system call or exception during instrumentation.
    //
    ULONG_PTR InstrumentationCallbackPreviousPc;

    //
    // The stack pointer (SP) of the previous system call or exception during instrumentation.
    //
    ULONG_PTR InstrumentationCallbackPreviousSp;

#ifdef _WIN64
    //
    // The miniversion ID of the current transacted file operation.
    //
    ULONG TxFsContext;
#endif

    //
    // Indicates the state of the system call or exception instrumentation callback.
    //
    BOOLEAN InstrumentationCallbackDisabled;

#ifdef _WIN64
    //
    // Indicates the state of alignment exceptions for unaligned load/store operations.
    //
    BOOLEAN UnalignedLoadStoreExceptions;
#endif

#ifndef _WIN64
    //
    // SpareBytes.
    //
    UCHAR SpareBytes[23];

    //
    // The miniversion ID of the current transacted file operation.
    //
    ULONG TxFsContext;
#endif

    //
    // Reserved for GDI.
    //
    GDI_TEB_BATCH GdiTebBatch;
    CLIENT_ID RealClientId;
    HANDLE GdiCachedProcessHandle;
    ULONG GdiClientPID;
    ULONG GdiClientTID;
    PVOID GdiThreadLocalInfo;

    //
    // Reserved for User32.
    //
    ULONG_PTR Win32ClientInfo[WIN32_CLIENT_INFO_LENGTH];

    //
    // Reserved for opengl32.dll
    //
    PVOID glDispatchTable[233];
    ULONG_PTR glReserved1[29];
    PVOID glReserved2;
    PVOID glSectionInfo;
    PVOID glSection;
    PVOID glTable;
    PVOID glCurrentRC;
    PVOID glContext;

    //
    // The previous status value for this thread.
    //
    NTSTATUS LastStatusValue;

    //
    // A static string for use by the application.
    //
    UNICODE_STRING StaticUnicodeString;

    //
    // A static buffer for use by the application.
    //
    WCHAR StaticUnicodeBuffer[STATIC_UNICODE_BUFFER_LENGTH];

    //
    // The maximum stack size and indicates the base of the stack.
    //
    PVOID DeallocationStack;

    //
    // Data for Thread Local Storage. (TlsGetValue)
    //
    PVOID TlsSlots[TLS_MINIMUM_AVAILABLE];

    //
    // Reserved.
    //
    LIST_ENTRY TlsLinks;

    //
    // Reserved for NTVDM.
    //
    PVOID Vdm;

    //
    // Reserved.
    //
    PVOID ReservedForNtRpc;

    //
    // Reserved.
    //
    PVOID DbgSsReserved[2];

    //
    // The error mode for the current thread. (GetThreadErrorMode)
    //
    ULONG HardErrorMode;

    //
    // Reserved.
    //
#ifdef _WIN64
    PVOID Instrumentation[11];
#else
    PVOID Instrumentation[9];
#endif

    //
    // Reserved.
    //
    GUID ActivityId;

    //
    // The service creating the thread (svchost).
    //
    PVOID SubProcessTag;

    //
    // Reserved.
    //
    PVOID PerflibData;

    //
    // Reserved.
    //
    PVOID EtwTraceData;

    //
    // The address of a socket handle during a blocking socket operation. (WSAStartup)
    //
    HANDLE WinSockData;

    //
    // The number of function calls accumulated in the current GDI batch. (GdiSetBatchLimit)
    //
    ULONG GdiBatchCount;

    //
    // The preferred processor for the current thread. (SetThreadIdealProcessor/SetThreadIdealProcessorEx)
    // 
    union
    {
        PROCESSOR_NUMBER CurrentIdealProcessor;
        ULONG IdealProcessorValue;
        struct
        {
            UCHAR ReservedPad0;
            UCHAR ReservedPad1;
            UCHAR ReservedPad2;
            UCHAR IdealProcessor;
        };
    };

    //
    // The minimum size of the stack available during any stack overflow exceptions. (SetThreadStackGuarantee)
    // 
    ULONG GuaranteedStackBytes;

    //
    // Reserved.
    //
    PVOID ReservedForPerf;

    //
    // Per-thread COM/OLE state
    //
    PSOleTlsData ReservedForOle;

    //
    // Indicates whether the thread is waiting on the loader lock.
    //
    ULONG WaitingOnLoaderLock;

    //
    // The saved priority state for the thread.
    //
    PVOID SavedPriorityState;

    //
    // Reserved.
    //
    ULONG_PTR ReservedForCodeCoverage;

    //
    // Reserved.
    //
    PVOID ThreadPoolData;

    //
    // Pointer to the TLS (Thread Local Storage) expansion slots for the thread.
    //
    PVOID* TlsExpansionSlots;

#ifdef _WIN64
    PVOID ChpeV2CpuAreaInfo; // CHPEV2_CPUAREA_INFO // previously DeallocationBStore
    PVOID Unused; // previously BStoreLimit
#endif

    //
    // The generation of the MUI (Multilingual User Interface) data.
    //
    ULONG MuiGeneration;

    //
    // Indicates whether the thread is impersonating another security context.
    //
    ULONG IsImpersonating;

    //
    // Pointer to the NLS (National Language Support) cache.
    //
    PVOID NlsCache;

    //
    // Pointer to the AppCompat/Shim Engine data.
    //
    PVOID pShimData;

    //
    // Reserved.
    //
    ULONG HeapData;

    //
    // Handle to the current transaction associated with the thread.
    //
    HANDLE CurrentTransactionHandle;

    //
    // Pointer to the active frame for the thread.
    //
    PTEB_ACTIVE_FRAME ActiveFrame;

    //
    // Reserved for FLS (RtlProcessFlsData).
    //
    PVOID FlsData;  // PFLS_DATA

    PVOID PreferredLanguages;
    PVOID UserPrefLanguages;
    PVOID MergedPrefLanguages;
    ULONG MuiImpersonation;

    union
    {
        USHORT CrossTebFlags;
        USHORT SpareCrossTebBits : 16;
    };
    union
    {
        USHORT SameTebFlags;
        struct
        {
            USHORT SafeThunkCall : 1;
            USHORT InDebugPrint : 1;
            USHORT HasFiberData : 1;
            USHORT SkipThreadAttach : 1;
            USHORT WerInShipAssertCode : 1;
            USHORT RanProcessInit : 1;
            USHORT ClonedThread : 1;
            USHORT SuppressDebugMsg : 1;
            USHORT DisableUserStackWalk : 1;
            USHORT RtlExceptionAttached : 1;
            USHORT InitialThread : 1;
            USHORT SessionAware : 1;
            USHORT LoadOwner : 1;
            USHORT LoaderWorker : 1;
            USHORT SkipLoaderInit : 1;
            USHORT SkipFileAPIBrokering : 1;
        };
    };

    PVOID TxnScopeEnterCallback;
    PVOID TxnScopeExitCallback;
    PVOID TxnScopeContext;
    ULONG LockCount;
    LONG WowTebOffset;
    PVOID ResourceRetValue;
    PVOID ReservedForWdf;
    ULONGLONG ReservedForCrt;
    GUID EffectiveContainerId;

    //
    // Reserved for Kernel32!Sleep (SpinWait).
    //
    ULONGLONG LastSleepCounter; // Win11

    //
    // Reserved for Kernel32!Sleep (SpinWait).
    //
    ULONG SpinCallCount;

    //
    // Extended feature disable mask (AVX).
    //
    ULONGLONG ExtendedFeatureDisableMask;

    //
    // Reserved.
    //
    PVOID SchedulerSharedDataSlot; // 24H2

    //
    // Reserved.
    //
    PVOID HeapWalkContext;

    //
    // The primary processor group affinity of the thread.
    //
    GROUP_AFFINITY PrimaryGroupAffinity;

    //
    // Read-copy-update (RCU) synchronization context.
    //
    ULONG Rcu[2];
} TEB, * PTEB;

#ifdef _WIN64
//STATIC_ASSERT(sizeof(TEB) == 0x1850, "Size of TEB is incorrect"); // WIN11
STATIC_ASSERT(sizeof(TEB) == 0x1878, "Size of TEB is incorrect"); // 24H2
#else
//STATIC_ASSERT(sizeof(TEB) == 0x1018, "Size of TEB is incorrect"); // WIN11
STATIC_ASSERT(sizeof(TEB) == 0x1038, "Size of TEB is incorrect"); // 24H2
#endif

typedef struct _TEB32
{
    NT_TIB32 NtTib;

    PVOID32 EnvironmentPointer;
    CLIENT_ID32 ClientId;
    PVOID32 ActiveRpcHandle;
    PVOID32 ThreadLocalStoragePointer;
    PPEB32 ProcessEnvironmentBlock;

    ULONG LastErrorValue;
    ULONG CountOfOwnedCriticalSections;
    PVOID32 CsrClientThread;
    PVOID32 Win32ThreadInfo;
    ULONG User32Reserved[26];
    ULONG UserReserved[5];
    PVOID32 WOW32Reserved;
    LCID CurrentLocale;
    ULONG FpSoftwareStatusRegister;
    PVOID32 ReservedForDebuggerInstrumentation[16];
    PVOID32 SystemReserved1[26];

    CHAR PlaceholderCompatibilityMode;
    BOOLEAN PlaceholderHydrationAlwaysExplicit;
    CHAR PlaceholderReserved[10];

    ULONG ProxiedProcessId;
    ACTIVATION_CONTEXT_STACK32 ActivationStack;

    UCHAR WorkingOnBehalfTicket[8];
    NTSTATUS ExceptionCode;

    PACTIVATION_CONTEXT_STACK32 ActivationContextStackPointer;
    ULONG_PTR32 InstrumentationCallbackSp;
    ULONG_PTR32 InstrumentationCallbackPreviousPc;
    ULONG_PTR32 InstrumentationCallbackPreviousSp;

    BOOLEAN InstrumentationCallbackDisabled;
    UCHAR SpareBytes[23];
    ULONG TxFsContext;
    GDI_TEB_BATCH32 GdiTebBatch;
    CLIENT_ID32 RealClientId;
    HANDLE32 GdiCachedProcessHandle;
    ULONG GdiClientPID;
    ULONG GdiClientTID;
    PVOID32 GdiThreadLocalInfo;
    ULONG_PTR32 Win32ClientInfo[WIN32_CLIENT_INFO_LENGTH];
    PVOID32 glDispatchTable[233];
    ULONG_PTR32 glReserved1[29];
    PVOID32 glReserved2;
    PVOID32 glSectionInfo;
    PVOID32 glSection;
    PVOID32 glTable;
    PVOID32 glCurrentRC;
    PVOID32 glContext;

    NTSTATUS LastStatusValue;
    UNICODE_STRING32 StaticUnicodeString;
    WCHAR StaticUnicodeBuffer[STATIC_UNICODE_BUFFER_LENGTH];

    PVOID32 DeallocationStack;
    PVOID32 TlsSlots[TLS_MINIMUM_AVAILABLE];
    LIST_ENTRY32 TlsLinks;

    PVOID32 Vdm;
    PVOID32 ReservedForNtRpc;
    PVOID32 DbgSsReserved[2];

    ULONG HardErrorMode;
    PVOID32 Instrumentation[9];
    GUID ActivityId;

    PVOID32 SubProcessTag;
    PVOID32 PerflibData;
    PVOID32 EtwTraceData;
    PVOID32 WinSockData;
    ULONG GdiBatchCount;

    union
    {
        PROCESSOR_NUMBER CurrentIdealProcessor;
        ULONG IdealProcessorValue;
        struct
        {
            UCHAR ReservedPad0;
            UCHAR ReservedPad1;
            UCHAR ReservedPad2;
            UCHAR IdealProcessor;
        };
    };

    ULONG GuaranteedStackBytes;
    PVOID32 ReservedForPerf;
    PVOID32 ReservedForOle; // tagSOleTlsData32
    ULONG WaitingOnLoaderLock;
    PVOID32 SavedPriorityState;
    ULONG_PTR32 ReservedForCodeCoverage;
    PVOID32 ThreadPoolData;
    PVOID32* POINTER_32 TlsExpansionSlots;
    ULONG MuiGeneration;
    ULONG IsImpersonating;
    PVOID32 NlsCache;
    PVOID32 pShimData;
    ULONG HeapData;
    HANDLE32 CurrentTransactionHandle;
    PTEB_ACTIVE_FRAME32 ActiveFrame;
    PVOID32 FlsData;

    PVOID32 PreferredLanguages;
    PVOID32 UserPrefLanguages;
    PVOID32 MergedPrefLanguages;
    ULONG MuiImpersonation;

    union
    {
        USHORT CrossTebFlags;
        USHORT SpareCrossTebBits : 16;
    };
    union
    {
        USHORT SameTebFlags;
        struct
        {
            USHORT SafeThunkCall : 1;
            USHORT InDebugPrint : 1;
            USHORT HasFiberData : 1;
            USHORT SkipThreadAttach : 1;
            USHORT WerInShipAssertCode : 1;
            USHORT RanProcessInit : 1;
            USHORT ClonedThread : 1;
            USHORT SuppressDebugMsg : 1;
            USHORT DisableUserStackWalk : 1;
            USHORT RtlExceptionAttached : 1;
            USHORT InitialThread : 1;
            USHORT SessionAware : 1;
            USHORT LoadOwner : 1;
            USHORT LoaderWorker : 1;
            USHORT SkipLoaderInit : 1;
            USHORT SkipFileAPIBrokering : 1;
        };
    };

    PVOID32 TxnScopeEnterCallback;
    PVOID32 TxnScopeExitCallback;
    PVOID32 TxnScopeContext;
    ULONG LockCount;
    LONG WowTebOffset;
    PVOID32 ResourceRetValue;
    PVOID32 ReservedForWdf;
    ULONGLONG ReservedForCrt;
    GUID EffectiveContainerId;
    ULONGLONG LastSleepCounter; // Win11
    ULONG SpinCallCount;
    ULONGLONG ExtendedFeatureDisableMask;
} TEB32, * POINTER_32 PTEB32;

STATIC_ASSERT(sizeof(TEB32) == 4120, "sizeof(TEB32) is incorrect");

typedef struct _WOW64_PROCESS
{
    PVOID Wow64;
} WOW64_PROCESS, * PWOW64_PROCESS;

#if !defined(_KERNEL_MODE)
// The Wow64Info structure follows the PEB32/TEB32 structures and is shared between 32-bit and 64-bit modules inside a Wow64 process.
// from SDK/10.0.10240.0/um/minwin/wow64t.h (dmex)
//
// Page size on x86 NT
//
#define PAGE_SIZE_X86NT  0x1000
#define PAGE_SHIFT_X86NT 12L
#define WOW64_SPLITS_PER_PAGE (PAGE_SIZE_X86NT / PAGE_SIZE_X86NT)

//
// Convert the number of native pages to sub x86-pages
//
#define Wow64GetNumberOfX86Pages(NativePages) \
    ((NativePages) * (PAGE_SIZE_X86NT >> PAGE_SHIFT_X86NT))

//
// Macro to round to the nearest page size
//
#define WOW64_ROUND_TO_PAGES(Size) \
    (((ULONG_PTR)(Size) + PAGE_SIZE_X86NT - 1) & ~(PAGE_SIZE_X86NT - 1))

//
// Get number of native pages
//
#define WOW64_BYTES_TO_PAGES(Size) \
    (((ULONG)(Size) >> WOW64_ROUND_TO_PAGES) + (((ULONG)(Size) & (PAGE_SIZE_X86NT - 1)) != 0))

//
// Get the 32-bit TEB without doing a memory reference.
//
#define WOW64_GET_TEB32(teb64) ((PTEB32)(PVOID)Add2Ptr((teb64), WOW64_ROUND_TO_PAGES(sizeof(TEB))))
#define WOW64_TEB32_POINTER_ADDRESS(teb64) (PVOID)&((teb64)->NtTib.ExceptionList)

//
// Get the 32-bit execute options.
//
typedef union _WOW64_EXECUTE_OPTIONS
{
    ULONG Flags;
    struct
    {
        ULONG StackReserveSize : 8;
        ULONG StackCommitSize : 4;
        ULONG Deprecated0 : 1;
        ULONG DisableWowAssert : 1;
        ULONG DisableTurboDispatch : 1;
        ULONG Unused : 13;
        ULONG Reserved0 : 1;
        ULONG Reserved1 : 1;
        ULONG Reserved2 : 1;
        ULONG Reserved3 : 1;
    };
} WOW64_EXECUTE_OPTIONS, * PWOW64_EXECUTE_OPTIONS;

#define WOW64_CPUFLAGS_MSFT64           0x00000001
#define WOW64_CPUFLAGS_SOFTWARE         0x00000002
#define WOW64_CPUFLAGS_IA64             0x00000004

typedef struct _WOW64INFO
{
    ULONG NativeSystemPageSize;
    ULONG CpuFlags;
    WOW64_EXECUTE_OPTIONS Wow64ExecuteFlags;
    ULONG InstrumentationCallback;
} WOW64INFO, * PWOW64INFO;

typedef struct _PEB32_WITH_WOW64INFO
{
    PEB32 Peb32;
    WOW64INFO Wow64Info;
} PEB32_WITH_WOW64INFO, * PPEB32_WITH_WOW64INFO;

#ifdef _M_X64

FORCEINLINE
TEB32*
POINTER_UNSIGNED
Wow64CurrentGuestTeb(
    VOID
)
{
    TEB* POINTER_UNSIGNED Teb;
    TEB32* POINTER_UNSIGNED Teb32;

    Teb = NtCurrentTeb();

    if (Teb->WowTebOffset == 0) {
        //
        // Not running under or over WoW, so there is no "guest teb"
        //

        return NULL;
    }

    if (Teb->WowTebOffset < 0) {
        //
        // Was called while running under WoW. The current teb is the guest teb.
        //

        Teb32 = (PTEB32)(ULONG)(ULONG_PTR)Teb;

        RTL_VERIFY(&Teb32->WowTebOffset == &Teb->WowTebOffset);
    }
    else {
        //
        // Called by the WoW Host, so calculate the position of the guest teb
        // relative to the current (host) teb.
        //

        Teb32 = (PTEB32)(ULONG)(ULONG_PTR)Add2Ptr(Teb, Teb->WowTebOffset);
    }

    RTL_VERIFY(Teb32->NtTib.Self == PtrToUlong(Teb32));

    return Teb32;
}

FORCEINLINE
VOID*
POINTER_UNSIGNED
Wow64CurrentNativeTeb(
    VOID
)
{
    TEB* POINTER_UNSIGNED Teb;
    VOID* POINTER_UNSIGNED HostTeb;

    Teb = NtCurrentTeb();

    if (Teb->WowTebOffset >= 0) {
        //
        // Not running under WoW, so it it either not running on WoW at all, or
        // it is the host. Return the current teb as native teb.
        //

        HostTeb = (PVOID)Teb;
    }
    else {
        //
        // Called while running under WoW Host, so calculate the position of the
        // host teb relative to the current (guest) teb.
        //

        HostTeb = (PVOID)Add2Ptr(Teb, Teb->WowTebOffset);
    }

    RTL_VERIFY((((PTEB32)(ULONG)(ULONG_PTR)HostTeb)->NtTib.Self == PtrToUlong(HostTeb)) || ((ULONG_PTR)((PTEB)HostTeb)->NtTib.Self == (ULONG_PTR)HostTeb));

    return HostTeb;
}

#define NtCurrentTeb32() (Wow64CurrentGuestTeb())
#define NtCurrentPeb32()  ((PPEB32)(UlongToPtr((NtCurrentTeb32()->ProcessEnvironmentBlock))))

#define Wow64GetNativeTebField(teb, field) (((ULONG)(teb) == ((PTEB32)(teb))->NtTib.Self) ? (((PTEB32)(teb))->##field) : (((PTEB)(teb))->##field) )
#define Wow64SetNativeTebField(teb, field, value) { if ((ULONG)(teb) == ((PTEB32)(teb))->NtTib.Self) {(((PTEB32)(teb))->##field) = (value);} else {(((PTEB)(teb))->##field) = (value);} }
#endif // _M_X64

#endif // !defined(_KERNEL_MODE)

#if defined(_KERNEL_MODE) && !defined(_WINDOWS_)

//
// Thread Context
//

#ifndef _LDT_ENTRY_DEFINED
#define _LDT_ENTRY_DEFINED

typedef struct _LDT_ENTRY
{
    WORD    LimitLow;
    WORD    BaseLow;
    union
    {
        struct
        {
            BYTE    BaseMid;
            BYTE    Flags1;     // Declare as bytes to avoid alignment
            BYTE    Flags2;     // Problems.
            BYTE    BaseHi;
        } Bytes;
        struct
        {
            DWORD   BaseMid : 8;
            DWORD   Type : 5;
            DWORD   Dpl : 2;
            DWORD   Pres : 1;
            DWORD   LimitHi : 4;
            DWORD   Sys : 1;
            DWORD   Reserved_0 : 1;
            DWORD   Default_Big : 1;
            DWORD   Granularity : 1;
            DWORD   BaseHi : 8;
        } Bits;
    } HighWord;
} LDT_ENTRY, * PLDT_ENTRY;

#endif

//
// WOW64 Thread Context
//

#if _MSC_VER >= 1200
#pragma warning(push)
#pragma warning(disable:4214) // bitfields other than int
#pragma warning(disable:4668) // #if not_defined treated as #if 0
#pragma warning(disable:4820) // padding added after data member
#endif

#if !defined(RC_INVOKED)

#define WOW64_CONTEXT_i386      0x00010000    // this assumes that i386 and
#define WOW64_CONTEXT_i486      0x00010000    // i486 have identical context records

#define WOW64_CONTEXT_CONTROL               (WOW64_CONTEXT_i386 | 0x00000001L) // SS:SP, CS:IP, FLAGS, BP
#define WOW64_CONTEXT_INTEGER               (WOW64_CONTEXT_i386 | 0x00000002L) // AX, BX, CX, DX, SI, DI
#define WOW64_CONTEXT_SEGMENTS              (WOW64_CONTEXT_i386 | 0x00000004L) // DS, ES, FS, GS
#define WOW64_CONTEXT_FLOATING_POINT        (WOW64_CONTEXT_i386 | 0x00000008L) // 387 state
#define WOW64_CONTEXT_DEBUG_REGISTERS       (WOW64_CONTEXT_i386 | 0x00000010L) // DB 0-3,6,7
#define WOW64_CONTEXT_EXTENDED_REGISTERS    (WOW64_CONTEXT_i386 | 0x00000020L) // cpu specific extensions

#define WOW64_CONTEXT_FULL      (WOW64_CONTEXT_CONTROL | WOW64_CONTEXT_INTEGER | WOW64_CONTEXT_SEGMENTS)

#define WOW64_CONTEXT_ALL       (WOW64_CONTEXT_CONTROL | WOW64_CONTEXT_INTEGER | WOW64_CONTEXT_SEGMENTS | \
                                 WOW64_CONTEXT_FLOATING_POINT | WOW64_CONTEXT_DEBUG_REGISTERS | \
                                 WOW64_CONTEXT_EXTENDED_REGISTERS)

#define WOW64_CONTEXT_XSTATE                (WOW64_CONTEXT_i386 | 0x00000040L)

#define WOW64_CONTEXT_EXCEPTION_ACTIVE      0x08000000
#define WOW64_CONTEXT_SERVICE_ACTIVE        0x10000000
#define WOW64_CONTEXT_EXCEPTION_REQUEST     0x40000000
#define WOW64_CONTEXT_EXCEPTION_REPORTING   0x80000000

#endif // !defined(RC_INVOKED)

//
//  Define the size of the 80387 save area, which is in the context frame.
//

#define WOW64_SIZE_OF_80387_REGISTERS      80

#define WOW64_MAXIMUM_SUPPORTED_EXTENSION     512

typedef struct _WOW64_FLOATING_SAVE_AREA
{
    DWORD   ControlWord;
    DWORD   StatusWord;
    DWORD   TagWord;
    DWORD   ErrorOffset;
    DWORD   ErrorSelector;
    DWORD   DataOffset;
    DWORD   DataSelector;
    BYTE    RegisterArea[WOW64_SIZE_OF_80387_REGISTERS];
    DWORD   Cr0NpxState;
} WOW64_FLOATING_SAVE_AREA;

typedef WOW64_FLOATING_SAVE_AREA* PWOW64_FLOATING_SAVE_AREA;

#include "pshpack4.h"

//
// Context Frame
//
//  This frame has a several purposes: 1) it is used as an argument to
//  NtContinue, 2) is is used to constuct a call frame for APC delivery,
//  and 3) it is used in the user level thread creation routines.
//
//  The layout of the record conforms to a standard call frame.
//

typedef struct _WOW64_CONTEXT
{

    //
    // The flags values within this flag control the contents of
    // a CONTEXT record.
    //
    // If the context record is used as an input parameter, then
    // for each portion of the context record controlled by a flag
    // whose value is set, it is assumed that that portion of the
    // context record contains valid context. If the context record
    // is being used to modify a threads context, then only that
    // portion of the threads context will be modified.
    //
    // If the context record is used as an IN OUT parameter to capture
    // the context of a thread, then only those portions of the thread's
    // context corresponding to set flags will be returned.
    //
    // The context record is never used as an OUT only parameter.
    //

    DWORD ContextFlags;

    //
    // This section is specified/returned if CONTEXT_DEBUG_REGISTERS is
    // set in ContextFlags.  Note that CONTEXT_DEBUG_REGISTERS is NOT
    // included in CONTEXT_FULL.
    //

    DWORD   Dr0;
    DWORD   Dr1;
    DWORD   Dr2;
    DWORD   Dr3;
    DWORD   Dr6;
    DWORD   Dr7;

    //
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_FLOATING_POINT.
    //

    WOW64_FLOATING_SAVE_AREA FloatSave;

    //
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_SEGMENTS.
    //

    DWORD   SegGs;
    DWORD   SegFs;
    DWORD   SegEs;
    DWORD   SegDs;

    //
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_INTEGER.
    //

    DWORD   Edi;
    DWORD   Esi;
    DWORD   Ebx;
    DWORD   Edx;
    DWORD   Ecx;
    DWORD   Eax;

    //
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_CONTROL.
    //

    DWORD   Ebp;
    DWORD   Eip;
    DWORD   SegCs;              // MUST BE SANITIZED
    DWORD   EFlags;             // MUST BE SANITIZED
    DWORD   Esp;
    DWORD   SegSs;

    //
    // This section is specified/returned if the ContextFlags word
    // contains the flag CONTEXT_EXTENDED_REGISTERS.
    // The format and contexts are processor specific
    //

    BYTE    ExtendedRegisters[WOW64_MAXIMUM_SUPPORTED_EXTENSION];

} WOW64_CONTEXT;

typedef WOW64_CONTEXT* PWOW64_CONTEXT;

#include "poppack.h"


typedef struct _WOW64_LDT_ENTRY
{
    WORD    LimitLow;
    WORD    BaseLow;
    union
    {
        struct
        {
            BYTE    BaseMid;
            BYTE    Flags1;     // Declare as bytes to avoid alignment
            BYTE    Flags2;     // Problems.
            BYTE    BaseHi;
        } Bytes;
        struct
        {
            DWORD   BaseMid : 8;
            DWORD   Type : 5;
            DWORD   Dpl : 2;
            DWORD   Pres : 1;
            DWORD   LimitHi : 4;
            DWORD   Sys : 1;
            DWORD   Reserved_0 : 1;
            DWORD   Default_Big : 1;
            DWORD   Granularity : 1;
            DWORD   BaseHi : 8;
        } Bits;
    } HighWord;
} WOW64_LDT_ENTRY, * PWOW64_LDT_ENTRY;

typedef struct _WOW64_DESCRIPTOR_TABLE_ENTRY
{
    DWORD Selector;
    WOW64_LDT_ENTRY Descriptor;
} WOW64_DESCRIPTOR_TABLE_ENTRY, * PWOW64_DESCRIPTOR_TABLE_ENTRY;

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

#endif // defined(_KERNEL_MODE) && !defined(_WINDOWS_)

#ifndef _KERNEL_MODE
//
// Process Information Classes
// NtQueryInformationProcess/NtSetInformationProcess types
//
typedef enum _PROCESSINFOCLASS
{
    ProcessBasicInformation,                // q: PROCESS_BASIC_INFORMATION, PROCESS_EXTENDED_BASIC_INFORMATION
    ProcessQuotaLimits,                     // qs: QUOTA_LIMITS, QUOTA_LIMITS_EX
    ProcessIoCounters,                      // q: IO_COUNTERS
    ProcessVmCounters,                      // q: VM_COUNTERS, VM_COUNTERS_EX, VM_COUNTERS_EX2
    ProcessTimes,                           // q: KERNEL_USER_TIMES
    ProcessBasePriority,                    // s: KPRIORITY
    ProcessRaisePriority,                   // s: ULONG
    ProcessDebugPort,                       // q: HANDLE
    ProcessExceptionPort,                   // s: PROCESS_EXCEPTION_PORT (requires SeTcbPrivilege)
    ProcessAccessToken,                     // s: PROCESS_ACCESS_TOKEN
    ProcessLdtInformation,                  // qs: PROCESS_LDT_INFORMATION // 10
    ProcessLdtSize,                         // s: PROCESS_LDT_SIZE
    ProcessDefaultHardErrorMode,            // qs: ULONG
    ProcessIoPortHandlers,                  // s: PROCESS_IO_PORT_HANDLER_INFORMATION // (kernel-mode only)
    ProcessPooledUsageAndLimits,            // q: POOLED_USAGE_AND_LIMITS
    ProcessWorkingSetWatch,                 // q: PROCESS_WS_WATCH_INFORMATION[]; s: void
    ProcessUserModeIOPL,                    // qs: ULONG (requires SeTcbPrivilege)
    ProcessEnableAlignmentFaultFixup,       // s: BOOLEAN
    ProcessPriorityClass,                   // qs: PROCESS_PRIORITY_CLASS
    ProcessWx86Information,                 // qs: ULONG (requires SeTcbPrivilege) (VdmAllowed)
    ProcessHandleCount,                     // q: ULONG, PROCESS_HANDLE_INFORMATION // 20
    ProcessAffinityMask,                    // (q >WIN7)s: KAFFINITY, qs: GROUP_AFFINITY
    ProcessPriorityBoost,                   // qs: ULONG
    ProcessDeviceMap,                       // qs: PROCESS_DEVICEMAP_INFORMATION, PROCESS_DEVICEMAP_INFORMATION_EX
    ProcessSessionInformation,              // q: PROCESS_SESSION_INFORMATION
    ProcessForegroundInformation,           // s: PROCESS_FOREGROUND_BACKGROUND
    ProcessWow64Information,                // q: ULONG_PTR
    ProcessImageFileName,                   // q: UNICODE_STRING
    ProcessLUIDDeviceMapsEnabled,           // q: ULONG
    ProcessBreakOnTermination,              // qs: ULONG
    ProcessDebugObjectHandle,               // q: HANDLE // 30
    ProcessDebugFlags,                      // qs: ULONG
    ProcessHandleTracing,                   // q: PROCESS_HANDLE_TRACING_QUERY; s: PROCESS_HANDLE_TRACING_ENABLE[_EX] or void to disable
    ProcessIoPriority,                      // qs: IO_PRIORITY_HINT
    ProcessExecuteFlags,                    // qs: ULONG (MEM_EXECUTE_OPTION_*)
    ProcessTlsInformation,                  // PROCESS_TLS_INFORMATION // ProcessResourceManagement 
    ProcessCookie,                          // q: ULONG
    ProcessImageInformation,                // q: SECTION_IMAGE_INFORMATION
    ProcessCycleTime,                       // q: PROCESS_CYCLE_TIME_INFORMATION // since VISTA
    ProcessPagePriority,                    // qs: PAGE_PRIORITY_INFORMATION
    ProcessInstrumentationCallback,         // s: PVOID or PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION // 40
    ProcessThreadStackAllocation,           // s: PROCESS_STACK_ALLOCATION_INFORMATION, PROCESS_STACK_ALLOCATION_INFORMATION_EX
    ProcessWorkingSetWatchEx,               // q: PROCESS_WS_WATCH_INFORMATION_EX[]; s: void
    ProcessImageFileNameWin32,              // q: UNICODE_STRING
    ProcessImageFileMapping,                // q: HANDLE (input)
    ProcessAffinityUpdateMode,              // qs: PROCESS_AFFINITY_UPDATE_MODE
    ProcessMemoryAllocationMode,            // qs: PROCESS_MEMORY_ALLOCATION_MODE
    ProcessGroupInformation,                // q: USHORT[]
    ProcessTokenVirtualizationEnabled,      // s: ULONG
    ProcessConsoleHostProcess,              // qs: ULONG_PTR // ProcessOwnerInformation
    ProcessWindowInformation,               // q: PROCESS_WINDOW_INFORMATION // 50
    ProcessHandleInformation,               // q: PROCESS_HANDLE_SNAPSHOT_INFORMATION // since WIN8
    ProcessMitigationPolicy,                // s: PROCESS_MITIGATION_POLICY_INFORMATION
    ProcessDynamicFunctionTableInformation, // s: PROCESS_DYNAMIC_FUNCTION_TABLE_INFORMATION
    ProcessHandleCheckingMode,              // qs: ULONG; s: 0 disables, otherwise enables
    ProcessKeepAliveCount,                  // q: PROCESS_KEEPALIVE_COUNT_INFORMATION
    ProcessRevokeFileHandles,               // s: PROCESS_REVOKE_FILE_HANDLES_INFORMATION
    ProcessWorkingSetControl,               // s: PROCESS_WORKING_SET_CONTROL
    ProcessHandleTable,                     // q: ULONG[] // since WINBLUE
    ProcessCheckStackExtentsMode,           // qs: ULONG // KPROCESS->CheckStackExtents (CFG)
    ProcessCommandLineInformation,          // q: UNICODE_STRING // 60
    ProcessProtectionInformation,           // q: PS_PROTECTION
    ProcessMemoryExhaustion,                // s: PROCESS_MEMORY_EXHAUSTION_INFO // since THRESHOLD
    ProcessFaultInformation,                // s: PROCESS_FAULT_INFORMATION
    ProcessTelemetryIdInformation,          // q: PROCESS_TELEMETRY_ID_INFORMATION
    ProcessCommitReleaseInformation,        // qs: PROCESS_COMMIT_RELEASE_INFORMATION
    ProcessDefaultCpuSetsInformation,       // qs: SYSTEM_CPU_SET_INFORMATION[5]
    ProcessAllowedCpuSetsInformation,       // qs: SYSTEM_CPU_SET_INFORMATION[5]
    ProcessSubsystemProcess,                // s: void // EPROCESS->SubsystemProcess
    ProcessJobMemoryInformation,            // q: PROCESS_JOB_MEMORY_INFO
    ProcessInPrivate,                       // q: BOOLEAN; s: void // ETW // since THRESHOLD2 // 70
    ProcessRaiseUMExceptionOnInvalidHandleClose, // qs: ULONG; s: 0 disables, otherwise enables
    ProcessIumChallengeResponse,
    ProcessChildProcessInformation,         // q: PROCESS_CHILD_PROCESS_INFORMATION
    ProcessHighGraphicsPriorityInformation, // qs: BOOLEAN (requires SeTcbPrivilege)
    ProcessSubsystemInformation,            // q: SUBSYSTEM_INFORMATION_TYPE // since REDSTONE2
    ProcessEnergyValues,                    // q: PROCESS_ENERGY_VALUES, PROCESS_EXTENDED_ENERGY_VALUES
    ProcessPowerThrottlingState,            // qs: POWER_THROTTLING_PROCESS_STATE
    ProcessReserved3Information,            // ProcessActivityThrottlePolicy // PROCESS_ACTIVITY_THROTTLE_POLICY
    ProcessWin32kSyscallFilterInformation,  // q: WIN32K_SYSCALL_FILTER
    ProcessDisableSystemAllowedCpuSets,     // s: BOOLEAN // 80
    ProcessWakeInformation,                 // q: PROCESS_WAKE_INFORMATION
    ProcessEnergyTrackingState,             // qs: PROCESS_ENERGY_TRACKING_STATE
    ProcessManageWritesToExecutableMemory,  // MANAGE_WRITES_TO_EXECUTABLE_MEMORY // since REDSTONE3
    ProcessCaptureTrustletLiveDump,         // q: ULONG
    ProcessTelemetryCoverage,               // q: TELEMETRY_COVERAGE_HEADER; s: TELEMETRY_COVERAGE_POINT
    ProcessEnclaveInformation,
    ProcessEnableReadWriteVmLogging,        // qs: PROCESS_READWRITEVM_LOGGING_INFORMATION
    ProcessUptimeInformation,               // q: PROCESS_UPTIME_INFORMATION
    ProcessImageSection,                    // q: HANDLE
    ProcessDebugAuthInformation,            // s: CiTool.exe --device-id // PplDebugAuthorization // since RS4 // 90
    ProcessSystemResourceManagement,        // s: PROCESS_SYSTEM_RESOURCE_MANAGEMENT
    ProcessSequenceNumber,                  // q: ULONGLONG
    ProcessLoaderDetour,                    // since RS5
    ProcessSecurityDomainInformation,       // q: PROCESS_SECURITY_DOMAIN_INFORMATION
    ProcessCombineSecurityDomainsInformation, // s: PROCESS_COMBINE_SECURITY_DOMAINS_INFORMATION
    ProcessEnableLogging,                   // qs: PROCESS_LOGGING_INFORMATION
    ProcessLeapSecondInformation,           // qs: PROCESS_LEAP_SECOND_INFORMATION
    ProcessFiberShadowStackAllocation,      // s: PROCESS_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION // since 19H1
    ProcessFreeFiberShadowStackAllocation,  // s: PROCESS_FREE_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION
    ProcessAltSystemCallInformation,        // s: PROCESS_SYSCALL_PROVIDER_INFORMATION // since 20H1 // 100
    ProcessDynamicEHContinuationTargets,    // s: PROCESS_DYNAMIC_EH_CONTINUATION_TARGETS_INFORMATION
    ProcessDynamicEnforcedCetCompatibleRanges, // s: PROCESS_DYNAMIC_ENFORCED_ADDRESS_RANGE_INFORMATION // since 20H2
    ProcessCreateStateChange,               // since WIN11
    ProcessApplyStateChange,
    ProcessEnableOptionalXStateFeatures,    // s: ULONG64 // optional XState feature bitmask
    ProcessAltPrefetchParam,                // qs: OVERRIDE_PREFETCH_PARAMETER // App Launch Prefetch (ALPF) // since 22H1
    ProcessAssignCpuPartitions,             // HANDLE
    ProcessPriorityClassEx,                 // s: PROCESS_PRIORITY_CLASS_EX
    ProcessMembershipInformation,           // q: PROCESS_MEMBERSHIP_INFORMATION
    ProcessEffectiveIoPriority,             // q: IO_PRIORITY_HINT // 110
    ProcessEffectivePagePriority,           // q: ULONG
    ProcessSchedulerSharedData,             // SCHEDULER_SHARED_DATA_SLOT_INFORMATION // since 24H2
    ProcessSlistRollbackInformation,
    ProcessNetworkIoCounters,               // q: PROCESS_NETWORK_COUNTERS
    ProcessFindFirstThreadByTebValue,       // PROCESS_TEB_VALUE_INFORMATION
    ProcessEnclaveAddressSpaceRestriction,  // since 25H2
    ProcessAvailableCpus,                   // PROCESS_AVAILABLE_CPUS_INFORMATION
    MaxProcessInfoClass
} PROCESSINFOCLASS;
#else
#define ProcessDefaultCpuSetsInformation            ((PROCESSINFOCLASS)66)
#define ProcessAllowedCpuSetsInformation            ((PROCESSINFOCLASS)67)
#define ProcessSubsystemProcess                     ((PROCESSINFOCLASS)68)
#define ProcessJobMemoryInformation                 ((PROCESSINFOCLASS)69)
#define ProcessInPrivate                            ((PROCESSINFOCLASS)70)
#define ProcessRaiseUMExceptionOnInvalidHandleClose ((PROCESSINFOCLASS)71)
#define ProcessIumChallengeResponse                 ((PROCESSINFOCLASS)72)
#define ProcessChildProcessInformation              ((PROCESSINFOCLASS)73)
#define ProcessHighGraphicsPriorityInformation      ((PROCESSINFOCLASS)74)
#define ProcessSubsystemInformation                 ((PROCESSINFOCLASS)75)
#define ProcessEnergyValues                         ((PROCESSINFOCLASS)76)
#define ProcessPowerThrottlingState                 ((PROCESSINFOCLASS)77)
#define ProcessReserved3Information                 ((PROCESSINFOCLASS)78)
#define ProcessWin32kSyscallFilterInformation       ((PROCESSINFOCLASS)79)
#define ProcessDisableSystemAllowedCpuSets          ((PROCESSINFOCLASS)80)
#define ProcessWakeInformation                      ((PROCESSINFOCLASS)81)
#define ProcessEnergyTrackingState                  ((PROCESSINFOCLASS)82)
#define ProcessManageWritesToExecutableMemory       ((PROCESSINFOCLASS)83)
#define ProcessCaptureTrustletLiveDump              ((PROCESSINFOCLASS)84)
#define ProcessTelemetryCoverage                    ((PROCESSINFOCLASS)85)
#define ProcessEnclaveInformation                   ((PROCESSINFOCLASS)86)
#define ProcessEnableReadWriteVmLogging             ((PROCESSINFOCLASS)87)
#define ProcessUptimeInformation                    ((PROCESSINFOCLASS)88)
#define ProcessImageSection                         ((PROCESSINFOCLASS)89)
#define ProcessDebugAuthInformation                 ((PROCESSINFOCLASS)90)
#define ProcessSystemResourceManagement             ((PROCESSINFOCLASS)91)
#define PROCESSINFOCLASS_ProcessSequenceNumber      ((PROCESSINFOCLASS)92)
#define ProcessLoaderDetour                         ((PROCESSINFOCLASS)93)
#define ProcessSecurityDomainInformation            ((PROCESSINFOCLASS)94)
#define ProcessCombineSecurityDomainsInformation    ((PROCESSINFOCLASS)95)
#define ProcessEnableLogging                        ((PROCESSINFOCLASS)96)
#define ProcessLeapSecondInformation                ((PROCESSINFOCLASS)97)
#define ProcessFiberShadowStackAllocation           ((PROCESSINFOCLASS)98)
#define ProcessFreeFiberShadowStackAllocation       ((PROCESSINFOCLASS)99)
#define ProcessAltSystemCallInformation             ((PROCESSINFOCLASS)100)
#define ProcessDynamicEHContinuationTargets         ((PROCESSINFOCLASS)101)
#define ProcessDynamicEnforcedCetCompatibleRanges   ((PROCESSINFOCLASS)102)
#define ProcessCreateStateChange                    ((PROCESSINFOCLASS)103)
#define ProcessApplyStateChange                     ((PROCESSINFOCLASS)104)
#define ProcessEnableOptionalXStateFeatures         ((PROCESSINFOCLASS)105)
#define ProcessAltPrefetchParam                     ((PROCESSINFOCLASS)106)
#define ProcessAssignCpuPartitions                  ((PROCESSINFOCLASS)107)
#define ProcessPriorityClassEx                      ((PROCESSINFOCLASS)108)
#define ProcessMembershipInformation                ((PROCESSINFOCLASS)109)
#define ProcessEffectiveIoPriority                  ((PROCESSINFOCLASS)110)
#define ProcessEffectivePagePriority                ((PROCESSINFOCLASS)111)
#define ProcessSchedulerSharedData                  ((PROCESSINFOCLASS)112)
#define ProcessSlistRollbackInformation             ((PROCESSINFOCLASS)113)
#define ProcessNetworkIoCounters                    ((PROCESSINFOCLASS)114)
#define ProcessFindFirstThreadByTebValue            ((PROCESSINFOCLASS)115)
#define ProcessEnclaveAddressSpaceRestriction       ((PROCESSINFOCLASS)116)
#define ProcessAvailableCpus                        ((PROCESSINFOCLASS)117)
#endif // !_KERNEL_MODE

#ifndef _KERNEL_MODE
//
// Thread Information Classes
// NtQueryInformationThread/NtSetInformationThread types
//
typedef enum _THREADINFOCLASS
{
    ThreadBasicInformation,             // q: THREAD_BASIC_INFORMATION
    ThreadTimes,                        // q: KERNEL_USER_TIMES
    ThreadPriority,                     // s: KPRIORITY (requires SeIncreaseBasePriorityPrivilege)
    ThreadBasePriority,                 // s: KPRIORITY
    ThreadAffinityMask,                 // s: KAFFINITY
    ThreadImpersonationToken,           // s: HANDLE
    ThreadDescriptorTableEntry,         // q: DESCRIPTOR_TABLE_ENTRY (or WOW64_DESCRIPTOR_TABLE_ENTRY)
    ThreadEnableAlignmentFaultFixup,    // s: BOOLEAN
    ThreadEventPair,                    // Obsolete
    ThreadQuerySetWin32StartAddress,    // q: ULONG_PTR
    ThreadZeroTlsCell,                  // s: ULONG // TlsIndex // 10
    ThreadPerformanceCount,             // q: LARGE_INTEGER
    ThreadAmILastThread,                // q: ULONG
    ThreadIdealProcessor,               // s: ULONG
    ThreadPriorityBoost,                // qs: ULONG
    ThreadSetTlsArrayAddress,           // s: ULONG_PTR
    ThreadIsIoPending,                  // q: ULONG
    ThreadHideFromDebugger,             // q: BOOLEAN; s: void
    ThreadBreakOnTermination,           // qs: ULONG
    ThreadSwitchLegacyState,            // s: void // NtCurrentThread // NPX/FPU
    ThreadIsTerminated,                 // q: ULONG // 20
    ThreadLastSystemCall,               // q: THREAD_LAST_SYSCALL_INFORMATION
    ThreadIoPriority,                   // qs: IO_PRIORITY_HINT (requires SeIncreaseBasePriorityPrivilege)
    ThreadCycleTime,                    // q: THREAD_CYCLE_TIME_INFORMATION (requires THREAD_QUERY_LIMITED_INFORMATION)
    ThreadPagePriority,                 // qs: PAGE_PRIORITY_INFORMATION
    ThreadActualBasePriority,           // s: LONG (requires SeIncreaseBasePriorityPrivilege)
    ThreadTebInformation,               // q: THREAD_TEB_INFORMATION (requires THREAD_GET_CONTEXT + THREAD_SET_CONTEXT)
    ThreadCSwitchMon,                   // Obsolete
    ThreadCSwitchPmu,                   // Obsolete
    ThreadWow64Context,                 // qs: WOW64_CONTEXT, ARM_NT_CONTEXT since 20H1
    ThreadGroupInformation,             // qs: GROUP_AFFINITY // 30
    ThreadUmsInformation,               // q: THREAD_UMS_INFORMATION // Obsolete
    ThreadCounterProfiling,             // q: BOOLEAN; s: THREAD_PROFILING_INFORMATION?
    ThreadIdealProcessorEx,             // qs: PROCESSOR_NUMBER; s: previous PROCESSOR_NUMBER on return
    ThreadCpuAccountingInformation,     // q: BOOLEAN; s: HANDLE (NtOpenSession) // NtCurrentThread // since WIN8
    ThreadSuspendCount,                 // q: ULONG // since WINBLUE
    ThreadHeterogeneousCpuPolicy,       // q: KHETERO_CPU_POLICY // since THRESHOLD
    ThreadContainerId,                  // q: GUID
    ThreadNameInformation,              // qs: THREAD_NAME_INFORMATION (requires THREAD_SET_LIMITED_INFORMATION)
    ThreadSelectedCpuSets,              // q: ULONG[]
    ThreadSystemThreadInformation,      // q: SYSTEM_THREAD_INFORMATION // 40
    ThreadActualGroupAffinity,          // q: GROUP_AFFINITY // since THRESHOLD2
    ThreadDynamicCodePolicyInfo,        // q: ULONG; s: ULONG (NtCurrentThread)
    ThreadExplicitCaseSensitivity,      // qs: ULONG; s: 0 disables, otherwise enables // (requires SeDebugPrivilege and PsProtectedSignerAntimalware)
    ThreadWorkOnBehalfTicket,           // ALPC_WORK_ON_BEHALF_TICKET // RTL_WORK_ON_BEHALF_TICKET_EX // NtCurrentThread
    ThreadSubsystemInformation,         // q: SUBSYSTEM_INFORMATION_TYPE // since REDSTONE2
    ThreadDbgkWerReportActive,          // s: ULONG; s: 0 disables, otherwise enables
    ThreadAttachContainer,              // s: HANDLE (job object) // NtCurrentThread
    ThreadManageWritesToExecutableMemory, // MANAGE_WRITES_TO_EXECUTABLE_MEMORY // since REDSTONE3
    ThreadPowerThrottlingState,         // qs: POWER_THROTTLING_THREAD_STATE // since REDSTONE3 (set), WIN11 22H2 (query)
    ThreadWorkloadClass,                // THREAD_WORKLOAD_CLASS // since REDSTONE5 // 50
    ThreadCreateStateChange,            // since WIN11
    ThreadApplyStateChange,
    ThreadStrongerBadHandleChecks,      // s: ULONG // NtCurrentThread // since 22H1
    ThreadEffectiveIoPriority,          // q: IO_PRIORITY_HINT
    ThreadEffectivePagePriority,        // q: ULONG
    ThreadUpdateLockOwnership,          // THREAD_LOCK_OWNERSHIP // since 24H2
    ThreadSchedulerSharedDataSlot,      // SCHEDULER_SHARED_DATA_SLOT_INFORMATION
    ThreadTebInformationAtomic,         // q: THREAD_TEB_INFORMATION (requires THREAD_GET_CONTEXT + THREAD_QUERY_INFORMATION)
    ThreadIndexInformation,             // THREAD_INDEX_INFORMATION
    MaxThreadInfoClass
} THREADINFOCLASS;
#else
#define ThreadHeterogeneousCpuPolicy            ((THREADINFOCLASS)36)
#define ThreadContainerId                       ((THREADINFOCLASS)37)
#define ThreadNameInformation                   ((THREADINFOCLASS)38)
#define ThreadSelectedCpuSets                   ((THREADINFOCLASS)39)
#define ThreadSystemThreadInformation           ((THREADINFOCLASS)40)
#define ThreadActualGroupAffinity               ((THREADINFOCLASS)41)
#define ThreadDynamicCodePolicyInfo             ((THREADINFOCLASS)42)
#define ThreadExplicitCaseSensitivity           ((THREADINFOCLASS)43)
#define ThreadWorkOnBehalfTicket                ((THREADINFOCLASS)44)
#define ThreadSubsystemInformation              ((THREADINFOCLASS)45)
#define ThreadDbgkWerReportActive               ((THREADINFOCLASS)46)
#define ThreadAttachContainer                   ((THREADINFOCLASS)47)
#define ThreadManageWritesToExecutableMemory    ((THREADINFOCLASS)48)
#define ThreadPowerThrottlingState              ((THREADINFOCLASS)49)
#define ThreadWorkloadClass                     ((THREADINFOCLASS)50)
#define ThreadCreateStateChange                 ((THREADINFOCLASS)51)
#define ThreadApplyStateChange                  ((THREADINFOCLASS)52)
#define ThreadStrongerBadHandleChecks           ((THREADINFOCLASS)53)
#define ThreadEffectiveIoPriority               ((THREADINFOCLASS)54)
#define ThreadEffectivePagePriority             ((THREADINFOCLASS)55)
#define ThreadUpdateLockOwnership               ((THREADINFOCLASS)56)
#define ThreadSchedulerSharedDataSlot           ((THREADINFOCLASS)57)
#define ThreadTebInformationAtomic              ((THREADINFOCLASS)58)
#define ThreadIndexInformation                  ((THREADINFOCLASS)59)
#endif // !_KERNEL_MODE

#ifndef _KERNEL_MODE
// Use with both ProcessPagePriority and ThreadPagePriority
typedef struct _PAGE_PRIORITY_INFORMATION
{
    ULONG PagePriority;
} PAGE_PRIORITY_INFORMATION, * PPAGE_PRIORITY_INFORMATION;

//
// Process information structures
//

/**
 * The PROCESS_BASIC_INFORMATION structure contains basic information about a process.
 *
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winternl/nf-winternl-ntqueryinformationprocess#process_basic_information
 */
typedef struct _PROCESS_BASIC_INFORMATION
{
    NTSTATUS ExitStatus;                    // The exit status of the process. (GetExitCodeProcess)
    PPEB PebBaseAddress;                    // A pointer to the process environment block (PEB) of the process.
    KAFFINITY AffinityMask;                 // The affinity mask of the process. (GetProcessAffinityMask) (deprecated)
    KPRIORITY BasePriority;                 // The base priority of the process. (GetPriorityClass)
    ULONG_PTR UniqueProcessId;                 // The unique identifier of the process. (GetProcessId)
    ULONG_PTR InheritedFromUniqueProcessId;    // The unique identifier of the parent process.
} PROCESS_BASIC_INFORMATION, * PPROCESS_BASIC_INFORMATION;

/**
 * The PROCESS_EXTENDED_BASIC_INFORMATION structure contains extended basic information about a process.
 */
typedef struct _PROCESS_EXTENDED_BASIC_INFORMATION
{
    _In_ SIZE_T Size; // The size of the structure, in bytes. This member must be set to sizeof(PROCESS_EXTENDED_BASIC_INFORMATION).
    union
    {
        PROCESS_BASIC_INFORMATION BasicInfo;
        struct
        {
            NTSTATUS ExitStatus;    // The exit status of the process. (GetExitCodeProcess)
            PPEB PebBaseAddress;    // A pointer to the process environment block (PEB) of the process.
            KAFFINITY AffinityMask; // The affinity mask of the process. (GetProcessAffinityMask) (deprecated)
            KPRIORITY BasePriority; // The base priority of the process. (GetPriorityClass)
            ULONG_PTR UniqueProcessId; // The unique identifier of the process. (GetProcessId)
            ULONG_PTR InheritedFromUniqueProcessId; // The unique identifier of the parent process.
        };
    };
    union
    {
        ULONG Flags;
        struct
        {
            ULONG IsProtectedProcess : 1;
            ULONG IsWow64Process : 1;
            ULONG IsProcessDeleting : 1;
            ULONG IsCrossSessionCreate : 1;
            ULONG IsFrozen : 1;
            ULONG IsBackground : 1;     // WIN://BGKD
            ULONG IsStronglyNamed : 1;  // WIN://SYSAPPID
            ULONG IsSecureProcess : 1;
            ULONG IsSubsystemProcess : 1;
            ULONG IsTrustedApp : 1; // since 24H2
            ULONG SpareBits : 22;
        };
    };
} PROCESS_EXTENDED_BASIC_INFORMATION, * PPROCESS_EXTENDED_BASIC_INFORMATION;

/**
 * The VM_COUNTERS structure contains various memory usage statistics for a process.
 *
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/psapi/ns-psapi-process_memory_counters
 */
typedef struct _VM_COUNTERS
{
    SIZE_T PeakVirtualSize;             // The peak virtual address space size of this process, in bytes.
    SIZE_T VirtualSize;                 // The virtual address space size of this process, in bytes.
    ULONG  PageFaultCount;               // The number of page faults.
    SIZE_T PeakWorkingSetSize;          // The peak working set size, in bytes.
    SIZE_T WorkingSetSize;              // The current working set size, in bytes
    SIZE_T QuotaPeakPagedPoolUsage;     // The peak paged pool usage, in bytes.
    SIZE_T QuotaPagedPoolUsage;         // The current paged pool usage, in bytes.
    SIZE_T QuotaPeakNonPagedPoolUsage;  // The peak non-paged pool usage, in bytes.
    SIZE_T QuotaNonPagedPoolUsage;      // The current non-paged pool usage, in bytes.
    SIZE_T PagefileUsage;               // The Commit Charge value in bytes for this process. Commit Charge is the total amount of private memory that the memory manager has committed for a running process.
    SIZE_T PeakPagefileUsage;           // The peak value in bytes of the Commit Charge during the lifetime of this process.
} VM_COUNTERS, * PVM_COUNTERS;

/**
 * The VM_COUNTERS_EX structure extends VM_COUNTERS to include private memory usage.
 *
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/psapi/ns-psapi-process_memory_counters_ex2
 */
typedef struct _VM_COUNTERS_EX
{
    SIZE_T PeakVirtualSize;             // The peak virtual address space size of this process, in bytes.
    SIZE_T VirtualSize;                 // The virtual address space size of this process, in bytes.
    ULONG  PageFaultCount;               // The number of page faults.
    SIZE_T PeakWorkingSetSize;          // The peak working set size, in bytes.
    SIZE_T WorkingSetSize;              // The current working set size, in bytes
    SIZE_T QuotaPeakPagedPoolUsage;     // The peak paged pool usage, in bytes.
    SIZE_T QuotaPagedPoolUsage;         // The current paged pool usage, in bytes.
    SIZE_T QuotaPeakNonPagedPoolUsage;  // The peak non-paged pool usage, in bytes.
    SIZE_T QuotaNonPagedPoolUsage;      // The current non-paged pool usage, in bytes.
    SIZE_T PagefileUsage;               // The Commit Charge value in bytes for this process. Commit Charge is the total amount of private memory that the memory manager has committed for a running process.
    SIZE_T PeakPagefileUsage;           // The peak value in bytes of the Commit Charge during the lifetime of this process.
    SIZE_T PrivateUsage;                // Same as PagefileUsage. The Commit Charge value in bytes for this process. Commit Charge is the total amount of private memory that the memory manager has committed for a running process.
} VM_COUNTERS_EX, * PVM_COUNTERS_EX;

/**
 * The VM_COUNTERS_EX2 structure extends VM_COUNTERS_EX to include private working set size and shared commit usage.
 *
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/psapi/ns-psapi-process_memory_counters_ex2
 */
typedef struct _VM_COUNTERS_EX2
{
    union
    {
        VM_COUNTERS_EX CountersEx;
        struct
        {
            SIZE_T PeakVirtualSize;             // The peak virtual address space size of this process, in bytes.
            SIZE_T VirtualSize;                 // The virtual address space size of this process, in bytes.
            ULONG PageFaultCount;               // The number of page faults.
            SIZE_T PeakWorkingSetSize;          // The peak working set size, in bytes.
            SIZE_T WorkingSetSize;              // The current working set size, in bytes
            SIZE_T QuotaPeakPagedPoolUsage;     // The peak paged pool usage, in bytes.
            SIZE_T QuotaPagedPoolUsage;         // The current paged pool usage, in bytes.
            SIZE_T QuotaPeakNonPagedPoolUsage;  // The peak non-paged pool usage, in bytes.
            SIZE_T QuotaNonPagedPoolUsage;      // The current non-paged pool usage, in bytes.
            SIZE_T PagefileUsage;               // The Commit Charge value in bytes for this process. Commit Charge is the total amount of private memory that the memory manager has committed for a running process.
            SIZE_T PeakPagefileUsage;           // The peak value in bytes of the Commit Charge during the lifetime of this process.
            SIZE_T PrivateUsage;                // Same as PagefileUsage. The Commit Charge value in bytes for this process. Commit Charge is the total amount of private memory that the memory manager has committed for a running process.
        };
    };
    SIZE_T PrivateWorkingSetSize;               // The current private working set size, in bytes.
    SIZE_T SharedCommitUsage;                   // The current shared commit usage, in bytes.
} VM_COUNTERS_EX2, * PVM_COUNTERS_EX2;

/**
 * The KERNEL_USER_TIMES structure contains timing information for a process or thread.
 *
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-getthreadtimes
 */
typedef struct _KERNEL_USER_TIMES
{
    LARGE_INTEGER CreateTime;        // The creation time of the process or thread.
    LARGE_INTEGER ExitTime;          // The exit time of the process or thread.
    LARGE_INTEGER KernelTime;        // The amount of time the process has executed in kernel mode.
    LARGE_INTEGER UserTime;          // The amount of time the process has executed in user mode.
} KERNEL_USER_TIMES, * PKERNEL_USER_TIMES;

/**
 * The POOLED_USAGE_AND_LIMITS structure contains information about the usage and limits of paged and non-paged pool memory.
 */
typedef struct _POOLED_USAGE_AND_LIMITS
{
    SIZE_T PeakPagedPoolUsage;       // The peak paged pool usage.
    SIZE_T PagedPoolUsage;           // The current paged pool usage.
    SIZE_T PagedPoolLimit;           // The limit on paged pool usage.
    SIZE_T PeakNonPagedPoolUsage;    // The peak non-paged pool usage.
    SIZE_T NonPagedPoolUsage;        // The current non-paged pool usage.
    SIZE_T NonPagedPoolLimit;        // The limit on non-paged pool usage.
    SIZE_T PeakPagefileUsage;        // The peak pagefile usage.
    SIZE_T PagefileUsage;            // The current pagefile usage.
    SIZE_T PagefileLimit;            // The limit on pagefile usage.
} POOLED_USAGE_AND_LIMITS, * PPOOLED_USAGE_AND_LIMITS;

#define PROCESS_EXCEPTION_PORT_ALL_STATE_BITS 0x00000003
#define PROCESS_EXCEPTION_PORT_ALL_STATE_FLAGS ((ULONG_PTR)((1UL << PROCESS_EXCEPTION_PORT_ALL_STATE_BITS) - 1))
/**
 * The PROCESS_EXCEPTION_PORT structure is used to manage exception ports for a process.
 */
typedef struct _PROCESS_EXCEPTION_PORT
{
    //
    // Handle to the exception port. No particular access required.
    //
    _In_ HANDLE ExceptionPortHandle;

    //
    // Miscellaneous state flags to be cached along with the exception
    // port in the kernel.
    //
    _Inout_ ULONG StateFlags;

} PROCESS_EXCEPTION_PORT, * PPROCESS_EXCEPTION_PORT;

/**
 * The PROCESS_ACCESS_TOKEN structure is used to manage the security context of a process or thread.
 *
 * A process's access token can only be changed if the process has no threads or a single thread that has not yet begun execution.
 */
typedef struct _PROCESS_ACCESS_TOKEN
{
    //
    // Handle to Primary token to assign to the process.
    // TOKEN_ASSIGN_PRIMARY access to this token is needed.
    //
    HANDLE Token;

    //
    // Handle to the initial thread of the process.
    // THREAD_QUERY_INFORMATION access to this thread is needed.
    //
    // N.B. This field is unused.
    //
    HANDLE Thread;

} PROCESS_ACCESS_TOKEN, * PPROCESS_ACCESS_TOKEN;
#endif // !_KERNEL_MODE

/**
 * The PROCESS_LDT_INFORMATION structure is used to manage Local Descriptor Table (LDT) entries for a process.
 */
typedef struct _PROCESS_LDT_INFORMATION
{
    ULONG Start;
    ULONG Length;
    LDT_ENTRY LdtEntries[1];
} PROCESS_LDT_INFORMATION, * PPROCESS_LDT_INFORMATION;

/**
 * The PROCESS_LDT_SIZE structure is used to specify the size of the Local Descriptor Table (LDT) for a process.
 */
typedef struct _PROCESS_LDT_SIZE
{
    ULONG Length;
} PROCESS_LDT_SIZE, * PPROCESS_LDT_SIZE;

#ifndef _KERNEL_MODE
/**
 * The PROCESS_WS_WATCH_INFORMATION structure is used to store information about working set watch events for a process.
 *
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/psapi/ns-psapi-psapi_ws_watch_information
 */
typedef struct _PROCESS_WS_WATCH_INFORMATION
{
    PVOID FaultingPc; // A pointer to the instruction that caused the page fault.
    PVOID FaultingVa; // A pointer to the page that was added to the working set.
} PROCESS_WS_WATCH_INFORMATION, * PPROCESS_WS_WATCH_INFORMATION;
#endif // !_KERNEL_MODE

/**
 * The PROCESS_WS_WATCH_INFORMATION_EX structure contains extended information about a page added to a process working set.
 *
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/psapi/ns-psapi-psapi_ws_watch_information_ex
 */
typedef struct _PROCESS_WS_WATCH_INFORMATION_EX
{
    union
    {
        PROCESS_WS_WATCH_INFORMATION BasicInfo;
        struct
        {
            PVOID FaultingPc;   // The address of the instruction that caused the page fault.
            PVOID FaultingVa;   // The virtual address that caused the page fault.
        };
    };
    HANDLE FaultingThreadId;    // The identifier of the thread that caused the page fault.
    ULONG_PTR Flags;            // This member is reserved for future use.
} PROCESS_WS_WATCH_INFORMATION_EX, * PPROCESS_WS_WATCH_INFORMATION_EX;

#define PROCESS_PRIORITY_CLASS_UNKNOWN      0
#define PROCESS_PRIORITY_CLASS_IDLE         1
#define PROCESS_PRIORITY_CLASS_NORMAL       2
#define PROCESS_PRIORITY_CLASS_HIGH         3
#define PROCESS_PRIORITY_CLASS_REALTIME     4
#define PROCESS_PRIORITY_CLASS_BELOW_NORMAL 5
#define PROCESS_PRIORITY_CLASS_ABOVE_NORMAL 6

/**
 * The PROCESS_PRIORITY_CLASS structure is used to manage the priority class of a process.
 */
typedef struct _PROCESS_PRIORITY_CLASS
{
    BOOLEAN Foreground;
    UCHAR PriorityClass;
} PROCESS_PRIORITY_CLASS, * PPROCESS_PRIORITY_CLASS;

/**
 * The PROCESS_PRIORITY_CLASS_EX structure extends PROCESS_PRIORITY_CLASS to include validity flags.
 */
typedef struct _PROCESS_PRIORITY_CLASS_EX
{
    union
    {
        struct
        {
            USHORT ForegroundValid : 1;
            USHORT PriorityClassValid : 1;
        };
        USHORT AllFlags;
    };
    UCHAR PriorityClass;
    BOOLEAN Foreground;
} PROCESS_PRIORITY_CLASS_EX, * PPROCESS_PRIORITY_CLASS_EX;

/**
 * The PROCESS_FOREGROUND_BACKGROUND structure is used to manage the the priority class of a process, specifically whether it runs in the foreground or background.
 */
typedef struct _PROCESS_FOREGROUND_BACKGROUND
{
    BOOLEAN Foreground;
} PROCESS_FOREGROUND_BACKGROUND, * PPROCESS_FOREGROUND_BACKGROUND;

#ifndef _KERNEL_MODE
/**
 * The PROCESS_DEVICEMAP_INFORMATION structure contains information about a process's device map.
 */
typedef struct _PROCESS_DEVICEMAP_INFORMATION
{
    union
    {
        struct
        {
            HANDLE DirectoryHandle; // A handle to a directory object that can be set as the new device map for the process. This handle must have DIRECTORY_TRAVERSE access.
        } Set;
        struct
        {
            ULONG DriveMap;         // A bitmask that indicates which drive letters are currently in use in the process's device map.
            UCHAR DriveType[32];    // A value that indicates the type of each drive (e.g., local disk, network drive, etc.). // DRIVE_* WinBase.h
        } Query;
    };
} PROCESS_DEVICEMAP_INFORMATION, * PPROCESS_DEVICEMAP_INFORMATION;

#define PROCESS_LUID_DOSDEVICES_ONLY 0x00000001

/**
 * The _PROCESS_DEVICEMAP_INFORMATION_EX structure contains information about a process's device map.
 */
typedef struct _PROCESS_DEVICEMAP_INFORMATION_EX
{
    union
    {
        struct
        {
            HANDLE DirectoryHandle; // A handle to a directory object that can be set as the new device map for the process. This handle must have DIRECTORY_TRAVERSE access.
        } Set;
        struct
        {
            ULONG DriveMap;         // A bitmask that indicates which drive letters are currently in use in the process's device map.
            UCHAR DriveType[32];    // A value that indicates the type of each drive (e.g., local disk, network drive, etc.). // DRIVE_* WinBase.h
        } Query;
    };
    ULONG Flags; // PROCESS_LUID_DOSDEVICES_ONLY
} PROCESS_DEVICEMAP_INFORMATION_EX, * PPROCESS_DEVICEMAP_INFORMATION_EX;

/**
 * The PROCESS_SESSION_INFORMATION structure is used to store information about the session ID of a process.
 */
typedef struct _PROCESS_SESSION_INFORMATION
{
    ULONG SessionId;
} PROCESS_SESSION_INFORMATION, * PPROCESS_SESSION_INFORMATION;

#define PROCESS_HANDLE_EXCEPTIONS_ENABLED 0x00000001

#define PROCESS_HANDLE_RAISE_EXCEPTION_ON_INVALID_HANDLE_CLOSE_DISABLED 0x00000000
#define PROCESS_HANDLE_RAISE_EXCEPTION_ON_INVALID_HANDLE_CLOSE_ENABLED 0x00000001

/**
 * The PROCESS_HANDLE_TRACING_ENABLE structure is used to enable handle tracing for a process.
 */
typedef struct _PROCESS_HANDLE_TRACING_ENABLE
{
    ULONG Flags; // Flags that control handle tracing.
} PROCESS_HANDLE_TRACING_ENABLE, * PPROCESS_HANDLE_TRACING_ENABLE;

/**
 * The PROCESS_HANDLE_TRACING_MAX_SLOTS macro specifies the maximum number of slots.
 */
#define PROCESS_HANDLE_TRACING_MAX_SLOTS 0x20000

/**
 * The PROCESS_HANDLE_TRACING_ENABLE_EX structure extends PROCESS_HANDLE_TRACING_ENABLE to include the total number of slots.
 */
typedef struct _PROCESS_HANDLE_TRACING_ENABLE_EX
{
    ULONG Flags;        // Flags that control handle tracing.
    ULONG TotalSlots;   // Total number of handle tracing slots.
} PROCESS_HANDLE_TRACING_ENABLE_EX, * PPROCESS_HANDLE_TRACING_ENABLE_EX;

#define PROCESS_HANDLE_TRACING_MAX_STACKS   16

#define PROCESS_HANDLE_TRACE_TYPE_OPEN      1
#define PROCESS_HANDLE_TRACE_TYPE_CLOSE     2
#define PROCESS_HANDLE_TRACE_TYPE_BADREF    3

/**
 * The PROCESS_HANDLE_TRACING_ENTRY structure contains information about the handle operation associated with the event.
 */
typedef struct _PROCESS_HANDLE_TRACING_ENTRY
{
    HANDLE Handle;
    CLIENT_ID ClientId;
    ULONG Type;
    PVOID Stacks[PROCESS_HANDLE_TRACING_MAX_STACKS];
} PROCESS_HANDLE_TRACING_ENTRY, * PPROCESS_HANDLE_TRACING_ENTRY;

/**
 * The PROCESS_HANDLE_TRACING_QUERY structure is used to query all handle events or a specific handle event for a process.
 */
typedef struct _PROCESS_HANDLE_TRACING_QUERY
{
    _In_opt_ HANDLE Handle;
    _Out_ ULONG TotalTraces;
    _Out_ PROCESS_HANDLE_TRACING_ENTRY HandleTrace[1];
} PROCESS_HANDLE_TRACING_QUERY, * PPROCESS_HANDLE_TRACING_QUERY;
#endif // !_KERNEL_MODE

/**
 * The THREAD_TLS_INFORMATION structure contains information about the Thread Local Storage (TLS) data for a thread.
 */
typedef struct _THREAD_TLS_INFORMATION
{
    ULONG Flags;         // Flags that provide additional information about the TLS data.
    PVOID NewTlsData;    // Pointer to the new TLS data.
    PVOID OldTlsData;    // Pointer to the old TLS data.
    HANDLE ThreadId;     // Handle to the thread associated with the TLS data.
} THREAD_TLS_INFORMATION, * PTHREAD_TLS_INFORMATION;

/**
 * The PROCESS_TLS_INFORMATION_TYPE enumeration defines the types of TLS operations that can be performed on a process.
 */
typedef enum _PROCESS_TLS_INFORMATION_TYPE
{
    ProcessTlsReplaceIndex,     // Replace the TLS index.
    ProcessTlsReplaceVector,    // Replace the TLS vector.
    MaxProcessTlsOperation      // Maximum value for the enumeration.
} PROCESS_TLS_INFORMATION_TYPE, * PPROCESS_TLS_INFORMATION_TYPE;

/**
 * The PROCESS_TLS_INFORMATION structure contains information about the TLS operations for a process.
 */
typedef struct _PROCESS_TLS_INFORMATION
{
    ULONG Flags;                // Flags that provide additional information about the TLS operation.
    ULONG OperationType;        // The type of TLS operation to be performed.
    ULONG ThreadDataCount;      // The number of THREAD_TLS_INFORMATION structures in the ThreadData array.
    ULONG TlsIndex;             // The TLS index to be replaced.
    ULONG PreviousCount;        // The previous count of TLS data.
    _Field_size_(ThreadDataCount) THREAD_TLS_INFORMATION ThreadData[1]; // Array of THREAD_TLS_INFORMATION structures.
} PROCESS_TLS_INFORMATION, * PPROCESS_TLS_INFORMATION;

/**
 * The PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION structure contains information about the instrumentation callback for a process.
 */
typedef struct _PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION
{
    ULONG Version;  // The version of the instrumentation callback information.
    ULONG Reserved; // Reserved for future use.
    PVOID Callback; // Pointer to the callback function.
} PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION, * PPROCESS_INSTRUMENTATION_CALLBACK_INFORMATION;

/**
 * The PROCESS_STACK_ALLOCATION_INFORMATION structure contains information about the stack allocation for a process.
 */
typedef struct _PROCESS_STACK_ALLOCATION_INFORMATION
{
    SIZE_T ReserveSize; // The size of the stack to be reserved.
    SIZE_T ZeroBits;    // The number of zero bits in the stack base address.
    PVOID StackBase;    // Pointer to the base of the stack.
} PROCESS_STACK_ALLOCATION_INFORMATION, * PPROCESS_STACK_ALLOCATION_INFORMATION;

/**
 * The PROCESS_STACK_ALLOCATION_INFORMATION_EX structure extends PROCESS_STACK_ALLOCATION_INFORMATION to include additional fields.
 */
typedef struct _PROCESS_STACK_ALLOCATION_INFORMATION_EX
{
    ULONG PreferredNode; // The preferred NUMA node for the stack allocation.
    ULONG Reserved0;     // Reserved for future use.
    ULONG Reserved1;     // Reserved for future use.
    ULONG Reserved2;     // Reserved for future use.
    PROCESS_STACK_ALLOCATION_INFORMATION AllocInfo; // The stack allocation information.
} PROCESS_STACK_ALLOCATION_INFORMATION_EX, * PPROCESS_STACK_ALLOCATION_INFORMATION_EX;

/**
 * The PROCESS_AFFINITY_UPDATE_MODE union is used to specify the affinity update mode for a process.
 */
typedef union _PROCESS_AFFINITY_UPDATE_MODE
{
    ULONG Flags;
    struct
    {
        ULONG EnableAutoUpdate : 1; // Indicates whether auto-update of affinity is enabled.
        ULONG Permanent : 1;        // Indicates whether the affinity update is permanent.
        ULONG Reserved : 30;        // Reserved for future use.
    };
} PROCESS_AFFINITY_UPDATE_MODE, * PPROCESS_AFFINITY_UPDATE_MODE;

/**
 * The PROCESS_MEMORY_ALLOCATION_MODE union is used to specify the memory allocation mode for a process.
 */
typedef union _PROCESS_MEMORY_ALLOCATION_MODE
{
    ULONG Flags;
    struct
    {
        ULONG TopDown : 1;      // Indicates whether memory allocation should be top-down.
        ULONG Reserved : 31;    // Reserved for future use.
    };
} PROCESS_MEMORY_ALLOCATION_MODE, * PPROCESS_MEMORY_ALLOCATION_MODE;

/**
 * The PROCESS_HANDLE_INFORMATION structure contains information about the handles of a process.
 */
typedef struct _PROCESS_HANDLE_INFORMATION
{
    ULONG HandleCount;              // The number of handles in the process.
    ULONG HandleCountHighWatermark; // The highest number of handles that the process has had.
} PROCESS_HANDLE_INFORMATION, * PPROCESS_HANDLE_INFORMATION;

/**
 * The PROCESS_CYCLE_TIME_INFORMATION structure contains information about the cycle time of a process.
 */
typedef struct _PROCESS_CYCLE_TIME_INFORMATION
{
    ULONGLONG AccumulatedCycles; // The total number of cycles accumulated by the process.
    ULONGLONG CurrentCycleCount; // The current cycle count of the process.
} PROCESS_CYCLE_TIME_INFORMATION, * PPROCESS_CYCLE_TIME_INFORMATION;

/**
 * The PROCESS_WINDOW_INFORMATION structure contains information about the windows of a process.
 */
typedef struct _PROCESS_WINDOW_INFORMATION
{
    ULONG WindowFlags;          // Flags that provide information about the window.
    USHORT WindowTitleLength;   // The length of the window title.
    _Field_size_bytes_(WindowTitleLength) WCHAR WindowTitle[1]; // The title of the window.
} PROCESS_WINDOW_INFORMATION, * PPROCESS_WINDOW_INFORMATION;

/**
 * The PROCESS_HANDLE_TABLE_ENTRY_INFO structure contains information about a handle table entry of a process.
 */
typedef struct _PROCESS_HANDLE_TABLE_ENTRY_INFO
{
    HANDLE HandleValue;         // The value of the handle.
    SIZE_T HandleCount;         // The number of references to the handle.
    SIZE_T PointerCount;        // The number of pointers to the handle.
    ACCESS_MASK GrantedAccess;  // The access rights granted to the handle.
    ULONG ObjectTypeIndex;      // The index of the object type.
    ULONG HandleAttributes;     // The attributes of the handle.
    ULONG Reserved;             // Reserved for future use.
} PROCESS_HANDLE_TABLE_ENTRY_INFO, * PPROCESS_HANDLE_TABLE_ENTRY_INFO;

/**
 * The PROCESS_HANDLE_SNAPSHOT_INFORMATION structure contains information about the handle snapshot of a process.
 */
typedef struct _PROCESS_HANDLE_SNAPSHOT_INFORMATION
{
    SIZE_T NumberOfHandles;
    ULONG_PTR Reserved;
    PROCESS_HANDLE_TABLE_ENTRY_INFO Handles[1];
} PROCESS_HANDLE_SNAPSHOT_INFORMATION, * PPROCESS_HANDLE_SNAPSHOT_INFORMATION;

typedef struct _PROCESS_MITIGATION_ACTIVATION_CONTEXT_TRUST_POLICY2
{
    union
    {
        ULONG Flags;
        struct
        {
            ULONG AssemblyManifestRedirectionTrust : 1;
            ULONG ReservedFlags : 31;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;
} PROCESS_MITIGATION_ACTIVATION_CONTEXT_TRUST_POLICY2, * PPROCESS_MITIGATION_ACTIVATION_CONTEXT_TRUST_POLICY2;

/**
 * The PROCESS_MITIGATION_POLICY_INFORMATION structure represents the different process mitigation policies.
 *
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winnt/ne-winnt-process_mitigation_policy
 */
typedef struct _PROCESS_MITIGATION_POLICY_INFORMATION
{
    PROCESS_MITIGATION_POLICY Policy;
    union
    {
        PROCESS_MITIGATION_ASLR_POLICY ASLRPolicy;
        PROCESS_MITIGATION_STRICT_HANDLE_CHECK_POLICY StrictHandleCheckPolicy;
        PROCESS_MITIGATION_SYSTEM_CALL_DISABLE_POLICY SystemCallDisablePolicy;
        PROCESS_MITIGATION_EXTENSION_POINT_DISABLE_POLICY ExtensionPointDisablePolicy;
        PROCESS_MITIGATION_DYNAMIC_CODE_POLICY DynamicCodePolicy;

#if (NTDDI_VERSION >= NTDDI_WIN10_TH2)
        PROCESS_MITIGATION_CONTROL_FLOW_GUARD_POLICY ControlFlowGuardPolicy;
        PROCESS_MITIGATION_BINARY_SIGNATURE_POLICY SignaturePolicy;
        PROCESS_MITIGATION_FONT_DISABLE_POLICY FontDisablePolicy;
        PROCESS_MITIGATION_IMAGE_LOAD_POLICY ImageLoadPolicy;
#endif // NTDDI_VERSION >= NTDDI_WIN10_TH2

#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)
        PROCESS_MITIGATION_SYSTEM_CALL_FILTER_POLICY SystemCallFilterPolicy;
        PROCESS_MITIGATION_PAYLOAD_RESTRICTION_POLICY PayloadRestrictionPolicy;
        PROCESS_MITIGATION_CHILD_PROCESS_POLICY ChildProcessPolicy;
#endif // NTDDI_VERSION >= NTDDI_WIN10

#if (NTDDI_VERSION >= NTDDI_WIN10_RS5)
        PROCESS_MITIGATION_SIDE_CHANNEL_ISOLATION_POLICY SideChannelIsolationPolicy;
#endif // NTDDI_VERSION >= NTDDI_WIN10_RS5

#if (NTDDI_VERSION >= NTDDI_WIN10_VB)
        PROCESS_MITIGATION_USER_SHADOW_STACK_POLICY UserShadowStackPolicy;
#endif // NTDDI_VERSION >= NTDDI_WIN10_MN

#if (NTDDI_VERSION >= NTDDI_WIN10_MN)
        PROCESS_MITIGATION_REDIRECTION_TRUST_POLICY RedirectionTrustPolicy;
#endif // NTDDI_VERSION >= NTDDI_WIN10_MN

#if (NTDDI_VERSION >= NTDDI_WIN11_NI)
        PROCESS_MITIGATION_USER_POINTER_AUTH_POLICY UserPointerAuthPolicy;
        PROCESS_MITIGATION_SEHOP_POLICY SEHOPPolicy;
#endif // NTDDI_VERSION >= NTDDI_WIN10_MN
    };
} PROCESS_MITIGATION_POLICY_INFORMATION, * PPROCESS_MITIGATION_POLICY_INFORMATION;

// private
typedef struct _DYNAMIC_FUNCTION_TABLE DYNAMIC_FUNCTION_TABLE, * PDYNAMIC_FUNCTION_TABLE;

// private
typedef struct _PROCESS_DYNAMIC_FUNCTION_TABLE_INFORMATION
{
    PDYNAMIC_FUNCTION_TABLE DynamicFunctionTable;
    BOOLEAN Remove;
} PROCESS_DYNAMIC_FUNCTION_TABLE_INFORMATION, * PPROCESS_DYNAMIC_FUNCTION_TABLE_INFORMATION;

#ifndef _KERNEL_MODE
typedef struct _PROCESS_KEEPALIVE_COUNT_INFORMATION
{
    ULONG WakeCount;
    ULONG NoWakeCount;
} PROCESS_KEEPALIVE_COUNT_INFORMATION, * PPROCESS_KEEPALIVE_COUNT_INFORMATION;

/**
 * The PROCESS_REVOKE_FILE_HANDLES_INFORMATION structure revokes handles to the specified device from a process.
 */
typedef struct _PROCESS_REVOKE_FILE_HANDLES_INFORMATION
{
    UNICODE_STRING TargetDevicePath;
} PROCESS_REVOKE_FILE_HANDLES_INFORMATION, * PPROCESS_REVOKE_FILE_HANDLES_INFORMATION;
#endif // !_KERNEL_MODE

// begin_private

#define PROCESS_WORKING_SET_CONTROL_VERSION 3

/**
 * The PROCESS_WORKING_SET_OPERATION enumeration defines the operation to perform on a process's working set.
 */
typedef enum _PROCESS_WORKING_SET_OPERATION
{
    ProcessWorkingSetSwap,              // Swap the working set of a process to disk. // (requires SeDebugPrivilege)
    ProcessWorkingSetEmpty,             // Remove all pages from the working set of a process.
    ProcessWorkingSetEmptyPrivatePages, // Remove private pages from the working set of a process.
    ProcessWorkingSetOperationMax
} PROCESS_WORKING_SET_OPERATION;

/**
 * The PROCESS_WORKING_SET_FLAG_EMPTY_PRIVATE_PAGES flag indicates that the operation should target private pages in the working set.
 * Private pages are those that are not shared with other processes.
 */
#define PROCESS_WORKING_SET_FLAG_EMPTY_PRIVATE_PAGES 0x01
 /**
  * The PROCESS_WORKING_SET_FLAG_EMPTY_SHARED_PAGES flag indicates that the operation should target shared pages in the working set.
  * Shared pages are those that are shared between multiple processes.
  */
#define PROCESS_WORKING_SET_FLAG_EMPTY_SHARED_PAGES  0x02
  /**
   * The PROCESS_WORKING_SET_FLAG_COMPRESS flag indicates that the operation should compress the pages before they are removed from the working set.
   * Compression is typically used in conjunction with other flags to specify that the pages should be compressed as part of the operation.
   */
#define PROCESS_WORKING_SET_FLAG_COMPRESS            0x08
   /**
    * The PROCESS_WORKING_SET_FLAG_STORE flag indicates that the operation should store the compressed pages.
    * This is useful when the compressed data might be needed later, allowing for efficient retrieval and decompression when required.
    * This flag is typically used in conjunction with the PROCESS_WORKING_SET_FLAG_COMPRESS flag to specify that the compressed pages should be stored.
    */
#define PROCESS_WORKING_SET_FLAG_STORE               0x10

/**
 * The PROCESS_WORKING_SET_CONTROL structure is used to control the working set of a process.
 */
typedef struct _PROCESS_WORKING_SET_CONTROL
{
    ULONG Version;
    PROCESS_WORKING_SET_OPERATION Operation;
    ULONG Flags;
} PROCESS_WORKING_SET_CONTROL, * PPROCESS_WORKING_SET_CONTROL;

/**
 * The PS_PROTECTED_TYPE enumeration defines the types of protection that can be applied to a process.
 */
typedef enum _PS_PROTECTED_TYPE
{
    PsProtectedTypeNone,            // No protection.
    PsProtectedTypeProtectedLight,  // Light protection.
    PsProtectedTypeProtected,       // Full protection.
    PsProtectedTypeMax
} PS_PROTECTED_TYPE;

/**
 * The PS_PROTECTED_SIGNER enumeration defines the types of signers that can be associated with a protected process.
 */
typedef enum _PS_PROTECTED_SIGNER
{
    PsProtectedSignerNone,          // No signer.
    PsProtectedSignerAuthenticode,  // Authenticode signer.
    PsProtectedSignerCodeGen,       // Code generation signer.
    PsProtectedSignerAntimalware,   // Antimalware signer.
    PsProtectedSignerLsa,           // Local Security Authority signer.
    PsProtectedSignerWindows,       // Windows signer.
    PsProtectedSignerWinTcb,        // Windows Trusted Computing Base signer.
    PsProtectedSignerWinSystem,     // Windows system signer.
    PsProtectedSignerApp,           // Application signer.
    PsProtectedSignerMax
} PS_PROTECTED_SIGNER;

#define PS_PROTECTED_SIGNER_MASK 0xFF
#define PS_PROTECTED_AUDIT_MASK 0x08
#define PS_PROTECTED_TYPE_MASK 0x07

// ProtectionLevel.Level = PsProtectedValue(PsProtectedSignerCodeGen, FALSE, PsProtectedTypeProtectedLight)
#define PsProtectedValue(PsSigner, PsAudit, PsType) ( \
    (((PsSigner) & PS_PROTECTED_SIGNER_MASK) << 4) | \
    (((PsAudit) & PS_PROTECTED_AUDIT_MASK) << 3) | \
    (((PsType) & PS_PROTECTED_TYPE_MASK)) \
    )

// InitializePsProtection(&ProtectionLevel, PsProtectedSignerCodeGen, FALSE, PsProtectedTypeProtectedLight)
#define InitializePsProtection(PsProtectionLevel, PsSigner, PsAudit, PsType) { \
    (PsProtectionLevel)->Signer = (PsSigner); \
    (PsProtectionLevel)->Audit = (PsAudit); \
    (PsProtectionLevel)->Type = (PsType); \
    }

/**
 * The PS_PROTECTION structure is used to define the protection level of a process.
 */
typedef struct _PS_PROTECTION
{
    union
    {
        UCHAR Level;
        struct
        {
            UCHAR Type : 3;
            UCHAR Audit : 1;
            UCHAR Signer : 4;
        };
    };
} PS_PROTECTION, * PPS_PROTECTION;

/**
 * The PROCESS_FAULT_INFORMATION structure contains information about process faults.
 */
typedef struct _PROCESS_FAULT_INFORMATION
{
    ULONG FaultFlags;       // Flags that provide additional information about the fault.
    ULONG AdditionalInfo;   // Additional information about the fault.
} PROCESS_FAULT_INFORMATION, * PPROCESS_FAULT_INFORMATION;

/**
 * The PROCESS_TELEMETRY_ID_INFORMATION structure contains telemetry information about a process.
 */
typedef struct _PROCESS_TELEMETRY_ID_INFORMATION
{
    ULONG HeaderSize;                       // The size of the structure, in bytes.
    ULONG ProcessId;                        // The ID of the process.
    ULONG64 ProcessStartKey;                // The start key of the process.
    ULONG64 CreateTime;                     // The creation time of the process.
    ULONG64 CreateInterruptTime;            // The interrupt time at creation.
    ULONG64 CreateUnbiasedInterruptTime;    // The unbiased interrupt time at creation.
    ULONG64 ProcessSequenceNumber;          // The monotonic sequence number of the process.
    ULONG64 SessionCreateTime;              // The session creation time.
    ULONG SessionId;                        // The ID of the session.
    ULONG BootId;                           // The boot ID.
    ULONG ImageChecksum;                    // The checksum of the process image.
    ULONG ImageTimeDateStamp;               // The timestamp of the process image.
    ULONG UserSidOffset;                    // The offset to the user SID.
    ULONG ImagePathOffset;                  // The offset to the image path.
    ULONG PackageNameOffset;                // The offset to the package name.
    ULONG RelativeAppNameOffset;            // The offset to the relative application name.
    ULONG CommandLineOffset;                // The offset to the command line.
} PROCESS_TELEMETRY_ID_INFORMATION, * PPROCESS_TELEMETRY_ID_INFORMATION;
/**
 * The PROCESS_COMMIT_RELEASE_INFORMATION structure contains information about the commit and release of memory for a process.
 */
typedef struct _PROCESS_COMMIT_RELEASE_INFORMATION
{
    ULONG Version;
    struct
    {
        ULONG Eligible : 1;
        ULONG ReleaseRepurposedMemResetCommit : 1;
        ULONG ForceReleaseMemResetCommit : 1;
        ULONG Spare : 29;
    };
    SIZE_T CommitDebt;
    SIZE_T CommittedMemResetSize;
    SIZE_T RepurposedMemResetSize;
} PROCESS_COMMIT_RELEASE_INFORMATION, * PPROCESS_COMMIT_RELEASE_INFORMATION;

/**
 * The PROCESS_JOB_MEMORY_INFO structure contains Represents app memory usage at a single point in time.
 *
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/ns-processthreadsapi-app_memory_information
 */
typedef struct _PROCESS_JOB_MEMORY_INFO
{
    ULONG64 SharedCommitUsage;        // The current shared commit usage, in bytes.
    ULONG64 PrivateCommitUsage;       // The current private commit usage, in bytes.
    ULONG64 PeakPrivateCommitUsage;   // The peak private commit usage, in bytes.
    ULONG64 PrivateCommitLimit;       // The private commit limit, in bytes.
    ULONG64 TotalCommitLimit;         // The total commit limit, in bytes.
} PROCESS_JOB_MEMORY_INFO, * PPROCESS_JOB_MEMORY_INFO;

/**
 * The PROCESS_CHILD_PROCESS_INFORMATION structure contains information about child process policies.
 */
typedef struct _PROCESS_CHILD_PROCESS_INFORMATION
{
    BOOLEAN ProhibitChildProcesses;         // Child processes are prohibited.
    BOOLEAN AlwaysAllowSecureChildProcess;  // Secure child processes are always allowed.
    BOOLEAN AuditProhibitChildProcesses;    // Child processes are audited.
} PROCESS_CHILD_PROCESS_INFORMATION, * PPROCESS_CHILD_PROCESS_INFORMATION;

#ifndef _KERNEL_MODE
//
// Process resource throttling information
//  NtQueryInformationProcess using ProcessPowerThrottlingState
//

#define POWER_THROTTLING_PROCESS_CURRENT_VERSION 1

#define POWER_THROTTLING_PROCESS_EXECUTION_SPEED         0x1
#define POWER_THROTTLING_PROCESS_DELAYTIMERS             0x2
#define POWER_THROTTLING_PROCESS_IGNORE_TIMER_RESOLUTION 0x4

#define POWER_THROTTLING_PROCESS_VALID_FLAGS ((POWER_THROTTLING_PROCESS_EXECUTION_SPEED | \
                                               POWER_THROTTLING_PROCESS_DELAYTIMERS | \
                                               POWER_THROTTLING_PROCESS_IGNORE_TIMER_RESOLUTION))

/**
 * The POWER_THROTTLING_PROCESS_STATE structure is used to manage the power throttling state of a process.
 */
typedef struct _POWER_THROTTLING_PROCESS_STATE
{
    ULONG Version;       // The version of the structure.
    ULONG ControlMask;   // A mask that specifies the control settings for power throttling.
    ULONG StateMask;     // A mask that specifies the current state of power throttling.
} POWER_THROTTLING_PROCESS_STATE, * PPOWER_THROTTLING_PROCESS_STATE;
#endif // !_KERNEL_MODE

// rev (tyranid)
#define WIN32K_SYSCALL_FILTER_STATE_ENABLE 0x1
#define WIN32K_SYSCALL_FILTER_STATE_AUDIT  0x2

typedef struct _WIN32K_SYSCALL_FILTER
{
    ULONG FilterState;
    ULONG FilterSet;
} WIN32K_SYSCALL_FILTER, * PWIN32K_SYSCALL_FILTER;

// private
typedef struct _JOBOBJECT_WAKE_FILTER
{
    ULONG HighEdgeFilter;
    ULONG LowEdgeFilter;
} JOBOBJECT_WAKE_FILTER, * PJOBOBJECT_WAKE_FILTER;

// private
typedef enum _PS_WAKE_REASON
{
    PsWakeReasonUser = 0,
    PsWakeReasonExecutionRequired = 1,
    PsWakeReasonKernel = 2,
    PsWakeReasonInstrumentation = 3,
    PsWakeReasonPreserveProcess = 4,
    PsWakeReasonActivityReference = 5,
    PsWakeReasonWorkOnBehalf = 6,
    PsMaxWakeReasons = 7,
} PS_WAKE_REASON, * PPS_WAKE_REASON;

typedef struct _PROCESS_WAKE_INFORMATION
{
    ULONG64 NotificationChannel;
    ULONG WakeCounters[PsMaxWakeReasons];
    struct _JOBOBJECT_WAKE_FILTER* WakeFilter;
} PROCESS_WAKE_INFORMATION, * PPROCESS_WAKE_INFORMATION;

typedef struct _PROCESS_ENERGY_TRACKING_STATE
{
    ULONG StateUpdateMask;
    ULONG StateDesiredValue;
    ULONG StateSequence;
    ULONG UpdateTag : 1;
    WCHAR Tag[64];
} PROCESS_ENERGY_TRACKING_STATE, * PPROCESS_ENERGY_TRACKING_STATE;

typedef struct _MANAGE_WRITES_TO_EXECUTABLE_MEMORY
{
    ULONG Version : 8;
    ULONG ProcessEnableWriteExceptions : 1;
    ULONG ThreadAllowWrites : 1;
    ULONG Spare : 22;
    PVOID KernelWriteToExecutableSignal; // 19H1
} MANAGE_WRITES_TO_EXECUTABLE_MEMORY, * PMANAGE_WRITES_TO_EXECUTABLE_MEMORY;

#ifndef _KERNEL_MODE
#define POWER_THROTTLING_THREAD_CURRENT_VERSION 1
#define POWER_THROTTLING_THREAD_EXECUTION_SPEED 0x1
#define POWER_THROTTLING_THREAD_VALID_FLAGS (POWER_THROTTLING_THREAD_EXECUTION_SPEED)

/**
 * The POWER_THROTTLING_THREAD_STATE structure contains the throttling policies of a thread subject to power management.
 *
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntddk/ns-ntddk-_power_throttling_thread_state
 */
typedef struct _POWER_THROTTLING_THREAD_STATE
{
    ULONG Version;          // The version of this structure. Set to THREAD_POWER_THROTTLING_CURRENT_VERSION.
    ULONG ControlMask;      // Flags that enable the caller to take control of the power throttling mechanism.
    ULONG StateMask;        // Flags that manage the power throttling mechanism on/off state.
} POWER_THROTTLING_THREAD_STATE, * PPOWER_THROTTLING_THREAD_STATE;

#endif // !_KERNEL_MODE

//
// Process Read/WriteVm Logging
// NtQueryInformationProcess using ProcessEnableReadWriteVmLogging
//
#define PROCESS_READWRITEVM_LOGGING_ENABLE_READVM       0x01
#define PROCESS_READWRITEVM_LOGGING_ENABLE_READVM_V     1UL
#define PROCESS_READWRITEVM_LOGGING_ENABLE_WRITEVM      0x02L
#define PROCESS_READWRITEVM_LOGGING_ENABLE_WRITEVM_V    2UL

#if (WDK_NTDDI_VERSION != NTDDI_WIN10_RS3) && (WDK_NTDDI_VERSION != NTDDI_WIN10_RS4)
typedef union _PROCESS_READWRITEVM_LOGGING_INFORMATION
{
    UCHAR Flags;
    struct
    {
        UCHAR EnableReadVmLogging : 1;
        UCHAR EnableWriteVmLogging : 1;
        UCHAR Unused : 6;
    };
} PROCESS_READWRITEVM_LOGGING_INFORMATION, * PPROCESS_READWRITEVM_LOGGING_INFORMATION;
#endif // (WDK_NTDDI_VERSION != NTDDI_WIN10_RS3) && (WDK_NTDDI_VERSION != NTDDI_WIN10_RS4)

/**
 * The PROCESS_UPTIME_INFORMATION structure contains information about the uptime of a process and diagnostic information.
 */
typedef struct _PROCESS_UPTIME_INFORMATION
{
    ULONGLONG QueryInterruptTime;      // The interrupt time when the query was made.
    ULONGLONG QueryUnbiasedTime;       // The unbiased time when the query was made.
    ULONGLONG EndInterruptTime;        // The interrupt time when the process ended.
    ULONGLONG TimeSinceCreation;       // The total time elapsed since the process was created.
    ULONGLONG Uptime;                  // The total uptime of the process.
    ULONGLONG SuspendedTime;           // The total time the process was in a suspended state.
    struct
    {
        ULONG HangCount : 4;           // The number of times the process was detected as hanging.
        ULONG GhostCount : 4;          // The number of times the process was detected as a ghost process.
        ULONG Crashed : 1;             // Indicates whether the process has crashed (1 if true, 0 otherwise).
        ULONG Terminated : 1;          // Indicates whether the process has been terminated (1 if true, 0 otherwise). 
    };
} PROCESS_UPTIME_INFORMATION, * PPROCESS_UPTIME_INFORMATION;

typedef union _PROCESS_SYSTEM_RESOURCE_MANAGEMENT
{
    ULONG Flags;
    struct
    {
        ULONG Foreground : 1;
        ULONG Reserved : 31;
    };
} PROCESS_SYSTEM_RESOURCE_MANAGEMENT, * PPROCESS_SYSTEM_RESOURCE_MANAGEMENT;

typedef struct _PROCESS_SECURITY_DOMAIN_INFORMATION
{
    ULONGLONG SecurityDomain;
} PROCESS_SECURITY_DOMAIN_INFORMATION, * PPROCESS_SECURITY_DOMAIN_INFORMATION;

typedef struct _PROCESS_COMBINE_SECURITY_DOMAINS_INFORMATION
{
    HANDLE ProcessHandle;
} PROCESS_COMBINE_SECURITY_DOMAINS_INFORMATION, * PPROCESS_COMBINE_SECURITY_DOMAINS_INFORMATION;

typedef union _PROCESS_LOGGING_INFORMATION
{
    ULONG Flags;
    struct
    {
        ULONG EnableReadVmLogging : 1;
        ULONG EnableWriteVmLogging : 1;
        ULONG EnableProcessSuspendResumeLogging : 1;
        ULONG EnableThreadSuspendResumeLogging : 1;
        ULONG EnableLocalExecProtectVmLogging : 1;
        ULONG EnableRemoteExecProtectVmLogging : 1;
        ULONG EnableImpersonationLogging : 1;
        ULONG Reserved : 25;
    };
} PROCESS_LOGGING_INFORMATION, * PPROCESS_LOGGING_INFORMATION;

typedef struct _PROCESS_LEAP_SECOND_INFORMATION
{
    ULONG Flags;
    ULONG Reserved;
} PROCESS_LEAP_SECOND_INFORMATION, * PPROCESS_LEAP_SECOND_INFORMATION;

typedef struct _PROCESS_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION
{
    ULONGLONG ReserveSize;
    ULONGLONG CommitSize;
    ULONG PreferredNode;
    ULONG Reserved;
    PVOID Ssp;
} PROCESS_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION, * PPROCESS_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION;

typedef struct _PROCESS_FREE_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION
{
    PVOID Ssp;
} PROCESS_FREE_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION, * PPROCESS_FREE_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION;

#if !defined(_KERNEL_MODE)
//
// Process Syscall Provider Information
//  NtSetInformationProcess using ProcessSyscallProviderInformation
// PROCESS_VM_WRITE access to the process is needed
// to use this info level.
//
typedef struct _PROCESS_SYSCALL_PROVIDER_INFORMATION
{
    GUID ProviderId;
    UCHAR Level;
} PROCESS_SYSCALL_PROVIDER_INFORMATION, * PPROCESS_SYSCALL_PROVIDER_INFORMATION;
#endif // !defined(_KERNEL_MODE)

//typedef struct _PROCESS_DYNAMIC_ENFORCED_ADDRESS_RANGE
//{
//    ULONG_PTR BaseAddress;
//    SIZE_T Size;
//    ULONG Flags;
//} PROCESS_DYNAMIC_ENFORCED_ADDRESS_RANGE, *PPROCESS_DYNAMIC_ENFORCED_ADDRESS_RANGE;
//
//typedef struct _PROCESS_DYNAMIC_ENFORCED_ADDRESS_RANGES_INFORMATION
//{
//    USHORT NumberOfRanges;
//    USHORT Reserved;
//    ULONG Reserved2;
//    PPROCESS_DYNAMIC_ENFORCED_ADDRESS_RANGE Ranges;
//} PROCESS_DYNAMIC_ENFORCED_ADDRESS_RANGES_INFORMATION, *PPROCESS_DYNAMIC_ENFORCED_ADDRESS_RANGES_INFORMATION;

#ifndef _KERNEL_MODE
/**
 * The PROCESS_MEMBERSHIP_INFORMATION structure contains the Silo identifier of the process.
 *
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntddk/ns-ntddk-process_membership_information
 */
typedef struct _PROCESS_MEMBERSHIP_INFORMATION
{
    ULONG ServerSiloId;
} PROCESS_MEMBERSHIP_INFORMATION, * PPROCESS_MEMBERSHIP_INFORMATION;
#endif // _KERNEL_MODE

typedef struct _PROCESS_TEB_VALUE_INFORMATION
{
    ULONG ThreadId;
    ULONG TebOffset;
    ULONG_PTR Value;
} PROCESS_TEB_VALUE_INFORMATION, * PPROCESS_TEB_VALUE_INFORMATION;

// rev
typedef struct _PROCESS_AVAILABLE_CPUS_INFORMATION
{
    ULONG64 ObservedSequenceNumber;
    ULONG64 SequenceNumber;
    ULONG AvailableCpusCount;
    PKAFFINITY_EX Affinity;
} PROCESS_AVAILABLE_CPUS_INFORMATION, * PPROCESS_AVAILABLE_CPUS_INFORMATION;

/**
 * The NtQueryPortInformationProcess function retrieves the status of the current process exception port.
 *
 * \return LOGICAL If TRUE, the process exception port is valid.
 */
__kernel_entry NTSYSCALLAPI
LOGICAL
NTAPI
NtQueryPortInformationProcess(
    VOID
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
LOGICAL
NTAPI
ZwQueryPortInformationProcess(
    VOID
);

//
// Thread information structures
//

//
// Priority flags
//

#define THREAD_BASE_PRIORITY_LOWRT  15  // value that gets a thread to LowRealtime-1
#define THREAD_BASE_PRIORITY_MAX    2   // maximum thread base priority boost
#define THREAD_BASE_PRIORITY_MIN    (-2)  // minimum thread base priority boost
#define THREAD_BASE_PRIORITY_IDLE   (-15) // value that gets a thread to idle

#define THREAD_PRIORITY_LOWEST          THREAD_BASE_PRIORITY_MIN
#define THREAD_PRIORITY_BELOW_NORMAL    (THREAD_PRIORITY_LOWEST+1)
#define THREAD_PRIORITY_NORMAL          0
#define THREAD_PRIORITY_HIGHEST         THREAD_BASE_PRIORITY_MAX
#define THREAD_PRIORITY_ABOVE_NORMAL    (THREAD_PRIORITY_HIGHEST-1)
#define THREAD_PRIORITY_ERROR_RETURN    (MAXLONG)

#define THREAD_PRIORITY_TIME_CRITICAL   THREAD_BASE_PRIORITY_LOWRT
#define THREAD_PRIORITY_IDLE            THREAD_BASE_PRIORITY_IDLE

/**
 * The THREAD_BASIC_INFORMATION structure contains basic information about the thread.
 */
typedef struct _THREAD_BASIC_INFORMATION
{
    NTSTATUS ExitStatus;        // The exit status of the thread or STATUS_PENDING when the thread has not terminated. (GetExitCodeThread)
    PTEB TebBaseAddress;        // The base address of the memory region containing the TEB structure. (NtCurrentTeb)
    CLIENT_ID ClientId;         // The process and thread identifier of the thread.
    KAFFINITY AffinityMask;     // The affinity mask of the thread. (deprecated) (SetThreadAffinityMask)
    KPRIORITY Priority;
    KPRIORITY BasePriority;
} THREAD_BASIC_INFORMATION, * PTHREAD_BASIC_INFORMATION;

typedef struct _THREAD_LAST_SYSCALL_INFORMATION
{
    PVOID FirstArgument;
    USHORT SystemCallNumber;
#ifdef WIN64
    USHORT Pad[0x3]; // since REDSTONE2
#else
    USHORT Pad[0x1]; // since REDSTONE2
#endif
    ULONG64 WaitTime;
} THREAD_LAST_SYSCALL_INFORMATION, * PTHREAD_LAST_SYSCALL_INFORMATION;

/**
 * The THREAD_CYCLE_TIME_INFORMATION structure contains information about the cycle time of a thread.
 */
typedef struct _THREAD_CYCLE_TIME_INFORMATION
{
    ULONG64 AccumulatedCycles;        // The total number of cycles accumulated by the thread.
    ULONG64 CurrentCycleCount;        // The current cycle count of the thread.
} THREAD_CYCLE_TIME_INFORMATION, * PTHREAD_CYCLE_TIME_INFORMATION;

// RtlAbPostRelease / ReleaseAllUserModeAutoBoostLockHandles 
typedef struct _THREAD_LOCK_OWNERSHIP
{
    ULONG SrwLock[1];
} THREAD_LOCK_OWNERSHIP, * PTHREAD_LOCK_OWNERSHIP;

typedef enum _SCHEDULER_SHARED_DATA_SLOT_ACTION
{
    SchedulerSharedSlotAssign,
    SchedulerSharedSlotFree,
    SchedulerSharedSlotQuery
} SCHEDULER_SHARED_DATA_SLOT_ACTION;

typedef struct _SCHEDULER_SHARED_DATA_SLOT_INFORMATION
{
    SCHEDULER_SHARED_DATA_SLOT_ACTION Action;
    PVOID SchedulerSharedDataHandle;
    PVOID Slot;
} SCHEDULER_SHARED_DATA_SLOT_INFORMATION, * PSCHEDULER_SHARED_DATA_SLOT_INFORMATION;

typedef struct _THREAD_TEB_INFORMATION
{
    _Inout_bytecount_(BytesToRead) PVOID TebInformation; // Buffer to write data into.
    _In_ ULONG TebOffset;                                // Offset in TEB to begin reading from.
    _In_ ULONG BytesToRead;                              // Number of bytes to read.
} THREAD_TEB_INFORMATION, * PTHREAD_TEB_INFORMATION;

// symbols
/**
 * The COUNTER_READING structure is used to store individual counter data from a hardware counter.
 *
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-hardware_counter_data
 */
typedef struct _COUNTER_READING
{
    HARDWARE_COUNTER_TYPE Type;     // Specifies the type of hardware counter data collected.  
    ULONG Index;                    // An identifier for the specific counter.   
    ULONG64 Start;                  // The initial value of the counter when measurement started.   
    ULONG64 Total;                  // The accumulated value of the counter over the measurement period.
} COUNTER_READING, * PCOUNTER_READING;

#ifndef THREAD_PERFORMANCE_DATA_VERSION
#define THREAD_PERFORMANCE_DATA_VERSION 1
#endif

/**
 * The THREAD_PERFORMANCE_DATA structure aggregates various performance metrics for a thread.
 *
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-performance_data
 */
typedef struct _THREAD_PERFORMANCE_DATA
{
    USHORT Size;                                    // The size of the structure.
    USHORT Version;                                 // The version of the structure. Must be set to \ref THREAD_PERFORMANCE_DATA_VERSION.
    PROCESSOR_NUMBER ProcessorNumber;               // The processor number that identifies where the thread is running.
    ULONG ContextSwitches;                          // The number of context switches that occurred from the time profiling was enabled.
    ULONG HwCountersCount;                          // The number of array elements in the HwCounters array that contain hardware counter data.
    ULONG64 UpdateCount;                            // The number of times that the read operation read the data to ensure a consistent snapshot of the data.
    ULONG64 WaitReasonBitMap;                       // A bitmask of \ref KWAIT_REASON that identifies the reasons for the context switches that occurred since the last time the data was read.
    ULONG64 HardwareCounters;                       // A bitmask of hardware counters used to collect counter data.
    COUNTER_READING CycleTime;                      // The cycle time of the thread (excludes the time spent interrupted) from the time profiling was enabled.
    COUNTER_READING HwCounters[MAX_HW_COUNTERS];    // The \ref COUNTER_READING structure that contains hardware counter data.
} THREAD_PERFORMANCE_DATA, * PTHREAD_PERFORMANCE_DATA;

#ifndef THREAD_PROFILING_FLAG_DISPATCH
#define THREAD_PROFILING_FLAG_DISPATCH 0x00000001
#endif

#ifndef THREAD_PROFILING_FLAG_HARDWARE_COUNTERS
#define THREAD_PROFILING_FLAG_HARDWARE_COUNTERS 0x00000002
#endif

/**
 * The THREAD_PROFILING_INFORMATION structure contains profiling information and references to performance data.
 *
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-readthreadprofilingdata
 */
typedef struct _THREAD_PROFILING_INFORMATION
{
    // To receive hardware performance counter data, set this parameter to a bitmask that identifies the hardware counters to collect.
    // You can specify up to 16 performance counters. Each bit relates directly to the zero-based hardware counter index for the hardware
    // performance counters that you configured. Set to zero if you are not collecting hardware counter data.
    // If you set a bit for a hardware counter that has not been configured, the counter value that is read for that counter is zero.
    ULONG64 HardwareCounters;
    // To receive thread profiling data such as context switch count, set this parameter to \ref THREAD_PROFILING_FLAG_DISPATCH.
    ULONG Flags;
    // Enable or disable thread profiling on the specified thread.
    ULONG Enable;
    // The PERFORMANCE_DATA structure that contains thread profiling and hardware counter data.
    PTHREAD_PERFORMANCE_DATA PerformanceData;
} THREAD_PROFILING_INFORMATION, * PTHREAD_PROFILING_INFORMATION;

typedef struct _RTL_UMS_CONTEXT
{
    SINGLE_LIST_ENTRY Link;
    CONTEXT Context;
    PVOID Teb;
    PVOID UserContext;
    volatile ULONG ScheduledThread : 1;
    volatile ULONG Suspended : 1;
    volatile ULONG VolatileContext : 1;
    volatile ULONG Terminated : 1;
    volatile ULONG DebugActive : 1;
    volatile ULONG RunningOnSelfThread : 1;
    volatile ULONG DenyRunningOnSelfThread : 1;
    volatile LONG Flags;
    volatile ULONG64 KernelUpdateLock : 2;
    volatile ULONG64 PrimaryClientID : 62;
    volatile ULONG64 ContextLock;
    struct _RTL_UMS_CONTEXT* PrimaryUmsContext;
    ULONG SwitchCount;
    ULONG KernelYieldCount;
    ULONG MixedYieldCount;
    ULONG YieldCount;
} RTL_UMS_CONTEXT, * PRTL_UMS_CONTEXT;

typedef enum _THREAD_UMS_INFORMATION_COMMAND
{
    UmsInformationCommandInvalid,
    UmsInformationCommandAttach,
    UmsInformationCommandDetach,
    UmsInformationCommandQuery
} THREAD_UMS_INFORMATION_COMMAND;

typedef struct _RTL_UMS_COMPLETION_LIST
{
    PSINGLE_LIST_ENTRY ThreadListHead;
    PVOID CompletionEvent;
    ULONG CompletionFlags;
    SINGLE_LIST_ENTRY InternalListHead;
} RTL_UMS_COMPLETION_LIST, * PRTL_UMS_COMPLETION_LIST;

typedef struct _THREAD_UMS_INFORMATION
{
    THREAD_UMS_INFORMATION_COMMAND Command;
    PRTL_UMS_COMPLETION_LIST CompletionList;
    PRTL_UMS_CONTEXT UmsContext;
    union
    {
        ULONG Flags;
        struct
        {
            ULONG IsUmsSchedulerThread : 1;
            ULONG IsUmsWorkerThread : 1;
            ULONG SpareBits : 30;
        };
    };
} THREAD_UMS_INFORMATION, * PTHREAD_UMS_INFORMATION;

/**
 * The THREAD_NAME_INFORMATION structure assigns a description to a thread.
 *
 * \remarks The handle must have THREAD_SET_LIMITED_INFORMATION access.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-setthreaddescription
 */
typedef struct _THREAD_NAME_INFORMATION
{
    UNICODE_STRING ThreadName;
} THREAD_NAME_INFORMATION, * PTHREAD_NAME_INFORMATION;

typedef struct _ALPC_WORK_ON_BEHALF_TICKET
{
    ULONG ThreadId;
    ULONG ThreadCreationTimeLow;
} ALPC_WORK_ON_BEHALF_TICKET, * PALPC_WORK_ON_BEHALF_TICKET;

typedef struct _RTL_WORK_ON_BEHALF_TICKET_EX
{
    ALPC_WORK_ON_BEHALF_TICKET Ticket;
    union
    {
        ULONG Flags;
        struct
        {
            ULONG CurrentThread : 1;
            ULONG Reserved1 : 31;
        };
    };
    ULONG Reserved2;
} RTL_WORK_ON_BEHALF_TICKET_EX, * PRTL_WORK_ON_BEHALF_TICKET_EX;

#ifndef _KERNEL_MODE
typedef enum _SUBSYSTEM_INFORMATION_TYPE
{
    SubsystemInformationTypeWin32,
    SubsystemInformationTypeWSL,
    MaxSubsystemInformationType
} SUBSYSTEM_INFORMATION_TYPE;
#endif // !_KERNEL_MODE

typedef enum _THREAD_WORKLOAD_CLASS
{
    ThreadWorkloadClassDefault,
    ThreadWorkloadClassGraphics,
    MaxThreadWorkloadClass
} THREAD_WORKLOAD_CLASS;

// private
typedef struct _THREAD_INDEX_INFORMATION
{
    ULONG Index;
    ULONG Sequence;
} THREAD_INDEX_INFORMATION, * PTHREAD_INDEX_INFORMATION;

//
// Processes
//

#ifndef STARTF_HASSHELLDATA
#define STARTF_HASSHELLDATA 0x00000400
#endif

/**
 * Creates a new process.
 *
 * \param ProcessHandle A pointer to a handle that receives the process object handle.
 * \param DesiredAccess The access rights desired for the process object.
 * \param ObjectAttributes Optional. A pointer to an OBJECT_ATTRIBUTES structure that specifies the attributes of the new process.
 * \param ParentProcess A handle to the parent process.
 * \param InheritObjectTable If TRUE, the new process inherits the object table of the parent process.
 * \param SectionHandle Optional. A handle to a section object to be used for the new process.
 * \param DebugPort Optional. A handle to a debug port to be used for the new process.
 * \param TokenHandle Optional. A handle to an access token to be used for the new process.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateProcess(
    _Out_ PHANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ PCOBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ParentProcess,
    _In_ BOOLEAN InheritObjectTable,
    _In_opt_ HANDLE SectionHandle,
    _In_opt_ HANDLE DebugPort,
    _In_opt_ HANDLE ExceptionPort
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateProcess(
    _Out_ PHANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ PCOBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ParentProcess,
    _In_ BOOLEAN InheritObjectTable,
    _In_opt_ HANDLE SectionHandle,
    _In_opt_ HANDLE DebugPort,
    _In_opt_ HANDLE TokenHandle
);

// begin_rev
#define PROCESS_CREATE_FLAGS_NONE                               0x00000000
#define PROCESS_CREATE_FLAGS_BREAKAWAY                          0x00000001 // NtCreateProcessEx & NtCreateUserProcess
#define PROCESS_CREATE_FLAGS_NO_DEBUG_INHERIT                   0x00000002 // NtCreateProcessEx & NtCreateUserProcess
#define PROCESS_CREATE_FLAGS_INHERIT_HANDLES                    0x00000004 // NtCreateProcessEx & NtCreateUserProcess
#define PROCESS_CREATE_FLAGS_OVERRIDE_ADDRESS_SPACE             0x00000008 // NtCreateProcessEx only
#define PROCESS_CREATE_FLAGS_LARGE_PAGES                        0x00000010 // NtCreateProcessEx only (requires SeLockMemoryPrivilege)
#define PROCESS_CREATE_FLAGS_LARGE_PAGE_SYSTEM_DLL              0x00000020 // NtCreateProcessEx only (requires SeLockMemoryPrivilege)
#define PROCESS_CREATE_FLAGS_PROTECTED_PROCESS                  0x00000040 // NtCreateUserProcess only
#define PROCESS_CREATE_FLAGS_CREATE_SESSION                     0x00000080 // NtCreateProcessEx & NtCreateUserProcess (requires SeLoadDriverPrivilege)
#define PROCESS_CREATE_FLAGS_INHERIT_FROM_PARENT                0x00000100 // NtCreateProcessEx & NtCreateUserProcess
#define PROCESS_CREATE_FLAGS_SUSPENDED                          0x00000200 // NtCreateProcessEx & NtCreateUserProcess
#define PROCESS_CREATE_FLAGS_FORCE_BREAKAWAY                    0x00000400 // NtCreateProcessEx & NtCreateUserProcess (requires SeTcbPrivilege)
#define PROCESS_CREATE_FLAGS_MINIMAL_PROCESS                    0x00000800 // NtCreateProcessEx only
#define PROCESS_CREATE_FLAGS_RELEASE_SECTION                    0x00001000 // NtCreateProcessEx & NtCreateUserProcess
#define PROCESS_CREATE_FLAGS_AUXILIARY_PROCESS                  0x00008000 // NtCreateProcessEx & NtCreateUserProcess (requires SeTcbPrivilege)
#define PROCESS_CREATE_FLAGS_CREATE_STORE                       0x00020000 // NtCreateProcessEx & NtCreateUserProcess
#define PROCESS_CREATE_FLAGS_USE_PROTECTED_ENVIRONMENT          0x00040000 // NtCreateProcessEx & NtCreateUserProcess
#define PROCESS_CREATE_FLAGS_IMAGE_EXPANSION_MITIGATION_DISABLE 0x00080000
#define PROCESS_CREATE_FLAGS_PARTITION_CREATE_SLAB_IDENTITY     0x00400000 // NtCreateProcessEx & NtCreateUserProcess (requires SeLockMemoryPrivilege)
// end_rev

/**
 * Creates a new process with extended options.
 *
 * \param ProcessHandle A pointer to a handle that receives the process object handle.
 * \param DesiredAccess The access rights desired for the process object.
 * \param ObjectAttributes Optional. A pointer to an OBJECT_ATTRIBUTES structure that specifies the attributes of the new process.
 * \param ParentProcess A handle to the parent process.
 * \param Flags Flags that control the creation of the process. These flags are defined as PROCESS_CREATE_FLAGS_*.
 * \param SectionHandle Optional. A handle to a section object to be used for the new process.
 * \param DebugPort Optional. A handle to a debug port to be used for the new process.
 * \param TokenHandle Optional. A handle to an access token to be used for the new process.
 * \param Reserved Reserved for future use. Must be zero.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateProcessEx(
    _Out_ PHANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ PCOBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ParentProcess,
    _In_ ULONG Flags, // PROCESS_CREATE_FLAGS_*
    _In_opt_ HANDLE SectionHandle,
    _In_opt_ HANDLE DebugPort,
    _In_opt_ HANDLE TokenHandle,
    _Reserved_ ULONG Reserved // JobMemberLevel
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateProcessEx(
    _Out_ PHANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ PCOBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ParentProcess,
    _In_ ULONG Flags,
    _In_opt_ HANDLE SectionHandle,
    _In_opt_ HANDLE DebugPort,
    _In_opt_ HANDLE ExceptionPort,
    _Reserved_ ULONG Reserved // JobMemberLevel
);

/**
 * Opens an existing process object.
 *
 * \param ProcessHandle A pointer to a handle that receives the process object handle.
 * \param DesiredAccess The access rights desired for the process object.
 * \param ObjectAttributes A pointer to an OBJECT_ATTRIBUTES structure that specifies the attributes of the new process.
 * \param ClientId Optional. A pointer to a CLIENT_ID structure that specifies the client ID of the process to be opened.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntddk/nf-ntddk-ntopenprocess
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenProcess(
    _Out_ PHANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PCLIENT_ID ClientId
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwOpenProcess(
    _Out_ PHANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PCLIENT_ID ClientId
);

/**
 * Terminates the specified process.
 *
 * \param ProcessHandle Optional. A handle to the process to be terminated. If this parameter is NULL, the calling process is terminated.
 * \param ExitStatus The exit status to be used by the process and the process's termination status.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntddk/nf-ntddk-zwterminateprocess
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtTerminateProcess(
    _In_opt_ HANDLE ProcessHandle,
    _In_ NTSTATUS ExitStatus
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwTerminateProcess(
    _In_opt_ HANDLE ProcessHandle,
    _In_ NTSTATUS ExitStatus
);

/**
 * Suspends the specified process.
 *
 * \param ProcessHandle A handle to the process to be suspended.
 * \return NTSTATUS Successful or errant status.
 * \remarks Use NtCreateProcessStateChange instead.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSuspendProcess(
    _In_ HANDLE ProcessHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSuspendProcess(
    _In_ HANDLE ProcessHandle
);

/**
 * Resumes the specified process.
 *
 * \param ProcessHandle A handle to the process to be resumed.
 * \return NTSTATUS Successful or errant status.
 * \remarks Use NtCreateProcessStateChange instead.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtResumeProcess(
    _In_ HANDLE ProcessHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwResumeProcess(
    _In_ HANDLE ProcessHandle
);

#ifndef _KERNEL_MODE
#define NtCurrentProcess()      ((HANDLE)(LONG_PTR)-1)
#define ZwCurrentProcess()      NtCurrentProcess()

#define NtCurrentThread()       ((HANDLE)(LONG_PTR)-2)
#define ZwCurrentThread()       NtCurrentThread()

#define NtCurrentSession()      ((HANDLE)(LONG_PTR)-3)
#define ZwCurrentSession()      NtCurrentSession()

#define ZwCurrentTeb()          NtCurrentTeb()

#define NtCurrentPeb()          (NtCurrentTeb()->ProcessEnvironmentBlock)
#define ZwCurrentPeb()          NtCurrentPeb()

// Not NT, but useful.
#define NtCurrentProcessId()    (NtCurrentTeb()->ClientId.UniqueProcess)
#define ZwCurrentProcessId()    NtCurrentProcessId()
#define NtCurrentThreadId()     (NtCurrentTeb()->ClientId.UniqueThread)
#define ZwCurrentThreadId()     NtCurrentThreadId()
#define NtCurrentSessionId()    RtlGetActiveConsoleId() // USER_SHARED_DATA->ActiveConsoleId
#define ZwCurrentSessionId()    NtCurrentSessionId()
#define NtCurrentLogonId()      (NtCurrentPeb()->LogonId)
#define ZwCurrentLogonId()      NtCurrentLogonId()

#else // ifdef _KERNEL_MODE

#define NtCurrentProcessId()    PsGetCurrentProcessId()
#define ZwCurrentProcessId()    NtCurrentProcessId()
#define NtCurrentThreadId()     PsGetCurrentThreadId()
#define ZwCurrentThreadId()     NtCurrentThreadId()
#define NtCurrentSessionId()    PsGetCurrentProcessSessionId()
#define ZwCurrentSessionId()    NtCurrentSessionId()

#endif // _KERNEL_MODE

// Windows 8 and above
#define NtCurrentProcessToken()         ((HANDLE)(LONG_PTR)-4) // NtOpenProcessToken(NtCurrentProcess())
#define NtCurrentThreadToken()          ((HANDLE)(LONG_PTR)-5) // NtOpenThreadToken(NtCurrentThread())
#define NtCurrentThreadEffectiveToken() ((HANDLE)(LONG_PTR)-6) // NtOpenThreadToken(NtCurrentThread()) + NtOpenProcessToken(NtCurrentProcess())

#define NtCurrentSilo() ( (HANDLE)(LONG_PTR) -1 )

/**
 * Retrieves information about the specified process.
 *
 * \param ProcessHandle A handle to the process.
 * \param ProcessInformationClass The type of process information to be retrieved.
 * \param ProcessInformation A pointer to a buffer that receives the process information.
 * \param ProcessInformationLength The size of the buffer pointed to by the ProcessInformation parameter.
 * \param ReturnLength An optional pointer to a variable that receives the size of the data returned.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryInformationProcess(
    _In_ HANDLE ProcessHandle,
    _In_ PROCESSINFOCLASS ProcessInformationClass,
    _Out_writes_bytes_(ProcessInformationLength) PVOID ProcessInformation,
    _In_ ULONG ProcessInformationLength,
    _Out_opt_ PULONG ReturnLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwQueryInformationProcess(
    _In_ HANDLE ProcessHandle,
    _In_ PROCESSINFOCLASS ProcessInformationClass,
    _Out_writes_bytes_(ProcessInformationLength) PVOID ProcessInformation,
    _In_ ULONG ProcessInformationLength,
    _Out_opt_ PULONG ReturnLength
);

// rev
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtWow64QueryInformationProcess64(
    _In_ HANDLE ProcessHandle,
    _In_ PROCESSINFOCLASS ProcessInformationClass,
    _Out_writes_bytes_(ProcessInformationLength) PVOID ProcessInformation,
    _In_ ULONG ProcessInformationLength,
    _Out_opt_ PULONG ReturnLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwWow64QueryInformationProcess64(
    _In_ HANDLE ProcessHandle,
    _In_ PROCESSINFOCLASS ProcessInformationClass,
    _Out_writes_bytes_(ProcessInformationLength) PVOID ProcessInformation,
    _In_ ULONG ProcessInformationLength,
    _Out_opt_ PULONG ReturnLength
);

/**
 * Sets information for the specified process.
 *
 * \param ProcessHandle A handle to the process.
 * \param ProcessInformationClass The type of process information to be set.
 * \param ProcessInformation A pointer to a buffer that contains the process information.
 * \param ProcessInformationLength The size of the buffer pointed to by the ProcessInformation parameter.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationProcess(
    _In_ HANDLE ProcessHandle,
    _In_ PROCESSINFOCLASS ProcessInformationClass,
    _In_reads_bytes_(ProcessInformationLength) PVOID ProcessInformation,
    _In_ ULONG ProcessInformationLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSetInformationProcess(
    _In_ HANDLE ProcessHandle,
    _In_ PROCESSINFOCLASS ProcessInformationClass,
    _In_reads_bytes_(ProcessInformationLength) PVOID ProcessInformation,
    _In_ ULONG ProcessInformationLength
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtWow64SetInformationProcess64(
    _In_ HANDLE ProcessHandle,
    _In_ PROCESSINFOCLASS ProcessInformationClass,
    _In_reads_bytes_(ProcessInformationLength) PVOID ProcessInformation,
    _In_ ULONG ProcessInformationLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwWow64SetInformationProcess64(
    _In_ HANDLE ProcessHandle,
    _In_ PROCESSINFOCLASS ProcessInformationClass,
    _In_reads_bytes_(ProcessInformationLength) PVOID ProcessInformation,
    _In_ ULONG ProcessInformationLength
);

#if (NTDDI_VERSION >= NTDDI_WS03)
#define PROCESS_GET_NEXT_FLAGS_PREVIOUS_PROCESS 0x00000001

/**
 * Retrieves a handle to the next process in the system.
 *
 * \param ProcessHandle An optional handle to the a process. If this parameter is NULL, the function retrieves the first process in the system.
 * \param DesiredAccess The access rights desired for the new process handle.
 * \param HandleAttributes The attributes for the new process handle.
 * \param Flags Flags that modify the behavior of the function. This can be a combination of the following flags:
 * - \ref PROCESS_GET_NEXT_FLAGS_PREVIOUS_PROCESS (0x00000001): Retrieve the previous process in the system.
 * \param NewProcessHandle A pointer to a variable that receives the handle to the next process.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtGetNextProcess(
    _In_opt_ HANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Flags,
    _Out_ PHANDLE NewProcessHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwGetNextProcess(
    _In_opt_ HANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Flags,
    _Out_ PHANDLE NewProcessHandle
);
#endif

/**
 * Retrieves a handle to the next thread in the system.
 *
 * \param ProcessHandle A handle to the process for enumerateration of threads.
 * \param ThreadHandle An optional handle to a thread. If this parameter is NULL, the function retrieves the first thread in the process.
 * \param DesiredAccess The access rights desired for the new thread handle.
 * \param HandleAttributes The attributes for the new thread handle.
 * \param Flags Flags that modify the behavior of the function. This can be a combination of the following flags:
 * - \ref THREAD_GET_NEXT_FLAGS_PREVIOUS_THREAD (0x00000001): Retrieve the previous thread in the process.
 * \param NewThreadHandle A pointer to a variable that receives the handle to the next thread.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtGetNextThread(
    _In_ HANDLE ProcessHandle,
    _In_opt_ HANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Flags,
    _Out_ PHANDLE NewThreadHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwGetNextThread(
    _In_ HANDLE ProcessHandle,
    _In_opt_ HANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Flags,
    _Out_ PHANDLE NewThreadHandle
);

#define STATECHANGE_SET_ATTRIBUTES 0x0001

typedef enum _PROCESS_STATE_CHANGE_TYPE
{
    ProcessStateChangeSuspend,
    ProcessStateChangeResume,
    ProcessStateChangeMax,
} PROCESS_STATE_CHANGE_TYPE, * PPROCESS_STATE_CHANGE_TYPE;

#if (NTDDI_VERSION >= NTDDI_WIN10_CO)

/**
 * Creates a state change handle for changing the suspension state of a process.
 *
 * \param ProcessStateChangeHandle A pointer to a variable that receives the handle.
 * \param DesiredAccess The access rights desired for the handle.
 * \param ObjectAttributes Optional attributes for the handle.
 * \param ProcessHandle A handle to the process.
 * \param Reserved Reserved for future use.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateProcessStateChange(
    _Out_ PHANDLE ProcessStateChangeHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ PCOBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ProcessHandle,
    _In_opt_ _Reserved_ ULONG Reserved
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateProcessStateChange(
    _Out_ PHANDLE ProcessStateChangeHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ PCOBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ProcessHandle,
    _In_opt_ _Reserved_ ULONG Reserved
);


/**
 * Changes the suspension state of a process.
 *
 * \param ProcessStateChangeHandle A handle to the process state change object.
 * \param ProcessHandle A handle to the process.
 * \param StateChangeType The type of state change.
 * \param ExtendedInformation Optional extended information.
 * \param ExtendedInformationLength The length of the extended information.
 * \param Reserved Reserved for future use.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtChangeProcessState(
    _In_ HANDLE ProcessStateChangeHandle,
    _In_ HANDLE ProcessHandle,
    _In_ PROCESS_STATE_CHANGE_TYPE StateChangeType,
    _In_opt_ _Reserved_ PVOID ExtendedInformation,
    _In_opt_ _Reserved_ SIZE_T ExtendedInformationLength,
    _In_opt_ _Reserved_ ULONG Reserved
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwChangeProcessState(
    _In_ HANDLE ProcessStateChangeHandle,
    _In_ HANDLE ProcessHandle,
    _In_ PROCESS_STATE_CHANGE_TYPE StateChangeType,
    _In_opt_ PVOID ExtendedInformation,
    _In_opt_ SIZE_T ExtendedInformationLength,
    _In_opt_ _Reserved_ ULONG Reserved
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_CO)
/**
 * Creates a state change handle for changing the suspension state of a process.
 *
 * \param ThreadStateChangeHandle A pointer to a variable that receives the handle.
 * \param DesiredAccess The access rights desired for the handle.
 * \param ObjectAttributes Optional attributes for the handle.
 * \param ThreadHandle A handle to the thread.
 * \param Reserved Reserved for future use.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateThreadStateChange(
    _Out_ PHANDLE ThreadStateChangeHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ PCOBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ThreadHandle,
    _In_opt_ _Reserved_ ULONG Reserved
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateThreadStateChange(
    _Out_ PHANDLE ThreadStateChangeHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ PCOBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ThreadHandle,
    _In_opt_ _Reserved_ ULONG Reserved
);

typedef enum _THREAD_STATE_CHANGE_TYPE
{
    ThreadStateChangeSuspend,
    ThreadStateChangeResume,
    ThreadStateChangeMax,
} THREAD_STATE_CHANGE_TYPE, * PTHREAD_STATE_CHANGE_TYPE;

/**
 * Changes the suspension state of a thread.
 *
 * \param ThreadStateChangeHandle A handle to the thread state change object.
 * \param ThreadHandle A handle to the thread.
 * \param StateChangeType The type of state change.
 * \param ExtendedInformation Optional extended information.
 * \param ExtendedInformationLength The length of the extended information.
 * \param Reserved Reserved for future use.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtChangeThreadState(
    _In_ HANDLE ThreadStateChangeHandle,
    _In_ HANDLE ThreadHandle,
    _In_ THREAD_STATE_CHANGE_TYPE StateChangeType,
    _In_opt_ PVOID ExtendedInformation,
    _In_opt_ SIZE_T ExtendedInformationLength,
    _In_opt_ _Reserved_ ULONG Reserved
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwChangeThreadState(
    _In_ HANDLE ThreadStateChangeHandle,
    _In_ HANDLE ThreadHandle,
    _In_ THREAD_STATE_CHANGE_TYPE StateChangeType,
    _In_opt_ PVOID ExtendedInformation,
    _In_opt_ SIZE_T ExtendedInformationLength,
    _In_opt_ _Reserved_ ULONG Reserved
);
#endif

// Process KeepAlive (also WakeCounter)

typedef enum _PROCESS_ACTIVITY_TYPE
{
    ProcessActivityTypeAudio = 0,
    ProcessActivityTypeMax = 1
} PROCESS_ACTIVITY_TYPE;

// rev
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAcquireProcessActivityReference(
    _Out_ PHANDLE ActivityReferenceHandle,
    _In_ HANDLE ParentProcessHandle,
    _In_ PROCESS_ACTIVITY_TYPE Reserved
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAcquireProcessActivityReference(
    _Out_ PHANDLE ActivityReferenceHandle,
    _In_ HANDLE ParentProcessHandle,
    _In_ PROCESS_ACTIVITY_TYPE Reserved
);

//
// Threads
//

/**
 * Creates a new thread in the specified process.
 *
 * \param ThreadHandle A pointer to a handle that receives the thread object handle.
 * \param DesiredAccess The access rights desired for the thread object.
 * \param ObjectAttributes Optional. A pointer to an OBJECT_ATTRIBUTES structure that specifies the attributes of the new thread.
 * \param ProcessHandle A handle to the process in which the thread is to be created.
 * \param ClientId A pointer to a CLIENT_ID structure that receives the client ID of the new thread.
 * \param ThreadContext A pointer to a CONTEXT structure that specifies the initial context of the new thread.
 * \param InitialTeb A pointer to an INITIAL_TEB structure that specifies the initial stack limits of the new thread.
 * \param CreateSuspended If TRUE, the thread is created in a suspended state.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateThread(
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ PCOBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ProcessHandle,
    _Out_ PCLIENT_ID ClientId,
    _In_ PCONTEXT ThreadContext,
    _In_ PINITIAL_TEB InitialTeb,
    _In_ BOOLEAN CreateSuspended
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateThread(
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ PCOBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ProcessHandle,
    _Out_ PCLIENT_ID ClientId,
    _In_ PCONTEXT ThreadContext,
    _In_ PINITIAL_TEB InitialTeb,
    _In_ BOOLEAN CreateSuspended
);

/**
 * Opens an existing thread object.
 *
 * \param ThreadHandle A pointer to a handle that receives the thread object handle.
 * \param DesiredAccess The access rights desired for the thread object.
 * \param ObjectAttributes Optional. A pointer to an OBJECT_ATTRIBUTES structure that specifies the attributes of the new thread.
 * \param ClientId Optional. A pointer to a CLIENT_ID structure that specifies the client ID of the thread to be opened.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenThread(
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PCLIENT_ID ClientId
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwOpenThread(
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PCLIENT_ID ClientId
);


/**
 * Terminates the specified thread.
 *
 * \param ThreadHandle Optional. A handle to the thread to be terminated. If this parameter is NULL, the calling thread is terminated.
 * \param ExitStatus The exit status to be used by the thread and the thread's termination status.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtTerminateThread(
    _In_opt_ HANDLE ThreadHandle,
    _In_ NTSTATUS ExitStatus
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwTerminateThread(
    _In_opt_ HANDLE ThreadHandle,
    _In_ NTSTATUS ExitStatus
);

/**
 * Suspends the specified thread.
 *
 * \param ThreadHandle A handle to the thread to be suspended.
 * \param PreviousSuspendCount Optional. A pointer to a variable that receives the thread's previous suspend count.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSuspendThread(
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PULONG PreviousSuspendCount
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSuspendThread(
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PULONG PreviousSuspendCount
);

/**
 * Resumes the specified thread.
 *
 * \param ThreadHandle A handle to the thread to be resumed.
 * \param PreviousSuspendCount Optional. A pointer to a variable that receives the thread's previous suspend count.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtResumeThread(
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PULONG PreviousSuspendCount
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwResumeThread(
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PULONG PreviousSuspendCount
);

/**
 * Retrieves the number of the current processor.
 *
 * \return ULONG The number of the current processor.
 * \sa https://learn.microsoft.com/en-us/windows/win32/procthread/ntgetcurrentprocessornumber
 */
__kernel_entry NTSYSCALLAPI
ULONG
NTAPI
NtGetCurrentProcessorNumber(
    VOID
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
ULONG
NTAPI
ZwGetCurrentProcessorNumber(
    VOID
);

#if (NTDDI_VERSION >= NTDDI_WIN10)
/**
 * Retrieves the number of the current processor.
 *
 * \param ProcessorNumber An optional pointer to a PROCESSOR_NUMBER structure that receives the processor number.
 * \return ULONG The number of the current processor.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntddk/nf-ntddk-kegetcurrentprocessornumberex
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtGetCurrentProcessorNumberEx(
    _Out_opt_ PPROCESSOR_NUMBER ProcessorNumber
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwGetCurrentProcessorNumberEx(
    _Out_opt_ PPROCESSOR_NUMBER ProcessorNumber
);
#endif // NTDDI_VERSION >= NTDDI_WIN10

/**
 * Retrieves the context of the specified thread.
 *
 * \param ThreadHandle A handle to the thread.
 * \param ThreadContext A pointer to a CONTEXT structure that receives the thread context.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtGetContextThread(
    _In_ HANDLE ThreadHandle,
    _Inout_ PCONTEXT ThreadContext
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwGetContextThread(
    _In_ HANDLE ThreadHandle,
    _Inout_ PCONTEXT ThreadContext
);

/**
 * Sets the context of the specified thread.
 *
 * \param ThreadHandle A handle to the thread.
 * \param ThreadContext A pointer to a CONTEXT structure that specifies the thread context.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetContextThread(
    _In_ HANDLE ThreadHandle,
    _In_ PCONTEXT ThreadContext
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSetContextThread(
    _In_ HANDLE ThreadHandle,
    _In_ PCONTEXT ThreadContext
);

/**
 * Retrieves information about the specified thread.
 *
 * \param ThreadHandle A handle to the thread.
 * \param ThreadInformationClass The type of thread information to be retrieved.
 * \param ThreadInformation A pointer to a buffer that receives the thread information.
 * \param ThreadInformationLength The size of the buffer pointed to by the ThreadInformation parameter.
 * \param ReturnLength An optional pointer to a variable that receives the size of the data returned.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryInformationThread(
    _In_ HANDLE ThreadHandle,
    _In_ THREADINFOCLASS ThreadInformationClass,
    _Out_writes_bytes_(ThreadInformationLength) PVOID ThreadInformation,
    _In_ ULONG ThreadInformationLength,
    _Out_opt_ PULONG ReturnLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwQueryInformationThread(
    _In_ HANDLE ThreadHandle,
    _In_ THREADINFOCLASS ThreadInformationClass,
    _Out_writes_bytes_(ThreadInformationLength) PVOID ThreadInformation,
    _In_ ULONG ThreadInformationLength,
    _Out_opt_ PULONG ReturnLength
);

#pragma warning(suppress: 28252 28253)
/**
 * Sets information for the specified thread.
 *
 * \param ThreadHandle A handle to the thread.
 * \param ThreadInformationClass The type of thread information to be set.
 * \param ThreadInformation A pointer to a buffer that contains the thread information.
 * \param ThreadInformationLength The size of the buffer pointed to by the ThreadInformation parameter.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationThread(
    _In_ HANDLE ThreadHandle,
    _In_ THREADINFOCLASS ThreadInformationClass,
    _When_((ThreadInformationClass != ThreadManageWritesToExecutableMemory),
        _In_reads_bytes_(ThreadInformationLength))
    _When_((ThreadInformationClass == ThreadManageWritesToExecutableMemory),
        _Inout_updates_(ThreadInformationLength))
    PVOID ThreadInformation,
    _In_ ULONG ThreadInformationLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSetInformationThread(
    _In_ HANDLE ThreadHandle,
    _In_ THREADINFOCLASS ThreadInformationClass,
    _In_reads_bytes_(ThreadInformationLength) PVOID ThreadInformation,
    _In_ ULONG ThreadInformationLength
);

/**
 * Sends an alert to the specified thread.
 *
 * \param ThreadHandle A handle to the thread to be alerted.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlertThread(
    _In_ HANDLE ThreadHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAlertThread(
    _In_ HANDLE ThreadHandle
);

/**
 * Resumes a thread that was previously suspended and sends an alert to it.
 *
 * \param ThreadHandle A handle to the thread to be resumed and alerted.
 * \param PreviousSuspendCount An optional pointer to a variable that receives the thread's previous suspend count.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlertResumeThread(
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PULONG PreviousSuspendCount
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAlertResumeThread(
    _In_ HANDLE ThreadHandle,
    _Out_opt_ PULONG PreviousSuspendCount
);

/**
 * Tests whether the current thread has an alert pending.
 *
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtTestAlert(
    VOID
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwTestAlert(
    VOID
);

#if (NTDDI_VERSION >= NTDDI_WIN8)
// rev
/**
 * Sends an alert to the specified thread.
 *
 * \param ThreadId The thread ID of the thread to be alerted.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlertThreadByThreadId(
    _In_ HANDLE ThreadId
);

// rev
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAlertThreadByThreadId(
    _In_ HANDLE ThreadId
);
#endif


#if (NTDDI_VERSION >= NTDDI_WIN11)
/**
 * Sends an alert to the specified thread by its thread ID, with an optional lock.
 *
 * \param ThreadId The thread ID of the thread to be alerted.
 * \param Lock An optional pointer to an SRW lock to be used during the alert.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlertThreadByThreadIdEx(
    _In_ HANDLE ThreadId,
    _In_opt_ PRTL_SRWLOCK Lock
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAlertThreadByThreadIdEx(
    _In_ HANDLE ThreadId,
    _In_opt_ PRTL_SRWLOCK Lock
);

/**
 * Sends an alert to multiple threads by their thread IDs.
 *
 * \param MultipleThreadId A pointer to an array of thread IDs to be alerted.
 * \param Count The number of thread IDs in the array.
 * \param Boost A pointer to a boost value to be applied to the threads.
 * \param BoostCount The number of boost values in the array.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAlertMultipleThreadByThreadId(
    _In_ PHANDLE MultipleThreadId,
    _In_ ULONG Count,
    _In_ PVOID Boost,
    _In_ ULONG BoostCount
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAlertMultipleThreadByThreadId(
    _In_ PHANDLE MultipleThreadId,
    _In_ ULONG Count,
    _In_ PVOID Boost,
    _In_ ULONG BoostCount
);
#endif


#if (NTDDI_VERSION >= NTDDI_WIN8)
// rev
/**
 * Waits for an alert to be delivered to the specified thread.
 *
 * \param Address The address to wait for an alert on.
 * \param Timeout The timeout value for waiting, or NULL for no timeout.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtWaitForAlertByThreadId(
    _In_opt_ PVOID Address,
    _In_opt_ PLARGE_INTEGER Timeout
);

// rev
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwWaitForAlertByThreadId(
    _In_opt_ PVOID Address,
    _In_opt_ PLARGE_INTEGER Timeout
);
#endif

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtContinue(
    _In_ PCONTEXT ContextRecord,
    _In_ BOOLEAN TestAlert
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwContinue(
    _In_ PCONTEXT ContextRecord,
    _In_ BOOLEAN TestAlert
);

typedef enum _KCONTINUE_TYPE
{
    KCONTINUE_UNWIND,
    KCONTINUE_RESUME,
    KCONTINUE_LONGJUMP,
    KCONTINUE_SET,
    KCONTINUE_LAST,
} KCONTINUE_TYPE;

typedef struct _KCONTINUE_ARGUMENT
{
    KCONTINUE_TYPE ContinueType;
    ULONG ContinueFlags;
    ULONGLONG Reserved[2];
} KCONTINUE_ARGUMENT, * PKCONTINUE_ARGUMENT;

#define KCONTINUE_FLAG_TEST_ALERT  0x00000001 // wbenny
#define KCONTINUE_FLAG_DELIVER_APC 0x00000002 // wbenny

#if (NTDDI_VERSION >= NTDDI_WIN10_VB)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtContinueEx(
    _In_ PCONTEXT ContextRecord,
    _In_ PVOID ContinueArgument // PKCONTINUE_ARGUMENT and BOOLEAN are valid
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwContinueEx(
    _In_ PCONTEXT ContextRecord,
    _In_ PVOID ContinueArgument // PKCONTINUE_ARGUMENT and BOOLEAN are valid
);
#endif // NTDDI_VERSION >= NTDDI_WIN10_VB

//FORCEINLINE
//NTSTATUS
//NtContinue(
//    _In_ PCONTEXT ContextRecord,
//    _In_ BOOLEAN TestAlert
//    )
//{
//    return NtContinueEx(ContextRecord, (PCONTINUE_ARGUMENT)TestAlert);
//}

//FORCEINLINE
//NTSTATUS
//ZwContinue(
//    _In_ PCONTEXT ContextRecord,
//    _In_ BOOLEAN TestAlert
//    )
//{
//    return ZwContinueEx(ContextRecord, (PCONTINUE_ARGUMENT)TestAlert);
//}

/**
 * Impersonates a client thread.
 *
 * \param ServerThreadHandle A handle to the server thread.
 * \param ClientThreadHandle A handle to the client thread.
 * \param SecurityQos A pointer to a SECURITY_QUALITY_OF_SERVICE structure that specifies the impersonation level and context tracking mode.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtImpersonateThread(
    _In_ HANDLE ServerThreadHandle,
    _In_ HANDLE ClientThreadHandle,
    _In_ PSECURITY_QUALITY_OF_SERVICE SecurityQos
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwImpersonateThread(
    _In_ HANDLE ServerThreadHandle,
    _In_ HANDLE ClientThreadHandle,
    _In_ PSECURITY_QUALITY_OF_SERVICE SecurityQos
);

/**
 * Registers a thread termination port.
 *
 * \param PortHandle A handle to the port to be registered.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtRegisterThreadTerminatePort(
    _In_ HANDLE PortHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwRegisterThreadTerminatePort(
    _In_ HANDLE PortHandle
);

/**
 * Sets LDT (Local Descriptor Table) entries.
 *
 * \param Selector0 The first selector.
 * \param Entry0Low The low part of the first entry.
 * \param Entry0Hi The high part of the first entry.
 * \param Selector1 The second selector.
 * \param Entry1Low The low part of the second entry.
 * \param Entry1Hi The high part of the second entry.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetLdtEntries(
    _In_ ULONG Selector0,
    _In_ ULONG Entry0Low,
    _In_ ULONG Entry0Hi,
    _In_ ULONG Selector1,
    _In_ ULONG Entry1Low,
    _In_ ULONG Entry1Hi
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSetLdtEntries(
    _In_ ULONG Selector0,
    _In_ ULONG Entry0Low,
    _In_ ULONG Entry0Hi,
    _In_ ULONG Selector1,
    _In_ ULONG Entry1Low,
    _In_ ULONG Entry1Hi
);

#ifndef _KERNEL_MODE
/**
 * Dispatches the Asynchronous Procedure Call (APC) from the NtQueueApc* functions to the specified routine.
 *
 * \param ApcRoutine A pointer to the APC routine to be executed.
 * \param Parameter Optional. A pointer to a parameter to be passed to the APC routine.
 * \param ActxContext Optional. A handle to an activation context.
 */
NTSYSAPI
VOID
NTAPI
RtlDispatchAPC(
    _In_ PAPCFUNC ApcRoutine,
    _In_opt_ PVOID Parameter,
    _In_opt_ HANDLE ActxContext
);
#endif

/**
 * A pointer to a function that serves as an APC routine.
 *
 * \param ApcArgument1 Optional. A pointer to the first argument to be passed to the APC routine.
 * \param ApcArgument2 Optional. A pointer to the second argument to be passed to the APC routine.
 * \param ApcArgument3 Optional. A pointer to the third argument to be passed to the APC routine.
 */

typedef _Function_class_(PS_APC_ROUTINE)
VOID NTAPI PS_APC_ROUTINE(
    _In_opt_ PVOID ApcArgument1,
    _In_opt_ PVOID ApcArgument2,
    _In_opt_ PVOID ApcArgument3
);
typedef PS_APC_ROUTINE* PPS_APC_ROUTINE;

/**
 * Encodes an APC routine pointer for use in a WOW64 environment.
 *
 * \param ApcRoutine The APC routine pointer to be encoded.
 * \return PVOID The encoded APC routine pointer.
 */
inline
PVOID Wow64EncodeApcRoutine(_In_ PVOID ApcRoutine)
{
    if (ApcRoutine <= (PVOID)(SIZE_T)0xFFFFFFFF) {
        ApcRoutine = (PVOID)(-((LONG_PTR)ApcRoutine << 2));
    }
    return ApcRoutine;
}

/**
 * Decodes an APC routine pointer that was encoded for use in a WOW64 environment.
 * 
 * \param ApcRoutine The encoded APC routine pointer to be decoded.
 * \return PVOID The decoded APC routine pointer.
 */
inline
PVOID Wow64DecodeApcRoutine(_In_ PVOID ApcRoutine)
{
    PVOID DecodedApcRoutine = (PVOID)((-(LONG_PTR)ApcRoutine) >> 2);
    if (DecodedApcRoutine > (PVOID)(SIZE_T)0xFFFFFFFF) {
        DecodedApcRoutine = ApcRoutine;
    }
    return DecodedApcRoutine;
}

/**
 * Queues an APC (Asynchronous Procedure Call) to a thread.
 *
 * \param ThreadHandle Handle to the thread to which the APC is to be queued.
 * \param ApcRoutine A pointer to the RtlDispatchAPC function or custom APC routine to be executed.
 * \param ApcArgument1 Optional first argument to be passed to the APC routine.
 * \param ApcArgument2 Optional second argument to be passed to the APC routine.
 * \param ApcArgument3 Optional third argument to be passed to the APC routine.
 * \return NTSTATUS Successful or errant status.
 * \remarks The APC will be executed in the context of the specified thread when the thread enters an alertable wait state or when any
 * process calls the NtTestAlert, NtAlertThread, NtAlertResumeThread or NtAlertThreadByThreadId functions.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueueApcThread(
    _In_ HANDLE ThreadHandle,
    _In_ PPS_APC_ROUTINE ApcRoutine, // RtlDispatchAPC
    _In_opt_ PVOID ApcArgument1,
    _In_opt_ PVOID ApcArgument2,
    _In_opt_ PVOID ApcArgument3
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwQueueApcThread(
    _In_ HANDLE ThreadHandle,
    _In_ PPS_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcArgument1,
    _In_opt_ PVOID ApcArgument2,
    _In_opt_ PVOID ApcArgument3
);

/**
 * A special handle value used to queue a user APC (Asynchronous Procedure Call).
 */
#define QUEUE_USER_APC_SPECIAL_USER_APC ((HANDLE)0x1)

/**
 * Queues an APC (Asynchronous Procedure Call) to a thread.
 *
 * \param ThreadHandle Handle to the thread to which the APC is to be queued.
 * \param ReserveHandle Optional handle to a reserve object. This can be QUEUE_USER_APC_SPECIAL_USER_APC or a handle returned by NtAllocateReserveObject.
 * \param ApcRoutine A pointer to the RtlDispatchAPC function or custom APC routine to be executed.
 * \param ApcArgument1 Optional first argument to be passed to the APC routine.
 * \param ApcArgument2 Optional second argument to be passed to the APC routine.
 * \param ApcArgument3 Optional third argument to be passed to the APC routine.
 * \return NTSTATUS Successful or errant status.
 * \remarks The APC will be executed in the context of the specified thread after the thread enters an alertable wait state or immediately
 * when QUEUE_USER_APC_SPECIAL_USER_APC is used or NtTestAlert, NtAlertThread, NtAlertResumeThread or NtAlertThreadByThreadId are called.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueueApcThreadEx(
    _In_ HANDLE ThreadHandle,
    _In_opt_ HANDLE ReserveHandle, // NtAllocateReserveObject // QUEUE_USER_APC_SPECIAL_USER_APC
    _In_ PPS_APC_ROUTINE ApcRoutine, // RtlDispatchAPC
    _In_opt_ PVOID ApcArgument1,
    _In_opt_ PVOID ApcArgument2,
    _In_opt_ PVOID ApcArgument3
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwQueueApcThreadEx(
    _In_ HANDLE ThreadHandle,
    _In_opt_ HANDLE ReserveHandle, // NtAllocateReserveObject // SPECIAL_USER_APC
    _In_ PPS_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcArgument1,
    _In_opt_ PVOID ApcArgument2,
    _In_opt_ PVOID ApcArgument3
);


#if (NTDDI_VERSION >= NTDDI_WIN10_MN)
/**
 * The APC_CALLBACK_DATA_CONTEXT structure is used to pass information to the APC callback routine.
 */
typedef struct _APC_CALLBACK_DATA_CONTEXT
{
    ULONG_PTR Parameter;
    PCONTEXT ContextRecord;
    ULONG_PTR Reserved0;
    ULONG_PTR Reserved1;
} APC_CALLBACK_DATA_CONTEXT, * PAPC_CALLBACK_DATA_CONTEXT;

#if defined(_KERNEL_MODE) && !defined(_WINDOWS_)
typedef enum _QUEUE_USER_APC_FLAGS
{
    QUEUE_USER_APC_FLAGS_NONE = 0x00000000,
    QUEUE_USER_APC_FLAGS_SPECIAL_USER_APC = 0x00000001,

    //
    // Used for requesting additional callback data.
    //

    QUEUE_USER_APC_CALLBACK_DATA_CONTEXT = 0x00010000,
} QUEUE_USER_APC_FLAGS;
#endif // !_KERNEL_MODE

/**
 * Queues an Asynchronous Procedure Call (APC) to a specified thread.
 *
 * \param ThreadHandle A handle to the thread to which the APC is to be queued.
 * \param ReserveHandle An optional handle to a reserve object. This can be obtained using NtAllocateReserveObject.
 * \param ApcFlags Flags that control the behavior of the APC. These flags are defined in QUEUE_USER_APC_FLAGS.
 * \param ApcRoutine A pointer to the RtlDispatchAPC function or custom APC routine to be executed.
 * \param ApcArgument1 An optional argument to be passed to the APC routine.
 * \param ApcArgument2 An optional argument to be passed to the APC routine.
 * \param ApcArgument3 An optional argument to be passed to the APC routine.
 * \return NTSTATUS Successful or errant status.
 * \remarks The APC will be executed in the context of the specified thread when the thread enters an alertable wait state or immediately
 * when QUEUE_USER_APC_SPECIAL_USER_APC is used or any process calls the NtTestAlert, NtAlertThread,
 * NtAlertResumeThread or NtAlertThreadByThreadId functions.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueueApcThreadEx2(
    _In_ HANDLE ThreadHandle,
    _In_opt_ HANDLE ReserveHandle, // NtAllocateReserveObject
    _In_ ULONG ApcFlags, // QUEUE_USER_APC_FLAGS
    _In_ PPS_APC_ROUTINE ApcRoutine, // RtlDispatchAPC
    _In_opt_ PVOID ApcArgument1,
    _In_opt_ PVOID ApcArgument2,
    _In_opt_ PVOID ApcArgument3
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwQueueApcThreadEx2(
    _In_ HANDLE ThreadHandle,
    _In_opt_ HANDLE ReserveHandle, // NtAllocateReserveObject
    _In_ QUEUE_USER_APC_FLAGS ApcFlags,
    _In_ PPS_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcArgument1,
    _In_opt_ PVOID ApcArgument2,
    _In_opt_ PVOID ApcArgument3
);
#endif // (NTDDI_VERSION >= NTDDI_WIN10_MN)


//
// User processes and threads
//

//
// Attributes
//

// private
#define PS_ATTRIBUTE_NUMBER_MASK    0x0000ffff
#define PS_ATTRIBUTE_THREAD         0x00010000 // may be used with thread creation
#define PS_ATTRIBUTE_INPUT          0x00020000 // input only
#define PS_ATTRIBUTE_ADDITIVE       0x00040000 // "accumulated" e.g. bitmasks, counters, etc.

#if defined(_KERNEL_MODE) && !defined(_WINDOWS_)
typedef enum _PROC_THREAD_ATTRIBUTE_NUM {
    ProcThreadAttributeParentProcess                = 0,
    ProcThreadAttributeExtendedFlags                = 1,
    ProcThreadAttributeHandleList                   = 2,
    ProcThreadAttributeGroupAffinity                = 3,
    ProcThreadAttributePreferredNode                = 4,
    ProcThreadAttributeIdealProcessor               = 5,
    ProcThreadAttributeUmsThread                    = 6,
    ProcThreadAttributeMitigationPolicy             = 7,
    ProcThreadAttributePackageFullName              = 8,
    ProcThreadAttributeSecurityCapabilities         = 9,
    ProcThreadAttributeConsoleReference             = 10,
    ProcThreadAttributeProtectionLevel              = 11,
    ProcThreadAttributeOsMaxVersionTested           = 12,
    ProcThreadAttributeJobList                      = 13,
    ProcThreadAttributeChildProcessPolicy           = 14,
    ProcThreadAttributeAllApplicationPackagesPolicy = 15,
    ProcThreadAttributeWin32kFilter                 = 16,
    ProcThreadAttributeSafeOpenPromptOriginClaim    = 17,
    ProcThreadAttributeDesktopAppPolicy             = 18,
    ProcThreadAttributeBnoIsolation                 = 19,
    ProcThreadAttributePseudoConsole                = 22,
    ProcThreadAttributeIsolationManifest            = 23,
    ProcThreadAttributeMitigationAuditPolicy        = 24,
    ProcThreadAttributeMachineType                  = 25,
    ProcThreadAttributeComponentFilter              = 26,
    ProcThreadAttributeEnableOptionalXStateFeatures = 27,
    ProcThreadAttributeCreateStore                  = 28,
    ProcThreadAttributeTrustedApp                   = 29,
    ProcThreadAttributeSveVectorLength              = 30,
} PROC_THREAD_ATTRIBUTE_NUM;
#else // _KERNEL_MODE
// PROC_THREAD_ATTRIBUTE_NUM (Win32 CreateProcess) (dmex)
#define ProcThreadAttributeParentProcess                ((_PROC_THREAD_ATTRIBUTE_NUM)0 ) // in HANDLE
#define ProcThreadAttributeExtendedFlags                ((_PROC_THREAD_ATTRIBUTE_NUM)1 ) // in ULONG (EXTENDED_PROCESS_CREATION_FLAG_*)
#define ProcThreadAttributeHandleList                   ((_PROC_THREAD_ATTRIBUTE_NUM)2 ) // in HANDLE[]
#define ProcThreadAttributeGroupAffinity                ((_PROC_THREAD_ATTRIBUTE_NUM)3 ) // in GROUP_AFFINITY // since WIN7
#define ProcThreadAttributePreferredNode                ((_PROC_THREAD_ATTRIBUTE_NUM)4 ) // in USHORT
#define ProcThreadAttributeIdealProcessor               ((_PROC_THREAD_ATTRIBUTE_NUM)5 ) // in PROCESSOR_NUMBER
#define ProcThreadAttributeUmsThread                    ((_PROC_THREAD_ATTRIBUTE_NUM)6 ) // in UMS_CREATE_THREAD_ATTRIBUTES
#define ProcThreadAttributeMitigationPolicy             ((_PROC_THREAD_ATTRIBUTE_NUM)7 ) // in ULONG, ULONG64 or ULONG64[2]
#define ProcThreadAttributePackageFullName              ((_PROC_THREAD_ATTRIBUTE_NUM)8 ) // in WCHAR[] // since WIN8
#define ProcThreadAttributeSecurityCapabilities         ((_PROC_THREAD_ATTRIBUTE_NUM)9 ) // in SECURITY_CAPABILITIES
#define ProcThreadAttributeConsoleReference             ((_PROC_THREAD_ATTRIBUTE_NUM)10) // BaseGetConsoleReference (kernelbase.dll)
#define ProcThreadAttributeProtectionLevel              ((_PROC_THREAD_ATTRIBUTE_NUM)11) // in ULONG (PROTECTION_LEVEL_*) // since WINBLUE
#define ProcThreadAttributeOsMaxVersionTested           ((_PROC_THREAD_ATTRIBUTE_NUM)12) // in MAXVERSIONTESTED_INFO // since THRESHOLD // (from exe.manifest)
#define ProcThreadAttributeJobList                      ((_PROC_THREAD_ATTRIBUTE_NUM)13) // in HANDLE[] // since WIN10
#define ProcThreadAttributeChildProcessPolicy           ((_PROC_THREAD_ATTRIBUTE_NUM)14) // in ULONG
#define ProcThreadAttributeAllApplicationPackagesPolicy ((_PROC_THREAD_ATTRIBUTE_NUM)15) // in ULONG
#define ProcThreadAttributeWin32kFilter                 ((_PROC_THREAD_ATTRIBUTE_NUM)16) // in PROC_THREAD_WIN32KFILTER_ATTRIBUTE
#define ProcThreadAttributeSafeOpenPromptOriginClaim    ((_PROC_THREAD_ATTRIBUTE_NUM)17) // since RS1
#define ProcThreadAttributeDesktopAppPolicy             ((_PROC_THREAD_ATTRIBUTE_NUM)18) // in ULONG // since RS2
#define ProcThreadAttributeBnoIsolation                 ((_PROC_THREAD_ATTRIBUTE_NUM)19) // in PROC_THREAD_BNOISOLATION_ATTRIBUTE
#define ProcThreadAttributePseudoConsole                ((_PROC_THREAD_ATTRIBUTE_NUM)22) // in HANDLE (HPCON) // since RS5
#define ProcThreadAttributeIsolationManifest            ((_PROC_THREAD_ATTRIBUTE_NUM)23) // in ISOLATION_MANIFEST_PROPERTIES // rev (diversenok) // since 19H2+
#define ProcThreadAttributeMitigationAuditPolicy        ((_PROC_THREAD_ATTRIBUTE_NUM)24) // in ULONG, ULONG64, or ULONG64[2] // since 21H1
#define ProcThreadAttributeMachineType                  ((_PROC_THREAD_ATTRIBUTE_NUM)25) // in USHORT // since 21H2
#define ProcThreadAttributeComponentFilter              ((_PROC_THREAD_ATTRIBUTE_NUM)26) // in ULONG
#define ProcThreadAttributeEnableOptionalXStateFeatures ((_PROC_THREAD_ATTRIBUTE_NUM)27) // in ULONG64 // since WIN11
#define ProcThreadAttributeCreateStore                  ((_PROC_THREAD_ATTRIBUTE_NUM)28) // ULONG // rev (diversenok)
#define ProcThreadAttributeTrustedApp                   ((_PROC_THREAD_ATTRIBUTE_NUM)29)
#define ProcThreadAttributeSveVectorLength              ((_PROC_THREAD_ATTRIBUTE_NUM)30)
#endif // !_KERNEL_MODE

#ifndef ProcThreadAttributeValue
#define ProcThreadAttributeValue(Number, Thread, Input, Additive) \
    (((Number) & PROC_THREAD_ATTRIBUTE_NUMBER) | \
     ((Thread != FALSE) ? PROC_THREAD_ATTRIBUTE_THREAD : 0) | \
     ((Input != FALSE) ? PROC_THREAD_ATTRIBUTE_INPUT : 0) | \
     ((Additive != FALSE) ? PROC_THREAD_ATTRIBUTE_ADDITIVE : 0))
#endif

#ifndef PROC_THREAD_ATTRIBUTE_PARENT_PROCESS
#define PROC_THREAD_ATTRIBUTE_PARENT_PROCESS \
    ProcThreadAttributeValue (ProcThreadAttributeParentProcess, FALSE, TRUE, FALSE)
#endif
#ifndef PROC_THREAD_ATTRIBUTE_EXTENDED_FLAGS
#define PROC_THREAD_ATTRIBUTE_EXTENDED_FLAGS \
    ProcThreadAttributeValue (ProcThreadAttributeExtendedFlags, FALSE, TRUE, TRUE)
#endif
#ifndef PROC_THREAD_ATTRIBUTE_PACKAGE_FULL_NAME
#define PROC_THREAD_ATTRIBUTE_PACKAGE_FULL_NAME \
    ProcThreadAttributeValue(ProcThreadAttributePackageFullName, FALSE, TRUE, FALSE)
#endif
#ifndef PROC_THREAD_ATTRIBUTE_HANDLE_LIST
#define PROC_THREAD_ATTRIBUTE_HANDLE_LIST \
    ProcThreadAttributeValue (ProcThreadAttributeHandleList, FALSE, TRUE, FALSE)
#endif
#ifndef PROC_THREAD_ATTRIBUTE_GROUP_AFFINITY
#define PROC_THREAD_ATTRIBUTE_GROUP_AFFINITY \
    ProcThreadAttributeValue (ProcThreadAttributeGroupAffinity, TRUE, TRUE, FALSE)
#endif
#ifndef PROC_THREAD_ATTRIBUTE_PREFERRED_NODE
#define PROC_THREAD_ATTRIBUTE_PREFERRED_NODE \
    ProcThreadAttributeValue (ProcThreadAttributePreferredNode, FALSE, TRUE, FALSE)
#endif
#ifndef PROC_THREAD_ATTRIBUTE_IDEAL_PROCESSOR
#define PROC_THREAD_ATTRIBUTE_IDEAL_PROCESSOR \
    ProcThreadAttributeValue (ProcThreadAttributeIdealProcessor, TRUE, TRUE, FALSE)
#endif
#ifndef PROC_THREAD_ATTRIBUTE_UMS_THREAD
#define PROC_THREAD_ATTRIBUTE_UMS_THREAD \
    ProcThreadAttributeValue (ProcThreadAttributeUmsThread, TRUE, TRUE, FALSE)
#endif
#ifndef PROC_THREAD_ATTRIBUTE_MITIGATION_POLICY
#define PROC_THREAD_ATTRIBUTE_MITIGATION_POLICY \
    ProcThreadAttributeValue (ProcThreadAttributeMitigationPolicy, FALSE, TRUE, FALSE)
#endif
#ifndef PROC_THREAD_ATTRIBUTE_SECURITY_CAPABILITIES
#define PROC_THREAD_ATTRIBUTE_SECURITY_CAPABILITIES \
    ProcThreadAttributeValue (ProcThreadAttributeSecurityCapabilities, FALSE, TRUE, FALSE)
#endif
#ifndef PROC_THREAD_ATTRIBUTE_CONSOLE_REFERENCE
#define PROC_THREAD_ATTRIBUTE_CONSOLE_REFERENCE \
    ProcThreadAttributeValue (ProcThreadAttributeConsoleReference, FALSE, TRUE, FALSE)
#endif
#ifndef PROC_THREAD_ATTRIBUTE_OSMAXVERSIONTESTED
#define PROC_THREAD_ATTRIBUTE_OSMAXVERSIONTESTED \
    ProcThreadAttributeValue(ProcThreadAttributeOsMaxVersionTested, FALSE, TRUE, FALSE)
#endif
#ifndef PROC_THREAD_ATTRIBUTE_PROTECTION_LEVEL
#define PROC_THREAD_ATTRIBUTE_PROTECTION_LEVEL \
    ProcThreadAttributeValue (ProcThreadAttributeProtectionLevel, FALSE, TRUE, FALSE)
#endif
#ifndef PROC_THREAD_ATTRIBUTE_SAFE_OPEN_PROMPT_ORIGIN_CLAIM
#define PROC_THREAD_ATTRIBUTE_SAFE_OPEN_PROMPT_ORIGIN_CLAIM \
    ProcThreadAttributeValue (ProcThreadAttributeSafeOpenPromptOriginClaim, FALSE, TRUE, FALSE)
#endif
#ifndef PROC_THREAD_ATTRIBUTE_BNO_ISOLATION
#define PROC_THREAD_ATTRIBUTE_BNO_ISOLATION \
    ProcThreadAttributeValue (ProcThreadAttributeBnoIsolation, FALSE, TRUE, FALSE)
#endif
#ifndef PROC_THREAD_ATTRIBUTE_ISOLATION_MANIFEST
#define PROC_THREAD_ATTRIBUTE_ISOLATION_MANIFEST \
    ProcThreadAttributeValue(ProcThreadAttributeIsolationManifest, FALSE, TRUE, FALSE)
#endif
#ifndef PROC_THREAD_ATTRIBUTE_PSEUDOCONSOLE
#define PROC_THREAD_ATTRIBUTE_PSEUDOCONSOLE \
    ProcThreadAttributeValue (ProcThreadAttributePseudoConsole, FALSE, TRUE, FALSE)
#endif
#ifndef PROC_THREAD_ATTRIBUTE_MACHINE_TYPE
#define PROC_THREAD_ATTRIBUTE_MACHINE_TYPE \
    ProcThreadAttributeValue (ProcThreadAttributeMachineType, FALSE, TRUE, FALSE)
#endif
#ifndef PROC_THREAD_ATTRIBUTE_ENABLE_OPTIONAL_XSTATE_FEATURES
#define PROC_THREAD_ATTRIBUTE_ENABLE_OPTIONAL_XSTATE_FEATURES \
    ProcThreadAttributeValue (ProcThreadAttributeEnableOptionalXStateFeatures, TRUE, TRUE, FALSE)
#endif
#ifndef PROC_THREAD_ATTRIBUTE_CREATE_STORE
#define PROC_THREAD_ATTRIBUTE_CREATE_STORE \
    ProcThreadAttributeValue(ProcThreadAttributeCreateStore, FALSE, TRUE, FALSE)
#endif
#ifndef PROC_THREAD_ATTRIBUTE_TRUSTED_APP
#define PROC_THREAD_ATTRIBUTE_TRUSTED_APP \
    ProcThreadAttributeValue(ProcThreadAttributeTrustedApp, FALSE, TRUE, FALSE)
#endif

// private
typedef struct _PROC_THREAD_ATTRIBUTE
{
    ULONG_PTR Attribute;
    SIZE_T Size;
    ULONG_PTR Value;
} PROC_THREAD_ATTRIBUTE, * PPROC_THREAD_ATTRIBUTE;

/**
 * The PROC_THREAD_ATTRIBUTE_LIST structure contains the list of attributes for process and thread creation.
 */
typedef struct _PROC_THREAD_ATTRIBUTE_LIST
{
    ULONG PresentFlags;             // A bitmask of flags that indicate the attributes for process and thread creation.
    ULONG AttributeCount;           // The number of attributes in the list.
    ULONG LastAttribute;            // The index of the last attribute in the list.
    ULONG SpareUlong0;              // Reserved for future use.
    PPROC_THREAD_ATTRIBUTE ExtendedFlagsAttribute; // A pointer to the extended flags attribute.
    _Field_size_(AttributeCount) PROC_THREAD_ATTRIBUTE Attributes[1]; // An array of attributes.
} PROC_THREAD_ATTRIBUTE_LIST, * PPROC_THREAD_ATTRIBUTE_LIST;

// private
#define EXTENDED_PROCESS_CREATION_FLAG_ELEVATION_HANDLED 0x00000001
#define EXTENDED_PROCESS_CREATION_FLAG_FORCELUA 0x00000002
#define EXTENDED_PROCESS_CREATION_FLAG_FORCE_BREAKAWAY 0x00000004 // requires SeTcbPrivilege // since WINBLUE

#define PROTECTION_LEVEL_WINTCB_LIGHT       0x00000000
#define PROTECTION_LEVEL_WINDOWS            0x00000001
#define PROTECTION_LEVEL_WINDOWS_LIGHT      0x00000002
#define PROTECTION_LEVEL_ANTIMALWARE_LIGHT  0x00000003
#define PROTECTION_LEVEL_LSA_LIGHT          0x00000004
#define PROTECTION_LEVEL_WINTCB             0x00000005
#define PROTECTION_LEVEL_CODEGEN_LIGHT      0x00000006
#define PROTECTION_LEVEL_AUTHENTICODE       0x00000007
#define PROTECTION_LEVEL_PPL_APP            0x00000008

#define PROTECTION_LEVEL_SAME               0xFFFFFFFF
#define PROTECTION_LEVEL_NONE               0xFFFFFFFE

// private
typedef enum _SE_SAFE_OPEN_PROMPT_EXPERIENCE_RESULTS
{
    SeSafeOpenExperienceNone = 0x00,
    SeSafeOpenExperienceCalled = 0x01,
    SeSafeOpenExperienceAppRepCalled = 0x02,
    SeSafeOpenExperiencePromptDisplayed = 0x04,
    SeSafeOpenExperienceUAC = 0x08,
    SeSafeOpenExperienceUninstaller = 0x10,
    SeSafeOpenExperienceIgnoreUnknownOrBad = 0x20,
    SeSafeOpenExperienceDefenderTrustedInstaller = 0x40,
    SeSafeOpenExperienceMOTWPresent = 0x80,
    SeSafeOpenExperienceElevatedNoPropagation = 0x100
} SE_SAFE_OPEN_PROMPT_EXPERIENCE_RESULTS;

// private
typedef struct _SE_SAFE_OPEN_PROMPT_RESULTS
{
    SE_SAFE_OPEN_PROMPT_EXPERIENCE_RESULTS Results;
    WCHAR Path[MAX_PATH];
} SE_SAFE_OPEN_PROMPT_RESULTS, * PSE_SAFE_OPEN_PROMPT_RESULTS;

typedef struct _PROC_THREAD_BNOISOLATION_ATTRIBUTE
{
    BOOL IsolationEnabled;
    WCHAR IsolationPrefix[0x88];
} PROC_THREAD_BNOISOLATION_ATTRIBUTE, * PPROC_THREAD_BNOISOLATION_ATTRIBUTE;

// private
typedef struct _ISOLATION_MANIFEST_PROPERTIES
{
    UNICODE_STRING InstancePath;
    UNICODE_STRING FriendlyName;
    UNICODE_STRING Description;
    ULONG_PTR Level;
} ISOLATION_MANIFEST_PROPERTIES, * PISOLATION_MANIFEST_PROPERTIES;

#define WIN32KFILTER_FLAG_ENABLE    0x1
#define WIN32KFILTER_FLAG_AUDIT     0x2

typedef struct _PROC_THREAD_WIN32KFILTER_ATTRIBUTE
{
    ULONG Flags;
    ULONG FilterLevel;
} PROC_THREAD_WIN32KFILTER_ATTRIBUTE, * PPROC_THREAD_WIN32KFILTER_ATTRIBUTE;

// private
typedef enum _PS_ATTRIBUTE_NUM
{
    PsAttributeParentProcess,                   // in HANDLE
    PsAttributeDebugObject,                     // in HANDLE
    PsAttributeToken,                           // in HANDLE
    PsAttributeClientId,                        // out PCLIENT_ID
    PsAttributeTebAddress,                      // out PTEB *
    PsAttributeImageName,                       // in PWSTR
    PsAttributeImageInfo,                       // out PSECTION_IMAGE_INFORMATION
    PsAttributeMemoryReserve,                   // in PPS_MEMORY_RESERVE
    PsAttributePriorityClass,                   // in UCHAR
    PsAttributeErrorMode,                       // in ULONG
    PsAttributeStdHandleInfo,                   // 10, in PPS_STD_HANDLE_INFO // 10
    PsAttributeHandleList,                      // in HANDLE[]
    PsAttributeGroupAffinity,                   // in PGROUP_AFFINITY
    PsAttributePreferredNode,                   // in PUSHORT
    PsAttributeIdealProcessor,                  // in PPROCESSOR_NUMBER
    PsAttributeUmsThread,                       // in PUMS_CREATE_THREAD_ATTRIBUTES
    PsAttributeMitigationOptions,               // in PPS_MITIGATION_OPTIONS_MAP (PROCESS_CREATION_MITIGATION_POLICY_*) // since WIN8
    PsAttributeProtectionLevel,                 // in PS_PROTECTION // since WINBLUE
    PsAttributeSecureProcess,                   // in PPS_TRUSTLET_CREATE_ATTRIBUTES, since THRESHOLD
    PsAttributeJobList,                         // in HANDLE[]
    PsAttributeChildProcessPolicy,              // in PULONG (PROCESS_CREATION_CHILD_PROCESS_*) // since THRESHOLD2 // 20
    PsAttributeAllApplicationPackagesPolicy,    // in PULONG (PROCESS_CREATION_ALL_APPLICATION_PACKAGES_*) // since REDSTONE
    PsAttributeWin32kFilter,                    // in PWIN32K_SYSCALL_FILTER
    PsAttributeSafeOpenPromptOriginClaim,       // in SE_SAFE_OPEN_PROMPT_RESULTS
    PsAttributeBnoIsolation,                    // in PPS_BNO_ISOLATION_PARAMETERS // since REDSTONE2
    PsAttributeDesktopAppPolicy,                // in PULONG (PROCESS_CREATION_DESKTOP_APP_*)
    PsAttributeChpe,                            // in BOOLEAN // since REDSTONE3
    PsAttributeMitigationAuditOptions,          // in PPS_MITIGATION_AUDIT_OPTIONS_MAP (PROCESS_CREATION_MITIGATION_AUDIT_POLICY_*) // since 21H1
    PsAttributeMachineType,                     // in USHORT // since 21H2
    PsAttributeComponentFilter,                 // in COMPONENT_FILTER
    PsAttributeEnableOptionalXStateFeatures,    // in ULONG64 // since WIN11 // 30
    PsAttributeSupportedMachines,               // in ULONG // since 24H2
    PsAttributeSveVectorLength,                 // PPS_PROCESS_CREATION_SVE_VECTOR_LENGTH
    PsAttributeMax
} PS_ATTRIBUTE_NUM;

// private
#define PS_ATTRIBUTE_NUMBER_MASK    0x0000ffff
#define PS_ATTRIBUTE_THREAD         0x00010000 // may be used with thread creation
#define PS_ATTRIBUTE_INPUT          0x00020000 // input only
#define PS_ATTRIBUTE_ADDITIVE       0x00040000 // "accumulated" e.g. bitmasks, counters, etc.

// begin_rev

#define PsAttributeValue(Number, Thread, Input, Additive) \
    (((Number) & PS_ATTRIBUTE_NUMBER_MASK) | \
    ((Thread) ? PS_ATTRIBUTE_THREAD : 0) | \
    ((Input) ? PS_ATTRIBUTE_INPUT : 0) | \
    ((Additive) ? PS_ATTRIBUTE_ADDITIVE : 0))

#define PS_ATTRIBUTE_PARENT_PROCESS \
    PsAttributeValue(PsAttributeParentProcess, FALSE, TRUE, TRUE)
#define PS_ATTRIBUTE_DEBUG_OBJECT \
    PsAttributeValue(PsAttributeDebugObject, FALSE, TRUE, TRUE)
#define PS_ATTRIBUTE_TOKEN \
    PsAttributeValue(PsAttributeToken, FALSE, TRUE, TRUE)
#define PS_ATTRIBUTE_CLIENT_ID \
    PsAttributeValue(PsAttributeClientId, TRUE, FALSE, FALSE)
#define PS_ATTRIBUTE_TEB_ADDRESS \
    PsAttributeValue(PsAttributeTebAddress, TRUE, FALSE, FALSE)
#define PS_ATTRIBUTE_IMAGE_NAME \
    PsAttributeValue(PsAttributeImageName, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_IMAGE_INFO \
    PsAttributeValue(PsAttributeImageInfo, FALSE, FALSE, FALSE)
#define PS_ATTRIBUTE_MEMORY_RESERVE \
    PsAttributeValue(PsAttributeMemoryReserve, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_PRIORITY_CLASS \
    PsAttributeValue(PsAttributePriorityClass, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_ERROR_MODE \
    PsAttributeValue(PsAttributeErrorMode, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_STD_HANDLE_INFO \
    PsAttributeValue(PsAttributeStdHandleInfo, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_HANDLE_LIST \
    PsAttributeValue(PsAttributeHandleList, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_GROUP_AFFINITY \
    PsAttributeValue(PsAttributeGroupAffinity, TRUE, TRUE, FALSE)
#define PS_ATTRIBUTE_PREFERRED_NODE \
    PsAttributeValue(PsAttributePreferredNode, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_IDEAL_PROCESSOR \
    PsAttributeValue(PsAttributeIdealProcessor, TRUE, TRUE, FALSE)
#define PS_ATTRIBUTE_UMS_THREAD \
    PsAttributeValue(PsAttributeUmsThread, TRUE, TRUE, FALSE)
#define PS_ATTRIBUTE_MITIGATION_OPTIONS \
    PsAttributeValue(PsAttributeMitigationOptions, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_PROTECTION_LEVEL \
    PsAttributeValue(PsAttributeProtectionLevel, FALSE, TRUE, TRUE)
#define PS_ATTRIBUTE_SECURE_PROCESS \
    PsAttributeValue(PsAttributeSecureProcess, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_JOB_LIST \
    PsAttributeValue(PsAttributeJobList, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_CHILD_PROCESS_POLICY \
    PsAttributeValue(PsAttributeChildProcessPolicy, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_ALL_APPLICATION_PACKAGES_POLICY \
    PsAttributeValue(PsAttributeAllApplicationPackagesPolicy, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_WIN32K_FILTER \
    PsAttributeValue(PsAttributeWin32kFilter, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_SAFE_OPEN_PROMPT_ORIGIN_CLAIM \
    PsAttributeValue(PsAttributeSafeOpenPromptOriginClaim, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_BNO_ISOLATION \
    PsAttributeValue(PsAttributeBnoIsolation, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_DESKTOP_APP_POLICY \
    PsAttributeValue(PsAttributeDesktopAppPolicy, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_CHPE \
    PsAttributeValue(PsAttributeChpe, FALSE, TRUE, TRUE)
#define PS_ATTRIBUTE_MITIGATION_AUDIT_OPTIONS \
    PsAttributeValue(PsAttributeMitigationAuditOptions, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_MACHINE_TYPE \
    PsAttributeValue(PsAttributeMachineType, FALSE, TRUE, TRUE)
#define PS_ATTRIBUTE_COMPONENT_FILTER \
    PsAttributeValue(PsAttributeComponentFilter, FALSE, TRUE, FALSE)
#define PS_ATTRIBUTE_ENABLE_OPTIONAL_XSTATE_FEATURES \
    PsAttributeValue(PsAttributeEnableOptionalXStateFeatures, TRUE, TRUE, FALSE)

// end_rev

// begin_private

typedef struct _PS_ATTRIBUTE
{
    ULONG_PTR Attribute;
    SIZE_T Size;
    union
    {
        ULONG_PTR Value;
        PVOID ValuePtr;
    };
    PSIZE_T ReturnLength;
} PS_ATTRIBUTE, * PPS_ATTRIBUTE;

typedef struct _PS_ATTRIBUTE_LIST
{
    SIZE_T TotalLength;
    PS_ATTRIBUTE Attributes[1];
} PS_ATTRIBUTE_LIST, * PPS_ATTRIBUTE_LIST;

typedef struct _PS_MEMORY_RESERVE
{
    PVOID ReserveAddress;
    SIZE_T ReserveSize;
} PS_MEMORY_RESERVE, * PPS_MEMORY_RESERVE;

typedef enum _PS_STD_HANDLE_STATE
{
    PsNeverDuplicate,
    PsRequestDuplicate, // duplicate standard handles specified by PseudoHandleMask, and only if StdHandleSubsystemType matches the image subsystem
    PsAlwaysDuplicate, // always duplicate standard handles
    PsMaxStdHandleStates
} PS_STD_HANDLE_STATE;

// begin_rev
#define PS_STD_INPUT_HANDLE  0x1
#define PS_STD_OUTPUT_HANDLE 0x2
#define PS_STD_ERROR_HANDLE  0x4
// end_rev

typedef struct _PS_STD_HANDLE_INFO
{
    union
    {
        ULONG Flags;
        struct
        {
            ULONG StdHandleState : 2; // PS_STD_HANDLE_STATE
            ULONG PseudoHandleMask : 3; // PS_STD_*
        };
    };
    ULONG StdHandleSubsystemType;
} PS_STD_HANDLE_INFO, * PPS_STD_HANDLE_INFO;

typedef union _PS_TRUSTLET_ATTRIBUTE_ACCESSRIGHTS
{
    UCHAR Trustlet : 1;
    UCHAR Ntos : 1;
    UCHAR WriteHandle : 1;
    UCHAR ReadHandle : 1;
    UCHAR Reserved : 4;
    UCHAR AccessRights;
} PS_TRUSTLET_ATTRIBUTE_ACCESSRIGHTS, * PPS_TRUSTLET_ATTRIBUTE_ACCESSRIGHTS;

typedef union _PS_TRUSTLET_ATTRIBUTE_TYPE
{
    ULONG AttributeType;
    struct
    {
        UCHAR Version;
        UCHAR DataCount;
        UCHAR SemanticType;
        PS_TRUSTLET_ATTRIBUTE_ACCESSRIGHTS AccessRights;
    } DUMMYSTRUCTNAME;
} PS_TRUSTLET_ATTRIBUTE_TYPE, * PPS_TRUSTLET_ATTRIBUTE_TYPE;

typedef struct _PS_TRUSTLET_ATTRIBUTE_HEADER
{
    PS_TRUSTLET_ATTRIBUTE_TYPE AttributeType;
    ULONG InstanceNumber : 8;
    ULONG Reserved : 24;
} PS_TRUSTLET_ATTRIBUTE_HEADER, * PPS_TRUSTLET_ATTRIBUTE_HEADER;

typedef struct _PS_TRUSTLET_ATTRIBUTE_DATA
{
    PS_TRUSTLET_ATTRIBUTE_HEADER Header;
    ULONGLONG Data[1];
} PS_TRUSTLET_ATTRIBUTE_DATA, * PPS_TRUSTLET_ATTRIBUTE_DATA;

typedef struct _PS_TRUSTLET_CREATE_ATTRIBUTES
{
    ULONGLONG TrustletIdentity;
    PS_TRUSTLET_ATTRIBUTE_DATA Attributes[1];
} PS_TRUSTLET_CREATE_ATTRIBUTES, * PPS_TRUSTLET_CREATE_ATTRIBUTES;

// private
typedef struct _PS_BNO_ISOLATION_PARAMETERS
{
    UNICODE_STRING IsolationPrefix;
    ULONG HandleCount;
    PVOID* Handles;
    BOOLEAN IsolationEnabled;
} PS_BNO_ISOLATION_PARAMETERS, * PPS_BNO_ISOLATION_PARAMETERS;

// private
typedef union _PS_PROCESS_CREATION_SVE_VECTOR_LENGTH
{
    ULONG VectorLength : 24;
    ULONG FlagsReserved : 8;
} PS_PROCESS_CREATION_SVE_VECTOR_LENGTH, * PPS_PROCESS_CREATION_SVE_VECTOR_LENGTH;

// private
typedef enum _PS_MITIGATION_OPTION
{
    PS_MITIGATION_OPTION_NX,
    PS_MITIGATION_OPTION_SEHOP,
    PS_MITIGATION_OPTION_FORCE_RELOCATE_IMAGES,
    PS_MITIGATION_OPTION_HEAP_TERMINATE,
    PS_MITIGATION_OPTION_BOTTOM_UP_ASLR,
    PS_MITIGATION_OPTION_HIGH_ENTROPY_ASLR,
    PS_MITIGATION_OPTION_STRICT_HANDLE_CHECKS,
    PS_MITIGATION_OPTION_WIN32K_SYSTEM_CALL_DISABLE,
    PS_MITIGATION_OPTION_EXTENSION_POINT_DISABLE,
    PS_MITIGATION_OPTION_PROHIBIT_DYNAMIC_CODE,
    PS_MITIGATION_OPTION_CONTROL_FLOW_GUARD,
    PS_MITIGATION_OPTION_BLOCK_NON_MICROSOFT_BINARIES,
    PS_MITIGATION_OPTION_FONT_DISABLE,
    PS_MITIGATION_OPTION_IMAGE_LOAD_NO_REMOTE,
    PS_MITIGATION_OPTION_IMAGE_LOAD_NO_LOW_LABEL,
    PS_MITIGATION_OPTION_IMAGE_LOAD_PREFER_SYSTEM32,
    PS_MITIGATION_OPTION_RETURN_FLOW_GUARD,
    PS_MITIGATION_OPTION_LOADER_INTEGRITY_CONTINUITY,
    PS_MITIGATION_OPTION_STRICT_CONTROL_FLOW_GUARD,
    PS_MITIGATION_OPTION_RESTRICT_SET_THREAD_CONTEXT,
    PS_MITIGATION_OPTION_ROP_STACKPIVOT, // since REDSTONE3
    PS_MITIGATION_OPTION_ROP_CALLER_CHECK,
    PS_MITIGATION_OPTION_ROP_SIMEXEC,
    PS_MITIGATION_OPTION_EXPORT_ADDRESS_FILTER,
    PS_MITIGATION_OPTION_EXPORT_ADDRESS_FILTER_PLUS,
    PS_MITIGATION_OPTION_RESTRICT_CHILD_PROCESS_CREATION,
    PS_MITIGATION_OPTION_IMPORT_ADDRESS_FILTER,
    PS_MITIGATION_OPTION_MODULE_TAMPERING_PROTECTION,
    PS_MITIGATION_OPTION_RESTRICT_INDIRECT_BRANCH_PREDICTION,
    PS_MITIGATION_OPTION_SPECULATIVE_STORE_BYPASS_DISABLE, // since REDSTONE5
    PS_MITIGATION_OPTION_ALLOW_DOWNGRADE_DYNAMIC_CODE_POLICY,
    PS_MITIGATION_OPTION_CET_USER_SHADOW_STACKS,
    PS_MITIGATION_OPTION_USER_CET_SET_CONTEXT_IP_VALIDATION, // since 21H1
    PS_MITIGATION_OPTION_BLOCK_NON_CET_BINARIES,
    PS_MITIGATION_OPTION_CET_DYNAMIC_APIS_OUT_OF_PROC_ONLY,
    PS_MITIGATION_OPTION_REDIRECTION_TRUST, // since 22H1
    PS_MITIGATION_OPTION_RESTRICT_CORE_SHARING,
    PS_MITIGATION_OPTION_FSCTL_SYSTEM_CALL_DISABLE, // since 24H2
} PS_MITIGATION_OPTION;

// windows-internals-book:"Chapter 5"
typedef enum _PS_CREATE_STATE
{
    PsCreateInitialState,
    PsCreateFailOnFileOpen,
    PsCreateFailOnSectionCreate,
    PsCreateFailExeFormat,
    PsCreateFailMachineMismatch,
    PsCreateFailExeName, // Debugger specified
    PsCreateSuccess,
    PsCreateMaximumStates
} PS_CREATE_STATE;

typedef struct _PS_CREATE_INFO
{
    SIZE_T Size;
    PS_CREATE_STATE State;
    union
    {
        // PsCreateInitialState
        struct
        {
            union
            {
                ULONG InitFlags;
                struct
                {
                    UCHAR WriteOutputOnExit : 1;
                    UCHAR DetectManifest : 1;
                    UCHAR IFEOSkipDebugger : 1;
                    UCHAR IFEODoNotPropagateKeyState : 1;
                    UCHAR SpareBits1 : 4;
                    UCHAR SpareBits2 : 8;
                    USHORT ProhibitedImageCharacteristics : 16;
                };
            };
            ACCESS_MASK AdditionalFileAccess;
        } InitState;

        // PsCreateFailOnSectionCreate
        struct
        {
            HANDLE FileHandle;
        } FailSection;

        // PsCreateFailExeFormat
        struct
        {
            USHORT DllCharacteristics;
        } ExeFormat;

        // PsCreateFailExeName
        struct
        {
            HANDLE IFEOKey;
        } ExeName;

        // PsCreateSuccess
        struct
        {
            union
            {
                ULONG OutputFlags;
                struct
                {
                    UCHAR ProtectedProcess : 1;
                    UCHAR AddressSpaceOverride : 1;
                    UCHAR DevOverrideEnabled : 1; // from Image File Execution Options
                    UCHAR ManifestDetected : 1;
                    UCHAR ProtectedProcessLight : 1;
                    UCHAR SpareBits1 : 3;
                    UCHAR SpareBits2 : 8;
                    USHORT SpareBits3 : 16;
                };
            };
            HANDLE FileHandle;
            HANDLE SectionHandle;
            ULONGLONG UserProcessParametersNative;
            ULONG UserProcessParametersWow64;
            ULONG CurrentParameterFlags;
            ULONGLONG PebAddressNative;
            ULONG PebAddressWow64;
            ULONGLONG ManifestAddress;
            ULONG ManifestSize;
        } SuccessState;
    };
} PS_CREATE_INFO, * PPS_CREATE_INFO;

// end_private

/**
 * Creates a new process and primary thread.
 *
 * \param ProcessHandle A pointer to a handle that receives the process object handle.
 * \param ThreadHandle A pointer to a handle that receives the thread object handle.
 * \param ProcessDesiredAccess The access rights desired for the process object.
 * \param ThreadDesiredAccess The access rights desired for the thread object.
 * \param ProcessObjectAttributes Optional. A pointer to an OBJECT_ATTRIBUTES structure that specifies the attributes of the new process.
 * \param ThreadObjectAttributes Optional. A pointer to an OBJECT_ATTRIBUTES structure that specifies the attributes of the new thread.
 * \param ProcessFlags Flags that control the creation of the process. These flags are defined as PROCESS_CREATE_FLAGS_*.
 * \param ThreadFlags Flags that control the creation of the thread. These flags are defined as THREAD_CREATE_FLAGS_*.
 * \param ProcessParameters Optional. A pointer to a RTL_USER_PROCESS_PARAMETERS structure that specifies the parameters for the new process.
 * \param CreateInfo A pointer to a PS_CREATE_INFO structure that specifies additional information for the process creation.
 * \param AttributeList Optional. A pointer to a list of attributes for the process and thread.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateUserProcess(
    _Out_ PHANDLE ProcessHandle,
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK ProcessDesiredAccess,
    _In_ ACCESS_MASK ThreadDesiredAccess,
    _In_opt_ PCOBJECT_ATTRIBUTES ProcessObjectAttributes,
    _In_opt_ PCOBJECT_ATTRIBUTES ThreadObjectAttributes,
    _In_ ULONG ProcessFlags, // PROCESS_CREATE_FLAGS_*
    _In_ ULONG ThreadFlags, // THREAD_CREATE_FLAGS_*
    _In_opt_ PVOID ProcessParameters, // PRTL_USER_PROCESS_PARAMETERS
    _Inout_ PPS_CREATE_INFO CreateInfo,
    _In_opt_ PPS_ATTRIBUTE_LIST AttributeList
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateUserProcess(
    _Out_ PHANDLE ProcessHandle,
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK ProcessDesiredAccess,
    _In_ ACCESS_MASK ThreadDesiredAccess,
    _In_opt_ PCOBJECT_ATTRIBUTES ProcessObjectAttributes,
    _In_opt_ PCOBJECT_ATTRIBUTES ThreadObjectAttributes,
    _In_ ULONG ProcessFlags, // PROCESS_CREATE_FLAGS_*
    _In_ ULONG ThreadFlags, // THREAD_CREATE_FLAGS_*
    _In_opt_ PVOID ProcessParameters, // PRTL_USER_PROCESS_PARAMETERS
    _Inout_ PPS_CREATE_INFO CreateInfo,
    _In_opt_ PPS_ATTRIBUTE_LIST AttributeList
);

// begin_rev
#define THREAD_CREATE_FLAGS_NONE                    0x00000000
#define THREAD_CREATE_FLAGS_CREATE_SUSPENDED        0x00000001 // NtCreateUserProcess & NtCreateThreadEx
#define THREAD_CREATE_FLAGS_SKIP_THREAD_ATTACH      0x00000002 // NtCreateThreadEx only
#define THREAD_CREATE_FLAGS_HIDE_FROM_DEBUGGER      0x00000004 // NtCreateThreadEx only
#define THREAD_CREATE_FLAGS_LOADER_WORKER           0x00000010 // NtCreateThreadEx only // since THRESHOLD
#define THREAD_CREATE_FLAGS_SKIP_LOADER_INIT        0x00000020 // NtCreateThreadEx only // since REDSTONE2
#define THREAD_CREATE_FLAGS_BYPASS_PROCESS_FREEZE   0x00000040 // NtCreateThreadEx only // since 19H1
// end_rev

/**
 * A pointer to a user-defined function that serves as the starting routine for a new thread.
 *
 * \param ThreadParameter A pointer to a variable to be passed to the thread.
 * \return NTSTATUS Successful or errant status.
 */
typedef _Function_class_(USER_THREAD_START_ROUTINE)
NTSTATUS NTAPI USER_THREAD_START_ROUTINE(
    _In_ PVOID ThreadParameter
);
typedef USER_THREAD_START_ROUTINE* PUSER_THREAD_START_ROUTINE;

/**
 * Creates a new thread in the specified process.
 *
 * \param ThreadHandle A pointer to a handle that receives the thread object handle.
 * \param DesiredAccess The access rights desired for the thread object.
 * \param ObjectAttributes Optional. A pointer to an OBJECT_ATTRIBUTES structure that specifies the attributes of the new thread.
 * \param ProcessHandle A handle to the process in which the thread is to be created.
 * \param StartRoutine A pointer to the application-defined function to be executed by the thread.
 * \param Argument Optional. A pointer to a variable to be passed to the thread.
 * \param CreateFlags Flags that control the creation of the thread. These flags are defined as THREAD_CREATE_FLAGS_*.
 * \param ZeroBits The number of zero bits in the starting address of the thread's stack.
 * \param StackSize The initial size of the thread's stack, in bytes.
 * \param MaximumStackSize The maximum size of the thread's stack, in bytes.
 * \param AttributeList Optional. A pointer to a list of attributes for the thread.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateThreadEx(
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ PCOBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ProcessHandle,
    _In_ PUSER_THREAD_START_ROUTINE StartRoutine,
    _In_opt_ PVOID Argument,
    _In_ ULONG CreateFlags, // THREAD_CREATE_FLAGS_*
    _In_ SIZE_T ZeroBits,
    _In_ SIZE_T StackSize,
    _In_ SIZE_T MaximumStackSize,
    _In_opt_ PPS_ATTRIBUTE_LIST AttributeList
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateThreadEx(
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ PCOBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ProcessHandle,
    _In_ PUSER_THREAD_START_ROUTINE StartRoutine,
    _In_opt_ PVOID Argument,
    _In_ ULONG CreateFlags, // THREAD_CREATE_FLAGS_*
    _In_ SIZE_T ZeroBits,
    _In_ SIZE_T StackSize,
    _In_ SIZE_T MaximumStackSize,
    _In_opt_ PPS_ATTRIBUTE_LIST AttributeList
);

//
// Job objects
//
#if defined(_KERNEL_MODE) && !defined(_WINDOWS_)
typedef enum _JOBOBJECTINFOCLASS
{
    JobObjectBasicAccountingInformation = 1,
    JobObjectBasicLimitInformation,
    JobObjectBasicProcessIdList,
    JobObjectBasicUIRestrictions,
    JobObjectSecurityLimitInformation,
    JobObjectEndOfJobTimeInformation,
    JobObjectAssociateCompletionPortInformation,
    JobObjectBasicAndIoAccountingInformation,
    JobObjectExtendedLimitInformation,
    JobObjectJobSetInformation,
    JobObjectGroupInformation,
    JobObjectNotificationLimitInformation,
    JobObjectLimitViolationInformation,
    JobObjectGroupInformationEx,
    JobObjectCpuRateControlInformation,
    JobObjectCompletionFilter,
    JobObjectCompletionCounter,
    JobObjectFreezeInformation,
    JobObjectExtendedAccountingInformation,
    JobObjectWakeInformation,
    JobObjectBackgroundInformation,
    JobObjectSchedulingRankBiasInformation,
    JobObjectTimerVirtualizationInformation,
    JobObjectCycleTimeNotification,
    JobObjectClearEvent,
    JobObjectInterferenceInformation,
    JobObjectClearPeakJobMemoryUsed,
    JobObjectMemoryUsageInformation,
    JobObjectSharedCommit,
    JobObjectContainerId,
    JobObjectIoRateControlInformation,
    JobObjectNetRateControlInformation,
    JobObjectNotificationLimitInformation2,
    JobObjectLimitViolationInformation2,
    JobObjectCreateSilo,
    JobObjectSiloBasicInformation,
    JobObjectSiloRootDirectory,
    JobObjectServerSiloBasicInformation,
    JobObjectServerSiloUserSharedData,
    JobObjectServerSiloInitialize,
    JobObjectServerSiloRunningState,
    JobObjectIoAttribution,
    JobObjectMemoryPartitionInformation,
    JobObjectContainerTelemetryId,
    JobObjectSiloSystemRoot,
    JobObjectEnergyTrackingState,
    JobObjectThreadImpersonationInformation,
    JobObjectIoPriorityLimit,
    JobObjectPagePriorityLimit,
    JobObjectServerSiloDiagnosticInformation,
    JobObjectNetworkAccountingInformation,
    MaxJobObjectInfoClass,
} JOBOBJECTINFOCLASS;
#else
// Note: We don't use an enum since it conflicts with the Windows SDK.
#define JobObjectBasicAccountingInformation         ((_JOBOBJECTINFOCLASS)1 ) // q:     JOBOBJECT_BASIC_ACCOUNTING_INFORMATION
#define JobObjectBasicLimitInformation              ((_JOBOBJECTINFOCLASS)2 ) // q; s:  JOBOBJECT_BASIC_LIMIT_INFORMATION
#define JobObjectBasicProcessIdList                 ((_JOBOBJECTINFOCLASS)3 ) // q:     JOBOBJECT_BASIC_PROCESS_ID_LIST
#define JobObjectBasicUIRestrictions                ((_JOBOBJECTINFOCLASS)4 ) // q; s:  JOBOBJECT_BASIC_UI_RESTRICTIONS
#define JobObjectSecurityLimitInformation           ((_JOBOBJECTINFOCLASS)5 ) //        JOBOBJECT_SECURITY_LIMIT_INFORMATION
#define JobObjectEndOfJobTimeInformation            ((_JOBOBJECTINFOCLASS)6 ) // q; s:  JOBOBJECT_END_OF_JOB_TIME_INFORMATION
#define JobObjectAssociateCompletionPortInformation ((_JOBOBJECTINFOCLASS)7 ) // s:     JOBOBJECT_ASSOCIATE_COMPLETION_PORT
#define JobObjectBasicAndIoAccountingInformation    ((_JOBOBJECTINFOCLASS)8 ) // q:     JOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION
#define JobObjectExtendedLimitInformation           ((_JOBOBJECTINFOCLASS)9 ) // q; s:  JOBOBJECT_EXTENDED_LIMIT_INFORMATION
#define JobObjectJobSetInformation                  ((_JOBOBJECTINFOCLASS)10) //        JOBOBJECT_JOBSET_INFORMATION
#define JobObjectGroupInformation                   ((_JOBOBJECTINFOCLASS)11) //        USHORT
#define JobObjectNotificationLimitInformation       ((_JOBOBJECTINFOCLASS)12) //        JOBOBJECT_NOTIFICATION_LIMIT_INFORMATION
#define JobObjectLimitViolationInformation          ((_JOBOBJECTINFOCLASS)13) //        JOBOBJECT_LIMIT_VIOLATION_INFORMATION
#define JobObjectGroupInformationEx                 ((_JOBOBJECTINFOCLASS)14) //        GROUP_AFFINITY (ARRAY)
#define JobObjectCpuRateControlInformation          ((_JOBOBJECTINFOCLASS)15) //        JOBOBJECT_CPU_RATE_CONTROL_INFORMATION
#define JobObjectCompletionFilter                   ((_JOBOBJECTINFOCLASS)16) // q; s: ULONG
#define JobObjectCompletionCounter                  ((_JOBOBJECTINFOCLASS)17) // q; s: ULONG
#define JobObjectFreezeInformation                  ((_JOBOBJECTINFOCLASS)18) // JOBOBJECT_FREEZE_INFORMATION
#define JobObjectExtendedAccountingInformation      ((_JOBOBJECTINFOCLASS)19) // JOBOBJECT_EXTENDED_ACCOUNTING_INFORMATION
#define JobObjectWakeInformation                    ((_JOBOBJECTINFOCLASS)20) // JOBOBJECT_WAKE_INFORMATION
#define JobObjectBackgroundInformation              ((_JOBOBJECTINFOCLASS)21) // s: BOOLEAN
#define JobObjectSchedulingRankBiasInformation      ((_JOBOBJECTINFOCLASS)22)
#define JobObjectTimerVirtualizationInformation     ((_JOBOBJECTINFOCLASS)23)
#define JobObjectCycleTimeNotification              ((_JOBOBJECTINFOCLASS)24)
#define JobObjectClearEvent                         ((_JOBOBJECTINFOCLASS)25)
#define JobObjectInterferenceInformation            ((_JOBOBJECTINFOCLASS)26) // JOBOBJECT_INTERFERENCE_INFORMATION
#define JobObjectClearPeakJobMemoryUsed             ((_JOBOBJECTINFOCLASS)27)
#define JobObjectMemoryUsageInformation             ((_JOBOBJECTINFOCLASS)28) // JOBOBJECT_MEMORY_USAGE_INFORMATION // JOBOBJECT_MEMORY_USAGE_INFORMATION_V2
#define JobObjectSharedCommit                       ((_JOBOBJECTINFOCLASS)29)
#define JobObjectContainerId                        ((_JOBOBJECTINFOCLASS)30) // JOBOBJECT_CONTAINER_IDENTIFIER_V2
#define JobObjectIoRateControlInformation           ((_JOBOBJECTINFOCLASS)31) // JOBOBJECT_IO_RATE_CONTROL_INFORMATION_NATIVE, JOBOBJECT_IO_RATE_CONTROL_INFORMATION_NATIVE_V2, JOBOBJECT_IO_RATE_CONTROL_INFORMATION_NATIVE_V3
#define JobObjectNetRateControlInformation          ((_JOBOBJECTINFOCLASS)32) // JOBOBJECT_NET_RATE_CONTROL_INFORMATION
#define JobObjectNotificationLimitInformation2      ((_JOBOBJECTINFOCLASS)33) // JOBOBJECT_NOTIFICATION_LIMIT_INFORMATION_2
#define JobObjectLimitViolationInformation2         ((_JOBOBJECTINFOCLASS)34) // JOBOBJECT_LIMIT_VIOLATION_INFORMATION_2
#define JobObjectCreateSilo                         ((_JOBOBJECTINFOCLASS)35) // s: NULL
#define JobObjectSiloBasicInformation               ((_JOBOBJECTINFOCLASS)36) // SILOOBJECT_BASIC_INFORMATION
#define JobObjectSiloRootDirectory                  ((_JOBOBJECTINFOCLASS)37) // SILOOBJECT_ROOT_DIRECTORY
#define JobObjectServerSiloBasicInformation         ((_JOBOBJECTINFOCLASS)38) // SERVERSILO_BASIC_INFORMATION
#define JobObjectServerSiloUserSharedData           ((_JOBOBJECTINFOCLASS)39) // SILO_USER_SHARED_DATA // NtQueryInformationJobObject(NULL, 39, Buffer, sizeof(SILO_USER_SHARED_DATA), 0);
#define JobObjectServerSiloInitialize               ((_JOBOBJECTINFOCLASS)40) // SERVERSILO_INIT_INFORMATION
#define JobObjectServerSiloRunningState             ((_JOBOBJECTINFOCLASS)41)
#define JobObjectIoAttribution                      ((_JOBOBJECTINFOCLASS)42) // JOBOBJECT_IO_ATTRIBUTION_INFORMATION
#define JobObjectMemoryPartitionInformation         ((_JOBOBJECTINFOCLASS)43)
#define JobObjectContainerTelemetryId               ((_JOBOBJECTINFOCLASS)44) // s: GUID // NtSetInformationJobObject(_In_ PGUID, 44, _In_ PGUID, sizeof(GUID)); // daxexec
#define JobObjectSiloSystemRoot                     ((_JOBOBJECTINFOCLASS)45) // s: UNICODE_STRING
#define JobObjectEnergyTrackingState                ((_JOBOBJECTINFOCLASS)46) // JOBOBJECT_ENERGY_TRACKING_STATE
#define JobObjectThreadImpersonationInformation     ((_JOBOBJECTINFOCLASS)47) // q; s: BOOLEAN
#define JobObjectIoPriorityLimit                    ((_JOBOBJECTINFOCLASS)48) // JOBOBJECT_IO_PRIORITY_LIMIT
#define JobObjectPagePriorityLimit                  ((_JOBOBJECTINFOCLASS)49) // JOBOBJECT_PAGE_PRIORITY_LIMIT
#define JobObjectServerSiloDiagnosticInformation    ((_JOBOBJECTINFOCLASS)50) // SERVERSILO_DIAGNOSTIC_INFORMATION // since 24H2
#define JobObjectNetworkAccountingInformation       ((_JOBOBJECTINFOCLASS)51) // JOBOBJECT_NETWORK_ACCOUNTING_INFORMATION
#define MaxJobObjectInfoClass                       ((_JOBOBJECTINFOCLASS)52)
#endif // _KERNEL_MODE

#ifdef _KERNEL_MODE
typedef struct _JOBOBJECT_BASIC_ACCOUNTING_INFORMATION {
    LARGE_INTEGER TotalUserTime;
    LARGE_INTEGER TotalKernelTime;
    LARGE_INTEGER ThisPeriodTotalUserTime;
    LARGE_INTEGER ThisPeriodTotalKernelTime;
    UINT32 TotalPageFaultCount;
    UINT32 TotalProcesses;
    UINT32 ActiveProcesses;
    UINT32 TotalTerminatedProcesses;
} JOBOBJECT_BASIC_ACCOUNTING_INFORMATION, * PJOBOBJECT_BASIC_ACCOUNTING_INFORMATION;

typedef struct _JOBOBJECT_BASIC_LIMIT_INFORMATION {
    LARGE_INTEGER PerProcessUserTimeLimit;
    LARGE_INTEGER PerJobUserTimeLimit;
    DWORD LimitFlags;
    SIZE_T MinimumWorkingSetSize;
    SIZE_T MaximumWorkingSetSize;
    DWORD ActiveProcessLimit;
    ULONG_PTR Affinity;
    DWORD PriorityClass;
    DWORD SchedulingClass;
} JOBOBJECT_BASIC_LIMIT_INFORMATION, * PJOBOBJECT_BASIC_LIMIT_INFORMATION;

// rev // extended limit v2
#define JOB_OBJECT_LIMIT_SILO_READY 0x00400000
typedef struct _JOBOBJECT_EXTENDED_LIMIT_INFORMATION {
    JOBOBJECT_BASIC_LIMIT_INFORMATION BasicLimitInformation;
    IO_COUNTERS IoInfo;
    SIZE_T ProcessMemoryLimit;
    SIZE_T JobMemoryLimit;
    SIZE_T PeakProcessMemoryUsed;
    SIZE_T PeakJobMemoryUsed;
    SIZE_T JobTotalMemoryLimit;
} JOBOBJECT_EXTENDED_LIMIT_INFORMATION, * PJOBOBJECT_EXTENDED_LIMIT_INFORMATION;
#endif // _KERNEL_MODE

// private
typedef struct _JOBOBJECT_EXTENDED_ACCOUNTING_INFORMATION
{
    JOBOBJECT_BASIC_ACCOUNTING_INFORMATION BasicInfo;
    IO_COUNTERS IoInfo;
    PROCESS_DISK_COUNTERS DiskIoInfo;
    ULONG64 ContextSwitches;
    LARGE_INTEGER TotalCycleTime;
    ULONG64 ReadyTime;
    PROCESS_ENERGY_VALUES EnergyValues;
} JOBOBJECT_EXTENDED_ACCOUNTING_INFORMATION, * PJOBOBJECT_EXTENDED_ACCOUNTING_INFORMATION;

// private
typedef struct _JOBOBJECT_WAKE_INFORMATION
{
    HANDLE NotificationChannel;
    ULONG64 WakeCounters[PsMaxWakeReasons];
} JOBOBJECT_WAKE_INFORMATION, * PJOBOBJECT_WAKE_INFORMATION;

// private
typedef struct _JOBOBJECT_WAKE_INFORMATION_V1
{
    HANDLE NotificationChannel;
    ULONG64 WakeCounters[4];
} JOBOBJECT_WAKE_INFORMATION_V1, * PJOBOBJECT_WAKE_INFORMATION_V1;

// private
typedef struct _JOBOBJECT_INTERFERENCE_INFORMATION
{
    ULONG64 Count;
} JOBOBJECT_INTERFERENCE_INFORMATION, * PJOBOBJECT_INTERFERENCE_INFORMATION;

// private
typedef struct _JOBOBJECT_FREEZE_INFORMATION
{
    union
    {
        ULONG Flags;
        struct
        {
            ULONG FreezeOperation : 1;
            ULONG FilterOperation : 1;
            ULONG SwapOperation : 1;
            ULONG Reserved : 29;
        };
    };
    BOOLEAN Freeze;
    BOOLEAN Swap;
    UCHAR Reserved0[2];
    JOBOBJECT_WAKE_FILTER WakeFilter;
} JOBOBJECT_FREEZE_INFORMATION, * PJOBOBJECT_FREEZE_INFORMATION;

// private
typedef struct _JOBOBJECT_CONTAINER_IDENTIFIER_V2
{
    GUID ContainerId;
    GUID ContainerTelemetryId;
    ULONG JobId;
} JOBOBJECT_CONTAINER_IDENTIFIER_V2, * PJOBOBJECT_CONTAINER_IDENTIFIER_V2;

// private
typedef struct _JOBOBJECT_MEMORY_USAGE_INFORMATION
{
    ULONG64 JobMemory;
    ULONG64 PeakJobMemoryUsed;
} JOBOBJECT_MEMORY_USAGE_INFORMATION, * PJOBOBJECT_MEMORY_USAGE_INFORMATION;

// private
typedef struct _JOBOBJECT_MEMORY_USAGE_INFORMATION_V2
{
    JOBOBJECT_MEMORY_USAGE_INFORMATION BasicInfo;
    ULONG64 JobSharedMemory;
    ULONG64 Reserved[2];
} JOBOBJECT_MEMORY_USAGE_INFORMATION_V2, * PJOBOBJECT_MEMORY_USAGE_INFORMATION_V2;

#if (NTDDI_VERSION != NTDDI_WIN10_RS1)
// private
//
// Define data shared between kernel and user mode per each Silo.
//
// N.B. User mode has read only access to this data
//
typedef struct _SILO_USER_SHARED_DATA
{
    ULONG ServiceSessionId;
    ULONG ActiveConsoleId;
    LONGLONG ConsoleSessionForegroundProcessId;
    NT_PRODUCT_TYPE NtProductType;
    ULONG SuiteMask;
    ULONG SharedUserSessionId; // since RS2
    BOOLEAN IsMultiSessionSku;
    BOOLEAN IsStateSeparationEnabled;
    WCHAR NtSystemRoot[260];
    USHORT UserModeGlobalLogger[16];
    ULONG TimeZoneId; // since 21H2
    LONG TimeZoneBiasStamp;
    KSYSTEM_TIME TimeZoneBias;
    LARGE_INTEGER TimeZoneBiasEffectiveStart;
    LARGE_INTEGER TimeZoneBiasEffectiveEnd;
} SILO_USER_SHARED_DATA, * PSILO_USER_SHARED_DATA;
#endif // WDK_NTDDI_VERSION != NTDDI_WIN10_RS1

#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)
// rev
#define SILO_OBJECT_ROOT_DIRECTORY_SHADOW_ROOT 0x00000001
#define SILO_OBJECT_ROOT_DIRECTORY_INITIALIZE 0x00000002
#define SILO_OBJECT_ROOT_DIRECTORY_SHADOW_DOS_DEVICES 0x00000004

// private
typedef struct _SILOOBJECT_ROOT_DIRECTORY
{
    union
    {
        ULONG ControlFlags; // SILO_OBJECT_ROOT_DIRECTORY_*
        UNICODE_STRING Path;
    };
} SILOOBJECT_ROOT_DIRECTORY, * PSILOOBJECT_ROOT_DIRECTORY;
#endif // NTDDI_VERSION >= NTDDI_WIN10_RS1

// private
typedef struct _SERVERSILO_INIT_INFORMATION
{
    HANDLE DeleteEvent;
    BOOLEAN IsDownlevelContainer;
} SERVERSILO_INIT_INFORMATION, *PSERVERSILO_INIT_INFORMATION;

// private
typedef struct _JOBOBJECT_ENERGY_TRACKING_STATE
{
    ULONG64 Value;
    ULONG UpdateMask;
    ULONG DesiredState;
} JOBOBJECT_ENERGY_TRACKING_STATE, * PJOBOBJECT_ENERGY_TRACKING_STATE;

// private
typedef enum _JOBOBJECT_IO_PRIORITY_LIMIT_FLAGS
{
    JOBOBJECT_IO_PRIORITY_LIMIT_ENABLE = 0x1,
    JOBOBJECT_IO_PRIORITY_LIMIT_VALID_FLAGS = 0x1,
} JOBOBJECT_IO_PRIORITY_LIMIT_FLAGS;

// private
typedef struct _JOBOBJECT_IO_PRIORITY_LIMIT
{
    JOBOBJECT_IO_PRIORITY_LIMIT_FLAGS Flags;
    ULONG Priority;
} JOBOBJECT_IO_PRIORITY_LIMIT, * PJOBOBJECT_IO_PRIORITY_LIMIT;

// private
typedef enum _JOBOBJECT_PAGE_PRIORITY_LIMIT_FLAGS
{
    JOBOBJECT_PAGE_PRIORITY_LIMIT_ENABLE = 0x1,
    JOBOBJECT_PAGE_PRIORITY_LIMIT_VALID_FLAGS = 0x1,
} JOBOBJECT_PAGE_PRIORITY_LIMIT_FLAGS;

// private
typedef struct _JOBOBJECT_PAGE_PRIORITY_LIMIT
{
    JOBOBJECT_PAGE_PRIORITY_LIMIT_FLAGS Flags;
    ULONG Priority;
} JOBOBJECT_PAGE_PRIORITY_LIMIT, * PJOBOBJECT_PAGE_PRIORITY_LIMIT;

/**
 * Creates or opens a job object.
 *
 * \param JobHandle A handle to the job object.
 * \param DesiredAccess The access rights desired for the thread object.
 * \param ObjectAttributes Optional. A pointer to an OBJECT_ATTRIBUTES structure that specifies the attributes of the new thread.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateJobObject(
    _Out_ PHANDLE JobHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ PCOBJECT_ATTRIBUTES ObjectAttributes
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateJobObject(
    _Out_ PHANDLE JobHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ PCOBJECT_ATTRIBUTES ObjectAttributes
);

/**
 * Opens an existing job object.
 *
 * \param JobHandle A handle to the job object.
 * \param DesiredAccess The access rights desired for the thread object.
 * \param ObjectAttributes Optional. A pointer to an OBJECT_ATTRIBUTES structure that specifies the attributes of the new thread.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenJobObject(
    _Out_ PHANDLE JobHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ PCOBJECT_ATTRIBUTES ObjectAttributes
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwOpenJobObject(
    _Out_ PHANDLE JobHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ PCOBJECT_ATTRIBUTES ObjectAttributes
);

/**
 * Assigns a process to an existing job object.
 *
 * \param JobHandle A handle to the job object to which the process will be associated. The handle must have the JOB_OBJECT_ASSIGN_PROCESS access right.
 * \param ProcessHandle A handle to the process to associate with the job object. The handle must have the PROCESS_SET_QUOTA and PROCESS_TERMINATE access rights.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAssignProcessToJobObject(
    _In_ HANDLE JobHandle,
    _In_ HANDLE ProcessHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAssignProcessToJobObject(
    _In_ HANDLE JobHandle,
    _In_ HANDLE ProcessHandle
);

/**
 * Terminates all processes associated with the job object. If the job is nested, all processes currently associated with the job and all child jobs in the hierarchy are terminated.
 *
 * \param JobHandle A handle to the job whose processes will be terminated. The handle must have the JOB_OBJECT_TERMINATE access right.
 * \param ExitStatus The exit status to be used by all processes and threads in the job object.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtTerminateJobObject(
    _In_ HANDLE JobHandle,
    _In_ NTSTATUS ExitStatus
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwTerminateJobObject(
    _In_ HANDLE JobHandle,
    _In_ NTSTATUS ExitStatus
);

/**
 * Checks if a process is associated with a job object.
 *
 * \param ProcessHandle A handle to the process to be checked.
 * \param JobHandle An optional handle to the job object. If this parameter is NULL, the function checks if the process is associated with any job object.
 * \return NTSTATUS Successful or errant status.
 * \remarks This function can be used to determine if a process is running within a job object, which can be useful for managing process resources and constraints.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtIsProcessInJob(
    _In_ HANDLE ProcessHandle,
    _In_opt_ HANDLE JobHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwIsProcessInJob(
    _In_ HANDLE ProcessHandle,
    _In_opt_ HANDLE JobHandle
);

/**
 * Retrieves information about a job object.
 *
 * \param JobHandle An optional handle to the job object. If this parameter is NULL, the function retrieves information about the job object associated with the calling process.
 * \param JobObjectInformationClass The type of job object information to be retrieved.
 * \param JobObjectInformation A pointer to a buffer that receives the job object information.
 * \param JobObjectInformationLength The size of the buffer pointed to by the JobObjectInformation parameter.
 * \param ReturnLength An optional pointer to a variable that receives the size of the data returned.
 * \return NTSTATUS Successful or errant status.
 * \remarks This function can be used to query various types of information about a job object, such as accounting information, limit information, and process ID list.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryInformationJobObject(
    _In_opt_ HANDLE JobHandle,
    _In_ JOBOBJECTINFOCLASS JobObjectInformationClass,
    _Out_writes_bytes_(JobObjectInformationLength) PVOID JobObjectInformation,
    _In_ ULONG JobObjectInformationLength,
    _Out_opt_ PULONG ReturnLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwQueryInformationJobObject(
    _In_opt_ HANDLE JobHandle,
    _In_ JOBOBJECTINFOCLASS JobObjectInformationClass,
    _Out_writes_bytes_(JobObjectInformationLength) PVOID JobObjectInformation,
    _In_ ULONG JobObjectInformationLength,
    _Out_opt_ PULONG ReturnLength
);

/**
 * Sets information for a job object.
 *
 * \param JobHandle A handle to the job object.
 * \param JobObjectInformationClass The type of job object information to be set.
 * \param JobObjectInformation A pointer to a buffer that contains the job object information.
 * \param JobObjectInformationLength The size of the buffer pointed to by the JobObjectInformation parameter.
 * \return NTSTATUS Successful or errant status.
 * \remarks This function can be used to set various types of information for a job object, such as limit information, UI restrictions, and security limit information.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationJobObject(
    _In_ HANDLE JobHandle,
    _In_ JOBOBJECTINFOCLASS JobObjectInformationClass,
    _In_reads_bytes_(JobObjectInformationLength) PVOID JobObjectInformation,
    _In_ ULONG JobObjectInformationLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSetInformationJobObject(
    _In_ HANDLE JobHandle,
    _In_ JOBOBJECTINFOCLASS JobObjectInformationClass,
    _In_reads_bytes_(JobObjectInformationLength) PVOID JobObjectInformation,
    _In_ ULONG JobObjectInformationLength
);

#if defined(_KERNEL_MODE) && !defined(_WINDOWS_)
typedef struct _JOB_SET_ARRAY
{
    HANDLE JobHandle;   // Handle to job object to insert
    UINT32 MemberLevel; // Level of this job in the set. Must be > 0. Can be sparse.
    UINT32 Flags;       // Unused. Must be zero
} JOB_SET_ARRAY, * PJOB_SET_ARRAY;
#endif // _KERNEL_MODE

/**
 * Creates a set of job objects.
 *
 * \param NumJob The number of job objects in the set.
 * \param UserJobSet A pointer to an array of JOB_SET_ARRAY structures that specify the job objects in the set.
 * \param Flags Reserved for future use. Must be zero.
 * \return NTSTATUS Successful or errant status.
 * \remarks This function can be used to create a set of job objects, which can be useful for managing groups of related processes.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateJobSet(
    _In_ ULONG NumJob,
    _In_reads_(NumJob) PJOB_SET_ARRAY UserJobSet,
    _In_ ULONG Flags
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateJobSet(
    _In_ ULONG NumJob,
    _In_reads_(NumJob) PJOB_SET_ARRAY UserJobSet,
    _In_ ULONG Flags
);

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtRevertContainerImpersonation(
    VOID
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwRevertContainerImpersonation(
    VOID
);
#endif

//
// Reserve objects
//

// private
typedef enum _MEMORY_RESERVE_TYPE
{
    MemoryReserveUserApc,
    MemoryReserveIoCompletion,
    MemoryReserveTypeMax
} MEMORY_RESERVE_TYPE;

/**
 * Allocates a memory reserve object.
 *
 * \param MemoryReserveHandle Pointer to a variable that receives the memory reserve object handle.
 * \param ObjectAttributes Pointer to an object attributes structure.
 * \param Type The type of memory reserve.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAllocateReserveObject(
    _Out_ PHANDLE MemoryReserveHandle,
    _In_ PCOBJECT_ATTRIBUTES ObjectAttributes,
    _In_ MEMORY_RESERVE_TYPE Type
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAllocateReserveObject(
    _Out_ PHANDLE MemoryReserveHandle,
    _In_ PCOBJECT_ATTRIBUTES ObjectAttributes,
    _In_ MEMORY_RESERVE_TYPE Type
);

//
// Process snapshotting
//

#ifndef _KERNEL_MODE

// Capture/creation flags.
typedef enum _PSSNT_CAPTURE_FLAGS
{
    PSSNT_CAPTURE_NONE = 0x00000000,
    PSSNT_CAPTURE_VA_CLONE = 0x00000001,
    PSSNT_CAPTURE_RESERVED_00000002 = 0x00000002,
    PSSNT_CAPTURE_HANDLES = 0x00000004,
    PSSNT_CAPTURE_HANDLE_NAME_INFORMATION = 0x00000008,
    PSSNT_CAPTURE_HANDLE_BASIC_INFORMATION = 0x00000010,
    PSSNT_CAPTURE_HANDLE_TYPE_SPECIFIC_INFORMATION = 0x00000020,
    PSSNT_CAPTURE_HANDLE_TRACE = 0x00000040,
    PSSNT_CAPTURE_THREADS = 0x00000080,
    PSSNT_CAPTURE_THREAD_CONTEXT = 0x00000100,
    PSSNT_CAPTURE_THREAD_CONTEXT_EXTENDED = 0x00000200,
    PSSNT_CAPTURE_RESERVED_00000400 = 0x00000400,
    PSSNT_CAPTURE_VA_SPACE = 0x00000800,
    PSSNT_CAPTURE_VA_SPACE_SECTION_INFORMATION = 0x00001000,
    PSSNT_CAPTURE_IPT_TRACE = 0x00002000,
    PSSNT_CAPTURE_RESERVED_00004000 = 0x00004000,

    PSSNT_CREATE_BREAKAWAY_OPTIONAL = 0x04000000,
    PSSNT_CREATE_BREAKAWAY = 0x08000000,
    PSSNT_CREATE_FORCE_BREAKAWAY = 0x10000000,
    PSSNT_CREATE_USE_VM_ALLOCATIONS = 0x20000000,
    PSSNT_CREATE_MEASURE_PERFORMANCE = 0x40000000,
    PSSNT_CREATE_RELEASE_SECTION = 0x80000000
} PSSNT_CAPTURE_FLAGS;
DEFINE_ENUM_FLAG_OPERATORS(PSSNT_CAPTURE_FLAGS);

typedef enum _PSSNT_DUPLICATE_FLAGS
{
    PSSNT_DUPLICATE_NONE = 0x00,
    PSSNT_DUPLICATE_CLOSE_SOURCE = 0x01
} PSSNT_DUPLICATE_FLAGS;
DEFINE_ENUM_FLAG_OPERATORS(PSSNT_DUPLICATE_FLAGS);

typedef enum _PSSNT_QUERY_INFORMATION_CLASS
{
    PSSNT_QUERY_PROCESS_INFORMATION = 0, // PSS_PROCESS_INFORMATION
    PSSNT_QUERY_VA_CLONE_INFORMATION = 1, // PSS_VA_CLONE_INFORMATION
    PSSNT_QUERY_AUXILIARY_PAGES_INFORMATION = 2, // PSS_AUXILIARY_PAGES_INFORMATION
    PSSNT_QUERY_VA_SPACE_INFORMATION = 3, // PSS_VA_SPACE_INFORMATION
    PSSNT_QUERY_HANDLE_INFORMATION = 4, // PSS_HANDLE_INFORMATION
    PSSNT_QUERY_THREAD_INFORMATION = 5, // PSS_THREAD_INFORMATION
    PSSNT_QUERY_HANDLE_TRACE_INFORMATION = 6, // PSS_HANDLE_TRACE_INFORMATION
    PSSNT_QUERY_PERFORMANCE_COUNTERS = 7 // PSS_PERFORMANCE_COUNTERS
} PSSNT_QUERY_INFORMATION_CLASS;

#define PSSNT_SIGNATURE_PSSD 'PSSD' // 0x50535344

#if (NTDDI_VERSION >= NTDDI_WINBLUE)
// rev
/**
 * Captures a snapshot of the specified process.
 *
 * \param SnapshotHandle Pointer to a variable that receives the snapshot handle.
 * \param ProcessHandle Handle to the process.
 * \param CaptureFlags Flags indicating what to capture.
 * \param ThreadContextFlags Optional flags for capturing thread context.
 * \return NTSTATUS Successful or errant status.
 */
NTSYSAPI
NTSTATUS
NTAPI
PssNtCaptureSnapshot(
    _Out_ PHANDLE SnapshotHandle,
    _In_ HANDLE ProcessHandle, _In_ PSSNT_CAPTURE_FLAGS CaptureFlags,
    _In_opt_ ULONG ThreadContextFlags
);

// rev
/**
 * Duplicates a process snapshot from one process to another.
 *
 * \param SourceProcessHandle Handle to the source process.
 * \param SnapshotHandle Handle to the snapshot to duplicate.
 * \param TargetProcessHandle Handle to the target process.
 * \param TargetSnapshotHandle Pointer to a variable that receives the duplicated snapshot handle.
 * \param Flags Optional flags for duplication.
 * \return NTSTATUS Successful or errant status.
 */
NTSYSAPI
NTSTATUS
NTAPI
PssNtDuplicateSnapshot(
    _In_ HANDLE SourceProcessHandle,
    _In_ HANDLE SnapshotHandle,
    _In_ HANDLE TargetProcessHandle,
    _Out_ PHANDLE TargetSnapshotHandle,
    _In_opt_ PSSNT_DUPLICATE_FLAGS Flags
);

// rev
/**
 * Frees a remote process snapshot.
 *
 * \param SnapshotHandle Handle to the snapshot to free.
 * \return NTSTATUS Successful or errant status.
 */
NTSYSAPI
NTSTATUS
NTAPI
PssNtFreeSnapshot(
    _In_ HANDLE SnapshotHandle
);

// rev
/**
 * Frees a snapshot.
 *
 * \param ProcessHandle A handle to the process that contains the snapshot. The handle must have PROCESS_VM_READ, PROCESS_VM_OPERATION, and PROCESS_DUP_HANDLE rights.
 * \param SnapshotHandle Handle to the snapshot to free.
 * \return NTSTATUS Successful or errant status.
 */
NTSYSAPI
NTSTATUS
NTAPI
PssNtFreeRemoteSnapshot(
    _In_ HANDLE ProcessHandle,
    _In_ HANDLE SnapshotHandle
);

// rev
/**
 * Queries information from a the specified snapshot.
 *
 * \param SnapshotHandle Handle to the snapshot.
 * \param InformationClass The information class to query.
 * \param Buffer Pointer to a buffer that receives the queried information.
 * \param BufferLength Length of the buffer.
 * \return NTSTATUS Successful or errant status.
 */
NTSYSAPI
NTSTATUS
NTAPI
PssNtQuerySnapshot(
    _In_ HANDLE SnapshotHandle,
    _In_ PSSNT_QUERY_INFORMATION_CLASS InformationClass,
    _Out_writes_bytes_(BufferLength) PVOID Buffer,
    _In_ ULONG BufferLength
);
#endif
#endif // !_KERNEL_MODE

// rev
/**
 * Flag indicating the type of bulk information to query.
 */
#define MEMORY_BULK_INFORMATION_FLAG_BASIC 0x00000001

// rev
/**
 * The NTPSS_MEMORY_BULK_INFORMATION structure is used to query basic memory information in bulk for a process.
 */
typedef struct _NTPSS_MEMORY_BULK_INFORMATION
{
    ULONG QueryFlags;
    ULONG NumberOfEntries;
    PVOID NextValidAddress;
} NTPSS_MEMORY_BULK_INFORMATION, * PNTPSS_MEMORY_BULK_INFORMATION;

#if (NTDDI_VERSION >= NTDDI_WIN10_VB)

// rev
/**
 * Captures virtual address space bulk information for a process.
 *
 * \param ProcessHandle Handle to the process.
 * \param BaseAddress Optional base address to start the capture.
 * \param BulkInformation Pointer to the memory bulk information structure.
 * \param BulkInformationLength Length of the memory bulk information structure.
 * \param ReturnLength Optional pointer to a variable that receives the length of the captured information.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtPssCaptureVaSpaceBulk(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_ PNTPSS_MEMORY_BULK_INFORMATION BulkInformation,
    _In_ SIZE_T BulkInformationLength,
    _Out_opt_ PSIZE_T ReturnLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwPssCaptureVaSpaceBulk(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_ PNTPSS_MEMORY_BULK_INFORMATION BulkInformation,
    _In_ SIZE_T BulkInformationLength,
    _Out_opt_ PSIZE_T ReturnLength
);
#endif // NTDDI_VERSION >= NTDDI_WIN10_VB

#ifdef _KERNEL_MODE

// Process

extern PLIST_ENTRY PsLoadedModuleList;
extern PERESOURCE  PsLoadedModuleResource;

NTKERNELAPI
NTSTATUS
NTAPI
PsLookupProcessThreadByCid(
    _In_ PCLIENT_ID ClientId,
    _Out_opt_ PEPROCESS* Process,
    _Out_ PETHREAD* Thread
);

NTSYSAPI
BOOLEAN
NTAPI
PsIsSystemProcess(
    _In_ PEPROCESS Process
);

NTSYSAPI
HANDLE NTAPI
PsGetProcessInheritedFromUniqueProcessId(
    _In_ PEPROCESS Process
);

NTSYSAPI
ULONG NTAPI
PsGetProcessSessionId(
    _In_ PEPROCESS Process
);

// The difference is that Ex will return -1
NTSYSAPI
ULONG
NTAPI
PsGetProcessSessionIdEx(
    _In_ PEPROCESS Process
);

NTSYSAPI
ULONG
NTAPI
PsGetCurrentProcessSessionId(
);

NTSYSAPI
BOOLEAN
NTAPI
PsGetProcessExitProcessCalled(
    _In_ PEPROCESS Process
);

NTSYSAPI
UCHAR*
NTAPI
PsGetProcessImageFileName(
    _In_ PEPROCESS Process
);

#define PsGetCurrentProcessImageFileName() PsGetProcessImageFileName(PsGetCurrentProcess())

NTSYSAPI
PVOID
NTAPI
PsGetProcessSectionBaseAddress(
    _In_ PEPROCESS Process
);

#define PsGetProcessPcb(Process) ((PKPROCESS)(Process))

NTSYSAPI
PPEB NTAPI
PsGetProcessPeb(
    _In_ PEPROCESS Process
);

NTSYSAPI
VOID
NTAPI
PsSetProcessPriorityClass(
    _Out_ PEPROCESS Process,
    _In_ UCHAR PriorityClass
);

NTSYSAPI
UCHAR
NTAPI
PsGetProcessPriorityClass(
    _In_ PEPROCESS Process
);

NTSYSAPI
VOID
NTAPI
PsSetProcessWindowStation(
    _Out_ PEPROCESS Process,
    _In_ HANDLE Win32WindowStation
);

NTSYSAPI
HANDLE
NTAPI
PsGetProcessWin32WindowStation(
    _In_ PEPROCESS Process
);

#define PsGetCurrentProcessWin32WindowStation() PsGetProcessWin32WindowStation(PsGetCurrentProcess())

NTSYSAPI
NTSTATUS
NTAPI
PsSetProcessWin32Process(
    _In_ PEPROCESS Process,
    _In_ PVOID Win32Process,
    _In_ PVOID PrevWin32Process
);

NTSYSAPI
PVOID
NTAPI
PsGetProcessWin32Process(
    _In_ PEPROCESS Process
);

NTSYSAPI
PVOID
NTAPI
PsGetCurrentProcessWin32Process(
    VOID
);

#ifdef _WIN64
NTSYSAPI
struct _PEB32*
NTAPI
PsGetProcessWow64Process(
    _In_ PEPROCESS Process
);

NTSYSAPI
struct _PEB32*
NTAPI
PsGetCurrentProcessWow64Process(
    VOID
);
#endif //_WIN64

FORCEINLINE BOOLEAN NTAPI PsIs32bitProcess(
    _In_ PEPROCESS Process
)
{
#ifdef _WIN64
    return !!PsGetProcessWow64Process(Process);
#else
    UNREFERENCED_PARAMETER(Process);
    return TRUE;
#endif
}

PVOID NTAPI
PsGetProcessSecurityPort(
    _In_ PEPROCESS Process
);

NTSTATUS NTAPI
PsSuspendProcess(
    _In_ PEPROCESS Process
);

NTSTATUS NTAPI
PsResumeProcess(
    _In_ PEPROCESS Process
);

NTKERNELAPI
NTSTATUS
NTAPI
PsAcquireProcessExitSynchronization(
    _In_ PEPROCESS Process
);

NTKERNELAPI
VOID
NTAPI
PsReleaseProcessExitSynchronization(
    _In_ PEPROCESS Process
);

// Job

NTSYSAPI
PEJOB
NTAPI
PsGetProcessJob(
    _In_ PEPROCESS Process
);

NTSYSAPI
PERESOURCE
NTAPI
PsGetJobLock(
    _In_ PEJOB Job
);

NTSYSAPI
ULONG
NTAPI
PsGetJobSessionId(
    _In_ PEJOB Job
);

NTSYSAPI
VOID
NTAPI
PsSetJobUIRestrictionsClass(
    _Out_ struct _EJOB* Job,
    _In_ ULONG UIRestrictionsClass
);

NTSYSAPI
ULONG
NTAPI
PsGetJobUIRestrictionsClass(
    _In_ PEJOB Job
);

// Debug

NTSYSAPI
PVOID
NTAPI
PsGetProcessDebugPort(
    _In_ PEPROCESS Process
);

NTSYSAPI
BOOLEAN
NTAPI
PsIsProcessBeingDebugged(
    _In_ PEPROCESS Process
);

// File Object

NTSYSAPI
NTSTATUS
NTAPI
PsReferenceProcessFilePointer(
    _In_ PEPROCESS Process,
    _Out_ PFILE_OBJECT* pFilePointer
);

// Thread

_IRQL_requires_max_(PASSIVE_LEVEL)
NTKERNELAPI
_Must_inspect_result_
NTSTATUS
PsCreateSystemThreadEx(
    _Out_ PHANDLE ThreadHandle,
    _In_ ULONG DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_  HANDLE ProcessHandle,
    _Out_opt_ PCLIENT_ID ClientId,
    _In_ PKSTART_ROUTINE StartRoutine,
    _In_opt_ _When_(return >= 0, __drv_aliasesMem) PVOID StartContext,
    _In_opt_ PGROUP_AFFINITY ProcessorGroup,
    _In_opt_ ULONG* IdealProcessor
);

NTKERNELAPI
BOOLEAN
PsIsSystemThread(
    _In_ PETHREAD Thread
);

_IRQL_requires_max_(DISPATCH_LEVEL)
NTKERNELAPI
BOOLEAN
PsIsThreadTerminating(
    _In_ PETHREAD Thread
);

NTKERNELAPI
BOOLEAN
NTAPI
PsIsThreadImpersonating(
    _In_ PETHREAD Thread
);

NTKERNELAPI
PVOID
NTAPI
PsGetCurrentThreadStackLimit(
    VOID
);

NTKERNELAPI
PVOID
NTAPI
PsGetCurrentThreadStackBase(
    VOID
);

NTKERNELAPI
KPROCESSOR_MODE
NTAPI
PsGetCurrentThreadPreviousMode(
    VOID
);

NTKERNELAPI
PEPROCESS
PsGetThreadProcess(
    _In_ PETHREAD Thread
);

NTKERNELAPI
PEPROCESS
NTAPI
PsGetCurrentThreadProcess(
    VOID
);

NTKERNELAPI
HANDLE
NTAPI
PsGetCurrentThreadProcessId(
    VOID
);

FORCEINLINE
CLIENT_ID
NTAPI
PsGetThreadClientId(
    _In_ PETHREAD Thread
)
{
    CLIENT_ID ClientId = { PsGetThreadProcessId(Thread), PsGetThreadId(Thread) };
    return ClientId;
}

NTKERNELAPI
ULONG
NTAPI
PsGetThreadSessionId(
    _In_ PETHREAD Thread
);

NTKERNELAPI
NTSTATUS
NTAPI
PsSetContextThread(
    _In_ PETHREAD Thread,
    _In_ PCONTEXT ThreadContext,
    _In_ KPROCESSOR_MODE Mode
);

NTKERNELAPI
NTSTATUS
NTAPI
PsGetContextThread(
    _In_ PETHREAD Thread,
    _Inout_ PCONTEXT ThreadContext,
    _In_ KPROCESSOR_MODE Mode
);

NTKERNELAPI
VOID
NTAPI
PsSetThreadWin32Thread(
    _Inout_ PETHREAD Thread,
    _In_ PVOID Win32Thread,
    _In_ PVOID PrevWin32Thread
);

NTKERNELAPI
PVOID
NTAPI
PsGetThreadWin32Thread(
    _In_ PETHREAD Thread
);

NTKERNELAPI
PVOID
NTAPI
PsGetCurrentThreadWin32Thread(
    VOID
);

NTKERNELAPI
PVOID
NTAPI
PsGetCurrentThreadWin32ThreadAndEnterCriticalRegion(
    _Out_ PHANDLE ProcessId
);

#define PsGetThreadTcb(Thread) ((PKTHREAD)(Thread))

NTKERNELAPI
PVOID
NTAPI
PsGetThreadTeb(
    _In_ PETHREAD Thread
);

NTKERNELAPI
CCHAR
NTAPI
PsGetThreadFreezeCount(
    _In_ PETHREAD Thread
);

NTKERNELAPI
BOOLEAN
NTAPI
PsGetThreadHardErrorsAreDisabled(
    _In_ PETHREAD Thread
);

#endif // _KERNEL_MODE

VEIL_END()

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
