/*
 * PROJECT:   Veil
 * FILE:      Veil.System.SxS.h
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


VEIL_BEGIN()

#define ACTIVATION_CONTEXT_DATA_MAGIC           ('xtcA')
#define ACTIVATION_CONTEXT_DATA_FORMAT_WHISTLER 1

#define ACTIVATION_CONTEXT_FLAG_NO_INHERIT      0x00000001

#if defined(_KERNEL_MODE)
typedef enum _ACTCTX_REQUESTED_RUN_LEVEL
{
    ACTCTX_RUN_LEVEL_UNSPECIFIED = 0,
    ACTCTX_RUN_LEVEL_AS_INVOKER,
    ACTCTX_RUN_LEVEL_HIGHEST_AVAILABLE,
    ACTCTX_RUN_LEVEL_REQUIRE_ADMIN,
    ACTCTX_RUN_LEVEL_NUMBERS
} ACTCTX_REQUESTED_RUN_LEVEL;

typedef enum _ACTCTX_COMPATIBILITY_ELEMENT_TYPE
{
    ACTCTX_COMPATIBILITY_ELEMENT_TYPE_UNKNOWN = 0,
    ACTCTX_COMPATIBILITY_ELEMENT_TYPE_OS,
    ACTCTX_COMPATIBILITY_ELEMENT_TYPE_MITIGATION,
    ACTCTX_COMPATIBILITY_ELEMENT_TYPE_MAXVERSIONTESTED
} ACTCTX_COMPATIBILITY_ELEMENT_TYPE;
#endif // _KERNEL_MODE

#include <pshpack4.h>

typedef struct _ACTIVATION_CONTEXT_DATA
{
    ULONG Magic;
    ULONG HeaderSize;
    ULONG FormatVersion;
    ULONG TotalSize;
    ULONG DefaultTocOffset;     // to ACTIVATION_CONTEXT_DATA_TOC_HEADER
    ULONG ExtendedTocOffset;    // to ACTIVATION_CONTEXT_DATA_EXTENDED_TOC_HEADER
    ULONG AssemblyRosterOffset; // to ACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_HEADER
    ULONG Flags;                // ACTIVATION_CONTEXT_FLAG_*
} ACTIVATION_CONTEXT_DATA, * PACTIVATION_CONTEXT_DATA;

#define ACTIVATION_CONTEXT_DATA_TOC_HEADER_DENSE    0x00000001
#define ACTIVATION_CONTEXT_DATA_TOC_HEADER_INORDER  0x00000002

typedef struct _ACTIVATION_CONTEXT_DATA_TOC_HEADER
{
    ULONG HeaderSize;
    ULONG EntryCount;
    ULONG FirstEntryOffset; // to ACTIVATION_CONTEXT_DATA_TOC_ENTRY[], from ACTIVATION_CONTEXT_DATA base
    ULONG Flags;            // ACTIVATION_CONTEXT_DATA_TOC_HEADER_*
} ACTIVATION_CONTEXT_DATA_TOC_HEADER, * PACTIVATION_CONTEXT_DATA_TOC_HEADER;

typedef struct _ACTIVATION_CONTEXT_DATA_TOC_ENTRY
{
    ULONG Id;       // ACTIVATION_CONTEXT_SECTION_*
    ULONG Offset;   // to ACTIVATION_CONTEXT_*_SECTION_HEADER, from ACTIVATION_CONTEXT_DATA base
    ULONG Length;
    ULONG Format;   // ACTIVATION_CONTEXT_SECTION_FORMAT_*
} ACTIVATION_CONTEXT_DATA_TOC_ENTRY, * PACTIVATION_CONTEXT_DATA_TOC_ENTRY;

typedef struct _ACTIVATION_CONTEXT_DATA_EXTENDED_TOC_HEADER
{
    ULONG HeaderSize;
    ULONG EntryCount;
    ULONG FirstEntryOffset; // to ACTIVATION_CONTEXT_DATA_EXTENDED_TOC_ENTRY[], from ACTIVATION_CONTEXT_DATA base
    ULONG Flags;
} ACTIVATION_CONTEXT_DATA_EXTENDED_TOC_HEADER, * PACTIVATION_CONTEXT_DATA_EXTENDED_TOC_HEADER;

typedef struct _ACTIVATION_CONTEXT_DATA_EXTENDED_TOC_ENTRY
{
    GUID ExtensionGuid;
    ULONG TocOffset; // to ACTIVATION_CONTEXT_DATA_TOC_HEADER, from ACTIVATION_CONTEXT_DATA base
    ULONG Length;
} ACTIVATION_CONTEXT_DATA_EXTENDED_TOC_ENTRY, * PACTIVATION_CONTEXT_DATA_EXTENDED_TOC_ENTRY;

#define ACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_ENTRY_INVALID   0x00000001
#define ACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_ENTRY_ROOT      0x00000002

typedef struct _ACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_HEADER
{
    ULONG HeaderSize;
    ULONG HashAlgorithm;    // HASH_STRING_ALGORITHM_*
    ULONG EntryCount;
    ULONG FirstEntryOffset; // to ACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_ENTRY[], from ACTIVATION_CONTEXT_DATA base
    ULONG AssemblyInformationSectionOffset; // to resolve section-relative offsets
} ACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_HEADER, * PACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_HEADER;

typedef struct _ACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_ENTRY
{
    ULONG Flags;
    ULONG PseudoKey;
    ULONG AssemblyNameOffset;        // to WCHAR[], from ACTIVATION_CONTEXT_DATA base
    ULONG AssemblyNameLength;
    ULONG AssemblyInformationOffset; // to ACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION, from ACTIVATION_CONTEXT_DATA base
    ULONG AssemblyInformationLength;
} ACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_ENTRY, * PACTIVATION_CONTEXT_DATA_ASSEMBLY_ROSTER_ENTRY;

#define ACTIVATION_CONTEXT_SECTION_FORMAT_UNKNOWN       0
#define ACTIVATION_CONTEXT_SECTION_FORMAT_STRING_TABLE  1 // ACTIVATION_CONTEXT_STRING_SECTION_HEADER
#define ACTIVATION_CONTEXT_SECTION_FORMAT_GUID_TABLE    2 // ACTIVATION_CONTEXT_GUID_SECTION_HEADER

#define ACTIVATION_CONTEXT_STRING_SECTION_MAGIC             ('dHsS')
#define ACTIVATION_CONTEXT_STRING_SECTION_FORMAT_WHISTLER   1

#define ACTIVATION_CONTEXT_STRING_SECTION_CASE_INSENSITIVE           0x00000001
#define ACTIVATION_CONTEXT_STRING_SECTION_ENTRIES_IN_PSEUDOKEY_ORDER 0x00000002

typedef struct _ACTIVATION_CONTEXT_STRING_SECTION_HEADER
{
    ULONG Magic;
    ULONG HeaderSize;
    ULONG FormatVersion;
    ULONG DataFormatVersion;
    ULONG Flags;                 // ACTIVATION_CONTEXT_STRING_SECTION_*
    ULONG ElementCount;
    ULONG ElementListOffset;     // to ACTIVATION_CONTEXT_STRING_SECTION_ENTRY[], from this struct base
    ULONG HashAlgorithm;         // HASH_STRING_ALGORITHM_*
    ULONG SearchStructureOffset; // to ACTIVATION_CONTEXT_STRING_SECTION_HASH_TABLE, from this struct base
    ULONG UserDataOffset;        // to data depending on section Id, from this struct base
    ULONG UserDataSize;
} ACTIVATION_CONTEXT_STRING_SECTION_HEADER, * PACTIVATION_CONTEXT_STRING_SECTION_HEADER;

typedef struct _ACTIVATION_CONTEXT_STRING_SECTION_ENTRY
{
    ULONG PseudoKey;
    ULONG KeyOffset; // to WCHAR[], from section header
    ULONG KeyLength;
    ULONG Offset;    // to data depending on section Id, from section header
    ULONG Length;
    ULONG AssemblyRosterIndex;
} ACTIVATION_CONTEXT_STRING_SECTION_ENTRY, * PACTIVATION_CONTEXT_STRING_SECTION_ENTRY;

typedef struct _ACTIVATION_CONTEXT_STRING_SECTION_HASH_TABLE
{
    ULONG BucketTableEntryCount;
    ULONG BucketTableOffset; // to ACTIVATION_CONTEXT_STRING_SECTION_HASH_BUCKET[], from section header
} ACTIVATION_CONTEXT_STRING_SECTION_HASH_TABLE, * PACTIVATION_CONTEXT_STRING_SECTION_HASH_TABLE;

typedef struct _ACTIVATION_CONTEXT_STRING_SECTION_HASH_BUCKET
{
    ULONG ChainCount;
    ULONG ChainOffset; // to LONG[], from section header
} ACTIVATION_CONTEXT_STRING_SECTION_HASH_BUCKET, * PACTIVATION_CONTEXT_STRING_SECTION_HASH_BUCKET;

#define ACTIVATION_CONTEXT_GUID_SECTION_MAGIC           ('dHsG')
#define ACTIVATION_CONTEXT_GUID_SECTION_FORMAT_WHISTLER 1

#define ACTIVATION_CONTEXT_GUID_SECTION_ENTRIES_IN_ORDER 0x00000001

typedef struct _ACTIVATION_CONTEXT_GUID_SECTION_HEADER
{
    ULONG Magic;
    ULONG HeaderSize;
    ULONG FormatVersion;
    ULONG DataFormatVersion;
    ULONG Flags;                 // ACTIVATION_CONTEXT_GUID_SECTION_*
    ULONG ElementCount;
    ULONG ElementListOffset;     // to ACTIVATION_CONTEXT_GUID_SECTION_ENTRY[], from this struct base
    ULONG SearchStructureOffset; // to ACTIVATION_CONTEXT_GUID_SECTION_HASH_TABLE, from this struct base
    ULONG UserDataOffset;        // to data depending on section Id, from this struct base
    ULONG UserDataSize;
} ACTIVATION_CONTEXT_GUID_SECTION_HEADER, * PACTIVATION_CONTEXT_GUID_SECTION_HEADER;

typedef struct _ACTIVATION_CONTEXT_GUID_SECTION_ENTRY
{
    GUID Guid;
    ULONG Offset; // to data depending on section Id, from section header
    ULONG Length;
    ULONG AssemblyRosterIndex;
} ACTIVATION_CONTEXT_GUID_SECTION_ENTRY, * PACTIVATION_CONTEXT_GUID_SECTION_ENTRY;

typedef struct _ACTIVATION_CONTEXT_GUID_SECTION_HASH_TABLE
{
    ULONG BucketTableEntryCount;
    ULONG BucketTableOffset; // to ACTIVATION_CONTEXT_GUID_SECTION_HASH_BUCKET, from section header
} ACTIVATION_CONTEXT_GUID_SECTION_HASH_TABLE, * PACTIVATION_CONTEXT_GUID_SECTION_HASH_TABLE;

typedef struct _ACTIVATION_CONTEXT_GUID_SECTION_HASH_BUCKET
{
    ULONG ChainCount;
    ULONG ChainOffset; // to LONG[], from section header
} ACTIVATION_CONTEXT_GUID_SECTION_HASH_BUCKET, * PACTIVATION_CONTEXT_GUID_SECTION_HASH_BUCKET;

// winnt.h - known section IDs
// #define ACTIVATION_CONTEXT_SECTION_ASSEMBLY_INFORMATION         (1) // ACTIVATION_CONTEXT_SECTION_ASSEMBLY_INFORMATION + ACTIVATION_CONTEXT_DATA_ASSEMBLY_GLOBAL_INFORMATION
// #define ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION              (2) // ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION
// #define ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION     (3) // ACTIVATION_CONTEXT_DATA_WINDOW_CLASS_REDIRECTION
// #define ACTIVATION_CONTEXT_SECTION_COM_SERVER_REDIRECTION       (4) // ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION
// #define ACTIVATION_CONTEXT_SECTION_COM_INTERFACE_REDIRECTION    (5) // ACTIVATION_CONTEXT_DATA_COM_INTERFACE_REDIRECTION
// #define ACTIVATION_CONTEXT_SECTION_COM_TYPE_LIBRARY_REDIRECTION (6) // ACTIVATION_CONTEXT_DATA_COM_TYPE_LIBRARY_REDIRECTION
// #define ACTIVATION_CONTEXT_SECTION_COM_PROGID_REDIRECTION       (7) // ACTIVATION_CONTEXT_DATA_COM_PROGID_REDIRECTION
// #define ACTIVATION_CONTEXT_SECTION_GLOBAL_OBJECT_RENAME_TABLE   (8)
// #define ACTIVATION_CONTEXT_SECTION_CLR_SURROGATES               (9) // ACTIVATION_CONTEXT_DATA_CLR_SURROGATE
// #define ACTIVATION_CONTEXT_SECTION_APPLICATION_SETTINGS         (10) // ACTIVATION_CONTEXT_DATA_APPLICATION_SETTINGS
// #define ACTIVATION_CONTEXT_SECTION_COMPATIBILITY_INFO           (11) // ACTIVATION_CONTEXT_COMPATIBILITY_INFORMATION[_LEGACY]
// #define ACTIVATION_CONTEXT_SECTION_WINRT_ACTIVATABLE_CLASSES    (12) // since 19H1

#define ACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION_FORMAT_WHISTLER 1

#define ACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION_ROOT_ASSEMBLY              0x00000001
#define ACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION_POLICY_APPLIED             0x00000002
#define ACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION_ASSEMBLY_POLICY_APPLIED    0x00000004
#define ACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION_ROOT_POLICY_APPLIED        0x00000008
#define ACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION_PRIVATE_ASSEMBLY           0x00000010

typedef struct _ACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION
{
    ULONG Size;
    ULONG Flags; // ACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION_*
    ULONG EncodedAssemblyIdentityLength;
    ULONG EncodedAssemblyIdentityOffset; // to WCHAR[], from section header
    ULONG ManifestPathType; // ACTIVATION_CONTEXT_PATH_TYPE_*
    ULONG ManifestPathLength;
    ULONG ManifestPathOffset; // to WCHAR[], from section header
    LARGE_INTEGER ManifestLastWriteTime;
    ULONG PolicyPathType; // ACTIVATION_CONTEXT_PATH_TYPE_*
    ULONG PolicyPathLength;
    ULONG PolicyPathOffset; // to WCHAR[], from section header
    LARGE_INTEGER PolicyLastWriteTime;
    ULONG MetadataSatelliteRosterIndex;
    ULONG Unused2;
    ULONG ManifestVersionMajor;
    ULONG ManifestVersionMinor;
    ULONG PolicyVersionMajor;
    ULONG PolicyVersionMinor;
    ULONG AssemblyDirectoryNameLength;
    ULONG AssemblyDirectoryNameOffset; // to WCHAR[], from section header
    ULONG NumOfFilesInAssembly;
    ULONG LanguageLength;
    ULONG LanguageOffset; // to WCHAR[], from section header
    ACTCTX_REQUESTED_RUN_LEVEL RunLevel;
    ULONG UiAccess;
} ACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION, * PACTIVATION_CONTEXT_DATA_ASSEMBLY_INFORMATION;

// via UserData
typedef struct _ACTIVATION_CONTEXT_DATA_ASSEMBLY_GLOBAL_INFORMATION
{
    ULONG Size;
    ULONG Flags;
    GUID PolicyCoherencyGuid;
    GUID PolicyOverrideGuid;
    ULONG ApplicationDirectoryPathType; // ACTIVATION_CONTEXT_PATH_TYPE_*
    ULONG ApplicationDirectoryLength;
    ULONG ApplicationDirectoryOffset; // to WCHAR[], from this struct base
    ULONG ResourceName;
} ACTIVATION_CONTEXT_DATA_ASSEMBLY_GLOBAL_INFORMATION, * PACTIVATION_CONTEXT_DATA_ASSEMBLY_GLOBAL_INFORMATION;

#define ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_FORMAT_WHISTLER 1

#define ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_INCLUDES_BASE_NAME                     0x00000001
#define ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_OMITS_ASSEMBLY_ROOT                    0x00000002
#define ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_EXPAND                                 0x00000004
#define ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_SYSTEM_DEFAULT_REDIRECTED_SYSTEM32_DLL 0x00000008

typedef struct _ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION
{
    ULONG Size;
    ULONG Flags; // ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_*
    ULONG TotalPathLength;
    ULONG PathSegmentCount;
    ULONG PathSegmentOffset; // to ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_SEGMENT[], from section header
} ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION, * PACTIVATION_CONTEXT_DATA_DLL_REDIRECTION;

typedef struct _ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_SEGMENT
{
    ULONG Length;
    ULONG Offset; // to WCHAR[], from section header
} ACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_SEGMENT, * PACTIVATION_CONTEXT_DATA_DLL_REDIRECTION_PATH_SEGMENT;

#define ACTIVATION_CONTEXT_DATA_WINDOW_CLASS_REDIRECTION_FORMAT_WHISTLER 1

typedef struct _ACTIVATION_CONTEXT_DATA_WINDOW_CLASS_REDIRECTION
{
    ULONG Size;
    ULONG Flags;
    ULONG VersionSpecificClassNameLength;
    ULONG VersionSpecificClassNameOffset; // to WHCAR[], from this struct base
    ULONG DllNameLength;
    ULONG DllNameOffset; // to WCHAR[], from section header
} ACTIVATION_CONTEXT_DATA_WINDOW_CLASS_REDIRECTION, * PACTIVATION_CONTEXT_DATA_WINDOW_CLASS_REDIRECTION;

#define ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_FORMAT_WHISTLER 1

#define ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_THREADING_MODEL_INVALID      0
#define ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_THREADING_MODEL_APARTMENT    1
#define ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_THREADING_MODEL_FREE         2
#define ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_THREADING_MODEL_SINGLE       3
#define ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_THREADING_MODEL_BOTH         4
#define ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_THREADING_MODEL_NEUTRAL      5

#define ACTIVATION_CONTEXT_DATA_COM_SERVER_MISCSTATUS_FLAG_OFFSET   8
#define ACTIVATION_CONTEXT_DATA_COM_SERVER_MISCSTATUS_HAS_DEFAULT   (0x01 << ACTIVATION_CONTEXT_DATA_COM_SERVER_MISCSTATUS_FLAG_OFFSET)
#define ACTIVATION_CONTEXT_DATA_COM_SERVER_MISCSTATUS_HAS_ICON      (0x02 << ACTIVATION_CONTEXT_DATA_COM_SERVER_MISCSTATUS_FLAG_OFFSET)
#define ACTIVATION_CONTEXT_DATA_COM_SERVER_MISCSTATUS_HAS_CONTENT   (0x04 << ACTIVATION_CONTEXT_DATA_COM_SERVER_MISCSTATUS_FLAG_OFFSET)
#define ACTIVATION_CONTEXT_DATA_COM_SERVER_MISCSTATUS_HAS_THUMBNAIL (0x08 << ACTIVATION_CONTEXT_DATA_COM_SERVER_MISCSTATUS_FLAG_OFFSET)
#define ACTIVATION_CONTEXT_DATA_COM_SERVER_MISCSTATUS_HAS_DOCPRINT  (0x10 << ACTIVATION_CONTEXT_DATA_COM_SERVER_MISCSTATUS_FLAG_OFFSET)

typedef struct _ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION
{
    ULONG Size;
    ULONG Flags;
    ULONG ThreadingModel; // ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_THREADING_MODEL_*
    GUID ReferenceClsid;
    GUID ConfiguredClsid;
    GUID ImplementedClsid;
    GUID TypeLibraryId;
    ULONG ModuleLength;
    ULONG ModuleOffset; // to WCHAR[], from section header
    ULONG ProgIdLength;
    ULONG ProgIdOffset; // to WCHAR[], from this struct base
    ULONG ShimDataLength;
    ULONG ShimDataOffset; // to ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_SHIM, from this struct base
    ULONG MiscStatusDefault;
    ULONG MiscStatusContent;
    ULONG MiscStatusThumbnail;
    ULONG MiscStatusIcon;
    ULONG MiscStatusDocPrint;
} ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION, * PACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION;

#define ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_SHIM_TYPE_OTHER      1
#define ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_SHIM_TYPE_CLR_CLASS  2

typedef struct _ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_SHIM
{
    ULONG Size;
    ULONG Flags;
    ULONG Type; // ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_SHIM_TYPE_*
    ULONG ModuleLength;
    ULONG ModuleOffset; // to WCHAR[], from section header
    ULONG TypeLength;
    ULONG TypeOffset; // to WCHAR[], from this struct base
    ULONG ShimVersionLength;
    ULONG ShimVersionOffset; // to WCHAR[], from this struct base
    ULONG DataLength;
    ULONG DataOffset; // from this struct base
} ACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_SHIM, * PACTIVATION_CONTEXT_DATA_COM_SERVER_REDIRECTION_SHIM;

#define ACTIVATION_CONTEXT_DATA_COM_INTERFACE_REDIRECTION_FORMAT_WHISTLER 1

#define ACTIVATION_CONTEXT_DATA_COM_INTERFACE_REDIRECTION_FLAG_NUM_METHODS_VALID    0x00000001
#define ACTIVATION_CONTEXT_DATA_COM_INTERFACE_REDIRECTION_FLAG_BASE_INTERFACE_VALID 0x00000002

typedef struct _ACTIVATION_CONTEXT_DATA_COM_INTERFACE_REDIRECTION
{
    ULONG Size;
    ULONG Flags; // ACTIVATION_CONTEXT_DATA_COM_INTERFACE_REDIRECTION_FLAG_*
    GUID ProxyStubClsid32;
    ULONG NumMethods;
    GUID TypeLibraryId;
    GUID BaseInterface;
    ULONG NameLength;
    ULONG NameOffset; // to WCHAR[], from this struct base
} ACTIVATION_CONTEXT_DATA_COM_INTERFACE_REDIRECTION, * PACTIVATION_CONTEXT_DATA_COM_INTERFACE_REDIRECTION;

#define ACTIVATION_CONTEXT_DATA_COM_TYPE_LIBRARY_REDIRECTION_FORMAT_WHISTLER 1

typedef struct _ACTIVATION_CONTEXT_DATA_TYPE_LIBRARY_VERSION
{
    USHORT Major;
    USHORT Minor;
} ACTIVATION_CONTEXT_DATA_TYPE_LIBRARY_VERSION, * PACTIVATION_CONTEXT_DATA_TYPE_LIBRARY_VERSION;

typedef struct _ACTIVATION_CONTEXT_DATA_COM_TYPE_LIBRARY_REDIRECTION
{
    ULONG   Size;
    ULONG   Flags;
    ULONG   NameLength;
    ULONG   NameOffset; // to WCHAR[], from section header
    USHORT  ResourceId;
    USHORT  LibraryFlags; // LIBFLAG_* oaidl.h
    ULONG   HelpDirLength;
    ULONG   HelpDirOffset; // to WCHAR[], from this struct base
    ACTIVATION_CONTEXT_DATA_TYPE_LIBRARY_VERSION Version;
} ACTIVATION_CONTEXT_DATA_COM_TYPE_LIBRARY_REDIRECTION, * PACTIVATION_CONTEXT_DATA_COM_TYPE_LIBRARY_REDIRECTION;

#define ACTIVATION_CONTEXT_DATA_COM_PROGID_REDIRECTION_FORMAT_WHISTLER 1

typedef struct _ACTIVATION_CONTEXT_DATA_COM_PROGID_REDIRECTION
{
    ULONG Size;
    ULONG Flags;
    ULONG ConfiguredClsidOffset; // to CLSID, from section header
} ACTIVATION_CONTEXT_DATA_COM_PROGID_REDIRECTION, * PACTIVATION_CONTEXT_DATA_COM_PROGID_REDIRECTION;

#define ACTIVATION_CONTEXT_DATA_CLR_SURROGATE_FORMAT_WHISTLER 1

typedef struct _ACTIVATION_CONTEXT_DATA_CLR_SURROGATE
{
    ULONG   Size;
    ULONG   Flags;
    GUID    SurrogateIdent;
    ULONG   VersionOffset;
    ULONG   VersionLength;
    ULONG   TypeNameOffset;
    ULONG   TypeNameLength; // to WCHAR[], from this struct base
} ACTIVATION_CONTEXT_DATA_CLR_SURROGATE, * PACTIVATION_CONTEXT_DATA_CLR_SURROGATE;

#define ACTIVATION_CONTEXT_DATA_APPLICATION_SETTINGS_FORMAT_LONGHORN 1

#define SXS_WINDOWS_SETTINGS_NAMESPACE      L"http://schemas.microsoft.com/SMI/2005/WindowsSettings"
#define SXS_WINDOWS_SETTINGS_2011_NAMESPACE L"http://schemas.microsoft.com/SMI/2011/WindowsSettings"
#define SXS_WINDOWS_SETTINGS_2013_NAMESPACE L"http://schemas.microsoft.com/SMI/2013/WindowsSettings"
#define SXS_WINDOWS_SETTINGS_2014_NAMESPACE L"http://schemas.microsoft.com/SMI/2014/WindowsSettings"
#define SXS_WINDOWS_SETTINGS_2016_NAMESPACE L"http://schemas.microsoft.com/SMI/2016/WindowsSettings"
#define SXS_WINDOWS_SETTINGS_2017_NAMESPACE L"http://schemas.microsoft.com/SMI/2017/WindowsSettings"
#define SXS_WINDOWS_SETTINGS_2019_NAMESPACE L"http://schemas.microsoft.com/SMI/2019/WindowsSettings"
#define SXS_WINDOWS_SETTINGS_2020_NAMESPACE L"http://schemas.microsoft.com/SMI/2020/WindowsSettings"

typedef struct _ACTIVATION_CONTEXT_DATA_APPLICATION_SETTINGS
{
    ULONG Size;
    ULONG Flags;
    ULONG SettingNamespaceLength;
    ULONG SettingNamespaceOffset; // to WCHAR[], from this struct base
    ULONG SettingNameLength;
    ULONG SettingNameOffset; // to WCHAR[], from this struct base
    ULONG SettingValueLength;
    ULONG SettingValueOffset; // to WCHAR[], from this struct base
} ACTIVATION_CONTEXT_DATA_APPLICATION_SETTINGS, * PACTIVATION_CONTEXT_DATA_APPLICATION_SETTINGS;

// COMPATIBILITY_CONTEXT_ELEMENT from winnt.h before 19H1
typedef struct _COMPATIBILITY_CONTEXT_ELEMENT_LEGACY
{
    GUID Id;
    ACTCTX_COMPATIBILITY_ELEMENT_TYPE Type;
} COMPATIBILITY_CONTEXT_ELEMENT_LEGACY, * PCOMPATIBILITY_CONTEXT_ELEMENT_LEGACY;

// ACTIVATION_CONTEXT_COMPATIBILITY_INFORMATION from winnt.h before 19H1
typedef struct _ACTIVATION_CONTEXT_COMPATIBILITY_INFORMATION_LEGACY
{
    DWORD ElementCount;
    COMPATIBILITY_CONTEXT_ELEMENT_LEGACY Elements[ANYSIZE_ARRAY];
} ACTIVATION_CONTEXT_COMPATIBILITY_INFORMATION_LEGACY, * PACTIVATION_CONTEXT_COMPATIBILITY_INFORMATION_LEGACY;

#include <poppack.h>

// begin_private

typedef struct _ASSEMBLY_STORAGE_MAP_ENTRY
{
    ULONG Flags;
    UNICODE_STRING DosPath;
    HANDLE Handle;
} ASSEMBLY_STORAGE_MAP_ENTRY, * PASSEMBLY_STORAGE_MAP_ENTRY;

typedef struct _ASSEMBLY_STORAGE_MAP_ENTRY32
{
    ULONG Flags;
    UNICODE_STRING32 DosPath;
    HANDLE32 Handle;
} ASSEMBLY_STORAGE_MAP_ENTRY32, * POINTER_32 PASSEMBLY_STORAGE_MAP_ENTRY32;

STATIC_ASSERT(sizeof(ASSEMBLY_STORAGE_MAP_ENTRY32) == 16);

#define ASSEMBLY_STORAGE_MAP_ASSEMBLY_ARRAY_IS_HEAP_ALLOCATED 0x00000001

typedef struct _ASSEMBLY_STORAGE_MAP
{
    ULONG Flags;
    ULONG AssemblyCount;
    PASSEMBLY_STORAGE_MAP_ENTRY* AssemblyArray;
} ASSEMBLY_STORAGE_MAP, * PASSEMBLY_STORAGE_MAP;

typedef struct _ASSEMBLY_STORAGE_MAP32
{
    ULONG Flags;
    ULONG AssemblyCount;
    PASSEMBLY_STORAGE_MAP_ENTRY32* POINTER_32 AssemblyArray;
} ASSEMBLY_STORAGE_MAP32, * POINTER_32 PASSEMBLY_STORAGE_MAP32;

STATIC_ASSERT(sizeof(ASSEMBLY_STORAGE_MAP32) == 12);

#define ACTIVATION_CONTEXT_NOTIFICATION_DESTROY 1
#define ACTIVATION_CONTEXT_NOTIFICATION_ZOMBIFY 2
#define ACTIVATION_CONTEXT_NOTIFICATION_USED    3

typedef
_Function_class_(ACTIVATION_CONTEXT_NOTIFY_ROUTINE)
VOID NTAPI ACTIVATION_CONTEXT_NOTIFY_ROUTINE(
    _In_ ULONG NotificationType, // ACTIVATION_CONTEXT_NOTIFICATION_*
    _In_ struct _ACTIVATION_CONTEXT* ActivationContext,
    _In_ PACTIVATION_CONTEXT_DATA ActivationContextData,
    _In_opt_ PVOID NotificationContext,
    _In_opt_ PVOID NotificationData,
    _Inout_ PBOOLEAN DisableThisNotification
    );
typedef ACTIVATION_CONTEXT_NOTIFY_ROUTINE* PACTIVATION_CONTEXT_NOTIFY_ROUTINE;

typedef struct _ACTIVATION_CONTEXT
{
    LONG RefCount;
    ULONG Flags;
    PACTIVATION_CONTEXT_DATA ActivationContextData;
    PACTIVATION_CONTEXT_NOTIFY_ROUTINE NotificationRoutine;
    PVOID NotificationContext;
    ULONG SentNotifications[8];
    ULONG DisabledNotifications[8];
    ASSEMBLY_STORAGE_MAP StorageMap;
    PASSEMBLY_STORAGE_MAP_ENTRY InlineStorageMapEntries[32];
} ACTIVATION_CONTEXT, * PACTIVATION_CONTEXT;

typedef struct _ACTIVATION_CONTEXT32
{
    LONG RefCount;
    ULONG Flags;
    struct _ACTIVATION_CONTEXT_DATA* POINTER_32 ActivationContextData;
    PVOID32 /*PACTIVATION_CONTEXT_NOTIFY_ROUTINE*/ NotificationRoutine;
    PVOID32 NotificationContext;
    ULONG SentNotifications[8];
    ULONG DisabledNotifications[8];
    ASSEMBLY_STORAGE_MAP32 StorageMap;
    PASSEMBLY_STORAGE_MAP_ENTRY32 InlineStorageMapEntries[32];
} ACTIVATION_CONTEXT32, * POINTER_32 PACTIVATION_CONTEXT32;

STATIC_ASSERT(sizeof(ACTIVATION_CONTEXT32) == 224);

#define RTL_ACTIVATION_CONTEXT_STACK_FRAME_FLAG_RELEASE_ON_DEACTIVATION 0x00000001
#define RTL_ACTIVATION_CONTEXT_STACK_FRAME_FLAG_NO_DEACTIVATE           0x00000002
#define RTL_ACTIVATION_CONTEXT_STACK_FRAME_FLAG_ON_FREE_LIST            0x00000004
#define RTL_ACTIVATION_CONTEXT_STACK_FRAME_FLAG_HEAP_ALLOCATED          0x00000008
#define RTL_ACTIVATION_CONTEXT_STACK_FRAME_FLAG_NOT_REALLY_ACTIVATED    0x00000010

typedef struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME
{
    struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME* Previous;
    PACTIVATION_CONTEXT ActivationContext;
    ULONG Flags; // RTL_ACTIVATION_CONTEXT_STACK_FRAME_FLAG_*
} RTL_ACTIVATION_CONTEXT_STACK_FRAME, * PRTL_ACTIVATION_CONTEXT_STACK_FRAME;

typedef struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME32
{
    struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME32* POINTER_32 Previous;
    PACTIVATION_CONTEXT32 ActivationContext;
    ULONG Flags; // RTL_ACTIVATION_CONTEXT_STACK_FRAME_FLAG_*
} RTL_ACTIVATION_CONTEXT_STACK_FRAME32, * POINTER_32 PRTL_ACTIVATION_CONTEXT_STACK_FRAME32;

STATIC_ASSERT(sizeof(RTL_ACTIVATION_CONTEXT_STACK_FRAME32) == 12);

#define ACTIVATION_CONTEXT_STACK_FLAG_QUERIES_DISABLED 0x00000001

typedef struct _ACTIVATION_CONTEXT_STACK
{
    PRTL_ACTIVATION_CONTEXT_STACK_FRAME ActiveFrame;
    LIST_ENTRY FrameListCache;
    ULONG Flags; // ACTIVATION_CONTEXT_STACK_FLAG_*
    ULONG NextCookieSequenceNumber;
    ULONG StackId;
} ACTIVATION_CONTEXT_STACK, * PACTIVATION_CONTEXT_STACK;

typedef struct _ACTIVATION_CONTEXT_STACK32
{
    PRTL_ACTIVATION_CONTEXT_STACK_FRAME32 ActiveFrame;
    LIST_ENTRY32 FrameListCache;
    ULONG Flags; // ACTIVATION_CONTEXT_STACK_FLAG_*
    ULONG NextCookieSequenceNumber;
    ULONG StackId;
} ACTIVATION_CONTEXT_STACK32, * POINTER_32 PACTIVATION_CONTEXT_STACK32;

STATIC_ASSERT(sizeof(ACTIVATION_CONTEXT_STACK32) == 24);

//
// Application compatibility cache
//

#ifndef _AHCACHE_H_
#define _AHCACHE_H_


typedef enum _AHC_INFO_CLASS
{
    AhcInfoClassSdbQueryResult = 0x00000001,
    AhcInfoClassSdbSxsOverrideManifest = 0x00000002,
    AhcInfoClassSdbRunlevelFlags = 0x00000004,
    AhcInfoClassSdbFusionFlags = 0x00000008,
    AhcInfoClassSdbInstallerFlags = 0x00000010,
    AhcInfoClassFusionFlags = 0x00000020,
    AhcInfoClassTelemetryFlags = 0x00000040,
    AhcInfoClassInstallDetect = 0x00000080,
    AhcInfoClassRacEventSent = 0x00000100,
    AhcInfoClassIsSystemFile = 0x00000200,
    AhcInfoClassMonitoringFlags = 0x00000400,
    AhcInfoClassExeType = 0x00000800,
} AHC_INFO_CLASS, * PAHC_INFO_CLASS;

#define AHC_INFO_CLASS_FILTER_ON_FILETIME_CHANGE            \
    (AHC_INFO_CLASS)(AhcInfoClassSdbQueryResult |           \
                     AhcInfoClassSdbSxsOverrideManifest |   \
                     AhcInfoClassSdbRunlevelFlags |         \
                     AhcInfoClassSdbFusionFlags |           \
                     AhcInfoClassSdbInstallerFlags |        \
                     AhcInfoClassFusionFlags |              \
                     AhcInfoClassRacEventSent)

#define AHC_INFO_CLASS_FILTER_ON_SDB_CHANGE                 \
    (AHC_INFO_CLASS)(AhcInfoClassSdbQueryResult |           \
                     AhcInfoClassSdbSxsOverrideManifest |   \
                     AhcInfoClassSdbRunlevelFlags |         \
                     AhcInfoClassSdbFusionFlags |           \
                     AhcInfoClassSdbInstallerFlags |        \
                     AhcInfoClassInstallDetect)

#define AHC_INFO_CLASS_ALL                                  \
    (AHC_INFO_CLASS)(AhcInfoClassSdbQueryResult |           \
                     AhcInfoClassSdbSxsOverrideManifest |   \
                     AhcInfoClassSdbRunlevelFlags |         \
                     AhcInfoClassSdbFusionFlags |           \
                     AhcInfoClassSdbInstallerFlags |        \
                     AhcInfoClassFusionFlags |              \
                     AhcInfoClassTelemetryFlags |           \
                     AhcInfoClassInstallDetect |            \
                     AhcInfoClassRacEventSent |             \
                     AhcInfoClassIsSystemFile |             \
                     AhcInfoClassMonitoringFlags |          \
                     AhcInfoClassExeType)

#define AHC_INFO_CLASS_INTERNALLY_COMPUTED                  \
    (AHC_INFO_CLASS)(AhcInfoClassSdbQueryResult |           \
                     AhcInfoClassSdbSxsOverrideManifest |   \
                     AhcInfoClassSdbRunlevelFlags |         \
                     AhcInfoClassSdbFusionFlags |           \
                     AhcInfoClassSdbInstallerFlags |        \
                     AhcInfoClassTelemetryFlags |           \
                     AhcInfoClassIsSystemFile |             \
                     AhcInfoClassMonitoringFlags |          \
                     AhcInfoClassExeType)

#define AHC_INFO_CLASS_SAFE_FOR_UNPRIVILEGED_UPDATE         \
    (AHC_INFO_CLASS)(AhcInfoClassInstallDetect |            \
                     AhcInfoClassRacEventSent |             \
                     AhcInfoClassTelemetryFlags |           \
                     AhcInfoClassMonitoringFlags)

//
// Cache structures and APIs.
//

typedef enum _AHC_SERVICE_CLASS
{
    ApphelpCacheServiceLookup = 0,
    ApphelpCacheServiceRemove,
    ApphelpCacheServiceUpdate,
    ApphelpCacheServiceClear,
    ApphelpCacheServiceSnapStatistics,
    ApphelpCacheServiceSnapCache,
    ApphelpCacheServiceLookupCdb,
    ApphelpCacheServiceRefreshCdb,
    ApphelpCacheServiceMapQuirks,
    ApphelpCacheServiceHwIdQuery,
    ApphelpCacheServiceMax
} AHC_SERVICE_CLASS;

typedef struct _AHC_SERVICE_LOOKUP
{
    AHC_INFO_CLASS InfoClass;                   // Information to lookup.
    UINT HintFlags;                             // Hint flags about cache query.
    UNICODE_STRING PackageAlias;                // Aliased package moniker in a packed string.
    HANDLE FileHandle;                          // User space handle to file.
    HANDLE ProcessHandle;                       // User space process handle.
    USHORT ExeType;                             // Executable bitness.
    USHORT Padding;                             // Padding to even USHORTs.
    UNICODE_STRING ExeSignature;                // Executable file signature.
    PCZZWSTR Environment;                       // Environment block.
    UINT EnvironmentSize;                       // Size of environment block in bytes.
} AHC_SERVICE_LOOKUP, * PAHC_SERVICE_LOOKUP;

typedef struct _AHC_SERVICE_CLEAR
{
    AHC_INFO_CLASS InfoClass;
} AHC_SERVICE_CLEAR, * PAHC_SERVICE_CLEAR;

typedef struct _AHC_SERVICE_UPDATE
{
    AHC_INFO_CLASS InfoClass;
    UNICODE_STRING PackageAlias;
    HANDLE FileHandle;
    UNICODE_STRING ExeSignature;
    PVOID Data;
    ULONG DataSize;
} AHC_SERVICE_UPDATE, * PAHC_SERVICE_UPDATE;

typedef struct _AHC_SERVICE_REMOVE
{
    AHC_INFO_CLASS InfoClass;
    UNICODE_STRING PackageAlias;
    HANDLE FileHandle;
    UNICODE_STRING ExeSignature;
} AHC_SERVICE_REMOVE, * PAHC_SERVICE_REMOVE;

typedef struct _AHC_SERVICE_LOOKUP_CDB
{
    UNICODE_STRING Name;
} AHC_SERVICE_LOOKUP_CDB, * PAHC_SERVICE_LOOKUP_CDB;

//
// AHC_HINT_* flags are used in the HintFlags variable.
//

#define AHC_HINT_FORCE_BYPASS                           0x00000001
#define AHC_HINT_REMOVABLE_MEDIA                        0x00000002
#define AHC_HINT_TEMPORARY_DIRECTORY                    0x00000004
#define AHC_HINT_USER_PERM_LAYER                        0x00000008
#define AHC_HINT_CREATE_PROCESS                         0x00000010
#define AHC_HINT_NATIVE_EXE                             0x00000020

#define SHIM_CACHE_MAIN_DATABASE_PATH32                 L"\\AppPatch\\sysmain.sdb"
#define SHIM_CACHE_MAIN_DATABASE_PATH64                 L"\\AppPatch\\AppPatch64\\sysmain.sdb"

//
// Flag definitions for various flag-type information in cache.
//

#define AHC_CACHE_FLAG_MONITORING_IS_CANDIDATE          0x00000001 // Candidate for monitoring.
#define AHC_CACHE_FLAG_MONITORING_IS_COMPLETE           0x00000002 // Monitoring has completed.
#define AHC_CACHE_FLAG_MONITORING_VALID_MASK            (AHC_CACHE_FLAG_MONITORING_IS_CANDIDATE | \
                                                         AHC_CACHE_FLAG_MONITORING_IS_COMPLETE)

#define AHC_CACHE_FLAG_TELEMETRY_IS_CANDIDATE           0x00000001 // Candidate for telemetry.
#define AHC_CACHE_FLAG_TELEMETRY_HAS_SAMPLED            0x00000002 // Telemetry has run.
#define AHC_CACHE_FLAG_TELEMETRY_VALID_MASK             (AHC_CACHE_FLAG_TELEMETRY_IS_CANDIDATE | \
                                                         AHC_CACHE_FLAG_TELEMETRY_HAS_SAMPLED)

#define AHC_CACHE_FLAG_FUSION_HASDOTLOCAL               0x00000001 // Dot local file exists.
#define AHC_CACHE_FLAG_FUSION_HASMANIFESTFILE           0x00000002 // Fusion manifest exists.
#define AHC_CACHE_FLAG_FUSION_HASMANIFESTRESOURCE       0x00000004 // Fusion manifest resource exists.
#define AHC_CACHE_FLAG_FUSION_VALID_MASK                (AHC_CACHE_FLAG_FUSION_HASDOTLOCAL | \
                                                         AHC_CACHE_FLAG_FUSION_HASMANIFESTFILE | \
                                                         AHC_CACHE_FLAG_FUSION_HASMANIFESTRESOURCE)

#define AHC_CACHE_FLAG_RAC_EVENTSENT                    0x00000001 // Rac event has been sent.
#define AHC_CACHE_FLAG_RAC_VALID_MASK                   (AHC_CACHE_FLAG_RAC_EVENTSENT)

#define AHC_CACHE_FLAG_INSTALLDETECT_CLAIMED            0x00000001 // InstallDetect claimed.
#define AHC_CACHE_FLAG_INSTALLDETECT_VALID_MASK         (AHC_CACHE_FLAG_RAC_EVENTSENT)

//
// Statistics.
//

typedef struct _AHC_MAIN_STATISTICS
{
    ULONG Lookup;                               // Count of lookup calls.
    ULONG Remove;                               // Count of remove calls.
    ULONG Update;                               // Count of update calls.
    ULONG Clear;                                // Count of clear calls.
    ULONG SnapStatistics;                       // Count of snap statistics calls.
    ULONG SnapCache;                            // Count of snap store calls.
} AHC_MAIN_STATISTICS, * PAHC_MAIN_STATISTICS;

typedef struct _AHC_STORE_STATISTICS
{
    ULONG LookupHits;                           // Count of lookup hits.
    ULONG LookupMisses;                         // Count of lookup misses.
    ULONG Inserted;                             // Count of inserted.
    ULONG Replaced;                             // Count of replaced.
    ULONG Updated;                              // Count of updates.
} AHC_STORE_STATISTICS, * PAHC_STORE_STATISTICS;

typedef struct _AHC_STATISTICS
{
    ULONG Size;                                 // Size of the structure.
    AHC_MAIN_STATISTICS Main;                   // Main statistics.
    AHC_STORE_STATISTICS Store;                 // Store statistics.
} AHC_STATISTICS, * PAHC_STATISTICS;

typedef struct _AHC_SERVICE_DATAQUERY
{
    AHC_STATISTICS Stats;                       // Statistics.
    ULONG DataSize;                             // Size of data.
    PBYTE Data;                                 // Data.
} AHC_SERVICE_DATAQUERY, * PAHC_SERVICE_DATAQUERY;

typedef struct _AHC_SERVICE_DATACACHE
{
    HANDLE FileHandle;                          // User space handle to file.
    USHORT ExeType;                             // Executable bitness.
    USHORT Padding;                             // Padding to even USHORTs.
    UINT HintFlags;                             // Metadata flags about cache query.
    HANDLE ProcessHandle;                       // User space process handle.
    UNICODE_STRING FileName;                    // Executable file name.
    UNICODE_STRING Environment;                 // Environment block.
    UNICODE_STRING PackageAlias;                // Aliased package moniker in a packed string.
    ULONG CustomDataSize;                       // Size of the custom data to cache.
    PBYTE CustomData;                           // Pointer to the custom data.
} AHC_SERVICE_DATACACHE, * PAHC_SERVICE_DATACACHE;

typedef struct _AHC_SERVICE_HWID_QUERY
{
    BOOLEAN QueryResult;                        // Query result
    UNICODE_STRING HwId;                        // Query HwId; can contain wildcards
} AHC_SERVICE_HWID_QUERY, * PAHC_SERVICE_HWID_QUERY;

typedef struct _AHC_SERVICE_DATA
{
    AHC_SERVICE_LOOKUP Lookup;                  // Lookup EXE/Package.
    AHC_SERVICE_UPDATE Update;                  // Updating flags for a given exe/package.
    AHC_SERVICE_DATACACHE Cache;                // For cache operations.
    AHC_SERVICE_LOOKUP_CDB LookupCdb;           // Lookup cdb.
    AHC_SERVICE_CLEAR Clear;                    // Clear flags for all exes/packages.
    AHC_SERVICE_REMOVE Remove;                  // Remove EXE/Package.
    AHC_SERVICE_HWID_QUERY HwIdQuery;           // For HWID cache queries.
    NTSTATUS DriverStatus;                      // Receive the status from the cache driver. Set error code in IoStatus block causes driver verifier violation.
    PVOID ParamsOut;                            // Parameters out data.
    ULONG ParamsOutSize;                        // Parameters out size.
} AHC_SERVICE_DATA, * PAHC_SERVICE_DATA;

//
// Kernel entry point.
//

__kernel_entry NTSYSCALLAPI
NTSTATUS
NtApphelpCacheControl(
    _In_ AHC_SERVICE_CLASS ServiceClass,
    _Inout_opt_ PVOID ServiceContext
);

NTSYSAPI
NTSTATUS
ZwApphelpCacheControl(
    _In_ AHC_SERVICE_CLASS ServiceClass,
    _Inout_opt_ PVOID ServiceContext
);

#endif

// end_private

VEIL_END()

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
