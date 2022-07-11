/*
 * PROJECT:   Veil
 * FILE:      Veil.h
 * PURPOSE:   Definition for the Windows Internal API from ntdll.dll,
 *            samlib.dll and winsta.dll
 *
 * LICENSE:   Relicensed under The MIT License from The CC BY 4.0 License
 *
 * DEVELOPER: MiroKaku (50670906+MiroKaku@users.noreply.github.com)
 */

 /*
  * PROJECT:   Mouri's Internal NT API Collections (MINT)
  * FILE:      MINT.h
  * PURPOSE:   Definition for the Windows Internal API from ntdll.dll,
  *            samlib.dll and winsta.dll
  *
  * LICENSE:   Relicensed under The MIT License from The CC BY 4.0 License
  *
  * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
  */

  /*
   * This file is part of the Process Hacker project - https://processhacker.sf.io/
   *
   * You can redistribute this file and/or modify it under the terms of the
   * Attribution 4.0 International (CC BY 4.0) license.
   *
   * You must give appropriate credit, provide a link to the license, and
   * indicate if changes were made. You may do so in any reasonable manner, but
   * not in any way that suggests the licensor endorses you or your use.
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

typedef enum _TRACE_CONTROL_INFORMATION_CLASS
{
    TraceControlStartLogger = 1,
    TraceControlStopLogger = 2,
    TraceControlQueryLogger = 3,
    TraceControlUpdateLogger = 4,
    TraceControlFlushLogger = 5,
    TraceControlIncrementLoggerFile = 6,

    TraceControlRealtimeConnect = 11,
    TraceControlWdiDispatchControl = 13,
    TraceControlRealtimeDisconnectConsumerByHandle = 14,

    TraceControlReceiveNotification = 16,
    TraceControlEnableGuid = 17,
    TraceControlSendReplyDataBlock = 18,
    TraceControlReceiveReplyDataBlock = 19,
    TraceControlWdiUpdateSem = 20,
    TraceControlGetTraceGuidList = 21,
    TraceControlGetTraceGuidInfo = 22,
    TraceControlEnumerateTraceGuids = 23,

    TraceControlQueryReferenceTime = 25,
    TraceControlTrackProviderBinary = 26,
    TraceControlAddNotificationEvent = 27,
    TraceControlUpdateDisallowList = 28,

    TraceControlUseDescriptorTypeUm = 31,
    TraceControlGetTraceGroupList = 32,
    TraceControlGetTraceGroupInfo = 33,
    TraceControlTraceSetDisallowList = 34,
    TraceControlSetCompressionSettings = 35,
    TraceControlGetCompressionSettings = 36,
    TraceControlUpdatePeriodicCaptureState = 37,
    TraceControlGetPrivateSessionTraceHandle = 38,
    TraceControlRegisterPrivateSession = 39,
    TraceControlQuerySessionDemuxObject = 40,
    TraceControlSetProviderBinaryTracking = 41,
    TraceControlMaxLoggers = 42,
    TraceControlMaxPmcCounter = 43
} TRACE_CONTROL_INFORMATION_CLASS;

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSCALLAPI
NTSTATUS
NTAPI
NtTraceControl(
    _In_ TRACE_CONTROL_INFORMATION_CLASS TraceInformationClass,
    _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(TraceInformationLength) PVOID TraceInformation,
    _In_ ULONG TraceInformationLength,
    _Out_ PULONG ReturnLength
);

NTSYSCALLAPI
NTSTATUS
NTAPI
ZwTraceControl(
    _In_ TRACE_CONTROL_INFORMATION_CLASS TraceInformationClass,
    _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(TraceInformationLength) PVOID TraceInformation,
    _In_ ULONG TraceInformationLength,
    _Out_ PULONG ReturnLength
);
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
