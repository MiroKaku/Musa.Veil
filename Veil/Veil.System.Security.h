/*
 * PROJECT:   Veil
 * FILE:      Veil.System.Security.h
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

//
// Privileges
//

#ifndef _KERNEL_MODE

//
// These must be converted to LUIDs before use.
//

#define SE_MIN_WELL_KNOWN_PRIVILEGE         (2L)
#define SE_CREATE_TOKEN_PRIVILEGE           (2L)    // Required to create a primary token.
#define SE_ASSIGNPRIMARYTOKEN_PRIVILEGE     (3L)    // Required to assign the primary token of a process.
#define SE_LOCK_MEMORY_PRIVILEGE            (4L)    // Required to lock physical pages in memory.
#define SE_INCREASE_QUOTA_PRIVILEGE         (5L)    // Required to increase the quota assigned to a process.


#define SE_MACHINE_ACCOUNT_PRIVILEGE        (6L)    // Required to create a computer account.
#define SE_TCB_PRIVILEGE                    (7L)    // Required to act as part of the Trusted Computer Base.
#define SE_SECURITY_PRIVILEGE               (8L)    // Required to perform a number of security-related functions, such as controlling and viewing audit messages. // Security operator.
#define SE_TAKE_OWNERSHIP_PRIVILEGE         (9L)    // Required to take ownership of an object without being granted discretionary access. 
#define SE_LOAD_DRIVER_PRIVILEGE            (10L)   // Required to load or unload a device driver.
#define SE_SYSTEM_PROFILE_PRIVILEGE         (11L)   // Required to gather profiling information for the entire system.
#define SE_SYSTEMTIME_PRIVILEGE             (12L)   // Required to modify the system time.
#define SE_PROF_SINGLE_PROCESS_PRIVILEGE    (13L)   // Required to gather profiling information for a single process.
#define SE_INC_BASE_PRIORITY_PRIVILEGE      (14L)   // Required to increase the base priority of a process.
#define SE_CREATE_PAGEFILE_PRIVILEGE        (15L)   // Required to create a paging file.
#define SE_CREATE_PERMANENT_PRIVILEGE       (16L)   // Required to create a permanent object.
#define SE_BACKUP_PRIVILEGE                 (17L)   // Required to perform backup operations. This privilege causes the system to grant all read access control to any file.
#define SE_RESTORE_PRIVILEGE                (18L)   // Required to perform restore operations. This privilege causes the system to grant all write access control to any file.
#define SE_SHUTDOWN_PRIVILEGE               (19L)   // Required to shut down a local system.
#define SE_DEBUG_PRIVILEGE                  (20L)   // Required to debug and adjust memory of any process, ignoring the DACL for the process.
#define SE_AUDIT_PRIVILEGE                  (21L)   // Required to generate audit-log entries.
#define SE_SYSTEM_ENVIRONMENT_PRIVILEGE     (22L)   // Required to modify UEFI variables of systems that use this type of memory to store configuration information.
#define SE_CHANGE_NOTIFY_PRIVILEGE          (23L)   // Required to receive notifications of changes to files or directories and skip all traversal access checks. It is enabled by default for all users.
#define SE_REMOTE_SHUTDOWN_PRIVILEGE        (24L)   // Required to shut down a system using a network request.
#define SE_UNDOCK_PRIVILEGE                 (25L)   // Required to undock a laptop.
#define SE_SYNC_AGENT_PRIVILEGE             (26L)   // Required for a domain controller to use the Lightweight Directory Access Protocol (LDAP) directory synchronization services. 
#define SE_ENABLE_DELEGATION_PRIVILEGE      (27L)   // Required to mark user and computer accounts as trusted for delegation.
#define SE_MANAGE_VOLUME_PRIVILEGE          (28L)   // Required to enable volume management privileges.
#define SE_IMPERSONATE_PRIVILEGE            (29L)   // Required to impersonate a client after authentication.
#define SE_CREATE_GLOBAL_PRIVILEGE          (30L)   // Required to create named file mapping objects in the global namespace during Terminal Services sessions. It is enabled by default for all administrators.
#define SE_TRUSTED_CREDMAN_ACCESS_PRIVILEGE (31L)   // Required to access Credential Manager as a trusted caller.
#define SE_RELABEL_PRIVILEGE                (32L)   // Required to modify the mandatory integrity level of an object.
#define SE_INC_WORKING_SET_PRIVILEGE        (33L)   // Required to allocate more memory for applications that run in the context of users.
#define SE_TIME_ZONE_PRIVILEGE              (34L)   // Required to adjust the time zone associated with the computer's internal clock.
#define SE_CREATE_SYMBOLIC_LINK_PRIVILEGE   (35L)   // Required to create a symbolic link.
#define SE_DELEGATE_SESSION_USER_IMPERSONATE_PRIVILEGE   (36L)  // Required to obtain an impersonation token for another user in the same session.
#define SE_MAX_WELL_KNOWN_PRIVILEGE         (SE_DELEGATE_SESSION_USER_IMPERSONATE_PRIVILEGE)

#endif // !_KERNEL_MODE

//
// Authz
//

// begin_rev

// Types

#define TOKEN_SECURITY_ATTRIBUTE_TYPE_INVALID   0x00
#define TOKEN_SECURITY_ATTRIBUTE_TYPE_INT64     0x01
#define TOKEN_SECURITY_ATTRIBUTE_TYPE_UINT64    0x02
// Case insensitive attribute value string by default.
// Unless the flag TOKEN_SECURITY_ATTRIBUTE_VALUE_CASE_SENSITIVE
// is set indicating otherwise.
#define TOKEN_SECURITY_ATTRIBUTE_TYPE_STRING    0x03 // Case insensitive attribute value string by default. Unless the flag TOKEN_SECURITY_ATTRIBUTE_VALUE_CASE_SENSITIVE is set.
// Fully-qualified binary name.
#define TOKEN_SECURITY_ATTRIBUTE_TYPE_FQBN      0x04 // Fully-qualified binary name.
#define TOKEN_SECURITY_ATTRIBUTE_TYPE_SID       0x05
#define TOKEN_SECURITY_ATTRIBUTE_TYPE_BOOLEAN   0x06
#define TOKEN_SECURITY_ATTRIBUTE_TYPE_OCTET_STRING 0x10

// Flags

// Fully-qualified binary name.
#define TOKEN_SECURITY_ATTRIBUTE_NON_INHERITABLE        0x0001
// Attribute value is compared in a case sensitive way. It is valid with string value
// or composite type containing string value. For other types of value, this flag
// will be ignored. Currently, it is valid with the two types:
// TOKEN_SECURITY_ATTRIBUTE_TYPE_STRING and TOKEN_SECURITY_ATTRIBUTE_TYPE_FQBN.
#define TOKEN_SECURITY_ATTRIBUTE_VALUE_CASE_SENSITIVE   0x0002
#define TOKEN_SECURITY_ATTRIBUTE_USE_FOR_DENY_ONLY      0x0004 // Attribute is considered only for Deny Aces.
#define TOKEN_SECURITY_ATTRIBUTE_DISABLED_BY_DEFAULT    0x0008 // Attribute is disabled by default.
#define TOKEN_SECURITY_ATTRIBUTE_DISABLED               0x0010 // Attribute is disabled.
#define TOKEN_SECURITY_ATTRIBUTE_MANDATORY              0x0020 // Attribute is mandatory.
#define TOKEN_SECURITY_ATTRIBUTE_COMPARE_IGNORE         0x0040 // Attribute is ignored.

#define TOKEN_SECURITY_ATTRIBUTE_VALID_FLAGS ( \
    TOKEN_SECURITY_ATTRIBUTE_NON_INHERITABLE | \
    TOKEN_SECURITY_ATTRIBUTE_VALUE_CASE_SENSITIVE | \
    TOKEN_SECURITY_ATTRIBUTE_USE_FOR_DENY_ONLY | \
    TOKEN_SECURITY_ATTRIBUTE_DISABLED_BY_DEFAULT | \
    TOKEN_SECURITY_ATTRIBUTE_DISABLED | \
    TOKEN_SECURITY_ATTRIBUTE_MANDATORY)

// Reserve upper 16 bits for custom flags. These should be preserved but not
// validated as they do not affect security in any way.
#define TOKEN_SECURITY_ATTRIBUTE_CUSTOM_FLAGS 0xffff0000

// end_rev

// private // CLAIM_SECURITY_ATTRIBUTE_FQBN_VALUE
typedef struct _TOKEN_SECURITY_ATTRIBUTE_FQBN_VALUE
{
    ULONG64 Version;
    UNICODE_STRING Name;
} TOKEN_SECURITY_ATTRIBUTE_FQBN_VALUE, * PTOKEN_SECURITY_ATTRIBUTE_FQBN_VALUE;

// private // CLAIM_SECURITY_ATTRIBUTE_OCTET_STRING_VALUE
typedef struct _TOKEN_SECURITY_ATTRIBUTE_OCTET_STRING_VALUE
{
    PVOID Value; // Pointer is BYTE aligned.
    ULONG ValueLength; // In bytes
} TOKEN_SECURITY_ATTRIBUTE_OCTET_STRING_VALUE, * PTOKEN_SECURITY_ATTRIBUTE_OCTET_STRING_VALUE;

// private
typedef struct _TOKEN_SECURITY_ATTRIBUTE_V1
{
    UNICODE_STRING Name;
    USHORT ValueType;
    USHORT Reserved;
    ULONG Flags;
    ULONG ValueCount;
    union
    {
        PLONG64  Int64;
        PULONG64 Uint64;
        PUNICODE_STRING String;
        PTOKEN_SECURITY_ATTRIBUTE_FQBN_VALUE Fqbn;
        PTOKEN_SECURITY_ATTRIBUTE_OCTET_STRING_VALUE OctetString;
    } Values;
} TOKEN_SECURITY_ATTRIBUTE_V1, * PTOKEN_SECURITY_ATTRIBUTE_V1;

// private
typedef struct _TOKEN_SECURITY_ATTRIBUTE_RELATIVE_V1
{
    UNICODE_STRING Name;
    USHORT ValueType;
    USHORT Reserved;
    ULONG Flags;
    ULONG ValueCount;
    union
    {
        ULONG Int64[ANYSIZE_ARRAY];
        ULONG Uint64[ANYSIZE_ARRAY];
        ULONG String[ANYSIZE_ARRAY];
        ULONG Fqbn[ANYSIZE_ARRAY];
        ULONG OctetString[ANYSIZE_ARRAY];
    } Values;
} TOKEN_SECURITY_ATTRIBUTE_RELATIVE_V1, * PTOKEN_SECURITY_ATTRIBUTE_RELATIVE_V1;

// rev
#define TOKEN_SECURITY_ATTRIBUTES_INFORMATION_VERSION_V1 1
// rev
#define TOKEN_SECURITY_ATTRIBUTES_INFORMATION_VERSION TOKEN_SECURITY_ATTRIBUTES_INFORMATION_VERSION_V1

// private
typedef struct _TOKEN_SECURITY_ATTRIBUTES_INFORMATION
{
    USHORT Version;
    USHORT Reserved;
    ULONG AttributeCount;
    union
    {
        PTOKEN_SECURITY_ATTRIBUTE_V1 AttributeV1;
    } Attribute;
} TOKEN_SECURITY_ATTRIBUTES_INFORMATION, * PTOKEN_SECURITY_ATTRIBUTES_INFORMATION;

// private
typedef enum _TOKEN_SECURITY_ATTRIBUTE_OPERATION
{
    TOKEN_SECURITY_ATTRIBUTE_OPERATION_NONE,
    TOKEN_SECURITY_ATTRIBUTE_OPERATION_REPLACE_ALL,
    TOKEN_SECURITY_ATTRIBUTE_OPERATION_ADD,
    TOKEN_SECURITY_ATTRIBUTE_OPERATION_DELETE,
    TOKEN_SECURITY_ATTRIBUTE_OPERATION_REPLACE
} TOKEN_SECURITY_ATTRIBUTE_OPERATION, * PTOKEN_SECURITY_ATTRIBUTE_OPERATION;

// private
typedef struct _TOKEN_SECURITY_ATTRIBUTES_AND_OPERATION_INFORMATION
{
    PTOKEN_SECURITY_ATTRIBUTES_INFORMATION Attributes;
    PTOKEN_SECURITY_ATTRIBUTE_OPERATION Operations;
} TOKEN_SECURITY_ATTRIBUTES_AND_OPERATION_INFORMATION, * PTOKEN_SECURITY_ATTRIBUTES_AND_OPERATION_INFORMATION;

// rev
typedef struct _TOKEN_PROCESS_TRUST_LEVEL
{
    PSID TrustLevelSid;
} TOKEN_PROCESS_TRUST_LEVEL, * PTOKEN_PROCESS_TRUST_LEVEL;

//
// Tokens
//

/**
 * The NtCreateToken routine creates a new access token.
 *
 * \param TokenHandle Pointer to a variable that receives the handle to the newly created token.
 * \param DesiredAccess Specifies the requested access rights for the new token.
 * \param ObjectAttributes Optional pointer to an OBJECT_ATTRIBUTES structure specifying object attributes.
 * \param Type Specifies the type of token to be created (primary or impersonation).
 * \param AuthenticationId Pointer to a locally unique identifier (LUID) for the token.
 * \param ExpirationTime Pointer to a LARGE_INTEGER specifying the expiration time of the token.
 * \param User Pointer to a TOKEN_USER structure specifying the user account for the token.
 * \param Groups Pointer to a TOKEN_GROUPS structure specifying the group accounts for the token.
 * \param Privileges Pointer to a TOKEN_PRIVILEGES structure specifying the privileges for the token.
 * \param Owner Optional pointer to a TOKEN_OWNER structure specifying the owner SID for the token.
 * \param PrimaryGroup Pointer to a TOKEN_PRIMARY_GROUP structure specifying the primary group SID for the token.
 * \param DefaultDacl Optional pointer to a TOKEN_DEFAULT_DACL structure specifying the default DACL for the token.
 * \param Source Pointer to a TOKEN_SOURCE structure specifying the source of the token.
 * \return NTSTATUS code indicating success or failure.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntcreatetoken
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateToken(
    _Out_ PHANDLE TokenHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ TOKEN_TYPE Type,
    _In_ PLUID AuthenticationId,
    _In_ PLARGE_INTEGER ExpirationTime,
    _In_ PTOKEN_USER User,
    _In_ PTOKEN_GROUPS Groups,
    _In_ PTOKEN_PRIVILEGES Privileges,
    _In_opt_ PTOKEN_OWNER Owner,
    _In_ PTOKEN_PRIMARY_GROUP PrimaryGroup,
    _In_opt_ PTOKEN_DEFAULT_DACL DefaultDacl,
    _In_ PTOKEN_SOURCE Source
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateToken(
    _Out_ PHANDLE TokenHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ TOKEN_TYPE Type,
    _In_ PLUID AuthenticationId,
    _In_ PLARGE_INTEGER ExpirationTime,
    _In_ PTOKEN_USER User,
    _In_ PTOKEN_GROUPS Groups,
    _In_ PTOKEN_PRIVILEGES Privileges,
    _In_opt_ PTOKEN_OWNER Owner,
    _In_ PTOKEN_PRIMARY_GROUP PrimaryGroup,
    _In_opt_ PTOKEN_DEFAULT_DACL DefaultDacl,
    _In_ PTOKEN_SOURCE Source
);

#if (NTDDI_VERSION >= NTDDI_WIN8)
/**
 * The NtCreateLowBoxToken routine creates a new lowbox access token based on an existing token.
 *
 * \param TokenHandle Pointer to a variable that receives the handle to the newly created lowbox token.
 * \param ExistingTokenHandle Handle to an existing token to base the new token on.
 * \param DesiredAccess Specifies the requested access rights for the new token.
 * \param ObjectAttributes Optional pointer to an OBJECT_ATTRIBUTES structure specifying object attributes.
 * \param PackageSid Pointer to a SID structure specifying the package SID for the lowbox token.
 * \param CapabilityCount Number of capabilities in the Capabilities array.
 * \param Capabilities Optional pointer to an array of SID_AND_ATTRIBUTES structures specifying capabilities.
 * \param HandleCount Number of handles in the Handles array.
 * \param Handles Optional pointer to an array of handles to be associated with the token.
 * \return NTSTATUS code indicating success or failure.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntcreatelowboxtoken
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateLowBoxToken(
    _Out_ PHANDLE TokenHandle,
    _In_ HANDLE ExistingTokenHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ PSID PackageSid,
    _In_ ULONG CapabilityCount,
    _In_reads_opt_(CapabilityCount) PSID_AND_ATTRIBUTES Capabilities,
    _In_ ULONG HandleCount,
    _In_reads_opt_(HandleCount) HANDLE* Handles
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateLowBoxToken(
    _Out_ PHANDLE TokenHandle,
    _In_ HANDLE ExistingTokenHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ PSID PackageSid,
    _In_ ULONG CapabilityCount,
    _In_reads_opt_(CapabilityCount) PSID_AND_ATTRIBUTES Capabilities,
    _In_ ULONG HandleCount,
    _In_reads_opt_(HandleCount) HANDLE* Handles
);

/**
 * The NtCreateTokenEx routine creates a new access token with extended attributes.
 *
 * \param TokenHandle Pointer to a variable that receives the handle to the newly created token.
 * \param DesiredAccess Specifies the requested access rights for the new token.
 * \param ObjectAttributes Optional pointer to an OBJECT_ATTRIBUTES structure specifying object attributes.
 * \param Type Specifies the type of token to be created (primary or impersonation).
 * \param AuthenticationId Pointer to a locally unique identifier (LUID) for the token.
 * \param ExpirationTime Pointer to a LARGE_INTEGER specifying the expiration time of the token.
 * \param User Pointer to a TOKEN_USER structure specifying the user account for the token.
 * \param Groups Pointer to a TOKEN_GROUPS structure specifying the group accounts for the token.
 * \param Privileges Pointer to a TOKEN_PRIVILEGES structure specifying the privileges for the token.
 * \param UserAttributes Optional pointer to a TOKEN_SECURITY_ATTRIBUTES_INFORMATION structure specifying user claims.
 * \param DeviceAttributes Optional pointer to a TOKEN_SECURITY_ATTRIBUTES_INFORMATION structure specifying device claims.
 * \param DeviceGroups Optional pointer to a TOKEN_GROUPS structure specifying device groups.
 * \param MandatoryPolicy Optional pointer to a TOKEN_MANDATORY_POLICY structure specifying the mandatory policy.
 * \param Owner Optional pointer to a TOKEN_OWNER structure specifying the owner SID for the token.
 * \param PrimaryGroup Pointer to a TOKEN_PRIMARY_GROUP structure specifying the primary group SID for the token.
 * \param DefaultDacl Optional pointer to a TOKEN_DEFAULT_DACL structure specifying the default DACL for the token.
 * \param Source Pointer to a TOKEN_SOURCE structure specifying the source of the token.
 * \return NTSTATUS code indicating success or failure.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntcreatetokenex
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateTokenEx(
    _Out_ PHANDLE TokenHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ TOKEN_TYPE Type,
    _In_ PLUID AuthenticationId,
    _In_ PLARGE_INTEGER ExpirationTime,
    _In_ PTOKEN_USER User,
    _In_ PTOKEN_GROUPS Groups,
    _In_ PTOKEN_PRIVILEGES Privileges,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION UserAttributes,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION DeviceAttributes,
    _In_opt_ PTOKEN_GROUPS DeviceGroups,
    _In_opt_ PTOKEN_MANDATORY_POLICY MandatoryPolicy,
    _In_opt_ PTOKEN_OWNER Owner,
    _In_ PTOKEN_PRIMARY_GROUP PrimaryGroup,
    _In_opt_ PTOKEN_DEFAULT_DACL DefaultDacl,
    _In_ PTOKEN_SOURCE Source
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateTokenEx(
    _Out_ PHANDLE TokenHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ TOKEN_TYPE Type,
    _In_ PLUID AuthenticationId,
    _In_ PLARGE_INTEGER ExpirationTime,
    _In_ PTOKEN_USER User,
    _In_ PTOKEN_GROUPS Groups,
    _In_ PTOKEN_PRIVILEGES Privileges,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION UserAttributes,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION DeviceAttributes,
    _In_opt_ PTOKEN_GROUPS DeviceGroups,
    _In_opt_ PTOKEN_MANDATORY_POLICY MandatoryPolicy,
    _In_opt_ PTOKEN_OWNER Owner,
    _In_ PTOKEN_PRIMARY_GROUP PrimaryGroup,
    _In_opt_ PTOKEN_DEFAULT_DACL DefaultDacl,
    _In_ PTOKEN_SOURCE Source
);
#endif

/**
 * The NtOpenProcessToken routine opens the access token associated with a process, and returns a handle that can be used to access that token.
 *
 * \param ProcessHandle Handle to the process whose access token is to be opened. The handle must have PROCESS_QUERY_INFORMATION access.
 * \param DesiredAccess ACCESS_MASK structure specifying the requested types of access to the access token.
 * \param TokenHandle Pointer to a caller-allocated variable that receives a handle to the newly opened access token.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntopenprocesstoken
 */
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenProcessToken(
    _In_ HANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _Out_ PHANDLE TokenHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwOpenProcessToken(
    _In_ HANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _Out_ PHANDLE TokenHandle
);

/**
 * The NtOpenProcessTokenEx routine opens the access token associated with a process, and returns a handle that can be used to access that token.
 *
 * \param ProcessHandle Handle to the process whose access token is to be opened. The handle must have PROCESS_QUERY_INFORMATION access.
 * \param DesiredAccess ACCESS_MASK structure specifying the requested types of access to the access token.
 * \param HandleAttributes Attributes for the created handle. Only OBJ_KERNEL_HANDLE is currently supported.
 * \param TokenHandle Pointer to a caller-allocated variable that receives a handle to the newly opened access token.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntopenprocesstokenex
 */
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenProcessTokenEx(
    _In_ HANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _Out_ PHANDLE TokenHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwOpenProcessTokenEx(
    _In_ HANDLE ProcessHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG HandleAttributes,
    _Out_ PHANDLE TokenHandle
);

/**
 * The NtOpenThreadToken routine opens the access token associated with a thread, and returns a handle that can be used to access that token.
 *
 * \param ThreadHandle Handle to the thread whose access token is to be opened. The handle must have THREAD_QUERY_INFORMATION access.
 * \param DesiredAccess ACCESS_MASK structure specifying the requested types of access to the access token.
 * \param OpenAsSelf Boolean value specifying whether the access check is to be made against the security context of the thread calling NtOpenThreadToken or against the security context of the process for the calling thread.
 * \param TokenHandle Pointer to a caller-allocated variable that receives a handle to the newly opened access token.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntopenthreadtoken
 */
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenThreadToken(
    _In_ HANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ BOOLEAN OpenAsSelf,
    _Out_ PHANDLE TokenHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwOpenThreadToken(
    _In_ HANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ BOOLEAN OpenAsSelf,
    _Out_ PHANDLE TokenHandle
);

/**
 * The NtOpenThreadTokenEx routine opens the access token associated with a thread, and returns a handle that can be used to access that token.
 *
 * \param ThreadHandle Handle to the thread whose access token is to be opened. The handle must have THREAD_QUERY_INFORMATION access.
 * \param DesiredAccess ACCESS_MASK structure specifying the requested types of access to the access token.
 * \param OpenAsSelf Boolean value specifying whether the access check is to be made against the security context of the thread calling NtOpenThreadToken or against the security context of the process for the calling thread.
 * \param HandleAttributes Attributes for the created handle. Only OBJ_KERNEL_HANDLE is currently supported.
 * \param TokenHandle Pointer to a caller-allocated variable that receives a handle to the newly opened access token.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntopenthreadtokenex
 */
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenThreadTokenEx(
    _In_ HANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ BOOLEAN OpenAsSelf,
    _In_ ULONG HandleAttributes,
    _Out_ PHANDLE TokenHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwOpenThreadTokenEx(
    _In_ HANDLE ThreadHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ BOOLEAN OpenAsSelf,
    _In_ ULONG HandleAttributes,
    _Out_ PHANDLE TokenHandle
);

/**
 * The NtDuplicateToken function creates a handle to a new access token that duplicates an existing token.
 *
 * \param ExistingTokenHandle A handle to an existing access token that was opened with the TOKEN_DUPLICATE access right.
 * \param DesiredAccess ACCESS_MASK structure specifying the requested types of access to the access token.
 * \param ObjectAttributes Pointer to an OBJECT_ATTRIBUTES structure that describes the requested properties for the new token.
 * \param EffectiveOnly A Boolean value that indicates whether the entire existing token should be duplicated into the new token or just the effective (currently enabled) part of the token.
 * \param Type Specifies the type of token to create either a primary token or an impersonation token.
 * \param NewTokenHandle Pointer to a caller-allocated variable that receives a handle to the newly duplicated token.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntduplicatetoken
 */
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtDuplicateToken(
    _In_ HANDLE ExistingTokenHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ BOOLEAN EffectiveOnly,
    _In_ TOKEN_TYPE TokenType,
    _Out_ PHANDLE NewTokenHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwDuplicateToken(
    _In_ HANDLE ExistingTokenHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ BOOLEAN EffectiveOnly,
    _In_ TOKEN_TYPE Type,
    _Out_ PHANDLE NewTokenHandle
);

/**
 * The NtQueryInformationToken routine retrieves a specified type of information about an access token. The calling process must have appropriate access rights to obtain the information.
 *
 * \param TokenHandle A handle to an existing access token from which information is to be retrieved. If TokenInformationClass is set to TokenSource, the handle must have TOKEN_QUERY_SOURCE access.
 * For all other TokenInformationClass values, the handle must have TOKEN_QUERY access.
 * \param TokenInformationClass A value from the TOKEN_INFORMATION_CLASS enumerated type identifying the type of information to be retrieved.
 * \param TokenInformation Pointer to a caller-allocated buffer that receives the requested information about the token.
 * \param TokenInformationLength Length, in bytes, of the caller-allocated TokenInformation buffer.
 * \param ReturnLength Pointer to a caller-allocated variable that receives the actual length, in bytes, of the information returned in the TokenInformation buffer.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntqueryinformationtoken
 */
_When_(TokenInformationClass == TokenAccessInformation,
_At_(TokenInformationLength,
    _In_range_(>= , sizeof(TOKEN_ACCESS_INFORMATION))))
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryInformationToken(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _Out_writes_bytes_to_opt_(TokenInformationLength, *ReturnLength) PVOID TokenInformation,
    _In_ ULONG TokenInformationLength,
    _Out_ PULONG ReturnLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwQueryInformationToken(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _Out_writes_bytes_to_opt_(TokenInformationLength, *ReturnLength) PVOID TokenInformation,
    _In_ ULONG TokenInformationLength,
    _Out_ PULONG ReturnLength
);

/**
 * The NtSetInformationToken routine modifies information in a specified token. The calling process must have appropriate access rights to set the information.
 *
 * \param TokenHandle A handle to an existing access token which information is to be modified.
 * \param TokenInformationClass A value from the TOKEN_INFORMATION_CLASS enumerated type identifying the type of information to be modified.
 * \param TokenInformation Pointer to a caller-allocated buffer containing the information to be modified in the token.
 * \param TokenInformationLength Length, in bytes, of the caller-allocated TokenInformation buffer.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntsetinformationtoken
 */
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationToken(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _In_reads_bytes_(TokenInformationLength) PVOID TokenInformation,
    _In_ ULONG TokenInformationLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSetInformationToken(
    _In_ HANDLE TokenHandle,
    _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
    _In_reads_bytes_(TokenInformationLength) PVOID TokenInformation,
    _In_ ULONG TokenInformationLength
);

/**
 * The NtAdjustPrivilegesToken routine enables or disables privileges in the specified access token.
 *
 * \param TokenHandle Handle to the token that contains the privileges to be modified. The handle must have TOKEN_ADJUST_PRIVILEGES access.
 * \param DisableAllPrivileges Specifies whether the function disables all of the token's privileges. If this value is TRUE, the function disables all privileges and ignores the NewState parameter.
 * If it is FALSE, the function modifies privileges based on the information pointed to by the NewState parameter.
 * \param NewState A pointer to a TOKEN_PRIVILEGES structure that specifies an array of privileges and their attributes. If DisableAllPrivileges is TRUE, the function ignores this parameter.
 * \param BufferLength Specifies the size, in bytes, of the buffer pointed to by the PreviousState parameter. This parameter can be zero if the PreviousState parameter is NULL.
 * \param PreviousState A pointer to a buffer that the function fills with a TOKEN_PRIVILEGES structure that contains the previous state of any privileges that the function modifies.
 * \param ReturnLength A pointer to a variable that receives the required size, in bytes, of the buffer pointed to by the PreviousState parameter. This parameter can be NULL if PreviousState is NULL.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/securitybaseapi/nf-securitybaseapi-adjusttokenprivileges
 */
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAdjustPrivilegesToken(
    _In_ HANDLE TokenHandle,
    _In_ BOOLEAN DisableAllPrivileges,
    _In_opt_ PTOKEN_PRIVILEGES NewState,
    _In_ ULONG BufferLength,
    _Out_writes_bytes_to_opt_(BufferLength, *ReturnLength) PTOKEN_PRIVILEGES PreviousState,
    _Out_ _When_(PreviousState == NULL, _Out_opt_) PULONG ReturnLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAdjustPrivilegesToken(
    _In_ HANDLE TokenHandle,
    _In_ BOOLEAN DisableAllPrivileges,
    _In_opt_ PTOKEN_PRIVILEGES NewState,
    _In_ ULONG BufferLength,
    _Out_writes_bytes_to_opt_(BufferLength, *ReturnLength) PTOKEN_PRIVILEGES PreviousState,
    _Out_opt_ PULONG ReturnLength
);

/**
 * The NtAdjustGroupsToken routine enables or disables groups in the specified access token.
 *
 * \param TokenHandle Handle to the token that contains the groups to be modified. The handle must have TOKEN_ADJUST_GROUPS access.
 * \param ResetToDefault Specifies whether the function resets the groups to the default state. If this value is TRUE, the function resets all groups to their default state and ignores the NewState parameter.
 * \param NewState A pointer to a TOKEN_GROUPS structure that specifies an array of groups and their attributes. If ResetToDefault is TRUE, the function ignores this parameter.
 * \param BufferLength Specifies the size, in bytes, of the buffer pointed to by the PreviousState parameter. This parameter can be zero if the PreviousState parameter is NULL.
 * \param PreviousState A pointer to a buffer that the function fills with a TOKEN_GROUPS structure that contains the previous state of any groups that the function modifies.
 * \param ReturnLength A pointer to a variable that receives the required size, in bytes, of the buffer pointed to by the PreviousState parameter. This parameter can be NULL if PreviousState is NULL.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/securitybaseapi/nf-securitybaseapi-adjusttokengroups
 */
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAdjustGroupsToken(
    _In_ HANDLE TokenHandle,
    _In_ BOOLEAN ResetToDefault,
    _In_opt_ PTOKEN_GROUPS NewState,
    _In_range_(>= , sizeof(TOKEN_GROUPS)) ULONG BufferLength,
    _Out_writes_bytes_to_opt_(BufferLength, *ReturnLength) PTOKEN_GROUPS PreviousState,
    _Out_ PULONG ReturnLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAdjustGroupsToken(
    _In_ HANDLE TokenHandle,
    _In_ BOOLEAN ResetToDefault,
    _In_opt_ PTOKEN_GROUPS NewState,
    _In_opt_ ULONG BufferLength,
    _Out_writes_bytes_to_opt_(BufferLength, *ReturnLength) PTOKEN_GROUPS PreviousState,
    _Out_opt_ PULONG ReturnLength
);

#if (NTDDI_VERSION >= NTDDI_WIN8)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAdjustTokenClaimsAndDeviceGroups(
    _In_ HANDLE TokenHandle,
    _In_ BOOLEAN UserResetToDefault,
    _In_ BOOLEAN DeviceResetToDefault,
    _In_ BOOLEAN DeviceGroupsResetToDefault,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION NewUserState,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION NewDeviceState,
    _In_opt_ PTOKEN_GROUPS NewDeviceGroupsState,
    _In_ ULONG UserBufferLength,
    _Out_writes_bytes_to_opt_(UserBufferLength, *UserReturnLength) PTOKEN_SECURITY_ATTRIBUTES_INFORMATION PreviousUserState,
    _In_ ULONG DeviceBufferLength,
    _Out_writes_bytes_to_opt_(DeviceBufferLength, *DeviceReturnLength) PTOKEN_SECURITY_ATTRIBUTES_INFORMATION PreviousDeviceState,
    _In_ ULONG DeviceGroupsBufferLength,
    _Out_writes_bytes_to_opt_(DeviceGroupsBufferLength, *DeviceGroupsReturnBufferLength) PTOKEN_GROUPS PreviousDeviceGroups,
    _Out_opt_ PULONG UserReturnLength,
    _Out_opt_ PULONG DeviceReturnLength,
    _Out_opt_ PULONG DeviceGroupsReturnBufferLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAdjustTokenClaimsAndDeviceGroups(
    _In_ HANDLE TokenHandle,
    _In_ BOOLEAN UserResetToDefault,
    _In_ BOOLEAN DeviceResetToDefault,
    _In_ BOOLEAN DeviceGroupsResetToDefault,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION NewUserState,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION NewDeviceState,
    _In_opt_ PTOKEN_GROUPS NewDeviceGroupsState,
    _In_ ULONG UserBufferLength,
    _Out_writes_bytes_to_opt_(UserBufferLength, *UserReturnLength) PTOKEN_SECURITY_ATTRIBUTES_INFORMATION PreviousUserState,
    _In_ ULONG DeviceBufferLength,
    _Out_writes_bytes_to_opt_(DeviceBufferLength, *DeviceReturnLength) PTOKEN_SECURITY_ATTRIBUTES_INFORMATION PreviousDeviceState,
    _In_ ULONG DeviceGroupsBufferLength,
    _Out_writes_bytes_to_opt_(DeviceGroupsBufferLength, *DeviceGroupsReturnBufferLength) PTOKEN_GROUPS PreviousDeviceGroups,
    _Out_opt_ PULONG UserReturnLength,
    _Out_opt_ PULONG DeviceReturnLength,
    _Out_opt_ PULONG DeviceGroupsReturnBufferLength
);
#endif

// NtFilterToken Flags
#define DISABLE_MAX_PRIVILEGE   0x1 // Disables all privileges in the new token except SE_CHANGE_NOTIFY_PRIVILEGE.
#define SANDBOX_INERT           0x2 // Stores the TOKEN_SANDBOX_INERT flag in the token.
#define LUA_TOKEN               0x4 
#define WRITE_RESTRICTED        0x8 

/**
 * The NtFilterToken routine creates a new access token that is a restricted version of an existing access token.
 *
 * \param ExistingTokenHandle Handle to a primary or impersonation token. The token can also be a restricted token. This token must already be open for TOKEN_DUPLICATE access.
 * \param Flags Specifies additional privilege options.
 * \param SidsToDisable The deny-only SIDs to include in the restricted token. The system uses a deny-only SID to deny access to a securable object. The absence of a deny-only SID does not allow access.
 * \param PrivilegesToDelete The privileges to delete in the restricted token. This parameter is optional and can be NULL.
 * \param RestrictedSids The list of restricting SIDs for the new token. This parameter is optional and can be NULL.
 * \param NewTokenHandle The new restricted token. The new token is the same type, primary or impersonation, as the existing token.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-sefiltertoken
 */
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtFilterToken(
    _In_ HANDLE ExistingTokenHandle,
    _In_ ULONG Flags,
    _In_opt_ PTOKEN_GROUPS SidsToDisable,
    _In_opt_ PTOKEN_PRIVILEGES PrivilegesToDelete,
    _In_opt_ PTOKEN_GROUPS RestrictedSids,
    _Out_ PHANDLE NewTokenHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwFilterToken(
    _In_ HANDLE ExistingTokenHandle,
    _In_ ULONG Flags,
    _In_opt_ PTOKEN_GROUPS SidsToDisable,
    _In_opt_ PTOKEN_PRIVILEGES PrivilegesToDelete,
    _In_opt_ PTOKEN_GROUPS RestrictedSids,
    _Out_ PHANDLE NewTokenHandle
);

#if (NTDDI_VERSION >= NTDDI_WIN8)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtFilterTokenEx(
    _In_ HANDLE ExistingTokenHandle,
    _In_ ULONG Flags,
    _In_opt_ PTOKEN_GROUPS SidsToDisable,
    _In_opt_ PTOKEN_PRIVILEGES PrivilegesToDelete,
    _In_opt_ PTOKEN_GROUPS RestrictedSids,
    _In_ ULONG DisableUserClaimsCount,
    _In_opt_ PUNICODE_STRING UserClaimsToDisable,
    _In_ ULONG DisableDeviceClaimsCount,
    _In_opt_ PUNICODE_STRING DeviceClaimsToDisable,
    _In_opt_ PTOKEN_GROUPS DeviceGroupsToDisable,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION RestrictedUserAttributes,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION RestrictedDeviceAttributes,
    _In_opt_ PTOKEN_GROUPS RestrictedDeviceGroups,
    _Out_ PHANDLE NewTokenHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwFilterTokenEx(
    _In_ HANDLE ExistingTokenHandle,
    _In_ ULONG Flags,
    _In_opt_ PTOKEN_GROUPS SidsToDisable,
    _In_opt_ PTOKEN_PRIVILEGES PrivilegesToDelete,
    _In_opt_ PTOKEN_GROUPS RestrictedSids,
    _In_ ULONG DisableUserClaimsCount,
    _In_opt_ PUNICODE_STRING UserClaimsToDisable,
    _In_ ULONG DisableDeviceClaimsCount,
    _In_opt_ PUNICODE_STRING DeviceClaimsToDisable,
    _In_opt_ PTOKEN_GROUPS DeviceGroupsToDisable,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION RestrictedUserAttributes,
    _In_opt_ PTOKEN_SECURITY_ATTRIBUTES_INFORMATION RestrictedDeviceAttributes,
    _In_opt_ PTOKEN_GROUPS RestrictedDeviceGroups,
    _Out_ PHANDLE NewTokenHandle
);
#endif

/**
 * The NtCompareTokens routine compares two access tokens to determine whether they are equivalent.
 *
 * \param FirstTokenHandle Handle to the first access token to compare. The handle must have TOKEN_QUERY access.
 * \param SecondTokenHandle Handle to the second access token to compare. The handle must have TOKEN_QUERY access.
 * \param Equal Pointer to a BOOLEAN variable that receives TRUE if the tokens are equivalent, or FALSE otherwise.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntcomparetokens
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCompareTokens(
    _In_ HANDLE FirstTokenHandle,
    _In_ HANDLE SecondTokenHandle,
    _Out_ PBOOLEAN Equal
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCompareTokens(
    _In_ HANDLE FirstTokenHandle,
    _In_ HANDLE SecondTokenHandle,
    _Out_ PBOOLEAN Equal
);

/**
 * The NtPrivilegeCheck routine determines whether a specified set of privileges are enabled in the access token of a client.
 *
 * \param ClientToken Handle to the access token of the client whose privileges are to be checked. The handle must have TOKEN_QUERY access.
 * \param RequiredPrivileges Pointer to a PRIVILEGE_SET structure that specifies the set of privileges to be checked. On input, this structure contains the privileges to check.
 * \param Result Pointer to a BOOLEAN variable that receives TRUE if all specified privileges are enabled, or FALSE otherwise.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/securitybaseapi/nf-securitybaseapi-privilegecheck
 */
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtPrivilegeCheck(
    _In_ HANDLE ClientToken,
    _Inout_ PPRIVILEGE_SET RequiredPrivileges,
    _Out_ PBOOLEAN Result
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwPrivilegeCheck(
    _In_ HANDLE ClientToken,
    _Inout_ PPRIVILEGE_SET RequiredPrivileges,
    _Out_ PBOOLEAN Result
);

/**
 * The NtImpersonateAnonymousToken routine causes a thread to impersonate the anonymous token.
 *
 * \param ThreadHandle Handle to the thread that will impersonate the anonymous token. The handle must have THREAD_DIRECT_IMPERSONATION access.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntimpersonateanonymoustoken
 */
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtImpersonateAnonymousToken(
    _In_ HANDLE ThreadHandle
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwImpersonateAnonymousToken(
    _In_ HANDLE ThreadHandle
);

// rev
/**
 * The NtQuerySecurityAttributesToken routine retrieves security attribute information from an access token.
 *
 * \param TokenHandle Handle to the access token from which to retrieve security attributes. The handle must have TOKEN_QUERY access.
 * \param Attributes Pointer to an array of UNICODE_STRING structures specifying the names of the attributes to query. This parameter can be NULL if NumberOfAttributes is zero.
 * \param NumberOfAttributes The number of attributes specified in the Attributes array.
 * \param Buffer Pointer to a buffer that receives the security attribute information. The buffer receives a TOKEN_SECURITY_ATTRIBUTES_INFORMATION structure.
 * \param Length The size, in bytes, of the Buffer parameter.
 * \param ReturnLength Pointer to a variable that receives the number of bytes required to store the complete security attribute information.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQuerySecurityAttributesToken(
    _In_ HANDLE TokenHandle,
    _In_reads_opt_(NumberOfAttributes) PUNICODE_STRING Attributes,
    _In_ ULONG NumberOfAttributes,
    _Out_writes_bytes_(Length) PVOID Buffer, // PTOKEN_SECURITY_ATTRIBUTES_INFORMATION
    _In_ ULONG Length,
    _Out_ PULONG ReturnLength
);

// rev
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwQuerySecurityAttributesToken(
    _In_ HANDLE TokenHandle,
    _In_reads_opt_(NumberOfAttributes) PUNICODE_STRING Attributes,
    _In_ ULONG NumberOfAttributes,
    _Out_writes_bytes_(Length) PVOID Buffer, // PTOKEN_SECURITY_ATTRIBUTES_INFORMATION
    _In_ ULONG Length,
    _Out_ PULONG ReturnLength
);

//
// Access checking
//

/**
 * The NtAccessCheck routine determines whether a security descriptor grants a specified set of access rights to the client represented by an access token.
 *
 * \param SecurityDescriptor Pointer to the SECURITY_DESCRIPTOR structure against which access is checked.
 * \param ClientToken Handle to the access token representing the client. The handle must have TOKEN_QUERY access.
 * \param DesiredAccess Access mask that specifies the access rights to check.
 * \param GenericMapping Pointer to the GENERIC_MAPPING structure associated with the object for which access is being checked.
 * \param PrivilegeSet Pointer to a PRIVILEGE_SET structure that receives the privileges required to access the object. The buffer must be large enough to hold the privilege set.
 * \param PrivilegeSetLength Pointer to a variable that specifies the size, in bytes, of the PrivilegeSet buffer. On input, this is the size of the buffer; on output, it receives the number of bytes required.
 * \param GrantedAccess Pointer to an access mask that receives the granted access rights.
 * \param AccessStatus Pointer to a variable that receives the results of the access check.
 * \return NTSTATUS code indicating success or failure.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/securitybaseapi/nf-securitybaseapi-accesscheck
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAccessCheck(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ HANDLE ClientToken,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ PGENERIC_MAPPING GenericMapping,
    _Out_writes_bytes_(*PrivilegeSetLength) PPRIVILEGE_SET PrivilegeSet,
    _Inout_ PULONG PrivilegeSetLength,
    _Out_ PACCESS_MASK GrantedAccess,
    _Out_ PNTSTATUS AccessStatus
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAccessCheck(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ HANDLE ClientToken,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ PGENERIC_MAPPING GenericMapping,
    _Out_writes_bytes_(*PrivilegeSetLength) PPRIVILEGE_SET PrivilegeSet,
    _Inout_ PULONG PrivilegeSetLength,
    _Out_ PACCESS_MASK GrantedAccess,
    _Out_ PNTSTATUS AccessStatus
);

/**
 * The NtAccessCheckByType routine determines whether a security descriptor grants a specified set of access rights to the client represented by an access token, taking into account object type information.
 *
 * \param SecurityDescriptor Pointer to the SECURITY_DESCRIPTOR structure against which access is checked.
 * \param PrincipalSelfSid Optional pointer to a SID structure representing the principal self SID, or NULL.
 * \param ClientToken Handle to the access token representing the client. The handle must have TOKEN_QUERY access.
 * \param DesiredAccess Access mask that specifies the access rights to check.
 * \param ObjectTypeList Pointer to an array of OBJECT_TYPE_LIST structures that specify the hierarchy of object types for the object being accessed.
 * \param ObjectTypeListLength The number of elements in the ObjectTypeList array.
 * \param GenericMapping Pointer to the GENERIC_MAPPING structure associated with the object for which access is being checked.
 * \param PrivilegeSet Pointer to a PRIVILEGE_SET structure that receives the privileges required to access the object. The buffer must be large enough to hold the privilege set.
 * \param PrivilegeSetLength Pointer to a variable that specifies the size, in bytes, of the PrivilegeSet buffer. On input, this is the size of the buffer; on output, it receives the number of bytes required.
 * \param GrantedAccess Pointer to an access mask that receives the granted access rights.
 * \param AccessStatus Pointer to a variable that receives the results of the access check.
 * \return NTSTATUS code indicating success or failure.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/securitybaseapi/nf-securitybaseapi-accesscheckbytype
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAccessCheckByType(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID PrincipalSelfSid,
    _In_ HANDLE ClientToken,
    _In_ ACCESS_MASK DesiredAccess,
    _In_reads_(ObjectTypeListLength) POBJECT_TYPE_LIST ObjectTypeList,
    _In_ ULONG ObjectTypeListLength,
    _In_ PGENERIC_MAPPING GenericMapping,
    _Out_writes_bytes_(*PrivilegeSetLength) PPRIVILEGE_SET PrivilegeSet,
    _Inout_ PULONG PrivilegeSetLength,
    _Out_ PACCESS_MASK GrantedAccess,
    _Out_ PNTSTATUS AccessStatus
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAccessCheckByType(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID PrincipalSelfSid,
    _In_ HANDLE ClientToken,
    _In_ ACCESS_MASK DesiredAccess,
    _In_reads_(ObjectTypeListLength) POBJECT_TYPE_LIST ObjectTypeList,
    _In_ ULONG ObjectTypeListLength,
    _In_ PGENERIC_MAPPING GenericMapping,
    _Out_writes_bytes_(*PrivilegeSetLength) PPRIVILEGE_SET PrivilegeSet,
    _Inout_ PULONG PrivilegeSetLength,
    _Out_ PACCESS_MASK GrantedAccess,
    _Out_ PNTSTATUS AccessStatus
);

/**
 * The NtAccessCheckByTypeResultList routine determines whether a security descriptor grants a specified set of access rights to the client represented by an access token, and returns the results for each object type in a list.
 *
 * \param SecurityDescriptor Pointer to the SECURITY_DESCRIPTOR structure against which access is checked.
 * \param PrincipalSelfSid Optional pointer to a SID structure representing the principal self SID, or NULL.
 * \param ClientToken Handle to the access token representing the client. The handle must have TOKEN_QUERY access.
 * \param DesiredAccess Access mask that specifies the access rights to check.
 * \param ObjectTypeList Pointer to an array of OBJECT_TYPE_LIST structures that specify the hierarchy of object types for the object being accessed.
 * \param ObjectTypeListLength The number of elements in the ObjectTypeList array.
 * \param GenericMapping Pointer to the GENERIC_MAPPING structure associated with the object for which access is being checked.
 * \param PrivilegeSet Pointer to a PRIVILEGE_SET structure that receives the privileges required to access the object. The buffer must be large enough to hold the privilege set.
 * \param PrivilegeSetLength Pointer to a variable that specifies the size, in bytes, of the PrivilegeSet buffer. On input, this is the size of the buffer; on output, it receives the number of bytes required.
 * \param GrantedAccess Pointer to an array of access masks that receive the granted access rights for each object type.
 * \param AccessStatus Pointer to an array of NTSTATUS values that receive the results of the access check for each object type.
 * \return NTSTATUS code indicating success or failure.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/securitybaseapi/nf-securitybaseapi-accesscheckbytyperesultlist
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAccessCheckByTypeResultList(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID PrincipalSelfSid,
    _In_ HANDLE ClientToken,
    _In_ ACCESS_MASK DesiredAccess,
    _In_reads_(ObjectTypeListLength) POBJECT_TYPE_LIST ObjectTypeList,
    _In_ ULONG ObjectTypeListLength,
    _In_ PGENERIC_MAPPING GenericMapping,
    _Out_writes_bytes_(*PrivilegeSetLength) PPRIVILEGE_SET PrivilegeSet,
    _Inout_ PULONG PrivilegeSetLength,
    _Out_writes_(ObjectTypeListLength) PACCESS_MASK GrantedAccess,
    _Out_writes_(ObjectTypeListLength) PNTSTATUS AccessStatus
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAccessCheckByTypeResultList(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID PrincipalSelfSid,
    _In_ HANDLE ClientToken,
    _In_ ACCESS_MASK DesiredAccess,
    _In_reads_(ObjectTypeListLength) POBJECT_TYPE_LIST ObjectTypeList,
    _In_ ULONG ObjectTypeListLength,
    _In_ PGENERIC_MAPPING GenericMapping,
    _Out_writes_bytes_(*PrivilegeSetLength) PPRIVILEGE_SET PrivilegeSet,
    _Inout_ PULONG PrivilegeSetLength,
    _Out_writes_(ObjectTypeListLength) PACCESS_MASK GrantedAccess,
    _Out_writes_(ObjectTypeListLength) PNTSTATUS AccessStatus
);

//
// Signing
//

#if (NTDDI_VERSION >= NTDDI_WIN8)

/**
 * The NtSetCachedSigningLevel routine sets the cached signing level of a file.
 *
 * \param Flags Pointer to the flags set on the file.
 * \param InputSigningLevel Pointer to the signing level.
 * \param SourceFiles Pointer to a set of source file handles.
 * \param SourceFileCount The source file count.
 * \param TargetFile The target file.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/securitybaseapi/nf-securitybaseapi-setcachedsigninglevel
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetCachedSigningLevel(
    _In_ ULONG Flags,
    _In_ SE_SIGNING_LEVEL InputSigningLevel,
    _In_reads_(SourceFileCount) PHANDLE SourceFiles,
    _In_ ULONG SourceFileCount,
    _In_opt_ HANDLE TargetFile
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSetCachedSigningLevel(
    _In_ ULONG Flags,
    _In_ SE_SIGNING_LEVEL InputSigningLevel,
    _In_reads_(SourceFileCount) PHANDLE SourceFiles,
    _In_ ULONG SourceFileCount,
    _In_opt_ HANDLE TargetFile
);

#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)
typedef struct _SE_FILE_CACHE_CLAIM_INFORMATION
{
    ULONG Size;
    PVOID Claim;
} SE_FILE_CACHE_CLAIM_INFORMATION, *PSE_FILE_CACHE_CLAIM_INFORMATION;

typedef struct _SE_SET_FILE_CACHE_INFORMATION
{
    ULONG Size;
    UNICODE_STRING CatalogDirectoryPath;
    SE_FILE_CACHE_CLAIM_INFORMATION OriginClaimInfo;

} SE_SET_FILE_CACHE_INFORMATION, *PSE_SET_FILE_CACHE_INFORMATION;

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetCachedSigningLevel2(
    _In_ ULONG Flags,
    _In_ SE_SIGNING_LEVEL InputSigningLevel,
    _In_reads_(SourceFileCount) PHANDLE SourceFiles,
    _In_ ULONG SourceFileCount,
    _In_opt_ HANDLE TargetFile,
    _In_opt_ SE_SET_FILE_CACHE_INFORMATION* CacheInformation
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwSetCachedSigningLevel2(
    _In_ ULONG Flags,
    _In_ SE_SIGNING_LEVEL InputSigningLevel,
    _In_reads_(SourceFileCount) PHANDLE SourceFiles,
    _In_ ULONG SourceFileCount,
    _In_opt_ HANDLE TargetFile,
    _In_opt_ SE_SET_FILE_CACHE_INFORMATION* CacheInformation
);
#endif // (NTDDI_VERSION >= NTDDI_WIN10_RS1)

/**
 * The NtGetCachedSigningLevel routine retrieves the cached signing level of a file.
 *
 * \param File Handle to a file.
 * \param Flags Pointer to the flags set on the file.
 * \param SigningLevel Pointer to the signing level.
 * \param Thumbprint Pointer to the thumbprint.
 * \param ThumbprintSize Pointer to the thumbprint size.
 * \param ThumbprintAlgorithm Pointer to the thumbprint algorithm.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/securitybaseapi/nf-securitybaseapi-getcachedsigninglevel
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtGetCachedSigningLevel(
    _In_ HANDLE File,
    _Out_ PULONG Flags,
    _Out_ PSE_SIGNING_LEVEL SigningLevel,
    _Out_writes_bytes_to_opt_(*ThumbprintSize, *ThumbprintSize) PUCHAR Thumbprint,
    _Inout_opt_ PULONG ThumbprintSize,
    _Out_opt_ PULONG ThumbprintAlgorithm
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwGetCachedSigningLevel(
    _In_ HANDLE File,
    _Out_ PULONG Flags,
    _Out_ PSE_SIGNING_LEVEL SigningLevel,
    _Out_writes_bytes_to_opt_(*ThumbprintSize, *ThumbprintSize) PUCHAR Thumbprint,
    _Inout_opt_ PULONG ThumbprintSize,
    _Out_opt_ PULONG ThumbprintAlgorithm
);
#endif // NTDDI_VERSION >= NTDDI_WIN8

#if (NTDDI_VERSION >= NTDDI_WIN10_RS2)
// rev
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCompareSigningLevels(
    _In_ SE_SIGNING_LEVEL FirstSigningLevel,
    _In_ SE_SIGNING_LEVEL SecondSigningLevel
);

// rev
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCompareSigningLevels(
    _In_ SE_SIGNING_LEVEL FirstSigningLevel,
    _In_ SE_SIGNING_LEVEL SecondSigningLevel
);
#endif // NTDDI_VERSION >= NTDDI_WIN10_RS2

//
// Audit alarm
//

/**
 * The NtAccessCheckAndAuditAlarm routine determines whether a security descriptor grants a specified set of access rights to the client being impersonated by the calling thread.
 * If the security descriptor has a SACL with ACEs that apply to the client, the function generates any necessary audit messages in the security event log.
 *
 * \param SubsystemName A pointer to a null-terminated string specifying the name of the subsystem calling the function.
 * \param HandleId A pointer to a unique value representing the client's handle to the object.
 * \param ObjectTypeName A pointer to a null-terminated string specifying the type of object being created or accessed.
 * \param ObjectName A pointer to a null-terminated string specifying the name of the object being created or accessed.
 * \param SecurityDescriptor A pointer to the SECURITY_DESCRIPTOR structure against which access is checked.
 * \param DesiredAccess Access mask that specifies the access rights to check. This mask must have been mapped by the MapGenericMask function to contain no generic access rights.
 * \param GenericMapping A pointer to the GENERIC_MAPPING structure associated with the object for which access is being checked.
 * \param ObjectCreation Specifies a flag that determines whether the calling application will create a new object when access is granted.
 * \param GrantedAccess A pointer to an access mask that receives the granted access rights.
 * \param AccessStatus A pointer to a variable that receives the results of the access check.
 * \param GenerateOnClose A pointer to a flag set by the audit-generation routine when the function returns.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-accesscheckandauditalarma
 */
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAccessCheckAndAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_ PUNICODE_STRING ObjectName,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ BOOLEAN ObjectCreation,
    _Out_ PACCESS_MASK GrantedAccess,
    _Out_ PNTSTATUS AccessStatus,
    _Out_ PBOOLEAN GenerateOnClose
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAccessCheckAndAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_ PUNICODE_STRING ObjectName,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ BOOLEAN ObjectCreation,
    _Out_ PACCESS_MASK GrantedAccess,
    _Out_ PNTSTATUS AccessStatus,
    _Out_ PBOOLEAN GenerateOnClose
);

/**
 * The NtAccessCheckByTypeAndAuditAlarm routine determines whether a security descriptor grants a specified set of access rights to the client being impersonated by the calling thread.
 * If the security descriptor has a SACL with ACEs that apply to the client, the function generates any necessary audit messages in the security event log.
 *
 * \param SubsystemName A pointer to a UNICODE_STRING specifying the name of the subsystem calling the function.
 * \param HandleId A pointer to a unique value representing the client's handle to the object.
 * \param ObjectTypeName A pointer to a UNICODE_STRING specifying the type of object being created or accessed.
 * \param ObjectName A pointer to a UNICODE_STRING specifying the name of the object being created or accessed.
 * \param SecurityDescriptor A pointer to the SECURITY_DESCRIPTOR structure against which access is checked.
 * \param PrincipalSelfSid A pointer to a SID structure representing the principal self SID, or NULL.
 * \param DesiredAccess Access mask that specifies the access rights to check. This mask must have been mapped by the MapGenericMask function to contain no generic access rights.
 * \param AuditType Specifies the type of audit event to be generated.
 * \param Flags Audit event flags.
 * \param ObjectTypeList A pointer to an array of OBJECT_TYPE_LIST structures that specify the hierarchy of object types for the object being accessed.
 * \param ObjectTypeListLength The number of elements in the ObjectTypeList array.
 * \param GenericMapping A pointer to the GENERIC_MAPPING structure associated with the object for which access is being checked.
 * \param ObjectCreation Specifies a flag that determines whether the calling application will create a new object when access is granted.
 * \param GrantedAccess A pointer to an access mask that receives the granted access rights.
 * \param AccessStatus A pointer to a variable that receives the results of the access check.
 * \param GenerateOnClose A pointer to a flag set by the audit-generation routine when the function returns.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-accesscheckbytypeandauditalarma
 */
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAccessCheckByTypeAndAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_ PUNICODE_STRING ObjectName,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID PrincipalSelfSid,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ AUDIT_EVENT_TYPE AuditType,
    _In_ ULONG Flags,
    _In_reads_opt_(ObjectTypeListLength) POBJECT_TYPE_LIST ObjectTypeList,
    _In_ ULONG ObjectTypeListLength,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ BOOLEAN ObjectCreation,
    _Out_ PACCESS_MASK GrantedAccess,
    _Out_ PNTSTATUS AccessStatus,
    _Out_ PBOOLEAN GenerateOnClose
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAccessCheckByTypeAndAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_ PUNICODE_STRING ObjectName,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID PrincipalSelfSid,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ AUDIT_EVENT_TYPE AuditType,
    _In_ ULONG Flags,
    _In_reads_opt_(ObjectTypeListLength) POBJECT_TYPE_LIST ObjectTypeList,
    _In_ ULONG ObjectTypeListLength,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ BOOLEAN ObjectCreation,
    _Out_ PACCESS_MASK GrantedAccess,
    _Out_ PNTSTATUS AccessStatus,
    _Out_ PBOOLEAN GenerateOnClose
);

/**
 * The NtAccessCheckByTypeResultListAndAuditAlarm routine determines whether a security descriptor grants a specified set of access rights to the client being impersonated by the calling thread.
 * It also generates audit messages for each object type in the hierarchy, and returns the results for each object type in a list.
 *
 * \param SubsystemName A pointer to a UNICODE_STRING specifying the name of the subsystem calling the function.
 * \param HandleId A pointer to a unique value representing the client's handle to the object.
 * \param ObjectTypeName A pointer to a UNICODE_STRING specifying the type of object being created or accessed.
 * \param ObjectName A pointer to a UNICODE_STRING specifying the name of the object being created or accessed.
 * \param SecurityDescriptor A pointer to the SECURITY_DESCRIPTOR structure against which access is checked.
 * \param PrincipalSelfSid A pointer to a SID structure representing the principal self SID, or NULL.
 * \param DesiredAccess Access mask that specifies the access rights to check.
 * \param AuditType Specifies the type of audit event to be generated.
 * \param Flags Audit event flags.
 * \param ObjectTypeList A pointer to an array of OBJECT_TYPE_LIST structures that specify the hierarchy of object types for the object being accessed.
 * \param ObjectTypeListLength The number of elements in the ObjectTypeList array.
 * \param GenericMapping A pointer to the GENERIC_MAPPING structure associated with the object for which access is being checked.
 * \param ObjectCreation Specifies a flag that determines whether the calling application will create a new object when access is granted.
 * \param GrantedAccess A pointer to an array of access masks that receive the granted access rights for each object type.
 * \param AccessStatus A pointer to an array of NTSTATUS values that receive the results of the access check for each object type.
 * \param GenerateOnClose A pointer to a flag set by the audit-generation routine when the function returns.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-accesscheckbytyperesultlistandauditalarma
 */
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAccessCheckByTypeResultListAndAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_ PUNICODE_STRING ObjectName,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID PrincipalSelfSid,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ AUDIT_EVENT_TYPE AuditType,
    _In_ ULONG Flags,
    _In_reads_opt_(ObjectTypeListLength) POBJECT_TYPE_LIST ObjectTypeList,
    _In_ ULONG ObjectTypeListLength,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ BOOLEAN ObjectCreation,
    _Out_writes_(ObjectTypeListLength) PACCESS_MASK GrantedAccess,
    _Out_writes_(ObjectTypeListLength) PNTSTATUS AccessStatus,
    _Out_ PBOOLEAN GenerateOnClose
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAccessCheckByTypeResultListAndAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_ PUNICODE_STRING ObjectName,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID PrincipalSelfSid,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ AUDIT_EVENT_TYPE AuditType,
    _In_ ULONG Flags,
    _In_reads_opt_(ObjectTypeListLength) POBJECT_TYPE_LIST ObjectTypeList,
    _In_ ULONG ObjectTypeListLength,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ BOOLEAN ObjectCreation,
    _Out_writes_(ObjectTypeListLength) PACCESS_MASK GrantedAccess,
    _Out_writes_(ObjectTypeListLength) PNTSTATUS AccessStatus,
    _Out_ PBOOLEAN GenerateOnClose
);

/**
 * The NtAccessCheckByTypeResultListAndAuditAlarmByHandle routine determines whether a security descriptor grants a specified set of access rights to the client represented by a specified access token.
 * It also generates audit messages for each object type in the hierarchy, and returns the results for each object type in a list.
 *
 * \param SubsystemName A pointer to a UNICODE_STRING specifying the name of the subsystem calling the function.
 * \param HandleId A pointer to a unique value representing the client's handle to the object.
 * \param ClientToken Handle to the access token representing the client.
 * \param ObjectTypeName A pointer to a UNICODE_STRING specifying the type of object being created or accessed.
 * \param ObjectName A pointer to a UNICODE_STRING specifying the name of the object being created or accessed.
 * \param SecurityDescriptor A pointer to the SECURITY_DESCRIPTOR structure against which access is checked.
 * \param PrincipalSelfSid A pointer to a SID structure representing the principal self SID, or NULL.
 * \param DesiredAccess Access mask that specifies the access rights to check.
 * \param AuditType Specifies the type of audit event to be generated.
 * \param Flags Audit event flags.
 * \param ObjectTypeList A pointer to an array of OBJECT_TYPE_LIST structures that specify the hierarchy of object types for the object being accessed.
 * \param ObjectTypeListLength The number of elements in the ObjectTypeList array.
 * \param GenericMapping A pointer to the GENERIC_MAPPING structure associated with the object for which access is being checked.
 * \param ObjectCreation Specifies a flag that determines whether the calling application will create a new object when access is granted.
 * \param GrantedAccess A pointer to an array of access masks that receive the granted access rights for each object type.
 * \param AccessStatus A pointer to an array of NTSTATUS values that receive the results of the access check for each object type.
 * \param GenerateOnClose A pointer to a flag set by the audit-generation routine when the function returns.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-accesscheckbytyperesultlistandauditalarmbyhandlea
 */
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAccessCheckByTypeResultListAndAuditAlarmByHandle(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ HANDLE ClientToken,
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_ PUNICODE_STRING ObjectName,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID PrincipalSelfSid,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ AUDIT_EVENT_TYPE AuditType,
    _In_ ULONG Flags,
    _In_reads_opt_(ObjectTypeListLength) POBJECT_TYPE_LIST ObjectTypeList,
    _In_ ULONG ObjectTypeListLength,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ BOOLEAN ObjectCreation,
    _Out_writes_(ObjectTypeListLength) PACCESS_MASK GrantedAccess,
    _Out_writes_(ObjectTypeListLength) PNTSTATUS AccessStatus,
    _Out_ PBOOLEAN GenerateOnClose
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAccessCheckByTypeResultListAndAuditAlarmByHandle(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ HANDLE ClientToken,
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_ PUNICODE_STRING ObjectName,
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID PrincipalSelfSid,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ AUDIT_EVENT_TYPE AuditType,
    _In_ ULONG Flags,
    _In_reads_opt_(ObjectTypeListLength) POBJECT_TYPE_LIST ObjectTypeList,
    _In_ ULONG ObjectTypeListLength,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_ BOOLEAN ObjectCreation,
    _Out_writes_(ObjectTypeListLength) PACCESS_MASK GrantedAccess,
    _Out_writes_(ObjectTypeListLength) PNTSTATUS AccessStatus,
    _Out_ PBOOLEAN GenerateOnClose
);

/**
 * The NtOpenObjectAuditAlarm routine generates an audit message in the security event log when an object is opened.
 *
 * \param SubsystemName A pointer to a UNICODE_STRING specifying the name of the subsystem calling the function.
 * \param HandleId A pointer to a unique value representing the client's handle to the object.
 * \param ObjectTypeName A pointer to a UNICODE_STRING specifying the type of object being opened.
 * \param ObjectName A pointer to a UNICODE_STRING specifying the name of the object being opened.
 * \param SecurityDescriptor A pointer to the SECURITY_DESCRIPTOR structure for the object.
 * \param ClientToken Handle to the access token representing the client.
 * \param DesiredAccess Access mask that specifies the access rights requested.
 * \param GrantedAccess Access mask that specifies the access rights granted.
 * \param Privileges A pointer to a PRIVILEGE_SET structure that specifies the privileges used to gain access, or NULL.
 * \param ObjectCreation Specifies a flag that determines whether the object is being created.
 * \param AccessGranted Specifies a flag that determines whether access was granted.
 * \param GenerateOnClose A pointer to a flag set by the audit-generation routine when the function returns.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-openobjectauditalarma
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenObjectAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_ PUNICODE_STRING ObjectName,
    _In_opt_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ HANDLE ClientToken,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ACCESS_MASK GrantedAccess,
    _In_opt_ PPRIVILEGE_SET Privileges,
    _In_ BOOLEAN ObjectCreation,
    _In_ BOOLEAN AccessGranted,
    _Out_ PBOOLEAN GenerateOnClose
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwOpenObjectAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ PUNICODE_STRING ObjectTypeName,
    _In_ PUNICODE_STRING ObjectName,
    _In_opt_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ HANDLE ClientToken,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ACCESS_MASK GrantedAccess,
    _In_opt_ PPRIVILEGE_SET Privileges,
    _In_ BOOLEAN ObjectCreation,
    _In_ BOOLEAN AccessGranted,
    _Out_ PBOOLEAN GenerateOnClose
);

/**
 * The NtPrivilegeObjectAuditAlarm routine generates an audit message in the security event log when a privilege is used to access an object.
 *
 * \param SubsystemName A pointer to a UNICODE_STRING specifying the name of the subsystem calling the function.
 * \param HandleId A pointer to a unique value representing the client's handle to the object.
 * \param ClientToken Handle to the access token representing the client.
 * \param DesiredAccess Access mask that specifies the access rights requested.
 * \param Privileges A pointer to a PRIVILEGE_SET structure that specifies the privileges used to gain access.
 * \param AccessGranted Specifies a flag that determines whether access was granted.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-privilegeobjectauditalarma
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtPrivilegeObjectAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ HANDLE ClientToken,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ PPRIVILEGE_SET Privileges,
    _In_ BOOLEAN AccessGranted
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwPrivilegeObjectAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ HANDLE ClientToken,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ PPRIVILEGE_SET Privileges,
    _In_ BOOLEAN AccessGranted
);

/**
 * The NtCloseObjectAuditAlarm routine generates an audit message in the security event log when an object handle is closed.
 *
 * \param SubsystemName A pointer to a UNICODE_STRING specifying the name of the subsystem calling the function.
 * \param HandleId A pointer to a unique value representing the client's handle to the object.
 * \param GenerateOnClose Specifies a flag that determines whether to generate an audit on close.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-closeobjectauditalarma
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCloseObjectAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ BOOLEAN GenerateOnClose
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCloseObjectAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ BOOLEAN GenerateOnClose
);

/**
 * The NtDeleteObjectAuditAlarm routine generates an audit message in the security event log when an object is deleted.
 *
 * \param SubsystemName A pointer to a UNICODE_STRING specifying the name of the subsystem calling the function.
 * \param HandleId A pointer to a unique value representing the client's handle to the object.
 * \param GenerateOnClose Specifies a flag that determines whether to generate an audit on close.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-deleteobjectauditalarma
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtDeleteObjectAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ BOOLEAN GenerateOnClose
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwDeleteObjectAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_opt_ PVOID HandleId,
    _In_ BOOLEAN GenerateOnClose
);

/**
 * The NtPrivilegedServiceAuditAlarm routine generates an audit message in the security event log when a privileged service is accessed.
 *
 * \param SubsystemName A pointer to a UNICODE_STRING specifying the name of the subsystem calling the function.
 * \param ServiceName A pointer to a UNICODE_STRING specifying the name of the service being accessed.
 * \param ClientToken Handle to the access token representing the client.
 * \param Privileges A pointer to a PRIVILEGE_SET structure that specifies the privileges used to access the service.
 * \param AccessGranted Specifies a flag that determines whether access was granted.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-privilegedserviceauditalarma
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtPrivilegedServiceAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_ PUNICODE_STRING ServiceName,
    _In_ HANDLE ClientToken,
    _In_ PPRIVILEGE_SET Privileges,
    _In_ BOOLEAN AccessGranted
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwPrivilegedServiceAuditAlarm(
    _In_ PUNICODE_STRING SubsystemName,
    _In_ PUNICODE_STRING ServiceName,
    _In_ HANDLE ClientToken,
    _In_ PPRIVILEGE_SET Privileges,
    _In_ BOOLEAN AccessGranted
);

// LSA

#ifndef _KERNEL_MODE

#include <NTSecAPI.h>

#else // _KERNEL_MODE

//#pragma comment(lib, "ksecdd.lib")

typedef struct _LSA_LAST_INTER_LOGON_INFO {
    LARGE_INTEGER LastSuccessfulLogon;
    LARGE_INTEGER LastFailedLogon;
    ULONG FailedAttemptCountSinceLastSuccessfulLogon;
} LSA_LAST_INTER_LOGON_INFO, * PLSA_LAST_INTER_LOGON_INFO;

typedef struct _SECURITY_LOGON_SESSION_DATA {
    ULONG               Size;
    LUID                LogonId;
    LSA_UNICODE_STRING  UserName;
    LSA_UNICODE_STRING  LogonDomain;
    LSA_UNICODE_STRING  AuthenticationPackage;
    ULONG               LogonType;
    ULONG               Session;
    PSID                Sid;
    LARGE_INTEGER       LogonTime;

    //
    // new for whistler:
    //

    LSA_UNICODE_STRING  LogonServer;
    LSA_UNICODE_STRING  DnsDomainName;
    LSA_UNICODE_STRING  Upn;

    //
    // new for LH
    //

    ULONG UserFlags;

    LSA_LAST_INTER_LOGON_INFO LastLogonInfo;
    LSA_UNICODE_STRING LogonScript;
    LSA_UNICODE_STRING ProfilePath;
    LSA_UNICODE_STRING HomeDirectory;
    LSA_UNICODE_STRING HomeDirectoryDrive;

    LARGE_INTEGER LogoffTime;
    LARGE_INTEGER KickOffTime;
    LARGE_INTEGER PasswordLastSet;
    LARGE_INTEGER PasswordCanChange;
    LARGE_INTEGER PasswordMustChange;

} SECURITY_LOGON_SESSION_DATA, * PSECURITY_LOGON_SESSION_DATA;

NTKERNELAPI
NTSTATUS
NTAPI
LsaEnumerateLogonSessions(
    _Out_ PULONG  LogonSessionCount,
    _Out_ PLUID* LogonSessionList
);

NTKERNELAPI
NTSTATUS
NTAPI
LsaGetLogonSessionData(
    _In_ PLUID    LogonId,
    _Out_ PSECURITY_LOGON_SESSION_DATA* LogonSessionData
);

FORCEINLINE
_IRQL_requires_same_
NTSTATUS
NTAPI
LsaFreeReturnBuffer(
    _In_ PVOID Buffer
)
{
    if (Buffer)
        return ExFreePool(Buffer), STATUS_SUCCESS;
    else
        return STATUS_INVALID_ADDRESS;
}

#endif // !_KERNEL_MODE

//
// Only Kernel
//

#ifdef _KERNEL_MODE

// Dacl

extern PACL SeSystemDefaultDacl;

// Token 

NTKERNELAPI
SECURITY_IMPERSONATION_LEVEL
NTAPI
SeTokenImpersonationLevel(
    __in PACCESS_TOKEN Token
);

#endif // _KERNEL_MODE


VEIL_END()

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
