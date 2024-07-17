/*
 * PROJECT:   Veil
 * FILE:      Veil.System.Etw.h
 * PURPOSE:   This file is part of Veil.
 *
 * LICENSE:   MIT License
 *
 * DEVELOPER: MeeSong (kkmi04@outlook.com)
 */

#pragma once

// Warnings which disabled for compiling
#if _MSC_VER >= 1200
#pragma warning(push)
// nonstandard extension used : nameless struct/union
#pragma warning(disable:4201)
// nonstandard extension used : bit field other than int
#pragma warning(disable:4214)
// 'struct_name' : structure was padded due to __declspec(align())
#pragma warning(disable:4324)
// 'enumeration': a forward declaration of an unscoped enumeration must have an
// underlying type (int assumed)
#pragma warning(disable:4471)
#endif

#include <initguid.h>
#include <wmistr.h>
#include <evntrace.h>

#if defined(_KERNEL_MODE)
#ifndef _ETW_KM_
#define _ETW_KM_
#endif
#endif

#include <evntprov.h>

VEIL_BEGIN()

//
// Circular Kernel Context Logger
// CKCLGuid is used to identify a event tracing session
//
DEFINE_GUID( /* 54dea73a-ed1f-42a4-af713e63d056f174 */
    CKCLGuid,
    0x54dea73a,
    0xed1f,
    0x42a4,
    0xaf, 0x71, 0x3e, 0x63, 0xd0, 0x56, 0xf1, 0x74
);

#define CKCL_LOGGER_NAMEW L"Circular Kernel Context Logger"

//
// Trace
//

#define EVENT_TRACE_CLOCK_RAW           0x00000000  // Use Raw timestamp
#define EVENT_TRACE_CLOCK_PERFCOUNTER   0x00000001  // Use HighPerfClock (Default)
#define EVENT_TRACE_CLOCK_SYSTEMTIME    0x00000002  // Use SystemTime
#define EVENT_TRACE_CLOCK_CPUCYCLE      0x00000003  // Use CPU cycle counter
#define EVENT_TRACE_CLOCK_MAX           EVENT_TRACE_CLOCK_CPUCYCLE


#if defined(_EVNTRACE_KERNEL_MODE)
typedef struct _EVENT_TRACE_PROPERTIES {
    WNODE_HEADER Wnode;
    //
    // data provided by caller
    ULONG BufferSize;                       // buffer size for logging (kbytes)
    ULONG MinimumBuffers;                   // minimum to preallocate
    ULONG MaximumBuffers;                   // maximum buffers allowed
    ULONG MaximumFileSize;                  // maximum logfile size (in MBytes)
    ULONG LogFileMode;                      // sequential, circular
    ULONG FlushTimer;                       // buffer flush timer, in seconds
    ULONG EnableFlags;                      // trace enable flags
    union {
        LONG  AgeLimit;                     // unused
        LONG  FlushThreshold;               // Number of buffers to fill before flushing
    } DUMMYUNIONNAME;

    // data returned to caller
    ULONG NumberOfBuffers;                  // no of buffers in use
    ULONG FreeBuffers;                      // no of buffers free
    ULONG EventsLost;                       // event records lost
    ULONG BuffersWritten;                   // no of buffers written to file
    ULONG LogBuffersLost;                   // no of logfile write failures
    ULONG RealTimeBuffersLost;              // no of rt delivery failures
    HANDLE LoggerThreadId;                  // thread id of Logger
    ULONG LogFileNameOffset;                // Offset to LogFileName
    ULONG LoggerNameOffset;                 // Offset to LoggerName
} EVENT_TRACE_PROPERTIES, * PEVENT_TRACE_PROPERTIES;

typedef struct _EVENT_TRACE_PROPERTIES_V2 {
    WNODE_HEADER Wnode;                     // Always have WNODE_FLAG_VERSIONED_PROPERTIES.
    //
    // data provided by caller
    ULONG BufferSize;                       // buffer size for logging (kbytes)
    ULONG MinimumBuffers;                   // minimum to preallocate
    ULONG MaximumBuffers;                   // maximum buffers allowed
    ULONG MaximumFileSize;                  // maximum logfile size (in MBytes)
    ULONG LogFileMode;                      // sequential, circular
    ULONG FlushTimer;                       // buffer flush timer, in seconds
    ULONG EnableFlags;                      // trace enable flags
    union {
        LONG  AgeLimit;                     // unused
        LONG  FlushThreshold;               // Number of buffers to fill before flushing
    } DUMMYUNIONNAME;

    // data returned to caller
    ULONG NumberOfBuffers;                  // no of buffers in use
    ULONG FreeBuffers;                      // no of buffers free
    ULONG EventsLost;                       // event records lost
    ULONG BuffersWritten;                   // no of buffers written to file
    ULONG LogBuffersLost;                   // no of logfile write failures
    ULONG RealTimeBuffersLost;              // no of rt delivery failures
    HANDLE LoggerThreadId;                  // thread id of Logger
    ULONG LogFileNameOffset;                // Offset to LogFileName
    ULONG LoggerNameOffset;                 // Offset to LoggerName

    // V2 data
    union {
        struct {
            ULONG VersionNumber : 8;        // Should be set to 2 for this version.
        } DUMMYSTRUCTNAME;
        ULONG V2Control;
    } DUMMYUNIONNAME2;
    ULONG FilterDescCount;                  // Number of filters
    PEVENT_FILTER_DESCRIPTOR FilterDesc;    // Only applicable for Private Loggers
    union {
        struct {
            ULONG Wow : 1;                  // Logger was started by a WOW64 process (output only).
            ULONG QpcDeltaTracking : 1;     // QPC delta tracking events are enabled.
            ULONG LargeMdlPages : 1;        // Buffers allocated via large MDL pages.
            ULONG ExcludeKernelStack : 1;   // Exclude kernel stack from stack walk.
        } DUMMYSTRUCTNAME;
        ULONG64 V2Options;
    } DUMMYUNIONNAME3;
} EVENT_TRACE_PROPERTIES_V2, * PEVENT_TRACE_PROPERTIES_V2;
#endif

typedef enum _ETWTRACECONTROLCODE
{
    EtwStartLoggerCode = 1, // inout WMI_LOGGER_INFORMATION
    EtwStopLoggerCode = 2, // inout WMI_LOGGER_INFORMATION
    EtwQueryLoggerCode = 3, // inout WMI_LOGGER_INFORMATION
    EtwUpdateLoggerCode = 4, // inout WMI_LOGGER_INFORMATION
    EtwFlushLoggerCode = 5, // inout WMI_LOGGER_INFORMATION
    EtwIncrementLoggerFile = 6, // inout WMI_LOGGER_INFORMATION
    EtwRealtimeTransition = 7, // inout WMI_LOGGER_INFORMATION
    // reserved
    EtwRealtimeConnectCode = 11,
    EtwActivityIdCreate = 12,
    EtwWdiScenarioCode = 13,
    EtwRealtimeDisconnectCode = 14, // in HANDLE
    EtwRegisterGuidsCode = 15,
    EtwReceiveNotification = 16,
    EtwSendDataBlock = 17, // ETW_ENABLE_NOTIFICATION_PACKET
    EtwSendReplyDataBlock = 18,
    EtwReceiveReplyDataBlock = 19,
    EtwWdiSemUpdate = 20,
    EtwEnumTraceGuidList = 21, // out GUID[]
    EtwGetTraceGuidInfo = 22, // in GUID, out ETW_TRACE_GUID_INFO
    EtwEnumerateTraceGuids = 23,
    EtwRegisterSecurityProv = 24,
    EtwReferenceTimeCode = 25, // in ULONG LoggerId, out ETW_REF_CLOCK
    EtwTrackBinaryCode = 26, // in HANDLE
    EtwAddNotificationEvent = 27,
    EtwUpdateDisallowList = 28,
    EtwSetEnableAllKeywordsCode = 29,
    EtwSetProviderTraitsCode = 30,
    EtwUseDescriptorTypeCode = 31,
    EtwEnumTraceGroupList = 32,
    EtwGetTraceGroupInfo = 33,
    EtwGetDisallowList = 34,
    EtwSetCompressionSettings = 35,
    EtwGetCompressionSettings = 36,
    EtwUpdatePeriodicCaptureState = 37,
    EtwGetPrivateSessionTraceHandle = 38,
    EtwRegisterPrivateSession = 39,
    EtwQuerySessionDemuxObject = 40,
    EtwSetProviderBinaryTracking = 41,
    EtwMaxLoggers = 42, // out ULONG
    EtwMaxPmcCounter = 43, // out ULONG
    EtwQueryUsedProcessorCount = 44, // ULONG // since WIN11
    EtwGetPmcOwnership = 45,
    EtwGetPmcSessions = 46,
} ETWTRACECONTROLCODE;

// public TRACE_PROVIDER_INSTANCE_INFO
typedef struct _ETW_TRACE_PROVIDER_INSTANCE_INFO
{
    ULONG NextOffset;
    ULONG EnableCount;
    ULONG Pid;
    ULONG Flags;
} ETW_TRACE_PROVIDER_INSTANCE_INFO, * PETW_TRACE_PROVIDER_INSTANCE_INFO;

// public TRACE_GUID_INFO
typedef struct _ETW_TRACE_GUID_INFO
{
    ULONG InstanceCount;
    ULONG Reserved;
    //ETW_TRACE_PROVIDER_INSTANCE_INFO Instances[1];
} ETW_TRACE_GUID_INFO, * PETW_TRACE_GUID_INFO;

typedef struct _ETW_REF_CLOCK
{
    LARGE_INTEGER StartTime;
    LARGE_INTEGER StartPerfClock;
} ETW_REF_CLOCK, * PETW_REF_CLOCK;

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtTraceControl(
    _In_ ETWTRACECONTROLCODE TraceInformationClass,
    _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength,
    _Out_ PULONG ReturnLength
);

NTSYSAPI
NTSTATUS
NTAPI
ZwTraceControl(
    _In_ ETWTRACECONTROLCODE TraceInformationClass,
    _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength,
    _Out_ PULONG ReturnLength
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtTraceEvent(
    _In_ HANDLE TraceHandle,
    _In_ ULONG Flags,
    _In_ ULONG FieldSize,
    _In_ PVOID Fields
);

NTSYSAPI
NTSTATUS
NTAPI
ZwTraceEvent(
    _In_ HANDLE TraceHandle,
    _In_ ULONG Flags,
    _In_ ULONG FieldSize,
    _In_ PVOID Fields
);

#ifndef _TRACEHANDLE_DEFINED
#define _TRACEHANDLE_DEFINED
typedef ULONG64 TRACEHANDLE, * PTRACEHANDLE;
#endif

typedef enum _EVENT_TRACE_INFORMATION_CLASS
{
    EventTraceKernelVersionInformation, // EVENT_TRACE_VERSION_INFORMATION
    EventTraceGroupMaskInformation, // EVENT_TRACE_GROUPMASK_INFORMATION
    EventTracePerformanceInformation, // EVENT_TRACE_PERFORMANCE_INFORMATION
    EventTraceTimeProfileInformation, // EVENT_TRACE_TIME_PROFILE_INFORMATION
    EventTraceSessionSecurityInformation, // EVENT_TRACE_SESSION_SECURITY_INFORMATION
    EventTraceSpinlockInformation, // EVENT_TRACE_SPINLOCK_INFORMATION
    EventTraceStackTracingInformation, // EVENT_TRACE_STACK_TRACING_INFORMATION
    EventTraceExecutiveResourceInformation, // EVENT_TRACE_EXECUTIVE_RESOURCE_INFORMATION
    EventTraceHeapTracingInformation, // EVENT_TRACE_HEAP_TRACING_INFORMATION
    EventTraceHeapSummaryTracingInformation, // EVENT_TRACE_HEAP_TRACING_INFORMATION
    EventTracePoolTagFilterInformation, // EVENT_TRACE_POOLTAG_FILTER_INFORMATION
    EventTracePebsTracingInformation, // EVENT_TRACE_PEBS_TRACING_INFORMATION
    EventTraceProfileConfigInformation, // EVENT_TRACE_PROFILE_CONFIG_INFORMATION
    EventTraceProfileSourceListInformation, // EVENT_TRACE_PROFILE_LIST_INFORMATION
    EventTraceProfileEventListInformation, // EVENT_TRACE_PROFILE_EVENT_INFORMATION
    EventTraceProfileCounterListInformation, // EVENT_TRACE_PROFILE_COUNTER_INFORMATION
    EventTraceStackCachingInformation, // EVENT_TRACE_STACK_CACHING_INFORMATION
    EventTraceObjectTypeFilterInformation, // EVENT_TRACE_OBJECT_TYPE_FILTER_INFORMATION
    EventTraceSoftRestartInformation, // EVENT_TRACE_SOFT_RESTART_INFORMATION
    EventTraceLastBranchConfigurationInformation, // REDSTONE3
    EventTraceLastBranchEventListInformation,
    EventTraceProfileSourceAddInformation, // EVENT_TRACE_PROFILE_ADD_INFORMATION // REDSTONE4
    EventTraceProfileSourceRemoveInformation, // EVENT_TRACE_PROFILE_REMOVE_INFORMATION
    EventTraceProcessorTraceConfigurationInformation,
    EventTraceProcessorTraceEventListInformation,
    EventTraceCoverageSamplerInformation, // EVENT_TRACE_COVERAGE_SAMPLER_INFORMATION
    EventTraceUnifiedStackCachingInformation, // since 21H1
    MaxEventTraceInfoClass
} EVENT_TRACE_INFORMATION_CLASS;

typedef struct _TRACE_ENABLE_FLAG_EXTENSION
{
    USHORT Offset; // Offset to the flag array in structure
    UCHAR Length; // Length of flag array in ULONGs
    UCHAR Flag; // Must be set to EVENT_TRACE_FLAG_EXTENSION
} TRACE_ENABLE_FLAG_EXTENSION, * PTRACE_ENABLE_FLAG_EXTENSION;

typedef struct _TRACE_ENABLE_FLAG_EXT_HEADER
{
    USHORT Length; // Length in ULONGs
    USHORT Items; // # of items
} TRACE_ENABLE_FLAG_EXT_HEADER, * PTRACE_ENABLE_FLAG_EXT_HEADER;

typedef struct _TRACE_ENABLE_FLAG_EXT_ITEM
{
    USHORT Offset; // Offset to the next block
    USHORT Type; // Extension type
} TRACE_ENABLE_FLAG_EXT_ITEM, * PTRACE_ENABLE_FLAG_EXT_ITEM;

#define EVENT_TRACE_FLAG_EXT_ITEMS 0x80FF0000    // New extension structure
#define EVENT_TRACE_FLAG_EXT_LEN_NEW_STRUCT 0xFF // Pseudo length to denote new struct format

#define ETW_MINIMUM_CACHED_STACK_LENGTH 4
#define ETW_SW_ARRAY_SIZE          256     // Frame Count allocated in lookaside list
#define ETW_STACK_SW_ARRAY_SIZE    192     // Frame Count allocated in stack
#define ETW_MAX_STACKWALK_FILTER   256 // Max number of HookId's
#define ETW_MAX_TAG_FILTER         4
#define ETW_MAX_POOLTAG_FILTER     ETW_MAX_TAG_FILTER

#define ETW_EXT_ENABLE_FLAGS       0x0001
#define ETW_EXT_PIDS               0x0002
#define ETW_EXT_STACKWALK_FILTER   0x0003
#define ETW_EXT_POOLTAG_FILTER     0x0004
#define ETW_EXT_STACK_CACHING      0x0005

// Extended item for configuring stack caching.
typedef struct _ETW_STACK_CACHING_CONFIG
{
    ULONG CacheSize;
    ULONG BucketCount;
} ETW_STACK_CACHING_CONFIG, * PETW_STACK_CACHING_CONFIG;

// The second bit is set if the trace is used by PM & CP (fixed headers)
// If not, the data block is used by for finer data for performance analysis
//
#define TRACE_HEADER_EVENT_TRACE 0x40000000
//
// If set, the data block is SYSTEM_TRACE_HEADER
//
#define TRACE_HEADER_ENUM_MASK 0x00FF0000

#define PERF_MASK_INDEX (0xe0000000)
#define PERF_MASK_GROUP (~PERF_MASK_INDEX)
#define PERF_NUM_MASKS 8

#define PERF_GET_MASK_INDEX(GM) (((GM) & PERF_MASK_INDEX) >> 29)
#define PERF_GET_MASK_GROUP(GM) ((GM) & PERF_MASK_GROUP)
#define PERFINFO_OR_GROUP_WITH_GROUPMASK(Group, pGroupMask) \
    (pGroupMask)->Masks[PERF_GET_MASK_INDEX(Group)] |= PERF_GET_MASK_GROUP(Group);

// Masks[0]
#define PERF_PROCESS            EVENT_TRACE_FLAG_PROCESS
#define PERF_THREAD             EVENT_TRACE_FLAG_THREAD
#define PERF_PROC_THREAD        EVENT_TRACE_FLAG_PROCESS | EVENT_TRACE_FLAG_THREAD
#define PERF_LOADER             EVENT_TRACE_FLAG_IMAGE_LOAD
#define PERF_PERF_COUNTER       EVENT_TRACE_FLAG_PROCESS_COUNTERS
#define PERF_FILENAME           EVENT_TRACE_FLAG_DISK_FILE_IO
#define PERF_DISK_IO            EVENT_TRACE_FLAG_DISK_FILE_IO | EVENT_TRACE_FLAG_DISK_IO
#define PERF_DISK_IO_INIT       EVENT_TRACE_FLAG_DISK_IO_INIT
#define PERF_ALL_FAULTS         EVENT_TRACE_FLAG_MEMORY_PAGE_FAULTS
#define PERF_HARD_FAULTS        EVENT_TRACE_FLAG_MEMORY_HARD_FAULTS
#define PERF_VAMAP              EVENT_TRACE_FLAG_VAMAP
#define PERF_NETWORK            EVENT_TRACE_FLAG_NETWORK_TCPIP
#define PERF_REGISTRY           EVENT_TRACE_FLAG_REGISTRY
#define PERF_DBGPRINT           EVENT_TRACE_FLAG_DBGPRINT
#define PERF_JOB                EVENT_TRACE_FLAG_JOB
#define PERF_ALPC               EVENT_TRACE_FLAG_ALPC
#define PERF_SPLIT_IO           EVENT_TRACE_FLAG_SPLIT_IO
#define PERF_DEBUG_EVENTS       EVENT_TRACE_FLAG_DEBUG_EVENTS
#define PERF_FILE_IO            EVENT_TRACE_FLAG_FILE_IO
#define PERF_FILE_IO_INIT       EVENT_TRACE_FLAG_FILE_IO_INIT
#define PERF_NO_SYSCONFIG       EVENT_TRACE_FLAG_NO_SYSCONFIG

// Masks[1]
#define PERF_MEMORY             0x20000001
#define PERF_PROFILE            0x20000002  // equivalent to EVENT_TRACE_FLAG_PROFILE
#define PERF_CONTEXT_SWITCH     0x20000004  // equivalent to EVENT_TRACE_FLAG_CSWITCH
#define PERF_FOOTPRINT          0x20000008
#define PERF_DRIVERS            0x20000010  // equivalent to EVENT_TRACE_FLAG_DRIVER
#define PERF_REFSET             0x20000020
#define PERF_POOL               0x20000040
#define PERF_POOLTRACE          0x20000041
#define PERF_DPC                0x20000080  // equivalent to EVENT_TRACE_FLAG_DPC
#define PERF_COMPACT_CSWITCH    0x20000100
#define PERF_DISPATCHER         0x20000200  // equivalent to EVENT_TRACE_FLAG_DISPATCHER
#define PERF_PMC_PROFILE        0x20000400
#define PERF_PROFILING          0x20000402
#define PERF_PROCESS_INSWAP     0x20000800
#define PERF_AFFINITY           0x20001000
#define PERF_PRIORITY           0x20002000
#define PERF_INTERRUPT          0x20004000  // equivalent to EVENT_TRACE_FLAG_INTERRUPT
#define PERF_VIRTUAL_ALLOC      0x20008000  // equivalent to EVENT_TRACE_FLAG_VIRTUAL_ALLOC
#define PERF_SPINLOCK           0x20010000
#define PERF_SYNC_OBJECTS       0x20020000
#define PERF_DPC_QUEUE          0x20040000
#define PERF_MEMINFO            0x20080000
#define PERF_CONTMEM_GEN        0x20100000
#define PERF_SPINLOCK_CNTRS     0x20200000
#define PERF_SPININSTR          0x20210000
#define PERF_SESSION            0x20400000
#define PERF_PFSECTION          0x20400000
#define PERF_MEMINFO_WS         0x20800000
#define PERF_KERNEL_QUEUE       0x21000000
#define PERF_INTERRUPT_STEER    0x22000000
#define PERF_SHOULD_YIELD       0x24000000
#define PERF_WS                 0x28000000
//#define PERF_POOLTRACE (PERF_MEMORY | PERF_POOL)
//#define PERF_PROFILING (PERF_PROFILE | PERF_PMC_PROFILE)
//#define PERF_SPININSTR (PERF_SPINLOCK | PERF_SPINLOCK_CNTRS)

// Masks[2]
#define PERF_ANTI_STARVATION    0x40000001
#define PERF_PROCESS_FREEZE     0x40000002
#define PERF_PFN_LIST           0x40000004
#define PERF_WS_DETAIL          0x40000008
#define PERF_WS_ENTRY           0x40000010
#define PERF_HEAP               0x40000020
#define PERF_SYSCALL            0x40000040  // equivalent to EVENT_TRACE_FLAG_SYSTEMCALL
#define PERF_UMS                0x40000080
#define PERF_BACKTRACE          0x40000100
#define PERF_VULCAN             0x40000200
#define PERF_OBJECTS            0x40000400
#define PERF_EVENTS             0x40000800
#define PERF_FULLTRACE          0x40001000
#define PERF_DFSS               0x40002000
#define PERF_PREFETCH           0x40004000
#define PERF_PROCESSOR_IDLE     0x40008000
#define PERF_CPU_CONFIG         0x40010000
#define PERF_TIMER              0x40020000
#define PERF_CLOCK_INTERRUPT    0x40040000
#define PERF_LOAD_BALANCER      0x40080000
#define PERF_CLOCK_TIMER        0x40100000
#define PERF_IDLE_SELECTION     0x40200000
#define PERF_IPI                0x40400000
#define PERF_IO_TIMER           0x40800000
#define PERF_REG_HIVE           0x41000000
#define PERF_REG_NOTIF          0x42000000
#define PERF_PPM_EXIT_LATENCY   0x44000000
#define PERF_WORKER_THREAD      0x48000000

// Masks[4]
#define PERF_OPTICAL_IO         0x80000001
#define PERF_OPTICAL_IO_INIT    0x80000002
// Reserved                     0x80000004
#define PERF_DLL_INFO           0x80000008
#define PERF_DLL_FLUSH_WS       0x80000010
// Reserved                     0x80000020
#define PERF_OB_HANDLE          0x80000040
#define PERF_OB_OBJECT          0x80000080
// Reserved                     0x80000100
#define PERF_WAKE_DROP          0x80000200
#define PERF_WAKE_EVENT         0x80000400
#define PERF_DEBUGGER           0x80000800
#define PERF_PROC_ATTACH        0x80001000
#define PERF_WAKE_COUNTER       0x80002000
// Reserved                     0x80004000
#define PERF_POWER              0x80008000
#define PERF_SOFT_TRIM          0x80010000
#define PERF_CC                 0x80020000
// Reserved                     0x80040000
#define PERF_FLT_IO_INIT        0x80080000
#define PERF_FLT_IO             0x80100000
#define PERF_FLT_FASTIO         0x80200000
#define PERF_FLT_IO_FAILURE     0x80400000
#define PERF_HV_PROFILE         0x80800000
#define PERF_WDF_DPC            0x81000000
#define PERF_WDF_INTERRUPT      0x82000000
#define PERF_CACHE_FLUSH        0x84000000

// Masks[5]
#define PERF_HIBER_RUNDOWN      0xA0000001

// Masks[6]
#define PERF_SYSCFG_SYSTEM      0xC0000001
#define PERF_SYSCFG_GRAPHICS    0xC0000002
#define PERF_SYSCFG_STORAGE     0xC0000004
#define PERF_SYSCFG_NETWORK     0xC0000008
#define PERF_SYSCFG_SERVICES    0xC0000010
#define PERF_SYSCFG_PNP         0xC0000020
#define PERF_SYSCFG_OPTICAL     0xC0000040
#define PERF_SYSCFG_ALL         0xDFFFFFFF

// Masks[7] - Control Mask. All flags that change system behavior go here.
#define PERF_CLUSTER_OFF        0xE0000001
#define PERF_MEMORY_CONTROL     0xE0000002

// The predefined event groups or families for NT subsystems
#define EVENT_TRACE_GROUP_HEADER               0x0000
#define EVENT_TRACE_GROUP_IO                   0x0100
#define EVENT_TRACE_GROUP_MEMORY               0x0200
#define EVENT_TRACE_GROUP_PROCESS              0x0300
#define EVENT_TRACE_GROUP_FILE                 0x0400
#define EVENT_TRACE_GROUP_THREAD               0x0500
#define EVENT_TRACE_GROUP_TCPIP                0x0600
#define EVENT_TRACE_GROUP_JOB                  0x0700
#define EVENT_TRACE_GROUP_UDPIP                0x0800
#define EVENT_TRACE_GROUP_REGISTRY             0x0900
#define EVENT_TRACE_GROUP_DBGPRINT             0x0A00
#define EVENT_TRACE_GROUP_CONFIG               0x0B00
#define EVENT_TRACE_GROUP_SPARE1               0x0C00   // Spare1
#define EVENT_TRACE_GROUP_WNF                  0x0D00
#define EVENT_TRACE_GROUP_POOL                 0x0E00
#define EVENT_TRACE_GROUP_PERFINFO             0x0F00
#define EVENT_TRACE_GROUP_HEAP                 0x1000
#define EVENT_TRACE_GROUP_OBJECT               0x1100
#define EVENT_TRACE_GROUP_POWER                0x1200
#define EVENT_TRACE_GROUP_MODBOUND             0x1300
#define EVENT_TRACE_GROUP_IMAGE                0x1400
#define EVENT_TRACE_GROUP_DPC                  0x1500
#define EVENT_TRACE_GROUP_CC                   0x1600
#define EVENT_TRACE_GROUP_CRITSEC              0x1700
#define EVENT_TRACE_GROUP_STACKWALK            0x1800
#define EVENT_TRACE_GROUP_UMS                  0x1900
#define EVENT_TRACE_GROUP_ALPC                 0x1A00
#define EVENT_TRACE_GROUP_SPLITIO              0x1B00
#define EVENT_TRACE_GROUP_THREAD_POOL          0x1C00
#define EVENT_TRACE_GROUP_HYPERVISOR           0x1D00
#define EVENT_TRACE_GROUP_HYPERVISORX          0x1E00

//
// Event for header
//
#define WMI_LOG_TYPE_HEADER                       (EVENT_TRACE_GROUP_HEADER | EVENT_TRACE_TYPE_INFO)
#define WMI_LOG_TYPE_HEADER_EXTENSION             (EVENT_TRACE_GROUP_HEADER | EVENT_TRACE_TYPE_EXTENSION)
#define WMI_LOG_TYPE_RUNDOWN_COMPLETE             (EVENT_TRACE_GROUP_HEADER | EVENT_TRACE_TYPE_CHECKPOINT)
#define WMI_LOG_TYPE_GROUP_MASKS_END              (EVENT_TRACE_GROUP_HEADER | 0x20)
#define WMI_LOG_TYPE_RUNDOWN_BEGIN                (EVENT_TRACE_GROUP_HEADER | 0x30)
#define WMI_LOG_TYPE_RUNDOWN_END                  (EVENT_TRACE_GROUP_HEADER | 0x31)
#define WMI_LOG_TYPE_DBGID_RSDS                   (EVENT_TRACE_GROUP_HEADER | EVENT_TRACE_TYPE_DBGID_RSDS)
#define WMI_LOG_TYPE_DBGID_NB10                   (EVENT_TRACE_GROUP_HEADER | 0x41)
#define WMI_LOG_TYPE_BUILD_LAB                    (EVENT_TRACE_GROUP_HEADER | 0x42)
#define WMI_LOG_TYPE_BINARY_PATH                  (EVENT_TRACE_GROUP_HEADER | 0x43)

//
// Event for system config
//
#define WMI_LOG_TYPE_CONFIG_CPU                   (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_CPU)
#define WMI_LOG_TYPE_CONFIG_PHYSICALDISK          (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_PHYSICALDISK)
#define WMI_LOG_TYPE_CONFIG_LOGICALDISK           (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_LOGICALDISK)
#define WMI_LOG_TYPE_CONFIG_OPTICALMEDIA          (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_OPTICALMEDIA)
#define WMI_LOG_TYPE_CONFIG_NIC                   (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_NIC)
#define WMI_LOG_TYPE_CONFIG_VIDEO                 (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_VIDEO)
#define WMI_LOG_TYPE_CONFIG_SERVICES              (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_SERVICES)
#define WMI_LOG_TYPE_CONFIG_POWER                 (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_POWER)
#define WMI_LOG_TYPE_CONFIG_OSVERSION             (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_OSVERSION)
#define WMI_LOG_TYPE_CONFIG_VISUALTHEME           (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_VISUALTHEME)
#define WMI_LOG_TYPE_CONFIG_SYSTEMRANGE           (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_SYSTEMRANGE)
#define WMI_LOG_TYPE_CONFIG_SYSDLLINFO            (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_SYSDLLINFO)
#define WMI_LOG_TYPE_CONFIG_IRQ                   (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_IRQ)
#define WMI_LOG_TYPE_CONFIG_PNP                   (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_PNP)
#define WMI_LOG_TYPE_CONFIG_IDECHANNEL            (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_IDECHANNEL)
#define WMI_LOG_TYPE_CONFIG_NUMANODE              (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_NUMANODE)
#define WMI_LOG_TYPE_CONFIG_PLATFORM              (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_PLATFORM)
#define WMI_LOG_TYPE_CONFIG_PROCESSORGROUP        (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_PROCESSORGROUP)
#define WMI_LOG_TYPE_CONFIG_PROCESSORNUMBER       (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_PROCESSORNUMBER)
#define WMI_LOG_TYPE_CONFIG_DPI                   (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_DPI)
#define WMI_LOG_TYPE_CONFIG_CODEINTEGRITY         (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_CI_INFO)
#define WMI_LOG_TYPE_CONFIG_MACHINEID             (EVENT_TRACE_GROUP_CONFIG | EVENT_TRACE_TYPE_CONFIG_MACHINEID)

//
// Event for Image and File Name
//
#define PERFINFO_LOG_TYPE_FILENAME                  (EVENT_TRACE_GROUP_FILE | EVENT_TRACE_TYPE_INFO)
#define PERFINFO_LOG_TYPE_FILENAME_CREATE           (EVENT_TRACE_GROUP_FILE | 0x20)
#define PERFINFO_LOG_TYPE_FILENAME_SAME             (EVENT_TRACE_GROUP_FILE | 0x21)
#define PERFINFO_LOG_TYPE_FILENAME_NULL             (EVENT_TRACE_GROUP_FILE | 0x22)
#define PERFINFO_LOG_TYPE_FILENAME_DELETE           (EVENT_TRACE_GROUP_FILE | 0x23)
#define PERFINFO_LOG_TYPE_FILENAME_RUNDOWN          (EVENT_TRACE_GROUP_FILE | 0x24)

#define PERFINFO_LOG_TYPE_MAPFILE                   (EVENT_TRACE_GROUP_FILE | 0x25)
#define PERFINFO_LOG_TYPE_UNMAPFILE                 (EVENT_TRACE_GROUP_FILE | 0x26)
#define PERFINFO_LOG_TYPE_MAPFILE_DC_START          (EVENT_TRACE_GROUP_FILE | 0x27)
#define PERFINFO_LOG_TYPE_MAPFILE_DC_END            (EVENT_TRACE_GROUP_FILE | 0x28)

#define PERFINFO_LOG_TYPE_FILE_IO_CREATE            (EVENT_TRACE_GROUP_FILE | 0x40)
#define PERFINFO_LOG_TYPE_FILE_IO_CLEANUP           (EVENT_TRACE_GROUP_FILE | 0x41)
#define PERFINFO_LOG_TYPE_FILE_IO_CLOSE             (EVENT_TRACE_GROUP_FILE | 0x42)
#define PERFINFO_LOG_TYPE_FILE_IO_READ              (EVENT_TRACE_GROUP_FILE | 0x43)
#define PERFINFO_LOG_TYPE_FILE_IO_WRITE             (EVENT_TRACE_GROUP_FILE | 0x44)
#define PERFINFO_LOG_TYPE_FILE_IO_SET_INFORMATION   (EVENT_TRACE_GROUP_FILE | 0x45)
#define PERFINFO_LOG_TYPE_FILE_IO_DELETE            (EVENT_TRACE_GROUP_FILE | 0x46)
#define PERFINFO_LOG_TYPE_FILE_IO_RENAME            (EVENT_TRACE_GROUP_FILE | 0x47)
#define PERFINFO_LOG_TYPE_FILE_IO_DIRENUM           (EVENT_TRACE_GROUP_FILE | 0x48)
#define PERFINFO_LOG_TYPE_FILE_IO_FLUSH             (EVENT_TRACE_GROUP_FILE | 0x49)
#define PERFINFO_LOG_TYPE_FILE_IO_QUERY_INFORMATION (EVENT_TRACE_GROUP_FILE | 0x4A)
#define PERFINFO_LOG_TYPE_FILE_IO_FS_CONTROL        (EVENT_TRACE_GROUP_FILE | 0x4B)
#define PERFINFO_LOG_TYPE_FILE_IO_OPERATION_END     (EVENT_TRACE_GROUP_FILE | 0x4C)
#define PERFINFO_LOG_TYPE_FILE_IO_DIRNOTIFY         (EVENT_TRACE_GROUP_FILE | 0x4D)
#define PERFINFO_LOG_TYPE_FILE_IO_CREATE_NEW        (EVENT_TRACE_GROUP_FILE | 0x4E)
#define PERFINFO_LOG_TYPE_FILE_IO_DELETE_PATH       (EVENT_TRACE_GROUP_FILE | 0x4F)
#define PERFINFO_LOG_TYPE_FILE_IO_RENAME_PATH       (EVENT_TRACE_GROUP_FILE | 0x50)
#define PERFINFO_LOG_TYPE_FILE_IO_SETLINK_PATH      (EVENT_TRACE_GROUP_FILE | 0x51)
#define PERFINFO_LOG_TYPE_FILE_IO_SETLINK           (EVENT_TRACE_GROUP_FILE | 0x52)

//
//  Event types for minifilter callbacks
//

#define PERFINFO_LOG_TYPE_FLT_PREOP_INIT        (EVENT_TRACE_GROUP_FILE | EVENT_TRACE_TYPE_FLT_PREOP_INIT)
#define PERFINFO_LOG_TYPE_FLT_POSTOP_INIT       (EVENT_TRACE_GROUP_FILE | EVENT_TRACE_TYPE_FLT_POSTOP_INIT)
#define PERFINFO_LOG_TYPE_FLT_PREOP_COMPLETION  (EVENT_TRACE_GROUP_FILE | EVENT_TRACE_TYPE_FLT_PREOP_COMPLETION)
#define PERFINFO_LOG_TYPE_FLT_POSTOP_COMPLETION (EVENT_TRACE_GROUP_FILE | EVENT_TRACE_TYPE_FLT_POSTOP_COMPLETION)
#define PERFINFO_LOG_TYPE_FLT_PREOP_FAILURE     (EVENT_TRACE_GROUP_FILE | EVENT_TRACE_TYPE_FLT_PREOP_FAILURE)
#define PERFINFO_LOG_TYPE_FLT_POSTOP_FAILURE    (EVENT_TRACE_GROUP_FILE | EVENT_TRACE_TYPE_FLT_POSTOP_FAILURE)

//
// Event types for Job
//

#define WMI_LOG_TYPE_JOB_CREATE                     (EVENT_TRACE_GROUP_JOB | 0x20)
#define WMI_LOG_TYPE_JOB_TERMINATE                  (EVENT_TRACE_GROUP_JOB | 0x21)
#define WMI_LOG_TYPE_JOB_OPEN                       (EVENT_TRACE_GROUP_JOB | 0x22)
#define WMI_LOG_TYPE_JOB_ASSIGN_PROCESS             (EVENT_TRACE_GROUP_JOB | 0x23)
#define WMI_LOG_TYPE_JOB_REMOVE_PROCESS             (EVENT_TRACE_GROUP_JOB | 0x24)
#define WMI_LOG_TYPE_JOB_SET                        (EVENT_TRACE_GROUP_JOB | 0x25)
#define WMI_LOG_TYPE_JOB_QUERY                      (EVENT_TRACE_GROUP_JOB | 0x26)
#define WMI_LOG_TYPE_JOB_SET_FAILED                 (EVENT_TRACE_GROUP_JOB | 0x27)
#define WMI_LOG_TYPE_JOB_QUERY_FAILED               (EVENT_TRACE_GROUP_JOB | 0x28)
#define WMI_LOG_TYPE_JOB_SET_NOTIFICATION           (EVENT_TRACE_GROUP_JOB | 0x29)
#define WMI_LOG_TYPE_JOB_SEND_NOTIFICATION          (EVENT_TRACE_GROUP_JOB | 0x2A)
#define WMI_LOG_TYPE_JOB_QUERY_VIOLATION            (EVENT_TRACE_GROUP_JOB | 0x2B)
#define WMI_LOG_TYPE_JOB_SET_CPU_RATE               (EVENT_TRACE_GROUP_JOB | 0x2C)
#define WMI_LOG_TYPE_JOB_SET_NET_RATE               (EVENT_TRACE_GROUP_JOB | 0x2D)

//
// Event types for Process
//

#define WMI_LOG_TYPE_PROCESS_CREATE                 (EVENT_TRACE_GROUP_PROCESS | EVENT_TRACE_TYPE_START)
#define WMI_LOG_TYPE_PROCESS_DELETE                 (EVENT_TRACE_GROUP_PROCESS | EVENT_TRACE_TYPE_END)
#define WMI_LOG_TYPE_PROCESS_DC_START               (EVENT_TRACE_GROUP_PROCESS | EVENT_TRACE_TYPE_DC_START)
#define WMI_LOG_TYPE_PROCESS_DC_END                 (EVENT_TRACE_GROUP_PROCESS | EVENT_TRACE_TYPE_DC_END)
#define WMI_LOG_TYPE_PROCESS_LOAD_IMAGE             (EVENT_TRACE_GROUP_PROCESS | EVENT_TRACE_TYPE_LOAD)
#define WMI_LOG_TYPE_PROCESS_TERMINATE              (EVENT_TRACE_GROUP_PROCESS | EVENT_TRACE_TYPE_TERMINATE)

#define PERFINFO_LOG_TYPE_PROCESS_PERFCTR_END       (EVENT_TRACE_GROUP_PROCESS | 0x20)
#define PERFINFO_LOG_TYPE_PROCESS_PERFCTR_RD        (EVENT_TRACE_GROUP_PROCESS | 0x21)
// Reserved                                         (EVENT_TRACE_GROUP_PROCESS | 0x22)
#define PERFINFO_LOG_TYPE_INSWAPPROCESS             (EVENT_TRACE_GROUP_PROCESS | 0x23)
#define PERFINFO_LOG_TYPE_PROCESS_FREEZE            (EVENT_TRACE_GROUP_PROCESS | 0x24)
#define PERFINFO_LOG_TYPE_PROCESS_THAW              (EVENT_TRACE_GROUP_PROCESS | 0x25)
#define PERFINFO_LOG_TYPE_BOOT_PHASE_START          (EVENT_TRACE_GROUP_PROCESS | 0x26)
#define PERFINFO_LOG_TYPE_ZOMBIE_PROCESS            (EVENT_TRACE_GROUP_PROCESS | 0x27)
#define PERFINFO_LOG_TYPE_PROCESS_SET_AFFINITY      (EVENT_TRACE_GROUP_PROCESS | 0x28)

#define PERFINFO_LOG_TYPE_CHARGE_WAKE_COUNTER_USER             (EVENT_TRACE_GROUP_PROCESS | 0x30)
#define PERFINFO_LOG_TYPE_CHARGE_WAKE_COUNTER_EXECUTION        (EVENT_TRACE_GROUP_PROCESS | 0x31)
#define PERFINFO_LOG_TYPE_CHARGE_WAKE_COUNTER_KERNEL           (EVENT_TRACE_GROUP_PROCESS | 0x32)
#define PERFINFO_LOG_TYPE_CHARGE_WAKE_COUNTER_INSTRUMENTATION  (EVENT_TRACE_GROUP_PROCESS | 0x33)
#define PERFINFO_LOG_TYPE_CHARGE_WAKE_COUNTER_PRESERVE_PROCESS (EVENT_TRACE_GROUP_PROCESS | 0x34)

#define PERFINFO_LOG_TYPE_RELEASE_WAKE_COUNTER_USER            (EVENT_TRACE_GROUP_PROCESS | 0x40)
#define PERFINFO_LOG_TYPE_RELEASE_WAKE_COUNTER_EXECUTION       (EVENT_TRACE_GROUP_PROCESS | 0x41)
#define PERFINFO_LOG_TYPE_RELEASE_WAKE_COUNTER_KERNEL          (EVENT_TRACE_GROUP_PROCESS | 0x42)
#define PERFINFO_LOG_TYPE_RELEASE_WAKE_COUNTER_INSTRUMENTATION (EVENT_TRACE_GROUP_PROCESS | 0x43)
#define PERFINFO_LOG_TYPE_RELEASE_WAKE_COUNTER_PRESERVE_PROCESS (EVENT_TRACE_GROUP_PROCESS | 0x44)

#define PERFINFO_LOG_TYPE_WAKE_DROP_USER                       (EVENT_TRACE_GROUP_PROCESS | 0x50)
#define PERFINFO_LOG_TYPE_WAKE_DROP_EXECUTION                  (EVENT_TRACE_GROUP_PROCESS | 0x51)
#define PERFINFO_LOG_TYPE_WAKE_DROP_KERNEL                     (EVENT_TRACE_GROUP_PROCESS | 0x52)
#define PERFINFO_LOG_TYPE_WAKE_DROP_INSTRUMENTATION            (EVENT_TRACE_GROUP_PROCESS | 0x53)
#define PERFINFO_LOG_TYPE_WAKE_DROP_PRESERVE_PROCESS           (EVENT_TRACE_GROUP_PROCESS | 0x54)

#define PERFINFO_LOG_TYPE_WAKE_EVENT_USER                      (EVENT_TRACE_GROUP_PROCESS | 0x60)
#define PERFINFO_LOG_TYPE_WAKE_EVENT_EXECUTION                 (EVENT_TRACE_GROUP_PROCESS | 0x61)
#define PERFINFO_LOG_TYPE_WAKE_EVENT_KERNEL                    (EVENT_TRACE_GROUP_PROCESS | 0x62)
#define PERFINFO_LOG_TYPE_WAKE_EVENT_INSTRUMENTATION           (EVENT_TRACE_GROUP_PROCESS | 0x63)
#define PERFINFO_LOG_TYPE_WAKE_EVENT_PRESERVE_PROCESS          (EVENT_TRACE_GROUP_PROCESS | 0x64)

#define PERFINFO_LOG_TYPE_DEBUG_EVENT                          (EVENT_TRACE_GROUP_PROCESS | 0x70)

//
// Event types for Image and Library Loader
//

#define WMI_LOG_TYPE_IMAGE_LOAD                     (EVENT_TRACE_GROUP_IMAGE | EVENT_TRACE_TYPE_START) // reserved for future
#define WMI_LOG_TYPE_IMAGE_UNLOAD                   (EVENT_TRACE_GROUP_IMAGE | EVENT_TRACE_TYPE_END)
#define WMI_LOG_TYPE_IMAGE_DC_START                 (EVENT_TRACE_GROUP_IMAGE | EVENT_TRACE_TYPE_DC_START)
#define WMI_LOG_TYPE_IMAGE_DC_END                   (EVENT_TRACE_GROUP_IMAGE | EVENT_TRACE_TYPE_DC_END)
#define WMI_LOG_TYPE_IMAGE_RELOCATION               (EVENT_TRACE_GROUP_IMAGE | 0x20)
#define WMI_LOG_TYPE_IMAGE_KERNEL_BASE              (EVENT_TRACE_GROUP_IMAGE | 0x21)
#define WMI_LOG_TYPE_IMAGE_HYPERCALL_PAGE           (EVENT_TRACE_GROUP_IMAGE | 0x22)

#define PERFINFO_LOG_TYPE_LDR_LOCK_ACQUIRE_ATTEMPT          (EVENT_TRACE_GROUP_IMAGE | 0x80) // 128
#define PERFINFO_LOG_TYPE_LDR_LOCK_ACQUIRE_SUCCESS          (EVENT_TRACE_GROUP_IMAGE | 0x81)
#define PERFINFO_LOG_TYPE_LDR_LOCK_ACQUIRE_FAIL             (EVENT_TRACE_GROUP_IMAGE | 0x82)
#define PERFINFO_LOG_TYPE_LDR_LOCK_ACQUIRE_WAIT             (EVENT_TRACE_GROUP_IMAGE | 0x83)
#define PERFINFO_LOG_TYPE_LDR_PROC_INIT_DONE                (EVENT_TRACE_GROUP_IMAGE | 0x84) // 132
#define PERFINFO_LOG_TYPE_LDR_CREATE_SECTION                (EVENT_TRACE_GROUP_IMAGE | 0x85)
#define PERFINFO_LOG_TYPE_LDR_SECTION_CREATED               (EVENT_TRACE_GROUP_IMAGE | 0x86)
#define PERFINFO_LOG_TYPE_LDR_MAP_VIEW                      (EVENT_TRACE_GROUP_IMAGE | 0x87)

#define PERFINFO_LOG_TYPE_LDR_RELOCATE_IMAGE                (EVENT_TRACE_GROUP_IMAGE | 0x90) // 144
#define PERFINFO_LOG_TYPE_LDR_IMAGE_RELOCATED               (EVENT_TRACE_GROUP_IMAGE | 0x91)
#define PERFINFO_LOG_TYPE_LDR_HANDLE_OLD_DESCRIPTORS        (EVENT_TRACE_GROUP_IMAGE | 0x92)
#define PERFINFO_LOG_TYPE_LDR_OLD_DESCRIPTORS_HANDLED       (EVENT_TRACE_GROUP_IMAGE | 0x93)
#define PERFINFO_LOG_TYPE_LDR_HANDLE_NEW_DESCRIPTORS        (EVENT_TRACE_GROUP_IMAGE | 0x94) // 148
#define PERFINFO_LOG_TYPE_LDR_NEW_DESCRIPTORS_HANDLED       (EVENT_TRACE_GROUP_IMAGE | 0x95)
#define PERFINFO_LOG_TYPE_LDR_DLLMAIN_EXIT                  (EVENT_TRACE_GROUP_IMAGE | 0x96)

#define PERFINFO_LOG_TYPE_LDR_FIND_DLL                      (EVENT_TRACE_GROUP_IMAGE | 0xA0) // 160
#define PERFINFO_LOG_TYPE_LDR_VIEW_MAPPED                   (EVENT_TRACE_GROUP_IMAGE | 0xA1)
#define PERFINFO_LOG_TYPE_LDR_LOCK_RELEASE                  (EVENT_TRACE_GROUP_IMAGE | 0xA2)
#define PERFINFO_LOG_TYPE_LDR_DLLMAIN_ENTER                 (EVENT_TRACE_GROUP_IMAGE | 0xA3)
#define PERFINFO_LOG_TYPE_LDR_ERROR                         (EVENT_TRACE_GROUP_IMAGE | 0xA4) // 164

#define PERFINFO_LOG_TYPE_LDR_VIEW_MAPPING                  (EVENT_TRACE_GROUP_IMAGE | 0xA5) // 165
#define PERFINFO_LOG_TYPE_LDR_SNAPPING                      (EVENT_TRACE_GROUP_IMAGE | 0xA6)
#define PERFINFO_LOG_TYPE_LDR_SNAPPED                       (EVENT_TRACE_GROUP_IMAGE | 0xA7)
#define PERFINFO_LOG_TYPE_LDR_LOADING                       (EVENT_TRACE_GROUP_IMAGE | 0xA8)
#define PERFINFO_LOG_TYPE_LDR_LOADED                        (EVENT_TRACE_GROUP_IMAGE | 0xA9)
#define PERFINFO_LOG_TYPE_LDR_FOUND_KNOWN_DLL               (EVENT_TRACE_GROUP_IMAGE | 0xAA) // 170
#define PERFINFO_LOG_TYPE_LDR_ABNORMAL                      (EVENT_TRACE_GROUP_IMAGE | 0xAB)
#define PERFINFO_LOG_TYPE_LDR_PLACEHOLDER                   (EVENT_TRACE_GROUP_IMAGE | 0xAC)
#define PERFINFO_LOG_TYPE_LDR_RDY_TO_INIT                   (EVENT_TRACE_GROUP_IMAGE | 0xAD)
#define PERFINFO_LOG_TYPE_LDR_RDY_TO_RUN                    (EVENT_TRACE_GROUP_IMAGE | 0xAE) // 174


#define PERFINFO_LOG_TYPE_LDR_NEW_DLL_LOAD                  (EVENT_TRACE_GROUP_IMAGE | 0xB0) // 176
#define PERFINFO_LOG_TYPE_LDR_NEW_DLL_AS_DATA               (EVENT_TRACE_GROUP_IMAGE | 0xB1) // 177

#define PERFINFO_LOG_TYPE_LDR_EXTERNAL_PATH                 (EVENT_TRACE_GROUP_IMAGE | 0xC0) // 192
#define PERFINFO_LOG_TYPE_LDR_GENERATED_PATH                (EVENT_TRACE_GROUP_IMAGE | 0xC1)

#define PERFINFO_LOG_TYPE_LDR_APISET_RESOLVING              (EVENT_TRACE_GROUP_IMAGE | 0xD0) // 208
#define PERFINFO_LOG_TYPE_LDR_APISET_HOSTED                 (EVENT_TRACE_GROUP_IMAGE | 0xD1) // 209
#define PERFINFO_LOG_TYPE_LDR_APISET_UNHOSTED               (EVENT_TRACE_GROUP_IMAGE | 0xD2) // 210
#define PERFINFO_LOG_TYPE_LDR_APISET_UNRESOLVED             (EVENT_TRACE_GROUP_IMAGE | 0xD3) // 211

#define PERFINFO_LOG_TYPE_LDR_SEARCH_SECURITY               (EVENT_TRACE_GROUP_IMAGE | 0xD4) // 212
#define PERFINFO_LOG_TYPE_LDR_SEARCH_PATH_SECURITY          (EVENT_TRACE_GROUP_IMAGE | 0xD5) // 213

//
// Event types for Thread
//

#define WMI_LOG_TYPE_THREAD_CREATE                  (EVENT_TRACE_GROUP_THREAD | EVENT_TRACE_TYPE_START)
#define WMI_LOG_TYPE_THREAD_DELETE                  (EVENT_TRACE_GROUP_THREAD | EVENT_TRACE_TYPE_END)
#define WMI_LOG_TYPE_THREAD_DC_START                (EVENT_TRACE_GROUP_THREAD | EVENT_TRACE_TYPE_DC_START)
#define WMI_LOG_TYPE_THREAD_DC_END                  (EVENT_TRACE_GROUP_THREAD | EVENT_TRACE_TYPE_DC_END)

// Reserved                                         (EVENT_TRACE_GROUP_THREAD | 0x20)
// Reserved                                         (EVENT_TRACE_GROUP_THREAD | 0x21)
// Reserved                                         (EVENT_TRACE_GROUP_THREAD | 0x22)
// Reserved                                         (EVENT_TRACE_GROUP_THREAD | 0x23)
#define PERFINFO_LOG_TYPE_CONTEXTSWAP               (EVENT_TRACE_GROUP_THREAD | 0x24)
#define PERFINFO_LOG_TYPE_CONTEXTSWAP_BATCH         (EVENT_TRACE_GROUP_THREAD | 0x25)
// Reserved                                         (EVENT_TRACE_GROUP_THREAD | 0x26)
// Reserved                                         (EVENT_TRACE_GROUP_THREAD | 0x27)
// Reserved                                         (EVENT_TRACE_GROUP_THREAD | 0x28)
#define PERFINFO_LOG_TYPE_SPINLOCK                  (EVENT_TRACE_GROUP_THREAD | 0x29)
#define PERFINFO_LOG_TYPE_QUEUE                     (EVENT_TRACE_GROUP_THREAD | 0x2A)
#define PERFINFO_LOG_TYPE_RESOURCE                  (EVENT_TRACE_GROUP_THREAD | 0x2B)
#define PERFINFO_LOG_TYPE_PUSHLOCK                  (EVENT_TRACE_GROUP_THREAD | 0x2C)
#define PERFINFO_LOG_TYPE_WAIT_SINGLE               (EVENT_TRACE_GROUP_THREAD | 0x2D)
#define PERFINFO_LOG_TYPE_WAIT_MULTIPLE             (EVENT_TRACE_GROUP_THREAD | 0x2E)
#define PERFINFO_LOG_TYPE_DELAY_EXECUTION           (EVENT_TRACE_GROUP_THREAD | 0x2F)
#define PERFINFO_LOG_TYPE_THREAD_SET_PRIORITY       (EVENT_TRACE_GROUP_THREAD | 0x30)
#define PERFINFO_LOT_TYPE_THREAD_SET_BASE_PRIORITY  (EVENT_TRACE_GROUP_THREAD | 0x31)
#define PERFINFO_LOG_TYPE_THREAD_SET_BASE_PRIORITY  (EVENT_TRACE_GROUP_THREAD | 0x31)
#define PERFINFO_LOG_TYPE_READY_THREAD              (EVENT_TRACE_GROUP_THREAD | 0x32)
#define PERFINFO_LOG_TYPE_THREAD_SET_PAGE_PRIORITY  (EVENT_TRACE_GROUP_THREAD | 0x33)
#define PERFINFO_LOG_TYPE_THREAD_SET_IO_PRIORITY    (EVENT_TRACE_GROUP_THREAD | 0x34)
#define PERFINFO_LOG_TYPE_THREAD_SET_AFFINITY       (EVENT_TRACE_GROUP_THREAD | 0x35)
#define PERFINFO_LOG_TYPE_WORKER_THREAD_ITEM        (EVENT_TRACE_GROUP_THREAD | 0x39)
#define PERFINFO_LOG_TYPE_DFSS_START_NEW_INTERVAL   (EVENT_TRACE_GROUP_THREAD | 0x3A)
#define PERFINFO_LOG_TYPE_DFSS_PROCESS_IDLE_ONLY_QUEUE (EVENT_TRACE_GROUP_THREAD | 0x3B)
#define PERFINFO_LOG_TYPE_ANTI_STARVATION_BOOST     (EVENT_TRACE_GROUP_THREAD | 0x3C)
#define PERFINFO_LOG_TYPE_THREAD_MIGRATION          (EVENT_TRACE_GROUP_THREAD | 0x3D)
#define PERFINFO_LOG_TYPE_KQUEUE_ENQUEUE            (EVENT_TRACE_GROUP_THREAD | 0x3E)
#define PERFINFO_LOG_TYPE_KQUEUE_DEQUEUE            (EVENT_TRACE_GROUP_THREAD | 0x3F)
#define PERFINFO_LOG_TYPE_WORKER_THREAD_ITEM_START  (EVENT_TRACE_GROUP_THREAD | 0x40)
#define PERFINFO_LOG_TYPE_WORKER_THREAD_ITEM_END    (EVENT_TRACE_GROUP_THREAD | 0x41)
#define PERFINFO_LOG_TYPE_AUTO_BOOST_SET_FLOOR      (EVENT_TRACE_GROUP_THREAD | 0x42)
#define PERFINFO_LOG_TYPE_AUTO_BOOST_CLEAR_FLOOR    (EVENT_TRACE_GROUP_THREAD | 0x43)
#define PERFINFO_LOG_TYPE_AUTO_BOOST_NO_ENTRIES     (EVENT_TRACE_GROUP_THREAD | 0x44)
#define PERFINFO_LOG_TYPE_THREAD_SUBPROCESSTAG_CHANGED (EVENT_TRACE_GROUP_THREAD | 0x45)

//
// Event types for Network subsystem (TCPIP/UDPIP)
//

#define WMI_LOG_TYPE_TCPIP_SEND                     (EVENT_TRACE_GROUP_TCPIP | EVENT_TRACE_TYPE_SEND)
#define WMI_LOG_TYPE_TCPIP_RECEIVE                  (EVENT_TRACE_GROUP_TCPIP | EVENT_TRACE_TYPE_RECEIVE)
#define WMI_LOG_TYPE_TCPIP_CONNECT                  (EVENT_TRACE_GROUP_TCPIP | EVENT_TRACE_TYPE_CONNECT)
#define WMI_LOG_TYPE_TCPIP_DISCONNECT               (EVENT_TRACE_GROUP_TCPIP | EVENT_TRACE_TYPE_DISCONNECT)
#define WMI_LOG_TYPE_TCPIP_RETRANSMIT               (EVENT_TRACE_GROUP_TCPIP | EVENT_TRACE_TYPE_RETRANSMIT)
#define WMI_LOG_TYPE_TCPIP_ACCEPT                   (EVENT_TRACE_GROUP_TCPIP | EVENT_TRACE_TYPE_ACCEPT)
#define WMI_LOG_TYPE_TCPIP_RECONNECT                (EVENT_TRACE_GROUP_TCPIP | EVENT_TRACE_TYPE_RECONNECT)
#define WMI_LOG_TYPE_TCPIP_FAIL                     (EVENT_TRACE_GROUP_TCPIP | EVENT_TRACE_TYPE_CONNFAIL)
#define WMI_LOG_TYPE_TCPIP_TCPCOPY                  (EVENT_TRACE_GROUP_TCPIP | EVENT_TRACE_TYPE_COPY_TCP)
#define WMI_LOG_TYPE_TCPIP_ARPCOPY                  (EVENT_TRACE_GROUP_TCPIP | EVENT_TRACE_TYPE_COPY_ARP)
#define WMI_LOG_TYPE_TCPIP_FULLACK                  (EVENT_TRACE_GROUP_TCPIP | EVENT_TRACE_TYPE_ACKFULL)
#define WMI_LOG_TYPE_TCPIP_PARTACK                  (EVENT_TRACE_GROUP_TCPIP | EVENT_TRACE_TYPE_ACKPART)
#define WMI_LOG_TYPE_TCPIP_DUPACK                   (EVENT_TRACE_GROUP_TCPIP | EVENT_TRACE_TYPE_ACKDUP)

#define WMI_LOG_TYPE_UDP_SEND                       (EVENT_TRACE_GROUP_UDPIP | EVENT_TRACE_TYPE_SEND)
#define WMI_LOG_TYPE_UDP_RECEIVE                    (EVENT_TRACE_GROUP_UDPIP | EVENT_TRACE_TYPE_RECEIVE)
#define WMI_LOG_TYPE_UDP_FAIL                       (EVENT_TRACE_GROUP_UDPIP | EVENT_TRACE_TYPE_CONNFAIL)

//
// Network events with IPV6
//
#define WMI_LOG_TYPE_TCPIP_SEND_IPV6                (EVENT_TRACE_GROUP_TCPIP | 0x1A)
#define WMI_LOG_TYPE_TCPIP_RECEIVE_IPV6             (EVENT_TRACE_GROUP_TCPIP | 0x1B)
#define WMI_LOG_TYPE_TCPIP_CONNECT_IPV6             (EVENT_TRACE_GROUP_TCPIP | 0x1C)
#define WMI_LOG_TYPE_TCPIP_DISCONNECT_IPV6          (EVENT_TRACE_GROUP_TCPIP | 0x1D)
#define WMI_LOG_TYPE_TCPIP_RETRANSMIT_IPV6          (EVENT_TRACE_GROUP_TCPIP | 0x1E)
#define WMI_LOG_TYPE_TCPIP_ACCEPT_IPV6              (EVENT_TRACE_GROUP_TCPIP | 0x1F)
#define WMI_LOG_TYPE_TCPIP_RECONNECT_IPV6           (EVENT_TRACE_GROUP_TCPIP | 0x20)
#define WMI_LOG_TYPE_TCPIP_FAIL_IPV6                (EVENT_TRACE_GROUP_TCPIP | 0x21)
#define WMI_LOG_TYPE_TCPIP_TCPCOPY_IPV6             (EVENT_TRACE_GROUP_TCPIP | 0x22)
#define WMI_LOG_TYPE_TCPIP_ARPCOPY_IPV6             (EVENT_TRACE_GROUP_TCPIP | 0x23)
#define WMI_LOG_TYPE_TCPIP_FULLACK_IPV6             (EVENT_TRACE_GROUP_TCPIP | 0x24)
#define WMI_LOG_TYPE_TCPIP_PARTACK_IPV6             (EVENT_TRACE_GROUP_TCPIP | 0x25)
#define WMI_LOG_TYPE_TCPIP_DUPACK_IPV6              (EVENT_TRACE_GROUP_TCPIP | 0x26)

#define WMI_LOG_TYPE_UDP_SEND_IPV6                  (EVENT_TRACE_GROUP_UDPIP | 0x1A)
#define WMI_LOG_TYPE_UDP_RECEIVE_IPV6               (EVENT_TRACE_GROUP_UDPIP | 0x1B)

//
// Event types for IO subsystem
//

#define WMI_LOG_TYPE_IO_READ                        (EVENT_TRACE_GROUP_IO | EVENT_TRACE_TYPE_IO_READ)
#define WMI_LOG_TYPE_IO_WRITE                       (EVENT_TRACE_GROUP_IO | EVENT_TRACE_TYPE_IO_WRITE)
#define WMI_LOG_TYPE_IO_READ_INIT                   (EVENT_TRACE_GROUP_IO | EVENT_TRACE_TYPE_IO_READ_INIT)
#define WMI_LOG_TYPE_IO_WRITE_INIT                  (EVENT_TRACE_GROUP_IO | EVENT_TRACE_TYPE_IO_WRITE_INIT)
#define WMI_LOG_TYPE_IO_FLUSH                       (EVENT_TRACE_GROUP_IO | EVENT_TRACE_TYPE_IO_FLUSH)
#define WMI_LOG_TYPE_IO_FLUSH_INIT                  (EVENT_TRACE_GROUP_IO | EVENT_TRACE_TYPE_IO_FLUSH_INIT)
#define WMI_LOG_TYPE_IO_REDIRECTED_INIT             (EVENT_TRACE_GROUP_IO | EVENT_TRACE_TYPE_IO_REDIRECTED_INIT)

#define PERFINFO_LOG_TYPE_DRIVER_INIT                       (EVENT_TRACE_GROUP_IO | 0x20)
#define PERFINFO_LOG_TYPE_DRIVER_INIT_COMPLETE              (EVENT_TRACE_GROUP_IO | 0x21)
#define PERFINFO_LOG_TYPE_DRIVER_MAJORFUNCTION_CALL         (EVENT_TRACE_GROUP_IO | 0x22)
#define PERFINFO_LOG_TYPE_DRIVER_MAJORFUNCTION_RETURN       (EVENT_TRACE_GROUP_IO | 0x23)
#define PERFINFO_LOG_TYPE_DRIVER_COMPLETIONROUTINE_CALL     (EVENT_TRACE_GROUP_IO | 0x24)
#define PERFINFO_LOG_TYPE_DRIVER_COMPLETIONROUTINE_RETURN   (EVENT_TRACE_GROUP_IO | 0x25)
#define PERFINFO_LOG_TYPE_DRIVER_ADD_DEVICE_CALL            (EVENT_TRACE_GROUP_IO | 0x26)
#define PERFINFO_LOG_TYPE_DRIVER_ADD_DEVICE_RETURN          (EVENT_TRACE_GROUP_IO | 0x27)
#define PERFINFO_LOG_TYPE_DRIVER_STARTIO_CALL               (EVENT_TRACE_GROUP_IO | 0x28)
#define PERFINFO_LOG_TYPE_DRIVER_STARTIO_RETURN             (EVENT_TRACE_GROUP_IO | 0x29)
// Reserved                                                 (EVENT_TRACE_GROUP_IO | 0x2a)
// Reserved                                                 (EVENT_TRACE_GROUP_IO | 0x2b)
// Reserved                                                 (EVENT_TRACE_GROUP_IO | 0x2c)
// Reserved                                                 (EVENT_TRACE_GROUP_IO | 0x2d)
// Reserved                                                 (EVENT_TRACE_GROUP_IO | 0x2e)
// Reserved                                                 (EVENT_TRACE_GROUP_IO | 0x2f)
#define PERFINFO_LOG_TYPE_PREFETCH_ACTION                   (EVENT_TRACE_GROUP_IO | 0x30)
#define PERFINFO_LOG_TYPE_PREFETCH_REQUEST                  (EVENT_TRACE_GROUP_IO | 0x31)
#define PERFINFO_LOG_TYPE_PREFETCH_READLIST                 (EVENT_TRACE_GROUP_IO | 0x32)
#define PERFINFO_LOG_TYPE_PREFETCH_READ                     (EVENT_TRACE_GROUP_IO | 0x33)
#define PERFINFO_LOG_TYPE_DRIVER_COMPLETE_REQUEST           (EVENT_TRACE_GROUP_IO | 0x34)
#define PERFINFO_LOG_TYPE_DRIVER_COMPLETE_REQUEST_RETURN    (EVENT_TRACE_GROUP_IO | 0x35)
#define PERFINFO_LOG_TYPE_BOOT_PREFETCH_INFORMATION         (EVENT_TRACE_GROUP_IO | 0x36)
#define PERFINFO_LOG_TYPE_OPTICAL_IO_READ                   (EVENT_TRACE_GROUP_IO | EVENT_TRACE_TYPE_OPTICAL_IO_READ)
#define PERFINFO_LOG_TYPE_OPTICAL_IO_WRITE                  (EVENT_TRACE_GROUP_IO | EVENT_TRACE_TYPE_OPTICAL_IO_WRITE)
#define PERFINFO_LOG_TYPE_OPTICAL_IO_FLUSH                  (EVENT_TRACE_GROUP_IO | EVENT_TRACE_TYPE_OPTICAL_IO_FLUSH)
#define PERFINFO_LOG_TYPE_OPTICAL_IO_READ_INIT              (EVENT_TRACE_GROUP_IO | EVENT_TRACE_TYPE_OPTICAL_IO_READ_INIT)
#define PERFINFO_LOG_TYPE_OPTICAL_IO_WRITE_INIT             (EVENT_TRACE_GROUP_IO | EVENT_TRACE_TYPE_OPTICAL_IO_WRITE_INIT)
#define PERFINFO_LOG_TYPE_OPTICAL_IO_FLUSH_INIT             (EVENT_TRACE_GROUP_IO | EVENT_TRACE_TYPE_OPTICAL_IO_FLUSH_INIT)

//
// Event types for Memory subsystem
//
#define WMI_LOG_TYPE_PAGE_FAULT_TRANSITION         (EVENT_TRACE_GROUP_MEMORY | EVENT_TRACE_TYPE_MM_TF)
#define WMI_LOG_TYPE_PAGE_FAULT_DEMAND_ZERO        (EVENT_TRACE_GROUP_MEMORY | EVENT_TRACE_TYPE_MM_DZF)
#define WMI_LOG_TYPE_PAGE_FAULT_COPY_ON_WRITE      (EVENT_TRACE_GROUP_MEMORY | EVENT_TRACE_TYPE_MM_COW)
#define WMI_LOG_TYPE_PAGE_FAULT_GUARD_PAGE         (EVENT_TRACE_GROUP_MEMORY | EVENT_TRACE_TYPE_MM_GPF)
#define WMI_LOG_TYPE_PAGE_FAULT_HARD_PAGE_FAULT    (EVENT_TRACE_GROUP_MEMORY | EVENT_TRACE_TYPE_MM_HPF)
#define WMI_LOG_TYPE_PAGE_FAULT_ACCESS_VIOLATION   (EVENT_TRACE_GROUP_MEMORY | EVENT_TRACE_TYPE_MM_AV)

#define PERFINFO_LOG_TYPE_HARDFAULT                (EVENT_TRACE_GROUP_MEMORY | 0x20)
#define PERFINFO_LOG_TYPE_REMOVEPAGEBYCOLOR        (EVENT_TRACE_GROUP_MEMORY | 0x21)
#define PERFINFO_LOG_TYPE_REMOVEPAGEFROMLIST       (EVENT_TRACE_GROUP_MEMORY | 0x22)
#define PERFINFO_LOG_TYPE_PAGEINMEMORY             (EVENT_TRACE_GROUP_MEMORY | 0x23)
#define PERFINFO_LOG_TYPE_INSERTINFREELIST         (EVENT_TRACE_GROUP_MEMORY | 0x24)
#define PERFINFO_LOG_TYPE_INSERTINMODIFIEDLIST     (EVENT_TRACE_GROUP_MEMORY | 0x25)
#define PERFINFO_LOG_TYPE_INSERTINLIST             (EVENT_TRACE_GROUP_MEMORY | 0x26)
#define PERFINFO_LOG_TYPE_INSERTATFRONT            (EVENT_TRACE_GROUP_MEMORY | 0x28)
#define PERFINFO_LOG_TYPE_UNLINKFROMSTANDBY        (EVENT_TRACE_GROUP_MEMORY | 0x29)
#define PERFINFO_LOG_TYPE_UNLINKFFREEORZERO        (EVENT_TRACE_GROUP_MEMORY | 0x2a)
#define PERFINFO_LOG_TYPE_WORKINGSETMANAGER        (EVENT_TRACE_GROUP_MEMORY | 0x2b)
#define PERFINFO_LOG_TYPE_TRIMPROCESS              (EVENT_TRACE_GROUP_MEMORY | 0x2c)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x2d)
#define PERFINFO_LOG_TYPE_ZEROSHARECOUNT           (EVENT_TRACE_GROUP_MEMORY | 0x2e)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x2f)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x30)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x31)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x32)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x33)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x34)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x35)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x36)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x37)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x38)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x39)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x3a)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x3b)
#define PERFINFO_LOG_TYPE_WSINFOPROCESS            (EVENT_TRACE_GROUP_MEMORY | 0x3c)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x3d)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x3e)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x3f)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x40)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x41)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x42)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x43)
// Reserved                                        (EVENT_TRACE_GROUP_MEMORY | 0x44)
#define PERFINFO_LOG_TYPE_FAULTADDR_WITH_IP        (EVENT_TRACE_GROUP_MEMORY | 0x45)
#define PERFINFO_LOG_TYPE_TRIMSESSION              (EVENT_TRACE_GROUP_MEMORY | 0x46)
#define PERFINFO_LOG_TYPE_MEMORYSNAPLITE           (EVENT_TRACE_GROUP_MEMORY | 0x47)
#define PERFINFO_LOG_TYPE_PFMAPPED_SECTION_RUNDOWN (EVENT_TRACE_GROUP_MEMORY | 0x48)
#define PERFINFO_LOG_TYPE_PFMAPPED_SECTION_CREATE  (EVENT_TRACE_GROUP_MEMORY | 0x49)
#define PERFINFO_LOG_TYPE_WSINFOSESSION            (EVENT_TRACE_GROUP_MEMORY | 0x4a)
#define PERFINFO_LOG_TYPE_CREATE_SESSION           (EVENT_TRACE_GROUP_MEMORY | 0x4b)
#define PERFINFO_LOG_TYPE_SESSION_RUNDOWN_DC_END   (EVENT_TRACE_GROUP_MEMORY | 0x4c)
#define PERFINFO_LOG_TYPE_SESSION_RUNDOWN_DC_START (EVENT_TRACE_GROUP_MEMORY | 0x4d)
#define PERFINFO_LOG_TYPE_SESSION_DELETE           (EVENT_TRACE_GROUP_MEMORY | 0x4e)
#define PERFINFO_LOG_TYPE_PFMAPPED_SECTION_DELETE  (EVENT_TRACE_GROUP_MEMORY | 0x4f)

#define PERFINFO_LOG_TYPE_VIRTUAL_ALLOC            (EVENT_TRACE_GROUP_MEMORY | 0x62)
#define PERFINFO_LOG_TYPE_VIRTUAL_FREE             (EVENT_TRACE_GROUP_MEMORY | 0x63)
#define PERFINFO_LOG_TYPE_HEAP_RANGE_RUNDOWN       (EVENT_TRACE_GROUP_MEMORY | 0x64)
#define PERFINFO_LOG_TYPE_HEAP_RANGE_CREATE        (EVENT_TRACE_GROUP_MEMORY | 0x65)
#define PERFINFO_LOG_TYPE_HEAP_RANGE_RESERVE       (EVENT_TRACE_GROUP_MEMORY | 0x66)
#define PERFINFO_LOG_TYPE_HEAP_RANGE_RELEASE       (EVENT_TRACE_GROUP_MEMORY | 0x67)
#define PERFINFO_LOG_TYPE_HEAP_RANGE_DESTROY       (EVENT_TRACE_GROUP_MEMORY | 0x68)

#define PERFINFO_LOG_TYPE_PAGEFILE_BACK            (EVENT_TRACE_GROUP_MEMORY | 0x69)
#define PERFINFO_LOG_TYPE_MEMINFO                  (EVENT_TRACE_GROUP_MEMORY | 0x70)
#define PERFINFO_LOG_TYPE_CONTMEM_GENERATE         (EVENT_TRACE_GROUP_MEMORY | 0x71)
#define PERFINFO_LOG_TYPE_FILE_STORE_FAULT         (EVENT_TRACE_GROUP_MEMORY | 0x72)
#define PERFINFO_LOG_TYPE_INMEMORY_STORE_FAULT     (EVENT_TRACE_GROUP_MEMORY | 0x73)
#define PERFINFO_LOG_TYPE_COMPRESSED_PAGE          (EVENT_TRACE_GROUP_MEMORY | 0x74)
#define PERFINFO_LOG_TYPE_PAGEINMEMORY_ACTIVE      (EVENT_TRACE_GROUP_MEMORY | 0x75)
#define PERFINFO_LOG_TYPE_PAGE_ACCESS              (EVENT_TRACE_GROUP_MEMORY | 0x76)
#define PERFINFO_LOG_TYPE_PAGE_RELEASE             (EVENT_TRACE_GROUP_MEMORY | 0x77)
#define PERFINFO_LOG_TYPE_PAGE_RANGE_ACCESS        (EVENT_TRACE_GROUP_MEMORY | 0x78)
#define PERFINFO_LOG_TYPE_PAGE_RANGE_RELEASE       (EVENT_TRACE_GROUP_MEMORY | 0x79)
#define PERFINFO_LOG_TYPE_PAGE_COMBINE             (EVENT_TRACE_GROUP_MEMORY | 0x7a)
#define PERFINFO_LOG_TYPE_KERNEL_MEMUSAGE          (EVENT_TRACE_GROUP_MEMORY | 0x7b)
#define PERFINFO_LOG_TYPE_MM_STATS                 (EVENT_TRACE_GROUP_MEMORY | 0x7c)
#define PERFINFO_LOG_TYPE_MEMINFOEX_WS             (EVENT_TRACE_GROUP_MEMORY | 0x7d)
#define PERFINFO_LOG_TYPE_MEMINFOEX_SESSIONWS      (EVENT_TRACE_GROUP_MEMORY | 0x7e)

#define PERFINFO_LOG_TYPE_VIRTUAL_ROTATE           (EVENT_TRACE_GROUP_MEMORY | 0x7f)
#define PERFINFO_LOG_TYPE_VIRTUAL_ALLOC_DC_START   (EVENT_TRACE_GROUP_MEMORY | 0x80)
#define PERFINFO_LOG_TYPE_VIRTUAL_ALLOC_DC_END     (EVENT_TRACE_GROUP_MEMORY | 0x81)

#define PERFINFO_LOG_TYPE_PAGE_ACCESS_EX           (EVENT_TRACE_GROUP_MEMORY | 0x82)
#define PERFINFO_LOG_TYPE_REMOVEFROMWS             (EVENT_TRACE_GROUP_MEMORY | 0x83)
#define PERFINFO_LOG_TYPE_WSSHAREABLE_RUNDOWN      (EVENT_TRACE_GROUP_MEMORY | 0x84)
#define PERFINFO_LOG_TYPE_INMEMORYACTIVE_RUNDOWN   (EVENT_TRACE_GROUP_MEMORY | 0x85)

#define PERFINFO_LOG_TYPE_MEM_RESET_INFO           (EVENT_TRACE_GROUP_MEMORY | 0x86)
#define PERFINFO_LOG_TYPE_PFMAPPED_SECTION_OBJECT_CREATE  (EVENT_TRACE_GROUP_MEMORY | 0x87)
#define PERFINFO_LOG_TYPE_PFMAPPED_SECTION_OBJECT_DELETE  (EVENT_TRACE_GROUP_MEMORY | 0x88)

//
//
// Event types for Registry subsystem
//
#define WMI_LOG_TYPE_REG_RUNDOWNBEGIN      (EVENT_TRACE_GROUP_REGISTRY | EVENT_TRACE_TYPE_REGKCBRUNDOWNBEGIN)
#define WMI_LOG_TYPE_REG_RUNDOWNEND        (EVENT_TRACE_GROUP_REGISTRY | EVENT_TRACE_TYPE_REGKCBRUNDOWNEND)

#define PERFINFO_LOG_TYPE_CMCELLREFERRED            (EVENT_TRACE_GROUP_REGISTRY | 0x20)
#define PERFINFO_LOG_TYPE_REG_SET_VALUE             (EVENT_TRACE_GROUP_REGISTRY | 0x21)
#define PERFINFO_LOG_TYPE_REG_COUNTERS              (EVENT_TRACE_GROUP_REGISTRY | 0x22)
#define PERFINFO_LOG_TYPE_REG_CONFIG                (EVENT_TRACE_GROUP_REGISTRY | 0x23)
#define PERFINFO_LOG_TYPE_REG_HIVE_INITIALIZE       (EVENT_TRACE_GROUP_REGISTRY | 0x24)
#define PERFINFO_LOG_TYPE_REG_HIVE_DESTROY          (EVENT_TRACE_GROUP_REGISTRY | 0x25)
#define PERFINFO_LOG_TYPE_REG_HIVE_LINK             (EVENT_TRACE_GROUP_REGISTRY | 0x26)
#define PERFINFO_LOG_TYPE_REG_HIVE_RUNDOWN_DC_END   (EVENT_TRACE_GROUP_REGISTRY | 0x27)
#define PERFINFO_LOG_TYPE_REG_HIVE_DIRTY            (EVENT_TRACE_GROUP_REGISTRY | 0x28)
// Reserved
#define PERFINFO_LOG_TYPE_REG_NOTIF_REGISTER        (EVENT_TRACE_GROUP_REGISTRY | 0x30)
#define PERFINFO_LOG_TYPE_REG_NOTIF_DELIVER         (EVENT_TRACE_GROUP_REGISTRY | 0x31)

//
// Event types for PERF tracing specific subsystem
//
#define PERFINFO_LOG_TYPE_RUNDOWN_CHECKPOINT           (EVENT_TRACE_GROUP_PERFINFO | 0x20)
// Reserved                                            (EVENT_TRACE_GROUP_PERFINFO | 0x21)
#define PERFINFO_LOG_TYPE_MARK                         (EVENT_TRACE_GROUP_PERFINFO | 0x22)
// Reserved                                            (EVENT_TRACE_GROUP_PERFINFO | 0x23)
#define PERFINFO_LOG_TYPE_ASYNCMARK                    (EVENT_TRACE_GROUP_PERFINFO | 0x24)
// Reserved                                            (EVENT_TRACE_GROUP_PERFINFO | 0x25)
#define PERFINFO_LOG_TYPE_IMAGENAME                    (EVENT_TRACE_GROUP_PERFINFO | 0x26)
#define PERFINFO_LOG_TYPE_DELAYS_CC_CAN_I_WRITE        (EVENT_TRACE_GROUP_PERFINFO | 0x27)
// Reserved                                            (EVENT_TRACE_GROUP_PERFINFO | 0x28)
// Reserved                                            (EVENT_TRACE_GROUP_PERFINFO | 0x29)
// Reserved                                            (EVENT_TRACE_GROUP_PERFINFO | 0x2a)
// Reserved                                            (EVENT_TRACE_GROUP_PERFINFO | 0x2b)
// Reserved                                            (EVENT_TRACE_GROUP_PERFINFO | 0x2c)
// Reserved                                            (EVENT_TRACE_GROUP_PERFINFO | 0x2d)
#define PERFINFO_LOG_TYPE_SAMPLED_PROFILE              (EVENT_TRACE_GROUP_PERFINFO | 0x2e)
#define PERFINFO_LOG_TYPE_PMC_INTERRUPT                (EVENT_TRACE_GROUP_PERFINFO | 0x2f)
#define PERFINFO_LOG_TYPE_PMC_CONFIG                   (EVENT_TRACE_GROUP_PERFINFO | 0x30)
// Reserved                                            (EVENT_TRACE_GROUP_PERFINFO | 0x31)
#define PERFINFO_LOG_TYPE_MSI_INTERRUPT                (EVENT_TRACE_GROUP_PERFINFO | 0x32)
#define PERFINFO_LOG_TYPE_SYSCALL_ENTER                (EVENT_TRACE_GROUP_PERFINFO | 0x33)
#define PERFINFO_LOG_TYPE_SYSCALL_EXIT                 (EVENT_TRACE_GROUP_PERFINFO | 0x34)
#define PERFINFO_LOG_TYPE_BACKTRACE                    (EVENT_TRACE_GROUP_PERFINFO | 0x35)
#define PERFINFO_LOG_TYPE_BACKTRACE_USERSTACK          (EVENT_TRACE_GROUP_PERFINFO | 0x36)
#define PERFINFO_LOG_TYPE_SAMPLED_PROFILE_CACHE        (EVENT_TRACE_GROUP_PERFINFO | 0x37)
#define PERFINFO_LOG_TYPE_EXCEPTION_STACK              (EVENT_TRACE_GROUP_PERFINFO | 0x38)
#define PERFINFO_LOG_TYPE_BRANCH_TRACE                 (EVENT_TRACE_GROUP_PERFINFO | 0x39)
#define PERFINFO_LOG_TYPE_DEBUGGER_ENABLED             (EVENT_TRACE_GROUP_PERFINFO | 0x3a)
#define PERFINFO_LOG_TYPE_DEBUGGER_EXIT                (EVENT_TRACE_GROUP_PERFINFO | 0x3b)
#define PERFINFO_LOG_TYPE_BRANCH_TRACE_DEBUG           (EVENT_TRACE_GROUP_PERFINFO | 0x40)
#define PERFINFO_LOG_TYPE_BRANCH_ADDRESS_DEBUG         (EVENT_TRACE_GROUP_PERFINFO | 0x41)
#define PERFINFO_LOG_TYPE_THREADED_DPC                 (EVENT_TRACE_GROUP_PERFINFO | 0x42)
#define PERFINFO_LOG_TYPE_INTERRUPT                    (EVENT_TRACE_GROUP_PERFINFO | 0x43)
#define PERFINFO_LOG_TYPE_DPC                          (EVENT_TRACE_GROUP_PERFINFO | 0x44)
#define PERFINFO_LOG_TYPE_TIMERDPC                     (EVENT_TRACE_GROUP_PERFINFO | 0x45)
#define PERFINFO_LOG_TYPE_IOTIMER_EXPIRATION           (EVENT_TRACE_GROUP_PERFINFO | 0x46)
#define PERFINFO_LOG_TYPE_SAMPLED_PROFILE_NMI          (EVENT_TRACE_GROUP_PERFINFO | 0x47)
#define PERFINFO_LOG_TYPE_SAMPLED_PROFILE_SET_INTERVAL (EVENT_TRACE_GROUP_PERFINFO | 0x48)
#define PERFINFO_LOG_TYPE_SAMPLED_PROFILE_DC_START     (EVENT_TRACE_GROUP_PERFINFO | 0x49)
#define PERFINFO_LOG_TYPE_SAMPLED_PROFILE_DC_END       (EVENT_TRACE_GROUP_PERFINFO | 0x4a)
#define PERFINFO_LOG_TYPE_SPINLOCK_DC_START            (EVENT_TRACE_GROUP_PERFINFO | 0x4b)
#define PERFINFO_LOG_TYPE_SPINLOCK_DC_END              (EVENT_TRACE_GROUP_PERFINFO | 0x4c)
#define PERFINFO_LOG_TYPE_ERESOURCE_DC_START           (EVENT_TRACE_GROUP_PERFINFO | 0x4d)
#define PERFINFO_LOG_TYPE_ERESOURCE_DC_END             (EVENT_TRACE_GROUP_PERFINFO | 0x4e)
#define PERFINFO_LOG_TYPE_CLOCK_INTERRUPT              (EVENT_TRACE_GROUP_PERFINFO | 0x4f)
#define PERFINFO_LOG_TYPE_TIMER_EXPIRATION_START       (EVENT_TRACE_GROUP_PERFINFO | 0x50)
#define PERFINFO_LOG_TYPE_TIMER_EXPIRATION             (EVENT_TRACE_GROUP_PERFINFO | 0x51)
#define PERFINFO_LOG_TYPE_TIMER_SET_PERIODIC           (EVENT_TRACE_GROUP_PERFINFO | 0x52)
#define PERFINFO_LOG_TYPE_TIMER_SET_ONE_SHOT           (EVENT_TRACE_GROUP_PERFINFO | 0x53)
#define PERFINFO_LOG_TYPE_TIMER_SET_THREAD             (EVENT_TRACE_GROUP_PERFINFO | 0x54)
#define PERFINFO_LOG_TYPE_TIMER_CANCEL                 (EVENT_TRACE_GROUP_PERFINFO | 0x55)
#define PERFINFO_LOG_TYPE_TIME_ADJUSTMENT              (EVENT_TRACE_GROUP_PERFINFO | 0x56)
#define PERFINFO_LOG_TYPE_CLOCK_MODE_SWITCH            (EVENT_TRACE_GROUP_PERFINFO | 0x57)
#define PERFINFO_LOG_TYPE_CLOCK_TIME_UPDATE            (EVENT_TRACE_GROUP_PERFINFO | 0x58)
#define PERFINFO_LOG_TYPE_CLOCK_DYNAMIC_TICK_VETO      (EVENT_TRACE_GROUP_PERFINFO | 0x59)
#define PERFINFO_LOG_TYPE_CLOCK_CONFIGURATION          (EVENT_TRACE_GROUP_PERFINFO | 0x5a)
#define PERFINFO_LOG_TYPE_IPI                          (EVENT_TRACE_GROUP_PERFINFO | 0x5b)
#define PERFINFO_LOG_TYPE_UNEXPECTED_INTERRUPT         (EVENT_TRACE_GROUP_PERFINFO | 0x5c)
#define PERFINFO_LOG_TYPE_IOTIMER_START                (EVENT_TRACE_GROUP_PERFINFO | 0x5d)
#define PERFINFO_LOG_TYPE_IOTIMER_STOP                 (EVENT_TRACE_GROUP_PERFINFO | 0x5e)
#define PERFINFO_LOG_TYPE_PASSIVE_INTERRUPT            (EVENT_TRACE_GROUP_PERFINFO | 0x5f)
#define PERFINFO_LOG_TYPE_WDF_INTERRUPT                (EVENT_TRACE_GROUP_PERFINFO | 0x60)
#define PERFINFO_LOG_TYPE_WDF_PASSIVE_INTERRUPT        (EVENT_TRACE_GROUP_PERFINFO | 0x61)
#define PERFINFO_LOG_TYPE_WDF_DPC                      (EVENT_TRACE_GROUP_PERFINFO | 0x62)
#define PERFINFO_LOG_TYPE_CPU_CACHE_FLUSH              (EVENT_TRACE_GROUP_PERFINFO | 0x63)
#define PERFINFO_LOG_TYPE_DPC_ENQUEUE                  (EVENT_TRACE_GROUP_PERFINFO | 0x64)
#define PERFINFO_LOG_TYPE_DPC_EXECUTION                (EVENT_TRACE_GROUP_PERFINFO | 0x65)
#define PERFINFO_LOG_TYPE_INTERRUPT_STEERING           (EVENT_TRACE_GROUP_PERFINFO | 0x66)
#define PERFINFO_LOG_TYPE_WDF_WORK_ITEM                (EVENT_TRACE_GROUP_PERFINFO | 0x67)
#define PERFINFO_LOG_TYPE_KTIMER2_SET                  (EVENT_TRACE_GROUP_PERFINFO | 0x68)
#define PERFINFO_LOG_TYPE_KTIMER2_EXPIRATION           (EVENT_TRACE_GROUP_PERFINFO | 0x69)
#define PERFINFO_LOG_TYPE_KTIMER2_CANCEL               (EVENT_TRACE_GROUP_PERFINFO | 0x6a)
#define PERFINFO_LOG_TYPE_KTIMER2_DISABLE              (EVENT_TRACE_GROUP_PERFINFO | 0x6b)
#define PERFINFO_LOG_TYPE_KTIMER2_FINALIZATION         (EVENT_TRACE_GROUP_PERFINFO | 0x6c)
#define PERFINFO_LOG_TYPE_SHOULD_YIELD_PROCESSOR       (EVENT_TRACE_GROUP_PERFINFO | 0x6d)

//
// Event types for ICE.
//

#define PERFINFO_LOG_TYPE_FUNCTION_CALL                (EVENT_TRACE_GROUP_PERFINFO | 0x80)
#define PERFINFO_LOG_TYPE_FUNCTION_RETURN              (EVENT_TRACE_GROUP_PERFINFO | 0x81)
#define PERFINFO_LOG_TYPE_FUNCTION_ENTER               (EVENT_TRACE_GROUP_PERFINFO | 0x82)
#define PERFINFO_LOG_TYPE_FUNCTION_EXIT                (EVENT_TRACE_GROUP_PERFINFO | 0x83)
#define PERFINFO_LOG_TYPE_TAILCALL                     (EVENT_TRACE_GROUP_PERFINFO | 0x84)
#define PERFINFO_LOG_TYPE_TRAP                         (EVENT_TRACE_GROUP_PERFINFO | 0x85)
#define PERFINFO_LOG_TYPE_SPINLOCK_ACQUIRE             (EVENT_TRACE_GROUP_PERFINFO | 0x86)
#define PERFINFO_LOG_TYPE_SPINLOCK_RELEASE             (EVENT_TRACE_GROUP_PERFINFO | 0x87)
#define PERFINFO_LOG_TYPE_CAP_COMMENT                  (EVENT_TRACE_GROUP_PERFINFO | 0x88)
#define PERFINFO_LOG_TYPE_CAP_RUNDOWN                  (EVENT_TRACE_GROUP_PERFINFO | 0x89)

//
// Event types for Debugger subsystem.
//

#define PERFINFO_LOG_TYPE_DEBUG_PRINT                  (EVENT_TRACE_GROUP_DBGPRINT | 0x20)

//
// Event types for WNF facility
//

#define PERFINFO_LOG_TYPE_WNF_SUBSCRIBE                (EVENT_TRACE_GROUP_WNF | 0x20)
#define PERFINFO_LOG_TYPE_WNF_UNSUBSCRIBE              (EVENT_TRACE_GROUP_WNF | 0x21)
#define PERFINFO_LOG_TYPE_WNF_CALLBACK                 (EVENT_TRACE_GROUP_WNF | 0x22)
#define PERFINFO_LOG_TYPE_WNF_PUBLISH                  (EVENT_TRACE_GROUP_WNF | 0x23)
#define PERFINFO_LOG_TYPE_WNF_NAME_SUB_RUNDOWN         (EVENT_TRACE_GROUP_WNF | 0x24)

//
// Event types for Pool subsystem.
//

#define PERFINFO_LOG_TYPE_ALLOCATEPOOL                 (EVENT_TRACE_GROUP_POOL | 0x20)
#define PERFINFO_LOG_TYPE_ALLOCATEPOOL_SESSION         (EVENT_TRACE_GROUP_POOL | 0x21)
#define PERFINFO_LOG_TYPE_FREEPOOL                     (EVENT_TRACE_GROUP_POOL | 0x22)
#define PERFINFO_LOG_TYPE_FREEPOOL_SESSION             (EVENT_TRACE_GROUP_POOL | 0x23)
#define PERFINFO_LOG_TYPE_ADDPOOLPAGE                  (EVENT_TRACE_GROUP_POOL | 0x24)
#define PERFINFO_LOG_TYPE_ADDPOOLPAGE_SESSION          (EVENT_TRACE_GROUP_POOL | 0x25)
#define PERFINFO_LOG_TYPE_BIGPOOLPAGE                  (EVENT_TRACE_GROUP_POOL | 0x26)
#define PERFINFO_LOG_TYPE_BIGPOOLPAGE_SESSION          (EVENT_TRACE_GROUP_POOL | 0x27)
#define PERFINFO_LOG_TYPE_POOLSNAP_DC_START            (EVENT_TRACE_GROUP_POOL | 0x28)
#define PERFINFO_LOG_TYPE_POOLSNAP_DC_END              (EVENT_TRACE_GROUP_POOL | 0x29)
#define PERFINFO_LOG_TYPE_BIGPOOLSNAP_DC_START         (EVENT_TRACE_GROUP_POOL | 0x2a)
#define PERFINFO_LOG_TYPE_BIGPOOLSNAP_DC_END           (EVENT_TRACE_GROUP_POOL | 0x2b)
#define PERFINFO_LOG_TYPE_POOLSNAP_SESSION_DC_START    (EVENT_TRACE_GROUP_POOL | 0x2c)
#define PERFINFO_LOG_TYPE_POOLSNAP_SESSION_DC_END      (EVENT_TRACE_GROUP_POOL | 0x2d)
#define PERFINFO_LOG_TYPE_SESSIONBIGPOOLSNAP_DC_START  (EVENT_TRACE_GROUP_POOL | 0x2e)
#define PERFINFO_LOG_TYPE_SESSIONBIGPOOLSNAP_DC_END    (EVENT_TRACE_GROUP_POOL | 0x2f)

//
// Event types for Heap subsystem
//
#define PERFINFO_LOG_TYPE_HEAP_CREATE                  (EVENT_TRACE_GROUP_HEAP | 0x20)
#define PERFINFO_LOG_TYPE_HEAP_ALLOC                   (EVENT_TRACE_GROUP_HEAP | 0x21)
#define PERFINFO_LOG_TYPE_HEAP_REALLOC                 (EVENT_TRACE_GROUP_HEAP | 0x22)
#define PERFINFO_LOG_TYPE_HEAP_DESTROY                 (EVENT_TRACE_GROUP_HEAP | 0x23)
#define PERFINFO_LOG_TYPE_HEAP_FREE                    (EVENT_TRACE_GROUP_HEAP | 0x24)
#define PERFINFO_LOG_TYPE_HEAP_EXTEND                  (EVENT_TRACE_GROUP_HEAP | 0x25)
#define PERFINFO_LOG_TYPE_HEAP_SNAPSHOT                (EVENT_TRACE_GROUP_HEAP | 0x26)
#define PERFINFO_LOG_TYPE_HEAP_CREATE_SNAPSHOT         (EVENT_TRACE_GROUP_HEAP | 0x27)
#define PERFINFO_LOG_TYPE_HEAP_DESTROY_SNAPSHOT        (EVENT_TRACE_GROUP_HEAP | 0x28)
#define PERFINFO_LOG_TYPE_HEAP_EXTEND_SNAPSHOT         (EVENT_TRACE_GROUP_HEAP | 0x29)
#define PERFINFO_LOG_TYPE_HEAP_CONTRACT                (EVENT_TRACE_GROUP_HEAP | 0x2a)
#define PERFINFO_LOG_TYPE_HEAP_LOCK                    (EVENT_TRACE_GROUP_HEAP | 0x2b)
#define PERFINFO_LOG_TYPE_HEAP_UNLOCK                  (EVENT_TRACE_GROUP_HEAP | 0x2c)
#define PERFINFO_LOG_TYPE_HEAP_VALIDATE                (EVENT_TRACE_GROUP_HEAP | 0x2d)
#define PERFINFO_LOG_TYPE_HEAP_WALK                    (EVENT_TRACE_GROUP_HEAP | 0x2e)

#define PERFINFO_LOG_TYPE_HEAP_SUBSEGMENT_ALLOC          (EVENT_TRACE_GROUP_HEAP | 0x2f)
#define PERFINFO_LOG_TYPE_HEAP_SUBSEGMENT_FREE           (EVENT_TRACE_GROUP_HEAP | 0x30)
#define PERFINFO_LOG_TYPE_HEAP_SUBSEGMENT_ALLOC_CACHE    (EVENT_TRACE_GROUP_HEAP | 0x31)
#define PERFINFO_LOG_TYPE_HEAP_SUBSEGMENT_FREE_CACHE     (EVENT_TRACE_GROUP_HEAP | 0x32)
#define PERFINFO_LOG_TYPE_HEAP_COMMIT                    (EVENT_TRACE_GROUP_HEAP | 0x33)
#define PERFINFO_LOG_TYPE_HEAP_DECOMMIT                  (EVENT_TRACE_GROUP_HEAP | 0x34)
#define PERFINFO_LOG_TYPE_HEAP_SUBSEGMENT_INIT           (EVENT_TRACE_GROUP_HEAP | 0x35)
#define PERFINFO_LOG_TYPE_HEAP_AFFINITY_ENABLE           (EVENT_TRACE_GROUP_HEAP | 0x36)
//Reserved                                               (EVENT_TRACE_GROUP_HEAP | 0x37)
#define PERFINFO_LOG_TYPE_HEAP_SUBSEGMENT_ACTIVATED      (EVENT_TRACE_GROUP_HEAP | 0x38)
#define PERFINFO_LOG_TYPE_HEAP_AFFINITY_ASSIGN           (EVENT_TRACE_GROUP_HEAP | 0x39)
#define PERFINFO_LOG_TYPE_HEAP_REUSE_THRESHOLD_ACTIVATED (EVENT_TRACE_GROUP_HEAP | 0x3a)

//
// Event Types for Critical Section Subsystem
//

#define PERFINFO_LOG_TYPE_CRITSEC_ENTER                (EVENT_TRACE_GROUP_CRITSEC | 0x20)
#define PERFINFO_LOG_TYPE_CRITSEC_LEAVE                (EVENT_TRACE_GROUP_CRITSEC | 0x21)
#define PERFINFO_LOG_TYPE_CRITSEC_COLLISION            (EVENT_TRACE_GROUP_CRITSEC | 0x22)
#define PERFINFO_LOG_TYPE_CRITSEC_INITIALIZE           (EVENT_TRACE_GROUP_CRITSEC | 0x23)

//
// Event types for Stackwalk subsystem
//

#define PERFINFO_LOG_TYPE_STACKWALK                    (EVENT_TRACE_GROUP_STACKWALK | 0x20)
//Reserved                                             (EVENT_TRACE_GROUP_STACKWALK | 0x21)
#define PERFINFO_LOG_TYPE_STACKTRACE_CREATE            (EVENT_TRACE_GROUP_STACKWALK | 0x22)
#define PERFINFO_LOG_TYPE_STACKTRACE_DELETE            (EVENT_TRACE_GROUP_STACKWALK | 0x23)
#define PERFINFO_LOG_TYPE_STACKTRACE_RUNDOWN           (EVENT_TRACE_GROUP_STACKWALK | 0x24)
#define PERFINFO_LOG_TYPE_STACKTRACE_KEY_KERNEL        (EVENT_TRACE_GROUP_STACKWALK | 0x25)
#define PERFINFO_LOG_TYPE_STACKTRACE_KEY_USER          (EVENT_TRACE_GROUP_STACKWALK | 0x26)

//
// Event types for ALPC
//

#define WMI_LOG_TYPE_ALPC_SEND_MESSAGE                  (EVENT_TRACE_GROUP_ALPC | 0x21)
#define WMI_LOG_TYPE_ALPC_RECEIVE_MESSAGE               (EVENT_TRACE_GROUP_ALPC | 0x22)
#define WMI_LOG_TYPE_ALPC_WAIT_FOR_REPLY                (EVENT_TRACE_GROUP_ALPC | 0x23)
#define WMI_LOG_TYPE_ALPC_WAIT_FOR_NEW_MESSAGE          (EVENT_TRACE_GROUP_ALPC | 0x24)
#define WMI_LOG_TYPE_ALPC_UNWAIT                        (EVENT_TRACE_GROUP_ALPC | 0x25)
#define WMI_LOG_TYPE_ALPC_CONNECT_REQUEST               (EVENT_TRACE_GROUP_ALPC | 0x26)
#define WMI_LOG_TYPE_ALPC_CONNECT_SUCCESS               (EVENT_TRACE_GROUP_ALPC | 0x27)
#define WMI_LOG_TYPE_ALPC_CONNECT_FAIL                  (EVENT_TRACE_GROUP_ALPC | 0x28)
#define WMI_LOG_TYPE_ALPC_CLOSE_PORT                    (EVENT_TRACE_GROUP_ALPC | 0x29)


//
// Event types for Object Manager subsystem
//

#define PERFINFO_LOG_TYPE_CREATE_HANDLE                (EVENT_TRACE_GROUP_OBJECT | 0x20)
#define PERFINFO_LOG_TYPE_CLOSE_HANDLE                 (EVENT_TRACE_GROUP_OBJECT | 0x21)
#define PERFINFO_LOG_TYPE_DUPLICATE_HANDLE             (EVENT_TRACE_GROUP_OBJECT | 0x22)
//Reserved                                             (EVENT_TRACE_GROUP_OBJECT | 0x23)
#define PERFINFO_LOG_TYPE_OBJECT_TYPE_DC_START         (EVENT_TRACE_GROUP_OBJECT | 0x24)
#define PERFINFO_LOG_TYPE_OBJECT_TYPE_DC_END           (EVENT_TRACE_GROUP_OBJECT | 0x25)
#define PERFINFO_LOG_TYPE_OBJECT_HANDLE_DC_START       (EVENT_TRACE_GROUP_OBJECT | 0x26)
#define PERFINFO_LOG_TYPE_OBJECT_HANDLE_DC_END         (EVENT_TRACE_GROUP_OBJECT | 0x27)
//Reserved                                             (EVENT_TRACE_GROUP_OBJECT | 0x28)
//Reserved                                             (EVENT_TRACE_GROUP_OBJECT | 0x29)
//Reserved                                             (EVENT_TRACE_GROUP_OBJECT | 0x2a)
//Reserved                                             (EVENT_TRACE_GROUP_OBJECT | 0x2b)
//Reserved                                             (EVENT_TRACE_GROUP_OBJECT | 0x2c)
//Reserved                                             (EVENT_TRACE_GROUP_OBJECT | 0x2d)
//Reserved                                             (EVENT_TRACE_GROUP_OBJECT | 0x2e)
//Reserved                                             (EVENT_TRACE_GROUP_OBJECT | 0x2f)
#define PERFINFO_LOG_TYPE_CREATE_OBJECT                (EVENT_TRACE_GROUP_OBJECT | 0x30)
#define PERFINFO_LOG_TYPE_DELETE_OBJECT                (EVENT_TRACE_GROUP_OBJECT | 0x31)
#define PERFINFO_LOG_TYPE_REFERENCE_OBJECT             (EVENT_TRACE_GROUP_OBJECT | 0x32)
#define PERFINFO_LOG_TYPE_DEREFERENCE_OBJECT           (EVENT_TRACE_GROUP_OBJECT | 0x33)

//
// Event types for Power subsystem
//

#define PERFINFO_LOG_TYPE_BATTERY_LIFE_INFO            (EVENT_TRACE_GROUP_POWER | 0x20)
#define PERFINFO_LOG_TYPE_IDLE_STATE_CHANGE            (EVENT_TRACE_GROUP_POWER | 0x21)
#define PERFINFO_LOG_TYPE_SET_POWER_ACTION             (EVENT_TRACE_GROUP_POWER | 0x22)
#define PERFINFO_LOG_TYPE_SET_POWER_ACTION_RET         (EVENT_TRACE_GROUP_POWER | 0x23)
#define PERFINFO_LOG_TYPE_SET_DEVICES_STATE            (EVENT_TRACE_GROUP_POWER | 0x24)
#define PERFINFO_LOG_TYPE_SET_DEVICES_STATE_RET        (EVENT_TRACE_GROUP_POWER | 0x25)
#define PERFINFO_LOG_TYPE_PO_NOTIFY_DEVICE             (EVENT_TRACE_GROUP_POWER | 0x26)
#define PERFINFO_LOG_TYPE_PO_NOTIFY_DEVICE_COMPLETE    (EVENT_TRACE_GROUP_POWER | 0x27)
#define PERFINFO_LOG_TYPE_PO_SESSION_CALLOUT           (EVENT_TRACE_GROUP_POWER | 0x28)
#define PERFINFO_LOG_TYPE_PO_SESSION_CALLOUT_RET       (EVENT_TRACE_GROUP_POWER | 0x29)
#define PERFINFO_LOG_TYPE_PO_PRESLEEP                  (EVENT_TRACE_GROUP_POWER | 0x30)
#define PERFINFO_LOG_TYPE_PO_POSTSLEEP                 (EVENT_TRACE_GROUP_POWER | 0x31)
#define PERFINFO_LOG_TYPE_PO_CALIBRATED_PERFCOUNTER    (EVENT_TRACE_GROUP_POWER | 0x32)
#define PERFINFO_LOG_TYPE_PPM_PERF_STATE_CHANGE        (EVENT_TRACE_GROUP_POWER | 0x33)
#define PERFINFO_LOG_TYPE_PPM_THROTTLE_STATE_CHANGE    (EVENT_TRACE_GROUP_POWER | 0x34)
#define PERFINFO_LOG_TYPE_PPM_IDLE_STATE_CHANGE        (EVENT_TRACE_GROUP_POWER | 0x35)
#define PERFINFO_LOG_TYPE_PPM_THERMAL_CONSTRAINT       (EVENT_TRACE_GROUP_POWER | 0x36)
#define PERFINFO_LOG_TYPE_PO_SIGNAL_RESUME_UI          (EVENT_TRACE_GROUP_POWER | 0x37)
#define PERFINFO_LOG_TYPE_PO_SIGNAL_VIDEO_ON           (EVENT_TRACE_GROUP_POWER | 0x38)
#define PERFINFO_LOG_TYPE_PPM_IDLE_STATE_ENTER         (EVENT_TRACE_GROUP_POWER | 0x39)
#define PERFINFO_LOG_TYPE_PPM_IDLE_STATE_EXIT          (EVENT_TRACE_GROUP_POWER | 0x3a)
#define PERFINFO_LOG_TYPE_PPM_PLATFORM_IDLE_STATE_ENTER (EVENT_TRACE_GROUP_POWER | 0x3b)
#define PERFINFO_LOG_TYPE_PPM_IDLE_EXIT_LATENCY        (EVENT_TRACE_GROUP_POWER | 0x3c)
#define PERFINFO_LOG_TYPE_PPM_IDLE_PROCESSOR_SELECTION (EVENT_TRACE_GROUP_POWER | 0x3d)
#define PERFINFO_LOG_TYPE_PPM_IDLE_PLATFORM_SELECTION  (EVENT_TRACE_GROUP_POWER | 0x3e)
#define PERFINFO_LOG_TYPE_PPM_COORDINATED_IDLE_ENTER   (EVENT_TRACE_GROUP_POWER | 0x3f)
#define PERFINFO_LOG_TYPE_PPM_COORDINATED_IDLE_EXIT    (EVENT_TRACE_GROUP_POWER | 0x40)

//
// Event types for MODBound subsystem
//
#define PERFINFO_LOG_TYPE_COWHEADER                    (EVENT_TRACE_GROUP_MODBOUND | 0x18)
#define PERFINFO_LOG_TYPE_COWBLOB                      (EVENT_TRACE_GROUP_MODBOUND | 0x19)
#define PERFINFO_LOG_TYPE_COWBLOB_CLOSED               (EVENT_TRACE_GROUP_MODBOUND | 0x1a)
#define PERFINFO_LOG_TYPE_MODULEBOUND_ENT              (EVENT_TRACE_GROUP_MODBOUND | 0x20)
#define PERFINFO_LOG_TYPE_MODULEBOUND_JUMP             (EVENT_TRACE_GROUP_MODBOUND | 0x21)
#define PERFINFO_LOG_TYPE_MODULEBOUND_RET              (EVENT_TRACE_GROUP_MODBOUND | 0x22)
#define PERFINFO_LOG_TYPE_MODULEBOUND_CALL             (EVENT_TRACE_GROUP_MODBOUND | 0x23)
#define PERFINFO_LOG_TYPE_MODULEBOUND_CALLRET          (EVENT_TRACE_GROUP_MODBOUND | 0x24)
#define PERFINFO_LOG_TYPE_MODULEBOUND_INT2E            (EVENT_TRACE_GROUP_MODBOUND | 0x25)
#define PERFINFO_LOG_TYPE_MODULEBOUND_INT2B            (EVENT_TRACE_GROUP_MODBOUND | 0x26)
#define PERFINFO_LOG_TYPE_MODULEBOUND_FULLTRACE        (EVENT_TRACE_GROUP_MODBOUND | 0x27)

//
// Event types for the thread class scheduler
//
// TODO: Because MMCSS is a DLL it doesn't need to use UMGL.
//
#define PERFINFO_LOG_TYPE_MMCSS_START                  (0x20)
#define PERFINFO_LOG_TYPE_MMCSS_STOP                   (0x21)
#define PERFINFO_LOG_TYPE_MMCSS_SCHEDULER_EVENT        (0x22)
#define PERFINFO_LOG_TYPE_MMCSS_SCHEDULER_WAKEUP       (0x23)
#define PERFINFO_LOG_TYPE_MMCSS_SCHEDULER_SLEEP        (0x24)
#define PERFINFO_LOG_TYPE_MMCSS_SCHEDULER_SLEEP_RESP   (0x25)


//
// Event types for SplitIo
//

#define PERFINFO_LOG_TYPE_SPLITIO_VOLMGR                    (EVENT_TRACE_GROUP_SPLITIO | 0x20)

// Event types for ThreadPool
#define PERFINFO_LOG_TYPE_TP_CALLBACK_ENQUEUE               (EVENT_TRACE_GROUP_THREAD_POOL | 0x20)
#define PERFINFO_LOG_TYPE_TP_CALLBACK_DEQUEUE               (EVENT_TRACE_GROUP_THREAD_POOL | 0x21)
#define PERFINFO_LOG_TYPE_TP_CALLBACK_START                 (EVENT_TRACE_GROUP_THREAD_POOL | 0x22)
#define PERFINFO_LOG_TYPE_TP_CALLBACK_STOP                  (EVENT_TRACE_GROUP_THREAD_POOL | 0x23)
#define PERFINFO_LOG_TYPE_TP_CALLBACK_CANCEL                (EVENT_TRACE_GROUP_THREAD_POOL | 0x24)
#define PERFINFO_LOG_TYPE_TP_POOL_CREATE                    (EVENT_TRACE_GROUP_THREAD_POOL | 0x25)
#define PERFINFO_LOG_TYPE_TP_POOL_CLOSE                     (EVENT_TRACE_GROUP_THREAD_POOL | 0x26)
#define PERFINFO_LOG_TYPE_TP_POOL_TH_MIN_SET                (EVENT_TRACE_GROUP_THREAD_POOL | 0x27)
#define PERFINFO_LOG_TYPE_TP_POOL_TH_MAX_SET                (EVENT_TRACE_GROUP_THREAD_POOL | 0x28)
#define PERFINFO_LOG_TYPE_TP_WORKER_NUMANODE_SWITCH         (EVENT_TRACE_GROUP_THREAD_POOL | 0x29)
#define PERFINFO_LOG_TYPE_TP_TIMER_SET                      (EVENT_TRACE_GROUP_THREAD_POOL | 0x2a)
#define PERFINFO_LOG_TYPE_TP_TIMER_CANCELLED                (EVENT_TRACE_GROUP_THREAD_POOL | 0x2b)
#define PERFINFO_LOG_TYPE_TP_TIMER_SET_NTTIMER              (EVENT_TRACE_GROUP_THREAD_POOL | 0x2c)
#define PERFINFO_LOG_TYPE_TP_TIMER_CANCEL_NTTIMER           (EVENT_TRACE_GROUP_THREAD_POOL | 0x2d)
#define PERFINFO_LOG_TYPE_TP_TIMER_EXPIRATION_BEGIN         (EVENT_TRACE_GROUP_THREAD_POOL | 0x2e)
#define PERFINFO_LOG_TYPE_TP_TIMER_EXPIRATION_END           (EVENT_TRACE_GROUP_THREAD_POOL | 0x2f)
#define PERFINFO_LOG_TYPE_TP_TIMER_EXPIRATION               (EVENT_TRACE_GROUP_THREAD_POOL | 0x30)

// Event types for UMS
#define PERFINFO_LOG_TYPE_UMS_DIRECTED_SWITCH_START         (EVENT_TRACE_GROUP_UMS | 0x20)
#define PERFINFO_LOG_TYPE_UMS_DIRECTED_SWITCH_END           (EVENT_TRACE_GROUP_UMS | 0x21)
#define PERFINFO_LOG_TYPE_UMS_PARK                          (EVENT_TRACE_GROUP_UMS | 0x22)
#define PERFINFO_LOG_TYPE_UMS_DISASSOCIATE                  (EVENT_TRACE_GROUP_UMS | 0x23)
#define PERFINFO_LOG_TYPE_UMS_CONTEXT_SWITCH                (EVENT_TRACE_GROUP_UMS | 0x24)

// Event types for Cache manager
#define PERFINFO_LOG_TYPE_CC_WORKITEM_ENQUEUE               (EVENT_TRACE_GROUP_CC | 0x00)
#define PERFINFO_LOG_TYPE_CC_WORKITEM_DEQUEUE               (EVENT_TRACE_GROUP_CC | 0x01)
#define PERFINFO_LOG_TYPE_CC_WORKITEM_COMPLETE              (EVENT_TRACE_GROUP_CC | 0x02)
#define PERFINFO_LOG_TYPE_CC_READ_AHEAD                     (EVENT_TRACE_GROUP_CC | 0x03)
#define PERFINFO_LOG_TYPE_CC_WRITE_BEHIND                   (EVENT_TRACE_GROUP_CC | 0x04)
#define PERFINFO_LOG_TYPE_CC_LAZY_WRITE_SCAN                (EVENT_TRACE_GROUP_CC | 0x05)
#define PERFINFO_LOG_TYPE_CC_CAN_I_WRITE_FAIL               (EVENT_TRACE_GROUP_CC | 0x06)
//#define PERFINFO_LOG_TYPE_CC_MAP_VIEW                       (EVENT_TRACE_GROUP_CC | 0x07)
//#define PERFINFO_LOG_TYPE_CC_UNMAP_VIEW                     (EVENT_TRACE_GROUP_CC | 0x08)
#define PERFINFO_LOG_TYPE_CC_FLUSH_CACHE                    (EVENT_TRACE_GROUP_CC | 0x09)
#define PERFINFO_LOG_TYPE_CC_FLUSH_SECTION                  (EVENT_TRACE_GROUP_CC | 0x0a)
#define PERFINFO_LOG_TYPE_CC_READ_AHEAD_PREFETCH            (EVENT_TRACE_GROUP_CC | 0x0b)
#define PERFINFO_LOG_TYPE_CC_SCHEDULE_READ_AHEAD            (EVENT_TRACE_GROUP_CC | 0x0c)
#define PERFINFO_LOG_TYPE_CC_LOGGED_STREAM_INFO             (EVENT_TRACE_GROUP_CC | 0x0d)
#define PERFINFO_LOG_TYPE_CC_EXTRA_WRITEBEHIND_THREAD       (EVENT_TRACE_GROUP_CC | 0x0e)

typedef ULONG PERFINFO_MASK;

typedef struct _PERFINFO_GROUPMASK
{
    ULONG Masks[PERF_NUM_MASKS];
} PERFINFO_GROUPMASK, * PPERFINFO_GROUPMASK;

typedef struct _EVENT_TRACE_VERSION_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    ULONG EventTraceKernelVersion;
} EVENT_TRACE_VERSION_INFORMATION, * PEVENT_TRACE_VERSION_INFORMATION;

typedef struct _EVENT_TRACE_GROUPMASK_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    TRACEHANDLE TraceHandle;
    PERFINFO_GROUPMASK EventTraceGroupMasks;
} EVENT_TRACE_GROUPMASK_INFORMATION, * PEVENT_TRACE_GROUPMASK_INFORMATION;

typedef struct _EVENT_TRACE_PERFORMANCE_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    LARGE_INTEGER LogfileBytesWritten;
} EVENT_TRACE_PERFORMANCE_INFORMATION, * PEVENT_TRACE_PERFORMANCE_INFORMATION;

typedef struct _EVENT_TRACE_TIME_PROFILE_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    ULONG ProfileInterval;
} EVENT_TRACE_TIME_PROFILE_INFORMATION, * PEVENT_TRACE_TIME_PROFILE_INFORMATION;

typedef struct _EVENT_TRACE_SESSION_SECURITY_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    ULONG SecurityInformation;
    TRACEHANDLE TraceHandle;
    UCHAR SecurityDescriptor[1];
} EVENT_TRACE_SESSION_SECURITY_INFORMATION, * PEVENT_TRACE_SESSION_SECURITY_INFORMATION;

typedef struct _EVENT_TRACE_SPINLOCK_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    ULONG SpinLockSpinThreshold;
    ULONG SpinLockAcquireSampleRate;
    ULONG SpinLockContentionSampleRate;
    ULONG SpinLockHoldThreshold;
} EVENT_TRACE_SPINLOCK_INFORMATION, * PEVENT_TRACE_SPINLOCK_INFORMATION;

typedef struct _EVENT_TRACE_SYSTEM_EVENT_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    TRACEHANDLE TraceHandle;
    ULONG HookId[1];
} EVENT_TRACE_SYSTEM_EVENT_INFORMATION, * PEVENT_TRACE_SYSTEM_EVENT_INFORMATION;

typedef EVENT_TRACE_SYSTEM_EVENT_INFORMATION EVENT_TRACE_STACK_TRACING_INFORMATION, * PEVENT_TRACE_STACK_TRACING_INFORMATION;
typedef EVENT_TRACE_SYSTEM_EVENT_INFORMATION EVENT_TRACE_PEBS_TRACING_INFORMATION, * PEVENT_TRACE_PEBS_TRACING_INFORMATION;
typedef EVENT_TRACE_SYSTEM_EVENT_INFORMATION EVENT_TRACE_PROFILE_EVENT_INFORMATION, * PEVENT_TRACE_PROFILE_EVENT_INFORMATION;

typedef struct _EVENT_TRACE_EXECUTIVE_RESOURCE_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    ULONG ReleaseSamplingRate;
    ULONG ContentionSamplingRate;
    ULONG NumberOfExcessiveTimeouts;
} EVENT_TRACE_EXECUTIVE_RESOURCE_INFORMATION, * PEVENT_TRACE_EXECUTIVE_RESOURCE_INFORMATION;

typedef struct _EVENT_TRACE_HEAP_TRACING_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    ULONG ProcessId[1];
} EVENT_TRACE_HEAP_TRACING_INFORMATION, * PEVENT_TRACE_HEAP_TRACING_INFORMATION;

typedef struct _EVENT_TRACE_TAG_FILTER_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    TRACEHANDLE TraceHandle;
    ULONG Filter[1];
} EVENT_TRACE_TAG_FILTER_INFORMATION, * PEVENT_TRACE_TAG_FILTER_INFORMATION;

typedef EVENT_TRACE_TAG_FILTER_INFORMATION EVENT_TRACE_POOLTAG_FILTER_INFORMATION, * PEVENT_TRACE_POOLTAG_FILTER_INFORMATION;
typedef EVENT_TRACE_TAG_FILTER_INFORMATION EVENT_TRACE_OBJECT_TYPE_FILTER_INFORMATION, * PEVENT_TRACE_OBJECT_TYPE_FILTER_INFORMATION;

// ProfileSource
#define ETW_MAX_PROFILING_SOURCES 4
#define ETW_MAX_PMC_EVENTS        4
#define ETW_MAX_PMC_COUNTERS      4

typedef struct _EVENT_TRACE_PROFILE_COUNTER_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    TRACEHANDLE TraceHandle;
    ULONG ProfileSource[1];
} EVENT_TRACE_PROFILE_COUNTER_INFORMATION, * PEVENT_TRACE_PROFILE_COUNTER_INFORMATION;

typedef EVENT_TRACE_PROFILE_COUNTER_INFORMATION EVENT_TRACE_PROFILE_CONFIG_INFORMATION, * PEVENT_TRACE_PROFILE_CONFIG_INFORMATION;

//typedef struct _PROFILE_SOURCE_INFO
//{
//    ULONG NextEntryOffset;
//    ULONG Source;
//    ULONG MinInterval;
//    ULONG MaxInterval;
//    PVOID Reserved;
//    WCHAR Description[1];
//} PROFILE_SOURCE_INFO, *PPROFILE_SOURCE_INFO;

typedef struct _PROFILE_SOURCE_INFO* PPROFILE_SOURCE_INFO;

typedef struct _EVENT_TRACE_PROFILE_LIST_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    ULONG Spare;
    PPROFILE_SOURCE_INFO Profile[1];
} EVENT_TRACE_PROFILE_LIST_INFORMATION, * PEVENT_TRACE_PROFILE_LIST_INFORMATION;

typedef struct _EVENT_TRACE_STACK_CACHING_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    TRACEHANDLE TraceHandle;
    BOOLEAN Enabled;
    UCHAR Reserved[3];
    ULONG CacheSize;
    ULONG BucketCount;
} EVENT_TRACE_STACK_CACHING_INFORMATION, * PEVENT_TRACE_STACK_CACHING_INFORMATION;

typedef struct _EVENT_TRACE_SOFT_RESTART_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    TRACEHANDLE TraceHandle;
    BOOLEAN PersistTraceBuffers;
    WCHAR FileName[1];
} EVENT_TRACE_SOFT_RESTART_INFORMATION, * PEVENT_TRACE_SOFT_RESTART_INFORMATION;

typedef struct _EVENT_TRACE_PROFILE_ADD_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    BOOLEAN PerfEvtEventSelect;
    BOOLEAN PerfEvtUnitSelect;
    ULONG PerfEvtType;
    ULONG CpuInfoHierarchy[0x3];
    ULONG InitialInterval;
    BOOLEAN AllowsHalt;
    BOOLEAN Persist;
    WCHAR ProfileSourceDescription[0x1];
} EVENT_TRACE_PROFILE_ADD_INFORMATION, * PEVENT_TRACE_PROFILE_ADD_INFORMATION;

typedef struct _EVENT_TRACE_PROFILE_REMOVE_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    KPROFILE_SOURCE ProfileSource;
    ULONG CpuInfoHierarchy[0x3];
} EVENT_TRACE_PROFILE_REMOVE_INFORMATION, * PEVENT_TRACE_PROFILE_REMOVE_INFORMATION;

typedef struct _EVENT_TRACE_COVERAGE_SAMPLER_INFORMATION
{
    EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
    UCHAR CoverageSamplerInformationClass;
    UCHAR MajorVersion;
    UCHAR MinorVersion;
    UCHAR Reserved;
    HANDLE SamplerHandle;
} EVENT_TRACE_COVERAGE_SAMPLER_INFORMATION, * PEVENT_TRACE_COVERAGE_SAMPLER_INFORMATION;


//
// Maximum supported buffer size in KB - Win8 (16MB)
//
// N.B. Prior to Win8 the value was 1MB (1024KB).
#define MIN_ETW_BUFFER_SIZE      1             // in KBytes
#define MAX_ETW_BUFFER_SIZE      (16 * 1024)   // in KBytes
#define MAX_ETW_BUFFER_SIZE_WIN7 (1 * 1024)    // in KBytes
#define MAX_ETW_EVENT_SIZE       0xFFFF        // MAX_USHORT

#define ETW_KERNEL_RUNDOWN_START 0x00000001
#define ETW_KERNEL_RUNDOWN_STOP  0x00000002
#define ETW_CKCL_RUNDOWN_START   0x00000004
#define ETW_CKCL_RUNDOWN_STOP    0x00000008
#define ETW_FILENAME_RUNDOWN     0x00000010

#if !defined(_KERNEL_MODE)

//
// Constants for UMGL (User Mode Global Logging).
//
// N.B. There is enough space reserved in UserSharedData
//      to support up to 16 providers, but to avoid needless
//      scanning MAX_PROVIDERS constant is currently set to 8.
//
// N.B. Heap and CritSec providers can be controlled with IFEO
//      making the indexes fixed.
#define ETW_UMGL_INDEX_HEAP             0
#define ETW_UMGL_INDEX_CRITSEC          1
#define ETW_UMGL_INDEX_LDR              2
#define ETW_UMGL_INDEX_THREAD_POOL      3
#define ETW_UMGL_INDEX_HEAPRANGE        4
#define ETW_UMGL_INDEX_HEAPSUMMARY      5
#define ETW_UMGL_INDEX_UMS              6
#define ETW_UMGL_INDEX_WNF              7
#define ETW_UMGL_INDEX_THREAD           8
#define ETW_UMGL_INDEX_SPARE2           9
#define ETW_UMGL_INDEX_SPARE3           10
#define ETW_UMGL_INDEX_SPARE4           11
#define ETW_UMGL_INDEX_SPARE5           12
#define ETW_UMGL_INDEX_SPARE6           13
#define ETW_UMGL_INDEX_SPARE7           14
#define ETW_UMGL_INDEX_SPARE8           15

#define ETW_UMGL_MAX_PROVIDERS          9

typedef struct _ETW_UMGL_KEY
{
    UCHAR LoggerId;
    UCHAR Flags;
} ETW_UMGL_KEY, * PETW_UMGL_KEY;

#define UMGL_LOGGER_ID(Index)               (((PETW_UMGL_KEY)(&SharedUserData->UserModeGlobalLogger[Index]))->LoggerId)
#define UMGL_LOGGER_FLAGS(Index)            (((PETW_UMGL_KEY)(&SharedUserData->UserModeGlobalLogger[Index]))->Flags)
#define IS_UMGL_LOGGING_ENABLED(Index)      (UMGL_LOGGER_ID(Index) != 0)
#define IS_UMGL_FLAG_ENABLED(Index, Flag)   ((UMGL_LOGGER_FLAGS(Index) & Flag) != 0)

#define IS_HEAP_LOGGING_ENABLED()           (IS_UMGL_LOGGING_ENABLED(ETW_UMGL_INDEX_HEAP) && (NtCurrentPeb()->HeapTracingEnabled != FALSE))
#define IS_HEAP_RANGE_LOGGING_ENABLED()     (IS_UMGL_LOGGING_ENABLED(ETW_UMGL_INDEX_HEAPRANGE))
#define HEAP_LOGGER_ID                      (UMGL_LOGGER_ID(ETW_UMGL_INDEX_HEAP))

#define IS_CRITSEC_LOGGING_ENABLED()        (IS_UMGL_LOGGING_ENABLED(ETW_UMGL_INDEX_CRITSEC) && (NtCurrentPeb()->CritSecTracingEnabled != FALSE))
#define CRITSEC_LOGGER_ID                   (UMGL_LOGGER_ID(ETW_UMGL_INDEX_CRITSEC))
#define IS_LOADER_LOGGING_ENABLED_FLAG(Flag) (IS_UMGL_LOGGING_ENABLED(ETW_UMGL_INDEX_LDR) && ((UMGL_LOGGER_FLAGS(ETW_UMGL_INDEX_LDR) & Flag) != 0) )
#define IS_PER_PROCESS_LOADER_LOGGING_ENABLED_FLAG(Flag) (IS_UMGL_LOGGING_ENABLED(ETW_UMGL_INDEX_LDR) && (NtCurrentPeb()->LibLoaderTracingEnabled != FALSE) && ((UMGL_LOGGER_FLAGS(ETW_UMGL_INDEX_LDR) & Flag) != 0) )
#define IS_GLOBAL_LOADER_LOGGING_ENABLED()  (IS_UMGL_LOGGING_ENABLED(ETW_UMGL_INDEX_LDR))
#define LOADER_LOGGER_ID                    (UMGL_LOGGER_ID(ETW_UMGL_INDEX_LDR))
#define HEAPRANGE_LOGGER_ID                 (UMGL_LOGGER_ID(ETW_UMGL_INDEX_HEAPRANGE))
#define IS_THREAD_POOL_LOGGING_ENABLED()    (IS_UMGL_LOGGING_ENABLED(ETW_UMGL_INDEX_THREAD_POOL))
#define THREAD_POOL_LOGGER_ID               (UMGL_LOGGER_ID(ETW_UMGL_INDEX_THREAD_POOL))
#define IS_UMS_LOGGING_ENABLED()            (IS_UMGL_LOGGING_ENABLED(ETW_UMGL_INDEX_UMS))
#define UMS_LOGGER_ID                       (UMGL_LOGGER_ID(ETW_UMGL_INDEX_UMS))
#define HEAPSUMMARY_LOGGER_ID               (UMGL_LOGGER_ID(ETW_UMGL_INDEX_HEAPSUMMARY))
#define IS_HEAPSUMMARY_LOGGING_ENABLED()    (IS_UMGL_LOGGING_ENABLED(ETW_UMGL_INDEX_HEAPSUMMARY))
#define WNF_LOGGER_ID                       (UMGL_LOGGER_ID(ETW_UMGL_INDEX_WNF))
#define IS_WNF_LOGGING_ENABLED()            (IS_UMGL_LOGGING_ENABLED(ETW_UMGL_INDEX_WNF))
#define UMGL_THREAD_LOGGER_ID               (UMGL_LOGGER_ID(ETW_UMGL_INDEX_THREAD))
#define IS_UMGL_THREAD_LOGGING_ENABLED()    (IS_UMGL_LOGGING_ENABLED(ETW_UMGL_INDEX_THREAD))

//
// Flags used by user mode loader logging to UMGL.
//
#define ETW_UMGL_LDR_MUI_VERBOSE_FLAG 0x0001
#define ETW_UMGL_LDR_MUI_TEST_FLAG    0x0002
#define ETW_UMGL_LDR_RELOCATION_FLAG  0x0004
#define ETW_UMGL_LDR_NEW_DLL_FLAG   0x0010
#define ETW_UMGL_LDR_TEST_FLAG      0x0020
#define ETW_UMGL_LDR_SECURITY_FLAG  0x0040

//
// Constants for heap log
//
#define MEMORY_FROM_LOOKASIDE                   1       //Activity from LookAside
#define MEMORY_FROM_LOWFRAG                     2       //Activity from Low Frag Heap
#define MEMORY_FROM_MAINPATH                    3       //Activity from Main Code Path
#define MEMORY_FROM_SLOWPATH                    4       //Activity from Slow C
#define MEMORY_FROM_INVALID                     5
#define MEMORY_FROM_SEGMENT_HEAP                6       //Activity from segment heap.

//
// Header preparation macro for UMGL
//
#define TRACE_HEADER_TYPE_SYSTEM32          1
#define TRACE_HEADER_TYPE_SYSTEM64          2
#define TRACE_HEADER_TYPE_COMPACT32         3
#define TRACE_HEADER_TYPE_COMPACT64         4
#define TRACE_HEADER_TYPE_FULL_HEADER32     10
#define TRACE_HEADER_TYPE_INSTANCE32        11
#define TRACE_HEADER_TYPE_TIMED             12  // Not used
#define TRACE_HEADER_TYPE_ERROR             13  // Error while logging event
#define TRACE_HEADER_TYPE_WNODE_HEADER      14  // Not used
#define TRACE_HEADER_TYPE_MESSAGE           15
#define TRACE_HEADER_TYPE_PERFINFO32        16
#define TRACE_HEADER_TYPE_PERFINFO64        17
#define TRACE_HEADER_TYPE_EVENT_HEADER32    18
#define TRACE_HEADER_TYPE_EVENT_HEADER64    19
#define TRACE_HEADER_TYPE_FULL_HEADER64     20
#define TRACE_HEADER_TYPE_INSTANCE64        21

#define EVENT_HEADER_SIZE_MASK              0x0000FFFF

#define SYSTEM_TRACE_VERSION                 2

#define TRACE_HEADER_FLAG                   0x80000000

#define EVENT_HEADER_EVENT64      ((USHORT)(((TRACE_HEADER_FLAG | TRACE_HEADER_EVENT_TRACE) >> 16) | TRACE_HEADER_TYPE_EVENT_HEADER64))
#define EVENT_HEADER_EVENT32      ((USHORT)(((TRACE_HEADER_FLAG | TRACE_HEADER_EVENT_TRACE) >> 16) | TRACE_HEADER_TYPE_EVENT_HEADER32))
#define EVENT_HEADER_ERROR        ((USHORT)(((TRACE_HEADER_FLAG | TRACE_HEADER_EVENT_TRACE) >> 16) | TRACE_HEADER_TYPE_ERROR))
#define TRACE_HEADER_FULL32       (TRACE_HEADER_FLAG | TRACE_HEADER_EVENT_TRACE | (TRACE_HEADER_TYPE_FULL_HEADER32 << 16))
#define TRACE_HEADER_FULL64       (TRACE_HEADER_FLAG | TRACE_HEADER_EVENT_TRACE | (TRACE_HEADER_TYPE_FULL_HEADER64 << 16))
#define TRACE_HEADER_INSTANCE32   (TRACE_HEADER_FLAG | TRACE_HEADER_EVENT_TRACE | (TRACE_HEADER_TYPE_INSTANCE32 << 16))
#define TRACE_HEADER_INSTANCE64   (TRACE_HEADER_FLAG | TRACE_HEADER_EVENT_TRACE | (TRACE_HEADER_TYPE_INSTANCE64 << 16))

#ifdef _WIN64
#define EVENT_HEADER_EVENT      EVENT_HEADER_EVENT64
#define TRACE_HEADER_FULL       TRACE_HEADER_FULL64
#define TRACE_HEADER_INSTANCE   TRACE_HEADER_INSTANCE64
#else
#define EVENT_HEADER_EVENT      EVENT_HEADER_EVENT32
#define TRACE_HEADER_FULL       TRACE_HEADER_FULL32
#define TRACE_HEADER_INSTANCE   TRACE_HEADER_INSTANCE32
#endif

#define PREPARE_ETW_TRACE_HEADER_GUID(Header, EventStruct, EventType, EventGuid, LoggerId) \
    (Header)->Size = sizeof(EventStruct); \
    (Header)->Class.Type = (EventType); \
    RtlCopyMemory(&((Header)->Guid), (EventGuid), sizeof(*(EventGuid))); \

// Used with OpenTrace(), prevents conversion of TimeStamps to UTC
#define EVENT_TRACE_USE_RAWTIMESTAMP 0x00000002
// Used with OpenTrace(), retrieves event from file as is.
#define EVENT_TRACE_GET_RAWEVENT 0x00000100
// Used with OpenTrace() to ReadBehind  a live logger session
#define EVENT_TRACE_READ_BEHIND 0x00000200
// Used in EventCallbacks to indicate that the InstanceId field is a sequence number.
#define EVENT_TRACE_USE_SEQUENCE  0x0004
// Kernel Event Version is used to indicate if any kernel event has changed.
#define ETW_KERNEL_EVENT_VERSION 60

typedef struct _ETW_KERNEL_HEADER_EXTENSION
{
    PERFINFO_GROUPMASK GroupMasks;
    ULONG Version;
} ETW_KERNEL_HEADER_EXTENSION, * PETW_KERNEL_HEADER_EXTENSION;

#define ETW_SET_MARK_WITH_FLUSH 0x00000001

typedef struct _ETW_SET_MARK_INFORMATION
{
    ULONG Flag;
    WCHAR Mark[1];
} ETW_SET_MARK_INFORMATION, * PETW_SET_MARK_INFORMATION;

//
// Data Block structure for ETW notification
//
typedef enum _ETW_NOTIFICATION_TYPE
{
    EtwNotificationTypeNoReply = 1,     // No data block reply
    EtwNotificationTypeLegacyEnable,    // Enable notification for RegisterTraceGuids
    EtwNotificationTypeEnable,          // Enable notification for EventRegister
    EtwNotificationTypePrivateLogger,   // Private logger notification for ETW
    EtwNotificationTypePerflib,         // PERFLIB V2 counter data request/delivery block
    EtwNotificationTypeAudio,           // Private notification for audio policy
    EtwNotificationTypeSession,         // Session related ETW notifications
    EtwNotificationTypeReserved,        // For internal use (test)
    EtwNotificationTypeCredentialUI,    // Private notification for media center elevation detection
    EtwNotificationTypeInProcSession,   // Private in-proc session related ETW notifications
    EtwNotificationTypeMax
} ETW_NOTIFICATION_TYPE;

#define ETW_MAX_DATA_BLOCK_BUFFER_SIZE (65536)

typedef struct _ETW_NOTIFICATION_HEADER
{
    ETW_NOTIFICATION_TYPE NotificationType; // Notification type
    ULONG                 NotificationSize; // Notification size in bytes
    ULONG                 Offset;           // Offset to the next notification
    BOOLEAN               ReplyRequested;   // Reply Requested
    ULONG                 Timeout;          // Timeout in milliseconds when requesting reply
    union
    {
        ULONG             ReplyCount;       // Out to sender: the number of notifications sent
        ULONG             NotifyeeCount;    // Out to notifyee: the order during notification
    };
    ULONGLONG             Reserved2;
    ULONG                 TargetPID;
    ULONG                 SourcePID;
    GUID                  DestinationGuid;  // Desctination GUID
    GUID                  SourceGuid;       // Source GUID
} ETW_NOTIFICATION_HEADER, * PETW_NOTIFICATION_HEADER;

typedef
_Function_class_(ETW_NOTIFICATION_CALLBACK)
ULONG
NTAPI
ETW_NOTIFICATION_CALLBACK(
    _In_ PETW_NOTIFICATION_HEADER NotificationHeader,
    _In_ PVOID Context
    );
typedef ETW_NOTIFICATION_CALLBACK *PETW_NOTIFICATION_CALLBACK;

typedef enum _ETW_SESSION_NOTIFICATION_TYPE
{
    EtwSessionNotificationMediaChanged = 1,
    EtwSessionNotificationSessionTerminated,
    EtwSessionNotificationLogfileError,
    EtwSessionNotificationRealtimeError,
    EtwSessionNotificationSessionStarted,
    EtwSessionNotificationMax
} ETW_SESSION_NOTIFICATION_TYPE;

typedef struct _ETW_SESSION_NOTIFICATION_PACKET
{
    ETW_NOTIFICATION_HEADER NotificationHeader;
    ETW_SESSION_NOTIFICATION_TYPE Type;
    NTSTATUS Status;
    TRACEHANDLE TraceHandle;
    ULONG Reserved[2];
} ETW_SESSION_NOTIFICATION_PACKET, * PETW_SESSION_NOTIFICATION_PACKET;

NTSYSAPI
ULONG
NTAPI
EtwSetMark(
    _In_opt_ TRACEHANDLE TraceHandle,
    _In_ PETW_SET_MARK_INFORMATION MarkInfo,
    _In_ ULONG Size
);

typedef struct _EVENT_DATA_DESCRIPTOR EVENT_DATA_DESCRIPTOR, * PEVENT_DATA_DESCRIPTOR;

NTSYSAPI
ULONG
NTAPI
EtwEventWriteFull(
    _In_ REGHANDLE RegHandle,
    _In_ PCEVENT_DESCRIPTOR EventDescriptor,
    _In_ USHORT EventProperty,
    _In_opt_ LPCGUID ActivityId,
    _In_opt_ LPCGUID RelatedActivityId,
    _In_ ULONG UserDataCount,
    _In_reads_opt_(UserDataCount) PEVENT_DATA_DESCRIPTOR UserData
);

NTSYSAPI
ULONG
NTAPI
EtwEventRegister(
    _In_ LPCGUID ProviderId,
    _In_opt_ PENABLECALLBACK EnableCallback,
    _In_opt_ PVOID CallbackContext,
    _Out_ PREGHANDLE RegHandle
    );

NTSYSAPI
ULONG
NTAPI
EtwEventUnregister(
    _In_ REGHANDLE RegHandle
);

typedef enum _EVENT_INFO_CLASS EVENT_INFO_CLASS;

NTSYSAPI
ULONG
NTAPI
EtwEventSetInformation(
    _In_ REGHANDLE RegHandle,
    _In_ EVENT_INFO_CLASS InformationClass,
    _In_reads_bytes_(InformationLength) PVOID EventInformation,
    _In_ ULONG InformationLength
);

NTSYSAPI
ULONG
NTAPI
EtwRegisterSecurityProvider(
    VOID
);

NTSYSAPI
BOOLEAN
NTAPI
EtwEventProviderEnabled(
    _In_ REGHANDLE RegHandle,
    _In_ UCHAR Level,
    _In_ ULONGLONG Keyword
);

NTSYSAPI
BOOLEAN
NTAPI
EtwEventEnabled(
    _In_ REGHANDLE RegHandle,
    _In_ PCEVENT_DESCRIPTOR EventDescriptor
);

NTSYSAPI
ULONG
NTAPI
EtwEventWrite(
    _In_ REGHANDLE RegHandle,
    _In_ PCEVENT_DESCRIPTOR EventDescriptor,
    _In_ ULONG UserDataCount,
    _In_reads_opt_(UserDataCount) PEVENT_DATA_DESCRIPTOR UserData
);

NTSYSAPI
ULONG
NTAPI
EtwEventWriteTransfer(
    _In_ REGHANDLE RegHandle,
    _In_ PCEVENT_DESCRIPTOR EventDescriptor,
    _In_opt_ LPCGUID ActivityId,
    _In_opt_ LPCGUID RelatedActivityId,
    _In_ ULONG UserDataCount,
    _In_reads_opt_(UserDataCount) PEVENT_DATA_DESCRIPTOR UserData
);

NTSYSAPI
ULONG
NTAPI
EtwEventWriteString(
    _In_ REGHANDLE RegHandle,
    _In_ UCHAR Level,
    _In_ ULONGLONG Keyword,
    _In_ PCWSTR String
);

ULONG
NTAPI
EtwEventWriteEx(
    _In_ REGHANDLE RegHandle,
    _In_ PCEVENT_DESCRIPTOR EventDescriptor,
    _In_ ULONG64 Filter,
    _In_ ULONG Flags,
    _In_opt_ LPCGUID ActivityId,
    _In_opt_ LPCGUID RelatedActivityId,
    _In_ ULONG UserDataCount,
    _In_reads_opt_(UserDataCount) PEVENT_DATA_DESCRIPTOR UserData
);

NTSYSAPI
ULONG
NTAPI
EtwEventWriteStartScenario(
    _In_ REGHANDLE RegHandle,
    _In_ PCEVENT_DESCRIPTOR EventDescriptor,
    _In_ ULONG UserDataCount,
    _In_reads_opt_(UserDataCount) PEVENT_DATA_DESCRIPTOR UserData
);

NTSYSAPI
ULONG
NTAPI
EtwEventWriteEndScenario(
    _In_ REGHANDLE RegHandle,
    _In_ PCEVENT_DESCRIPTOR EventDescriptor,
    _In_ ULONG UserDataCount,
    _In_reads_opt_(UserDataCount) PEVENT_DATA_DESCRIPTOR UserData
);

NTSYSAPI
ULONG
NTAPI
EtwWriteUMSecurityEvent(
    _In_ PCEVENT_DESCRIPTOR EventDescriptor,
    _In_ USHORT EventProperty,
    _In_ ULONG UserDataCount,
    _In_opt_ PEVENT_DATA_DESCRIPTOR UserData
);

ULONG
NTAPI
EtwEventWriteNoRegistration(
    _In_ LPCGUID ProviderId,
    _In_ PCEVENT_DESCRIPTOR EventDescriptor,
    _In_ ULONG UserDataCount,
    _In_reads_opt_(UserDataCount) PEVENT_DATA_DESCRIPTOR UserData
);

NTSYSAPI
ULONG
NTAPI
EtwEventActivityIdControl(
    _In_ ULONG ControlCode,
    _Inout_ LPGUID ActivityId
);

NTSYSAPI
ULONG
NTAPI
EtwNotificationRegister(
    _In_ LPCGUID Guid,
    _In_ ULONG Type,
    _In_ PETW_NOTIFICATION_CALLBACK Callback,
    _In_opt_ PVOID Context,
    _Out_ PREGHANDLE RegHandle
);

NTSYSAPI
ULONG
NTAPI
EtwNotificationUnregister(
    _In_ REGHANDLE RegHandle,
    _Out_opt_ PVOID* Context
);

NTSYSAPI
ULONG
NTAPI
EtwSendNotification(
    _In_ PETW_NOTIFICATION_HEADER DataBlock,
    _In_ ULONG ReceiveDataBlockSize,
    _Inout_ PVOID ReceiveDataBlock,
    _Out_ PULONG ReplyReceived,
    _Out_ PULONG ReplySizeNeeded
);

NTSYSAPI
ULONG
NTAPI
EtwReplyNotification(
    _In_ PETW_NOTIFICATION_HEADER Notification
);

NTSYSAPI
ULONG
NTAPI
EtwEnumerateProcessRegGuids(
    _Out_writes_bytes_opt_(OutBufferSize) PVOID OutBuffer,
    _In_ ULONG OutBufferSize,
    _Out_ PULONG ReturnLength
);

NTSYSAPI
ULONG
NTAPI
EtwQueryRealtimeConsumer(
    _In_ TRACEHANDLE TraceHandle,
    _Out_ PULONG EventsLostCount,
    _Out_ PULONG BuffersLostCount
);
#endif // !defined(_KERNEL_MODE)

// private
typedef struct _TELEMETRY_COVERAGE_POINT
{
    PWSTR Name;
    ULONG Hash;
    ULONG LastCoveredRound;
    ULONG Flags;
} TELEMETRY_COVERAGE_POINT, * PTELEMETRY_COVERAGE_POINT;

#if !defined _KERNEL_MODE
// rev
#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)
NTSYSAPI
BOOLEAN
NTAPI
EtwCheckCoverage(
    _Inout_ PTELEMETRY_COVERAGE_POINT CoveragePoint
);
#endif
#endif

//
// WMI
//

//Extracted from ComBase.pdb symbol file
typedef struct _WMI_LOGGER_INFORMATION {
    WNODE_HEADER Wnode;
    ULONG BufferSize;
    ULONG MinimumBuffers;
    ULONG MaximumBuffers;
    ULONG MaximumFileSize;
    ULONG LogFileMode;
    ULONG FlushTimer;
    ULONG EnableFlags;
    union {
        LONG AgeLimit;
        LONG FlushThreshold;
    };
    union {
        struct {
            ULONG Wow : 1;                  // Logger was started by a WOW64 process (output only).
            ULONG QpcDeltaTracking : 1;     // QPC delta tracking events are enabled.
            ULONG LargeMdlPages : 1;        // Buffers allocated via large MDL pages.
            ULONG ExcludeKernelStack : 1;   // Exclude kernel stack from stack walk.
        };
        ULONG64 V2Options;
    };
    union {
        HANDLE LogFileHandle;
        ULONG64 LogFileHandle64;
    };
    union {
        ULONG NumberOfBuffers;
        ULONG InstanceCount;
    };
    union {
        ULONG FreeBuffers;
        ULONG InstanceId;
    };
    union {
        ULONG EventsLost;
        ULONG NumberOfProcessors;
    };
    ULONG BuffersWritten;
    union {
        ULONG LogBuffersLost;
        ULONG Flags;
    };
    ULONG RealTimeBuffersLost;
    union {
        HANDLE LoggerThreadId;
        ULONG64 LoggerThreadId64;
    };
    union {
        UNICODE_STRING LogFileName;
        UNICODE_STRING64 LogFileName64;
    };
    union {
        UNICODE_STRING LoggerName;
        UNICODE_STRING64 LoggerName64;
    };
    ULONG RealTimeConsumerCount;
    ULONG SequenceNumber;
    union {
        PVOID LoggerExtension;
        ULONG64 LoggerExtension64;
    };
} WMI_LOGGER_INFORMATION, * PWMI_LOGGER_INFORMATION;


VEIL_END()

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
