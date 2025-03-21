/*
 * PROJECT:   Veil
 * FILE:      Veil.System.PowerManager.h
 * PURPOSE:   This file is part of Veil.
 *
 * LICENSE:   MIT License
 *
 * DEVELOPER: MeeSong (meesong@outlook.com)
 */

#pragma once

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

//#define SystemPowerPolicyAc             ((POWER_INFORMATION_LEVEL)0)  // SYSTEM_POWER_POLICY // GET: InputBuffer NULL. SET: InputBuffer not NULL.
//#define SystemPowerPolicyDc             ((POWER_INFORMATION_LEVEL)1)  // SYSTEM_POWER_POLICY
//#define VerifySystemPolicyAc            ((POWER_INFORMATION_LEVEL)2)  // SYSTEM_POWER_POLICY
//#define VerifySystemPolicyDc            ((POWER_INFORMATION_LEVEL)3)  // SYSTEM_POWER_POLICY
//#define SystemPowerCapabilities         ((POWER_INFORMATION_LEVEL)4)  // SYSTEM_POWER_CAPABILITIES
//#define SystemBatteryState              ((POWER_INFORMATION_LEVEL)5)  // SYSTEM_BATTERY_STATE
//#define SystemPowerStateHandler         ((POWER_INFORMATION_LEVEL)6)  // POWER_STATE_HANDLER // (kernel-mode only)
//#define ProcessorStateHandler           ((POWER_INFORMATION_LEVEL)7)  // PROCESSOR_STATE_HANDLER // (kernel-mode only)
//#define SystemPowerPolicyCurrent        ((POWER_INFORMATION_LEVEL)8)  // SYSTEM_POWER_POLICY
//#define AdministratorPowerPolicy        ((POWER_INFORMATION_LEVEL)9)  // ADMINISTRATOR_POWER_POLICY
//#define SystemReserveHiberFile          ((POWER_INFORMATION_LEVEL)10) // BOOLEAN // (requires SeCreatePagefilePrivilege) // TRUE: hibernation file created. FALSE: hibernation file deleted.
//#define ProcessorInformation            ((POWER_INFORMATION_LEVEL)11) // PROCESSOR_POWER_INFORMATION
//#define SystemPowerInformation          ((POWER_INFORMATION_LEVEL)12) // SYSTEM_POWER_INFORMATION
//#define ProcessorStateHandler2          ((POWER_INFORMATION_LEVEL)13) // PROCESSOR_STATE_HANDLER2 // not implemented
//#define LastWakeTime                    ((POWER_INFORMATION_LEVEL)14) // ULONGLONG // InterruptTime
//#define LastSleepTime                   ((POWER_INFORMATION_LEVEL)15) // ULONGLONG // InterruptTime
//#define SystemExecutionState            ((POWER_INFORMATION_LEVEL)16) // EXECUTION_STATE // NtSetThreadExecutionState
//#define SystemPowerStateNotifyHandler   ((POWER_INFORMATION_LEVEL)17) // POWER_STATE_NOTIFY_HANDLER // (kernel-mode only)
//#define ProcessorPowerPolicyAc          ((POWER_INFORMATION_LEVEL)18) // PROCESSOR_POWER_POLICY // not implemented
//#define ProcessorPowerPolicyDc          ((POWER_INFORMATION_LEVEL)19) // PROCESSOR_POWER_POLICY // not implemented
//#define VerifyProcessorPowerPolicyAc    ((POWER_INFORMATION_LEVEL)20) // PROCESSOR_POWER_POLICY // not implemented
//#define VerifyProcessorPowerPolicyDc    ((POWER_INFORMATION_LEVEL)21) // PROCESSOR_POWER_POLICY // not implemented
//#define ProcessorPowerPolicyCurrent     ((POWER_INFORMATION_LEVEL)22) // PROCESSOR_POWER_POLICY // not implemented
//#define SystemPowerStateLogging         ((POWER_INFORMATION_LEVEL)23) // SYSTEM_POWER_STATE_DISABLE_REASON[]
//#define SystemPowerLoggingEntry         ((POWER_INFORMATION_LEVEL)24) // SYSTEM_POWER_LOGGING_ENTRY[] // (kernel-mode only)
//#define SetPowerSettingValue            ((POWER_INFORMATION_LEVEL)25) // (kernel-mode only)
//#define NotifyUserPowerSetting          ((POWER_INFORMATION_LEVEL)26) // not implemented
//#define PowerInformationLevelUnused0    ((POWER_INFORMATION_LEVEL)27) // not implemented
//#define SystemMonitorHiberBootPowerOff  ((POWER_INFORMATION_LEVEL)28) // NULL (PowerMonitorOff)
//#define SystemVideoState                ((POWER_INFORMATION_LEVEL)29) // MONITOR_DISPLAY_STATE
//#define TraceApplicationPowerMessage    ((POWER_INFORMATION_LEVEL)30) // (kernel-mode only)
//#define TraceApplicationPowerMessageEnd ((POWER_INFORMATION_LEVEL)31) // (kernel-mode only)
//#define ProcessorPerfStates             ((POWER_INFORMATION_LEVEL)32) // (kernel-mode only)
//#define ProcessorIdleStates             ((POWER_INFORMATION_LEVEL)33) // PROCESSOR_IDLE_STATES // (kernel-mode only)
//#define ProcessorCap                    ((POWER_INFORMATION_LEVEL)34) // PROCESSOR_CAP // (kernel-mode only)
//#define SystemWakeSource                ((POWER_INFORMATION_LEVEL)35) // out: POWER_WAKE_SOURCE_INFO
//#define SystemHiberFileInformation      ((POWER_INFORMATION_LEVEL)36) // out: SYSTEM_HIBERFILE_INFORMATION
//#define TraceServicePowerMessage        ((POWER_INFORMATION_LEVEL)37)
//#define ProcessorLoad                   ((POWER_INFORMATION_LEVEL)38) // in: PROCESSOR_LOAD (sets), in: PPROCESSOR_NUMBER (clears)
//#define PowerShutdownNotification       ((POWER_INFORMATION_LEVEL)39) // (kernel-mode only)
//#define MonitorCapabilities             ((POWER_INFORMATION_LEVEL)40) // (kernel-mode only)
//#define SessionPowerInit                ((POWER_INFORMATION_LEVEL)41) // (kernel-mode only)
//#define SessionDisplayState             ((POWER_INFORMATION_LEVEL)42) // (kernel-mode only)
//#define PowerRequestCreate              ((POWER_INFORMATION_LEVEL)43) // in: COUNTED_REASON_CONTEXT, out: HANDLE
//#define PowerRequestAction              ((POWER_INFORMATION_LEVEL)44) // in: POWER_REQUEST_ACTION
//#define GetPowerRequestList             ((POWER_INFORMATION_LEVEL)45) // out: POWER_REQUEST_LIST
//#define ProcessorInformationEx          ((POWER_INFORMATION_LEVEL)46) // in: USHORT ProcessorGroup, out: PROCESSOR_POWER_INFORMATION
//#define NotifyUserModeLegacyPowerEvent  ((POWER_INFORMATION_LEVEL)47) // (kernel-mode only)
//#define GroupPark                       ((POWER_INFORMATION_LEVEL)48) // (debug-mode boot only)
//#define ProcessorIdleDomains            ((POWER_INFORMATION_LEVEL)49) // (kernel-mode only)
//#define WakeTimerList                   ((POWER_INFORMATION_LEVEL)50) // out: WAKE_TIMER_INFO[]
//#define SystemHiberFileSize             ((POWER_INFORMATION_LEVEL)51) // ULONG
//#define ProcessorIdleStatesHv           ((POWER_INFORMATION_LEVEL)52) // (kernel-mode only)
//#define ProcessorPerfStatesHv           ((POWER_INFORMATION_LEVEL)53) // (kernel-mode only)
//#define ProcessorPerfCapHv              ((POWER_INFORMATION_LEVEL)54) // PROCESSOR_PERF_CAP_HV // (kernel-mode only)
//#define ProcessorSetIdle                ((POWER_INFORMATION_LEVEL)55) // (debug-mode boot only)
//#define LogicalProcessorIdling          ((POWER_INFORMATION_LEVEL)56) // (kernel-mode only)
//#define UserPresence                    ((POWER_INFORMATION_LEVEL)57) // POWER_USER_PRESENCE // not implemented
//#define PowerSettingNotificationName    ((POWER_INFORMATION_LEVEL)58) // in: ? (optional) // out: PWNF_STATE_NAME (RtlSubscribeWnfStateChangeNotification)
//#define GetPowerSettingValue            ((POWER_INFORMATION_LEVEL)59) // GUID
//#define IdleResiliency                  ((POWER_INFORMATION_LEVEL)60) // POWER_IDLE_RESILIENCY
//#define SessionRITState                 ((POWER_INFORMATION_LEVEL)61) // POWER_SESSION_RIT_STATE
//#define SessionConnectNotification      ((POWER_INFORMATION_LEVEL)62) // POWER_SESSION_WINLOGON
//#define SessionPowerCleanup             ((POWER_INFORMATION_LEVEL)63)
//#define SessionLockState                ((POWER_INFORMATION_LEVEL)64) // POWER_SESSION_WINLOGON
//#define SystemHiberbootState            ((POWER_INFORMATION_LEVEL)65) // BOOLEAN // fast startup supported
//#define PlatformInformation             ((POWER_INFORMATION_LEVEL)66) // BOOLEAN // connected standby supported
//#define PdcInvocation                   ((POWER_INFORMATION_LEVEL)67) // (kernel-mode only)
//#define MonitorInvocation               ((POWER_INFORMATION_LEVEL)68) // (kernel-mode only)
//#define FirmwareTableInformationRegistered ((POWER_INFORMATION_LEVEL)69) // (kernel-mode only)
//#define SetShutdownSelectedTime         ((POWER_INFORMATION_LEVEL)70) // in: NULL
//#define SuspendResumeInvocation         ((POWER_INFORMATION_LEVEL)71) // (kernel-mode only) // not implemented
//#define PlmPowerRequestCreate           ((POWER_INFORMATION_LEVEL)72) // in: COUNTED_REASON_CONTEXT, out: HANDLE
//#define ScreenOff                       ((POWER_INFORMATION_LEVEL)73) // in: NULL (PowerMonitorOff)
//#define CsDeviceNotification            ((POWER_INFORMATION_LEVEL)74) // (kernel-mode only)
//#define PlatformRole                    ((POWER_INFORMATION_LEVEL)75) // POWER_PLATFORM_ROLE
//#define LastResumePerformance           ((POWER_INFORMATION_LEVEL)76) // RESUME_PERFORMANCE
//#define DisplayBurst                    ((POWER_INFORMATION_LEVEL)77) // in: NULL (PowerMonitorOn)
//#define ExitLatencySamplingPercentage   ((POWER_INFORMATION_LEVEL)78) // in: NULL (ClearExitLatencySamplingPercentage), in: ULONG (SetExitLatencySamplingPercentage) (max 100)
//#define RegisterSpmPowerSettings        ((POWER_INFORMATION_LEVEL)79) // (kernel-mode only)
//#define PlatformIdleStates              ((POWER_INFORMATION_LEVEL)80) // (kernel-mode only)
//#define ProcessorIdleVeto               ((POWER_INFORMATION_LEVEL)81) // (kernel-mode only) // deprecated
//#define PlatformIdleVeto                ((POWER_INFORMATION_LEVEL)82) // (kernel-mode only) // deprecated
//#define SystemBatteryStatePrecise       ((POWER_INFORMATION_LEVEL)83) // SYSTEM_BATTERY_STATE
//#define ThermalEvent                    ((POWER_INFORMATION_LEVEL)84)  // THERMAL_EVENT // PowerReportThermalEvent
//#define PowerRequestActionInternal      ((POWER_INFORMATION_LEVEL)85) // POWER_REQUEST_ACTION_INTERNAL
//#define BatteryDeviceState              ((POWER_INFORMATION_LEVEL)86)
//#define PowerInformationInternal        ((POWER_INFORMATION_LEVEL)87) // POWER_INFORMATION_LEVEL_INTERNAL // PopPowerInformationInternal
//#define ThermalStandby                  ((POWER_INFORMATION_LEVEL)88) // NULL // shutdown with thermal standby as reason.
//#define SystemHiberFileType             ((POWER_INFORMATION_LEVEL)89) // ULONG // zero ? reduced : full // powercfg.exe /h /type
//#define PhysicalPowerButtonPress        ((POWER_INFORMATION_LEVEL)90) // BOOLEAN
//#define QueryPotentialDripsConstraint   ((POWER_INFORMATION_LEVEL)91) // (kernel-mode only)
//#define EnergyTrackerCreate             ((POWER_INFORMATION_LEVEL)92)
//#define EnergyTrackerQuery              ((POWER_INFORMATION_LEVEL)93)
//#define UpdateBlackBoxRecorder          ((POWER_INFORMATION_LEVEL)94)
//#define SessionAllowExternalDmaDevices  ((POWER_INFORMATION_LEVEL)95) // POWER_SESSION_ALLOW_EXTERNAL_DMA_DEVICES
//#define SendSuspendResumeNotification   ((POWER_INFORMATION_LEVEL)96) // since WIN11
//#define BlackBoxRecorderDirectAccessBuffer ((POWER_INFORMATION_LEVEL)97)
//#define SystemPowerSourceState          ((POWER_INFORMATION_LEVEL)98) // since 25H2
//#define PowerInformationLevelMaximum    ((POWER_INFORMATION_LEVEL)99)

typedef struct _PROCESSOR_POWER_INFORMATION
{
    ULONG Number;
    ULONG MaxMhz;
    ULONG CurrentMhz;
    ULONG MhzLimit;
    ULONG MaxIdleState;
    ULONG CurrentIdleState;
} PROCESSOR_POWER_INFORMATION, * PPROCESSOR_POWER_INFORMATION;

typedef struct _SYSTEM_POWER_INFORMATION
{
    ULONG MaxIdlenessAllowed;
    ULONG Idleness;
    ULONG TimeRemaining;
    UCHAR CoolingMode;
} SYSTEM_POWER_INFORMATION, * PSYSTEM_POWER_INFORMATION;

typedef struct _SYSTEM_HIBERFILE_INFORMATION
{
    ULONG NumberOfMcbPairs;
    LARGE_INTEGER Mcb[1];
} SYSTEM_HIBERFILE_INFORMATION, * PSYSTEM_HIBERFILE_INFORMATION;

#define POWER_PERF_SCALE    100
#define PERF_LEVEL_TO_PERCENT(_x_) ((_x_ * 1000) / (POWER_PERF_SCALE * 10))
#define PERCENT_TO_PERF_LEVEL(_x_) ((_x_ * POWER_PERF_SCALE * 10) / 1000)
#define PO_REASON_STATE_STANDBY (PO_REASON_STATE_S1 | \
                                 PO_REASON_STATE_S2 | \
                                 PO_REASON_STATE_S3)

#define PO_REASON_STATE_ALL     (PO_REASON_STATE_STANDBY | \
                                 PO_REASON_STATE_S4 | \
                                 PO_REASON_STATE_S4FIRM)

typedef struct _SYSTEM_POWER_LOGGING_ENTRY
{
    ULONG Reason;
    ULONG States;
} SYSTEM_POWER_LOGGING_ENTRY, * PSYSTEM_POWER_LOGGING_ENTRY;

typedef enum _POWER_STATE_DISABLED_TYPE
{
    PoDisabledStateSleeping1 = 0,
    PoDisabledStateSleeping2 = 1,
    PoDisabledStateSleeping3 = 2,
    PoDisabledStateSleeping4 = 3,
    PoDisabledStateSleeping0Idle = 4,
    PoDisabledStateReserved5 = 5,
    PoDisabledStateSleeping4Firmware = 6,
    PoDisabledStateMaximum = 7
} POWER_STATE_DISABLED_TYPE, PPOWER_STATE_DISABLED_TYPE;

#define POWER_STATE_DISABLED_TYPE_MAX  8

_Struct_size_bytes_(sizeof(SYSTEM_POWER_STATE_DISABLE_REASON) + PowerReasonLength)
typedef struct _SYSTEM_POWER_STATE_DISABLE_REASON
{
    BOOLEAN AffectedState[POWER_STATE_DISABLED_TYPE_MAX];
    ULONG PowerReasonCode;
    ULONG PowerReasonLength;
    //UCHAR PowerReasonInfo[ANYSIZE_ARRAY];
} SYSTEM_POWER_STATE_DISABLE_REASON, * PSYSTEM_POWER_STATE_DISABLE_REASON;

// Reason Context
#define POWER_REQUEST_CONTEXT_NOT_SPECIFIED DIAGNOSTIC_REASON_NOT_SPECIFIED

// enum _POWER_REQUEST_TYPE
#define PowerRequestDisplayRequired         ((_POWER_REQUEST_TYPE)0)
#define PowerRequestSystemRequired          ((_POWER_REQUEST_TYPE)1)
#define PowerRequestAwayModeRequired        ((_POWER_REQUEST_TYPE)2)
#define PowerRequestExecutionRequired       ((_POWER_REQUEST_TYPE)3)
#define PowerRequestPerfBoostRequired       ((_POWER_REQUEST_TYPE)4)
#define PowerRequestActiveLockScreen        ((_POWER_REQUEST_TYPE)5)
#define PowerRequestInvalid                 ((_POWER_REQUEST_TYPE)6)
#define PowerRequestUnknown                 ((_POWER_REQUEST_TYPE)7)
#define PowerRequestFullScreenVideoRequired ((_POWER_REQUEST_TYPE)8)

#ifndef _KERNEL_MODE
typedef struct _POWER_REQUEST_ACTION
{
    HANDLE PowerRequestHandle;
    POWER_REQUEST_TYPE RequestType;
    BOOLEAN SetAction;
    HANDLE ProcessHandle; // Windows 8+ and only for requests created via PlmPowerRequestCreate
} POWER_REQUEST_ACTION, * PPOWER_REQUEST_ACTION;

typedef union _POWER_STATE
{
    SYSTEM_POWER_STATE SystemState;
    DEVICE_POWER_STATE DeviceState;
} POWER_STATE, * PPOWER_STATE;

typedef enum _POWER_STATE_TYPE
{
    SystemPowerState = 0,
    DevicePowerState
} POWER_STATE_TYPE, * PPOWER_STATE_TYPE;

typedef struct _SYSTEM_POWER_STATE_CONTEXT {
    union {
        struct {
            ULONG   Reserved1               : 8;
            ULONG   TargetSystemState       : 4;
            ULONG   EffectiveSystemState    : 4;
            ULONG   CurrentSystemState      : 4;
            ULONG   IgnoreHibernationPath   : 1;
            ULONG   PseudoTransition        : 1;
            ULONG   KernelSoftReboot        : 1;
            ULONG   DirectedDripsTransition : 1;
            ULONG   Reserved2               : 8;
        } DUMMYSTRUCTNAME;

        ULONG ContextAsUlong;
    } DUMMYUNIONNAME;
} SYSTEM_POWER_STATE_CONTEXT, *PSYSTEM_POWER_STATE_CONTEXT;

typedef struct _COUNTED_REASON_CONTEXT
{
    ULONG Version;
    ULONG Flags;
    union
    {
        struct
        {
            UNICODE_STRING ResourceFileName;
            USHORT ResourceReasonId;
            ULONG StringCount;
            _Field_size_(StringCount) PUNICODE_STRING ReasonStrings;
        };

        UNICODE_STRING SimpleString;
    };
} COUNTED_REASON_CONTEXT, * PCOUNTED_REASON_CONTEXT;
#endif // !_KERNEL_MODE

typedef enum _REQUESTER_TYPE
{
    KernelRequester = 0,
    UserProcessRequester = 1,
    UserSharedServiceRequester = 2
} REQUESTER_TYPE;

typedef struct _COUNTED_REASON_CONTEXT_RELATIVE
{
    ULONG Flags;
    union
    {
        struct
        {
            SIZE_T ResourceFileNameOffset;
            USHORT ResourceReasonId;
            ULONG StringCount;
            SIZE_T SubstitutionStringsOffset;
        }DUMMYSTRUCTNAME;
        SIZE_T SimpleStringOffset;
    }DUMMYSTRUCTNAME;
} COUNTED_REASON_CONTEXT_RELATIVE, * PCOUNTED_REASON_CONTEXT_RELATIVE;

typedef struct _DIAGNOSTIC_BUFFER
{
    SIZE_T Size;
    REQUESTER_TYPE CallerType;
    union
    {
        struct
        {
            SIZE_T ProcessImageNameOffset; // PWSTR
            ULONG ProcessId;
            ULONG ServiceTag;
        } DUMMYSTRUCTNAME;
        struct
        {
            SIZE_T DeviceDescriptionOffset; // PWSTR
            SIZE_T DevicePathOffset; // PWSTR
        } DUMMYSTRUCTNAME;
    } DUMMYSTRUCTNAME;
    SIZE_T ReasonOffset; // PCOUNTED_REASON_CONTEXT_RELATIVE
} DIAGNOSTIC_BUFFER, * PDIAGNOSTIC_BUFFER;

// rev
typedef struct _WAKE_TIMER_INFO
{
    SIZE_T OffsetToNext;
    LARGE_INTEGER DueTime;
    ULONG Period;
    DIAGNOSTIC_BUFFER ReasonContext;
} WAKE_TIMER_INFO, * PWAKE_TIMER_INFO;

// rev
typedef struct _PROCESSOR_PERF_CAP_HV
{
    ULONG Version;
    ULONG InitialApicId;
    ULONG Ppc;
    ULONG Tpc;
    ULONG ThermalCap;
} PROCESSOR_PERF_CAP_HV, * PPROCESSOR_PERF_CAP_HV;

typedef struct PROCESSOR_IDLE_TIMES
{
    ULONG64 StartTime;
    ULONG64 EndTime;
    ULONG Reserved[4];
} PROCESSOR_IDLE_TIMES, * PPROCESSOR_IDLE_TIMES;

typedef
_Function_class_(PROCESSOR_IDLE_HANDLER)
NTSTATUS FASTCALL PROCESSOR_IDLE_HANDLER(
    _In_ ULONG_PTR Context,
    _Inout_ PPROCESSOR_IDLE_TIMES IdleTimes
    );

typedef PROCESSOR_IDLE_HANDLER* PPROCESSOR_IDLE_HANDLER;

#define PROCESSOR_STATE_TYPE_PERFORMANCE    0x1
#define PROCESSOR_STATE_TYPE_THROTTLE       0x2

#define IDLE_STATE_FLAGS_C1_HLT     0x01        // describes C1 only
#define IDLE_STATE_FLAGS_C1_IO_HLT  0x02        // describes C1 only
#define IDLE_STATE_FLAGS_IO         0x04        // describes C2 and C3 only
#define IDLE_STATE_FLAGS_MWAIT      0x08        // describes C1, C2, C3, C4, ...

typedef struct _PROCESSOR_IDLE_STATE
{
    UCHAR StateType;
    ULONG StateFlags;
    ULONG HardwareLatency;
    ULONG Power;
    ULONG_PTR Context;
    PPROCESSOR_IDLE_HANDLER Handler;
} PROCESSOR_IDLE_STATE, * PPROCESSOR_IDLE_STATE;

typedef struct _PROCESSOR_IDLE_STATES
{
    ULONG Size;
    ULONG Revision;
    ULONG Count;
    ULONG Type;
    KAFFINITY TargetProcessors;
    PROCESSOR_IDLE_STATE State[ANYSIZE_ARRAY];
} PROCESSOR_IDLE_STATES, * PPROCESSOR_IDLE_STATES;

// rev
typedef struct _PROCESSOR_LOAD
{
    PROCESSOR_NUMBER ProcessorNumber;
    UCHAR BusyPercentage;
    UCHAR FrequencyPercentage;
    USHORT Padding;
} PROCESSOR_LOAD, * PPROCESSOR_LOAD;

// rev
typedef struct _PROCESSOR_CAP
{
    ULONG Version;
    PROCESSOR_NUMBER ProcessorNumber;
    ULONG PlatformCap;
    ULONG ThermalCap;
    ULONG LimitReasons;
} PROCESSOR_CAP, * PPROCESSOR_CAP;

typedef struct _PO_WAKE_SOURCE_INFO
{
    ULONG Count;
    ULONG Offsets[ANYSIZE_ARRAY]; // POWER_WAKE_SOURCE_HEADER, POWER_WAKE_SOURCE_INTERNAL, POWER_WAKE_SOURCE_TIMER, POWER_WAKE_SOURCE_FIXED
} PO_WAKE_SOURCE_INFO, * PPO_WAKE_SOURCE_INFO;

typedef struct _PO_WAKE_SOURCE_HISTORY
{
    ULONG Count;
    ULONG Offsets[ANYSIZE_ARRAY]; // POWER_WAKE_SOURCE_HEADER, POWER_WAKE_SOURCE_INTERNAL, POWER_WAKE_SOURCE_TIMER, POWER_WAKE_SOURCE_FIXED
} PO_WAKE_SOURCE_HISTORY, * PPO_WAKE_SOURCE_HISTORY;

typedef enum _PO_WAKE_SOURCE_TYPE
{
    DeviceWakeSourceType = 0,
    FixedWakeSourceType = 1,
    TimerWakeSourceType = 2,
    TimerPresumedWakeSourceType = 3,
    InternalWakeSourceType = 4
} PO_WAKE_SOURCE_TYPE, * PPO_WAKE_SOURCE_TYPE;

typedef enum _PO_INTERNAL_WAKE_SOURCE_TYPE
{
    InternalWakeSourceDozeToHibernate = 0,
    InternalWakeSourcePredictedUserPresence = 1
} PO_INTERNAL_WAKE_SOURCE_TYPE;

typedef enum _PO_FIXED_WAKE_SOURCE_TYPE
{
    FixedWakeSourcePowerButton = 0,
    FixedWakeSourceSleepButton = 1,
    FixedWakeSourceRtc = 2,
    FixedWakeSourceDozeToHibernate = 3
} PO_FIXED_WAKE_SOURCE_TYPE, * PPO_FIXED_WAKE_SOURCE_TYPE;

typedef struct _PO_WAKE_SOURCE_HEADER
{
    PO_WAKE_SOURCE_TYPE Type;
    ULONG Size;
} PO_WAKE_SOURCE_HEADER, * PPO_WAKE_SOURCE_HEADER;

typedef struct _PO_WAKE_SOURCE_DEVICE
{
    PO_WAKE_SOURCE_HEADER Header;
    WCHAR InstancePath[ANYSIZE_ARRAY];
} PO_WAKE_SOURCE_DEVICE, * PPO_WAKE_SOURCE_DEVICE;

typedef struct _PO_WAKE_SOURCE_FIXED
{
    PO_WAKE_SOURCE_HEADER Header;
    PO_FIXED_WAKE_SOURCE_TYPE FixedWakeSourceType;
} PO_WAKE_SOURCE_FIXED, * PPO_WAKE_SOURCE_FIXED;

typedef struct _PO_WAKE_SOURCE_INTERNAL
{
    PO_WAKE_SOURCE_HEADER Header;
    PO_INTERNAL_WAKE_SOURCE_TYPE InternalWakeSourceType;
} PO_WAKE_SOURCE_INTERNAL, * PPO_WAKE_SOURCE_INTERNAL;

typedef struct _PO_WAKE_SOURCE_TIMER
{
    PO_WAKE_SOURCE_HEADER Header;
    DIAGNOSTIC_BUFFER Reason;
} PO_WAKE_SOURCE_TIMER, * PPO_WAKE_SOURCE_TIMER;

// The number of supported request types per version
#define POWER_REQUEST_SUPPORTED_TYPES_V1 3 // Windows 7
#define POWER_REQUEST_SUPPORTED_TYPES_V2 9 // Windows 8
#define POWER_REQUEST_SUPPORTED_TYPES_V3 5 // Windows 8.1 and Windows 10 TH1-TH2
#define POWER_REQUEST_SUPPORTED_TYPES_V4 6 // Windows 10 RS1+

typedef struct _POWER_REQUEST
{
    union
    {
        struct
        {
            ULONG SupportedRequestMask;
            ULONG PowerRequestCount[POWER_REQUEST_SUPPORTED_TYPES_V1];
            DIAGNOSTIC_BUFFER DiagnosticBuffer;
        } V1;
#if (NTDDI_VERSION >= NTDDI_WIN8)
        struct
        {
            ULONG SupportedRequestMask;
            ULONG PowerRequestCount[POWER_REQUEST_SUPPORTED_TYPES_V2];
            DIAGNOSTIC_BUFFER DiagnosticBuffer;
        } V2;
#endif
#if (NTDDI_VERSION >= NTDDI_WINBLUE)
        struct
        {
            ULONG SupportedRequestMask;
            ULONG PowerRequestCount[POWER_REQUEST_SUPPORTED_TYPES_V3];
            DIAGNOSTIC_BUFFER DiagnosticBuffer;
        } V3;
#endif
#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)
        struct
        {
            ULONG SupportedRequestMask;
            ULONG PowerRequestCount[POWER_REQUEST_SUPPORTED_TYPES_V4];
            DIAGNOSTIC_BUFFER DiagnosticBuffer;
        } V4;
#endif
    };
} POWER_REQUEST, * PPOWER_REQUEST;

typedef struct _POWER_REQUEST_LIST
{
    ULONG_PTR Count;
    ULONG_PTR PowerRequestOffsets[ANYSIZE_ARRAY]; // PPOWER_REQUEST
} POWER_REQUEST_LIST, * PPOWER_REQUEST_LIST;

typedef enum _POWER_STATE_HANDLER_TYPE
{
    PowerStateSleeping1 = 0,
    PowerStateSleeping2 = 1,
    PowerStateSleeping3 = 2,
    PowerStateSleeping4 = 3,
    PowerStateShutdownOff = 4,
    PowerStateShutdownReset = 5,
    PowerStateSleeping4Firmware = 6,
    PowerStateMaximum = 7
} POWER_STATE_HANDLER_TYPE, * PPOWER_STATE_HANDLER_TYPE;

typedef NTSTATUS(NTAPI* PENTER_STATE_SYSTEM_HANDLER)(
    _In_ PVOID SystemContext
    );

typedef NTSTATUS(NTAPI* PENTER_STATE_HANDLER)(
    _In_ PVOID Context,
    _In_opt_ PENTER_STATE_SYSTEM_HANDLER SystemHandler,
    _In_ PVOID SystemContext,
    _In_ LONG NumberProcessors,
    _In_ LONG volatile* Number
    );

typedef struct _POWER_STATE_HANDLER
{
    POWER_STATE_HANDLER_TYPE Type;
    BOOLEAN RtcWake;
    UCHAR Spare[3];
    PENTER_STATE_HANDLER Handler;
    PVOID Context;
} POWER_STATE_HANDLER, * PPOWER_STATE_HANDLER;

typedef NTSTATUS(NTAPI* PENTER_STATE_NOTIFY_HANDLER)(
    _In_ POWER_STATE_HANDLER_TYPE State,
    _In_ PVOID Context,
    _In_ BOOLEAN Entering
    );

typedef struct _POWER_STATE_NOTIFY_HANDLER
{
    PENTER_STATE_NOTIFY_HANDLER Handler;
    PVOID Context;
} POWER_STATE_NOTIFY_HANDLER, * PPOWER_STATE_NOTIFY_HANDLER;

typedef struct _POWER_REQUEST_ACTION_INTERNAL
{
    PVOID PowerRequestPointer;
    POWER_REQUEST_TYPE RequestType;
    BOOLEAN SetAction;
} POWER_REQUEST_ACTION_INTERNAL, * PPOWER_REQUEST_ACTION_INTERNAL;

typedef enum _POWER_INFORMATION_LEVEL_INTERNAL
{
    PowerInternalAcpiInterfaceRegister,
    PowerInternalS0LowPowerIdleInfo, // POWER_S0_LOW_POWER_IDLE_INFO
    PowerInternalReapplyBrightnessSettings,
    PowerInternalUserAbsencePrediction, // POWER_USER_ABSENCE_PREDICTION
    PowerInternalUserAbsencePredictionCapability, // POWER_USER_ABSENCE_PREDICTION_CAPABILITY
    PowerInternalPoProcessorLatencyHint, // POWER_PROCESSOR_LATENCY_HINT
    PowerInternalStandbyNetworkRequest, // POWER_STANDBY_NETWORK_REQUEST (requires PopNetBIServiceSid)
    PowerInternalDirtyTransitionInformation, // out: BOOLEAN
    PowerInternalSetBackgroundTaskState, // POWER_SET_BACKGROUND_TASK_STATE
    PowerInternalTtmOpenTerminal, // (requires SeShutdownPrivilege and terminalPowerManagement capability)
    PowerInternalTtmCreateTerminal, // (requires SeShutdownPrivilege and terminalPowerManagement capability) // 10
    PowerInternalTtmEvacuateDevices, // (requires SeShutdownPrivilege and terminalPowerManagement capability)
    PowerInternalTtmCreateTerminalEventQueue, // (requires SeShutdownPrivilege and terminalPowerManagement capability)
    PowerInternalTtmGetTerminalEvent, // (requires SeShutdownPrivilege and terminalPowerManagement capability)
    PowerInternalTtmSetDefaultDeviceAssignment, // (requires SeShutdownPrivilege and terminalPowerManagement capability)
    PowerInternalTtmAssignDevice, // (requires SeShutdownPrivilege and terminalPowerManagement capability)
    PowerInternalTtmSetDisplayState, // (requires SeShutdownPrivilege and terminalPowerManagement capability)
    PowerInternalTtmSetDisplayTimeouts, // (requires SeShutdownPrivilege and terminalPowerManagement capability)
    PowerInternalBootSessionStandbyActivationInformation, // out: POWER_BOOT_SESSION_STANDBY_ACTIVATION_INFO
    PowerInternalSessionPowerState, // in: POWER_SESSION_POWER_STATE
    PowerInternalSessionTerminalInput, // 20
    PowerInternalSetWatchdog,
    PowerInternalPhysicalPowerButtonPressInfoAtBoot,
    PowerInternalExternalMonitorConnected,
    PowerInternalHighPrecisionBrightnessSettings,
    PowerInternalWinrtScreenToggle,
    PowerInternalPpmQosDisable,
    PowerInternalTransitionCheckpoint,
    PowerInternalInputControllerState,
    PowerInternalFirmwareResetReason,
    PowerInternalPpmSchedulerQosSupport, // out: POWER_INTERNAL_PROCESSOR_QOS_SUPPORT // 30
    PowerInternalBootStatGet,
    PowerInternalBootStatSet,
    PowerInternalCallHasNotReturnedWatchdog,
    PowerInternalBootStatCheckIntegrity,
    PowerInternalBootStatRestoreDefaults, // in: void
    PowerInternalHostEsStateUpdate, // in: POWER_INTERNAL_HOST_ENERGY_SAVER_STATE
    PowerInternalGetPowerActionState, // out: ULONG
    PowerInternalBootStatUnlock,
    PowerInternalWakeOnVoiceState,
    PowerInternalDeepSleepBlock, // 40
    PowerInternalIsPoFxDevice,
    PowerInternalPowerTransitionExtensionAtBoot,
    PowerInternalProcessorBrandedFrequency, // in: POWER_INTERNAL_PROCESSOR_BRANDED_FREQENCY_INPUT, out: POWER_INTERNAL_PROCESSOR_BRANDED_FREQENCY_OUTPUT
    PowerInternalTimeBrokerExpirationReason,
    PowerInternalNotifyUserShutdownStatus,
    PowerInternalPowerRequestTerminalCoreWindow,
    PowerInternalProcessorIdleVeto, // PROCESSOR_IDLE_VETO
    PowerInternalPlatformIdleVeto, // PLATFORM_IDLE_VETO
    PowerInternalIsLongPowerButtonBugcheckEnabled,
    PowerInternalAutoChkCausedReboot, // 50
    PowerInternalSetWakeAlarmOverride,

    PowerInternalDirectedFxAddTestDevice = 53,
    PowerInternalDirectedFxRemoveTestDevice,

    PowerInternalDirectedFxSetMode = 56,
    PowerInternalRegisterPowerPlane,
    PowerInternalSetDirectedDripsFlags,
    PowerInternalClearDirectedDripsFlags,
    PowerInternalRetrieveHiberFileResumeContext, // 60
    PowerInternalReadHiberFilePage,
    PowerInternalLastBootSucceeded, // out: BOOLEAN
    PowerInternalQuerySleepStudyHelperRoutineBlock,
    PowerInternalDirectedDripsQueryCapabilities,
    PowerInternalClearConstraints,
    PowerInternalSoftParkVelocityEnabled,
    PowerInternalQueryIntelPepCapabilities,
    PowerInternalGetSystemIdleLoopEnablement, // since WIN11
    PowerInternalGetVmPerfControlSupport,
    PowerInternalGetVmPerfControlConfig, // 70
    PowerInternalSleepDetailedDiagUpdate,
    PowerInternalProcessorClassFrequencyBandsStats,
    PowerInternalHostGlobalUserPresenceStateUpdate,
    PowerInternalCpuNodeIdleIntervalStats,
    PowerInternalClassIdleIntervalStats,
    PowerInternalCpuNodeConcurrencyStats,
    PowerInternalClassConcurrencyStats,
    PowerInternalQueryProcMeasurementCapabilities, // PPROCESSOR_QUERY_MEASUREMENT_CAPABILITIES
    PowerInternalQueryProcMeasurementValues, // PROCESSOR_QUERY_MEASUREMENT_VALUES
    PowerInternalPrepareForSystemInitiatedReboot, // 80
    PowerInternalGetAdaptiveSessionState,
    PowerInternalSetConsoleLockedState,
    PowerInternalOverrideSystemInitiatedRebootState,
    PowerInternalFanImpactStats,
    PowerInternalFanRpmBuckets,
    PowerInternalPowerBootAppDiagInfo, // out: POWER_INTERNAL_BOOTAPP_DIAGNOSTIC
    PowerInternalUnregisterShutdownNotification, // since 22H1
    PowerInternalManageTransitionStateRecord,
    PowerInternalGetAcpiTimeAndAlarmCapabilities, // since 22H2
    PowerInternalSuspendResumeRequest,
    PowerInternalEnergyEstimationInfo, // since 23H2
    PowerInternalProvSocIdentifierOperation, // since 24H2
    PowerInternalGetVmPerfPrioritySupport,
    PowerInternalGetVmPerfPriorityConfig,
    PowerInternalNotifyWin32kPowerRequestQueued,
    PowerInternalNotifyWin32kPowerRequestCompleted,
    PowerInformationInternalMaximum
} POWER_INFORMATION_LEVEL_INTERNAL;

typedef enum _POWER_S0_DISCONNECTED_REASON
{
    PoS0DisconnectedReasonNone,
    PoS0DisconnectedReasonNonCompliantNic,
    PoS0DisconnectedReasonSettingPolicy,
    PoS0DisconnectedReasonEnforceDsPolicy,
    PoS0DisconnectedReasonCsChecksFailed,
    PoS0DisconnectedReasonSmartStandby,
    PoS0DisconnectedReasonMaximum
} POWER_S0_DISCONNECTED_REASON;

typedef struct _POWER_S0_LOW_POWER_IDLE_INFO
{
    POWER_S0_DISCONNECTED_REASON DisconnectedReason;
    union
    {
        BOOLEAN Storage : 1;
        BOOLEAN WiFi : 1;
        BOOLEAN Mbn : 1;
        BOOLEAN Ethernet : 1;
        BOOLEAN Reserved : 4;
        UCHAR AsUCHAR;
    } CsDeviceCompliance;
    union
    {
        BOOLEAN DisconnectInStandby : 1;
        BOOLEAN EnforceDs : 1;
        BOOLEAN Reserved : 6;
        UCHAR AsUCHAR;
    } Policy;
} POWER_S0_LOW_POWER_IDLE_INFO, * PPOWER_S0_LOW_POWER_IDLE_INFO;

typedef struct _POWER_INFORMATION_INTERNAL_HEADER
{
    POWER_INFORMATION_LEVEL_INTERNAL InternalType;
    ULONG Version;
} POWER_INFORMATION_INTERNAL_HEADER, * PPOWER_INFORMATION_INTERNAL_HEADER;

typedef struct _POWER_USER_ABSENCE_PREDICTION
{
    POWER_INFORMATION_INTERNAL_HEADER Header;
    LARGE_INTEGER ReturnTime;
} POWER_USER_ABSENCE_PREDICTION, * PPOWER_USER_ABSENCE_PREDICTION;

typedef struct _POWER_USER_ABSENCE_PREDICTION_CAPABILITY
{
    BOOLEAN AbsencePredictionCapability;
} POWER_USER_ABSENCE_PREDICTION_CAPABILITY, * PPOWER_USER_ABSENCE_PREDICTION_CAPABILITY;

typedef struct _POWER_PROCESSOR_LATENCY_HINT
{
    POWER_INFORMATION_INTERNAL_HEADER PowerInformationInternalHeader;
    ULONG Type;
} POWER_PROCESSOR_LATENCY_HINT, * PPOWER_PROCESSOR_LATENCY_HINT;

typedef struct _POWER_STANDBY_NETWORK_REQUEST
{
    POWER_INFORMATION_INTERNAL_HEADER PowerInformationInternalHeader;
    BOOLEAN Active;
} POWER_STANDBY_NETWORK_REQUEST, * PPOWER_STANDBY_NETWORK_REQUEST;

typedef struct _POWER_SET_BACKGROUND_TASK_STATE
{
    POWER_INFORMATION_INTERNAL_HEADER PowerInformationInternalHeader;
    BOOLEAN Engaged;
} POWER_SET_BACKGROUND_TASK_STATE, * PPOWER_SET_BACKGROUND_TASK_STATE;

// rev
typedef struct _POWER_BOOT_SESSION_STANDBY_ACTIVATION_INFO
{
    ULONG StandbyTotalTime;
    ULONG DripsTotalTime;
    ULONG ActivatorClientTotalActiveTime;
    ULONG PerActivatorClientTotalActiveTime[98];
} POWER_BOOT_SESSION_STANDBY_ACTIVATION_INFO, * PPOWER_BOOT_SESSION_STANDBY_ACTIVATION_INFO;
// rev
typedef struct _POWER_SESSION_POWER_STATE
{
    POWER_INFORMATION_INTERNAL_HEADER Header;
    ULONG SessionId;
    BOOLEAN On;
    BOOLEAN IsConsole;
    POWER_MONITOR_REQUEST_REASON RequestReason;
} POWER_SESSION_POWER_STATE, * PPOWER_SESSION_POWER_STATE;

// rev
typedef struct _POWER_INTERNAL_PROCESSOR_QOS_SUPPORT
{
    BOOLEAN QosSupportedAndConfigured;
    BOOLEAN SchedulerDirectedPerfStatesSupported;
    BOOLEAN QosGroupPolicyDisable;
} POWER_INTERNAL_PROCESSOR_QOS_SUPPORT, * PPOWER_INTERNAL_PROCESSOR_QOS_SUPPORT;

// rev
typedef struct _POWER_INTERNAL_HOST_ENERGY_SAVER_STATE
{
    POWER_INFORMATION_INTERNAL_HEADER Header;
    BOOLEAN EsEnabledOnHost;
} POWER_INTERNAL_HOST_ENERGY_SAVER_STATE, * PPOWER_INTERNAL_HOST_ENERGY_SAVER_STATE;

typedef struct _POWER_INTERNAL_PROCESSOR_BRANDED_FREQUENCY_INPUT
{
    POWER_INFORMATION_LEVEL_INTERNAL InternalType;
    PROCESSOR_NUMBER ProcessorNumber; // ULONG_MAX
} POWER_INTERNAL_PROCESSOR_BRANDED_FREQUENCY_INPUT, * PPOWER_INTERNAL_PROCESSOR_BRANDED_FREQUENCY_INPUT;

#define POWER_INTERNAL_PROCESSOR_BRANDED_FREQUENCY_VERSION 1

// rev
typedef struct _POWER_INTERNAL_PROCESSOR_BRANDED_FREQUENCY_OUTPUT
{
    ULONG Version;
    ULONG NominalFrequency; // if (Domain) Prcb->PowerState.CheckContext.Domain.NominalFrequency else Prcb->MHz
} POWER_INTERNAL_PROCESSOR_BRANDED_FREQUENCY_OUTPUT, * PPOWER_INTERNAL_PROCESSOR_BRANDED_FREQUENCY_OUTPUT;

// rev
typedef struct _PROCESSOR_IDLE_VETO
{
    ULONG Version;
    PROCESSOR_NUMBER ProcessorNumber;
    ULONG StateIndex;
    ULONG VetoReason;
    UCHAR Increment;
} PROCESSOR_IDLE_VETO, * PPROCESSOR_IDLE_VETO;

// rev
typedef struct _PLATFORM_IDLE_VETO
{
    ULONG Version;
    ULONG StateIndex;
    ULONG VetoReason;
    UCHAR Increment;
} PLATFORM_IDLE_VETO, * PPLATFORM_IDLE_VETO;

// rev
typedef struct _POWER_INTERNAL_BOOTAPP_DIAGNOSTIC
{
    ULONG BootAppErrorDiagCode; // bcdedit last status
    ULONG BootAppFailureStatus; // bcdedit last status
} POWER_INTERNAL_BOOTAPP_DIAGNOSTIC, * PPOWER_INTERNAL_BOOTAPP_DIAGNOSTIC;

/**
 * The NtPowerInformation routine sets or retrieves system power information.
 *
 * @param InformationLevel Specifies the requested information level, which indicates the specific power information to be set or retrieved.
 * @param InputBuffer Optional pointer to a caller-allocated input buffer.
 * @param InputBufferLength Size, in bytes, of the buffer at InputBuffer.
 * @param OutputBuffer Optional pointer to an output buffer. The type depends on the InformationLevel requested.
 * @param OutputBufferLength Size, in bytes, of the output buffer.
 * @return Successful or errant status.
 */
_IRQL_requires_max_(APC_LEVEL)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtPowerInformation(
    _In_ POWER_INFORMATION_LEVEL InformationLevel,
    _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwPowerInformation(
    _In_ POWER_INFORMATION_LEVEL InformationLevel,
    _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength
);

/**
 * Enables an application to inform the system that it is in use,
 * thereby preventing the system from entering sleep or turning off the display while the application is running.
 *
 * @param NewFlags New execution state flags.
 * @param PreviousFlags Pointer to receive the previous execution state flags.
 * @return Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetThreadExecutionState(
    _In_ EXECUTION_STATE NewFlags, // ES_* flags
    _Out_ EXECUTION_STATE* PreviousFlags
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSetThreadExecutionState(
    _In_ EXECUTION_STATE NewFlags, // ES_* flags
    _Out_ EXECUTION_STATE* PreviousFlags
);

/**
 * Requests the system resume latency.
 *
 * @param latency The desired latency time.
 * @return Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtRequestWakeupLatency(
    _In_ LATENCY_TIME latency
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwRequestWakeupLatency(
    _In_ LATENCY_TIME latency
);

/**
 * Initiates a power action of the current system.
 *
 * @param SystemAction The system power action.
 * @param LightestSystemState The lightest system power state.
 * @param Flags Flags for the power action.
 * @param Asynchronous Whether the action is asynchronous.
 * @return Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtInitiatePowerAction(
    _In_ POWER_ACTION SystemAction,
    _In_ SYSTEM_POWER_STATE LightestSystemState,
    _In_ ULONG Flags, // POWER_ACTION_* flags
    _In_ BOOLEAN Asynchronous
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwInitiatePowerAction(
    _In_ POWER_ACTION SystemAction,
    _In_ SYSTEM_POWER_STATE LightestSystemState,
    _In_ ULONG Flags, // POWER_ACTION_* flags
    _In_ BOOLEAN Asynchronous
);

/**
 * Initiates a power action of the current system. Depending on the Flags parameter, the function either
 * suspends operation immediately or requests permission from all applications and device drivers before doing so.
 *
 * @param SystemAction The system power action.
 * @param LightestSystemState The lightest system power state.
 * @param Flags Flags for the power action.
 * @return Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetSystemPowerState(
    _In_ POWER_ACTION SystemAction,
    _In_ SYSTEM_POWER_STATE LightestSystemState,
    _In_ ULONG Flags // POWER_ACTION_* flags
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSetSystemPowerState(
    _In_ POWER_ACTION SystemAction,
    _In_ SYSTEM_POWER_STATE LightestSystemState,
    _In_ ULONG Flags // POWER_ACTION_* flags
);

/**
 * Retrieves the current power state of the specified device. This function cannot be used to query the power state of a display device.
 *
 * @param Device A handle to an object on the device, such as a file or socket, or a handle to the device itself.
 * @param State A pointer to the variable that receives the power state.
 * @return Successful or errant status.
 * @remarks An application can use NtGetDevicePowerState to determine whether a device is in the working state or a low-power state.
 * If the device is in a low-power state, accessing the device may cause it to either queue or fail any I/O requests, or transition the device into the working state.
 * The exact behavior depends on the implementation of the device.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtGetDevicePowerState(
    _In_ HANDLE Device,
    _Out_ PDEVICE_POWER_STATE State
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwGetDevicePowerState(
    _In_ HANDLE Device,
    _Out_ PDEVICE_POWER_STATE State
);

/**
 * Checks if the system resume is automatic.
 *
 * @return BOOLEAN TRUE if the system resume is automatic, FALSE otherwise.
 */
__kernel_entry NTSYSCALLAPI
BOOLEAN
NTAPI
NtIsSystemResumeAutomatic(
    VOID
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
BOOLEAN
NTAPI
ZwIsSystemResumeAutomatic(
    VOID
);


VEIL_END()

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
