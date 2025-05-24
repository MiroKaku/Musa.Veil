/*
 * PROJECT:   Veil
 * FILE:      Veil.System.ObjectManager.h
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

#ifndef _KERNEL_MODE
//
// Object Manager Object Type Specific Access Rights.
//

#define OBJECT_TYPE_CREATE              (0x0001)
#define OBJECT_TYPE_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | 0x1)

//
// Object Manager Directory Specific Access Rights.
//

#define DIRECTORY_QUERY                 (0x0001)
#define DIRECTORY_TRAVERSE              (0x0002)
#define DIRECTORY_CREATE_OBJECT         (0x0004)
#define DIRECTORY_CREATE_SUBDIRECTORY   (0x0008)
#define DIRECTORY_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | 0xF)

//
// Object Manager Symbolic Link Specific Access Rights.
//

#define SYMBOLIC_LINK_QUERY             (0x0001)
#define SYMBOLIC_LINK_SET               (0x0002)
#define SYMBOLIC_LINK_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | 0x1)
#define SYMBOLIC_LINK_ALL_ACCESS_EX (STANDARD_RIGHTS_REQUIRED | SPECIFIC_RIGHTS_ALL)
#endif // !_KERNEL_MODE

#ifndef _KERNEL_MODE
typedef enum _OBJECT_INFORMATION_CLASS
{
    ObjectBasicInformation, // q: OBJECT_BASIC_INFORMATION
    ObjectNameInformation, // q: OBJECT_NAME_INFORMATION
    ObjectTypeInformation, // q: OBJECT_TYPE_INFORMATION
    ObjectTypesInformation, // q: OBJECT_TYPES_INFORMATION
    ObjectHandleFlagInformation, // qs: OBJECT_HANDLE_FLAG_INFORMATION
    ObjectSessionInformation, // s: void // change object session // (requires SeTcbPrivilege)
    ObjectSessionObjectInformation, // s: void // change object session // (requires SeTcbPrivilege)
    MaxObjectInfoClass
} OBJECT_INFORMATION_CLASS;
#else
#define ObjectBasicInformation          ((_OBJECT_INFORMATION_CLASS)0)
#define ObjectNameInformation           ((_OBJECT_INFORMATION_CLASS)1)
#define ObjectTypeInformation           ((_OBJECT_INFORMATION_CLASS)2)
#define ObjectTypesInformation          ((_OBJECT_INFORMATION_CLASS)3)
#define ObjectHandleFlagInformation     ((_OBJECT_INFORMATION_CLASS)4)
#define ObjectSessionInformation        ((_OBJECT_INFORMATION_CLASS)5)
#define ObjectSessionObjectInformation  ((_OBJECT_INFORMATION_CLASS)6)
#endif // !_KERNEL_MODE

/**
 * The OBJECT_BASIC_INFORMATION structure contains basic information about an object.
 */
typedef struct _OBJECT_BASIC_INFORMATION
{
    ULONG Attributes;               // The attributes of the object include whether the object is permanent, can be inherited, and other characteristics.
    ACCESS_MASK GrantedAccess;      // Specifies a mask that represents the granted access when the object was created.
    ULONG HandleCount;              // The number of handles that are currently open for the object.
    ULONG PointerCount;             // The number of references to the object from both handles and other references, such as those from the system.
    ULONG PagedPoolCharge;          // The amount of paged pool memory that the object is using.
    ULONG NonPagedPoolCharge;       // The amount of non-paged pool memory that the object is using.
    ULONG Reserved[3];              // Reserved for future use.
    ULONG NameInfoSize;             // The size of the name information for the object.
    ULONG TypeInfoSize;             // The size of the type information for the object.
    ULONG SecurityDescriptorSize;   // The size of the security descriptor for the object.
    LARGE_INTEGER CreationTime;     // The time when a symbolic link was created. Not supported for other types of objects.
} OBJECT_BASIC_INFORMATION, * POBJECT_BASIC_INFORMATION;

#ifndef _KERNEL_MODE
/**
 * The OBJECT_NAME_INFORMATION structure contains the name, if there is one, of a given object.
 */
typedef struct _OBJECT_NAME_INFORMATION
{
    UNICODE_STRING Name; // The object name (when present) includes a NULL-terminator and all path separators "\" in the name.
} OBJECT_NAME_INFORMATION, * POBJECT_NAME_INFORMATION;
#endif // !_KERNEL_MODE

/**
 * The OBJECT_NAME_INFORMATION structure contains various statistics and properties about an object type.
 */
typedef struct _OBJECT_TYPE_INFORMATION
{
    UNICODE_STRING TypeName;
    ULONG TotalNumberOfObjects;
    ULONG TotalNumberOfHandles;
    ULONG TotalPagedPoolUsage;
    ULONG TotalNonPagedPoolUsage;
    ULONG TotalNamePoolUsage;
    ULONG TotalHandleTableUsage;
    ULONG HighWaterNumberOfObjects;
    ULONG HighWaterNumberOfHandles;
    ULONG HighWaterPagedPoolUsage;
    ULONG HighWaterNonPagedPoolUsage;
    ULONG HighWaterNamePoolUsage;
    ULONG HighWaterHandleTableUsage;
    ULONG InvalidAttributes;
    GENERIC_MAPPING GenericMapping;
    ULONG ValidAccessMask;
    BOOLEAN SecurityRequired;
    BOOLEAN MaintainHandleCount;
    UCHAR TypeIndex; // since WINBLUE
    CHAR ReservedByte;
    ULONG PoolType;
    ULONG DefaultPagedPoolCharge;
    ULONG DefaultNonPagedPoolCharge;
} OBJECT_TYPE_INFORMATION, * POBJECT_TYPE_INFORMATION;

typedef struct _OBJECT_TYPES_INFORMATION
{
    ULONG NumberOfTypes;
} OBJECT_TYPES_INFORMATION, * POBJECT_TYPES_INFORMATION;

typedef struct _OBJECT_HANDLE_FLAG_INFORMATION
{
    BOOLEAN Inherit;
    BOOLEAN ProtectFromClose;
} OBJECT_HANDLE_FLAG_INFORMATION, * POBJECT_HANDLE_FLAG_INFORMATION;

//
// Objects, handles
//

/**
 * The NtQueryObject routine retrieves various kinds of object information.
 *
 * \param Handle The handle of the object for which information is being queried.
 * \param ObjectInformationClass The information class indicating the kind of object information to be retrieved.
 * \param ObjectInformation An optional pointer to a buffer where the requested information is to be returned.
 * \param ObjectInformationLength The size of the buffer pointed to by the ObjectInformation parameter, in bytes.
 * \param ReturnLength An optional pointer to a location where the function writes the actual size of the information requested.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winternl/nf-winternl-ntqueryobject
 */
_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryObject(
    _In_opt_ HANDLE Handle,
    _In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
    _Out_writes_bytes_opt_(ObjectInformationLength) PVOID ObjectInformation,
    _In_ ULONG ObjectInformationLength,
    _Out_opt_ PULONG ReturnLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwQueryObject(
    _In_opt_ HANDLE Handle,
    _In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
    _Out_writes_bytes_opt_(ObjectInformationLength) PVOID ObjectInformation,
    _In_ ULONG ObjectInformationLength,
    _Out_opt_ PULONG ReturnLength
);

/**
 * The NtSetInformationObject routine changes various kinds of information about a object.
 *
 * \param Handle The handle of the object for which information is being changed.
 * \param ObjectInformationClass The type of information, supplied in the buffer pointed to by ObjectInformation, to set for the object.
 * \param ObjectInformation Pointer to a buffer that contains the information to set for the object.
 * \param ObjectInformationLength The size of the buffer pointed to by the ObjectInformation parameter, in bytes.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationObject(
    _In_ HANDLE Handle,
    _In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
    _In_reads_bytes_(ObjectInformationLength) PVOID ObjectInformation,
    _In_ ULONG ObjectInformationLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSetInformationObject(
    _In_ HANDLE Handle,
    _In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
    _In_reads_bytes_(ObjectInformationLength) PVOID ObjectInformation,
    _In_ ULONG ObjectInformationLength
);

#define DUPLICATE_CLOSE_SOURCE    0x00000001    // Close the source handle.
#define DUPLICATE_SAME_ACCESS     0x00000002    // Instead of using the DesiredAccess parameter, copy the access rights from the source handle to the target handle.
#define DUPLICATE_SAME_ATTRIBUTES 0x00000004    // Instead of using the HandleAttributes parameter, copy the attributes from the source handle to the target handle.

/**
 * The NtDuplicateObject routine creates a handle that is a duplicate of the specified source handle.
 *
 * \param SourceProcessHandle A handle to the source process for the handle being duplicated.
 * \param SourceHandle The handle to duplicate.
 * \param TargetProcessHandle A handle to the target process that is to receive the new handle. This parameter is optional and can be specified as NULL if the DUPLICATE_CLOSE_SOURCE flag is set in Options.
 * \param TargetHandle A pointer to a HANDLE variable into which the routine writes the new duplicated handle. The duplicated handle is valid in the specified target process. This parameter is optional and can be specified as NULL if no duplicate handle is to be created.
 * \param DesiredAccess An ACCESS_MASK value that specifies the desired access for the new handle.
 * \param HandleAttributes A ULONG that specifies the desired attributes for the new handle.
 * \param Options A set of flags to control the behavior of the duplication operation.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-zwduplicateobject
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtDuplicateObject(
    _In_ HANDLE SourceProcessHandle,
    _In_ HANDLE SourceHandle,
    _In_opt_ HANDLE TargetProcessHandle,
    _Out_opt_ PHANDLE TargetHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Options
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwDuplicateObject(
    _In_ HANDLE SourceProcessHandle,
    _In_ HANDLE SourceHandle,
    _In_opt_ HANDLE TargetProcessHandle,
    _Out_opt_ PHANDLE TargetHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Options
);

/**
 * The NtMakeTemporaryObject routine changes the attributes of an object to make it temporary.
 *
 * \param Handle Handle to an object of any type.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-zwmaketemporaryobject
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtMakeTemporaryObject(
    _In_ HANDLE Handle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwMakeTemporaryObject(
    _In_ HANDLE Handle
);

/**
 * The NtMakePermanentObject routine changes the attributes of an object to make it permanent.
 *
 * \param Handle Handle to an object of any type.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-zwmaketemporaryobject
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtMakePermanentObject(
    _In_ HANDLE Handle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwMakePermanentObject(
    _In_ HANDLE Handle
);

/**
 * The NtSignalAndWaitForSingleObject routine signals one object and waits on another object as a single operation.
 *
 * \param SignalHandle A handle to the object to be signaled.
 * \param WaitHandle A handle to the object to wait on. The SYNCHRONIZE access right is required.
 * \param Alertable If this parameter is TRUE, the function returns when the system queues an I/O completion routine or APC function, and the thread calls the function.
 * \param Timeout The time-out interval. The function returns if the interval elapses, even if the object's state is nonsignaled and no completion or APC objects are queued.
 * If zero, the function tests the object's state, checks for queued completion routines or APCs, and returns immediately.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-signalobjectandwait
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSignalAndWaitForSingleObject(
    _In_ HANDLE SignalHandle,
    _In_ HANDLE WaitHandle,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSignalAndWaitForSingleObject(
    _In_ HANDLE SignalHandle,
    _In_ HANDLE WaitHandle,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
);

/**
 * The NtWaitForSingleObject routine waits until the specified object is in the signaled state or the time-out interval elapses.
 *
 * \param Handle The handle to the wait object.
 * \param Alertable The function returns when either the time-out period has elapsed or when the APC function is called.
 * \param Timeout A pointer to an absolute or relative time over which the wait is to occur. Can be null. If a timeout is specified,
 * and the object has not attained a state of signaled when the timeout expires, then the wait is automatically satisfied.
 * If an explicit timeout value of zero is specified, then no wait occurs if the wait cannot be satisfied immediately.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winternl/nf-winternl-ntwaitforsingleobject
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtWaitForSingleObject(
    _In_ HANDLE Handle,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
);

_When_(Timeout == NULL, _IRQL_requires_max_(APC_LEVEL))
_When_(Timeout->QuadPart != 0, _IRQL_requires_max_(APC_LEVEL))
_When_(Timeout->QuadPart == 0, _IRQL_requires_max_(DISPATCH_LEVEL))
NTSYSAPI
NTSTATUS
NTAPI
ZwWaitForSingleObject(
    _In_ HANDLE Handle,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
);

/**
 * The NtWaitForMultipleObjects routine waits until one or all of the specified objects are in the signaled state, an I/O completion routine or asynchronous procedure call (APC) is queued to the thread, or the time-out interval elapses.
 *
 * \param Count The number of object handles to wait for in the array pointed to by lpHandles. The maximum number of object handles is MAXIMUM_WAIT_OBJECTS. This parameter cannot be zero.
 * \param Handles An array of object handles. The array can contain handles of objects of different types. It may not contain multiple copies of the same handle.
 * \param WaitType If this parameter is WaitAll, the function returns when the state of all objects in the Handles array is set to signaled.
 * \param Alertable f this parameter is TRUE and the thread is in the waiting state, the function returns when the system queues an I/O completion routine or APC, and the thread runs the routine or function.
 * \param Timeout A pointer to an absolute or relative time over which the wait is to occur. Can be null. If a timeout is specified,
 * and the object has not attained a state of signaled when the timeout expires, then the wait is automatically satisfied.
 * If an explicit timeout value of zero is specified, then no wait occurs if the wait cannot be satisfied immediately.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-waitformultipleobjectsex
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtWaitForMultipleObjects(
    _In_ ULONG Count,
    _In_reads_(Count) HANDLE* Handles,
    _In_ WAIT_TYPE WaitType,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwWaitForMultipleObjects(
    _In_ ULONG Count,
    _In_reads_(Count) HANDLE* Handles,
    _In_ WAIT_TYPE WaitType,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
);

#if (NTDDI_VERSION >= NTDDI_WS03)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtWaitForMultipleObjects32(
    _In_ ULONG Count,
    _In_reads_(Count) LONG* Handles,
    _In_ WAIT_TYPE WaitType,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwWaitForMultipleObjects32(
    _In_ ULONG Count,
    _In_reads_(Count) LONG* Handles,
    _In_ WAIT_TYPE WaitType,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout
);
#endif

/**
 * The NtSetSecurityObject routine sets an object's security state.
 *
 * \param Handle Handle for the object whose security state is to be set.
 * \param SecurityInformation A SECURITY_INFORMATION value specifying the information to be set.
 * \param SecurityDescriptor Pointer to the security descriptor to be set for the object.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-zwsetsecurityobject
 */
_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetSecurityObject(
    _In_ HANDLE Handle,
    _In_ SECURITY_INFORMATION SecurityInformation,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSetSecurityObject(
    _In_ HANDLE Handle,
    _In_ SECURITY_INFORMATION SecurityInformation,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor
);

/**
 * The NtQuerySecurityObject routine retrieves a copy of an object's security descriptor.
 *
 * \param Handle Handle for the object whose security descriptor is to be queried.
 * \param SecurityInformation A SECURITY_INFORMATION value specifying the information to be queried.
 * \param SecurityDescriptor Caller-allocated buffer that NtQuerySecurityObject fills with a copy of the specified security descriptor.
 * \param Length Size, in bytes, of the buffer pointed to by SecurityDescriptor.
 * \param LengthNeeded Pointer to a caller-allocated variable that receives the number of bytes required to store the copied security descriptor.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntquerysecurityobject
 */
_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQuerySecurityObject(
    _In_ HANDLE Handle,
    _In_ SECURITY_INFORMATION SecurityInformation,
    _Out_writes_bytes_opt_(Length) PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ ULONG Length,
    _Out_ PULONG LengthNeeded
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwQuerySecurityObject(
    _In_ HANDLE Handle,
    _In_ SECURITY_INFORMATION SecurityInformation,
    _Out_writes_bytes_to_(Length, *LengthNeeded) PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ ULONG Length,
    _Out_ PULONG LengthNeeded
);

/**
 * The NtClose routine closes the specified handle.
 *
 * \param Handle The handle being closed.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-zwclose
 */
_IRQL_requires_max_(PASSIVE_LEVEL)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtClose(
    _In_ _Post_ptr_invalid_ HANDLE Handle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwClose(
    _In_ HANDLE Handle
);

#if (NTDDI_VERSION >= NTDDI_WIN10)
/**
 * Compares two object handles to determine if they refer to the same underlying kernel object.
 *
 * \param FirstObjectHandle The first object handle to compare.
 * \param SecondObjectHandle The second object handle to compare.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-compareobjecthandles
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCompareObjects(
    _In_ HANDLE FirstObjectHandle,
    _In_ HANDLE SecondObjectHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCompareObjects(
    _In_ HANDLE FirstObjectHandle,
    _In_ HANDLE SecondObjectHandle
);
#endif // NTDDI_VERSION >= NTDDI_WIN10

//
// Directory objects
//

/**
 * The NtCreateDirectoryObject routine creates or opens an object-directory object.
 *
 * \param DirectoryHandle Pointer to a HANDLE variable that receives a handle to the object directory.
 * \param DesiredAccess An ACCESS_MASK that specifies the requested access to the directory object.
 * \param ObjectAttributes The attributes for the directory object.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-zwcreatedirectoryobject
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateDirectoryObject(
    _Out_ PHANDLE DirectoryHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateDirectoryObject(
    _Out_ PHANDLE DirectoryHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
);

#if (NTDDI_VERSION >= NTDDI_WIN8)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateDirectoryObjectEx(
    _Out_ PHANDLE DirectoryHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ShadowDirectoryHandle,
    _In_ ULONG Flags
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateDirectoryObjectEx(
    _Out_ PHANDLE DirectoryHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ HANDLE ShadowDirectoryHandle,
    _In_ ULONG Flags
);
#endif

/**
 * Opens an existing directory object.
 *
 * \param DirectoryHandle A handle to the newly opened directory object.
 * \param DesiredAccess An ACCESS_MASK that specifies the requested access to the directory object.
 * \param ObjectAttributes The attributes for the directory object.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/devnotes/ntopendirectoryobject
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenDirectoryObject(
    _Out_ PHANDLE DirectoryHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwOpenDirectoryObject(
    _Out_ PHANDLE DirectoryHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
);

/**
 * The OBJECT_DIRECTORY_INFORMATION structure contains information about the directory object.
 */
typedef struct _OBJECT_DIRECTORY_INFORMATION
{
    UNICODE_STRING Name;
    UNICODE_STRING TypeName;
} OBJECT_DIRECTORY_INFORMATION, * POBJECT_DIRECTORY_INFORMATION;

/**
 * Retrieves information about the specified directory object.
 *
 * \param DirectoryHandle A handle to the directory object. This handle must have been opened with the appropriate access rights.
 * \param Buffer A pointer to a buffer that receives the directory information.
 * \param Length The size, in bytes, of the buffer pointed to by the Buffer parameter.
 * \param ReturnSingleEntry A BOOLEAN value that specifies whether to return a single entry or multiple entries.
 * \param RestartScan A BOOLEAN value that specifies whether to restart the scan from the beginning of the directory.
 * \param Context A pointer to a variable that maintains the context of the directory enumeration.
 * \param ReturnLength An optional pointer to a variable that receives the number of bytes returned in the buffer.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/devnotes/ntquerydirectoryobject
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryDirectoryObject(
    _In_ HANDLE DirectoryHandle,
    _Out_writes_bytes_opt_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_ BOOLEAN ReturnSingleEntry,
    _In_ BOOLEAN RestartScan,
    _Inout_ PULONG Context,
    _Out_opt_ PULONG ReturnLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwQueryDirectoryObject(
    _In_ HANDLE DirectoryHandle,
    _Out_writes_bytes_opt_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_ BOOLEAN ReturnSingleEntry,
    _In_ BOOLEAN RestartScan,
    _Inout_ PULONG Context,
    _Out_opt_ PULONG ReturnLength
);

//
// Private namespaces
//

// private
typedef enum _BOUNDARY_ENTRY_TYPE
{
    OBNS_Invalid,
    OBNS_Name,
    OBNS_SID,
    OBNS_IL
} BOUNDARY_ENTRY_TYPE;

// private
typedef struct _OBJECT_BOUNDARY_ENTRY
{
    BOUNDARY_ENTRY_TYPE EntryType;
    ULONG EntrySize;

    //union
    //{
    //    WCHAR Name[1];
    //    PSID Sid;
    //    PSID IntegrityLabel;
    //} DUMMYUNIONNAME;
} OBJECT_BOUNDARY_ENTRY, * POBJECT_BOUNDARY_ENTRY;

// rev
#define OBJECT_BOUNDARY_DESCRIPTOR_VERSION 1

// private
typedef struct _OBJECT_BOUNDARY_DESCRIPTOR
{
    ULONG Version;
    ULONG Items;
    ULONG TotalSize;
    union
    {
        ULONG Flags;
        struct
        {
            ULONG AddAppContainerSid : 1;
            ULONG Reserved : 31;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;
    //OBJECT_BOUNDARY_ENTRY Entries[1];
} OBJECT_BOUNDARY_DESCRIPTOR, * POBJECT_BOUNDARY_DESCRIPTOR;

/**
 * Creates a private namespace.
 *
 * \param NamespaceHandle A handle to the newly created private namespace.
 * \param DesiredAccess An ACCESS_MASK that specifies the requested access to the private namespace.
 * \param ObjectAttributes The attributes for the private namespace.
 * \param BoundaryDescriptor A descriptor that defines how the namespace is to be isolated. The RtlCreateBoundaryDescriptor function creates a boundary descriptor.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-createprivatenamespacea
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreatePrivateNamespace(
    _Out_ PHANDLE NamespaceHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ POBJECT_BOUNDARY_DESCRIPTOR BoundaryDescriptor
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreatePrivateNamespace(
    _Out_ PHANDLE NamespaceHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ POBJECT_BOUNDARY_DESCRIPTOR BoundaryDescriptor
);

/**
 * Opens a private namespace.
 *
 * \param NamespaceHandle A handle to the newly opened private namespace.
 * \param DesiredAccess An ACCESS_MASK that specifies the requested access to the private namespace.
 * \param ObjectAttributes The attributes for the private namespace.
 * \param BoundaryDescriptor A descriptor that defines how the namespace is to be isolated. The RtlCreateBoundaryDescriptor function creates a boundary descriptor.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-openprivatenamespacea
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenPrivateNamespace(
    _Out_ PHANDLE NamespaceHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ POBJECT_BOUNDARY_DESCRIPTOR BoundaryDescriptor
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwOpenPrivateNamespace(
    _Out_ PHANDLE NamespaceHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ POBJECT_BOUNDARY_DESCRIPTOR BoundaryDescriptor
);

/**
 * Deletes an open namespace handle.
 *
 * \param NamespaceHandle A handle to the private namespace.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/namespaceapi/nf-namespaceapi-closeprivatenamespace
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtDeletePrivateNamespace(
    _In_ HANDLE NamespaceHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwDeletePrivateNamespace(
    _In_ HANDLE NamespaceHandle
);

//
// Symbolic links
//

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateSymbolicLinkObject(
    _Out_ PHANDLE LinkHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ PUNICODE_STRING LinkTarget
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateSymbolicLinkObject(
    _Out_ PHANDLE LinkHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ PUNICODE_STRING LinkTarget
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenSymbolicLinkObject(
    _Out_ PHANDLE LinkHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwOpenSymbolicLinkObject(
    _Out_ PHANDLE LinkHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQuerySymbolicLinkObject(
    _In_ HANDLE LinkHandle,
    _Inout_ PUNICODE_STRING LinkTarget,
    _Out_opt_ PULONG ReturnedLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwQuerySymbolicLinkObject(
    _In_ HANDLE LinkHandle,
    _Inout_ PUNICODE_STRING LinkTarget,
    _Out_opt_ PULONG ReturnedLength
);

#if (NTDDI_VERSION >= NTDDI_WIN10)
typedef enum _SYMBOLIC_LINK_INFORMATION_CLASS
{
    SymbolicLinkGlobalInformation = 1, // s: ULONG
    SymbolicLinkAccessMask, // s: ACCESS_MASK
    MaxnSymbolicLinkInfoClass
} SYMBOLIC_LINK_INFORMATION_CLASS;

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationSymbolicLink(
    _In_ HANDLE LinkHandle,
    _In_ SYMBOLIC_LINK_INFORMATION_CLASS SymbolicLinkInformationClass,
    _In_reads_bytes_(SymbolicLinkInformationLength) PVOID SymbolicLinkInformation,
    _In_ ULONG SymbolicLinkInformationLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSetInformationSymbolicLink(
    _In_ HANDLE LinkHandle,
    _In_ SYMBOLIC_LINK_INFORMATION_CLASS SymbolicLinkInformationClass,
    _In_reads_bytes_(SymbolicLinkInformationLength) PVOID SymbolicLinkInformation,
    _In_ ULONG SymbolicLinkInformationLength
);
#endif // (NTDDI_VERSION >= NTDDI_WIN10)

//
// Only Kernel
//

#ifdef _KERNEL_MODE

// Object Type

extern POBJECT_TYPE* CmKeyObjectType;
extern POBJECT_TYPE* LpcPortObjectType;
extern POBJECT_TYPE* SeTokenObjectType;
extern POBJECT_TYPE* MmSectionObjectType;

extern POBJECT_TYPE* ExActivationObjectType;
extern POBJECT_TYPE* ExCompositionObjectType;
extern POBJECT_TYPE* ExCoreMessagingObjectType;
extern POBJECT_TYPE* ExDesktopObjectType;
extern POBJECT_TYPE* ExEventObjectType;
extern POBJECT_TYPE* ExRawInputManagerObjectType;
extern POBJECT_TYPE* ExSemaphoreObjectType;
extern POBJECT_TYPE* ExTimerObjectType;
extern POBJECT_TYPE* ExWindowStationObjectType;

extern POBJECT_TYPE* IoAdapterObjectType;
extern POBJECT_TYPE* IoCompletionObjectType;
extern POBJECT_TYPE* IoDeviceHandlerObjectType;
extern POBJECT_TYPE* IoDeviceObjectType;
extern POBJECT_TYPE* IoDriverObjectType;
extern POBJECT_TYPE* IoFileObjectType;

extern POBJECT_TYPE* TmEnlistmentObjectType;
extern POBJECT_TYPE* TmResourceManagerObjectType;
extern POBJECT_TYPE* TmTransactionManagerObjectType;
extern POBJECT_TYPE* TmTransactionObjectType;

// Function

typedef struct _OBJECT_DUMP_CONTROL {
    PVOID Stream;
    ULONG Detail;
} OB_DUMP_CONTROL, * POB_DUMP_CONTROL;

typedef VOID(NTAPI * OB_DUMP_METHOD)(
    _In_ PVOID Object,
    _In_opt_ POB_DUMP_CONTROL Control
    );

typedef enum _OB_OPEN_REASON
{
    ObCreateHandle,
    ObOpenHandle,
    ObDuplicateHandle,
    ObInheritHandle,
    ObMaxOpenReason
} OB_OPEN_REASON;

typedef NTSTATUS(NTAPI * OB_OPEN_METHOD)(
    _In_ OB_OPEN_REASON OpenReason,
    _In_ KPROCESSOR_MODE PreviousMode,
    _In_opt_ PEPROCESS Process,
    _In_ PVOID Object,
    _In_ ACCESS_MASK GrantedAccess,
    _In_ ULONG HandleCount
    );

typedef BOOLEAN(NTAPI * OB_OKAYTOCLOSE_METHOD)(
    _In_opt_ PEPROCESS Process,
    _In_ PVOID Object,
    _In_ HANDLE Handle,
    _In_ KPROCESSOR_MODE PreviousMode
    );

typedef VOID(NTAPI *OB_CLOSE_METHOD)(
    _In_opt_ PEPROCESS Process,
    _In_ PVOID Object,
    _In_ ULONG_PTR ProcessHandleCount,
    _In_ ULONG_PTR SystemHandleCount
    );

typedef VOID(NTAPI*OB_DELETE_METHOD)(
    _In_  PVOID Object
    );

typedef NTSTATUS(NTAPI*OB_PARSE_METHOD)(
    _In_ PVOID ParseObject,
    _In_ PVOID ObjectType,
    _Inout_ PACCESS_STATE AccessState,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_ ULONG Attributes,
    _Inout_ PUNICODE_STRING CompleteName,
    _Inout_ PUNICODE_STRING RemainingName,
    _Inout_opt_ PVOID Context,
    _In_opt_ PSECURITY_QUALITY_OF_SERVICE SecurityQos,
    _Out_ PVOID* Object
    );

typedef struct _OB_EXTENDED_PARSE_PARAMETERS
{
    UINT16  Length;
    ULONG32 RestrictedAccessMask;
    struct _EJOB* Silo;
} OB_EXTENDED_PARSE_PARAMETERS, * POB_EXTENDED_PARSE_PARAMETERS;

typedef NTSTATUS(NTAPI* OB_PARSE_EX_METHOD)(
    _In_ PVOID ParseObject,
    _In_ PVOID ObjectType,
    _Inout_ PACCESS_STATE AccessState,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_ ULONG Attributes,
    _Inout_ PUNICODE_STRING CompleteName,
    _Inout_ PUNICODE_STRING RemainingName,
    _Inout_opt_ PVOID Context,
    _In_opt_ PSECURITY_QUALITY_OF_SERVICE SecurityQos,
    POB_EXTENDED_PARSE_PARAMETERS ExtendedParameters,
    _Out_ PVOID* Object
    );

typedef NTSTATUS(NTAPI*OB_SECURITY_METHOD)(
    _In_ PVOID Object,
    _In_ SECURITY_OPERATION_CODE OperationCode,
    _In_ PSECURITY_INFORMATION SecurityInformation,
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Inout_ PULONG CapturedLength,
    _Inout_ PSECURITY_DESCRIPTOR* ObjectsSecurityDescriptor,
    _In_ POOL_TYPE PoolType,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ KPROCESSOR_MODE AccessMode
    );

typedef NTSTATUS(NTAPI*OB_QUERYNAME_METHOD)(
    _In_ PVOID Object,
    _In_ BOOLEAN HasObjectName,
    _Out_ POBJECT_NAME_INFORMATION ObjectNameInfo,
    _In_ ULONG Length,
    _Out_ PULONG ReturnLength,
    _In_ KPROCESSOR_MODE Mode
    );

typedef struct _OBJECT_TYPE_INITIALIZER
{
    UINT16 Length;
    union
    {
        UINT16 ObjectTypeFlags;
        struct
        {
            struct
            {
                UINT8 CaseInsensitive : 1;
                UINT8 UnnamedObjectsOnly : 1;
                UINT8 UseDefaultObject : 1;
                UINT8 SecurityRequired : 1;
                UINT8 MaintainHandleCount : 1;
                UINT8 MaintainTypeList : 1;
                UINT8 SupportsObjectCallbacks : 1;
                UINT8 CacheAligned : 1;
            };
            struct
            {
                UINT8 UseExtendedParameters : 1;
                UINT8 Reserved : 7;
            };
        };
    };
    ULONG32         ObjectTypeCode;
    ULONG32         InvalidAttributes;
    GENERIC_MAPPING GenericMapping;
    ULONG32         ValidAccessMask;
    ULONG32         RetainAccess;
    POOL_TYPE       PoolType;
    ULONG32         DefaultPagedPoolCharge;
    ULONG32         DefaultNonPagedPoolCharge;
    OB_DUMP_METHOD    DumpProcedure;
    OB_OPEN_METHOD    OpenProcedure;
    OB_CLOSE_METHOD   CloseProcedure;
    OB_DELETE_METHOD  DeleteProcedure;
    union
    {
        OB_PARSE_METHOD    ParseProcedure;
        OB_PARSE_EX_METHOD ParseProcedureEx;
    };
    OB_SECURITY_METHOD    SecurityProcedure;
    OB_QUERYNAME_METHOD   QueryNameProcedure;
    OB_OKAYTOCLOSE_METHOD OkayToCloseProcedure;
    ULONG32 WaitObjectFlagMask;
    UINT16  WaitObjectFlagOffset;
    UINT16  WaitObjectPointerOffset;
} OBJECT_TYPE_INITIALIZER, * POBJECT_TYPE_INITIALIZER;

#if (NTDDI_VERSION >= NTDDI_WIN8)
#define SIZEOF_OBJECT_TYPE_INITIALIZER  (sizeof OBJECT_TYPE_INITIALIZER)
#else
#define SIZEOF_OBJECT_TYPE_INITIALIZER  (FIELD_OFFSET(OBJECT_TYPE_INITIALIZER, WaitObjectFlagMask))
#endif

NTKERNELAPI
NTSTATUS
NTAPI
ObCreateObjectType(
    _In_ PUNICODE_STRING            TypeName,
    _In_ POBJECT_TYPE_INITIALIZER   ObjectTypeInitializer,
    _In_opt_ PSECURITY_DESCRIPTOR   SecurityDescriptor,
    _Out_ POBJECT_TYPE*             ObjectType
);

NTKERNELAPI
NTSTATUS
NTAPI
ObCreateObject(
    _In_ KPROCESSOR_MODE ProbeMode,
    _In_ POBJECT_TYPE    ObjectType,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ KPROCESSOR_MODE OwnershipMode,
    _Inout_opt_  PVOID   ParseContext,
    _In_ ULONG           ObjectBodySize,
    _In_ ULONG           PagedPoolCharge,
    _In_ ULONG           NonPagedPoolCharge,
    _Out_ PVOID*         Object
);

NTKERNELAPI
NTSTATUS
ObInsertObject(
    _In_ PVOID Object,
    _Inout_opt_ PACCESS_STATE PassedAccessState,
    _In_opt_ ACCESS_MASK DesiredAccess,
    _In_ ULONG ObjectPointerBias,
    _Out_opt_ PVOID* NewObject,
    _Out_opt_ PHANDLE Handle
);

NTKERNELAPI
NTSTATUS
NTAPI
ObOpenObjectByName(
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ POBJECT_TYPE ObjectType,
    _In_ KPROCESSOR_MODE AccessMode,
    _Inout_opt_ PACCESS_STATE AccessState,
    _In_opt_ ACCESS_MASK DesiredAccess,
    _Inout_opt_ PVOID ParseContext,
    _Out_ PHANDLE Handle
);

NTKERNELAPI
NTSTATUS
ObOpenObjectByPointer(
    _In_ PVOID Object,
    _In_ ULONG HandleAttributes,
    _In_opt_ PACCESS_STATE PassedAccessState,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_TYPE ObjectType,
    _In_ KPROCESSOR_MODE AccessMode,
    _Out_ PHANDLE Handle
);

NTKERNELAPI
NTSTATUS
ObOpenObjectByPointerWithTag(
    _In_ PVOID Object,
    _In_ ULONG HandleAttributes,
    _In_opt_ PACCESS_STATE PassedAccessState,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_TYPE ObjectType,
    _In_ KPROCESSOR_MODE AccessMode,
    _In_ ULONG Tag,
    _Out_ PHANDLE Handle
);

NTKERNELAPI
VOID
ObMakeTemporaryObject(
    _In_ PVOID Object
);

NTSYSAPI
BOOLEAN
NTAPI
ObFindHandleForObject(
    _In_ PEPROCESS Process,
    _In_ PVOID Object,
    _In_opt_ POBJECT_TYPE ObjectType,
    _In_opt_ POBJECT_HANDLE_INFORMATION MatchCriteria,
    _Out_ PHANDLE Handle
);

#if (NTDDI_VERSION >= NTDDI_WIN8)

NTKERNELAPI
BOOLEAN
FASTCALL
ObReferenceObjectSafe(
    _In_ PVOID Object
);

NTKERNELAPI
BOOLEAN
FASTCALL
ObReferenceObjectSafeWithTag(
    _In_ PVOID Object,
    _In_ ULONG Tag
);

#endif // NTDDI_VERSION >= NTDDI_WIN8

NTKERNELAPI
NTSTATUS
NTAPI
ObReferenceObjectByName(
    _In_ PUNICODE_STRING ObjectName,
    _In_ ULONG Attributes,
    _In_opt_ PACCESS_STATE AccessState,
    _In_opt_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_TYPE ObjectType,
    _In_ KPROCESSOR_MODE AccessMode,
    _Inout_opt_ PVOID ParseContext,
    _Out_ PVOID* Object
);

NTKERNELAPI
NTSTATUS
ObQueryNameString(
    _In_ PVOID Object,
    _Out_writes_bytes_opt_(Length) POBJECT_NAME_INFORMATION ObjectNameInfo,
    _In_ ULONG Length,
    _Out_ PULONG ReturnLength
);

FORCEINLINE HANDLE ObMakeKernelHandle(HANDLE Handle)
{
#ifdef _X86_
#define KERNEL_HANDLE_BIT (0x80000000)
#else
#define KERNEL_HANDLE_BIT (0xffffffff80000000)
#endif

    return ((HANDLE)(__int3264)((ULONG_PTR)(Handle) | KERNEL_HANDLE_BIT));
}

NTKERNELAPI
BOOLEAN
ObIsKernelHandle(
    _In_ HANDLE Handle
);

// begin: Object Header
#include <pshpack8.h>

typedef struct _OBJECT_HEADER_CREATOR_INFO
{
    LIST_ENTRY  TypeList;
    HANDLE      CreatorUniqueProcess;
    USHORT      CreatorBackTraceIndex;
    USHORT      Reserved1;
#ifdef _WIN64
    ULONG       Reserved2;
#endif
} OBJECT_HEADER_CREATOR_INFO, * POBJECT_HEADER_CREATOR_INFO;
STATIC_ASSERT(sizeof(OBJECT_HEADER_CREATOR_INFO) == (sizeof(void*) == sizeof(__int32) ? 0x0010 : 0x0020));

typedef struct _OBJECT_HEADER_NAME_INFO
{
    struct _OBJECT_DIRECTORY* Directory;
    UNICODE_STRING     Name;
    LONG               ReferenceCount;
#ifdef _WIN64
    ULONG              Reserved;
#endif
} OBJECT_HEADER_NAME_INFO, * POBJECT_HEADER_NAME_INFO;
STATIC_ASSERT(sizeof(OBJECT_HEADER_NAME_INFO) == (sizeof(void*) == sizeof(__int32) ? 0x0010 : 0x0020));

typedef struct _OBJECT_HANDLE_COUNT_ENTRY
{
    PEPROCESS Process;
    struct
    {
        ULONG HandleCount : 24;
        ULONG LockCount : 8;
    };
} OBJECT_HANDLE_COUNT_ENTRY, * POBJECT_HANDLE_COUNT_ENTRY;
STATIC_ASSERT(sizeof(OBJECT_HANDLE_COUNT_ENTRY) == (sizeof(void*) == sizeof(__int32) ? 0x0008 : 0x0010));

typedef struct _OBJECT_HANDLE_COUNT_DATABASE
{
    ULONG CountEntries;
    OBJECT_HANDLE_COUNT_ENTRY HandleCountEntries[1];

} OBJECT_HANDLE_COUNT_DATABASE, * POBJECT_HANDLE_COUNT_DATABASE;
STATIC_ASSERT(sizeof(OBJECT_HANDLE_COUNT_DATABASE) == (sizeof(void*) == sizeof(__int32) ? 0x000C : 0x0018));

typedef struct _OBJECT_HEADER_HANDLE_INFO
{
    union
    {
        POBJECT_HANDLE_COUNT_DATABASE  HandleCountDataBase;
        OBJECT_HANDLE_COUNT_ENTRY      SingleEntry;
    };
} OBJECT_HEADER_HANDLE_INFO, * POBJECT_HEADER_HANDLE_INFO;
STATIC_ASSERT(sizeof(OBJECT_HEADER_HANDLE_INFO) == (sizeof(void*) == sizeof(__int32) ? 0x0008 : 0x0010));

typedef struct _OBJECT_HEADER_QUOTA_INFO
{
    ULONG PagedPoolCharge;
    ULONG NonPagedPoolCharge;
    ULONG SecurityDescriptorCharge;
#ifdef _WIN64
    ULONG Reserved1;
    PVOID SecurityDescriptorQuotaBlock;
    ULONG64 Reserved2;
#else
    PVOID SecurityDescriptorQuotaBlock;
#endif
} OBJECT_HEADER_QUOTA_INFO, * POBJECT_HEADER_QUOTA_INFO;
STATIC_ASSERT(sizeof(OBJECT_HEADER_QUOTA_INFO) == (sizeof(void*) == sizeof(__int32) ? 0x0010 : 0x0020));

typedef struct _OBJECT_HEADER_PROCESS_INFO
{
    PEPROCESS  ExclusiveProcess;
    SIZE_T     Reserved;

} OBJECT_HEADER_PROCESS_INFO, * POBJECT_HEADER_PROCESS_INFO;
STATIC_ASSERT(sizeof(OBJECT_HEADER_PROCESS_INFO) == (sizeof(void*) == sizeof(__int32) ? 0x0008 : 0x0010));

typedef struct _OBJECT_HEADER_AUDIT_INFO
{
    PVOID  SecurityDescriptor;
    SIZE_T Reserved;

} OBJECT_HEADER_AUDIT_INFO, * POBJECT_HEADER_AUDIT_INFO;
STATIC_ASSERT(sizeof(OBJECT_HEADER_AUDIT_INFO) == (sizeof(void*) == sizeof(__int32) ? 0x0008 : 0x0010));

typedef struct _OBJECT_HEADER_HANDLE_REVOCATION_INFO
{
    LIST_ENTRY ListEntry;
    struct _OB_HANDLE_REVOCATION_BLOCK* RevocationBlock;
    UINT8 Padding1[4];
#ifdef _WIN64
    UINT8 Padding2[4];
#endif
} OBJECT_HEADER_HANDLE_REVOCATION_INFO, * POBJECT_HEADER_HANDLE_REVOCATION_INFO;
STATIC_ASSERT(sizeof(OBJECT_HEADER_HANDLE_REVOCATION_INFO) == (sizeof(void*) == sizeof(__int32) ? 0x0010 : 0x0020));

typedef struct _OBJECT_HEADER_EXTENDED_INFO
{
    struct _OBJECT_FOOTER* Footer;
    SIZE_T Reserved;

} OBJECT_HEADER_EXTENDED_INFO, * POBJECT_HEADER_EXTENDED_INFO;
STATIC_ASSERT(sizeof(OBJECT_HEADER_EXTENDED_INFO) == (sizeof(void*) == sizeof(__int32) ? 0x0008 : 0x0010));

typedef struct _OBJECT_HEADER_PADDING_INFO
{
    ULONG PaddingAmount;

} OBJECT_HEADER_PADDING_INFO, * POBJECT_HEADER_PADDING_INFO;
STATIC_ASSERT(sizeof(OBJECT_HEADER_PADDING_INFO) == (sizeof(void*) == sizeof(__int32) ? 0x0004 : 0x0004));

typedef struct _OBJECT_CREATE_INFORMATION
{
    ULONG   Attributes;
    HANDLE  RootDirectory;
    KPROCESSOR_MODE ProbeMode;
    ULONG   PagedPoolCharge;
    ULONG   NonPagedPoolCharge;
    ULONG   SecurityDescriptorCharge;
    PVOID   SecurityDescriptor;
    PSECURITY_QUALITY_OF_SERVICE   SecurityQos;
    SECURITY_QUALITY_OF_SERVICE    SecurityQualityOfService;

} OBJECT_CREATE_INFORMATION, * POBJECT_CREATE_INFORMATION;
STATIC_ASSERT(sizeof(OBJECT_CREATE_INFORMATION) == (sizeof(void*) == sizeof(__int32) ? 0x002C : 0x0040));

typedef struct _OBJECT_HEADER
{
    LONG_PTR PointerCount;
    union
    {
        LONG_PTR HandleCount;
        PVOID    NextToFree;
    };
    EX_PUSH_LOCK Lock;
    UINT8 TypeIndex;
    union
    {
        UINT8 TraceFlags;
        struct
        {
            UINT8 DbgRefTrace : 1;
            UINT8 DbgTracePermanent : 1;
        };
    };
    UINT8 InfoMask;
    union
    {
        UINT8 Flags;
        struct
        {
            UINT8 NewObject : 1;
            UINT8 KernelObject : 1;
            UINT8 KernelOnlyAccess : 1;
            UINT8 ExclusiveObject : 1;
            UINT8 PermanentObject : 1;
            UINT8 DefaultSecurityQuota : 1;
            UINT8 SingleHandleEntry : 1;
            UINT8 DeletedInline : 1;
        };
    };

#ifdef _WIN64
    ULONG Reserved;
#endif

    union
    {
        POBJECT_CREATE_INFORMATION ObjectCreateInfo;
        PVOID QuotaBlockCharged;
    };

    PVOID SecurityDescriptor;
    QUAD Body;

} OBJECT_HEADER, * POBJECT_HEADER;
STATIC_ASSERT(sizeof(OBJECT_HEADER) == (sizeof(void*) == sizeof(__int32) ? 0x0020 : 0x0038));

#include <poppack.h>
// end: Object Header

NTKERNELAPI
POBJECT_HEADER_NAME_INFO
NTAPI
ObQueryNameInfo(
    _In_ PVOID Object
);

NTKERNELAPI
POBJECT_TYPE
NTAPI
ObGetObjectType(
    _In_ PVOID Object
);

NTKERNELAPI
NTSTATUS
NTAPI
ObDuplicateObject(
    _In_ PEPROCESS SourceProcess,
    _In_ HANDLE SourceHandle,
    _In_opt_ PEPROCESS TargetProcess,
    _Out_opt_ PHANDLE TargetHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _In_ ULONG Options,
    _In_ KPROCESSOR_MODE PreviousMode
);

NTKERNELAPI
NTSTATUS
NTAPI
ObSetHandleAttributes(
    _In_ HANDLE Handle,
    _In_ POBJECT_HANDLE_FLAG_INFORMATION HandleFlags,
    _In_ KPROCESSOR_MODE PreviousMode
);

// begin: ObRegisterCallbacks() cookie struct
#include <pshpack8.h>

// private
// 
// ObRegisterCallbacks() cookie's memory layout
//
// +-------------------------------------------+
// | OB_CALLBACK_OBJECT_HEADER                 |
// +-------------------------------------------+
// | OB_CALLBACK_OBJECT_BODY[Header.BodyCount] |
// +-------------------------------------------+
// | WCHAR AltitudeBuffer[Altitude.Length]     |
// +-------------------------------------------+
//

typedef struct _OB_CALLBACK_OBJECT_BODY
{
    // all OB_CALLBACK_BODY
    // Header -> OBJECT_TYPE.CallbackList
    LIST_ENTRY                  ListEntry;

    OB_OPERATION                Operations;
    ULONG                       Always_1;

    // Self
    struct _OB_CALLBACK_OBJECT_HEADER* CallbackObject;

    POBJECT_TYPE                ObjectType;
    POB_PRE_OPERATION_CALLBACK  PreOperation;
    POB_POST_OPERATION_CALLBACK PostOperation;

    ULONG                       Reserved;

}OB_CALLBACK_OBJECT_BODY, *POB_CALLBACK_OBJECT_BODY;

typedef struct _OB_CALLBACK_OBJECT_HEADER
{
    USHORT          Version; // ObGetFilterVersion()
    USHORT          BodyCount;
    PVOID           RegistrationContext;
    UNICODE_STRING  Altitude;

    OB_CALLBACK_OBJECT_BODY Body[ANYSIZE_ARRAY];

}OB_CALLBACK_OBJECT_HEADER, *POB_CALLBACK_OBJECT_HEADER;

#include <poppack.h>
// end: ObRegisterCallbacks() cookie struct

#endif // _KERNEL_MODE

VEIL_END()

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
