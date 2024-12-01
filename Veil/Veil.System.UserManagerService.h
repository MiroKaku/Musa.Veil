/*
 * PROJECT:   Veil
 * FILE:      Veil.System.WindowStation.h
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


// private
typedef struct _SESSION_USER_CONTEXT
{
    ULONGLONG ContextToken;
    ULONG SessionId;
    ULONG Reserved;
} SESSION_USER_CONTEXT, * PSESSION_USER_CONTEXT;

// private
typedef struct _CRED_PROV_CREDENTIAL
{
    ULONG Flags;
    ULONG AuthenticationPackage;
    ULONG Size;
    PVOID Information;
} CRED_PROV_CREDENTIAL, * PCRED_PROV_CREDENTIAL;

#define USERMGRAPI DECLSPEC_IMPORT

// Contexts

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)

// rev
USERMGRAPI
VOID
WINAPI
UMgrFreeSessionUsers(
    _In_ _Post_invalid_ PSESSION_USER_CONTEXT SessionUsers
);

// rev
USERMGRAPI
HRESULT
WINAPI
UMgrEnumerateSessionUsers(
    _Out_ PULONG Count,
    _Outptr_ PSESSION_USER_CONTEXT* SessionUsers
);

// rev
USERMGRAPI
HRESULT
WINAPI
UMgrQueryUserContext(
    _In_ HANDLE TokenHandle,
    _Out_ PULONGLONG ContextToken
);

// rev
USERMGRAPI
HRESULT
WINAPI
UMgrQueryUserContextFromSid(
    _In_ PCWSTR SidString,
    _Out_ PULONGLONG ContextToken
);

// rev
USERMGRAPI
HRESULT
WINAPI
UMgrQueryUserContextFromName(
    _In_ PCWSTR UserName,
    _Out_ PULONGLONG ContextToken
);

#endif

// Tokens

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)

// rev
USERMGRAPI
HRESULT
WINAPI
UMgrQueryDefaultAccountToken(
    _Out_ PHANDLE TokenHandle
);

// rev
USERMGRAPI
HRESULT
WINAPI
UMgrQuerySessionUserToken(
    _In_ ULONG SessionId,
    _Out_ PHANDLE TokenHandle
);

// rev
USERMGRAPI
HRESULT
WINAPI
UMgrQueryUserToken(
    _In_ ULONGLONG Context,
    _Out_ PHANDLE TokenHandle
);

// rev
USERMGRAPI
HRESULT
WINAPI
UMgrQueryUserTokenFromSid(
    _In_ PCWSTR SidString,
    _Out_ PHANDLE TokenHandle
);

// rev
USERMGRAPI
HRESULT
WINAPI
UMgrQueryUserTokenFromName(
    _In_ PCWSTR UserName,
    _Out_ PHANDLE TokenHandle
);

// rev
USERMGRAPI
HRESULT
WINAPI
UMgrGetConstrainedUserToken(
    _In_opt_ HANDLE InputTokenHandle,
    _In_ ULONGLONG Context,
    _In_opt_ PSECURITY_CAPABILITIES Capabilities,
    _Out_ _Ret_maybenull_ PHANDLE OutputTokenHandle
);

#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_TH2)

// rev
USERMGRAPI
HRESULT
WINAPI
UMgrChangeSessionUserToken(
    _In_ HANDLE TokenHandle
);

// rev
USERMGRAPI
HRESULT
WINAPI
UMgrGetImpersonationTokenForContext(
    _In_ HANDLE InputTokenHandle,
    _In_ ULONGLONG Context,
    _Out_ PHANDLE OutputTokenHandle
);

#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)

// rev
USERMGRAPI
HRESULT
WINAPI
UMgrGetSessionActiveShellUserToken(
    _In_ ULONG SessionId,
    _Out_ PHANDLE TokenHandle
);

#endif

// Single-session SKU

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)

// rev
USERMGRAPI
HRESULT
WINAPI
UMgrOpenProcessTokenForQuery(
    _In_ ULONG ProcessId,
    _Out_ PHANDLE TokenHandle
);

// rev
USERMGRAPI
HRESULT
WINAPI
UMgrOpenProcessHandleForAccess(
    _In_ ACCESS_MASK DesiredAccess,
    _In_ ULONG ProcessId,
    _Out_ PHANDLE ProcessHandle
);

#endif

// Credentials

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)

// rev
USERMGRAPI
HRESULT
WINAPI
UMgrFreeUserCredentials(
    _In_ PCRED_PROV_CREDENTIAL Credentials
);

// rev
USERMGRAPI
HRESULT
WINAPI
UMgrGetCachedCredentials(
    _In_ PSID Sid,
    _Outptr_ PCRED_PROV_CREDENTIAL* Credentials
);

#endif


#endif // !_KERNEL_MODE

VEIL_END()

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
