/*
 * PROJECT:   Veil
 * FILE:      Veil.System.ConfigurationManager.h
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
// 'struct_name' : structure was padded due to __declspec(align())
#pragma warning(disable:4324)
// 'enumeration': a forward declaration of an unscoped enumeration must have an
// underlying type (int assumed)
#pragma warning(disable:4471)
#endif

VEIL_BEGIN()

// Boot condition flags (NtInitializeRegistry)

#define REG_INIT_BOOT_SM            0x0000
#define REG_INIT_BOOT_SETUP         0x0001
#define REG_INIT_BOOT_ACCEPTED_BASE 0x0002
#define REG_INIT_BOOT_ACCEPTED_MAX  REG_INIT_BOOT_ACCEPTED_BASE + 999

#define REG_MAX_KEY_VALUE_NAME_LENGTH   32767
#define REG_MAX_KEY_NAME_LENGTH         512

#ifndef _KERNEL_MODE
typedef enum _KEY_INFORMATION_CLASS
{
    KeyBasicInformation, // KEY_BASIC_INFORMATION
    KeyNodeInformation, // KEY_NODE_INFORMATION
    KeyFullInformation, // KEY_FULL_INFORMATION
    KeyNameInformation, // KEY_NAME_INFORMATION
    KeyCachedInformation, // KEY_CACHED_INFORMATION
    KeyFlagsInformation, // KEY_FLAGS_INFORMATION
    KeyVirtualizationInformation, // KEY_VIRTUALIZATION_INFORMATION
    KeyHandleTagsInformation, // KEY_HANDLE_TAGS_INFORMATION
    KeyTrustInformation, // KEY_TRUST_INFORMATION
    KeyLayerInformation, // KEY_LAYER_INFORMATION
    MaxKeyInfoClass
} KEY_INFORMATION_CLASS;

typedef struct _KEY_BASIC_INFORMATION
{
    LARGE_INTEGER LastWriteTime;
    ULONG TitleIndex;
    ULONG NameLength;
    _Field_size_bytes_(NameLength) WCHAR Name[1];
} KEY_BASIC_INFORMATION, * PKEY_BASIC_INFORMATION;

typedef struct _KEY_NODE_INFORMATION
{
    LARGE_INTEGER LastWriteTime;
    ULONG TitleIndex;
    ULONG ClassOffset;
    ULONG ClassLength;
    ULONG NameLength;
    _Field_size_bytes_(NameLength) WCHAR Name[1];
    // ...
    // _Field_size_bytes_(ClassLength) WCHAR Class[1];
} KEY_NODE_INFORMATION, * PKEY_NODE_INFORMATION;

typedef struct _KEY_FULL_INFORMATION
{
    LARGE_INTEGER LastWriteTime;
    ULONG   TitleIndex;
    ULONG   ClassOffset;
    ULONG   ClassLength;
    ULONG   SubKeys;
    ULONG   MaxNameLen;
    ULONG   MaxClassLen;
    ULONG   Values;
    ULONG   MaxValueNameLen;
    ULONG   MaxValueDataLen;
    _Field_size_bytes_(ClassLength) WCHAR   Class[1];           // Variable length
} KEY_FULL_INFORMATION, * PKEY_FULL_INFORMATION;

typedef struct _KEY_NAME_INFORMATION
{
    ULONG NameLength;
    _Field_size_bytes_(NameLength) WCHAR Name[1];
} KEY_NAME_INFORMATION, * PKEY_NAME_INFORMATION;

typedef struct _KEY_CACHED_INFORMATION
{
    LARGE_INTEGER LastWriteTime;
    ULONG TitleIndex;
    ULONG SubKeys;
    ULONG MaxNameLen;
    ULONG Values;
    ULONG MaxValueNameLen;
    ULONG MaxValueDataLen;
    ULONG NameLength;
    _Field_size_bytes_(NameLength) WCHAR Name[1];
} KEY_CACHED_INFORMATION, * PKEY_CACHED_INFORMATION;
#endif //!_KERNEL_MODE

// rev
#define REG_FLAG_VOLATILE   0x0001
#define REG_FLAG_LINK       0x0002

// msdn
#define REG_KEY_DONT_VIRTUALIZE     0x0002
#define REG_KEY_DONT_SILENT_FAIL    0x0004
#define REG_KEY_RECURSE_FLAG        0x0008

// private
typedef struct _KEY_FLAGS_INFORMATION
{
    ULONG Wow64Flags;
    ULONG KeyFlags; // REG_FLAG_*
    ULONG ControlFlags; // REG_KEY_*
} KEY_FLAGS_INFORMATION, * PKEY_FLAGS_INFORMATION;

#ifndef _KERNEL_MODE
typedef struct _KEY_VIRTUALIZATION_INFORMATION
{
    ULONG VirtualizationCandidate : 1; // Tells whether the key is part of the virtualization namespace scope (only HKLM\Software for now).
    ULONG VirtualizationEnabled : 1; // Tells whether virtualization is enabled on this key. Can be 1 only if above flag is 1.
    ULONG VirtualTarget : 1; // Tells if the key is a virtual key. Can be 1 only if above 2 are 0. Valid only on the virtual store key handles.
    ULONG VirtualStore : 1; // Tells if the key is a part of the virtual store path. Valid only on the virtual store key handles.
    ULONG VirtualSource : 1; // Tells if the key has ever been virtualized, can be 1 only if VirtualizationCandidate is 1.
    ULONG Reserved : 27;
} KEY_VIRTUALIZATION_INFORMATION, * PKEY_VIRTUALIZATION_INFORMATION;

// private
typedef struct _KEY_TRUST_INFORMATION
{
    ULONG TrustedKey : 1;
    ULONG Reserved : 31;
} KEY_TRUST_INFORMATION, * PKEY_TRUST_INFORMATION;

// private
typedef struct _KEY_LAYER_INFORMATION
{
    ULONG IsTombstone : 1;
    ULONG IsSupersedeLocal : 1;
    ULONG IsSupersedeTree : 1;
    ULONG ClassIsInherited : 1;
    ULONG Reserved : 28;
} KEY_LAYER_INFORMATION, * PKEY_LAYER_INFORMATION;

typedef enum _KEY_SET_INFORMATION_CLASS
{
    KeyWriteTimeInformation, // KEY_WRITE_TIME_INFORMATION
    KeyWow64FlagsInformation, // KEY_WOW64_FLAGS_INFORMATION
    KeyControlFlagsInformation, // KEY_CONTROL_FLAGS_INFORMATION
    KeySetVirtualizationInformation, // KEY_SET_VIRTUALIZATION_INFORMATION
    KeySetDebugInformation,
    KeySetHandleTagsInformation, // KEY_HANDLE_TAGS_INFORMATION
    KeySetLayerInformation, // KEY_SET_LAYER_INFORMATION
    MaxKeySetInfoClass
} KEY_SET_INFORMATION_CLASS;

typedef struct _KEY_WRITE_TIME_INFORMATION
{
    LARGE_INTEGER LastWriteTime;
} KEY_WRITE_TIME_INFORMATION, * PKEY_WRITE_TIME_INFORMATION;

typedef struct _KEY_WOW64_FLAGS_INFORMATION
{
    ULONG UserFlags;
} KEY_WOW64_FLAGS_INFORMATION, * PKEY_WOW64_FLAGS_INFORMATION;

typedef struct _KEY_HANDLE_TAGS_INFORMATION
{
    ULONG HandleTags;
} KEY_HANDLE_TAGS_INFORMATION, * PKEY_HANDLE_TAGS_INFORMATION;

typedef struct _KEY_SET_LAYER_INFORMATION
{
    ULONG IsTombstone : 1;
    ULONG IsSupersedeLocal : 1;
    ULONG IsSupersedeTree : 1;
    ULONG ClassIsInherited : 1;
    ULONG Reserved : 28;
} KEY_SET_LAYER_INFORMATION, * PKEY_SET_LAYER_INFORMATION;

typedef struct _KEY_CONTROL_FLAGS_INFORMATION
{
    ULONG ControlFlags;
} KEY_CONTROL_FLAGS_INFORMATION, * PKEY_CONTROL_FLAGS_INFORMATION;

typedef struct _KEY_SET_VIRTUALIZATION_INFORMATION
{
    ULONG VirtualTarget : 1;
    ULONG VirtualStore : 1;
    ULONG VirtualSource : 1; // true if key has been virtualized at least once
    ULONG Reserved : 29;
} KEY_SET_VIRTUALIZATION_INFORMATION, * PKEY_SET_VIRTUALIZATION_INFORMATION;

typedef enum _KEY_VALUE_INFORMATION_CLASS
{
    KeyValueBasicInformation, // KEY_VALUE_BASIC_INFORMATION
    KeyValueFullInformation, // KEY_VALUE_FULL_INFORMATION
    KeyValuePartialInformation, // KEY_VALUE_PARTIAL_INFORMATION
    KeyValueFullInformationAlign64,
    KeyValuePartialInformationAlign64,  // KEY_VALUE_PARTIAL_INFORMATION_ALIGN64
    KeyValueLayerInformation, // KEY_VALUE_LAYER_INFORMATION
    MaxKeyValueInfoClass
} KEY_VALUE_INFORMATION_CLASS;

typedef struct _KEY_VALUE_BASIC_INFORMATION
{
    ULONG TitleIndex;
    ULONG Type;
    ULONG NameLength;
    WCHAR Name[1];
} KEY_VALUE_BASIC_INFORMATION, * PKEY_VALUE_BASIC_INFORMATION;

typedef struct _KEY_VALUE_FULL_INFORMATION
{
    ULONG TitleIndex;
    ULONG Type;
    ULONG DataOffset;
    ULONG DataLength;
    ULONG NameLength;
    WCHAR Name[1];
    // ...
    // UCHAR Data[1];
} KEY_VALUE_FULL_INFORMATION, * PKEY_VALUE_FULL_INFORMATION;

typedef struct _KEY_VALUE_PARTIAL_INFORMATION
{
    ULONG TitleIndex;
    ULONG Type;
    ULONG DataLength;
    UCHAR Data[1];
} KEY_VALUE_PARTIAL_INFORMATION, * PKEY_VALUE_PARTIAL_INFORMATION;

typedef struct _KEY_VALUE_PARTIAL_INFORMATION_ALIGN64
{
    ULONG Type;
    ULONG DataLength;
    UCHAR Data[1];
} KEY_VALUE_PARTIAL_INFORMATION_ALIGN64, * PKEY_VALUE_PARTIAL_INFORMATION_ALIGN64;

// private
typedef struct _KEY_VALUE_LAYER_INFORMATION
{
    ULONG IsTombstone : 1;
    ULONG Reserved : 31;
} KEY_VALUE_LAYER_INFORMATION, * PKEY_VALUE_LAYER_INFORMATION;
#endif //!_KERNEL_MODE

// private
typedef enum _CM_EXTENDED_PARAMETER_TYPE
{
    CmExtendedParameterInvalidType,
    CmExtendedParameterTrustClassKey,
    CmExtendedParameterEvent,
    CmExtendedParameterFileAccessToken,
    CmExtendedParameterMax,
} CM_EXTENDED_PARAMETER_TYPE;

#define CM_EXTENDED_PARAMETER_TYPE_BITS 8

// private
typedef struct DECLSPEC_ALIGN(8) _CM_EXTENDED_PARAMETER
{
    struct
    {
        ULONG64 Type : CM_EXTENDED_PARAMETER_TYPE_BITS;
        ULONG64 Reserved : 64 - CM_EXTENDED_PARAMETER_TYPE_BITS;
    };

    union
    {
        ULONG64 ULong64;
        PVOID Pointer;
        SIZE_T Size;
        HANDLE Handle;
        ULONG ULong;
        ACCESS_MASK AccessMask;
    };
} CM_EXTENDED_PARAMETER, * PCM_EXTENDED_PARAMETER;

#ifndef _KERNEL_MODE
typedef struct _KEY_VALUE_ENTRY
{
    PUNICODE_STRING ValueName;
    ULONG DataLength;
    ULONG DataOffset;
    ULONG Type;
} KEY_VALUE_ENTRY, * PKEY_VALUE_ENTRY;
#endif // !_KERNEL_MODE

typedef enum _REG_ACTION
{
    KeyAdded,
    KeyRemoved,
    KeyModified
} REG_ACTION;

typedef struct _REG_NOTIFY_INFORMATION
{
    ULONG NextEntryOffset;
    REG_ACTION Action;
    ULONG KeyLength;
    _Field_size_bytes_(KeyLength) WCHAR Key[1];
} REG_NOTIFY_INFORMATION, * PREG_NOTIFY_INFORMATION;

typedef struct _KEY_PID_ARRAY
{
    HANDLE ProcessId;
    UNICODE_STRING KeyName;
} KEY_PID_ARRAY, * PKEY_PID_ARRAY;

typedef struct _KEY_OPEN_SUBKEYS_INFORMATION
{
    ULONG Count;
    KEY_PID_ARRAY KeyArray[1];
} KEY_OPEN_SUBKEYS_INFORMATION, * PKEY_OPEN_SUBKEYS_INFORMATION;

// Differencing registry & virtualization // since REDSTONE

// rev
#define VR_DEVICE_NAME L"\\Device\\VRegDriver"

// rev
#define IOCTL_VR_INITIALIZE_JOB_FOR_VREG            CTL_CODE(FILE_DEVICE_UNKNOWN, 1, METHOD_BUFFERED, FILE_ANY_ACCESS) // in: VR_INITIALIZE_JOB_FOR_VREG
#define IOCTL_VR_LOAD_DIFFERENCING_HIVE             CTL_CODE(FILE_DEVICE_UNKNOWN, 2, METHOD_BUFFERED, FILE_ANY_ACCESS) // in: VR_LOAD_DIFFERENCING_HIVE
#define IOCTL_VR_CREATE_NAMESPACE_NODE              CTL_CODE(FILE_DEVICE_UNKNOWN, 3, METHOD_BUFFERED, FILE_ANY_ACCESS) // in: VR_CREATE_NAMESPACE_NODE
#define IOCTL_VR_MODIFY_FLAGS                       CTL_CODE(FILE_DEVICE_UNKNOWN, 4, METHOD_BUFFERED, FILE_ANY_ACCESS) // in: VR_MODIFY_FLAGS
#define IOCTL_VR_CREATE_MULTIPLE_NAMESPACE_NODES    CTL_CODE(FILE_DEVICE_UNKNOWN, 5, METHOD_BUFFERED, FILE_ANY_ACCESS) // in: VR_CREATE_MULTIPLE_NAMESPACE_NODES
#define IOCTL_VR_UNLOAD_DYNAMICALLY_LOADED_HIVES    CTL_CODE(FILE_DEVICE_UNKNOWN, 6, METHOD_BUFFERED, FILE_ANY_ACCESS) // in: VR_UNLOAD_DYNAMICALLY_LOADED_HIVES
#define IOCTL_VR_GET_VIRTUAL_ROOT_KEY               CTL_CODE(FILE_DEVICE_UNKNOWN, 7, METHOD_BUFFERED, FILE_ANY_ACCESS) // in: VR_GET_VIRTUAL_ROOT; out: VR_GET_VIRTUAL_ROOT_RESULT
#define IOCTL_VR_LOAD_DIFFERENCING_HIVE_FOR_HOST    CTL_CODE(FILE_DEVICE_UNKNOWN, 8, METHOD_BUFFERED, FILE_ANY_ACCESS) // in: VR_LOAD_DIFFERENCING_HIVE_FOR_HOST
#define IOCTL_VR_UNLOAD_DIFFERENCING_HIVE_FOR_HOST  CTL_CODE(FILE_DEVICE_UNKNOWN, 9, METHOD_BUFFERED, FILE_ANY_ACCESS) // in: VR_UNLOAD_DIFFERENCING_HIVE_FOR_HOST

// private
typedef struct _VR_INITIALIZE_JOB_FOR_VREG
{
    HANDLE Job;
} VR_INITIALIZE_JOB_FOR_VREG, * PVR_INITIALIZE_JOB_FOR_VREG;

// rev
#define VR_FLAG_INHERIT_TRUST_CLASS 0x00000001
#define VR_FLAG_WRITE_THROUGH_HIVE 0x00000002 // since REDSTONE2
#define VR_FLAG_LOCAL_MACHINE_TRUST_CLASS 0x00000004 // since 21H1

// rev + private
typedef struct _VR_LOAD_DIFFERENCING_HIVE
{
    HANDLE Job;
    ULONG NextLayerIsHost;
    ULONG Flags; // VR_FLAG_*
    ULONG LoadFlags; // NtLoadKeyEx flags
    WORD KeyPathLength;
    WORD HivePathLength;
    WORD NextLayerKeyPathLength;
    HANDLE FileAccessToken; // since 20H1
    WCHAR Strings[ANYSIZE_ARRAY];
    // ...
    // WCHAR KeyPath[1];
    // WCHAR HivePath[1];
    // WCHAR NextLayerKeyPath[1];
} VR_LOAD_DIFFERENCING_HIVE, * PVR_LOAD_DIFFERENCING_HIVE;

// rev + private
typedef struct _VR_CREATE_NAMESPACE_NODE
{
    HANDLE Job;
    WORD ContainerPathLength;
    WORD HostPathLength;
    ULONG Flags;
    ACCESS_MASK AccessMask; // since 20H1
    WCHAR Strings[ANYSIZE_ARRAY];
    // ...
    // WCHAR ContainerPath[1];
    // WCHAR HostPath[1];
} VR_CREATE_NAMESPACE_NODE, * PVR_CREATE_NAMESPACE_NODE;

// private
typedef struct _VR_MODIFY_FLAGS
{
    HANDLE Job;
    ULONG AddFlags;
    ULONG RemoveFlags;
} VR_MODIFY_FLAGS, * PVR_MODIFY_FLAGS;

// private
typedef struct _NAMESPACE_NODE_DATA
{
    ACCESS_MASK AccessMask;
    WORD ContainerPathLength;
    WORD HostPathLength;
    ULONG Flags;
    WCHAR Strings[ANYSIZE_ARRAY];
    // ...
    // WCHAR ContainerPath[1];
    // WCHAR HostPath[1];
} NAMESPACE_NODE_DATA, * PNAMESPACE_NODE_DATA;

// private
typedef struct _VR_CREATE_MULTIPLE_NAMESPACE_NODES
{
    HANDLE Job;
    ULONG NumNewKeys;
    NAMESPACE_NODE_DATA Keys[1];
} VR_CREATE_MULTIPLE_NAMESPACE_NODES, * PVR_CREATE_MULTIPLE_NAMESPACE_NODES;

// private
typedef struct _VR_UNLOAD_DYNAMICALLY_LOADED_HIVES
{
    HANDLE Job;
} VR_UNLOAD_DYNAMICALLY_LOADED_HIVES, * PVR_UNLOAD_DYNAMICALLY_LOADED_HIVES;

// rev
#define VR_KEY_COMROOT 0          // \Registry\ComRoot\Classes
#define VR_KEY_MACHINE_SOFTWARE 1 // \Registry\Machine\Software // since REDSTONE2
#define VR_KEY_CONTROL_SET 2      // \Registry\Machine\System\ControlSet001 // since REDSTONE2

// rev
typedef struct _VR_GET_VIRTUAL_ROOT
{
    HANDLE Job;
    ULONG Index; // VR_KEY_* // since REDSTONE2
} VR_GET_VIRTUAL_ROOT, * PVR_GET_VIRTUAL_ROOT;

// rev
typedef struct _VR_GET_VIRTUAL_ROOT_RESULT
{
    HANDLE Key;
} VR_GET_VIRTUAL_ROOT_RESULT, * PVR_GET_VIRTUAL_ROOT_RESULT;

// rev
typedef struct _VR_LOAD_DIFFERENCING_HIVE_FOR_HOST
{
    ULONG LoadFlags; // NtLoadKeyEx flags
    ULONG Flags; // VR_FLAG_* // since REDSTONE2
    WORD KeyPathLength;
    WORD HivePathLength;
    WORD NextLayerKeyPathLength;
    HANDLE FileAccessToken; // since 20H1
    WCHAR Strings[ANYSIZE_ARRAY];
    // ...
    // WCHAR KeyPath[1];
    // WCHAR HivePath[1];
    // WCHAR NextLayerKeyPath[1];
} VR_LOAD_DIFFERENCING_HIVE_FOR_HOST, * PVR_LOAD_DIFFERENCING_HIVE_FOR_HOST;

// rev
typedef struct _VR_UNLOAD_DIFFERENCING_HIVE_FOR_HOST
{
    ULONG Reserved;
    WORD TargetKeyPathLength;
    WCHAR TargetKeyPath[ANYSIZE_ARRAY];
} VR_UNLOAD_DIFFERENCING_HIVE_FOR_HOST, * PVR_UNLOAD_DIFFERENCING_HIVE_FOR_HOST;

// System calls

__kernel_entry __kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateKey(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Reserved_ ULONG TitleIndex,
    _In_opt_ PUNICODE_STRING Class,
    _In_ ULONG CreateOptions,
    _Out_opt_ PULONG Disposition
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateKey(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Reserved_ ULONG TitleIndex,
    _In_opt_ PUNICODE_STRING Class,
    _In_ ULONG CreateOptions,
    _Out_opt_ PULONG Disposition
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateKeyTransacted(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Reserved_ ULONG TitleIndex,
    _In_opt_ PUNICODE_STRING Class,
    _In_ ULONG CreateOptions,
    _In_ HANDLE TransactionHandle,
    _Out_opt_ PULONG Disposition
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
ZwCreateKeyTransacted(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _Reserved_ ULONG TitleIndex,
    _In_opt_ PUNICODE_STRING Class,
    _In_ ULONG CreateOptions,
    _In_ HANDLE TransactionHandle,
    _Out_opt_ PULONG Disposition
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenKey(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwOpenKey(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenKeyTransacted(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE TransactionHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwOpenKeyTransacted(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE TransactionHandle
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenKeyEx(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG OpenOptions
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwOpenKeyEx(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG OpenOptions
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenKeyTransactedEx(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG OpenOptions,
    _In_ HANDLE TransactionHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwOpenKeyTransactedEx(
    _Out_ PHANDLE KeyHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG OpenOptions,
    _In_ HANDLE TransactionHandle
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtDeleteKey(
    _In_ HANDLE KeyHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwDeleteKey(
    _In_ HANDLE KeyHandle
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtRenameKey(
    _In_ HANDLE KeyHandle,
    _In_ PUNICODE_STRING NewName
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwRenameKey(
    _In_ HANDLE KeyHandle,
    _In_ PUNICODE_STRING NewName
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtDeleteValueKey(
    _In_ HANDLE KeyHandle,
    _In_ PUNICODE_STRING ValueName
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwDeleteValueKey(
    _In_ HANDLE KeyHandle,
    _In_ PUNICODE_STRING ValueName
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryKey(
    _In_ HANDLE KeyHandle,
    _In_ KEY_INFORMATION_CLASS KeyInformationClass,
    _Out_writes_bytes_opt_(Length) PVOID KeyInformation,
    _In_ ULONG Length,
    _Out_ PULONG ResultLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_When_(Length == 0, _Post_satisfies_(return < 0))
_When_(Length > 0, _Post_satisfies_(return <= 0))
_Success_(return == STATUS_SUCCESS)
_On_failure_(_When_(return == STATUS_BUFFER_OVERFLOW || return == STATUS_BUFFER_TOO_SMALL, _Post_satisfies_(*ResultLength > Length)))
NTSYSAPI
NTSTATUS
NTAPI
ZwQueryKey(
    _In_ HANDLE KeyHandle,
    _In_ KEY_INFORMATION_CLASS KeyInformationClass,
    _Out_writes_bytes_to_opt_(Length, *ResultLength) PVOID KeyInformation,
    _In_ ULONG Length,
    _Out_ PULONG ResultLength
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationKey(
    _In_ HANDLE KeyHandle,
    _In_ KEY_SET_INFORMATION_CLASS KeySetInformationClass,
    _In_reads_bytes_(KeySetInformationLength) PVOID KeySetInformation,
    _In_ ULONG KeySetInformationLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSetInformationKey(
    _In_ HANDLE KeyHandle,
    _In_ __drv_strictTypeMatch(__drv_typeConst)
    KEY_SET_INFORMATION_CLASS KeySetInformationClass,
    _In_reads_bytes_(KeySetInformationLength) PVOID KeySetInformation,
    _In_ ULONG KeySetInformationLength
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryValueKey(
    _In_ HANDLE KeyHandle,
    _In_ PUNICODE_STRING ValueName,
    _In_ KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
    _Out_writes_bytes_opt_(Length) PVOID KeyValueInformation,
    _In_ ULONG Length,
    _Out_ PULONG ResultLength
);


_IRQL_requires_max_(PASSIVE_LEVEL)
_When_(Length == 0, _Post_satisfies_(return < 0))
_When_(Length > 0, _Post_satisfies_(return <= 0))
_Success_(return == STATUS_SUCCESS)
_On_failure_(_When_(return == STATUS_BUFFER_OVERFLOW || return == STATUS_BUFFER_TOO_SMALL, _Post_satisfies_(*ResultLength > Length)))
NTSYSAPI
NTSTATUS
NTAPI
ZwQueryValueKey(
    _In_ HANDLE KeyHandle,
    _In_ PUNICODE_STRING ValueName,
    _In_ KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
    _Out_writes_bytes_to_opt_(Length, *ResultLength) PVOID KeyValueInformation,
    _In_ ULONG Length,
    _Out_ PULONG ResultLength
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetValueKey(
    _In_ HANDLE KeyHandle,
    _In_ PUNICODE_STRING ValueName,
    _In_opt_ ULONG TitleIndex,
    _In_ ULONG Type,
    _In_reads_bytes_opt_(DataSize) PVOID Data,
    _In_ ULONG DataSize
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSetValueKey(
    _In_ HANDLE KeyHandle,
    _In_ PUNICODE_STRING ValueName,
    _In_opt_ ULONG TitleIndex,
    _In_ ULONG Type,
    _In_reads_bytes_opt_(DataSize) PVOID Data,
    _In_ ULONG DataSize
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryMultipleValueKey(
    _In_ HANDLE KeyHandle,
    _Inout_updates_(EntryCount) PKEY_VALUE_ENTRY ValueEntries,
    _In_ ULONG EntryCount,
    _Out_writes_bytes_(*BufferLength) PVOID ValueBuffer,
    _Inout_ PULONG BufferLength,
    _Out_opt_ PULONG RequiredBufferLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwQueryMultipleValueKey(
    _In_ HANDLE KeyHandle,
    _Inout_updates_(EntryCount) PKEY_VALUE_ENTRY ValueEntries,
    _In_ ULONG EntryCount,
    _Out_writes_bytes_(*BufferLength) PVOID ValueBuffer,
    _Inout_ PULONG BufferLength,
    _Out_opt_ PULONG RequiredBufferLength
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtEnumerateKey(
    _In_ HANDLE KeyHandle,
    _In_ ULONG Index,
    _In_ KEY_INFORMATION_CLASS KeyInformationClass,
    _Out_writes_bytes_opt_(Length) PVOID KeyInformation,
    _In_ ULONG Length,
    _Out_ PULONG ResultLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_When_(Length == 0, _Post_satisfies_(return < 0))
_When_(Length > 0, _Post_satisfies_(return <= 0))
_Success_(return == STATUS_SUCCESS)
_On_failure_(_When_(return == STATUS_BUFFER_OVERFLOW || return == STATUS_BUFFER_TOO_SMALL, _Post_satisfies_(*ResultLength > Length)))
NTSYSAPI
NTSTATUS
NTAPI
ZwEnumerateKey(
    _In_ HANDLE KeyHandle,
    _In_ ULONG Index,
    _In_ KEY_INFORMATION_CLASS KeyInformationClass,
    _Out_writes_bytes_to_opt_(Length, *ResultLength) PVOID KeyInformation,
    _In_ ULONG Length,
    _Out_ PULONG ResultLength
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtEnumerateValueKey(
    _In_ HANDLE KeyHandle,
    _In_ ULONG Index,
    _In_ KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
    _Out_writes_bytes_opt_(Length) PVOID KeyValueInformation,
    _In_ ULONG Length,
    _Out_ PULONG ResultLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_When_(Length == 0, _Post_satisfies_(return < 0))
_When_(Length > 0, _Post_satisfies_(return <= 0))
_Success_(return == STATUS_SUCCESS)
_On_failure_(_When_(return == STATUS_BUFFER_OVERFLOW || return == STATUS_BUFFER_TOO_SMALL, _Post_satisfies_(*ResultLength > Length)))
NTSYSAPI
NTSTATUS
NTAPI
ZwEnumerateValueKey(
    _In_ HANDLE KeyHandle,
    _In_ ULONG Index,
    _In_ KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
    _Out_writes_bytes_to_opt_(Length, *ResultLength) PVOID KeyValueInformation,
    _In_ ULONG Length,
    _Out_ PULONG ResultLength
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtFlushKey(
    _In_ HANDLE KeyHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwFlushKey(
    _In_ HANDLE KeyHandle
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCompactKeys(
    _In_ ULONG Count,
    _In_reads_(Count) HANDLE* KeyArray
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCompactKeys(
    _In_ ULONG Count,
    _In_reads_(Count) HANDLE* KeyArray
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCompressKey(
    _In_ HANDLE KeyHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCompressKey(
    _In_ HANDLE KeyHandle
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtLoadKey(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ POBJECT_ATTRIBUTES SourceFile
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwLoadKey(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ POBJECT_ATTRIBUTES SourceFile
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtLoadKey2(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ POBJECT_ATTRIBUTES SourceFile,
    _In_ ULONG Flags
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwLoadKey2(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ POBJECT_ATTRIBUTES SourceFile,
    _In_ ULONG Flags
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtLoadKeyEx(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ POBJECT_ATTRIBUTES SourceFile,
    _In_ ULONG Flags,
    _In_opt_ HANDLE TrustClassKey, // this and below were added on Win10
    _In_opt_ HANDLE Event,
    _In_opt_ ACCESS_MASK DesiredAccess,
    _Out_opt_ PHANDLE RootHandle,
    _Reserved_ PVOID Reserved // previously PIO_STATUS_BLOCK
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwLoadKeyEx(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ POBJECT_ATTRIBUTES SourceFile,
    _In_ ULONG Flags,
    _In_opt_ HANDLE TrustClassKey, // this and below were added on Win10
    _In_opt_ HANDLE Event,
    _In_opt_ ACCESS_MASK DesiredAccess,
    _Out_opt_ PHANDLE RootHandle,
    _Reserved_ PVOID Reserved // previously PIO_STATUS_BLOCK
);

// rev by tyranid
#if (NTDDI_VERSION >= NTDDI_WIN10_VB)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtLoadKey3(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ POBJECT_ATTRIBUTES SourceFile,
    _In_ ULONG Flags,
    _In_reads_(ExtendedParameterCount) PCM_EXTENDED_PARAMETER ExtendedParameters,
    _In_ ULONG ExtendedParameterCount,
    _In_opt_ ACCESS_MASK DesiredAccess,
    _Out_opt_ PHANDLE RootHandle,
    _Reserved_ PVOID Reserved
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwLoadKey3(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ POBJECT_ATTRIBUTES SourceFile,
    _In_ ULONG Flags,
    _In_reads_(ExtendedParameterCount) PCM_EXTENDED_PARAMETER ExtendedParameters,
    _In_ ULONG ExtendedParameterCount,
    _In_opt_ ACCESS_MASK DesiredAccess,
    _Out_opt_ PHANDLE RootHandle,
    _Reserved_ PVOID Reserved
);
#endif // NTDDI_VERSION >= NTDDI_WIN10_VB

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtReplaceKey(
    _In_ POBJECT_ATTRIBUTES NewFile,
    _In_ HANDLE TargetHandle,
    _In_ POBJECT_ATTRIBUTES OldFile
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwReplaceKey(
    _In_ POBJECT_ATTRIBUTES NewFile,
    _In_ HANDLE TargetHandle,
    _In_ POBJECT_ATTRIBUTES OldFile
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSaveKey(
    _In_ HANDLE KeyHandle,
    _In_ HANDLE FileHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSaveKey(
    _In_ HANDLE KeyHandle,
    _In_ HANDLE FileHandle
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSaveKeyEx(
    _In_ HANDLE KeyHandle,
    _In_ HANDLE FileHandle,
    _In_ ULONG Format
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSaveKeyEx(
    _In_ HANDLE KeyHandle,
    _In_ HANDLE FileHandle,
    _In_ ULONG Format
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSaveMergedKeys(
    _In_ HANDLE HighPrecedenceKeyHandle,
    _In_ HANDLE LowPrecedenceKeyHandle,
    _In_ HANDLE FileHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSaveMergedKeys(
    _In_ HANDLE HighPrecedenceKeyHandle,
    _In_ HANDLE LowPrecedenceKeyHandle,
    _In_ HANDLE FileHandle
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtRestoreKey(
    _In_ HANDLE KeyHandle,
    _In_ HANDLE FileHandle,
    _In_ ULONG Flags
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwRestoreKey(
    _In_ HANDLE KeyHandle,
    _In_opt_ HANDLE FileHandle,
    _In_ ULONG Flags
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtUnloadKey(
    _In_ POBJECT_ATTRIBUTES TargetKey
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwUnloadKey(
    _In_ POBJECT_ATTRIBUTES TargetKey
);

//
// NtUnloadKey2 Flags (from winnt.h)
//
//#define REG_FORCE_UNLOAD            1
//#define REG_UNLOAD_LEGAL_FLAGS      (REG_FORCE_UNLOAD)

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtUnloadKey2(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ ULONG Flags
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwUnloadKey2(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ ULONG Flags
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtUnloadKeyEx(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_opt_ HANDLE Event
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwUnloadKeyEx(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_opt_ HANDLE Event
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtNotifyChangeKey(
    _In_ HANDLE KeyHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG CompletionFilter,
    _In_ BOOLEAN WatchTree,
    _Out_writes_bytes_opt_(BufferSize) PVOID Buffer,
    _In_ ULONG BufferSize,
    _In_ BOOLEAN Asynchronous
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwNotifyChangeKey(
    _In_ HANDLE KeyHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG CompletionFilter,
    _In_ BOOLEAN WatchTree,
    _Out_writes_bytes_opt_(BufferSize) PVOID Buffer,
    _In_ ULONG BufferSize,
    _In_ BOOLEAN Asynchronous
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtNotifyChangeMultipleKeys(
    _In_ HANDLE MasterKeyHandle,
    _In_opt_ ULONG Count,
    _In_reads_opt_(Count) OBJECT_ATTRIBUTES* SubordinateObjects,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG CompletionFilter,
    _In_ BOOLEAN WatchTree,
    _Out_writes_bytes_opt_(BufferSize) PVOID Buffer,
    _In_ ULONG BufferSize,
    _In_ BOOLEAN Asynchronous
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwNotifyChangeMultipleKeys(
    _In_ HANDLE MasterKeyHandle,
    _In_opt_ ULONG Count,
    _In_reads_opt_(Count) OBJECT_ATTRIBUTES* SubordinateObjects,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG CompletionFilter,
    _In_ BOOLEAN WatchTree,
    _Out_writes_bytes_opt_(BufferSize) PVOID Buffer,
    _In_ ULONG BufferSize,
    _In_ BOOLEAN Asynchronous
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryOpenSubKeys(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _Out_ PULONG HandleCount
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwQueryOpenSubKeys(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _Out_ PULONG HandleCount
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryOpenSubKeysEx(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ ULONG BufferLength,
    _Out_writes_bytes_opt_(BufferLength) PVOID Buffer,
    _Out_ PULONG RequiredSize
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwQueryOpenSubKeysEx(
    _In_ POBJECT_ATTRIBUTES TargetKey,
    _In_ ULONG BufferLength,
    _Out_writes_bytes_opt_(BufferLength) PVOID Buffer,
    _Out_ PULONG RequiredSize
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtInitializeRegistry(
    _In_ USHORT BootCondition
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwInitializeRegistry(
    _In_ USHORT BootCondition
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtLockRegistryKey(
    _In_ HANDLE KeyHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwLockRegistryKey(
    _In_ HANDLE KeyHandle
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtLockProductActivationKeys(
    _Inout_opt_ ULONG* pPrivateVer,
    _Out_opt_ ULONG* pSafeMode
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwLockProductActivationKeys(
    _Inout_opt_ ULONG* pPrivateVer,
    _Out_opt_ ULONG* pSafeMode
);

// private
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtFreezeRegistry(
    _In_ ULONG TimeOutInSeconds
);

// private
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwFreezeRegistry(
    _In_ ULONG TimeOutInSeconds
);

// private
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtThawRegistry(
    VOID
);

// private
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwThawRegistry(
    VOID
);

#if (NTDDI_VERSION >= NTDDI_WIN10_TH2)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateRegistryTransaction(
    _Out_ HANDLE* RegistryTransactionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjAttributes,
    _Reserved_ ULONG CreateOptions
);

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCreateRegistryTransaction(
    _Out_ PHANDLE TransactionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ ULONG CreateOptions
);

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenRegistryTransaction(
    _Out_ PHANDLE TransactionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwOpenRegistryTransaction(
    _Out_ HANDLE* RegistryTransactionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjAttributes
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCommitRegistryTransaction(
    _In_ HANDLE RegistryTransactionHandle,
    _Reserved_ ULONG Flags
);

_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
ZwCommitRegistryTransaction(
    _In_ HANDLE TransactionHandle,
    _In_ ULONG Flags
);

_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtRollbackRegistryTransaction(
    _In_ HANDLE TransactionHandle,
    _In_ ULONG Flags
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwRollbackRegistryTransaction(
    _In_ HANDLE RegistryTransactionHandle,
    _Reserved_ ULONG Flags
);
#endif // NTDDI_VERSION >= NTDDI_WIN10_TH2

VEIL_END()

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
