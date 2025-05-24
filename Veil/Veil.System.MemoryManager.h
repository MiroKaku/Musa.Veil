/*
 * PROJECT:   Veil
 * FILE:      Veil.System.MemoryManager.h
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
// Memory Protection Constants
//

#define PAGE_NOACCESS                   0x01    // Disables all access to the committed region of pages. An attempt to read from, write to, or execute the committed region results in an access violation.
#define PAGE_READONLY                   0x02    // Enables read-only access to the committed region of pages. An attempt to write or execute the committed region results in an access violation.
#define PAGE_READWRITE                  0x04    // Enables read-only or read/write access to the committed region of pages.
#define PAGE_WRITECOPY                  0x08    // Enables read-only or copy-on-write access to a mapped view of a file mapping object. 
#define PAGE_EXECUTE                    0x10    // Enables execute access to the committed region of pages. An attempt to write to the committed region results in an access violation.
#define PAGE_EXECUTE_READ               0x20    // Enables execute or read-only access to the committed region of pages. An attempt to write to the committed region results in an access violation.
#define PAGE_EXECUTE_READWRITE          0x40    // Enables execute, read-only, or read/write access to the committed region of pages.
#define PAGE_EXECUTE_WRITECOPY          0x80    // Enables execute, read-only, or copy-on-write access to a mapped view of a file mapping object.
#define PAGE_GUARD                      0x100   // Pages in the region become guard pages. Any attempt to access a guard page causes the system to raise a STATUS_GUARD_PAGE_VIOLATION exception.
#define PAGE_NOCACHE                    0x200   // Sets all pages to be non-cachable. Applications should not use this attribute. Using interlocked functions with memory that is mapped with SEC_NOCACHE can result in an EXCEPTION_ILLEGAL_INSTRUCTION exception.
#define PAGE_WRITECOMBINE               0x400   // Sets all pages to be write-combined. Applications should not use this attribute. Using interlocked functions with memory that is mapped with SEC_NOCACHE can result in an EXCEPTION_ILLEGAL_INSTRUCTION exception.
#define PAGE_GRAPHICS_NOACCESS          0x0800
#define PAGE_GRAPHICS_READONLY          0x1000
#define PAGE_GRAPHICS_READWRITE         0x2000
#define PAGE_GRAPHICS_EXECUTE           0x4000
#define PAGE_GRAPHICS_EXECUTE_READ      0x8000
#define PAGE_GRAPHICS_EXECUTE_READWRITE 0x10000
#define PAGE_GRAPHICS_COHERENT          0x20000
#define PAGE_GRAPHICS_NOCACHE           0x40000
#define PAGE_ENCLAVE_THREAD_CONTROL     0x80000000  // Pages in the region contain a thread control structure (TCS) from the Intel Software Guard Extensions programming model.
#define PAGE_REVERT_TO_FILE_MAP         0x80000000  // Pages in the region can revert modified copy-on-write pages to the original unmodified page when using the mapped view of a file mapping object.
#define PAGE_TARGETS_NO_UPDATE          0x40000000  // Pages in the region will not update the CFG bitmap when the protection changes. The default behavior for VirtualProtect is to mark all locations as valid call targets for CFG.
#define PAGE_TARGETS_INVALID            0x40000000  // Pages in the region are excluded from the CFG bitmap as valid targets. Any indirect call to locations in those pages will terminate the process using the __fastfail intrinsic.
#define PAGE_ENCLAVE_UNVALIDATED        0x20000000  // Pages in the region are excluded from measurement with the EEXTEND instruction of the Intel Software Guard Extensions programming model.
#define PAGE_ENCLAVE_MASK               0x10000000
#ifndef PAGE_ENCLAVE_DECOMMIT
#define PAGE_ENCLAVE_DECOMMIT       (PAGE_ENCLAVE_MASK | 0)
#endif
#define PAGE_ENCLAVE_SS_FIRST       (PAGE_ENCLAVE_MASK | 1)
#define PAGE_ENCLAVE_SS_REST        (PAGE_ENCLAVE_MASK | 2)

//
// Memory Region and Section Constants
//

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
#define SEC_DRIVER_IMAGE                0x00100000  // rev
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
    MemoryImageExtensionInformation,        // MEMORY_IMAGE_EXTENSION_INFORMATION // since 24H2
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
#define MemoryImageExtensionInformation     ((_MEMORY_INFORMATION_CLASS)0xE)
#endif // !_KERNEL_MODE

// MEMORY_WORKING_SET_BLOCK->Protection
#define MEMORY_BLOCK_NOT_ACCESSED 0
#define MEMORY_BLOCK_READONLY 1
#define MEMORY_BLOCK_EXECUTABLE 2
#define MEMORY_BLOCK_EXECUTABLE_READONLY 3
#define MEMORY_BLOCK_READWRITE 4
#define MEMORY_BLOCK_COPYONWRITE 5
#define MEMORY_BLOCK_EXECUTABLE_READWRITE 6
#define MEMORY_BLOCK_EXECUTABLE_COPYONWRITE 7
#define MEMORY_BLOCK_NOT_ACCESSED_2 8
#define MEMORY_BLOCK_NON_CACHEABLE_READONLY 9
#define MEMORY_BLOCK_NON_CACHEABLE_EXECUTABLE 10
#define MEMORY_BLOCK_NON_CACHEABLE_EXECUTABLE_READONLY 11
#define MEMORY_BLOCK_NON_CACHEABLE_READWRITE 12
#define MEMORY_BLOCK_NON_CACHEABLE_COPYONWRITE 13
#define MEMORY_BLOCK_NON_CACHEABLE_EXECUTABLE_READWRITE 14
#define MEMORY_BLOCK_NON_CACHEABLE_EXECUTABLE_COPYONWRITE 15
#define MEMORY_BLOCK_NOT_ACCESSED_3 16
#define MEMORY_BLOCK_GUARD_READONLY 17
#define MEMORY_BLOCK_GUARD_EXECUTABLE 18
#define MEMORY_BLOCK_GUARD_EXECUTABLE_READONLY 19
#define MEMORY_BLOCK_GUARD_READWRITE 20
#define MEMORY_BLOCK_GUARD_COPYONWRITE 21
#define MEMORY_BLOCK_GUARD_EXECUTABLE_READWRITE 22
#define MEMORY_BLOCK_GUARD_EXECUTABLE_COPYONWRITE 23
#define MEMORY_BLOCK_NOT_ACCESSED_4 24
#define MEMORY_BLOCK_NON_CACHEABLE_GUARD_READONLY 25
#define MEMORY_BLOCK_NON_CACHEABLE_GUARD_EXECUTABLE 26
#define MEMORY_BLOCK_NON_CACHEABLE_GUARD_EXECUTABLE_READONLY 27
#define MEMORY_BLOCK_NON_CACHEABLE_GUARD_READWRITE 28
#define MEMORY_BLOCK_NON_CACHEABLE_GUARD_COPYONWRITE 29
#define MEMORY_BLOCK_NON_CACHEABLE_GUARD_EXECUTABLE_READWRITE 30
#define MEMORY_BLOCK_NON_CACHEABLE_GUARD_EXECUTABLE_COPYONWRITE 31

/**
 * The MEMORY_WORKING_SET_BLOCK structure contains working set information for a page.
 *
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/psapi/ns-psapi-psapi_working_set_block
 */
typedef struct _MEMORY_WORKING_SET_BLOCK
{
    ULONG_PTR Protection : 5;       // The protection attributes of the page. This member can be one of above MEMORY_BLOCK_* values.
    ULONG_PTR ShareCount : 3;       // The number of processes that share this page. The maximum value of this member is 7.
    ULONG_PTR Shared : 1;           // If this bit is 1, the page is sharable; otherwise, the page is not sharable.
    ULONG_PTR Node : 3;             // The NUMA node where the physical memory should reside.
#ifdef _WIN64
    ULONG_PTR VirtualPage : 52;     // The address of the page in the virtual address space.
#else
    ULONG VirtualPage : 20;         // The address of the page in the virtual address space.
#endif
} MEMORY_WORKING_SET_BLOCK, * PMEMORY_WORKING_SET_BLOCK;

/**
 * The MEMORY_WORKING_SET_INFORMATION structure contains working set information for a process.
 *
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/psapi/ns-psapi-psapi_working_set_information
 */
typedef struct _MEMORY_WORKING_SET_INFORMATION
{
    ULONG_PTR NumberOfEntries;
    _Field_size_(NumberOfEntries) MEMORY_WORKING_SET_BLOCK WorkingSetInfo[ANYSIZE_ARRAY];
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

typedef enum _MEMORY_WORKING_SET_EX_LOCATION
{
    MemoryLocationInvalid,
    MemoryLocationResident,
    MemoryLocationPagefile,
    MemoryLocationReserved
} MEMORY_WORKING_SET_EX_LOCATION;

/**
 * The MEMORY_WORKING_SET_EX_BLOCK structure contains extended working set information for a page.
 *
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/psapi/ns-psapi-psapi_working_set_ex_block
 */
typedef union _MEMORY_WORKING_SET_EX_BLOCK
{
    ULONG_PTR Flags;
    union
    {
        struct
        {
            ULONG_PTR Valid : 1;                    // If this bit is 1, the subsequent members are valid; otherwise they should be ignored.
            ULONG_PTR ShareCount : 3;               // The number of processes that share this page. The maximum value of this member is 7.
            ULONG_PTR Win32Protection : 11;         // The memory protection attributes of the page.
            ULONG_PTR Shared : 1;                   // If this bit is 1, the page can be shared.
            ULONG_PTR Node : 6;                     // The NUMA node. The maximum value of this member is 63.
            ULONG_PTR Locked : 1;                   // If this bit is 1, the virtual page is locked in physical memory.
            ULONG_PTR LargePage : 1;                // If this bit is 1, the page is a large page.
            ULONG_PTR Priority : 3;                 // The memory priority attributes of the page.
            ULONG_PTR Reserved : 3;
            ULONG_PTR SharedOriginal : 1;           // If this bit is 1, the page was not modified.
            ULONG_PTR Bad : 1;                      // If this bit is 1, the page is has been reported as bad.
        #ifdef _WIN64
            ULONG_PTR Win32GraphicsProtection : 4;  // The memory protection attributes of the page. // since 19H1
            ULONG_PTR ReservedUlong : 28;
        #endif
        };
        struct
        {
            ULONG_PTR Valid : 1;                    // If this bit is 0, the subsequent members are valid; otherwise they should be ignored.
            ULONG_PTR Reserved0 : 14;
            ULONG_PTR Shared : 1;                   // If this bit is 1, the page can be shared.
            ULONG_PTR Reserved1 : 5;
            ULONG_PTR PageTable : 1;
            ULONG_PTR Location : 2;                 // The memory location of the page.  MEMORY_WORKING_SET_EX_LOCATION
            ULONG_PTR Priority : 3;                 // The memory priority of the page.
            ULONG_PTR ModifiedList : 1;
            ULONG_PTR Reserved2 : 2;
            ULONG_PTR SharedOriginal : 1;           // If this bit is 1, the page was not modified.
            ULONG_PTR Bad : 1;                      // If this bit is 1, the page is has been reported as bad.
        #ifdef _WIN64
            ULONG_PTR ReservedUlong : 32;
        #endif
        } Invalid;
    };
} MEMORY_WORKING_SET_EX_BLOCK, * PMEMORY_WORKING_SET_EX_BLOCK;

/**
 * The MEMORY_WORKING_SET_EX_INFORMATION structure contains extended working set information for a process.
 *
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/psapi/ns-psapi-psapi_working_set_ex_information
 */
typedef struct _MEMORY_WORKING_SET_EX_INFORMATION
{
    PVOID VirtualAddress;                             // The virtual address.
    MEMORY_WORKING_SET_EX_BLOCK VirtualAttributes;    // The attributes of the page at VirtualAddress.
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
            ULONG ImageExtensionPresent : 1; // since 24H2
            ULONG Reserved : 25;
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

// private
typedef struct _RTL_SCP_CFG_ARM64_HEADER
{
    ULONG EcInvalidCallHandlerRva;
    ULONG EcCfgCheckRva;
    ULONG EcCfgCheckESRva;
    ULONG EcCallCheckRva;
    ULONG CpuInitializationCompleteLoadRva;
    ULONG LdrpValidateEcCallTargetInitRva;
    ULONG SyscallFfsSizeRva;
    ULONG SyscallFfsBaseRva;
} RTL_SCP_CFG_ARM64_HEADER, * PRTL_SCP_CFG_ARM64_HEADER;

// private
typedef enum _RTL_SCP_CFG_PAGE_TYPE
{
    RtlScpCfgPageTypeNop,
    RtlScpCfgPageTypeDefault,
    RtlScpCfgPageTypeExportSuppression,
    RtlScpCfgPageTypeFptr,
    RtlScpCfgPageTypeMax,
    RtlScpCfgPageTypeNone
} RTL_SCP_CFG_PAGE_TYPE;

// private
typedef struct _RTL_SCP_CFG_COMMON_HEADER
{
    ULONG CfgDispatchRva;
    ULONG CfgDispatchESRva;
    ULONG CfgCheckRva;
    ULONG CfgCheckESRva;
    ULONG InvalidCallHandlerRva;
    ULONG FnTableRva;
} RTL_SCP_CFG_COMMON_HEADER, * PRTL_SCP_CFG_COMMON_HEADER;

// private
typedef struct _RTL_SCP_CFG_HEADER
{
    RTL_SCP_CFG_COMMON_HEADER Common;
} RTL_SCP_CFG_HEADER, * PRTL_SCP_CFG_HEADER;

// private
typedef struct _RTL_SCP_CFG_REGION_BOUNDS
{
    PVOID StartAddress;
    PVOID EndAddress;
} RTL_SCP_CFG_REGION_BOUNDS, * PRTL_SCP_CFG_REGION_BOUNDS;

// private
typedef struct _RTL_SCP_CFG_NTDLL_EXPORTS
{
    RTL_SCP_CFG_REGION_BOUNDS ScpRegions[4];
    PVOID CfgDispatchFptr;
    PVOID CfgDispatchESFptr;
    PVOID CfgCheckFptr;
    PVOID CfgCheckESFptr;
    PVOID IllegalCallHandler;
} RTL_SCP_CFG_NTDLL_EXPORTS, * PRTL_SCP_CFG_NTDLL_EXPORTS;

// private
typedef struct _RTL_SCP_CFG_NTDLL_EXPORTS_ARM64EC
{
    PVOID EcInvalidCallHandler;
    PVOID EcCfgCheckFptr;
    PVOID EcCfgCheckESFptr;
    PVOID EcCallCheckFptr;
    PVOID CpuInitializationComplete;
    PVOID LdrpValidateEcCallTargetInit;
    struct
    {
        PVOID SyscallFfsSize;
        union
        {
            PVOID Ptr;
            ULONG Value;
        };
    };
    PVOID SyscallFfsBase;
} RTL_SCP_CFG_NTDLL_EXPORTS_ARM64EC, * PRTL_SCP_CFG_NTDLL_EXPORTS_ARM64EC;

// private
typedef struct _RTL_RETPOLINE_ROUTINES
{
    ULONG SwitchtableJump[16];
    ULONG CfgIndirectRax;
    ULONG NonCfgIndirectRax;
    ULONG ImportR10;
    ULONG JumpHpat;
} RTL_RETPOLINE_ROUTINES, * PRTL_RETPOLINE_ROUTINES;

// private
typedef struct _RTL_KSCP_ROUTINES
{
    ULONG UnwindDataOffset;
    RTL_RETPOLINE_ROUTINES RetpolineRoutines;
    ULONG CfgDispatchSmep;
    ULONG CfgDispatchNoSmep;
} RTL_KSCP_ROUTINES, * PRTL_KSCP_ROUTINES;

// private
typedef enum _MEMORY_IMAGE_EXTENSION_TYPE
{
    MemoryImageExtensionCfgScp,
    MemoryImageExtensionCfgEmulatedScp,
    MemoryImageExtensionTypeMax,
} MEMORY_IMAGE_EXTENSION_TYPE;

// private
typedef struct _MEMORY_IMAGE_EXTENSION_INFORMATION
{
    MEMORY_IMAGE_EXTENSION_TYPE ExtensionType;
    ULONG Flags;
    PVOID ExtensionImageBaseRva;
    SIZE_T ExtensionSize;
} MEMORY_IMAGE_EXTENSION_INFORMATION, * PMEMORY_IMAGE_EXTENSION_INFORMATION;

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

#define MMPFNLIST_ZERO              0
#define MMPFNLIST_FREE              1
#define MMPFNLIST_STANDBY           2
#define MMPFNLIST_MODIFIED          3
#define MMPFNLIST_MODIFIEDNOWRITE   4
#define MMPFNLIST_BAD               5
#define MMPFNLIST_ACTIVE            6
#define MMPFNLIST_TRANSITION        7

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

#define MMPFNUSE_PROCESSPRIVATE     0
#define MMPFNUSE_FILE               1
#define MMPFNUSE_PAGEFILEMAPPED     2
#define MMPFNUSE_PAGETABLE          3
#define MMPFNUSE_PAGEDPOOL          4
#define MMPFNUSE_NONPAGEDPOOL       5
#define MMPFNUSE_SYSTEMPTE          6
#define MMPFNUSE_SESSIONPRIVATE     7
#define MMPFNUSE_METAFILE           8
#define MMPFNUSE_AWEPAGE            9
#define MMPFNUSE_DRIVERLOCKPAGE     10
#define MMPFNUSE_KERNELSTACK        11

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
} MEMORY_FRAME_INFORMATION, * PMEMORY_FRAME_INFORMATION;

// private
typedef struct _FILEOFFSET_INFORMATION
{
    ULONGLONG DontUse : 9; // MEMORY_FRAME_INFORMATION overlay
    ULONGLONG Offset : 48; // mapped files
    ULONGLONG Reserved : 7;
} FILEOFFSET_INFORMATION, * PFILEOFFSET_INFORMATION;

// private
typedef struct _PAGEDIR_INFORMATION
{
    ULONGLONG DontUse : 9; // MEMORY_FRAME_INFORMATION overlay
    ULONGLONG PageDirectoryBase : 48; // private pages
    ULONGLONG Reserved : 7;
} PAGEDIR_INFORMATION, * PPAGEDIR_INFORMATION;

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
    } DUMMYUNIONNAME;
    ULONG_PTR PageFrameIndex; // all
    union
    {
        struct
        {
            ULONG_PTR Image : 1;
            ULONG_PTR Mismatch : 1;
        } DUMMYSTRUCTNAME;
        struct
        {
            ULONG_PTR CombinedPage;
        } DUMMYSTRUCTNAME2;
        ULONG_PTR FileObject; // mapped files
        ULONG_PTR UniqueFileObjectKey;
        ULONG_PTR ProtoPteAddress;
        ULONG_PTR VirtualAddress;  // everything else
    } DUMMYUNIONNAME2;
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
    SectionOriginalBaseInformation, // q; PVOID BaseAddress // since REDSTONE
    SectionInternalImageInformation, // q; SECTION_INTERNAL_IMAGE_INFORMATION // since REDSTONE2
    MaxSectionInfoClass
} SECTION_INFORMATION_CLASS;

/**
 * The SECTION_BASIC_INFORMATION structure contains information of an opened section object.
 *
 * \sa https://learn.microsoft.com/en-us/windows/win32/devnotes/ntquerysection
 */
typedef struct _SECTION_BASIC_INFORMATION
{
    PVOID BaseAddress;              // The base virtual address of the section if the section is based.
    ULONG AllocationAttributes;     // The allocation attributes flags.
    LARGE_INTEGER MaximumSize;      // The maximum size of the section in bytes.
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
            ULONG ImageExportSuppressionInfoPresent : 1;
            ULONG ImageCfgEnabled : 1;
            ULONG Reserved : 22;
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

/**
 * The NtAllocateVirtualMemory routine reserves, commits, or both, a region of pages within the user-mode virtual address space of a specified process.
 *
 * \param ProcessHandle A handle for the process for which the mapping should be done.
 * \param BaseAddress A pointer to a variable that will receive the base address of the allocated region of pages. If the initial value is not zero, the region is allocated at the specified virtual address.
 * \param ZeroBits The number of high-order address bits that must be zero in the base address of the section view. This value must be less than 21 and the initial value of BaseAddress must be zero.
 * \param RegionSize A pointer to a variable that will receive the actual size, in bytes, of the allocated region of pages.
 * \param AllocationType A bitmask containing flags that specify the type of allocation to be performed.
 * \param PageProtection A bitmask containing page protection flags that specify the protection desired for the committed region of pages.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-zwallocatevirtualmemory
 */
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
    _In_ ULONG PageProtection
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
    _In_ ULONG PageProtection
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

/**
 * The NtAllocateVirtualMemoryEx routine reserves, commits, or both, a region of pages within the user-mode virtual address space of a specified process.
 *
 * \param ProcessHandle A handle for the process for which the mapping should be done.
 * \param BaseAddress A pointer to a variable that will receive the base address of the allocated region of pages. If the initial value is not zero, the region is allocated at the specified virtual address.
 * \param RegionSize A pointer to a variable that will receive the actual size, in bytes, of the allocated region of pages.
 * \param AllocationType A bitmask containing flags that specify the type of allocation to be performed.
 * \param PageProtection A bitmask containing page protection flags that specify the protection desired for the committed region of pages.
 * \param ExtendedParameters An optional pointer to one or more extended parameters of type MEM_EXTENDED_PARAMETER.
 * \param ExtendedParameterCount Specifies the number of elements in the ExtendedParameters array.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-zwallocatevirtualmemory
 */
_Must_inspect_result_
_When_(return == 0, __drv_allocatesMem(Region))
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

/**
 * Frees virtual memory allocated for a process.
 *
 * \param ProcessHandle A handle to the process whose virtual memory is to be freed.
 * \param BaseAddress A pointer to the base address of the region of pages to be freed.
 * \param RegionSize A pointer to a variable that specifies the size of the region of memory to be freed.
 * \param FreeType The type of free operation. This parameter can be MEM_DECOMMIT or MEM_RELEASE.
 * \return NTSTATUS Successful or errant status.
 */
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

/**
 * Reads virtual memory from a process.
 *
 * \param ProcessHandle A handle to the process whose memory is to be read.
 * \param BaseAddress A pointer to the base address in the specified process from which to read.
 * \param Buffer A pointer to a buffer that receives the contents from the address space of the specified process.
 * \param NumberOfBytesToRead The number of bytes to be read from the specified process.
 * \param NumberOfBytesRead A pointer to a variable that receives the number of bytes transferred into the specified buffer.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtReadVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _Out_writes_bytes_to_(NumberOfBytesToRead, *NumberOfBytesRead) PVOID Buffer,
    _In_ SIZE_T NumberOfBytesToRead,
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

// rev
/**
 * Reads virtual memory of a 64-bit process from a 32-bit process.
 *
 * \param ProcessHandle A handle to the process whose memory is to be read.
 * \param BaseAddress A pointer to the base address in the specified process from which to read.
 * \param Buffer A pointer to a buffer that receives the contents from the address space of the specified process.
 * \param NumberOfBytesToRead The number of bytes to be read from the specified process.
 * \param NumberOfBytesRead A pointer to a variable that receives the number of bytes transferred into the specified buffer.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtWow64ReadVirtualMemory64(
    _In_ HANDLE ProcessHandle,
    _In_opt_ ULONGLONG BaseAddress,
    _Out_writes_bytes_to_(NumberOfBytesToRead, *NumberOfBytesRead) PVOID Buffer,
    _In_ ULONGLONG NumberOfBytesToRead,
    _Out_opt_ PULONGLONG NumberOfBytesRead
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwWow64ReadVirtualMemory64(
    _In_ HANDLE ProcessHandle,
    _In_opt_ ULONGLONG BaseAddress,
    _Out_writes_bytes_to_(NumberOfBytesToRead, *NumberOfBytesRead) PVOID Buffer,
    _In_ ULONGLONG NumberOfBytesToRead,
    _Out_opt_ PULONGLONG NumberOfBytesRead
);

#if (NTDDI_VERSION >= NTDDI_WIN10_CO)
/**
 * Reads virtual memory from a process with extended options.
 *
 * \param ProcessHandle A handle to the process whose memory is to be read.
 * \param BaseAddress A pointer to the base address in the specified process from which to read.
 * \param Buffer A pointer to a buffer that receives the contents from the address space of the specified process.
 * \param NumberOfBytesToRead The number of bytes to be read from the specified process.
 * \param NumberOfBytesRead A pointer to a variable that receives the number of bytes transferred into the specified buffer.
 * \param Flags Additional flags for the read operation.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtReadVirtualMemoryEx(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _Out_writes_bytes_to_(NumberOfBytesToRead, *NumberOfBytesRead) PVOID Buffer,
    _In_ SIZE_T NumberOfBytesToRead,
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

/**
 * Writes virtual memory to a process.
 *
 * \param ProcessHandle A handle to the process whose memory is to be written.
 * \param BaseAddress A pointer to the base address in the specified process to which to write.
 * \param Buffer A pointer to the buffer that contains the data to be written to the address space of the specified process.
 * \param NumberOfBytesToWrite The number of bytes to be written to the specified process.
 * \param NumberOfBytesWritten A pointer to a variable that receives the number of bytes transferred into the specified buffer.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtWriteVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_opt_ PVOID BaseAddress,
    _In_reads_bytes_(NumberOfBytesToWrite) PVOID Buffer,
    _In_ SIZE_T NumberOfBytesToWrite,
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

// rev
/**
 * Writes virtual memory to a 64-bit process from a 32-bit process.
 *
 * \param ProcessHandle A handle to the process whose memory is to be written.
 * \param BaseAddress A pointer to the base address in the specified process to which to write.
 * \param Buffer A pointer to the buffer that contains the data to be written to the address space of the specified process.
 * \param NumberOfBytesToWrite The number of bytes to be written to the specified process.
 * \param NumberOfBytesWritten A pointer to a variable that receives the number of bytes transferred into the specified buffer.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtWow64WriteVirtualMemory64(
    _In_ HANDLE ProcessHandle,
    _In_opt_ ULONGLONG BaseAddress,
    _In_reads_bytes_(NumberOfBytesToWrite) PVOID Buffer,
    _In_ ULONGLONG NumberOfBytesToWrite,
    _Out_opt_ PULONGLONG NumberOfBytesWritten
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwWow64WriteVirtualMemory64(
    _In_ HANDLE ProcessHandle,
    _In_opt_ ULONGLONG BaseAddress,
    _In_reads_bytes_(NumberOfBytesToWrite) PVOID Buffer,
    _In_ ULONGLONG NumberOfBytesToWrite,
    _Out_opt_ PULONGLONG NumberOfBytesWritten
);

/**
 * Changes the protection on a region of virtual memory.
 *
 * \param ProcessHandle A handle to the process whose memory protection is to be changed.
 * \param BaseAddress A pointer to the base address of the region of pages whose access protection attributes are to be changed.
 * \param RegionSize A pointer to a variable that specifies the size of the region whose access protection attributes are to be changed.
 * \param NewProtection The memory protection option. This parameter can be one of the memory protection constants.
 * \param OldProtection A pointer to a variable that receives the previous access protection of the first page in the specified region of pages.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtProtectVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID* BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG NewProtection,
    _Out_ PULONG OldProtection
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwProtectVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ PVOID* BaseAddress,
    _Inout_ PSIZE_T RegionSize,
    _In_ ULONG NewProtection,
    _Out_ PULONG OldProtection
);

/**
 * Queries information about a region of virtual memory in a process.
 *
 * \param ProcessHandle A handle to the process whose memory information is to be queried.
 * \param BaseAddress A pointer to the base address of the region of pages to be queried.
 * \param MemoryInformationClass The type of information to be queried.
 * \param MemoryInformation A pointer to a buffer that receives the memory information.
 * \param MemoryInformationLength The size of the buffer pointed to by the MemoryInformation parameter.
 * \param ReturnLength A pointer to a variable that receives the number of bytes returned in the MemoryInformation buffer.
 * \return NTSTATUS Successful or errant status.
 */
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

// rev
/**
 * Queries information about a region of virtual memory in a 64-bit process from a 32-bit process.
 *
 * \param ProcessHandle A handle to the process whose memory information is to be queried.
 * \param BaseAddress A pointer to the base address of the region of pages to be queried.
 * \param MemoryInformationClass The type of information to be queried.
 * \param MemoryInformation A pointer to a buffer that receives the memory information.
 * \param MemoryInformationLength The size of the buffer pointed to by the MemoryInformation parameter.
 * \param ReturnLength A pointer to a variable that receives the number of bytes returned in the MemoryInformation buffer.
 * \return NTSTATUS Successful or errant status.
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtWow64QueryVirtualMemory64(
    _In_ HANDLE ProcessHandle,
    _In_opt_ ULONGLONG BaseAddress,
    _In_ MEMORY_INFORMATION_CLASS MemoryInformationClass,
    _Out_writes_bytes_(MemoryInformationLength) PVOID MemoryInformation,
    _In_ ULONGLONG MemoryInformationLength,
    _Out_opt_ PULONGLONG ReturnLength
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwWow64QueryVirtualMemory64(
    _In_ HANDLE ProcessHandle,
    _In_opt_ ULONGLONG BaseAddress,
    _In_ MEMORY_INFORMATION_CLASS MemoryInformationClass,
    _Out_writes_bytes_(MemoryInformationLength) PVOID MemoryInformation,
    _In_ ULONGLONG MemoryInformationLength,
    _Out_opt_ PULONGLONG ReturnLength
);

/**
 * Flushes the instruction cache for a specified process.
 *
 * \param ProcessHandle A handle to the process whose instruction cache is to be flushed.
 * \param BaseAddress A pointer to the base address of the region of memory to be flushed.
 * \param RegionSize A pointer to a variable that specifies the size of the region to be flushed.
 * \param IoStatus A pointer to an IO_STATUS_BLOCK structure that receives the status of the flush operation.
 * \return NTSTATUS Successful or errant status.
 */
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
    VmPrefetchInformation,                  // MEMORY_PREFETCH_INFORMATION
    VmPagePriorityInformation,              // MEMORY_PAGE_PRIORITY_INFORMATION
    VmCfgCallTargetInformation,             // CFG_CALL_TARGET_LIST_INFORMATION // REDSTONE2
    VmPageDirtyStateInformation,            // MEMORY_PAGE_DIRTY_STATE_INFORMATION // REDSTONE3
    VmImageHotPatchInformation,             // 19H1
    VmPhysicalContiguityInformation,        // MEMORY_PHYSICAL_CONTIGUITY_INFORMATION // 20H1 // (requires SeLockMemoryPrivilege)
    VmVirtualMachinePrepopulateInformation,
    VmRemoveFromWorkingSetInformation,      // MEMORY_REMOVE_WORKING_SET_INFORMATION
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

#define VM_PREFETCH_TO_WORKING_SET        0x1  // since 24H4

typedef struct _MEMORY_PREFETCH_INFORMATION
{
    ULONG Flags;
} MEMORY_PREFETCH_INFORMATION, * PMEMORY_PREFETCH_INFORMATION;

//
// Page/memory priorities.
//

#define MEMORY_PRIORITY_LOWEST           0
#define MEMORY_PRIORITY_VERY_LOW         1
#define MEMORY_PRIORITY_LOW              2
#define MEMORY_PRIORITY_MEDIUM           3
#define MEMORY_PRIORITY_BELOW_NORMAL     4
#define MEMORY_PRIORITY_NORMAL           5
#define MEMORY_PRIORITY_ABOVE_NORMAL     6 // rev
#define MEMORY_PRIORITY_HIGH             7 // rev

// VmPagePriorityInformation
typedef struct _MEMORY_PAGE_PRIORITY_INFORMATION
{
    ULONG PagePriority;
} MEMORY_PAGE_PRIORITY_INFORMATION, * PMEMORY_PAGE_PRIORITY_INFORMATION;

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

// VmCfgCallTargetInformation
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

// rev
typedef struct _MEMORY_PAGE_DIRTY_STATE_INFORMATION
{
    ULONG Flags;
} MEMORY_PAGE_DIRTY_STATE_INFORMATION, * PMEMORY_PAGE_DIRTY_STATE_INFORMATION;

// rev
typedef struct _MEMORY_REMOVE_WORKING_SET_INFORMATION
{
    ULONG Flags;
} MEMORY_REMOVE_WORKING_SET_INFORMATION, * PMEMORY_REMOVE_WORKING_SET_INFORMATION;

#ifndef _KERNEL_MODE
typedef struct _MEMORY_RANGE_ENTRY
{
    PVOID VirtualAddress;
    SIZE_T NumberOfBytes;
} MEMORY_RANGE_ENTRY, * PMEMORY_RANGE_ENTRY;
#endif // !_KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_WIN8)
_Must_inspect_result_
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _In_ VIRTUAL_MEMORY_INFORMATION_CLASS VmInformationClass,
    _In_ SIZE_T NumberOfEntries,
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
    _In_ SIZE_T NumberOfEntries,
    _In_reads_(NumberOfEntries) PMEMORY_RANGE_ENTRY VirtualAddresses,
    _In_reads_bytes_(VmInformationLength) PVOID VmInformation,
    _In_ ULONG VmInformationLength
);
#endif

#define MAP_PROCESS 1 // Process WorkingSet
#define MAP_SYSTEM  2 // Physical Memory // (requires SeLockMemoryPrivilege)

/**
 * Locks the specified region of the process's virtual address space into physical memory, ensuring that subsequent access to the region will not incur a page fault.
 *
 * \param ProcessHandle A handle to the process whose virtual address space is to be locked.
 * \param BaseAddress A pointer to the base address of the region of pages to be locked.
 * \param RegionSize The size of the region to be locked, in bytes. The size is rounded up to the nearest multiple of PAGE_SIZE.
 * \param MapType A bitmask containing one or more flags that specify the type of operations to be performed.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtuallock
 */
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

/**
 * Unlocks a specified range of pages in the virtual address space of a process, enabling the system to swap the pages out to the paging file if necessary.
 *
 * \param ProcessHandle A handle to the process whose virtual address space is to be unlocked.
 * \param BaseAddress A pointer to the base address of the region of pages to be unlocked.
 * \param RegionSize The size of the region to be unlocked, in bytes. The size is rounded up to the nearest multiple of PAGE_SIZE.
 * \param MapType A bitmask containing one or more flags that specify the type of operations to be performed.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualunlock
 */
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

/**
 * The NtCreateSection routine creates a section object.
 *
 * \param SectionHandle Pointer to a variable that receives a handle to the section object.
 * \param DesiredAccess The access mask that specifies the requested access to the section object.
 * \param ObjectAttributes Pointer to the base virtual address of the view to unmap. This value can be any virtual address within the view.
 * \param MaximumSize The maximum size, in bytes, of the section. The actual size when backed by the paging file, or the maximum the file can be extended or mapped when backed by an ordinary file.
 * \param SectionPageProtection Specifies the protection to place on each page in the section.
 * \param AllocationAttributes A bitmask of SEC_XXX flags that determines the allocation attributes of the section.
 * \param FileHandle Optionally specifies a handle for an open file object. If the value of FileHandle is NULL, the section is backed by the paging file. Otherwise, the section is backed by the specified file.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-zwcreatesection
 */
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

/**
 * The NtCreateSectionEx routine creates a section object.
 *
 * \param SectionHandle Pointer to a variable that receives a handle to the section object.
 * \param DesiredAccess The access mask that specifies the requested access to the section object.
 * \param ObjectAttributes Pointer to the base virtual address of the view to unmap. This value can be any virtual address within the view.
 * \param MaximumSize The maximum size, in bytes, of the section. The actual size when backed by the paging file, or the maximum the file can be extended or mapped when backed by an ordinary file.
 * \param SectionPageProtection Specifies the protection to place on each page in the section.
 * \param AllocationAttributes A bitmask of SEC_XXX flags that determines the allocation attributes of the section.
 * \param FileHandle Optionally specifies a handle for an open file object. If the value of FileHandle is NULL, the section is backed by the paging file. Otherwise, the section is backed by the specified file.
 * \param ExtendedParameters An optional pointer to one or more extended parameters of type MEM_EXTENDED_PARAMETER.
 * \param ExtendedParameterCount Specifies the number of elements in the ExtendedParameters array.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-zwcreatesection
 */
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

/**
 * The NtOpenSection routine opens a handle for an existing section object.
 *
 * \param SectionHandle Handle to a process object that was previously passed to NtMapViewOfSection.
 * \param DesiredAccess The access mask that specifies the requested access to the section object.
 * \param ObjectAttributes Pointer to an OBJECT_ATTRIBUTES structure that specifies the object name and other attributes.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-zwopensection
 */
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

/**
 * Maps a view of a section into the virtual address space of a subject process.
 *
 * \param SectionHandle A handle to an existing section object.
 * \param ProcessHandle A handle to the object that represents the process that the view should be mapped into. The handle must have been opened with PROCESS_VM_OPERATION access.
 * \param BaseAddress A pointer to a variable that receives the base address of the view. If the value is not NULL, the view is allocated starting at the specified virtual address rounded down to the next 64-kilobyte address boundary.
 * \param ZeroBits The number of high-order address bits that must be zero in the base address of the section view. The value of this parameter must be less than 21 and is used only if BaseAddress is NULL.
 * \param CommitSize Specifies the size, in bytes, of the initially committed region of the view. CommitSize is meaningful only for page-file backed sections and is rounded up to the nearest multiple of PAGE_SIZE.
 * \param SectionOffset A pointer to a variable that receives the offset, in bytes, from the beginning of the section to the view.
 * \param ViewSize A pointer to a variable that specifies the size of the view in bytes. If the initial value is zero, NtMapViewOfSection maps a view of the section that starts at SectionOffset and continues to the end of the section.
 * \param InheritDisposition A value that specifies how the view is to be shared with child processes.
 * \param AllocationType Specifies the type of allocation to be performed for the specified region of pages. The valid flags are MEM_RESERVE, MEM_TOP_DOWN, MEM_LARGE_PAGES, MEM_DIFFERENT_IMAGE_BASE_OK and MEM_REPLACE_PLACEHOLDER. Although MEM_COMMIT is not allowed, it is implied unless MEM_RESERVE is specified.
 * \param PageProtection Specifies the page protection to be applied to the mapped view. Not used with SEC_IMAGE, must be set to PAGE_READONLY for SEC_IMAGE_NO_EXECUTE. For non-image sections, the value must be compatible with the section's page protection from NtCreateSection.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-zwmapviewofsection
 */
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
    _In_ ULONG PageProtection
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
/**
 * Maps a view of a section into the virtual address space of a subject process.
 *
 * \param SectionHandle A handle to an existing section object.
 * \param ProcessHandle A handle to the object that represents the process that the view should be mapped into. The handle must have been opened with PROCESS_VM_OPERATION access.
 * \param BaseAddress A pointer to a variable that receives the base address of the view. If the value is not NULL, the view is allocated starting at the specified virtual address rounded down to the next 64-kilobyte address boundary.
 * \param SectionOffset A pointer to a variable that receives the offset, in bytes, from the beginning of the section to the view.
 * \param ViewSize A pointer to a variable that specifies the size of the view in bytes. If the initial value is zero, NtMapViewOfSection maps a view of the section that starts at SectionOffset and continues to the end of the section.
 * \param AllocationType Specifies the type of allocation to be performed for the specified region of pages. The valid flags are MEM_RESERVE, MEM_TOP_DOWN, MEM_LARGE_PAGES, MEM_DIFFERENT_IMAGE_BASE_OK and MEM_REPLACE_PLACEHOLDER. Although MEM_COMMIT is not allowed, it is implied unless MEM_RESERVE is specified.
 * \param PageProtection Specifies the page protection to be applied to the mapped view. Not used with SEC_IMAGE, must be set to PAGE_READONLY for SEC_IMAGE_NO_EXECUTE. For non-image sections, the value must be compatible with the section's page protection from NtCreateSection.
 * \param ExtendedParameters An optional pointer to one or more extended parameters of type MEM_EXTENDED_PARAMETER.
 * \param ExtendedParameterCount Specifies the number of elements in the ExtendedParameters array.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-zwmapviewofsectionex
 */
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
    _In_ ULONG PageProtection,
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
    _In_ ULONG PageProtection,
    _Inout_updates_opt_(ExtendedParameterCount) PMEM_EXTENDED_PARAMETER ExtendedParameters,
    _In_ ULONG ExtendedParameterCount
);
#endif // NTDDI_VERSION >= NTDDI_WIN10_RS4

/**
 * The NtUnmapViewOfSection routine unmaps a view of a section from the virtual address space of a subject process.
 *
 * \param ProcessHandle Handle to a process object that was previously passed to NtMapViewOfSection.
 * \param BaseAddress Pointer to the base virtual address of the view to unmap. This value can be any virtual address within the view.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-zwunmapviewofsection
 */
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
/**
 * The NtUnmapViewOfSectionEx routine unmaps a view of a section from the virtual address space of a subject process.
 *
 * \param ProcessHandle Handle to a process object that was previously passed to NtMapViewOfSection.
 * \param BaseAddress Pointer to the base virtual address of the view to unmap. This value can be any virtual address within the view.
 * \param Flags Additional flags for the unmap operation.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-zwunmapviewofsection
 */
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

/**
 * Provides the capability to determine the base address, size, granted access, and allocation of an opened section object.
 *
 * \param SectionHandle An open handle to a section object.
 * \param SectionInformationClass The section information class about which to retrieve information.
 * \param SectionInformation A pointer to a buffer that receives the specified information. The format and content of the buffer depend on the specified section class.
 * \param SectionInformationLength Specifies the length in bytes of the section information buffer.
 * \param ReturnLength An optional pointer which, if specified, receives the number of bytes placed in the section information buffer.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/devnotes/ntquerysection
 */
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
// Memory Partitions
//

#ifndef MEMORY_CURRENT_PARTITION_HANDLE
#define MEMORY_CURRENT_PARTITION_HANDLE         ((HANDLE)(LONG_PTR)-1)
#endif // MEMORY_CURRENT_PARTITION_HANDLE

#ifndef MEMORY_SYSTEM_PARTITION_HANDLE
#define MEMORY_SYSTEM_PARTITION_HANDLE          ((HANDLE)(LONG_PTR)-2)
#endif // MEMORY_SYSTEM_PARTITION_HANDLE

#ifndef MEMORY_EXISTING_VAD_PARTITION_HANDLE
#define MEMORY_EXISTING_VAD_PARTITION_HANDLE    ((HANDLE)(LONG_PTR)-3)
#endif // MEMORY_EXISTING_VAD_PARTITION_HANDLE

#ifndef MEMORY_PARTITION_QUERY_ACCESS
#define MEMORY_PARTITION_QUERY_ACCESS  0x0001
#define MEMORY_PARTITION_MODIFY_ACCESS 0x0002
#define MEMORY_PARTITION_ALL_ACCESS \
    (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | MEMORY_PARTITION_QUERY_ACCESS | MEMORY_PARTITION_MODIFY_ACCESS)
#endif

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
    SystemMemoryPartitionMemoryListCommand, // since 24H2
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
#define SystemMemoryPartitionMemoryListCommand          ((_PARTITION_INFORMATION_CLASS)0xE)
#define SystemMemoryPartitionMax                        ((_PARTITION_INFORMATION_CLASS)0xF)
#endif //!_KERNEL_MODE

// private
typedef struct _MEMORY_PARTITION_CONFIGURATION_INFORMATION
{
    ULONG Flags;
    ULONG NumaNode;
    ULONG Channel;
    ULONG NumberOfNumaNodes;
    SIZE_T ResidentAvailablePages;
    SIZE_T CommittedPages;
    SIZE_T CommitLimit;
    SIZE_T PeakCommitment;
    SIZE_T TotalNumberOfPages;
    SIZE_T AvailablePages;
    SIZE_T ZeroPages;
    SIZE_T FreePages;
    SIZE_T StandbyPages;
    SIZE_T StandbyPageCountByPriority[8]; // since REDSTONE2
    SIZE_T RepurposedPagesByPriority[8];
    SIZE_T MaximumCommitLimit;
    SIZE_T Reserved; // DonatedPagesToPartitions
} MEMORY_PARTITION_CONFIGURATION_INFORMATION, * PMEMORY_PARTITION_CONFIGURATION_INFORMATION;

// private
typedef struct _MEMORY_PARTITION_TRANSFER_INFORMATION
{
    SIZE_T NumberOfPages;
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
    SIZE_T TotalNumberOfPages;
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
    SIZE_T NumberOfPagesAdded;
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
    ACCESS_MASK DesiredAccess;
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
    _In_opt_ PCOBJECT_ATTRIBUTES ObjectAttributes,
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
    _In_opt_ PCOBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG PreferredNode
);

__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenPartition(
    _Out_ PHANDLE PartitionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ PCOBJECT_ATTRIBUTES ObjectAttributes
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwOpenPartition(
    _Out_ PHANDLE PartitionHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ PCOBJECT_ATTRIBUTES ObjectAttributes
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

/**
 * Maps previously allocated physical memory pages at a specified address in an Address Windowing Extensions (AWE) region.
 *
 * \param VirtualAddress A pointer to the starting address of the region of memory to remap. The value of VirtualAddress must be within the address range that the VirtualAlloc function returns when the Address Windowing Extensions (AWE) region is allocated.
 * \param NumberOfPages The size of the physical memory and virtual address space for which to establish translations, in pages.
 * \param UserPfnArray A pointer to an array of physical page frame numbers.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-mapuserphysicalpages
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtMapUserPhysicalPages(
    _In_ PVOID VirtualAddress,
    _In_ SIZE_T NumberOfPages,
    _In_reads_opt_(NumberOfPages) PULONG_PTR UserPfnArray
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwMapUserPhysicalPages(
    _In_ PVOID VirtualAddress,
    _In_ SIZE_T NumberOfPages,
    _In_reads_opt_(NumberOfPages) PULONG_PTR UserPfnArray
);

/**
 * Maps previously allocated physical memory pages at a specified address in an Address Windowing Extensions (AWE) region.
 *
 * \param VirtualAddresses A pointer to an array of starting addresses of the regions of memory to remap. The value of VirtualAddress must be within the address range that the VirtualAlloc function returns when the Address Windowing Extensions (AWE) region is allocated.
 * \param NumberOfPages The size of the physical memory and virtual address space for which to establish translations, in pages.
 * \param UserPfnArray A pointer to an array of values that indicates how each corresponding page in VirtualAddresses should be treated. A 0 (zero) indicates the entry should be unmapped, and any nonzero value should be mapped.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-mapuserphysicalpagesscatter
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtMapUserPhysicalPagesScatter(
    _In_reads_(NumberOfPages) PVOID* VirtualAddresses,
    _In_ SIZE_T NumberOfPages,
    _In_reads_opt_(NumberOfPages) PULONG_PTR UserPfnArray
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwMapUserPhysicalPagesScatter(
    _In_reads_(NumberOfPages) PVOID* VirtualAddresses,
    _In_ SIZE_T NumberOfPages,
    _In_reads_opt_(NumberOfPages) PULONG_PTR UserPfnArray
);

/**
 * Allocates physical memory pages to be mapped and unmapped within any Address Windowing Extensions (AWE) region of a specified process.
 *
 * \param ProcessHandle A handle to the process whose physical memory pages are to be allocated within the virtual address space of this process.
 * \param NumberOfPages The size of the physical memory to allocate, in pages.
 * \param UserPfnArray A pointer to an array to store the page frame numbers of the allocated memory. Do not attempt to modify this buffer. It contains operating system data, and corruption could be catastrophic. The information in the buffer is not useful to an application.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-allocateuserphysicalpages
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAllocateUserPhysicalPages(
    _In_ HANDLE ProcessHandle,
    _Inout_ PSIZE_T NumberOfPages,
    _Out_writes_(*NumberOfPages) PULONG_PTR UserPfnArray
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAllocateUserPhysicalPages(
    _In_ HANDLE ProcessHandle,
    _Inout_ PSIZE_T NumberOfPages,
    _Out_writes_(*NumberOfPages) PULONG_PTR UserPfnArray
);

#if (NTDDI_VERSION >= NTDDI_WIN10_VB)
/**
 * Allocates physical memory pages to be mapped and unmapped within any Address Windowing Extensions (AWE) region of a specified process, with extended parameters.
 *
 * \param ProcessHandle A handle to the process whose physical memory pages are to be allocated within the virtual address space of this process.
 * \param NumberOfPages The size of the physical memory to allocate, in pages.
 * \param UserPfnArray A pointer to an array to store the page frame numbers of the allocated memory. Do not attempt to modify this buffer. It contains operating system data, and corruption could be catastrophic. The information in the buffer is not useful to an application.
 * \param ExtendedParameters Pointer to an array of MEM_EXTENDED_PARAMETER structures.
 * \param ExtendedParameterCount The number of MEM_EXTENDED_PARAMETER in the ExtendedParameters array.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-allocateuserphysicalpages
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAllocateUserPhysicalPagesEx(
    _In_ HANDLE ProcessHandle,
    _Inout_ PSIZE_T NumberOfPages,
    _Out_writes_(*NumberOfPages) PULONG_PTR UserPfnArray,
    _Inout_updates_opt_(ExtendedParameterCount) PMEM_EXTENDED_PARAMETER ExtendedParameters,
    _In_ ULONG ExtendedParameterCount
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAllocateUserPhysicalPagesEx(
    _In_ HANDLE ProcessHandle,
    _Inout_ PSIZE_T NumberOfPages,
    _Out_writes_(*NumberOfPages) PULONG_PTR UserPfnArray,
    _Inout_updates_opt_(ExtendedParameterCount) PMEM_EXTENDED_PARAMETER ExtendedParameters,
    _In_ ULONG ExtendedParameterCount
);
#endif // NTDDI_VERSION >= NTDDI_WIN10_VB

/**
 * Frees physical memory pages that are allocated previously by using NtAllocateUserPhysicalPages.
 *
 * \param ProcessHandle A handle to the process. The function frees memory within the virtual address space of this process.
 * \param NumberOfPages The size of the physical memory to free, in pages. On return, if the function fails, this parameter indicates the number of pages that are freed.
 * \param UserPfnArray A pointer to an array of page frame numbers of the allocated memory to be freed.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-freeuserphysicalpages
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtFreeUserPhysicalPages(
    _In_ HANDLE ProcessHandle,
    _Inout_ PSIZE_T NumberOfPages,
    _In_reads_(*NumberOfPages) PULONG_PTR UserPfnArray
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwFreeUserPhysicalPages(
    _In_ HANDLE ProcessHandle,
    _Inout_ PSIZE_T NumberOfPages,
    _In_reads_(*NumberOfPages) PULONG_PTR UserPfnArray
);

// Misc.

/**
 * Retrieves the addresses of the pages that are written to in a region of virtual memory.
 *
 * \param ProcessHandle A handle to the process whose watch information is to be queried.
 * \param Flags Additional flags for the operation. To reset the write-tracking state, set this parameter to WRITE_WATCH_FLAG_RESET. Otherwise, set this parameter to zero.
 * \param BaseAddress The base address of the memory region for which to retrieve write-tracking information. This address must a region that is allocated using MEM_WRITE_WATCH.
 * \param RegionSize The size of the memory region for which to retrieve write-tracking information, in bytes.
 * \param UserAddressArray A pointer to a buffer that receives an array of page addresses that have been written to since the region has been allocated or the write-tracking state has been reset.
 * \param EntriesInUserAddressArray On input, this variable indicates the size of the UserAddressArray array. On output, the variable receives the number of page addresses that are returned in the array.
 * \param Granularity A pointer to a variable that receives the page size, in bytes.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-getwritewatch
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtGetWriteWatch(
    _In_ HANDLE ProcessHandle,
    _In_ ULONG Flags,
    _In_ PVOID BaseAddress,
    _In_ SIZE_T RegionSize,
    _Out_writes_(*EntriesInUserAddressArray) PVOID* UserAddressArray,
    _Inout_ PSIZE_T EntriesInUserAddressArray,
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
    _Inout_ PSIZE_T EntriesInUserAddressArray,
    _Out_ PULONG Granularity
);

/**
 * Resets the write-tracking state for a region of virtual memory.
 *
 * \param ProcessHandle A handle to the process whose watch information is to be reset.
 * \param BaseAddress A pointer to the base address of the memory region for which to reset the write-tracking state.
 * \param RegionSize The size of the memory region for which to reset the write-tracking information, in bytes.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-resetwritewatch
 */
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

/**
 * Flushes the instruction cache for the specified process.
 *
 * \param ProcessHandle A handle to the process whose instruction cache is to be flushed.
 * \param BaseAddress A pointer to the base address of the memory region to be flushed. This parameter can be NULL.
 * \param RegionSize The size of the memory region to be flushed, in bytes.
 * \return NTSTATUS Successful or errant status.
 * \remarks Applications should call NtFlushInstructionCache if they generate or modify code in memory. The CPU cannot detect the change, and may execute the old code it cached.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-flushinstructioncache
 */
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

/**
 * The NtFlushWriteBuffer routine flushes the write queue of the current processor that is running a thread of the current process.
 *
 * \return NTSTATUS Successful or errant status.
 */
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

/**
 * The NtFlushProcessWriteBuffers routine flushes the write queue of each processor that is running a thread of the current process.
 *
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-flushprocesswritebuffers
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtFlushProcessWriteBuffers(
    VOID
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwFlushProcessWriteBuffers(
    VOID
);

//
// Enclave support
//

#if (NTDDI_VERSION >= NTDDI_WIN10_TH2)

/**
 * Creates a new uninitialized enclave. An enclave is an isolated region of code and data within the address space for an application.
 * Only code that runs within the enclave can access data within the same enclave.
 *
 * \param ProcessHandle A handle to the process for which you want to create an enclave.
 * \param BaseAddress The preferred base address of the enclave. Specify NULL to have the operating system assign the base address.
 * \param ZeroBits The number of high-order address bits that must be zero in the base address of the section view. This value must be less than 21 and the initial value of BaseAddress must be zero.
 * \param Size The size of the enclave that you want to create, including the size of the code that you will load into the enclave, in bytes. VBS enclaves must be a multiple of 2 MB in size.
 * SGX enclaves must be a power of 2 in size and must have their base aligned to the same power of 2 as the size, with a minimum alignment of 2 MB. As an example, if the enclave is 128 MB, then its base must be aligned to a 128 MB boundary.
 * \param InitialCommitment The amount of memory to commit for the enclave, in bytes.
 * \param EnclaveType The architecture type of the enclave that you want to create. To verify that an enclave type is supported, call IsEnclaveTypeSupported.
 * \param EnclaveInformation A pointer to the architecture-specific information to use to create the enclave.
 * \param EnclaveInformationLength The length of the structure that the EnclaveInformation parameter points to, in bytes.
 * For the ENCLAVE_TYPE_SGX and ENCLAVE_TYPE_SGX2 enclave types, this value must be 4096. For the ENCLAVE_TYPE_VBS enclave type, this value must be sizeof(ENCLAVE_CREATE_INFO_VBS), which is 36 bytes.
 * \param EnclaveError An optional pointer to a variable that receives an enclave error code that is architecture-specific.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/enclaveapi/nf-enclaveapi-createenclave
 */
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

/**
 * Loads data into an uninitialized enclave that you created by calling NtCreateEnclave.
 *
 * \param ProcessHandle A handle to the process for which the enclave was created.
 * \param BaseAddress The address in the enclave where you want to load the data.
 * \param Buffer A pointer to the data the you want to load into the enclave.
 * \param BufferSize The size of the data that you want to load into the enclave, in bytes. This value must be a whole-number multiple of the page size.
 * \param Protect The memory protection to use for the pages that you want to add to the enclave.
 * \param PageInformation A pointer to information that describes the pages that you want to add to the enclave.
 * \param PageInformationLength The length of the structure that the PageInformation parameter points to, in bytes.
 * \param NumberOfBytesWritten A pointer to a variable that receives the number of bytes that NtLoadEnclaveData copied into the enclave.
 * \param EnclaveError An optional pointer to a variable that receives an enclave error code that is architecture-specific.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/enclaveapi/nf-enclaveapi-loadenclavedata
 */
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

/**
 * Initializes an enclave that you created and loaded with data.
 *
 * \param ProcessHandle A handle to the process for which the enclave was created.
 * \param BaseAddress Any address within the enclave.
 * \param EnclaveInformation A pointer to architecture-specific information to use to initialize the enclave.
 * \param EnclaveInformationLength The length of the structure that the EnclaveInformation parameter points to, in bytes.
 * \param EnclaveError An optional pointer to a variable that receives an enclave error code that is architecture-specific.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/enclaveapi/nf-enclaveapi-initializeenclave
 */
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
/**
 * Ends the execution of the threads that are running within an enclave.
 *
 * \param BaseAddress The base address of the enclave in which to end the execution of the threads.
 * \param Flags Additional flags for the termination operation.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/enclaveapi/nf-enclaveapi-terminateenclave
 */
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
/**
 * Calls a function within an enclave. NtCallEnclave can also be called within an enclave to call a function outside of the enclave.
 *
 * \param Routine The address of the function that you want to call.
 * \param Reserved Reserved for dispatch (RtlEnclaveCallDispatch)
 * \param Flags Additional flags for the call operation.
 * \param RoutineParamReturn The parameter than you want to pass to the function and return value of the function.
 * \return NTSTATUS Successful or errant status.
 * \sa https://learn.microsoft.com/en-us/windows/win32/api/enclaveapi/nf-enclaveapi-callenclave
 */
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCallEnclave(
    _In_ PENCLAVE_ROUTINE Routine,
    _In_ PVOID Reserved,              // SelectVsmEnclaveByNumber > 0 // reserved for dispatch (RtlEnclaveCallDispatch)
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
// Cross Vm
//

// rev
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateCrossVmEvent(
    _Out_ PHANDLE CrossVmEvent,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG CrossVmEventFlags,
    _In_ LPCGUID VMID,
    _In_ LPCGUID ServiceID
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateCrossVmEvent(
    _Out_ PHANDLE CrossVmEvent,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG CrossVmEventFlags,
    _In_ LPCGUID VMID,
    _In_ LPCGUID ServiceID
);

// rev
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateCrossVmMutant(
    _Out_ PHANDLE EventHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG CrossVmEventFlags,
    _In_ LPCGUID VMID,
    _In_ LPCGUID ServiceID
);

// rev
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwCreateCrossVmMutant(
    _Out_ PHANDLE EventHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG CrossVmEventFlags,
    _In_ LPCGUID VMID,
    _In_ LPCGUID ServiceID
);

// rev
__kernel_entry NTSYSCALLAPI
NTSTATUS
NTAPI
NtAcquireCrossVmMutant(
    _In_ HANDLE CrossVmMutant,
    _In_ PLARGE_INTEGER Timeout
);

// rev
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
ZwAcquireCrossVmMutant(
    _In_ HANDLE CrossVmMutant,
    _In_ PLARGE_INTEGER Timeout
);

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
