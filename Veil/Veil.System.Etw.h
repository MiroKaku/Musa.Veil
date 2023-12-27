/*
 * PROJECT:   Veil
 * FILE:      Veil.System.Etw.h
 * PURPOSE:   This file is part of Veil.
 *
 * LICENSE:   MIT License
 *
 * DEVELOPER: MiroKaku (kkmi04@outlook.com)
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

// private
typedef struct _TELEMETRY_COVERAGE_POINT
{
    PWSTR Name;
    ULONG Hash;
    ULONG LastCoveredRound;
    ULONG Flags;
} TELEMETRY_COVERAGE_POINT, * PTELEMETRY_COVERAGE_POINT;

// rev
#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)
NTSYSAPI
BOOLEAN
NTAPI
EtwCheckCoverage(
    _Inout_ PTELEMETRY_COVERAGE_POINT CoveragePoint
);
#endif

#endif // !defined(_KERNEL_MODE)

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
