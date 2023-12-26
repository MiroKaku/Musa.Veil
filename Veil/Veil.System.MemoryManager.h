/*
 * PROJECT:   Veil
 * FILE:      Veil.System.MemoryManager.h
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

#define PAGE_NOACCESS           0x01    
#define PAGE_READONLY           0x02    
#define PAGE_READWRITE          0x04    
#define PAGE_WRITECOPY          0x08    
#define PAGE_EXECUTE            0x10    
#define PAGE_EXECUTE_READ       0x20    
#define PAGE_EXECUTE_READWRITE  0x40    
#define PAGE_EXECUTE_WRITECOPY  0x80    
#define PAGE_GUARD             0x100    
#define PAGE_NOCACHE           0x200    
#define PAGE_WRITECOMBINE      0x400    
#define PAGE_GRAPHICS_NOACCESS           0x0800    
#define PAGE_GRAPHICS_READONLY           0x1000    
#define PAGE_GRAPHICS_READWRITE          0x2000    
#define PAGE_GRAPHICS_EXECUTE            0x4000    
#define PAGE_GRAPHICS_EXECUTE_READ       0x8000    
#define PAGE_GRAPHICS_EXECUTE_READWRITE 0x10000    
#define PAGE_GRAPHICS_COHERENT          0x20000    
#define PAGE_GRAPHICS_NOCACHE           0x40000    
#define PAGE_ENCLAVE_THREAD_CONTROL 0x80000000  
#define PAGE_REVERT_TO_FILE_MAP     0x80000000  
#define PAGE_TARGETS_NO_UPDATE      0x40000000  
#define PAGE_TARGETS_INVALID        0x40000000  
#define PAGE_ENCLAVE_UNVALIDATED    0x20000000  
#define PAGE_ENCLAVE_MASK           0x10000000  
#ifndef PAGE_ENCLAVE_DECOMMIT
#define PAGE_ENCLAVE_DECOMMIT       (PAGE_ENCLAVE_MASK | 0) 
#endif
#define PAGE_ENCLAVE_SS_FIRST       (PAGE_ENCLAVE_MASK | 1) 
#define PAGE_ENCLAVE_SS_REST        (PAGE_ENCLAVE_MASK | 2) 

#define MEM_COMMIT                      0x00001000  
#define MEM_RESERVE                     0x00002000  
#define MEM_DECOMMIT                    0x00004000  
#define MEM_RELEASE                     0x00008000  
#define MEM_FREE                        0x00010000  
#define MEM_PRIVATE                     0x00020000  
#define MEM_MAPPED                      0x00040000  
#define MEM_RESET                       0x00080000  
#define MEM_TOP_DOWN                    0x00100000  
#define MEM_WRITE_WATCH                 0x00200000  
#define MEM_PHYSICAL                    0x00400000  
#define MEM_ROTATE                      0x00800000  
#define MEM_DIFFERENT_IMAGE_BASE_OK     0x00800000  
#define MEM_RESET_UNDO                  0x01000000  
#define MEM_LARGE_PAGES                 0x20000000  
#define MEM_DOS_LIM                     0x40000000  
#define MEM_4MB_PAGES                   0x80000000  
#define MEM_64K_PAGES                   (MEM_LARGE_PAGES | MEM_PHYSICAL)  
#define MEM_UNMAP_WITH_TRANSIENT_BOOST  0x00000001  
#define MEM_COALESCE_PLACEHOLDERS       0x00000001  
#define MEM_PRESERVE_PLACEHOLDER        0x00000002  
#define MEM_REPLACE_PLACEHOLDER         0x00004000  
#define MEM_RESERVE_PLACEHOLDER         0x00040000  

#define SEC_HUGE_PAGES                  0x00020000  
#define SEC_PARTITION_OWNER_HANDLE      0x00040000  
#define SEC_64K_PAGES                   0x00080000  
#define SEC_BASED                       0x00200000  
#define SEC_NO_CHANGE                   0x00400000  
#define SEC_FILE                        0x00800000  
#define SEC_IMAGE                       0x01000000  
#define SEC_PROTECTED_IMAGE             0x02000000  
#define SEC_RESERVE                     0x04000000  
#define SEC_COMMIT                      0x08000000  
#define SEC_NOCACHE                     0x10000000  
#define SEC_GLOBAL                      0x20000000  
#define SEC_WRITECOMBINE                0x40000000  
#define SEC_LARGE_PAGES                 0x80000000  
#define SEC_IMAGE_NO_EXECUTE (SEC_IMAGE | SEC_NOCACHE)  

#ifdef _KERNEL_MODE
#define MEM_IMAGE SEC_IMAGE
#endif

// private
#ifndef _KERNEL_MODE
typedef enum _MEMORY_INFORMATION_CLASS
{
    MemoryBasicInformation,                 // q: MEMORY_BASIC_INFORMATION
    MemoryWorkingSetInformation,            // q: MEMORY_WORKING_SET_INFORMATION
    MemoryMappedFilenameInformation,        // q: UNICODE_STRING
    MemoryRegionInformation,                // q: MEMORY_REGION_INFORMATION
    MemoryWorkingSetExInformation,          // q: MEMORY_WORKING_SET_EX_INFORMATION // since VISTA
    MemorySharedCommitInformation,          // q: MEMORY_SHARED_COMMIT_INFORMATION // since WIN8
    MemoryImageInformation,                 // q: MEMORY_IMAGE_INFORMATION
    MemoryRegionInformationEx,              // MEMORY_REGION_INFORMATION
    MemoryPrivilegedBasicInformation,       // MEMORY_BASIC_INFORMATION
    MemoryEnclaveImageInformation,          // MEMORY_ENCLAVE_IMAGE_INFORMATION // since REDSTONE3
    MemoryBasicInformationCapped,           // 10
    MemoryPhysicalContiguityInformation,    // MEMORY_PHYSICAL_CONTIGUITY_INFORMATION // since 20H1
    MemoryBadInformation,                   // since WIN11
    MemoryBadInformationAllProcesses,       // since 22H1
    MaxMemoryInfoClass
} MEMORY_INFORMATION_CLASS;
#else
#define MemoryBasicInformation              ((_MEMORY_INFORMATION_CLASS)0x0)
#define MemoryWorkingSetInformation         ((_MEMORY_INFORMATION_CLASS)0x1)
#define MemoryMappedFileNameInformation     ((_MEMORY_INFORMATION_CLASS)0x2)
#define MemoryRegionInformation             ((_MEMORY_INFORMATION_CLASS)0x3)
#define MemoryWorkingSetExInformation       ((_MEMORY_INFORMATION_CLASS)0x4)
#define MemorySharedCommitInformation       ((_MEMORY_INFORMATION_CLASS)0x5)
#define MemoryImageInformation              ((_MEMORY_INFORMATION_CLASS)0x6)
#define MemoryRegionInformationEx           ((_MEMORY_INFORMATION_CLASS)0x7)
#define MemoryPrivilegedBasicInformation    ((_MEMORY_INFORMATION_CLASS)0x8)
#define MemoryEnclaveImageInformation       ((_MEMORY_INFORMATION_CLASS)0x9)
#define MemoryBasicInformationCapped        ((_MEMORY_INFORMATION_CLASS)0xA)
#define MemoryPhysicalContiguityInformation ((_MEMORY_INFORMATION_CLASS)0xB)
#define MemoryBadInformation                ((_MEMORY_INFORMATION_CLASS)0xC)
#define MemoryBadInformationAllProcesses    ((_MEMORY_INFORMATION_CLASS)0xD)
#endif // !_KERNEL_MODE

typedef struct _MEMORY_WORKING_SET_BLOCK
{
    ULONG_PTR Protection : 5;
    ULONG_PTR ShareCount : 3;
    ULONG_PTR Shared : 1;
    ULONG_PTR Node : 3;
#ifdef _WIN64
    ULONG_PTR VirtualPage : 52;
#else
    ULONG VirtualPage : 20;
#endif
} MEMORY_WORKING_SET_BLOCK, * PMEMORY_WORKING_SET_BLOCK;

typedef struct _MEMORY_WORKING_SET_INFORMATION
{
    ULONG_PTR NumberOfEntries;
    MEMORY_WORKING_SET_BLOCK WorkingSetInfo[1];
} MEMORY_WORKING_SET_INFORMATION, * PMEMORY_WORKING_SET_INFORMATION;

// private
typedef struct _MEMORY_REGION_INFORMATION
{
    PVOID AllocationBase;
    ULONG AllocationProtect;
    union
    {
        ULONG RegionType;
        struct
        {
            ULONG Private : 1;
            ULONG MappedDataFile : 1;
            ULONG MappedImage : 1;
            ULONG MappedPageFile : 1;
            ULONG MappedPhysical : 1;
            ULONG DirectMapped : 1;
            ULONG SoftwareEnclave : 1; // REDSTONE3
            ULONG PageSize64K : 1;
            ULONG PlaceholderReservation : 1; // REDSTONE4
            ULONG MappedAwe : 1; // 21H1
            ULONG MappedWriteWatch : 1;
            ULONG PageSizeLarge : 1;
            ULONG PageSizeHuge : 1;
            ULONG Reserved : 19;
        };
    };
    SIZE_T RegionSize;
    SIZE_T CommitSize;
    ULONG_PTR PartitionId; // 19H1
    ULONG_PTR NodePreference; // 20H1
} MEMORY_REGION_INFORMATION, * PMEMORY_REGION_INFORMATION;

// private 
typedef enum _MEMORY_WORKING_SET_EX_LOCATION
{
    MemoryLocationInvalid,
    MemoryLocationResident,
    MemoryLocationPagefile,
    MemoryLocationReserved
} MEMORY_WORKING_SET_EX_LOCATION;

// private
typedef struct _MEMORY_WORKING_SET_EX_BLOCK
{
    union
    {
        struct
        {
            ULONG_PTR Valid : 1;
            ULONG_PTR ShareCount : 3;
            ULONG_PTR Win32Protection : 11;
            ULONG_PTR Shared : 1;
            ULONG_PTR Node : 6;
            ULONG_PTR Locked : 1;
            ULONG_PTR LargePage : 1;
            ULONG_PTR Priority : 3;
            ULONG_PTR Reserved : 3;
            ULONG_PTR SharedOriginal : 1;
            ULONG_PTR Bad : 1;
            ULONG_PTR Win32GraphicsProtection : 4; // 19H1
#ifdef _WIN64
            ULONG_PTR ReservedUlong : 28;
#endif
        };
        struct
        {
            ULONG_PTR Valid : 1;
            ULONG_PTR Reserved0 : 14;
            ULONG_PTR Shared : 1;
            ULONG_PTR Reserved1 : 5;
            ULONG_PTR PageTable : 1;
            ULONG_PTR Location : 2;
            ULONG_PTR Priority : 3;
            ULONG_PTR ModifiedList : 1;
            ULONG_PTR Reserved2 : 2;
            ULONG_PTR SharedOriginal : 1;
            ULONG_PTR Bad : 1;
#ifdef _WIN64
            ULONG_PTR ReservedUlong : 32;
#endif
        } Invalid;
    };
} MEMORY_WORKING_SET_EX_BLOCK, * PMEMORY_WORKING_SET_EX_BLOCK;

// private
typedef struct _MEMORY_WORKING_SET_EX_INFORMATION
{
    PVOID VirtualAddress;
    union
    {
        MEMORY_WORKING_SET_EX_BLOCK VirtualAttributes;
        ULONG_PTR Long;
    } u1;
} MEMORY_WORKING_SET_EX_INFORMATION, * PMEMORY_WORKING_SET_EX_INFORMATION;

// private
typedef struct _MEMORY_SHARED_COMMIT_INFORMATION
{
    SIZE_T CommitSize;
} MEMORY_SHARED_COMMIT_INFORMATION, * PMEMORY_SHARED_COMMIT_INFORMATION;

// private
typedef struct _MEMORY_IMAGE_INFORMATION
{
    PVOID ImageBase;
    SIZE_T SizeOfImage;
    union
    {
        ULONG ImageFlags;
        struct
        {
            ULONG ImagePartialMap : 1;
            ULONG ImageNotExecutable : 1;
            ULONG ImageSigningLevel : 4; // REDSTONE3
            ULONG Reserved : 26;
        };
    };
} MEMORY_IMAGE_INFORMATION, * PMEMORY_IMAGE_INFORMATION;

// private
typedef struct _MEMORY_ENCLAVE_IMAGE_INFORMATION
{
    MEMORY_IMAGE_INFORMATION ImageInfo;
    UCHAR UniqueID[32];
    UCHAR AuthorID[32];
} MEMORY_ENCLAVE_IMAGE_INFORMATION, * PMEMORY_ENCLAVE_IMAGE_INFORMATION;

// private
typedef enum _MEMORY_PHYSICAL_CONTIGUITY_UNIT_STATE
{
    MemoryNotContiguous,
    MemoryAlignedAndContiguous,
    MemoryNotResident,
    MemoryNotEligibleToMakeContiguous,
    MemoryContiguityStateMax,
} MEMORY_PHYSICAL_CONTIGUITY_UNIT_STATE;

// private
typedef struct _MEMORY_PHYSICAL_CONTIGUITY_UNIT_INFORMATION
{
    union
    {
        struct
        {
            ULONG State : 2;
            ULONG Reserved : 30;
        };
        ULONG AllInformation;
    };
} MEMORY_PHYSICAL_CONTIGUITY_UNIT_INFORMATION, * PMEMORY_PHYSICAL_CONTIGUITY_UNIT_INFORMATION;

// private
typedef struct _MEMORY_PHYSICAL_CONTIGUITY_INFORMATION
{
    PVOID VirtualAddress;
    ULONG_PTR Size;
    ULONG_PTR ContiguityUnitSize;
    ULONG Flags;
    PMEMORY_PHYSICAL_CONTIGUITY_UNIT_INFORMATION ContiguityUnitInformation;
} MEMORY_PHYSICAL_CONTIGUITY_INFORMATION, * PMEMORY_PHYSICAL_CONTIGUITY_INFORMATION;

typedef enum _MMLISTS
{
    ZeroedPageList = 0,
    FreePageList = 1,
    StandbyPageList = 2,
    ModifiedPageList = 3,
    ModifiedNoWritePageList = 4,
    BadPageList = 5,
    ActiveAndValid = 6,
    TransitionPage = 7
} MMLISTS;

typedef enum _MMPFNUSE
{
    ProcessPrivatePage,
    MemoryMappedFilePage,
    PageFileMappedPage,
    PageTablePage,
    PagedPoolPage,
    NonPagedPoolPage,
    SystemPTEPage,
    SessionPrivatePage,
    MetafilePage,
    AWEPage,
    DriverLockedPage,
    KernelStackPage
} MMPFNUSE;

// private
typedef struct _MEMORY_FRAME_INFORMATION
{
    ULONGLONG UseDescription : 4; // MMPFNUSE_*
    ULONGLONG ListDescription : 3; // MMPFNLIST_*
    ULONGLONG Cold : 1; // 19H1
    ULONGLONG Pinned : 1; // 1 - pinned, 0 - not pinned
    ULONGLONG DontUse : 48; // *_INFORMATION overlay
    ULONGLONG Priority : 3;
    ULONGLONG NonTradeable : 1;
    ULONGLONG Reserved : 3;
} MEMORY_FRAME_INFORMATION;

// private
typedef struct _FILEOFFSET_INFORMATION
{
    ULONGLONG DontUse : 9; // MEMORY_FRAME_INFORMATION overlay
    ULONGLONG Offset : 48; // mapped files
    ULONGLONG Reserved : 7;
} FILEOFFSET_INFORMATION;

// private
typedef struct _PAGEDIR_INFORMATION
{
    ULONGLONG DontUse : 9; // MEMORY_FRAME_INFORMATION overlay
    ULONGLONG PageDirectoryBase : 48; // private pages
    ULONGLONG Reserved : 7;
} PAGEDIR_INFORMATION;

// private
typedef struct _UNIQUE_PROCESS_INFORMATION
{
    ULONGLONG DontUse : 9; // MEMORY_FRAME_INFORMATION overlay
    ULONGLONG UniqueProcessKey : 48; // ProcessId
    ULONGLONG Reserved : 7;
} UNIQUE_PROCESS_INFORMATION, * PUNIQUE_PROCESS_INFORMATION;

// private
typedef struct _MMPFN_IDENTITY
{
    union
    {
        MEMORY_FRAME_INFORMATION e1; // all
        FILEOFFSET_INFORMATION e2; // mapped files
        PAGEDIR_INFORMATION e3; // private pages
        UNIQUE_PROCESS_INFORMATION e4; // owning process
    } u1;
    ULONG_PTR PageFrameIndex; // all
    union
    {
        struct
        {
            ULONG_PTR Image : 1;
            ULONG_PTR Mismatch : 1;
        } e1;
        struct
        {
            ULONG_PTR CombinedPage;
        } e2;
        ULONG_PTR FileObject; // mapped files
        ULONG_PTR UniqueFileObjectKey;
        ULONG_PTR ProtoPteAddress;
        ULONG_PTR VirtualAddress;  // everything else
    } u2;
} MMPFN_IDENTITY, * PMMPFN_IDENTITY;

typedef struct _MMPFN_MEMSNAP_INFORMATION
{
    ULONG_PTR InitialPageFrameIndex;
    ULONG_PTR Count;
} MMPFN_MEMSNAP_INFORMATION, * PMMPFN_MEMSNAP_INFORMATION;

typedef enum _SECTION_INFORMATION_CLASS
{
    SectionBasicInformation, // q; SECTION_BASIC_INFORMATION
    SectionImageInformation, // q; SECTION_IMAGE_INFORMATION
    SectionRelocationInformation, // q; ULONG_PTR RelocationDelta // name:wow64:whNtQuerySection_SectionRelocationInformation // since WIN7
    SectionOriginalBaseInformation, // PVOID BaseAddress
    SectionInternalImageInformation, // SECTION_INTERNAL_IMAGE_INFORMATION // since REDSTONE2
    MaxSectionInfoClass
} SECTION_INFORMATION_CLASS;

typedef struct _SECTION_BASIC_INFORMATION
{
    PVOID BaseAddress;
    ULONG AllocationAttributes;
    LARGE_INTEGER MaximumSize;
} SECTION_BASIC_INFORMATION, * PSECTION_BASIC_INFORMATION;

// symbols
typedef struct _SECTION_IMAGE_INFORMATION
{
    PVOID TransferAddress;
    ULONG ZeroBits;
    SIZE_T MaximumStackSize;
    SIZE_T CommittedStackSize;
    ULONG SubSystemType;
    union
    {
        struct
        {
            USHORT SubSystemMinorVersion;
            USHORT SubSystemMajorVersion;
        };
        ULONG SubSystemVersion;
    };
    union
    {
        struct
        {
            USHORT MajorOperatingSystemVersion;
            USHORT MinorOperatingSystemVersion;
        };
        ULONG OperatingSystemVersion;
    };
    USHORT ImageCharacteristics;
    USHORT DllCharacteristics;
    USHORT Machine;
    BOOLEAN ImageContainsCode;
    union
    {
        UCHAR ImageFlags;
        struct
        {
            UCHAR ComPlusNativeReady : 1;
            UCHAR ComPlusILOnly : 1;
            UCHAR ImageDynamicallyRelocated : 1;
            UCHAR ImageMappedFlat : 1;
            UCHAR BaseBelow4gb : 1;
            UCHAR ComPlusPrefer32bit : 1;
            UCHAR Reserved : 2;
        };
    };
    ULONG LoaderFlags;
    ULONG ImageFileSize;
    ULONG CheckSum;
} SECTION_IMAGE_INFORMATION, * PSECTION_IMAGE_INFORMATION;

// symbols
typedef struct _SECTION_INTERNAL_IMAGE_INFORMATION
{
    SECTION_IMAGE_INFORMATION SectionInformation;
    union
    {
        ULONG ExtendedFlags;
        struct
        {
            ULONG ImageExportSuppressionEnabled : 1;
            ULONG ImageCetShadowStacksReady : 1; // 20H1
            ULONG ImageXfgEnabled : 1; // 20H2
            ULONG ImageCetShadowStacksStrictMode : 1;
            ULONG ImageCetSetContextIpValidationRelaxedMode : 1;
            ULONG ImageCetDynamicApisAllowInProc : 1;
            ULONG ImageCetDowngradeReserved1 : 1;
            ULONG ImageCetDowngradeReserved2 : 1;
            ULONG Reserved : 24;
        };
    };
} SECTION_INTERNAL_IMAGE_INFORMATION, * PSECTION_INTERNAL_IMAGE_INFORMATION;

#ifndef _KERNEL_MODE
typedef enum _SECTION_INHERIT
{
    ViewShare = 1,
    ViewUnmap = 2
} SECTION_INHERIT;
#endif // !_KERNEL_MODE

#define MEM_EXECUTE_OPTION_ENABLE                   0x1
#define MEM_EXECUTE_OPTION_DISABLE                  0x2
#define MEM_EXECUTE_OPTION_DISABLE_THUNK_EMULATION  0x4
#define MEM_EXECUTE_OPTION_PERMANENT                0x8
#define MEM_EXECUTE_OPTION_EXECUTE_DISPATCH_ENABLE  0x10
#define MEM_EXECUTE_OPTION_IMAGE_DISPATCH_ENABLE    0x20
#define MEM_EXECUTE_OPTION_DISABLE_EXCEPTION_CHAIN_VALIDATION 0x40
#define MEM_EXECUTE_OPTION_VALID_FLAGS              0x7f

//
// Virtual memory
//

_Must_inspect_result_
__drv_allocatesMem(Mem)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAllocateVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ _At_(*BaseAddress, _Readable_bytes_(*RegionSize) _Writable_bytes_(*RegionSize) _Post_readable_byte_size_(*RegionSize)) PVOID* BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG AllocationType,
    _In_ ULONG Protect
);

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
_When_(return == 0, __drv_allocatesMem(Region))
NTSYSAPI
NTSTATUS
NTAPI
ZwAllocateVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID * BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG AllocationType,
    _In_ ULONG Protect
);

#if (WDK_NTDDI_VERSION <= NTDDI_WIN10_RS4)

typedef struct _MEM_ADDRESS_REQUIREMENTS {
    PVOID LowestStartingAddress;
    PVOID HighestEndingAddress;
    SIZE_T Alignment;
} MEM_ADDRESS_REQUIREMENTS, * PMEM_ADDRESS_REQUIREMENTS;

#define MEM_EXTENDED_PARAMETER_GRAPHICS                 0x00000001
#define MEM_EXTENDED_PARAMETER_NONPAGED                 0x00000002
#define MEM_EXTENDED_PARAMETER_ZERO_PAGES_OPTIONAL      0x00000004
#define MEM_EXTENDED_PARAMETER_NONPAGED_LARGE           0x00000008
#define MEM_EXTENDED_PARAMETER_NONPAGED_HUGE            0x00000010
#define MEM_EXTENDED_PARAMETER_SOFT_FAULT_PAGES         0x00000020
#define MEM_EXTENDED_PARAMETER_EC_CODE                  0x00000040

//
// Use the high ULONG64 bit of the MEM_EXTENDED_PARAMETER to indicate
// that the supplied NUMA node in the low bits is mandatory.  Note this
// is different from the MEM_EXTENDED_PARAMETER_XXX fields above because
// those are encoded in the Type field; this is encoded in the ULong64 field.
//
// This can only be used nonpaged allocations since we don't want page
// faults to fail due to transient memory shortages on arbitrary nodes.
//

#define MEM_EXTENDED_PARAMETER_NUMA_NODE_MANDATORY      MINLONG64

typedef enum MEM_EXTENDED_PARAMETER_TYPE {
    MemExtendedParameterInvalidType = 0,
    MemExtendedParameterAddressRequirements,
    MemExtendedParameterNumaNode,
    MemExtendedParameterPartitionHandle,
    MemExtendedParameterUserPhysicalHandle,
    MemExtendedParameterAttributeFlags,
    MemExtendedParameterImageMachine,
    MemExtendedParameterMax
} MEM_EXTENDED_PARAMETER_TYPE, * PMEM_EXTENDED_PARAMETER_TYPE;

#define MEM_EXTENDED_PARAMETER_TYPE_BITS    8

typedef struct DECLSPEC_ALIGN(8) MEM_EXTENDED_PARAMETER {

    struct {
        ULONG64 Type : MEM_EXTENDED_PARAMETER_TYPE_BITS;
        ULONG64 Reserved : 64 - MEM_EXTENDED_PARAMETER_TYPE_BITS;
    } DUMMYSTRUCTNAME;

    union {
        ULONG64 ULong64;
        PVOID Pointer;
        SIZE_T Size;
        HANDLE Handle;
        ULONG ULong;
    } DUMMYUNIONNAME;

} MEM_EXTENDED_PARAMETER, * PMEM_EXTENDED_PARAMETER;

#define MEMORY_CURRENT_PARTITION_HANDLE         ((HANDLE) (LONG_PTR) -1)
#define MEMORY_SYSTEM_PARTITION_HANDLE          ((HANDLE) (LONG_PTR) -2)
#define MEMORY_EXISTING_VAD_PARTITION_HANDLE    ((HANDLE) (LONG_PTR) -3)

//
// Dedicated memory attributes.
//

#define MEM_DEDICATED_ATTRIBUTE_NOT_SPECIFIED   ((ULONG64) -1)

typedef enum _MEM_DEDICATED_ATTRIBUTE_TYPE {
    MemDedicatedAttributeReadBandwidth = 0,
    MemDedicatedAttributeReadLatency,
    MemDedicatedAttributeWriteBandwidth,
    MemDedicatedAttributeWriteLatency,
    MemDedicatedAttributeMax
} MEM_DEDICATED_ATTRIBUTE_TYPE, * PMEM_DEDICATED_ATTRIBUTE_TYPE;

typedef struct _MEMORY_PARTITION_DEDICATED_MEMORY_OPEN_INFORMATION {

    //
    // Type identifier of the dedicated memory to open.
    //

    ULONG64 DedicatedMemoryTypeId;

    //
    // Attributes and desired access for the new handle to be opened and stored
    // in DedicatedMemoryPartitionHandle.
    //

    ULONG HandleAttributes;
    ACCESS_MASK DesiredAccess;

    //
    // Returned handle to the opened dedicated memory partition.
    //

    HANDLE DedicatedMemoryPartitionHandle;

} MEMORY_PARTITION_DEDICATED_MEMORY_OPEN_INFORMATION, * PMEMORY_PARTITION_DEDICATED_MEMORY_OPEN_INFORMATION;

typedef enum MEM_SECTION_EXTENDED_PARAMETER_TYPE {
    MemSectionExtendedParameterInvalidType = 0,
    MemSectionExtendedParameterUserPhysicalFlags,
    MemSectionExtendedParameterNumaNode,
    MemSectionExtendedParameterSigningLevel,
    MemSectionExtendedParameterMax
} MEM_SECTION_EXTENDED_PARAMETER_TYPE, * PMEM_SECTION_EXTENDED_PARAMETER_TYPE;

#endif // WDK_NTDDI_VERSION <= NTDDI_WIN10_RS4

#if (NTDDI_VERSION >= NTDDI_WIN10_RS4)
_Must_inspect_result_
__drv_allocatesMem(Mem)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAllocateVirtualMemoryEx(
    _In_ HANDLE ProcessHandle,
    _Inout_ _At_(*BaseAddress, _Readable_bytes_(*RegionSize) _Writable_bytes_(*RegionSize) _Post_readable_byte_size_(*RegionSize)) PVOID* BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG AllocationType,
    _In_ ULONG PageProtection,
    _Inout_updates_opt_(ExtendedParameterCount) PMEM_EXTENDED_PARAMETER ExtendedParameters,
    _In_ ULONG ExtendedParameterCount
);

_Must_inspect_result_
_IRQL_requires_max_(PASSIVE_LEVEL)
_When_(return == 0, __drv_allocatesMem(Region))
NTSYSAPI
NTSTATUS
NTAPI
ZwAllocateVirtualMemoryEx(
    _In_ HANDLE ProcessHandle,
    _Inout_ _At_(*BaseAddress, _Readable_bytes_(*RegionSize) _Writable_bytes_(*RegionSize) _Post_readable_byte_size_(*RegionSize)) PVOID * BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG AllocationType,
    _In_ ULONG PageProtection,
    _Inout_updates_opt_(ExtendedParameterCount) PMEM_EXTENDED_PARAMETER ExtendedParameters,
    _In_ ULONG ExtendedParameterCount
);
#endif // NTDDI_VERSION >= NTDDI_WIN10_RS4

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtFreeVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ __drv_freesMem(Mem) PVOID* BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG FreeType
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_When_(return == 0, __drv_freesMem(Region))
NTSYSAPI
NTSTATUS
NTAPI
ZwFreeVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID * BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG FreeType
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtReadVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _Out_writes_bytes_(BufferSize) PVOID Buffer,
    _In_ SIZE_T BufferSize,
    _Out_opt_ PSIZE_T NumberOfBytesRead
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwReadVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _Out_writes_bytes_(BufferSize) PVOID Buffer,
    _In_ SIZE_T BufferSize,
    _Out_opt_ PSIZE_T NumberOfBytesRead
);

#if (NTDDI_VERSION >= NTDDI_WIN10_CO)
// rev
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtReadVirtualMemoryEx(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _Out_writes_bytes_(BufferSize) PVOID Buffer,
    _In_ SIZE_T BufferSize,
    _Out_opt_ PSIZE_T NumberOfBytesRead,
    _In_ ULONG Flags
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwReadVirtualMemoryEx(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _Out_writes_bytes_(BufferSize) PVOID Buffer,
    _In_ SIZE_T BufferSize,
    _Out_opt_ PSIZE_T NumberOfBytesRead,
    _In_ ULONG Flags
);
#endif

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtWriteVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ SIZE_T BufferSize,
    _Out_opt_ PSIZE_T NumberOfBytesWritten
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwWriteVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ SIZE_T BufferSize,
    _Out_opt_ PSIZE_T NumberOfBytesWritten
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtProtectVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID* BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG NewProtect,
    _Out_ PULONG OldProtect
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwProtectVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID* BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG NewProtect,
    _Out_ PULONG OldProtect
);

_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQueryVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_ MEMORY_INFORMATION_CLASS MemoryInformationClass,
    _Out_writes_bytes_(MemoryInformationLength) PVOID MemoryInformation,
    _In_ SIZE_T MemoryInformationLength,
    _Out_opt_ PSIZE_T ReturnLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
ZwQueryVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_ MEMORY_INFORMATION_CLASS MemoryInformationClass,
    _Out_writes_bytes_(MemoryInformationLength) PVOID MemoryInformation,
    _In_ SIZE_T MemoryInformationLength,
    _Out_opt_ PSIZE_T ReturnLength
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtFlushVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID* BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _Out_ PIO_STATUS_BLOCK IoStatus
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwFlushVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID* BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _Out_ PIO_STATUS_BLOCK IoStatus
);

// begin_private
#ifndef _KERNEL_MODE
typedef enum _VIRTUAL_MEMORY_INFORMATION_CLASS
{
    VmPrefetchInformation,                  // ULONG
    VmPagePriorityInformation,              // OFFER_PRIORITY
    VmCfgCallTargetInformation,             // CFG_CALL_TARGET_LIST_INFORMATION // REDSTONE2
    VmPageDirtyStateInformation,            // REDSTONE3
    VmImageHotPatchInformation,             // 19H1
    VmPhysicalContiguityInformation,        // 20H1
    VmVirtualMachinePrepopulateInformation,
    VmRemoveFromWorkingSetInformation,
    MaxVmInfoClass
} VIRTUAL_MEMORY_INFORMATION_CLASS;
#else
#define VmPrefetchInformation                   ((_VIRTUAL_MEMORY_INFORMATION_CLASS)0)
#define VmPagePriorityInformation               ((_VIRTUAL_MEMORY_INFORMATION_CLASS)1)
#define VmCfgCallTargetInformation              ((_VIRTUAL_MEMORY_INFORMATION_CLASS)2)
#define VmPageDirtyStateInformation             ((_VIRTUAL_MEMORY_INFORMATION_CLASS)3)
#define VmImageHotPatchInformation              ((_VIRTUAL_MEMORY_INFORMATION_CLASS)4)
#define VmPhysicalContiguityInformation         ((_VIRTUAL_MEMORY_INFORMATION_CLASS)5)
#define VmVirtualMachinePrepopulateInformation  ((_VIRTUAL_MEMORY_INFORMATION_CLASS)6)
#define VmRemoveFromWorkingSetInformation       ((_VIRTUAL_MEMORY_INFORMATION_CLASS)7)
#define MaxVmInfoClass                          ((_VIRTUAL_MEMORY_INFORMATION_CLASS)8)
#endif // !_KERNEL_MODE

#ifndef _KERNEL_MODE
typedef struct _MEMORY_RANGE_ENTRY
{
    PVOID VirtualAddress;
    SIZE_T NumberOfBytes;
} MEMORY_RANGE_ENTRY, * PMEMORY_RANGE_ENTRY;
#endif // !_KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_WIN10_RS2)

#if defined(_KERNEL_MODE) && !defined(_WINDOWS_)

//
// Define flags for setting process CFG valid call target entries.
//

//
// Call target should be made valid.  If not set, the call target is made
// invalid.  Input flag.
//

#define CFG_CALL_TARGET_VALID                               (0x00000001) 

//
// Call target has been successfully processed.  Used to report to the caller
// how much progress has been made.  Output flag.
//

#define CFG_CALL_TARGET_PROCESSED                           (0x00000002)

//
// Call target should be made valid only if it is suppressed export.
// What this flag means is that it can *only* be used on a cell which is
// currently in the CFG export suppressed state (only considered for export
// suppressed processes and not legacy CFG processes!), and it is also
// allowed to be used even if the process is a restricted (i.e. no ACG) process.
//

#define CFG_CALL_TARGET_CONVERT_EXPORT_SUPPRESSED_TO_VALID  (0x00000004)

//
// Call target should be made into an XFG call target.
//

#define CFG_CALL_TARGET_VALID_XFG                           (0x00000008)

//
// Call target should be made valid only if it is already an XFG target
// in a process which has XFG audit mode enabled.
//

#define CFG_CALL_TARGET_CONVERT_XFG_TO_CFG                  (0x00000010)

typedef struct _CFG_CALL_TARGET_INFO {
    ULONG_PTR Offset;
    ULONG_PTR Flags;
} CFG_CALL_TARGET_INFO, * PCFG_CALL_TARGET_INFO;
#endif // _KERNEL_MODE

typedef struct _CFG_CALL_TARGET_LIST_INFORMATION
{
    ULONG NumberOfEntries;
    ULONG Reserved;
    PULONG NumberOfEntriesProcessed;
    PCFG_CALL_TARGET_INFO CallTargetInfo;
    PVOID Section; // since REDSTONE5
    ULONGLONG FileOffset;
} CFG_CALL_TARGET_LIST_INFORMATION, * PCFG_CALL_TARGET_LIST_INFORMATION;

#endif // NTDDI_VERSION >= NTDDI_WIN10_RS2

// end_private

#if (NTDDI_VERSION >= NTDDI_WIN8)
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_ VIRTUAL_MEMORY_INFORMATION_CLASS VmInformationClass,
    _In_ ULONG_PTR NumberOfEntries,
    _In_reads_(NumberOfEntries) PMEMORY_RANGE_ENTRY VirtualAddresses,
    _In_reads_bytes_(VmInformationLength) PVOID VmInformation,
    _In_ ULONG VmInformationLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
ZwSetInformationVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_ VIRTUAL_MEMORY_INFORMATION_CLASS VmInformationClass,
    _In_ ULONG_PTR NumberOfEntries,
    _In_reads_(NumberOfEntries) PMEMORY_RANGE_ENTRY VirtualAddresses,
    _In_reads_bytes_(VmInformationLength) PVOID VmInformation,
    _In_ ULONG VmInformationLength
);
#endif

#define MAP_PROCESS 1
#define MAP_SYSTEM  2

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtLockVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID* BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG MapType
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwLockVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID* BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG MapType
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtUnlockVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID* BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG MapType
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwUnlockVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID* BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG MapType
);

//
// Sections
//

_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateSection(
    _Out_ PHANDLE SectionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PLARGE_INTEGER MaximumSize,
    _In_ ULONG SectionPageProtection,
    _In_ ULONG AllocationAttributes,
    _In_opt_ HANDLE FileHandle
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateSection(
    _Out_ PHANDLE SectionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PLARGE_INTEGER MaximumSize,
    _In_ ULONG SectionPageProtection,
    _In_ ULONG AllocationAttributes,
    _In_opt_ HANDLE FileHandle
);

#if (NTDDI_VERSION >= NTDDI_WIN10_RS5)

_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateSectionEx(
    _Out_ PHANDLE SectionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PLARGE_INTEGER MaximumSize,
    _In_ ULONG SectionPageProtection,
    _In_ ULONG AllocationAttributes,
    _In_opt_ HANDLE FileHandle,
    _Inout_updates_opt_(ExtendedParameterCount) PMEM_EXTENDED_PARAMETER ExtendedParameters,
    _In_ ULONG ExtendedParameterCount
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateSectionEx(
    _Out_ PHANDLE SectionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_opt_ PLARGE_INTEGER MaximumSize,
    _In_ ULONG SectionPageProtection,
    _In_ ULONG AllocationAttributes,
    _In_opt_ HANDLE FileHandle,
    _Inout_updates_opt_(ExtendedParameterCount) PMEM_EXTENDED_PARAMETER ExtendedParameters,
    _In_ ULONG ExtendedParameterCount
);
#endif // NTDDI_VERSION >= NTDDI_WIN10_RS5

_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenSection(
    _Out_ PHANDLE SectionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwOpenSection(
    _Out_ PHANDLE SectionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
);

_Must_inspect_result_
_Post_satisfies_(*ViewSize >= _Old_(*ViewSize))
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtMapViewOfSection(
    _In_ HANDLE SectionHandle,
    _In_ HANDLE ProcessHandle,
    _Inout_ _At_(*BaseAddress, _Readable_bytes_(*ViewSize) _Writable_bytes_(*ViewSize) _Post_readable_byte_size_(*ViewSize)) PVOID* BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _In_ SIZE_T CommitSize,
    _Inout_opt_ PLARGE_INTEGER SectionOffset,
    _Inout_ PSIZE_T ViewSize,
    _In_ SECTION_INHERIT InheritDisposition,
    _In_ ULONG AllocationType,
    _In_ ULONG Win32Protect
);

_Must_inspect_result_
_Post_satisfies_(*ViewSize >= _Old_(*ViewSize))
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwMapViewOfSection(
    _In_ HANDLE SectionHandle,
    _In_ HANDLE ProcessHandle,
    _Outptr_result_bytebuffer_(*ViewSize) PVOID* BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _In_ SIZE_T CommitSize,
    _Inout_opt_ PLARGE_INTEGER SectionOffset,
    _Inout_ PSIZE_T ViewSize,
    _In_ SECTION_INHERIT InheritDisposition,
    _In_ ULONG AllocationType,
    _In_ ULONG Win32Protect
);

#if (NTDDI_VERSION >= NTDDI_WIN10_RS4)
_Must_inspect_result_
_Post_satisfies_(*ViewSize >= _Old_(*ViewSize))
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtMapViewOfSectionEx(
    _In_ HANDLE SectionHandle,
    _In_ HANDLE ProcessHandle,
    _Inout_ _At_(*BaseAddress, _Readable_bytes_(*ViewSize) _Writable_bytes_(*ViewSize) _Post_readable_byte_size_(*ViewSize)) PVOID* BaseAddress,
    _Inout_opt_ PLARGE_INTEGER SectionOffset,
    _Inout_ PSIZE_T ViewSize,
    _In_ ULONG AllocationType,
    _In_ ULONG Win32Protect,
    _Inout_updates_opt_(ExtendedParameterCount) PMEM_EXTENDED_PARAMETER ExtendedParameters,
    _In_ ULONG ExtendedParameterCount
);

_Must_inspect_result_
_Post_satisfies_(*ViewSize >= _Old_(*ViewSize))
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwMapViewOfSectionEx(
    _In_ HANDLE SectionHandle,
    _In_ HANDLE ProcessHandle,
    _Inout_ _At_(*BaseAddress, _Readable_bytes_(*ViewSize) _Writable_bytes_(*ViewSize) _Post_readable_byte_size_(*ViewSize)) PVOID* BaseAddress,
    _Inout_opt_ PLARGE_INTEGER SectionOffset,
    _Inout_ PSIZE_T ViewSize,
    _In_ ULONG AllocationType,
    _In_ ULONG Win32Protect,
    _Inout_updates_opt_(ExtendedParameterCount) PMEM_EXTENDED_PARAMETER ExtendedParameters,
    _In_ ULONG ExtendedParameterCount
);
#endif // NTDDI_VERSION >= NTDDI_WIN10_RS4

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtUnmapViewOfSection(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwUnmapViewOfSection(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress
);

#if (NTDDI_VERSION >= NTDDI_WIN8)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtUnmapViewOfSectionEx(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_ ULONG Flags
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwUnmapViewOfSectionEx(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_ ULONG Flags
);
#endif

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtExtendSection(
    _In_ HANDLE SectionHandle,
    _Inout_ PLARGE_INTEGER NewSectionSize
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwExtendSection(
    _In_ HANDLE SectionHandle,
    _Inout_ PLARGE_INTEGER NewSectionSize
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtQuerySection(
    _In_ HANDLE SectionHandle,
    _In_ SECTION_INFORMATION_CLASS SectionInformationClass,
    _Out_writes_bytes_(SectionInformationLength) PVOID SectionInformation,
    _In_ SIZE_T SectionInformationLength,
    _Out_opt_ PSIZE_T ReturnLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwQuerySection(
    _In_ HANDLE SectionHandle,
    _In_ SECTION_INFORMATION_CLASS SectionInformationClass,
    _Out_writes_bytes_(SectionInformationLength) PVOID SectionInformation,
    _In_ SIZE_T SectionInformationLength,
    _Out_opt_ PSIZE_T ReturnLength
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAreMappedFilesTheSame(
    _In_ PVOID File1MappedAsAnImage,
    _In_ PVOID File2MappedAsFile
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAreMappedFilesTheSame(
    _In_ PVOID File1MappedAsAnImage,
    _In_ PVOID File2MappedAsFile
);

//
// Partitions
//

#if !defined(_KERNEL_MODE) || (WDK_NTDDI_VERSION <= NTDDI_WIN10_VB)
// private
typedef enum _PARTITION_INFORMATION_CLASS
{
    SystemMemoryPartitionInformation,           // q: MEMORY_PARTITION_CONFIGURATION_INFORMATION
    SystemMemoryPartitionMoveMemory,            // s: MEMORY_PARTITION_TRANSFER_INFORMATION
    SystemMemoryPartitionAddPagefile,           // s: MEMORY_PARTITION_PAGEFILE_INFORMATION
    SystemMemoryPartitionCombineMemory,         // q; s: MEMORY_PARTITION_PAGE_COMBINE_INFORMATION
    SystemMemoryPartitionInitialAddMemory,      // q; s: MEMORY_PARTITION_INITIAL_ADD_INFORMATION
    SystemMemoryPartitionGetMemoryEvents,       // MEMORY_PARTITION_MEMORY_EVENTS_INFORMATION // since REDSTONE2
    SystemMemoryPartitionSetAttributes,
    SystemMemoryPartitionNodeInformation,
    SystemMemoryPartitionCreateLargePages,
    SystemMemoryPartitionDedicatedMemoryInformation,
    SystemMemoryPartitionOpenDedicatedMemory,   // 10
    SystemMemoryPartitionMemoryChargeAttributes,
    SystemMemoryPartitionClearAttributes,
    SystemMemoryPartitionSetMemoryThresholds,   // since WIN11
    SystemMemoryPartitionMax
} PARTITION_INFORMATION_CLASS, * PPARTITION_INFORMATION_CLASS;
#else
#define SystemMemoryPartitionInformation                ((_PARTITION_INFORMATION_CLASS)0x0)
#define SystemMemoryPartitionMoveMemory                 ((_PARTITION_INFORMATION_CLASS)0x1)
#define SystemMemoryPartitionAddPagefile                ((_PARTITION_INFORMATION_CLASS)0x2)
#define SystemMemoryPartitionCombineMemory              ((_PARTITION_INFORMATION_CLASS)0x3)
#define SystemMemoryPartitionInitialAddMemory           ((_PARTITION_INFORMATION_CLASS)0x4)
#define SystemMemoryPartitionGetMemoryEvents            ((_PARTITION_INFORMATION_CLASS)0x5)
#define SystemMemoryPartitionSetAttributes              ((_PARTITION_INFORMATION_CLASS)0x6)
#define SystemMemoryPartitionNodeInformation            ((_PARTITION_INFORMATION_CLASS)0x7)
#define SystemMemoryPartitionCreateLargePages           ((_PARTITION_INFORMATION_CLASS)0x8)
#define SystemMemoryPartitionDedicatedMemoryInformation ((_PARTITION_INFORMATION_CLASS)0x9)
#define SystemMemoryPartitionOpenDedicatedMemory        ((_PARTITION_INFORMATION_CLASS)0xA)
#define SystemMemoryPartitionMemoryChargeAttributes     ((_PARTITION_INFORMATION_CLASS)0xB)
#define SystemMemoryPartitionClearAttributes            ((_PARTITION_INFORMATION_CLASS)0xC)
#define SystemMemoryPartitionSetMemoryThresholds        ((_PARTITION_INFORMATION_CLASS)0xD)
#define SystemMemoryPartitionMax                        ((_PARTITION_INFORMATION_CLASS)0xE)
#endif //!_KERNEL_MODE

// private
typedef struct _MEMORY_PARTITION_CONFIGURATION_INFORMATION
{
    ULONG Flags;
    ULONG NumaNode;
    ULONG Channel;
    ULONG NumberOfNumaNodes;
    ULONG_PTR ResidentAvailablePages;
    ULONG_PTR CommittedPages;
    ULONG_PTR CommitLimit;
    ULONG_PTR PeakCommitment;
    ULONG_PTR TotalNumberOfPages;
    ULONG_PTR AvailablePages;
    ULONG_PTR ZeroPages;
    ULONG_PTR FreePages;
    ULONG_PTR StandbyPages;
    ULONG_PTR StandbyPageCountByPriority[8]; // since REDSTONE2
    ULONG_PTR RepurposedPagesByPriority[8];
    ULONG_PTR MaximumCommitLimit;
    ULONG_PTR Reserved; // DonatedPagesToPartitions
    ULONG PartitionId; // since REDSTONE3
} MEMORY_PARTITION_CONFIGURATION_INFORMATION, * PMEMORY_PARTITION_CONFIGURATION_INFORMATION;

// private
typedef struct _MEMORY_PARTITION_TRANSFER_INFORMATION
{
    ULONG_PTR NumberOfPages;
    ULONG NumaNode;
    ULONG Flags;
} MEMORY_PARTITION_TRANSFER_INFORMATION, * PMEMORY_PARTITION_TRANSFER_INFORMATION;

// private
typedef struct _MEMORY_PARTITION_PAGEFILE_INFORMATION
{
    UNICODE_STRING PageFileName;
    LARGE_INTEGER MinimumSize;
    LARGE_INTEGER MaximumSize;
    ULONG Flags;
} MEMORY_PARTITION_PAGEFILE_INFORMATION, * PMEMORY_PARTITION_PAGEFILE_INFORMATION;

// private
typedef struct _MEMORY_PARTITION_PAGE_COMBINE_INFORMATION
{
    HANDLE StopHandle;
    ULONG Flags;
    ULONG_PTR TotalNumberOfPages;
} MEMORY_PARTITION_PAGE_COMBINE_INFORMATION, * PMEMORY_PARTITION_PAGE_COMBINE_INFORMATION;

// private
typedef struct _MEMORY_PARTITION_PAGE_RANGE
{
    ULONG_PTR StartPage;
    ULONG_PTR NumberOfPages;
} MEMORY_PARTITION_PAGE_RANGE, * PMEMORY_PARTITION_PAGE_RANGE;

// private
typedef struct _MEMORY_PARTITION_INITIAL_ADD_INFORMATION
{
    ULONG Flags;
    ULONG NumberOfRanges;
    ULONG_PTR NumberOfPagesAdded;
    MEMORY_PARTITION_PAGE_RANGE PartitionRanges[1];
} MEMORY_PARTITION_INITIAL_ADD_INFORMATION, * PMEMORY_PARTITION_INITIAL_ADD_INFORMATION;

// private
typedef struct _MEMORY_PARTITION_MEMORY_EVENTS_INFORMATION
{
    union
    {
        struct
        {
            ULONG CommitEvents : 1;
            ULONG Spare : 31;
        };
        ULONG AllFlags;
    } Flags;

    ULONG HandleAttributes;
    ULONG DesiredAccess;
    HANDLE LowCommitCondition; // \KernelObjects\LowCommitCondition
    HANDLE HighCommitCondition; // \KernelObjects\HighCommitCondition
    HANDLE MaximumCommitCondition; // \KernelObjects\MaximumCommitCondition
} MEMORY_PARTITION_MEMORY_EVENTS_INFORMATION, * PMEMORY_PARTITION_MEMORY_EVENTS_INFORMATION;

#if (NTDDI_VERSION >= NTDDI_WIN10)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreatePartition(
    _In_opt_ HANDLE ParentPartitionHandle,
    _Out_ PHANDLE PartitionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG PreferredNode
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreatePartition(
    _In_opt_ HANDLE ParentPartitionHandle,
    _Out_ PHANDLE PartitionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG PreferredNode
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenPartition(
    _Out_ PHANDLE PartitionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwOpenPartition(
    _Out_ PHANDLE PartitionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes
);

_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtManagePartition(
    _In_ HANDLE TargetHandle,
    _In_opt_ HANDLE SourceHandle,
    _In_ PARTITION_INFORMATION_CLASS PartitionInformationClass,
    _Inout_updates_bytes_(PartitionInformationLength) PVOID PartitionInformation,
    _In_ ULONG PartitionInformationLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwManagePartition(
    _In_ HANDLE TargetHandle,
    _In_opt_ HANDLE SourceHandle,
    _In_ PARTITION_INFORMATION_CLASS PartitionInformationClass,
    _Inout_updates_bytes_(PartitionInformationLength) PVOID PartitionInformation,
    _In_ ULONG PartitionInformationLength
);
#endif // NTDDI_VERSION >= NTDDI_WIN10

//
// User physical pages
//

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtMapUserPhysicalPages(
    _In_ PVOID VirtualAddress,
    _In_ ULONG_PTR NumberOfPages,
    _In_reads_opt_(NumberOfPages) PULONG_PTR UserPfnArray
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwMapUserPhysicalPages(
    _In_ PVOID VirtualAddress,
    _In_ ULONG_PTR NumberOfPages,
    _In_reads_opt_(NumberOfPages) PULONG_PTR UserPfnArray
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtMapUserPhysicalPagesScatter(
    _In_reads_(NumberOfPages) PVOID* VirtualAddresses,
    _In_ ULONG_PTR NumberOfPages,
    _In_reads_opt_(NumberOfPages) PULONG_PTR UserPfnArray
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwMapUserPhysicalPagesScatter(
    _In_reads_(NumberOfPages) PVOID* VirtualAddresses,
    _In_ ULONG_PTR NumberOfPages,
    _In_reads_opt_(NumberOfPages) PULONG_PTR UserPfnArray
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAllocateUserPhysicalPages(
    _In_ HANDLE ProcessHandle,
    _Inout_ PULONG_PTR NumberOfPages,
    _Out_writes_(*NumberOfPages) PULONG_PTR UserPfnArray
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAllocateUserPhysicalPages(
    _In_ HANDLE ProcessHandle,
    _Inout_ PULONG_PTR NumberOfPages,
    _Out_writes_(*NumberOfPages) PULONG_PTR UserPfnArray
);

#if (NTDDI_VERSION >= NTDDI_WIN10_VB)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAllocateUserPhysicalPagesEx(
    _In_ HANDLE ProcessHandle,
    _Inout_ PULONG_PTR NumberOfPages,
    _Out_writes_(*NumberOfPages) PULONG_PTR UserPfnArray,
    _Inout_updates_opt_(ParameterCount) PMEM_EXTENDED_PARAMETER ExtendedParameters,
    _In_ ULONG ExtendedParameterCount
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAllocateUserPhysicalPagesEx(
    _In_ HANDLE ProcessHandle,
    _Inout_ PULONG_PTR NumberOfPages,
    _Out_writes_(*NumberOfPages) PULONG_PTR UserPfnArray,
    _Inout_updates_opt_(ParameterCount) PMEM_EXTENDED_PARAMETER ExtendedParameters,
    _In_ ULONG ExtendedParameterCount
);
#endif // NTDDI_VERSION >= NTDDI_WIN10_VB

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtFreeUserPhysicalPages(
    _In_ HANDLE ProcessHandle,
    _Inout_ PULONG_PTR NumberOfPages,
    _In_reads_(*NumberOfPages) PULONG_PTR UserPfnArray
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwFreeUserPhysicalPages(
    _In_ HANDLE ProcessHandle,
    _Inout_ PULONG_PTR NumberOfPages,
    _In_reads_(*NumberOfPages) PULONG_PTR UserPfnArray
);

// Misc.

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtGetWriteWatch(
    _In_ HANDLE ProcessHandle,
    _In_ ULONG Flags,
    _In_ PVOID BaseAddress,
    _In_ SIZE_T RegionSize,
    _Out_writes_(*EntriesInUserAddressArray) PVOID* UserAddressArray,
    _Inout_ PULONG_PTR EntriesInUserAddressArray,
    _Out_ PULONG Granularity
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwGetWriteWatch(
    _In_ HANDLE ProcessHandle,
    _In_ ULONG Flags,
    _In_ PVOID BaseAddress,
    _In_ SIZE_T RegionSize,
    _Out_writes_(*EntriesInUserAddressArray) PVOID* UserAddressArray,
    _Inout_ PULONG_PTR EntriesInUserAddressArray,
    _Out_ PULONG Granularity
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtResetWriteWatch(
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress,
    _In_ SIZE_T RegionSize
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwResetWriteWatch(
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress,
    _In_ SIZE_T RegionSize
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreatePagingFile(
    _In_ PUNICODE_STRING PageFileName,
    _In_ PLARGE_INTEGER MinimumSize,
    _In_ PLARGE_INTEGER MaximumSize,
    _In_ ULONG Priority
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreatePagingFile(
    _In_ PUNICODE_STRING PageFileName,
    _In_ PLARGE_INTEGER MinimumSize,
    _In_ PLARGE_INTEGER MaximumSize,
    _In_ ULONG Priority
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtFlushInstructionCache(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_ SIZE_T Length
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwFlushInstructionCache(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_ SIZE_T Length
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtFlushWriteBuffer(
    VOID
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwFlushWriteBuffer(
    VOID
);

//
// Enclave support
//

#if (NTDDI_VERSION >= NTDDI_WIN10_TH2)
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateEnclave(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID* BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _In_ SIZE_T Size,
    _In_ SIZE_T InitialCommitment,
    _In_ ULONG EnclaveType,
    _In_reads_bytes_(EnclaveInformationLength) PVOID EnclaveInformation,
    _In_ ULONG EnclaveInformationLength,
    _Out_opt_ PULONG EnclaveError
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateEnclave(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID* BaseAddress,
    _In_ ULONG_PTR ZeroBits,
    _In_ SIZE_T Size,
    _In_ SIZE_T InitialCommitment,
    _In_ ULONG EnclaveType,
    _In_reads_bytes_(EnclaveInformationLength) PVOID EnclaveInformation,
    _In_ ULONG EnclaveInformationLength,
    _Out_opt_ PULONG EnclaveError
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtLoadEnclaveData(
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ SIZE_T BufferSize,
    _In_ ULONG Protect,
    _In_reads_bytes_(PageInformationLength) PVOID PageInformation,
    _In_ ULONG PageInformationLength,
    _Out_opt_ PSIZE_T NumberOfBytesWritten,
    _Out_opt_ PULONG EnclaveError
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwLoadEnclaveData(
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ SIZE_T BufferSize,
    _In_ ULONG Protect,
    _In_reads_bytes_(PageInformationLength) PVOID PageInformation,
    _In_ ULONG PageInformationLength,
    _Out_opt_ PSIZE_T NumberOfBytesWritten,
    _Out_opt_ PULONG EnclaveError
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtInitializeEnclave(
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress,
    _In_reads_bytes_(EnclaveInformationLength) PVOID EnclaveInformation,
    _In_ ULONG EnclaveInformationLength,
    _Out_opt_ PULONG EnclaveError
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwInitializeEnclave(
    _In_ HANDLE ProcessHandle,
    _In_ PVOID BaseAddress,
    _In_reads_bytes_(EnclaveInformationLength) PVOID EnclaveInformation,
    _In_ ULONG EnclaveInformationLength,
    _Out_opt_ PULONG EnclaveError
);

#endif // NTDDI_VERSION >= NTDDI_WIN10_TH2

#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)

#define TERMINATE_ENCLAVE_FLAG_NO_WAIT    0x00000001ul
#define TERMINATE_ENCLAVE_FLAG_WAIT_ERROR 0x00000004ul // STATUS_PENDING -> STATUS_ENCLAVE_NOT_TERMINATED
#define TERMINATE_ENCLAVE_VALID_FLAGS     0x00000005ul

// rev
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtTerminateEnclave(
    _In_ PVOID BaseAddress,
    _In_ ULONG Flags // TERMINATE_ENCLAVE_FLAG_*
);

// rev
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwTerminateEnclave(
    _In_ PVOID BaseAddress,
    _In_ BOOLEAN WaitForThread
);

#ifdef _KERNEL_MODE
typedef PVOID(NTAPI* PENCLAVE_ROUTINE)(
    PVOID lpThreadParameter
    );
typedef PENCLAVE_ROUTINE LPENCLAVE_ROUTINE;
#endif // _KERNEL_MODE

// rev
#define ENCLAVE_CALL_VALID_FLAGS  0x00000001ul
#define ENCLAVE_CALL_FLAG_NO_WAIT 0x00000001ul

// rev
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCallEnclave(
    _In_ PENCLAVE_ROUTINE Routine,
    _In_ PVOID Reserved,              // reserved for dispatch (RtlEnclaveCallDispatch)
    _In_ ULONG Flags,                 // ENCLAVE_CALL_FLAG_*
    _Inout_ PVOID* RoutineParamReturn // input routine parameter, output routine return value
);

// rev
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCallEnclave(
    _In_ PENCLAVE_ROUTINE Routine,
    _In_ PVOID Reserved,
    _In_ ULONG Flags,
    _Inout_ PVOID* RoutineParamReturn
);

#endif // NTDDI_VERSION >= NTDDI_VERSION_RS3

//
// Only Kernel
//

#ifdef _KERNEL_MODE

// Section

NTSYSAPI
NTSTATUS
NTAPI
MmCreateSection(
    _Deref_out_ PVOID* SectionObject,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ PLARGE_INTEGER InputMaximumSize,
    _In_ ULONG SectionPageProtection,
    _In_ ULONG AllocationAttributes,
    _In_opt_ HANDLE FileHandle,
    _In_opt_ PFILE_OBJECT FileObject
);

NTSYSAPI
NTSTATUS
NTAPI
MmMapViewOfSection(
    _In_ PVOID SectionToMap,
    _In_ PEPROCESS Process,
    __deref_inout_bcount(*CapturedViewSize) PVOID* CapturedBase,
    _In_ ULONG_PTR ZeroBits,
    _In_ SIZE_T CommitSize,
    _Inout_ PLARGE_INTEGER SectionOffset,
    _Inout_ PSIZE_T CapturedViewSize,
    _In_ SECTION_INHERIT InheritDisposition,
    _In_ ULONG AllocationType,
    _In_ ULONG Win32Protect
);

NTSYSAPI
NTSTATUS
NTAPI
MmUnmapViewOfSection(
    _In_ PEPROCESS Process,
    _In_ PVOID BaseAddress
);

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
BOOLEAN
MmForceSectionClosed(
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
    _In_ BOOLEAN DelayClose
);

_IRQL_requires_max_(APC_LEVEL)
NTKERNELAPI
BOOLEAN
MmForceSectionClosedEx(
    _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
    _In_ ULONG ForceCloseFlags
);

// Virtual Memory

NTSYSAPI
NTSTATUS
NTAPI
MmCopyVirtualMemory(
    _In_ PEPROCESS   aFromProcess,
    _In_ CONST PVOID aFromAddress,
    _In_ PEPROCESS   aToProcess,
    _Out_ PVOID      aToAddress,
    _In_ SIZE_T      aBufferSize,
    _In_ KPROCESSOR_MODE aPreviousMode,
    _Out_ PSIZE_T    aNumberOfBytesCopied
);


#endif // _KERNEL_MODE

VEIL_END()

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
