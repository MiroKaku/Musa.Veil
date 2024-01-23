/*
 * PROJECT:   Veil
 * FILE:      Veil.System.Process.h
 * PURPOSE:   This file is part of Veil.
 *
 * LICENSE:   MIT License
 *
 * DEVELOPER: MiroKaku (kkmi04@outlook.com)
 */

#pragma once
#include "Veil.System.SxS.h"

// Warnings which disabled for compiling
#if _MSC_VER >= 1200
#pragma warning(push)
// nonstandard extension used : nameless struct/union
#pragma warning(disable:4201)
// 'struct_name' : structure was padded due to __declspec(align())
#pragma warning(disable:4324)
// 'enumeration': a forward declaration of an unscoped enumeration must have an
// underlying type (int assumed)
#pragma warning(disable:4471)
#endif

VEIL_BEGIN()

#ifdef _KERNEL_MODE
#define PROCESS_TERMINATE                   0x0001
#define PROCESS_CREATE_THREAD               0x0002
#define PROCESS_SET_SESSIONID               0x0004
#define PROCESS_VM_OPERATION                0x0008
#define PROCESS_VM_READ                     0x0010
#define PROCESS_VM_WRITE                    0x0020
#define PROCESS_CREATE_PROCESS              0x0080
#define PROCESS_SET_QUOTA                   0x0100
#define PROCESS_SET_INFORMATION             0x0200
#define PROCESS_QUERY_INFORMATION           0x0400
#define PROCESS_SET_PORT                    0x0800
#define PROCESS_SUSPEND_RESUME              0x0800
#define PROCESS_QUERY_LIMITED_INFORMATION   0x1000
#else
#ifndef PROCESS_SET_PORT
#define PROCESS_SET_PORT                    0x0800
#endif
#endif

#ifdef _KERNEL_MODE
#define THREAD_QUERY_INFORMATION            0x0040
#define THREAD_SET_THREAD_TOKEN             0x0080
#define THREAD_IMPERSONATE                  0x0100
#define THREAD_DIRECT_IMPERSONATION         0x0200
#else
#ifndef THREAD_ALERT
#define THREAD_ALERT                        0x0004
#endif
#endif

#ifdef _KERNEL_MODE
#define JOB_OBJECT_ASSIGN_PROCESS           0x0001
#define JOB_OBJECT_SET_ATTRIBUTES           0x0002
#define JOB_OBJECT_QUERY                    0x0004
#define JOB_OBJECT_TERMINATE                0x0008
#define JOB_OBJECT_SET_SECURITY_ATTRIBUTES  0x0010
#define JOB_OBJECT_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x3F)
#endif

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

#ifndef FLS_MAXIMUM_AVAILABLE
#define FLS_MAXIMUM_AVAILABLE 128
#endif
#ifndef TLS_MINIMUM_AVAILABLE
#define TLS_MINIMUM_AVAILABLE 64
#endif
#ifndef TLS_EXPANSION_SLOTS
#define TLS_EXPANSION_SLOTS 1024
#endif

// symbols
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
typedef struct _API_SET_NAMESPACE
{
    ULONG Version;
    ULONG Size;
    ULONG Flags;
    ULONG Count;
    ULONG EntryOffset;
    ULONG HashOffset;
    ULONG HashFactor;
} API_SET_NAMESPACE, * PAPI_SET_NAMESPACE;

// private
typedef struct _API_SET_HASH_ENTRY
{
    ULONG Hash;
    ULONG Index;
} API_SET_HASH_ENTRY, * PAPI_SET_HASH_ENTRY;

// private
typedef struct _API_SET_NAMESPACE_ENTRY
{
    ULONG Flags;
    ULONG NameOffset;
    ULONG NameLength;
    ULONG HashedLength;
    ULONG ValueOffset;
    ULONG ValueCount;
} API_SET_NAMESPACE_ENTRY, * PAPI_SET_NAMESPACE_ENTRY;

// private
typedef struct _API_SET_VALUE_ENTRY
{
    ULONG Flags;
    ULONG NameOffset;
    ULONG NameLength;
    ULONG ValueOffset;
    ULONG ValueLength;
} API_SET_VALUE_ENTRY, * PAPI_SET_VALUE_ENTRY;

// private
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

// symbols
typedef struct _PEB
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

    HANDLE Mutant;

    PVOID ImageBaseAddress;
    PPEB_LDR_DATA Ldr;
    PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
    PVOID SubSystemData;
    PVOID ProcessHeap;
    PRTL_CRITICAL_SECTION FastPebLock;
    PSLIST_HEADER AtlThunkSListPtr;
    PVOID IFEOKey;

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
        PVOID KernelCallbackTable;
        PVOID UserSharedInfoPtr;
    };
    ULONG SystemReserved;
    ULONG AtlThunkSListPtr32;
    PAPI_SET_NAMESPACE ApiSetMap;
    ULONG TlsExpansionCounter;
    PVOID TlsBitmap;
    ULONG TlsBitmapBits[2]; // TLS_MINIMUM_AVAILABLE

    PVOID ReadOnlySharedMemoryBase;
    struct _SILO_USER_SHARED_DATA* SharedData; // HotpatchInformation
    PVOID* ReadOnlyStaticServerData;

    PVOID AnsiCodePageData; // PCPTABLEINFO
    PVOID OemCodePageData; // PCPTABLEINFO
    PVOID UnicodeCaseTableData; // PNLSTABLEINFO

    ULONG NumberOfProcessors;
    ULONG NtGlobalFlag;

    ULARGE_INTEGER CriticalSectionTimeout;
    SIZE_T HeapSegmentReserve;
    SIZE_T HeapSegmentCommit;
    SIZE_T HeapDeCommitTotalFreeThreshold;
    SIZE_T HeapDeCommitFreeBlockThreshold;

    ULONG NumberOfHeaps;
    ULONG MaximumNumberOfHeaps;
    PVOID* ProcessHeaps; // PHEAP

    PVOID GdiSharedHandleTable; // PGDI_SHARED_MEMORY
    PVOID ProcessStarterHelper;
    ULONG GdiDCAttributeList;

    PRTL_CRITICAL_SECTION LoaderLock;

    ULONG OSMajorVersion;
    ULONG OSMinorVersion;
    USHORT OSBuildNumber;
    USHORT OSCSDVersion;
    ULONG OSPlatformId;
    ULONG ImageSubsystem;
    ULONG ImageSubsystemMajorVersion;
    ULONG ImageSubsystemMinorVersion;
    KAFFINITY ActiveProcessAffinityMask;
    GDI_HANDLE_BUFFER GdiHandleBuffer;
    PVOID PostProcessInitRoutine;

    PVOID TlsExpansionBitmap;
    ULONG TlsExpansionBitmapBits[32]; // TLS_EXPANSION_SLOTS

    ULONG SessionId;

    ULARGE_INTEGER AppCompatFlags; // KACF_*
    ULARGE_INTEGER AppCompatFlagsUser;
    PVOID pShimData;
    PVOID AppCompatInfo; // APPCOMPAT_EXE_DATA

    UNICODE_STRING CSDVersion;

    PACTIVATION_CONTEXT_DATA ActivationContextData;
    PASSEMBLY_STORAGE_MAP ProcessAssemblyStorageMap;
    PACTIVATION_CONTEXT_DATA SystemDefaultActivationContextData;
    PASSEMBLY_STORAGE_MAP SystemAssemblyStorageMap;

    SIZE_T MinimumStackCommit;

    PVOID SparePointers[2]; // 19H1 (previously FlsCallback to FlsHighIndex)
    PVOID PatchLoaderData;
    PVOID ChpeV2ProcessInfo; // _CHPEV2_PROCESS_INFO

    ULONG AppModelFeatureState;
    ULONG SpareUlongs[2];

    USHORT ActiveCodePage;
    USHORT OemCodePage;
    USHORT UseCaseMapping;
    USHORT UnusedNlsField;

    PVOID WerRegistrationData;
    PVOID WerShipAssertPtr;

    union
    {
        PVOID pContextData; // WIN7
        PVOID pUnused; // WIN10
        PVOID EcCodeBitMap; // WIN11
    };

    PVOID pImageHeaderHash;
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
    PRTL_CRITICAL_SECTION TppWorkerpListLock;
    LIST_ENTRY TppWorkerpList;
    PVOID WaitOnAddressHashTable[128];
    PTELEMETRY_COVERAGE_HEADER TelemetryCoverageHeader; // REDSTONE3
    ULONG CloudFileFlags;
    ULONG CloudFileDiagFlags; // REDSTONE4
    CHAR PlaceholderCompatibilityMode;
    CHAR PlaceholderCompatibilityModeReserved[7];
    struct _LEAP_SECOND_DATA* LeapSecondData; // REDSTONE5
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

} PEB, * PPEB;

#ifdef _WIN64
STATIC_ASSERT(FIELD_OFFSET(PEB, SessionId) == 0x2C0);
//STATIC_ASSERT(sizeof(PEB) == 0x7B0); // REDSTONE3
//STATIC_ASSERT(sizeof(PEB) == 0x7B8); // REDSTONE4
//STATIC_ASSERT(sizeof(PEB) == 0x7C8); // REDSTONE5 // 19H1
STATIC_ASSERT(sizeof(PEB) == 0x7d0); // WIN11
#else
STATIC_ASSERT(FIELD_OFFSET(PEB, SessionId) == 0x1D4);
//STATIC_ASSERT(sizeof(PEB) == 0x468); // REDSTONE3
//STATIC_ASSERT(sizeof(PEB) == 0x470); // REDSTONE4
//STATIC_ASSERT(sizeof(PEB) == 0x480); // REDSTONE5 // 19H1
STATIC_ASSERT(sizeof(PEB) == 0x488); // WIN11
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
    PVOID32 TlsBitmap;
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

STATIC_ASSERT(sizeof(PEB32) == 0x488); // WIN11

#define GDI_BATCH_BUFFER_SIZE 310

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

STATIC_ASSERT(sizeof(GDI_TEB_BATCH32) == 1248);

typedef struct _TEB_ACTIVE_FRAME_CONTEXT
{
    ULONG Flags;
    PSTR FrameName;
} TEB_ACTIVE_FRAME_CONTEXT, * PTEB_ACTIVE_FRAME_CONTEXT;

typedef struct _TEB_ACTIVE_FRAME_CONTEXT32
{
    ULONG Flags;
    char * POINTER_32 FrameName;
} TEB_ACTIVE_FRAME_CONTEXT32, * POINTER_32 PTEB_ACTIVE_FRAME_CONTEXT32;

typedef struct _TEB_ACTIVE_FRAME_CONTEXT_EX
{
    TEB_ACTIVE_FRAME_CONTEXT BasicContext;
    PSTR SourceLocation;
} TEB_ACTIVE_FRAME_CONTEXT_EX, * PTEB_ACTIVE_FRAME_CONTEXT_EX;

typedef struct _TEB_ACTIVE_FRAME_CONTEXT_EX32
{
    TEB_ACTIVE_FRAME_CONTEXT32 BasicContext;
    char* POINTER_32 SourceLocation;
} TEB_ACTIVE_FRAME_CONTEXT_EX32, * PTEB_ACTIVE_FRAME_CONTEXT_EX32;

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

typedef struct _TEB
{
    NT_TIB NtTib;

    PVOID EnvironmentPointer;
    CLIENT_ID ClientId;
    PVOID ActiveRpcHandle;
    PVOID ThreadLocalStoragePointer;
    PPEB ProcessEnvironmentBlock;

    ULONG LastErrorValue;
    ULONG CountOfOwnedCriticalSections;
    PVOID CsrClientThread;
    PVOID Win32ThreadInfo;
    ULONG User32Reserved[26];
    ULONG UserReserved[5];
    PVOID WOW32Reserved;
    LCID CurrentLocale;
    ULONG FpSoftwareStatusRegister;
    PVOID ReservedForDebuggerInstrumentation[16];
#ifdef _WIN64
    PVOID SystemReserved1[30];
#else
    PVOID SystemReserved1[26];
#endif

    CHAR PlaceholderCompatibilityMode;
    BOOLEAN PlaceholderHydrationAlwaysExplicit;
    CHAR PlaceholderReserved[10];

    ULONG ProxiedProcessId;
    ACTIVATION_CONTEXT_STACK ActivationStack;

    UCHAR WorkingOnBehalfTicket[8];
    NTSTATUS ExceptionCode;

    PACTIVATION_CONTEXT_STACK ActivationContextStackPointer;
    ULONG_PTR InstrumentationCallbackSp;
    ULONG_PTR InstrumentationCallbackPreviousPc;
    ULONG_PTR InstrumentationCallbackPreviousSp;
#ifdef _WIN64
    ULONG TxFsContext;
#endif

    BOOLEAN InstrumentationCallbackDisabled;
#ifdef _WIN64
    BOOLEAN UnalignedLoadStoreExceptions;
#endif
#ifndef _WIN64
    UCHAR SpareBytes[23];
    ULONG TxFsContext;
#endif
    GDI_TEB_BATCH GdiTebBatch;
    CLIENT_ID RealClientId;
    HANDLE GdiCachedProcessHandle;
    ULONG GdiClientPID;
    ULONG GdiClientTID;
    PVOID GdiThreadLocalInfo;
    ULONG_PTR Win32ClientInfo[WIN32_CLIENT_INFO_LENGTH];
    PVOID glDispatchTable[233];
    ULONG_PTR glReserved1[29];
    PVOID glReserved2;
    PVOID glSectionInfo;
    PVOID glSection;
    PVOID glTable;
    PVOID glCurrentRC;
    PVOID glContext;

    NTSTATUS LastStatusValue;
    UNICODE_STRING StaticUnicodeString;
    WCHAR StaticUnicodeBuffer[STATIC_UNICODE_BUFFER_LENGTH];

    PVOID DeallocationStack;
    PVOID TlsSlots[TLS_MINIMUM_AVAILABLE];
    LIST_ENTRY TlsLinks;

    PVOID Vdm;
    PVOID ReservedForNtRpc;
    PVOID DbgSsReserved[2];

    ULONG HardErrorMode;
#ifdef _WIN64
    PVOID Instrumentation[11];
#else
    PVOID Instrumentation[9];
#endif
    GUID ActivityId;

    PVOID SubProcessTag;
    PVOID PerflibData;
    PVOID EtwTraceData;
    PVOID WinSockData;
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
    PVOID ReservedForPerf;
    PVOID ReservedForOle; // tagSOleTlsData
    ULONG WaitingOnLoaderLock;
    PVOID SavedPriorityState;
    ULONG_PTR ReservedForCodeCoverage;
    PVOID ThreadPoolData;
    PVOID* TlsExpansionSlots;
#ifdef _WIN64
    PVOID DeallocationBStore;
    PVOID BStoreLimit;
#endif
    ULONG MuiGeneration;
    ULONG IsImpersonating;
    PVOID NlsCache;
    PVOID pShimData;
    ULONG HeapData;
    HANDLE CurrentTransactionHandle;
    PTEB_ACTIVE_FRAME ActiveFrame;
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
    ULONGLONG LastSleepCounter; // Win11
    ULONG SpinCallCount;
    ULONGLONG ExtendedFeatureDisableMask;
} TEB, * PTEB;

STATIC_ASSERT(sizeof(TEB) == (sizeof(void*) == sizeof(__int32) ? 0x1018 : 0x1850)); // WIN11

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
    PVOID32 ReservedForOle; // tagSOleTlsData
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

STATIC_ASSERT(sizeof(TEB32) == 4120);

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
    (NativePages * (PAGE_SIZE_X86NT >> PAGE_SHIFT_X86NT))

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
        // Was called while running under WoW. The current teb is the guest
        // teb.
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
        // Called while runnign under WoW Host, so calculate the position of the
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
//
typedef enum _PROCESSINFOCLASS
{
    ProcessBasicInformation, // q: PROCESS_BASIC_INFORMATION, PROCESS_EXTENDED_BASIC_INFORMATION
    ProcessQuotaLimits, // qs: QUOTA_LIMITS, QUOTA_LIMITS_EX
    ProcessIoCounters, // q: IO_COUNTERS
    ProcessVmCounters, // q: VM_COUNTERS, VM_COUNTERS_EX, VM_COUNTERS_EX2
    ProcessTimes, // q: KERNEL_USER_TIMES
    ProcessBasePriority, // s: KPRIORITY
    ProcessRaisePriority, // s: ULONG
    ProcessDebugPort, // q: HANDLE
    ProcessExceptionPort, // s: PROCESS_EXCEPTION_PORT (requires SeTcbPrivilege)
    ProcessAccessToken, // s: PROCESS_ACCESS_TOKEN
    ProcessLdtInformation, // qs: PROCESS_LDT_INFORMATION // 10
    ProcessLdtSize, // s: PROCESS_LDT_SIZE
    ProcessDefaultHardErrorMode, // qs: ULONG
    ProcessIoPortHandlers, // (kernel-mode only) // s: PROCESS_IO_PORT_HANDLER_INFORMATION
    ProcessPooledUsageAndLimits, // q: POOLED_USAGE_AND_LIMITS
    ProcessWorkingSetWatch, // q: PROCESS_WS_WATCH_INFORMATION[]; s: void
    ProcessUserModeIOPL, // qs: ULONG (requires SeTcbPrivilege)
    ProcessEnableAlignmentFaultFixup, // s: BOOLEAN
    ProcessPriorityClass, // qs: PROCESS_PRIORITY_CLASS
    ProcessWx86Information, // qs: ULONG (requires SeTcbPrivilege) (VdmAllowed)
    ProcessHandleCount, // q: ULONG, PROCESS_HANDLE_INFORMATION // 20
    ProcessAffinityMask, // (q >WIN7)s: KAFFINITY, qs: GROUP_AFFINITY
    ProcessPriorityBoost, // qs: ULONG
    ProcessDeviceMap, // qs: PROCESS_DEVICEMAP_INFORMATION, PROCESS_DEVICEMAP_INFORMATION_EX
    ProcessSessionInformation, // q: PROCESS_SESSION_INFORMATION
    ProcessForegroundInformation, // s: PROCESS_FOREGROUND_BACKGROUND
    ProcessWow64Information, // q: ULONG_PTR
    ProcessImageFileName, // q: UNICODE_STRING
    ProcessLUIDDeviceMapsEnabled, // q: ULONG
    ProcessBreakOnTermination, // qs: ULONG
    ProcessDebugObjectHandle, // q: HANDLE // 30
    ProcessDebugFlags, // qs: ULONG
    ProcessHandleTracing, // q: PROCESS_HANDLE_TRACING_QUERY; s: PROCESS_HANDLE_TRACING_ENABLE[_EX] or void to disable
    ProcessIoPriority, // qs: IO_PRIORITY_HINT
    ProcessExecuteFlags, // qs: ULONG (MEM_EXECUTE_OPTION_*)
    ProcessTlsInformation, // PROCESS_TLS_INFORMATION // ProcessResourceManagement 
    ProcessCookie, // q: ULONG
    ProcessImageInformation, // q: SECTION_IMAGE_INFORMATION
    ProcessCycleTime, // q: PROCESS_CYCLE_TIME_INFORMATION // since VISTA
    ProcessPagePriority, // qs: PAGE_PRIORITY_INFORMATION
    ProcessInstrumentationCallback, // s: PVOID or PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION // 40
    ProcessThreadStackAllocation, // s: PROCESS_STACK_ALLOCATION_INFORMATION, PROCESS_STACK_ALLOCATION_INFORMATION_EX
    ProcessWorkingSetWatchEx, // q: PROCESS_WS_WATCH_INFORMATION_EX[]; s: void
    ProcessImageFileNameWin32, // q: UNICODE_STRING
    ProcessImageFileMapping, // q: HANDLE (input)
    ProcessAffinityUpdateMode, // qs: PROCESS_AFFINITY_UPDATE_MODE
    ProcessMemoryAllocationMode, // qs: PROCESS_MEMORY_ALLOCATION_MODE
    ProcessGroupInformation, // q: USHORT[]
    ProcessTokenVirtualizationEnabled, // s: ULONG
    ProcessConsoleHostProcess, // qs: ULONG_PTR // ProcessOwnerInformation
    ProcessWindowInformation, // q: PROCESS_WINDOW_INFORMATION // 50
    ProcessHandleInformation, // q: PROCESS_HANDLE_SNAPSHOT_INFORMATION // since WIN8
    ProcessMitigationPolicy, // s: PROCESS_MITIGATION_POLICY_INFORMATION
    ProcessDynamicFunctionTableInformation, // s: PROCESS_DYNAMIC_FUNCTION_TABLE_INFORMATION
    ProcessHandleCheckingMode, // qs: ULONG; s: 0 disables, otherwise enables
    ProcessKeepAliveCount, // q: PROCESS_KEEPALIVE_COUNT_INFORMATION
    ProcessRevokeFileHandles, // s: PROCESS_REVOKE_FILE_HANDLES_INFORMATION
    ProcessWorkingSetControl, // s: PROCESS_WORKING_SET_CONTROL (requires SeDebugPrivilege)
    ProcessHandleTable, // q: ULONG[] // since WINBLUE
    ProcessCheckStackExtentsMode, // qs: ULONG // KPROCESS->CheckStackExtents (CFG)
    ProcessCommandLineInformation, // q: UNICODE_STRING // 60
    ProcessProtectionInformation, // q: PS_PROTECTION
    ProcessMemoryExhaustion, // s: PROCESS_MEMORY_EXHAUSTION_INFO // since THRESHOLD
    ProcessFaultInformation, // s: PROCESS_FAULT_INFORMATION
    ProcessTelemetryIdInformation, // q: PROCESS_TELEMETRY_ID_INFORMATION
    ProcessCommitReleaseInformation, // qs: PROCESS_COMMIT_RELEASE_INFORMATION
    ProcessDefaultCpuSetsInformation, // qs: SYSTEM_CPU_SET_INFORMATION[5]
    ProcessAllowedCpuSetsInformation, // qs: SYSTEM_CPU_SET_INFORMATION[5]
    ProcessSubsystemProcess,
    ProcessJobMemoryInformation, // q: PROCESS_JOB_MEMORY_INFO
    ProcessInPrivate, // q: BOOLEAN; s: void // ETW // since THRESHOLD2 // 70
    ProcessRaiseUMExceptionOnInvalidHandleClose, // qs: ULONG; s: 0 disables, otherwise enables
    ProcessIumChallengeResponse,
    ProcessChildProcessInformation, // q: PROCESS_CHILD_PROCESS_INFORMATION
    ProcessHighGraphicsPriorityInformation, // qs: BOOLEAN (requires SeTcbPrivilege)
    ProcessSubsystemInformation, // q: SUBSYSTEM_INFORMATION_TYPE // since REDSTONE2
    ProcessEnergyValues, // q: PROCESS_ENERGY_VALUES, PROCESS_EXTENDED_ENERGY_VALUES
    ProcessPowerThrottlingState, // qs: POWER_THROTTLING_PROCESS_STATE
    ProcessReserved3Information, // ProcessActivityThrottlePolicy // PROCESS_ACTIVITY_THROTTLE_POLICY
    ProcessWin32kSyscallFilterInformation, // q: WIN32K_SYSCALL_FILTER
    ProcessDisableSystemAllowedCpuSets, // s: BOOLEAN // 80
    ProcessWakeInformation, // q: PROCESS_WAKE_INFORMATION
    ProcessEnergyTrackingState, // qs: PROCESS_ENERGY_TRACKING_STATE
    ProcessManageWritesToExecutableMemory, // MANAGE_WRITES_TO_EXECUTABLE_MEMORY // since REDSTONE3
    ProcessCaptureTrustletLiveDump,
    ProcessTelemetryCoverage, // q: TELEMETRY_COVERAGE_HEADER; s: TELEMETRY_COVERAGE_POINT
    ProcessEnclaveInformation,
    ProcessEnableReadWriteVmLogging, // qs: PROCESS_READWRITEVM_LOGGING_INFORMATION
    ProcessUptimeInformation, // q: PROCESS_UPTIME_INFORMATION
    ProcessImageSection, // q: HANDLE
    ProcessDebugAuthInformation, // since REDSTONE4 // 90
    ProcessSystemResourceManagement, // s: PROCESS_SYSTEM_RESOURCE_MANAGEMENT
    ProcessSequenceNumber, // q: ULONGLONG
    ProcessLoaderDetour, // since REDSTONE5
    ProcessSecurityDomainInformation, // q: PROCESS_SECURITY_DOMAIN_INFORMATION
    ProcessCombineSecurityDomainsInformation, // s: PROCESS_COMBINE_SECURITY_DOMAINS_INFORMATION
    ProcessEnableLogging, // qs: PROCESS_LOGGING_INFORMATION
    ProcessLeapSecondInformation, // qs: PROCESS_LEAP_SECOND_INFORMATION
    ProcessFiberShadowStackAllocation, // s: PROCESS_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION // since 19H1
    ProcessFreeFiberShadowStackAllocation, // s: PROCESS_FREE_FIBER_SHADOW_STACK_ALLOCATION_INFORMATION
    ProcessAltSystemCallInformation, // s: PROCESS_SYSCALL_PROVIDER_INFORMATION // since 20H1 // 100
    ProcessDynamicEHContinuationTargets, // s: PROCESS_DYNAMIC_EH_CONTINUATION_TARGETS_INFORMATION
    ProcessDynamicEnforcedCetCompatibleRanges, // s: PROCESS_DYNAMIC_ENFORCED_ADDRESS_RANGE_INFORMATION // since 20H2
    ProcessCreateStateChange, // since WIN11
    ProcessApplyStateChange,
    ProcessEnableOptionalXStateFeatures, // s: ULONG64 // optional XState feature bitmask
    ProcessAltPrefetchParam, // since 22H1
    ProcessAssignCpuPartitions,
    ProcessPriorityClassEx, // s: PROCESS_PRIORITY_CLASS_EX
    ProcessMembershipInformation, // q: PROCESS_MEMBERSHIP_INFORMATION
    ProcessEffectiveIoPriority, // q: IO_PRIORITY_HINT
    ProcessEffectivePagePriority, // q: ULONG
    MaxProcessInfoClass
} PROCESSINFOCLASS;

//
// Thread Information Classes
//

typedef enum _THREADINFOCLASS
{
    ThreadBasicInformation, // q: THREAD_BASIC_INFORMATION
    ThreadTimes, // q: KERNEL_USER_TIMES
    ThreadPriority, // s: KPRIORITY (requires SeIncreaseBasePriorityPrivilege)
    ThreadBasePriority, // s: KPRIORITY
    ThreadAffinityMask, // s: KAFFINITY
    ThreadImpersonationToken, // s: HANDLE
    ThreadDescriptorTableEntry, // q: DESCRIPTOR_TABLE_ENTRY (or WOW64_DESCRIPTOR_TABLE_ENTRY)
    ThreadEnableAlignmentFaultFixup, // s: BOOLEAN
    ThreadEventPair,
    ThreadQuerySetWin32StartAddress, // q: ULONG_PTR
    ThreadZeroTlsCell, // s: ULONG // TlsIndex // 10
    ThreadPerformanceCount, // q: LARGE_INTEGER
    ThreadAmILastThread, // q: ULONG
    ThreadIdealProcessor, // s: ULONG
    ThreadPriorityBoost, // qs: ULONG
    ThreadSetTlsArrayAddress, // s: ULONG_PTR // Obsolete
    ThreadIsIoPending, // q: ULONG
    ThreadHideFromDebugger, // q: BOOLEAN; s: void
    ThreadBreakOnTermination, // qs: ULONG
    ThreadSwitchLegacyState, // s: void // NtCurrentThread // NPX/FPU
    ThreadIsTerminated, // q: ULONG // 20
    ThreadLastSystemCall, // q: THREAD_LAST_SYSCALL_INFORMATION
    ThreadIoPriority, // qs: IO_PRIORITY_HINT (requires SeIncreaseBasePriorityPrivilege)
    ThreadCycleTime, // q: THREAD_CYCLE_TIME_INFORMATION
    ThreadPagePriority, // qs: PAGE_PRIORITY_INFORMATION
    ThreadActualBasePriority, // s: LONG (requires SeIncreaseBasePriorityPrivilege)
    ThreadTebInformation, // q: THREAD_TEB_INFORMATION (requires THREAD_GET_CONTEXT + THREAD_SET_CONTEXT)
    ThreadCSwitchMon, // Obsolete
    ThreadCSwitchPmu,
    ThreadWow64Context, // qs: WOW64_CONTEXT, ARM_NT_CONTEXT since 20H1
    ThreadGroupInformation, // qs: GROUP_AFFINITY // 30
    ThreadUmsInformation, // q: THREAD_UMS_INFORMATION // Obsolete
    ThreadCounterProfiling, // q: BOOLEAN; s: THREAD_PROFILING_INFORMATION?
    ThreadIdealProcessorEx, // qs: PROCESSOR_NUMBER; s: previous PROCESSOR_NUMBER on return
    ThreadCpuAccountingInformation, // q: BOOLEAN; s: HANDLE (NtOpenSession) // NtCurrentThread // since WIN8
    ThreadSuspendCount, // q: ULONG // since WINBLUE
    ThreadHeterogeneousCpuPolicy, // q: KHETERO_CPU_POLICY // since THRESHOLD
    ThreadContainerId, // q: GUID
    ThreadNameInformation, // qs: THREAD_NAME_INFORMATION
    ThreadSelectedCpuSets,
    ThreadSystemThreadInformation, // q: SYSTEM_THREAD_INFORMATION // 40
    ThreadActualGroupAffinity, // q: GROUP_AFFINITY // since THRESHOLD2
    ThreadDynamicCodePolicyInfo, // q: ULONG; s: ULONG (NtCurrentThread)
    ThreadExplicitCaseSensitivity, // qs: ULONG; s: 0 disables, otherwise enables
    ThreadWorkOnBehalfTicket, // RTL_WORK_ON_BEHALF_TICKET_EX
    ThreadSubsystemInformation, // q: SUBSYSTEM_INFORMATION_TYPE // since REDSTONE2
    ThreadDbgkWerReportActive, // s: ULONG; s: 0 disables, otherwise enables
    ThreadAttachContainer, // s: HANDLE (job object) // NtCurrentThread
    ThreadManageWritesToExecutableMemory, // MANAGE_WRITES_TO_EXECUTABLE_MEMORY // since REDSTONE3
    ThreadPowerThrottlingState, // POWER_THROTTLING_THREAD_STATE
    ThreadWorkloadClass, // THREAD_WORKLOAD_CLASS // since REDSTONE5 // 50
    ThreadCreateStateChange, // since WIN11
    ThreadApplyStateChange,
    ThreadStrongerBadHandleChecks, // since 22H1
    ThreadEffectiveIoPriority, // q: IO_PRIORITY_HINT
    ThreadEffectivePagePriority, // q: ULONG
    MaxThreadInfoClass
} THREADINFOCLASS;
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

typedef struct _PROCESS_BASIC_INFORMATION
{
    NTSTATUS ExitStatus;
    PPEB PebBaseAddress;
    KAFFINITY AffinityMask;
    KPRIORITY BasePriority;
    HANDLE UniqueProcessId;
    HANDLE InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION, * PPROCESS_BASIC_INFORMATION;

typedef struct _PROCESS_EXTENDED_BASIC_INFORMATION
{
    SIZE_T Size; // set to sizeof structure on input
    PROCESS_BASIC_INFORMATION BasicInfo;
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
            ULONG IsBackground : 1;
            ULONG IsStronglyNamed : 1;
            ULONG IsSecureProcess : 1;
            ULONG IsSubsystemProcess : 1;
            ULONG SpareBits : 23;
        };
    };
} PROCESS_EXTENDED_BASIC_INFORMATION, * PPROCESS_EXTENDED_BASIC_INFORMATION;

typedef struct _VM_COUNTERS
{
    SIZE_T PeakVirtualSize;
    SIZE_T VirtualSize;
    ULONG PageFaultCount;
    SIZE_T PeakWorkingSetSize;
    SIZE_T WorkingSetSize;
    SIZE_T QuotaPeakPagedPoolUsage;
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;
    SIZE_T PeakPagefileUsage;
} VM_COUNTERS, * PVM_COUNTERS;

typedef struct _VM_COUNTERS_EX
{
    SIZE_T PeakVirtualSize;
    SIZE_T VirtualSize;
    ULONG PageFaultCount;
    SIZE_T PeakWorkingSetSize;
    SIZE_T WorkingSetSize;
    SIZE_T QuotaPeakPagedPoolUsage;
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;
    SIZE_T PeakPagefileUsage;
    SIZE_T PrivateUsage;
} VM_COUNTERS_EX, * PVM_COUNTERS_EX;

typedef struct _VM_COUNTERS_EX2
{
    VM_COUNTERS_EX CountersEx;
    SIZE_T PrivateWorkingSetSize;
    SIZE_T SharedCommitUsage;
} VM_COUNTERS_EX2, * PVM_COUNTERS_EX2;

typedef struct _KERNEL_USER_TIMES
{
    LARGE_INTEGER CreateTime;
    LARGE_INTEGER ExitTime;
    LARGE_INTEGER KernelTime;
    LARGE_INTEGER UserTime;
} KERNEL_USER_TIMES, * PKERNEL_USER_TIMES;

typedef struct _POOLED_USAGE_AND_LIMITS
{
    SIZE_T PeakPagedPoolUsage;
    SIZE_T PagedPoolUsage;
    SIZE_T PagedPoolLimit;
    SIZE_T PeakNonPagedPoolUsage;
    SIZE_T NonPagedPoolUsage;
    SIZE_T NonPagedPoolLimit;
    SIZE_T PeakPagefileUsage;
    SIZE_T PagefileUsage;
    SIZE_T PagefileLimit;
} POOLED_USAGE_AND_LIMITS, * PPOOLED_USAGE_AND_LIMITS;

#define PROCESS_EXCEPTION_PORT_ALL_STATE_BITS 0x00000003
#define PROCESS_EXCEPTION_PORT_ALL_STATE_FLAGS ((ULONG_PTR)((1UL << PROCESS_EXCEPTION_PORT_ALL_STATE_BITS) - 1))

typedef struct _PROCESS_EXCEPTION_PORT
{
    _In_ HANDLE ExceptionPortHandle; // Handle to the exception port. No particular access required.
    _Inout_ ULONG StateFlags; // Miscellaneous state flags to be cached along with the exception port in the kernel.
} PROCESS_EXCEPTION_PORT, * PPROCESS_EXCEPTION_PORT;

typedef struct _PROCESS_ACCESS_TOKEN
{
    HANDLE Token; // needs TOKEN_ASSIGN_PRIMARY access
    HANDLE Thread; // handle to initial/only thread; needs THREAD_QUERY_INFORMATION access
} PROCESS_ACCESS_TOKEN, * PPROCESS_ACCESS_TOKEN;
#endif // !_KERNEL_MODE

typedef struct _PROCESS_LDT_INFORMATION
{
    ULONG Start;
    ULONG Length;
    LDT_ENTRY LdtEntries[1];
} PROCESS_LDT_INFORMATION, * PPROCESS_LDT_INFORMATION;

typedef struct _PROCESS_LDT_SIZE
{
    ULONG Length;
} PROCESS_LDT_SIZE, * PPROCESS_LDT_SIZE;

#ifndef _KERNEL_MODE
typedef struct _PROCESS_WS_WATCH_INFORMATION
{
    PVOID FaultingPc;
    PVOID FaultingVa;
} PROCESS_WS_WATCH_INFORMATION, * PPROCESS_WS_WATCH_INFORMATION;
#endif // !_KERNEL_MODE

// psapi:PSAPI_WS_WATCH_INFORMATION_EX
typedef struct _PROCESS_WS_WATCH_INFORMATION_EX
{
    PROCESS_WS_WATCH_INFORMATION BasicInfo;
    ULONG_PTR FaultingThreadId;
    ULONG_PTR Flags;
} PROCESS_WS_WATCH_INFORMATION_EX, * PPROCESS_WS_WATCH_INFORMATION_EX;

#define PROCESS_PRIORITY_CLASS_UNKNOWN      0
#define PROCESS_PRIORITY_CLASS_IDLE         1
#define PROCESS_PRIORITY_CLASS_NORMAL       2
#define PROCESS_PRIORITY_CLASS_HIGH         3
#define PROCESS_PRIORITY_CLASS_REALTIME     4
#define PROCESS_PRIORITY_CLASS_BELOW_NORMAL 5
#define PROCESS_PRIORITY_CLASS_ABOVE_NORMAL 6

typedef struct _PROCESS_PRIORITY_CLASS
{
    BOOLEAN Foreground;
    UCHAR PriorityClass;
} PROCESS_PRIORITY_CLASS, * PPROCESS_PRIORITY_CLASS;

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

typedef struct _PROCESS_FOREGROUND_BACKGROUND
{
    BOOLEAN Foreground;
} PROCESS_FOREGROUND_BACKGROUND, * PPROCESS_FOREGROUND_BACKGROUND;

#ifndef _KERNEL_MODE
typedef struct _PROCESS_DEVICEMAP_INFORMATION
{
    union
    {
        struct
        {
            HANDLE DirectoryHandle; // needs DIRECTORY_TRAVERSE access
        } Set;
        struct
        {
            ULONG DriveMap;  // bit mask
            UCHAR DriveType[32]; // DRIVE_* WinBase.h
        } Query;
    };
} PROCESS_DEVICEMAP_INFORMATION, * PPROCESS_DEVICEMAP_INFORMATION;

#define PROCESS_LUID_DOSDEVICES_ONLY 0x00000001

typedef struct _PROCESS_DEVICEMAP_INFORMATION_EX
{
    union
    {
        struct
        {
            HANDLE DirectoryHandle;
        } Set;
        struct
        {
            ULONG DriveMap;
            UCHAR DriveType[32];
        } Query;
    };
    ULONG Flags; // PROCESS_LUID_DOSDEVICES_ONLY
} PROCESS_DEVICEMAP_INFORMATION_EX, * PPROCESS_DEVICEMAP_INFORMATION_EX;

typedef struct _PROCESS_SESSION_INFORMATION
{
    ULONG SessionId;
} PROCESS_SESSION_INFORMATION, * PPROCESS_SESSION_INFORMATION;

#define PROCESS_HANDLE_EXCEPTIONS_ENABLED 0x00000001

#define PROCESS_HANDLE_RAISE_EXCEPTION_ON_INVALID_HANDLE_CLOSE_DISABLED 0x00000000
#define PROCESS_HANDLE_RAISE_EXCEPTION_ON_INVALID_HANDLE_CLOSE_ENABLED 0x00000001

typedef struct _PROCESS_HANDLE_TRACING_ENABLE
{
    ULONG Flags;
} PROCESS_HANDLE_TRACING_ENABLE, * PPROCESS_HANDLE_TRACING_ENABLE;

#define PROCESS_HANDLE_TRACING_MAX_SLOTS 0x20000

typedef struct _PROCESS_HANDLE_TRACING_ENABLE_EX
{
    ULONG Flags;
    ULONG TotalSlots;
} PROCESS_HANDLE_TRACING_ENABLE_EX, * PPROCESS_HANDLE_TRACING_ENABLE_EX;

#define PROCESS_HANDLE_TRACING_MAX_STACKS   16

#define PROCESS_HANDLE_TRACE_TYPE_OPEN      1
#define PROCESS_HANDLE_TRACE_TYPE_CLOSE     2
#define PROCESS_HANDLE_TRACE_TYPE_BADREF    3

typedef struct _PROCESS_HANDLE_TRACING_ENTRY
{
    HANDLE Handle;
    CLIENT_ID ClientId;
    ULONG Type;
    PVOID Stacks[PROCESS_HANDLE_TRACING_MAX_STACKS];
} PROCESS_HANDLE_TRACING_ENTRY, * PPROCESS_HANDLE_TRACING_ENTRY;

typedef struct _PROCESS_HANDLE_TRACING_QUERY
{
    _In_opt_ HANDLE Handle;
    _Out_ ULONG TotalTraces;
    _Out_ PROCESS_HANDLE_TRACING_ENTRY HandleTrace[1];
} PROCESS_HANDLE_TRACING_QUERY, * PPROCESS_HANDLE_TRACING_QUERY;
#endif // !_KERNEL_MODE

typedef struct _THREAD_TLS_INFORMATION
{
    ULONG Flags;
    PVOID NewTlsData;
    PVOID OldTlsData;
    HANDLE ThreadId;
} THREAD_TLS_INFORMATION, * PTHREAD_TLS_INFORMATION;

typedef enum _PROCESS_TLS_INFORMATION_TYPE
{
    ProcessTlsReplaceIndex,
    ProcessTlsReplaceVector,
    MaxProcessTlsOperation
} PROCESS_TLS_INFORMATION_TYPE, * PPROCESS_TLS_INFORMATION_TYPE;

typedef struct _PROCESS_TLS_INFORMATION
{
    ULONG Flags;
    ULONG OperationType;
    ULONG ThreadDataCount;
    ULONG TlsIndex;
    ULONG PreviousCount;
    THREAD_TLS_INFORMATION ThreadData[1];
} PROCESS_TLS_INFORMATION, * PPROCESS_TLS_INFORMATION;

typedef struct _PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION
{
    ULONG Version;
    ULONG Reserved;
    PVOID Callback;
} PROCESS_INSTRUMENTATION_CALLBACK_INFORMATION, * PPROCESS_INSTRUMENTATION_CALLBACK_INFORMATION;

typedef struct _PROCESS_STACK_ALLOCATION_INFORMATION
{
    SIZE_T ReserveSize;
    SIZE_T ZeroBits;
    PVOID StackBase;
} PROCESS_STACK_ALLOCATION_INFORMATION, * PPROCESS_STACK_ALLOCATION_INFORMATION;

typedef struct _PROCESS_STACK_ALLOCATION_INFORMATION_EX
{
    ULONG PreferredNode;
    ULONG Reserved0;
    ULONG Reserved1;
    ULONG Reserved2;
    PROCESS_STACK_ALLOCATION_INFORMATION AllocInfo;
} PROCESS_STACK_ALLOCATION_INFORMATION_EX, * PPROCESS_STACK_ALLOCATION_INFORMATION_EX;

typedef union _PROCESS_AFFINITY_UPDATE_MODE
{
    ULONG Flags;
    struct
    {
        ULONG EnableAutoUpdate : 1;
        ULONG Permanent : 1;
        ULONG Reserved : 30;
    };
} PROCESS_AFFINITY_UPDATE_MODE, * PPROCESS_AFFINITY_UPDATE_MODE;

typedef union _PROCESS_MEMORY_ALLOCATION_MODE
{
    ULONG Flags;
    struct
    {
        ULONG TopDown : 1;
        ULONG Reserved : 31;
    };
} PROCESS_MEMORY_ALLOCATION_MODE, * PPROCESS_MEMORY_ALLOCATION_MODE;

typedef struct _PROCESS_HANDLE_INFORMATION
{
    ULONG HandleCount;
    ULONG HandleCountHighWatermark;
} PROCESS_HANDLE_INFORMATION, * PPROCESS_HANDLE_INFORMATION;

typedef struct _PROCESS_CYCLE_TIME_INFORMATION
{
    ULONGLONG AccumulatedCycles;
    ULONGLONG CurrentCycleCount;
} PROCESS_CYCLE_TIME_INFORMATION, * PPROCESS_CYCLE_TIME_INFORMATION;

typedef struct _PROCESS_WINDOW_INFORMATION
{
    ULONG WindowFlags;
    USHORT WindowTitleLength;
    WCHAR WindowTitle[1];
} PROCESS_WINDOW_INFORMATION, * PPROCESS_WINDOW_INFORMATION;

typedef struct _PROCESS_HANDLE_TABLE_ENTRY_INFO
{
    HANDLE HandleValue;
    ULONG_PTR HandleCount;
    ULONG_PTR PointerCount;
    ULONG GrantedAccess;
    ULONG ObjectTypeIndex;
    ULONG HandleAttributes;
    ULONG Reserved;
} PROCESS_HANDLE_TABLE_ENTRY_INFO, * PPROCESS_HANDLE_TABLE_ENTRY_INFO;

typedef struct _PROCESS_HANDLE_SNAPSHOT_INFORMATION
{
    ULONG_PTR NumberOfHandles;
    ULONG_PTR Reserved;
    PROCESS_HANDLE_TABLE_ENTRY_INFO Handles[1];
} PROCESS_HANDLE_SNAPSHOT_INFORMATION, * PPROCESS_HANDLE_SNAPSHOT_INFORMATION;

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
typedef struct _PROCESS_DYNAMIC_FUNCTION_TABLE_INFORMATION
{
    struct _DYNAMIC_FUNCTION_TABLE* DynamicFunctionTable;
    BOOLEAN Remove;
} PROCESS_DYNAMIC_FUNCTION_TABLE_INFORMATION, * PPROCESS_DYNAMIC_FUNCTION_TABLE_INFORMATION;

#ifndef _KERNEL_MODE
typedef struct _PROCESS_KEEPALIVE_COUNT_INFORMATION
{
    ULONG WakeCount;
    ULONG NoWakeCount;
} PROCESS_KEEPALIVE_COUNT_INFORMATION, * PPROCESS_KEEPALIVE_COUNT_INFORMATION;

typedef struct _PROCESS_REVOKE_FILE_HANDLES_INFORMATION
{
    UNICODE_STRING TargetDevicePath;
} PROCESS_REVOKE_FILE_HANDLES_INFORMATION, * PPROCESS_REVOKE_FILE_HANDLES_INFORMATION;
#endif // !_KERNEL_MODE

// begin_private

typedef enum _PROCESS_WORKING_SET_OPERATION
{
    ProcessWorkingSetSwap,
    ProcessWorkingSetEmpty,
    ProcessWorkingSetOperationMax
} PROCESS_WORKING_SET_OPERATION;

typedef struct _PROCESS_WORKING_SET_CONTROL
{
    ULONG Version;
    PROCESS_WORKING_SET_OPERATION Operation;
    ULONG Flags;
} PROCESS_WORKING_SET_CONTROL, * PPROCESS_WORKING_SET_CONTROL;

typedef enum _PS_PROTECTED_TYPE
{
    PsProtectedTypeNone,
    PsProtectedTypeProtectedLight,
    PsProtectedTypeProtected,
    PsProtectedTypeMax
} PS_PROTECTED_TYPE;

typedef enum _PS_PROTECTED_SIGNER
{
    PsProtectedSignerNone,
    PsProtectedSignerAuthenticode,
    PsProtectedSignerCodeGen,
    PsProtectedSignerAntimalware,
    PsProtectedSignerLsa,
    PsProtectedSignerWindows,
    PsProtectedSignerWinTcb,
    PsProtectedSignerWinSystem,
    PsProtectedSignerApp,
    PsProtectedSignerMax
} PS_PROTECTED_SIGNER;

#define PS_PROTECTED_SIGNER_MASK 0xFF
#define PS_PROTECTED_AUDIT_MASK 0x08
#define PS_PROTECTED_TYPE_MASK 0x07

// ProtectionLevel.Level = PsProtectedValue(PsProtectedSignerCodeGen, FALSE, PsProtectedTypeProtectedLight)
#define PsProtectedValue(Signer, Audit, Type) ( \
    ((Signer & PS_PROTECTED_SIGNER_MASK) << 4) | \
    ((Audit & PS_PROTECTED_AUDIT_MASK) << 3) | \
    (Type & PS_PROTECTED_TYPE_MASK)\
    )

// InitializePsProtection(&ProtectionLevel, PsProtectedSignerCodeGen, FALSE, PsProtectedTypeProtectedLight)
#define InitializePsProtection(ProtectionLevelPtr, Signer, Audit, Type) { \
    (ProtectionLevelPtr)->Signer = Signer; \
    (ProtectionLevelPtr)->Audit = Audit; \
    (ProtectionLevelPtr)->Type = Type; \
    }

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

typedef struct _PROCESS_FAULT_INFORMATION
{
    ULONG FaultFlags;
    ULONG AdditionalInfo;
} PROCESS_FAULT_INFORMATION, * PPROCESS_FAULT_INFORMATION;

typedef struct _PROCESS_TELEMETRY_ID_INFORMATION
{
    ULONG HeaderSize;
    ULONG ProcessId;
    ULONGLONG ProcessStartKey;
    ULONGLONG CreateTime;
    ULONGLONG CreateInterruptTime;
    ULONGLONG CreateUnbiasedInterruptTime;
    ULONGLONG ProcessSequenceNumber;
    ULONGLONG SessionCreateTime;
    ULONG SessionId;
    ULONG BootId;
    ULONG ImageChecksum;
    ULONG ImageTimeDateStamp;
    ULONG UserSidOffset;
    ULONG ImagePathOffset;
    ULONG PackageNameOffset;
    ULONG RelativeAppNameOffset;
    ULONG CommandLineOffset;
} PROCESS_TELEMETRY_ID_INFORMATION, * PPROCESS_TELEMETRY_ID_INFORMATION;

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

typedef struct _PROCESS_JOB_MEMORY_INFO
{
    ULONGLONG SharedCommitUsage;
    ULONGLONG PrivateCommitUsage;
    ULONGLONG PeakPrivateCommitUsage;
    ULONGLONG PrivateCommitLimit;
    ULONGLONG TotalCommitLimit;
} PROCESS_JOB_MEMORY_INFO, * PPROCESS_JOB_MEMORY_INFO;

typedef struct _PROCESS_CHILD_PROCESS_INFORMATION
{
    BOOLEAN ProhibitChildProcesses;
    BOOLEAN AlwaysAllowSecureChildProcess; // REDSTONE3
    BOOLEAN AuditProhibitChildProcesses;
} PROCESS_CHILD_PROCESS_INFORMATION, * PPROCESS_CHILD_PROCESS_INFORMATION;

#ifndef _KERNEL_MODE
//
// Process resource throttling information
//  NtQueryInformationProcess using ProcessPowerThrottlingState
//

#define POWER_THROTTLING_PROCESS_CURRENT_VERSION 1

#define POWER_THROTTLING_PROCESS_EXECUTION_SPEED 0x1
#define POWER_THROTTLING_PROCESS_DELAYTIMERS 0x2
#define POWER_THROTTLING_PROCESS_IGNORE_TIMER_RESOLUTION 0x4

#define POWER_THROTTLING_PROCESS_VALID_FLAGS ((POWER_THROTTLING_PROCESS_EXECUTION_SPEED | \
                                               POWER_THROTTLING_PROCESS_DELAYTIMERS | \
                                               POWER_THROTTLING_PROCESS_IGNORE_TIMER_RESOLUTION))

typedef struct _POWER_THROTTLING_PROCESS_STATE
{
    ULONG Version;
    ULONG ControlMask;
    ULONG StateMask;
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

typedef struct _PROCESS_WAKE_INFORMATION
{
    ULONGLONG NotificationChannel;
    ULONG WakeCounters[7];
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

typedef struct _POWER_THROTTLING_THREAD_STATE
{
    ULONG Version;
    ULONG ControlMask;
    ULONG StateMask;
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

typedef struct _PROCESS_UPTIME_INFORMATION
{
    ULONGLONG QueryInterruptTime;
    ULONGLONG QueryUnbiasedTime;
    ULONGLONG EndInterruptTime;
    ULONGLONG TimeSinceCreation;
    ULONGLONG Uptime;
    ULONGLONG SuspendedTime;
    struct
    {
        ULONG HangCount : 4;
        ULONG GhostCount : 4;
        ULONG Crashed : 1;
        ULONG Terminated : 1;
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
        ULONG Reserved : 26;
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
typedef struct _PROCESS_MEMBERSHIP_INFORMATION
{
    ULONG ServerSiloId;
} PROCESS_MEMBERSHIP_INFORMATION, * PPROCESS_MEMBERSHIP_INFORMATION;
#endif

// end_private

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryPortInformationProcess(
    VOID
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwQueryPortInformationProcess(
    VOID
);

//
// Thread information structures
//

typedef struct _THREAD_BASIC_INFORMATION
{
    NTSTATUS ExitStatus;
    PTEB TebBaseAddress;
    CLIENT_ID ClientId;
    KAFFINITY AffinityMask;
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

typedef struct _THREAD_CYCLE_TIME_INFORMATION
{
    ULONGLONG AccumulatedCycles;
    ULONGLONG CurrentCycleCount;
} THREAD_CYCLE_TIME_INFORMATION, * PTHREAD_CYCLE_TIME_INFORMATION;

typedef struct _THREAD_TEB_INFORMATION
{
    PVOID TebInformation; // buffer to place data in
    ULONG TebOffset; // offset in TEB to begin reading from
    ULONG BytesToRead; // number of bytes to read
} THREAD_TEB_INFORMATION, * PTHREAD_TEB_INFORMATION;

// symbols
typedef struct _COUNTER_READING
{
    HARDWARE_COUNTER_TYPE Type;
    ULONG Index;
    ULONG64 Start;
    ULONG64 Total;
} COUNTER_READING, * PCOUNTER_READING;

// symbols
typedef struct _THREAD_PERFORMANCE_DATA
{
    USHORT Size;
    USHORT Version;
    PROCESSOR_NUMBER ProcessorNumber;
    ULONG ContextSwitches;
    ULONG HwCountersCount;
    ULONG64 UpdateCount;
    ULONG64 WaitReasonBitMap;
    ULONG64 HardwareCounters;
    COUNTER_READING CycleTime;
    COUNTER_READING HwCounters[MAX_HW_COUNTERS];
} THREAD_PERFORMANCE_DATA, * PTHREAD_PERFORMANCE_DATA;

typedef struct _THREAD_PROFILING_INFORMATION
{
    ULONG64 HardwareCounters;
    ULONG Flags;
    ULONG Enable;
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

//
// Processes
//

#ifndef STARTF_HASSHELLDATA
#define STARTF_HASSHELLDATA 0x00000400
#endif

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateProcess(
    _Out_ PHANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
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
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ParentProcess,
    _In_ BOOLEAN InheritObjectTable,
    _In_opt_ HANDLE SectionHandle,
    _In_opt_ HANDLE DebugPort,
    _In_opt_ HANDLE TokenHandle
);

// begin_rev
#define PROCESS_CREATE_FLAGS_BREAKAWAY              0x00000001 // NtCreateProcessEx & NtCreateUserProcess
#define PROCESS_CREATE_FLAGS_NO_DEBUG_INHERIT       0x00000002 // NtCreateProcessEx & NtCreateUserProcess
#define PROCESS_CREATE_FLAGS_INHERIT_HANDLES        0x00000004 // NtCreateProcessEx & NtCreateUserProcess
#define PROCESS_CREATE_FLAGS_OVERRIDE_ADDRESS_SPACE 0x00000008 // NtCreateProcessEx only
#define PROCESS_CREATE_FLAGS_LARGE_PAGES            0x00000010 // NtCreateProcessEx only, requires SeLockMemory
#define PROCESS_CREATE_FLAGS_LARGE_PAGE_SYSTEM_DLL  0x00000020 // NtCreateProcessEx only, requires SeLockMemory
#define PROCESS_CREATE_FLAGS_PROTECTED_PROCESS      0x00000040 // NtCreateUserProcess only
#define PROCESS_CREATE_FLAGS_CREATE_SESSION         0x00000080 // NtCreateProcessEx & NtCreateUserProcess, requires SeLoadDriver
#define PROCESS_CREATE_FLAGS_INHERIT_FROM_PARENT    0x00000100 // NtCreateProcessEx & NtCreateUserProcess
#define PROCESS_CREATE_FLAGS_SUSPENDED              0x00000200 // NtCreateProcessEx & NtCreateUserProcess
#define PROCESS_CREATE_FLAGS_FORCE_BREAKAWAY        0x00000400 // NtCreateProcessEx & NtCreateUserProcess, requires SeTcb
#define PROCESS_CREATE_FLAGS_MINIMAL_PROCESS        0x00000800 // NtCreateProcessEx only
#define PROCESS_CREATE_FLAGS_RELEASE_SECTION        0x00001000 // NtCreateProcessEx & NtCreateUserProcess
#define PROCESS_CREATE_FLAGS_AUXILIARY_PROCESS      0x00008000 // NtCreateProcessEx & NtCreateUserProcess, requires SeTcb
#define PROCESS_CREATE_FLAGS_CREATE_STORE           0x00020000 // NtCreateProcessEx & NtCreateUserProcess
#define PROCESS_CREATE_FLAGS_USE_PROTECTED_ENVIRONMENT 0x00040000 // NtCreateProcessEx & NtCreateUserProcess
// end_rev

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateProcessEx(
    _Out_ PHANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
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
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ParentProcess,
    _In_ ULONG Flags,
    _In_opt_ HANDLE SectionHandle,
    _In_opt_ HANDLE DebugPort,
    _In_opt_ HANDLE ExceptionPort,
    _Reserved_ ULONG Reserved // JobMemberLevel
);

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

#else // ifdef _KERNEL_MODE

#define NtCurrentProcessId()    PsGetCurrentProcessId()
#define ZwCurrentProcessId()    NtCurrentProcessId()
#define NtCurrentThreadId()     PsGetCurrentThreadId()
#define ZwCurrentThreadId()     NtCurrentThreadId()

#endif // _KERNEL_MODE

// Windows 8 and above
#define NtCurrentProcessToken()         ((HANDLE)(LONG_PTR)-4) // NtOpenProcessToken(NtCurrentProcess())
#define NtCurrentThreadToken()          ((HANDLE)(LONG_PTR)-5) // NtOpenThreadToken(NtCurrentThread())
#define NtCurrentThreadEffectiveToken() ((HANDLE)(LONG_PTR)-6) // NtOpenThreadToken(NtCurrentThread()) + NtOpenProcessToken(NtCurrentProcess())

#define NtCurrentSilo() ( (HANDLE)(LONG_PTR) -1 )

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

#if (NTDDI_VERSION >= NTDDI_WS03)
#define PROCESS_GET_NEXT_FLAGS_PREVIOUS_PROCESS 0x00000001

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

#define STATECHANGE_SET_ATTRIBUTES 0x0001

typedef enum _PROCESS_STATE_CHANGE_TYPE
{
    ProcessStateChangeSuspend,
    ProcessStateChangeResume,
    ProcessStateChangeMax,
} PROCESS_STATE_CHANGE_TYPE, * PPROCESS_STATE_CHANGE_TYPE;

#if (NTDDI_VERSION >= NTDDI_WIN10_CO)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateProcessStateChange(
    _Out_ PHANDLE ProcessStateChangeHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ProcessHandle,
    _In_opt_ ULONG64 Reserved
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateProcessStateChange(
    _Out_ PHANDLE ProcessStateChangeHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ProcessHandle,
    _In_opt_ ULONG64 Reserved
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtChangeProcessState(
    _In_ HANDLE ProcessStateChangeHandle,
    _In_ HANDLE ProcessHandle,
    _In_ PROCESS_STATE_CHANGE_TYPE StateChangeType,
    _In_opt_ PVOID ExtendedInformation,
    _In_opt_ SIZE_T ExtendedInformationLength,
    _In_opt_ ULONG64 Reserved
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
    _In_opt_ ULONG64 Reserved
);
#endif

typedef enum _THREAD_STATE_CHANGE_TYPE
{
    ThreadStateChangeSuspend,
    ThreadStateChangeResume,
    ThreadStateChangeMax,
} THREAD_STATE_CHANGE_TYPE, * PTHREAD_STATE_CHANGE_TYPE;

#if (NTDDI_VERSION >= NTDDI_WIN10_CO)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateThreadStateChange(
    _Out_ PHANDLE ThreadStateChangeHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ThreadHandle,
    _In_opt_ ULONG64 Reserved
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateThreadStateChange(
    _Out_ PHANDLE ThreadStateChangeHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ThreadHandle,
    _In_opt_ ULONG64 Reserved
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtChangeThreadState(
    _In_ HANDLE ThreadStateChangeHandle,
    _In_ HANDLE ThreadHandle,
    _In_ THREAD_STATE_CHANGE_TYPE StateChangeType,
    _In_opt_ PVOID ExtendedInformation,
    _In_opt_ SIZE_T ExtendedInformationLength,
    _In_opt_ ULONG64 Reserved
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
    _In_opt_ ULONG64 Reserved
);
#endif

//
// Threads
//

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateThread(
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
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
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ProcessHandle,
    _Out_ PCLIENT_ID ClientId,
    _In_ PCONTEXT ThreadContext,
    _In_ PINITIAL_TEB InitialTeb,
    _In_ BOOLEAN CreateSuspended
);

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

typedef VOID(NTAPI*PPS_APC_ROUTINE)(
    _In_opt_ PVOID ApcArgument1,
    _In_opt_ PVOID ApcArgument2,
    _In_opt_ PVOID ApcArgument3
    );

inline
PVOID Wow64EncodeApcRoutine(_In_ PVOID ApcRoutine)
{
    if (ApcRoutine <= (PVOID)(SIZE_T)0xFFFFFFFF) {
        ApcRoutine = (PVOID)(-((LONG_PTR)ApcRoutine << 2));
    }
    return ApcRoutine;
}

inline
PVOID Wow64DecodeApcRoutine(_In_ PVOID ApcRoutine)
{
    PVOID DecodedApcRoutine = (PVOID)((-(LONG_PTR)ApcRoutine) >> 2);
    if (DecodedApcRoutine > (PVOID)(SIZE_T)0xFFFFFFFF) {
        DecodedApcRoutine = ApcRoutine;
    }
    return DecodedApcRoutine;
}

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueueApcThread(
    _In_ HANDLE ThreadHandle,
    _In_ PPS_APC_ROUTINE ApcRoutine,
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

#if (NTDDI_VERSION >= ntddi_WIN7)
#define QUEUE_USER_APC_SPECIAL_USER_APC ((HANDLE)0x1)

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueueApcThreadEx(
    _In_ HANDLE ThreadHandle,
    _In_opt_ HANDLE ReserveHandle, // NtAllocateReserveObject // SPECIAL_USER_APC
    _In_ PPS_APC_ROUTINE ApcRoutine,
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
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_CO)

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

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueueApcThreadEx2(
    _In_ HANDLE ThreadHandle,
    _In_opt_ HANDLE ReserveHandle, // NtAllocateReserveObject
    _In_ ULONG ApcFlags, // QUEUE_USER_APC_FLAGS
    _In_ PPS_APC_ROUTINE ApcRoutine,
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
#endif // (NTDDI_VERSION >= NTDDI_WIN10_CO)

#if (NTDDI_VERSION >= NTDDI_WIN8)
// rev
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

// rev
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtWaitForAlertByThreadId(
    _In_ PVOID Address,
    _In_opt_ PLARGE_INTEGER Timeout
);

// rev
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwWaitForAlertByThreadId(
    _In_ PVOID Address,
    _In_opt_ PLARGE_INTEGER Timeout
);
#endif

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

// private
typedef struct _PROC_THREAD_ATTRIBUTE_LIST
{
    ULONG PresentFlags;
    ULONG AttributeCount;
    ULONG LastAttribute;
    ULONG SpareUlong0;
    PPROC_THREAD_ATTRIBUTE ExtendedFlagsAttribute;
    PROC_THREAD_ATTRIBUTE Attributes[1];
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
    PsAttributeParentProcess, // in HANDLE
    PsAttributeDebugObject, // in HANDLE
    PsAttributeToken, // in HANDLE
    PsAttributeClientId, // out PCLIENT_ID
    PsAttributeTebAddress, // out PTEB *
    PsAttributeImageName, // in PWSTR
    PsAttributeImageInfo, // out PSECTION_IMAGE_INFORMATION
    PsAttributeMemoryReserve, // in PPS_MEMORY_RESERVE
    PsAttributePriorityClass, // in UCHAR
    PsAttributeErrorMode, // in ULONG
    PsAttributeStdHandleInfo, // 10, in PPS_STD_HANDLE_INFO
    PsAttributeHandleList, // in HANDLE[]
    PsAttributeGroupAffinity, // in PGROUP_AFFINITY
    PsAttributePreferredNode, // in PUSHORT
    PsAttributeIdealProcessor, // in PPROCESSOR_NUMBER
    PsAttributeUmsThread, // ? in PUMS_CREATE_THREAD_ATTRIBUTES
    PsAttributeMitigationOptions, // in PPS_MITIGATION_OPTIONS_MAP (PROCESS_CREATION_MITIGATION_POLICY_*) // since WIN8
    PsAttributeProtectionLevel, // in PS_PROTECTION // since WINBLUE
    PsAttributeSecureProcess, // in PPS_TRUSTLET_CREATE_ATTRIBUTES, since THRESHOLD
    PsAttributeJobList, // in HANDLE[]
    PsAttributeChildProcessPolicy, // 20, in PULONG (PROCESS_CREATION_CHILD_PROCESS_*) // since THRESHOLD2
    PsAttributeAllApplicationPackagesPolicy, // in PULONG (PROCESS_CREATION_ALL_APPLICATION_PACKAGES_*) // since REDSTONE
    PsAttributeWin32kFilter, // in PWIN32K_SYSCALL_FILTER
    PsAttributeSafeOpenPromptOriginClaim, // in SE_SAFE_OPEN_PROMPT_RESULTS
    PsAttributeBnoIsolation, // in PPS_BNO_ISOLATION_PARAMETERS // since REDSTONE2
    PsAttributeDesktopAppPolicy, // in PULONG (PROCESS_CREATION_DESKTOP_APP_*)
    PsAttributeChpe, // in BOOLEAN // since REDSTONE3
    PsAttributeMitigationAuditOptions, // in PPS_MITIGATION_AUDIT_OPTIONS_MAP (PROCESS_CREATION_MITIGATION_AUDIT_POLICY_*) // since 21H1
    PsAttributeMachineType, // in USHORT // since 21H2
    PsAttributeComponentFilter,
    PsAttributeEnableOptionalXStateFeatures, // since WIN11
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

typedef struct _PS_TRUSTLET_ATTRIBUTE_TYPE
{
    union
    {
        struct
        {
            UCHAR Version;
            UCHAR DataCount;
            UCHAR SemanticType;
            PS_TRUSTLET_ATTRIBUTE_ACCESSRIGHTS AccessRights;
        };
        ULONG AttributeType;
    };
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

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateUserProcess(
    _Out_ PHANDLE ProcessHandle,
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK ProcessDesiredAccess,
    _In_ ACCESS_MASK ThreadDesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ProcessObjectAttributes,
    _In_opt_ POBJECT_ATTRIBUTES ThreadObjectAttributes,
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
    _In_opt_ POBJECT_ATTRIBUTES ProcessObjectAttributes,
    _In_opt_ POBJECT_ATTRIBUTES ThreadObjectAttributes,
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
#define THREAD_CREATE_FLAGS_LOADER_WORKER           0x00000010 // NtCreateThreadEx only
#define THREAD_CREATE_FLAGS_SKIP_LOADER_INIT        0x00000020 // NtCreateThreadEx only
#define THREAD_CREATE_FLAGS_BYPASS_PROCESS_FREEZE   0x00000040 // NtCreateThreadEx only
// end_rev

typedef NTSTATUS(NTAPI* PUSER_THREAD_START_ROUTINE)(
    _In_ PVOID ThreadParameter
    );

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateThreadEx(
    _Out_ PHANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
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
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
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
    JobObjectBasicAccountingInformation, // JOBOBJECT_BASIC_ACCOUNTING_INFORMATION
    JobObjectBasicLimitInformation, // JOBOBJECT_BASIC_LIMIT_INFORMATION
    JobObjectBasicProcessIdList, // JOBOBJECT_BASIC_PROCESS_ID_LIST
    JobObjectBasicUIRestrictions, // JOBOBJECT_BASIC_UI_RESTRICTIONS
    JobObjectSecurityLimitInformation, // JOBOBJECT_SECURITY_LIMIT_INFORMATION
    JobObjectEndOfJobTimeInformation = 6, // JOBOBJECT_END_OF_JOB_TIME_INFORMATION
    JobObjectAssociateCompletionPortInformation, // JOBOBJECT_ASSOCIATE_COMPLETION_PORT
    JobObjectBasicAndIoAccountingInformation, // JOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION
    JobObjectExtendedLimitInformation, // JOBOBJECT_EXTENDED_LIMIT_INFORMATION
    JobObjectJobSetInformation, // JOBOBJECT_JOBSET_INFORMATION
    JobObjectGroupInformation = 11, // USHORT
    JobObjectNotificationLimitInformation, // JOBOBJECT_NOTIFICATION_LIMIT_INFORMATION
    JobObjectLimitViolationInformation, // JOBOBJECT_LIMIT_VIOLATION_INFORMATION
    JobObjectGroupInformationEx, // GROUP_AFFINITY (ARRAY)
    JobObjectCpuRateControlInformation, // JOBOBJECT_CPU_RATE_CONTROL_INFORMATION
    JobObjectCompletionFilter = 16,
    JobObjectCompletionCounter,
    JobObjectFreezeInformation, // JOBOBJECT_FREEZE_INFORMATION
    JobObjectExtendedAccountingInformation, // JOBOBJECT_EXTENDED_ACCOUNTING_INFORMATION
    JobObjectWakeInformation, // JOBOBJECT_WAKE_INFORMATION
    JobObjectBackgroundInformation = 21,
    JobObjectSchedulingRankBiasInformation,
    JobObjectTimerVirtualizationInformation,
    JobObjectCycleTimeNotification,
    JobObjectClearEvent,
    JobObjectInterferenceInformation = 26, // JOBOBJECT_INTERFERENCE_INFORMATION
    JobObjectClearPeakJobMemoryUsed,
    JobObjectMemoryUsageInformation, // JOBOBJECT_MEMORY_USAGE_INFORMATION // JOBOBJECT_MEMORY_USAGE_INFORMATION_V2
    JobObjectSharedCommit,
    JobObjectContainerId,
    JobObjectIoRateControlInformation = 31,
    JobObjectNetRateControlInformation, // JOBOBJECT_NET_RATE_CONTROL_INFORMATION
    JobObjectNotificationLimitInformation2, // JOBOBJECT_NOTIFICATION_LIMIT_INFORMATION_2
    JobObjectLimitViolationInformation2, // JOBOBJECT_LIMIT_VIOLATION_INFORMATION_2
    JobObjectCreateSilo,
    JobObjectSiloBasicInformation = 36, // SILOOBJECT_BASIC_INFORMATION
    JobObjectSiloRootDirectory, // SILOOBJECT_ROOT_DIRECTORY
    JobObjectServerSiloBasicInformation, // SERVERSILO_BASIC_INFORMATION
    JobObjectServerSiloUserSharedData, // SILO_USER_SHARED_DATA
    JobObjectServerSiloInitialize,
    JobObjectServerSiloRunningState = 41,
    JobObjectIoAttribution,
    JobObjectMemoryPartitionInformation,
    JobObjectContainerTelemetryId,
    JobObjectSiloSystemRoot,
    JobObjectEnergyTrackingState = 46, // JOBOBJECT_ENERGY_TRACKING_STATE
    JobObjectThreadImpersonationInformation,
    JobObjectIoPriorityLimit,
    JobObjectPagePriorityLimit,
    MaxJobObjectInfoClass
}JOBOBJECTINFOCLASS;
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
#define JobObjectCompletionFilter                   ((_JOBOBJECTINFOCLASS)16)
#define JobObjectCompletionCounter                  ((_JOBOBJECTINFOCLASS)17)
#define JobObjectFreezeInformation                  ((_JOBOBJECTINFOCLASS)18) // JOBOBJECT_FREEZE_INFORMATION
#define JobObjectExtendedAccountingInformation      ((_JOBOBJECTINFOCLASS)19) // JOBOBJECT_EXTENDED_ACCOUNTING_INFORMATION
#define JobObjectWakeInformation                    ((_JOBOBJECTINFOCLASS)20) // JOBOBJECT_WAKE_INFORMATION
#define JobObjectBackgroundInformation              ((_JOBOBJECTINFOCLASS)21)
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
#define JobObjectCreateSilo                         ((_JOBOBJECTINFOCLASS)35)
#define JobObjectSiloBasicInformation               ((_JOBOBJECTINFOCLASS)36) // SILOOBJECT_BASIC_INFORMATION
#define JobObjectSiloRootDirectory                  ((_JOBOBJECTINFOCLASS)37) // SILOOBJECT_ROOT_DIRECTORY
#define JobObjectServerSiloBasicInformation         ((_JOBOBJECTINFOCLASS)38) // SERVERSILO_BASIC_INFORMATION
#define JobObjectServerSiloUserSharedData           ((_JOBOBJECTINFOCLASS)39) // SILO_USER_SHARED_DATA // NtQueryInformationJobObject(NULL, 39, Buffer, sizeof(SILO_USER_SHARED_DATA), 0);
#define JobObjectServerSiloInitialize               ((_JOBOBJECTINFOCLASS)40) // SERVERSILO_INIT_INFORMATION
#define JobObjectServerSiloRunningState             ((_JOBOBJECTINFOCLASS)41)
#define JobObjectIoAttribution                      ((_JOBOBJECTINFOCLASS)42) // JOBOBJECT_IO_ATTRIBUTION_INFORMATION
#define JobObjectMemoryPartitionInformation         ((_JOBOBJECTINFOCLASS)43)
#define JobObjectContainerTelemetryId               ((_JOBOBJECTINFOCLASS)44)
#define JobObjectSiloSystemRoot                     ((_JOBOBJECTINFOCLASS)45)
#define JobObjectEnergyTrackingState                ((_JOBOBJECTINFOCLASS)46) // JOBOBJECT_ENERGY_TRACKING_STATE
#define JobObjectThreadImpersonationInformation     ((_JOBOBJECTINFOCLASS)47)
#define JobObjectIoPriorityLimit                    ((_JOBOBJECTINFOCLASS)48) // JOBOBJECT_IO_PRIORITY_LIMIT
#define JobObjectPagePriorityLimit                  ((_JOBOBJECTINFOCLASS)49) // JOBOBJECT_PAGE_PRIORITY_LIMIT
#define MaxJobObjectInfoClass                       ((_JOBOBJECTINFOCLASS)50)
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
    ULONG64 WakeCounters[7];
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
typedef struct _JOBOBJECT_WAKE_FILTER
{
    ULONG HighEdgeFilter;
    ULONG LowEdgeFilter;
} JOBOBJECT_WAKE_FILTER, * PJOBOBJECT_WAKE_FILTER;

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
} SERVERSILO_INIT_INFORMATION, * PSERVERSILO_INIT_INFORMATION;

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

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateJobObject(
    _Out_ PHANDLE JobHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateJobObject(
    _Out_ PHANDLE JobHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenJobObject(
    _Out_ PHANDLE JobHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwOpenJobObject(
    _Out_ PHANDLE JobHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
);

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

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAllocateReserveObject(
    _Out_ PHANDLE MemoryReserveHandle,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ MEMORY_RESERVE_TYPE Type
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAllocateReserveObject(
    _Out_ PHANDLE MemoryReserveHandle,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ MEMORY_RESERVE_TYPE Type
);

// Process snapshotting

#ifndef _KERNEL_MODE
#if (NTDDI_VERSION >= NTDDI_WINBLUE)
// rev
NTSYSCALLAPI
NTSTATUS
NTAPI
PssNtCaptureSnapshot(
    _Out_ PHANDLE SnapshotHandle,
    _In_ HANDLE ProcessHandle,
    _In_ ULONG CaptureFlags,
    _In_ ULONG ThreadContextFlags
);
#endif
#endif // !_KERNEL_MODE

// rev
#define MEMORY_BULK_INFORMATION_FLAG_BASIC 0x00000001

// rev
typedef struct _NTPSS_MEMORY_BULK_INFORMATION
{
    ULONG QueryFlags;
    ULONG NumberOfEntries;
    PVOID NextValidAddress;
} NTPSS_MEMORY_BULK_INFORMATION, * PNTPSS_MEMORY_BULK_INFORMATION;

#if (NTDDI_VERSION >= NTDDI_WIN10_VB)

// rev
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
