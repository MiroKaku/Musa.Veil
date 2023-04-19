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
// 'struct_name' : structure was padded due to __declspec(align())
#pragma warning(disable:4324)
// 'enumeration': a forward declaration of an unscoped enumeration must have an
// underlying type (int assumed)
#pragma warning(disable:4471)
#endif

VEIL_BEGIN()

//
// System service table descriptor.
//

#define NUMBER_SERVICE_TABLES       2
#define SERVICE_TABLE_MASK          0x0FFF
#define SERVICE_TABLE_WIN32K_TEST   (~SERVICE_TABLE_MASK)

typedef struct _KKSYSTEM_SERVICE_TABLE
{
    INT32* ServiceTable;        // nt!KiServiceTable /win32k!W32pServiceTable  (ServiceTable[SystemCallNumber])
    ULONG* ServiceCallCount;    // unused
    ULONG  NumberOfServices;    // nt!KiServiceLimit
    BYTE * ArgumentTable;       // nt!KiArgumentTable/win32k!W32pArgumentTable (ArgumentTable[SystemCallNumber])
} KSYSTEM_SERVICE_TABLE, * PKSYSTEM_SERVICE_TABLE;

//
// Thread State
//

#ifndef _KERNEL_MODE
#define LOW_PRIORITY             0 // Lowest thread priority level
#define LOW_REALTIME_PRIORITY   16 // Lowest realtime priority level
#define HIGH_PRIORITY           31 // Highest thread priority level
#define MAXIMUM_PRIORITY        32 // Number of thread priority levels
#endif // !_KERNEL_MODE

// private
typedef enum _KTHREAD_STATE
{
    Initialized,
    Ready,
    Running,
    Standby,
    Terminated,
    Waiting,
    Transition,
    DeferredReady,
    GateWaitObsolete,
    WaitingForProcessInSwap,
    MaximumThreadState
} KTHREAD_STATE, * PKTHREAD_STATE;

// private
typedef enum _KHETERO_CPU_POLICY
{
    KHeteroCpuPolicyAll,
    KHeteroCpuPolicyLarge,
    KHeteroCpuPolicyLargeOrIdle,
    KHeteroCpuPolicySmall,
    KHeteroCpuPolicySmallOrIdle,
    KHeteroCpuPolicyDynamic,
    KHeteroCpuPolicyStaticMax = 5, // valid
    KHeteroCpuPolicyBiasedSmall,
    KHeteroCpuPolicyBiasedLarge,
    KHeteroCpuPolicyDefault,
    KHeteroCpuPolicyMax
} KHETERO_CPU_POLICY, * PKHETERO_CPU_POLICY;

#ifndef _KERNEL_MODE
//
// Wait reasons
//

typedef enum _KWAIT_REASON
{
    Executive,
    FreePage,
    PageIn,
    PoolAllocation,
    DelayExecution,
    Suspended,
    UserRequest,
    WrExecutive,
    WrFreePage,
    WrPageIn,
    WrPoolAllocation,
    WrDelayExecution,
    WrSuspended,
    WrUserRequest,
    WrEventPair,
    WrQueue,
    WrLpcReceive,
    WrLpcReply,
    WrVirtualMemory,
    WrPageOut,
    WrRendezvous,
    WrKeyedEvent,
    WrTerminated,
    WrProcessInSwap,
    WrCpuRateControl,
    WrCalloutStack,
    WrKernel,
    WrResource,
    WrPushLock,
    WrMutex,
    WrQuantumEnd,
    WrDispatchInt,
    WrPreempted,
    WrYieldExecution,
    WrFastMutex,
    WrGuardedMutex,
    WrRundown,
    WrAlertByThreadId,
    WrDeferredPreempt,
    WrPhysicalFault,
    WrIoRing,
    WrMdlCache,
    MaximumWaitReason
} KWAIT_REASON, * PKWAIT_REASON;

//
// Profile source types
//

typedef enum _KPROFILE_SOURCE
{
    ProfileTime,
    ProfileAlignmentFixup,
    ProfileTotalIssues,
    ProfilePipelineDry,
    ProfileLoadInstructions,
    ProfilePipelineFrozen,
    ProfileBranchInstructions,
    ProfileTotalNonissues,
    ProfileDcacheMisses,
    ProfileIcacheMisses,
    ProfileCacheMisses,
    ProfileBranchMispredictions,
    ProfileStoreInstructions,
    ProfileFpInstructions,
    ProfileIntegerInstructions,
    Profile2Issue,
    Profile3Issue,
    Profile4Issue,
    ProfileSpecialInstructions,
    ProfileTotalCycles,
    ProfileIcacheIssues,
    ProfileDcacheAccesses,
    ProfileMemoryBarrierCycles,
    ProfileLoadLinkedIssues,
    ProfileMaximum
} KPROFILE_SOURCE;
#endif // !_KERNEL_MODE

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCallbackReturn(
    _In_reads_bytes_opt_(OutputLength) PVOID OutputBuffer,
    _In_ ULONG OutputLength,
    _In_ NTSTATUS Status
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCallbackReturn(
    _In_reads_bytes_opt_(OutputLength) PVOID OutputBuffer,
    _In_ ULONG OutputLength,
    _In_ NTSTATUS Status
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
__kernel_entry NTSYSCALLAPI
VOID
NTAPI
NtFlushProcessWriteBuffers(
    VOID
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
VOID
NTAPI
ZwFlushProcessWriteBuffers(
    VOID
);
#endif

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtYieldExecution(
    VOID
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwYieldExecution(
    VOID
);


//
// Only Kernel
//

#ifdef _KERNEL_MODE

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
BOOLEAN
NTAPI
KeAddSystemServiceTable(
    _In_ PULONG_PTR Base,
    _In_opt_ PULONG Count,
    _In_ ULONG      Limit,
    _In_ PUCHAR     Number,
    _In_ ULONG      Index
);

// Thread 

typedef enum _KAPC_ENVIRONMENT
{
    OriginalApcEnvironment,
    AttachedApcEnvironment,
    CurrentApcEnvironment,
    InsertApcEnvironment
} KAPC_ENVIRONMENT;

typedef
VOID
(*PKNORMAL_ROUTINE) (
    IN PVOID NormalContext,
    IN PVOID SystemArgument1,
    IN PVOID SystemArgument2
    );

typedef
VOID
(*PKKERNEL_ROUTINE) (
    IN struct _KAPC* Apc,
    IN OUT PKNORMAL_ROUTINE* NormalRoutine,
    IN OUT PVOID* NormalContext,
    IN OUT PVOID* SystemArgument1,
    IN OUT PVOID* SystemArgument2
    );

typedef
VOID
(*PKRUNDOWN_ROUTINE) (
    IN struct _KAPC* Apc
    );

typedef
BOOLEAN
(*PKSYNCHRONIZE_ROUTINE) (
    IN PVOID SynchronizeContext
    );

typedef
BOOLEAN
(*PKTRANSFER_ROUTINE) (
    VOID
    );

NTSYSAPI
VOID
NTAPI
KeInitializeApc(
    _Out_    PRKAPC             Apc,
    _In_     PRKTHREAD          Thread,
    _In_     KAPC_ENVIRONMENT   Environment,
    _In_     PKKERNEL_ROUTINE   KernelRoutine,
    _In_opt_ PKRUNDOWN_ROUTINE  RundownRoutine,
    _In_opt_ PKNORMAL_ROUTINE   NormalRoutine,
    _In_opt_ KPROCESSOR_MODE    ProcessorMode,
    _In_opt_ PVOID              NormalContext
);

NTSYSAPI
BOOLEAN
NTAPI
KeInsertQueueApc(
    _Inout_ PRKAPC Apc,
    _In_opt_ PVOID SystemArgument1,
    _In_opt_ PVOID SystemArgument2,
    _In_ KPRIORITY Increment
);

NTSYSAPI
BOOLEAN
NTAPI
KeRemoveQueueApc(
    _In_ PKAPC Apc
);

NTSYSAPI
BOOLEAN
NTAPI
KeTestAlertThread(
    _In_ KPROCESSOR_MODE AlertMode
);

// Processor

NTSYSAPI
VOID
NTAPI
KeGenericCallDpc(
    _In_ PKDEFERRED_ROUTINE Routine,
    _In_ PVOID Context
);

NTSYSAPI
VOID
NTAPI
KeSignalCallDpcDone(
    _In_ PVOID SystemArgument1
);

NTSYSAPI
LOGICAL
NTAPI
KeSignalCallDpcSynchronize(
    _In_ PVOID SystemArgument2
);

// Fix: unresolved external symbol 'KeInitializeSpinLock'
#if ((defined(_X86_) && (defined(_WDM_INCLUDED_) || defined(WIN9X_COMPAT_SPINLOCK))) || \
     ((NTDDI_VERSION > NTDDI_WIN7) && !defined(WIN9X_COMPAT_SPINLOCK) && \
      (defined(_NTDRIVER_) || defined(_NTDDK_) || defined(_NTIFS_) || defined(_NTHAL_) || defined(_NTOSP_) || defined(_BLDR_))))

#ifndef KeInitializeSpinLock

inline
VOID
NTAPI
_VEIL_IMPL_KeInitializeSpinLock(
    _Out_ PKSPIN_LOCK SpinLock
)

/*++

Routine Description:

    This function initializes a spinlock.

Arguments:

    SpinLock - Supplies a pointer to a spinlock.

Return Value:

    None.

--*/

{
    *SpinLock = 0;
    return;
}

#if defined _M_X64 || defined _M_ARM || defined _M_ARM64
_VEIL_DEFINE_IAT_SYMBOL(KeInitializeSpinLock, _VEIL_IMPL_KeInitializeSpinLock);
#endif

#endif // KeInitializeSpinLock
#endif

#endif // _KERNEL_MODE

VEIL_END()

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
