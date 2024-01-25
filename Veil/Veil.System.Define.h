/*
 * PROJECT:   Veil
 * FILE:      Veil.System.Define.h
 * PURPOSE:   This file is part of Veil.
 *
 * LICENSE:   MIT License
 *
 * DEVELOPER: MiroKaku (kkmi04@outlook.com)
 */

#pragma once
#include <minwindef.h>

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
//  These macros are used to test, set and clear flags respectivly
//

#ifndef FlagOn
#define FlagOn(_F,_SF)        ((_F) & (_SF))
#endif

#ifndef BooleanFlagOn
#define BooleanFlagOn(F,SF)   ((BOOLEAN)(((F) & (SF)) != 0))
#endif

#ifndef SetFlag
#define SetFlag(_F,_SF)       ((_F) |= (_SF))
#endif

#ifndef ClearFlag
#define ClearFlag(_F,_SF)     ((_F) &= ~(_SF))
#endif

//
//  Handy macros for doing pointer arithmetic
//

#ifndef Add2Ptr
#define Add2Ptr(P,I) ((PVOID)((PUCHAR)(P) + (I)))
#endif

#ifndef PtrOffset
#define PtrOffset(B,O) ((ULONG)((ULONG_PTR)(O) - (ULONG_PTR)(B)))
#endif

//
//  This macro takes a length & rounds it up to a multiple of the alignment
//  Alignment is given as a power of 2
//

#ifndef ROUND_TO_SIZE
#define ROUND_TO_SIZE(_length, _alignment)                      \
            ((((ULONG_PTR)(_length)) + ((_alignment)-1)) & ~(ULONG_PTR) ((_alignment) - 1))
#endif

//
//  Checks if 1st argument is aligned on given power of 2 boundary specified
//  by 2nd argument
//

#ifndef IS_ALIGNED
#define IS_ALIGNED(_pointer, _alignment)                        \
        ((((ULONG_PTR) (_pointer)) & ((_alignment) - 1)) == 0)
#endif


//
// Define alignment macros to align structure sizes and pointers up and down.
//

#ifndef ALIGN_DOWN_BY
#define ALIGN_DOWN_BY(length, alignment) \
    ((ULONG_PTR)(length) & ~((ULONG_PTR)(alignment) - 1))
#endif

#ifndef ALIGN_UP_BY
#define ALIGN_UP_BY(length, alignment) \
    (ALIGN_DOWN_BY(((ULONG_PTR)(length) + (alignment) - 1), alignment))
#endif

#ifndef ALIGN_DOWN_POINTER_BY
#define ALIGN_DOWN_POINTER_BY(address, alignment) \
    ((PVOID)((ULONG_PTR)(address) & ~((ULONG_PTR)(alignment) - 1)))
#endif

#ifndef ALIGN_UP_POINTER_BY
#define ALIGN_UP_POINTER_BY(address, alignment) \
    (ALIGN_DOWN_POINTER_BY(((ULONG_PTR)(address) + (alignment) - 1), alignment))
#endif

#ifndef ALIGN_DOWN
#define ALIGN_DOWN(length, type) \
    ALIGN_DOWN_BY(length, sizeof(type))
#endif

#ifndef ALIGN_UP
#define ALIGN_UP(length, type) \
    ALIGN_UP_BY(length, sizeof(type))
#endif

#ifndef ALIGN_DOWN_POINTER
#define ALIGN_DOWN_POINTER(address, type) \
    ALIGN_DOWN_POINTER_BY(address, sizeof(type))
#endif

#ifndef ALIGN_UP_POINTER
#define ALIGN_UP_POINTER(address, type) \
    ALIGN_UP_POINTER_BY(address, sizeof(type))
#endif

//
// Calculate the byte offset of a field in a structure of type type.
//

#ifndef FIELD_OFFSET
#define FIELD_OFFSET(type, field) ((ULONG)&(((type *)0)->field))
#endif

#ifndef FIELD_SIZE
#define FIELD_SIZE(type, field) (sizeof(((type *)0)->field))
#endif


#ifndef STATIC_ASSERT
#define STATIC_ASSERT(expr) typedef char __static_assert_t[ (expr) ]
#endif

typedef void* POINTER_32    PVOID32;
typedef int                 INT_PTR32;
typedef unsigned int        UINT_PTR32;
typedef long                LONG_PTR32;
typedef unsigned long       ULONG_PTR32;

typedef short               HALF_PTR32, * POINTER_32 PHALF_PTR32;
typedef unsigned short      UHALF_PTR32, * POINTER_32 PUHALF_PTR32;
typedef long                SHANDLE_PTR32;
typedef unsigned long       HANDLE_PTR32;

typedef ULONG_PTR32 SIZE_T32, * POINTER_32 PSIZE_T32;
typedef LONG_PTR32 SSIZE_T32, * POINTER_32 PSSIZE_T32;

#ifdef STRICT
typedef void* POINTER_32 HANDLE32;
#if 0 && (_MSC_VER > 1000)
#define DECLARE_HANDLE32(name) struct name##__; typedef struct name##__ * POINTER_32 name
#else
#define DECLARE_HANDLE32(name) struct name##__{int unused;}; typedef struct name##__ * POINTER_32 name
#endif
#else
typedef UINT32 HANDLE32;
#define DECLARE_HANDLE32(name) typedef HANDLE32 name
#endif
typedef HANDLE32* POINTER_32 PHANDLE32;

//
// Legacy thread affinity.
//

typedef ULONG_PTR32 KAFFINITY32;
typedef KAFFINITY32* POINTER_32 PKAFFINITY32;

//
// RC Resource
//

#ifdef _KERNEL_MODE

#define IS_INTRESOURCE(_r)  ((((ULONG_PTR)(_r)) >> 16) == 0)
#define MAKEINTRESOURCEA(i) ((LPSTR)((ULONG_PTR)((WORD)(i))))
#define MAKEINTRESOURCEW(i) ((LPWSTR)((ULONG_PTR)((WORD)(i))))
#ifdef UNICODE
#define MAKEINTRESOURCE  MAKEINTRESOURCEW
#else
#define MAKEINTRESOURCE  MAKEINTRESOURCEA
#endif // !UNICODE

#ifndef NORESOURCE

/*
 * Predefined Resource Types
 */
#define RT_CURSOR           MAKEINTRESOURCE(1)
#define RT_BITMAP           MAKEINTRESOURCE(2)
#define RT_ICON             MAKEINTRESOURCE(3)
#define RT_MENU             MAKEINTRESOURCE(4)
#define RT_DIALOG           MAKEINTRESOURCE(5)
#define RT_STRING           MAKEINTRESOURCE(6)
#define RT_FONTDIR          MAKEINTRESOURCE(7)
#define RT_FONT             MAKEINTRESOURCE(8)
#define RT_ACCELERATOR      MAKEINTRESOURCE(9)
#define RT_RCDATA           MAKEINTRESOURCE(10)
#define RT_MESSAGETABLE     MAKEINTRESOURCE(11)

#define DIFFERENCE     11
#define RT_GROUP_CURSOR MAKEINTRESOURCE((ULONG_PTR)(RT_CURSOR) + DIFFERENCE)
#define RT_GROUP_ICON   MAKEINTRESOURCE((ULONG_PTR)(RT_ICON) + DIFFERENCE)
#define RT_VERSION      MAKEINTRESOURCE(16)
#define RT_DLGINCLUDE   MAKEINTRESOURCE(17)
#if(WINVER >= 0x0400)
#define RT_PLUGPLAY     MAKEINTRESOURCE(19)
#define RT_VXD          MAKEINTRESOURCE(20)
#define RT_ANICURSOR    MAKEINTRESOURCE(21)
#define RT_ANIICON      MAKEINTRESOURCE(22)
#endif /* WINVER >= 0x0400 */
#define RT_HTML         MAKEINTRESOURCE(23)
#ifdef RC_INVOKED
#define RT_MANIFEST                        24
#define CREATEPROCESS_MANIFEST_RESOURCE_ID  1
#define ISOLATIONAWARE_MANIFEST_RESOURCE_ID 2
#define ISOLATIONAWARE_NOSTATICIMPORT_MANIFEST_RESOURCE_ID 3
#define ISOLATIONPOLICY_MANIFEST_RESOURCE_ID 4
#define ISOLATIONPOLICY_BROWSER_MANIFEST_RESOURCE_ID 5
#define MINIMUM_RESERVED_MANIFEST_RESOURCE_ID 1   /* inclusive */
#define MAXIMUM_RESERVED_MANIFEST_RESOURCE_ID 16  /* inclusive */
#else  /* RC_INVOKED */
#define RT_MANIFEST                        MAKEINTRESOURCE(24)
#define CREATEPROCESS_MANIFEST_RESOURCE_ID MAKEINTRESOURCE( 1)
#define ISOLATIONAWARE_MANIFEST_RESOURCE_ID MAKEINTRESOURCE(2)
#define ISOLATIONAWARE_NOSTATICIMPORT_MANIFEST_RESOURCE_ID MAKEINTRESOURCE(3)
#define ISOLATIONPOLICY_MANIFEST_RESOURCE_ID MAKEINTRESOURCE(4)
#define ISOLATIONPOLICY_BROWSER_MANIFEST_RESOURCE_ID MAKEINTRESOURCE(5)
#define MINIMUM_RESERVED_MANIFEST_RESOURCE_ID MAKEINTRESOURCE( 1 /*inclusive*/)
#define MAXIMUM_RESERVED_MANIFEST_RESOURCE_ID MAKEINTRESOURCE(16 /*inclusive*/)
#endif /* RC_INVOKED */

#endif /* !NORESOURCE */

//
// Misc
//

#ifndef INFINITE
#define INFINITE            0xFFFFFFFF  // Infinite timeout
#endif

#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)
#endif

#endif // if _KERNEL_MODE

#if !defined(ASSERT)

#if DBG

NTSYSAPI
__analysis_noreturn
VOID
NTAPI
RtlAssert(
    _In_ PVOID VoidFailedAssertion,
    _In_ PVOID VoidFileName,
    _In_ ULONG LineNumber,
    _In_opt_ PSTR MutableMessage
);

ULONG
__cdecl
DbgPrint(
    _In_z_ _Printf_format_string_ PCSTR Format,
    ...
);

#define ASSERT( exp ) \
    ((!(exp)) ? \
        (RtlAssert( (PVOID)#exp, (PVOID)__FILE__, __LINE__, NULL ),FALSE) : \
        TRUE)

#define ASSERTMSG( msg, exp ) \
    ((!(exp)) ? \
        (RtlAssert( (PVOID)#exp, (PVOID)__FILE__, __LINE__, msg ),FALSE) : \
        TRUE)

#define RTL_SOFT_ASSERT(_exp) \
    ((!(_exp)) ? \
        (DbgPrint("%s(%d): Soft assertion failed\n   Expression: %s\n", __FILE__, __LINE__, #_exp),FALSE) : \
        TRUE)

#define RTL_SOFT_ASSERTMSG(_msg, _exp) \
    ((!(_exp)) ? \
        (DbgPrint("%s(%d): Soft assertion failed\n   Expression: %s\n   Message: %s\n", __FILE__, __LINE__, #_exp, (_msg)),FALSE) : \
        TRUE)

#define RTL_VERIFY         ASSERT
#define RTL_VERIFYMSG      ASSERTMSG

#define RTL_SOFT_VERIFY    RTL_SOFT_ASSERT
#define RTL_SOFT_VERIFYMSG RTL_SOFT_ASSERTMSG

#else
#define ASSERT( exp )         ((void) 0)
#define ASSERTMSG( msg, exp ) ((void) 0)

#define RTL_SOFT_ASSERT(_exp)          ((void) 0)
#define RTL_SOFT_ASSERTMSG(_msg, _exp) ((void) 0)

#define RTL_VERIFY( exp )         ((exp) ? TRUE : FALSE)
#define RTL_VERIFYMSG( msg, exp ) ((exp) ? TRUE : FALSE)

#define RTL_SOFT_VERIFY(_exp)         ((_exp) ? TRUE : FALSE)
#define RTL_SOFT_VERIFYMSG(msg, _exp) ((_exp) ? TRUE : FALSE)

#endif // DBG

#endif // !defined(ASSERT)

//
// ntdef
//

//
// Object Attributes
//

// Valid values for the Attributes field

#define OBJ_PROTECT_CLOSE                   0x00000001L
#define OBJ_INHERIT                         0x00000002L
#define OBJ_AUDIT_OBJECT_CLOSE              0x00000004L
#define OBJ_NO_RIGHTS_UPGRADE               0x00000008L
#define OBJ_PERMANENT                       0x00000010L
#define OBJ_EXCLUSIVE                       0x00000020L
#define OBJ_CASE_INSENSITIVE                0x00000040L
#define OBJ_OPENIF                          0x00000080L
#define OBJ_OPENLINK                        0x00000100L
#define OBJ_KERNEL_HANDLE                   0x00000200L
#define OBJ_FORCE_ACCESS_CHECK              0x00000400L
#define OBJ_IGNORE_IMPERSONATED_DEVICEMAP   0x00000800L
#define OBJ_DONT_REPARSE                    0x00001000L
#define OBJ_VALID_ATTRIBUTES                0x00001FF2L

#ifndef _NTDEF_
#define _NTDEF_

// This header file provides basic NT types not included in Win32. If you have included winnt.h
// (perhaps indirectly), you must use this file instead of ntdef.h.

// Functions

#ifndef _MANAGED
#if defined(_M_IX86)
#define FASTCALL __fastcall
#else
#define FASTCALL
#endif
#else
#define FASTCALL NTAPI
#endif

//
// Cardinal Data Types [0 - 2**N-2)
//

//
// The type QUAD and UQUAD are intended to use when a 8 byte aligned structure
// is required, but it is not a floating point number.
//

typedef double DOUBLE;

typedef struct _QUAD {
    union {
        __int64 UseThisFieldToCopy;
        double  DoNotUseThisField;
    } DUMMYUNIONNAME;

} QUAD;

typedef QUAD* PQUAD;
typedef QUAD UQUAD;
typedef UQUAD* PUQUAD;

#if _WIN32_WINNT >= 0x0600 || (defined(__cplusplus) && defined(WINDOWS_ENABLE_CPLUSPLUS))

//
// Pointer to Const Unsigned Basics
//

typedef CONST UCHAR* PCUCHAR;
typedef CONST USHORT* PCUSHORT;
typedef CONST ULONG* PCULONG;
typedef CONST UQUAD* PCUQUAD;

#endif // _WIN32_WINNT >= 0x0600

//
// Signed characters
//

typedef signed char SCHAR;
typedef SCHAR* PSCHAR;

#if _WIN32_WINNT >= 0x0600 || (defined(__cplusplus) && defined(WINDOWS_ENABLE_CPLUSPLUS))

typedef CONST SCHAR* PCSCHAR;

#endif // _WIN32_WINNT >= 0x0600

#ifndef __LPGUID_DEFINED__
#define __LPGUID_DEFINED__
typedef GUID* LPGUID;
#endif

#ifndef __LPCGUID_DEFINED__
#define __LPCGUID_DEFINED__
typedef const GUID* LPCGUID;
#endif

typedef char    CCHAR;  // winnt
typedef short   CSHORT;
typedef ULONG   CLONG;

typedef CCHAR*  PCCHAR;
typedef CSHORT* PCSHORT;
typedef CLONG*  PCLONG;

//
// Logical Data Type - These are 32-bit logical values.
//
typedef ULONG LOGICAL;
typedef ULONG* PLOGICAL;

//
// NTSTATUS
//

typedef _Return_type_success_(return >= 0) LONG NTSTATUS;
/*lint -save -e624 */  // Don't complain about different typedefs.
typedef NTSTATUS* PNTSTATUS;
/*lint -restore */  // Resume checking for different typedefs.

#if _WIN32_WINNT >= 0x0600
typedef CONST NTSTATUS* PCNTSTATUS;
#endif // _WIN32_WINNT >= 0x0600

//
//  Status values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-------------------------+-------------------------------+
//  |Sev|C|       Facility          |               Code            |
//  +---+-+-------------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//

//
// Generic test for success on any status value (non-negative numbers
// indicate success).
//

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

//
// Generic test for information on any status value.
//

#ifdef _PREFAST_
#define NT_INFORMATION(Status) (((NTSTATUS)(Status)) >= (long)0x40000000)
#else
#define NT_INFORMATION(Status) ((((ULONG)(Status)) >> 30) == 1)
#endif

//
// Generic test for warning on any status value.
//

#ifdef _PREFAST_
#define NT_WARNING(Status) (((NTSTATUS)(Status) < (long)0xc0000000))
#else
#define NT_WARNING(Status) ((((ULONG)(Status)) >> 30) == 2)
#endif

//
// Generic test for error on any status value.
//

#ifdef _PREFAST_
#define NT_ERROR(Status) (((NTSTATUS)(Status)) >= (unsigned long)0xc0000000)
#else
#define NT_ERROR(Status) ((((ULONG)(Status)) >> 30) == 3)
#endif

#ifndef __SECSTATUS_DEFINED__
typedef long SECURITY_STATUS;
#define __SECSTATUS_DEFINED__
#endif

//
// Large (64-bit) integer types and operations
//

#define TIME LARGE_INTEGER
#define _TIME _LARGE_INTEGER
#define PTIME PLARGE_INTEGER
#define LowTime LowPart
#define HighTime HighPart

//
// Physical address.
//

typedef LARGE_INTEGER PHYSICAL_ADDRESS, * PPHYSICAL_ADDRESS;

//
// Kernel
//

#ifndef _KERNEL_MODE
typedef struct _PEB* PPEB;  // ntddk.h
typedef LONG KPRIORITY;     // wdm.h

typedef struct _IO_STATUS_BLOCK
{
    union
    {
        NTSTATUS Status;
        PVOID Pointer;
    };
    ULONG_PTR Information;
} IO_STATUS_BLOCK, * PIO_STATUS_BLOCK;

typedef VOID(NTAPI* PIO_APC_ROUTINE)(
    _In_ PVOID ApcContext,
    _In_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG Reserved
    );
#else
typedef int BOOL;
#endif // !_KERNEL_MODE

//
// Event type
//
typedef enum _EVENT_TYPE
{
    NotificationEvent,
    SynchronizationEvent
} EVENT_TYPE;

//
// Timer type
//

typedef enum _TIMER_TYPE
{
    NotificationTimer,
    SynchronizationTimer
} TIMER_TYPE;

//
// Wait type
//

typedef enum _WAIT_TYPE
{
    WaitAll,
    WaitAny,
    WaitNotification,
    WaitDequeue,
    WaitDpc
} WAIT_TYPE;

//
// Pointer to an Asciiz string
//

typedef _Null_terminated_ CHAR* PSZ;
typedef _Null_terminated_ CONST char* PCSZ;

//
// Counted String
//

typedef USHORT RTL_STRING_LENGTH_TYPE;

typedef struct _STRING {
    USHORT Length;
    USHORT MaximumLength;
#ifdef MIDL_PASS
    [size_is(MaximumLength), length_is(Length)]
#endif // MIDL_PASS
    _Field_size_bytes_part_opt_(MaximumLength, Length) PCHAR Buffer;
} STRING;
typedef STRING* PSTRING;
typedef STRING ANSI_STRING;
typedef PSTRING PANSI_STRING;

typedef STRING OEM_STRING;
typedef PSTRING POEM_STRING;
typedef CONST STRING* PCOEM_STRING;

//
// CONSTCounted String
//

typedef struct _CSTRING {
    USHORT Length;
    USHORT MaximumLength;
    CONST char* Buffer;
} CSTRING;
typedef CSTRING* PCSTRING;
#define ANSI_NULL ((CHAR)0)     // winnt

typedef STRING CANSI_STRING;
typedef PSTRING PCANSI_STRING;

typedef STRING UTF8_STRING;
typedef PSTRING PUTF8_STRING;

//
// Unicode strings are counted 16-bit character strings. If they are
// NULL terminated, Length does not include trailing NULL.
//

typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
#ifdef MIDL_PASS
    [size_is(MaximumLength / 2), length_is((Length) / 2)] USHORT* Buffer;
#else // MIDL_PASS
    _Field_size_bytes_part_opt_(MaximumLength, Length) PWCH   Buffer;
#endif // MIDL_PASS
} UNICODE_STRING;
typedef UNICODE_STRING* PUNICODE_STRING;
typedef const UNICODE_STRING* PCUNICODE_STRING;

#define UNICODE_NULL ((WCHAR)0) // winnt

#if _WIN32_WINNT >= 0x0500

#define DECLARE_CONST_UNICODE_STRING(_var, _string) \
const WCHAR _var ## _buffer[] = _string; \
__pragma(warning(push)) \
__pragma(warning(disable:4221)) __pragma(warning(disable:4204)) \
const UNICODE_STRING _var = { sizeof(_string) - sizeof(WCHAR), sizeof(_string), (PWCH) _var ## _buffer } \
__pragma(warning(pop))

#define DECLARE_GLOBAL_CONST_UNICODE_STRING(_var, _str) \
extern const __declspec(selectany) UNICODE_STRING _var = RTL_CONSTANT_STRING(_str)

#define DECLARE_UNICODE_STRING_SIZE(_var, _size) \
WCHAR _var ## _buffer[_size]; \
__pragma(warning(push)) \
__pragma(warning(disable:4221)) __pragma(warning(disable:4204)) \
UNICODE_STRING _var = { 0, (_size) * sizeof(WCHAR) , _var ## _buffer } \
__pragma(warning(pop))

#endif // _WIN32_WINNT >= 0x0500

//
// Balanced tree node (AVL or RB) structure definition.
//

#pragma warning(push)
#pragma warning(disable:4214)

typedef struct _RTL_BALANCED_NODE {
    union {
        struct _RTL_BALANCED_NODE* Children[2];
        struct {
            struct _RTL_BALANCED_NODE* Left;
            struct _RTL_BALANCED_NODE* Right;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

#define RTL_BALANCED_NODE_RESERVED_PARENT_MASK 3

    union {
        UCHAR Red : 1;
        UCHAR Balance : 2;
        ULONG_PTR ParentValue;
    } DUMMYUNIONNAME2;
} RTL_BALANCED_NODE, * PRTL_BALANCED_NODE;

#pragma warning(pop)

#define RTL_BALANCED_NODE_GET_PARENT_POINTER(Node) \
    ((PRTL_BALANCED_NODE)((Node)->ParentValue & \
                          ~RTL_BALANCED_NODE_RESERVED_PARENT_MASK))

typedef struct _SINGLE_LIST_ENTRY32
{
    ULONG Next;
} SINGLE_LIST_ENTRY32, * POINTER_32 PSINGLE_LIST_ENTRY32;

typedef struct _STRING32 {
    USHORT   Length;
    USHORT   MaximumLength;
    ULONG  Buffer;
} STRING32;
typedef STRING32* PSTRING32;

typedef STRING32 UNICODE_STRING32;
typedef UNICODE_STRING32* PUNICODE_STRING32;

typedef STRING32 ANSI_STRING32;
typedef ANSI_STRING32* PANSI_STRING32;


typedef struct _STRING64 {
    USHORT   Length;
    USHORT   MaximumLength;
    ULONGLONG  Buffer;
} STRING64;
typedef STRING64* PSTRING64;

typedef STRING64 UNICODE_STRING64;
typedef UNICODE_STRING64* PUNICODE_STRING64;

typedef STRING64 ANSI_STRING64;
typedef ANSI_STRING64* PANSI_STRING64;

typedef struct _OBJECT_ATTRIBUTES
{
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor;       // PSECURITY_DESCRIPTOR;
    PVOID SecurityQualityOfService; // PSECURITY_QUALITY_OF_SERVICE
} OBJECT_ATTRIBUTES, * POBJECT_ATTRIBUTES;

typedef const OBJECT_ATTRIBUTES* PCOBJECT_ATTRIBUTES;

#define InitializeObjectAttributes(p, n, a, r, s) { \
    (p)->Length = sizeof(OBJECT_ATTRIBUTES); \
    (p)->RootDirectory = r; \
    (p)->Attributes = a; \
    (p)->ObjectName = n; \
    (p)->SecurityDescriptor = s; \
    (p)->SecurityQualityOfService = NULL; \
    }

// RTL_ to avoid collisions in the global namespace.
// I don't believe there are possible/likely constant RootDirectory
// or SecurityDescriptor values other than NULL, so they are hardcoded.
// As well, the string will generally be const, so we cast that away.
#define RTL_CONSTANT_OBJECT_ATTRIBUTES(n, a) \
    { sizeof(OBJECT_ATTRIBUTES), NULL, RTL_CONST_CAST(PUNICODE_STRING)(n), a, NULL, NULL }

// This synonym is more appropriate for initializing what isn't actually const.
#define RTL_INIT_OBJECT_ATTRIBUTES(n, a) RTL_CONSTANT_OBJECT_ATTRIBUTES(n, a)

#define OBJ_NAME_PATH_SEPARATOR ((WCHAR)L'\\')

// Portability

typedef struct _OBJECT_ATTRIBUTES64
{
    ULONG Length;
    ULONG64 RootDirectory;
    ULONG64 ObjectName;
    ULONG Attributes;
    ULONG64 SecurityDescriptor;
    ULONG64 SecurityQualityOfService;
} OBJECT_ATTRIBUTES64, * POBJECT_ATTRIBUTES64;

typedef const OBJECT_ATTRIBUTES64* PCOBJECT_ATTRIBUTES64;

typedef struct _OBJECT_ATTRIBUTES32
{
    ULONG Length;
    ULONG RootDirectory;
    ULONG ObjectName;
    ULONG Attributes;
    ULONG SecurityDescriptor;
    ULONG SecurityQualityOfService;
} OBJECT_ATTRIBUTES32, * POBJECT_ATTRIBUTES32;

typedef const OBJECT_ATTRIBUTES32* PCOBJECT_ATTRIBUTES32;

//
// This works "generically" for Unicode and Ansi/Oem strings.
// Usage:
//   const static UNICODE_STRING FooU = RTL_CONSTANT_STRING(L"Foo");
//   const static         STRING Foo  = RTL_CONSTANT_STRING( "Foo");
// instead of the slower:
//   UNICODE_STRING FooU;
//           STRING Foo;
//   RtlInitUnicodeString(&FooU, L"Foo");
//          RtlInitString(&Foo ,  "Foo");
//
// Or:
//   const static char szFoo[] = "Foo";
//   const static STRING sFoo = RTL_CONSTANT_STRING(szFoo);
//
// This will compile without error or warning in C++. C will get a warning.
//
#ifdef __cplusplus
extern "C++"
{
    char _RTL_CONSTANT_STRING_type_check(const char* s);
    char _RTL_CONSTANT_STRING_type_check(const WCHAR* s);
    // __typeof would be desirable here instead of sizeof.
    template <size_t N> class _RTL_CONSTANT_STRING_remove_const_template_class;
template <> class _RTL_CONSTANT_STRING_remove_const_template_class<sizeof(char)> { public: typedef  char T; };
template <> class _RTL_CONSTANT_STRING_remove_const_template_class<sizeof(WCHAR)> { public: typedef WCHAR T; };
#define _RTL_CONSTANT_STRING_remove_const_macro(s) \
    (const_cast<_RTL_CONSTANT_STRING_remove_const_template_class<sizeof((s)[0])>::T*>(s))
}
#else
char _RTL_CONSTANT_STRING_type_check(const void* s);
#define _RTL_CONSTANT_STRING_remove_const_macro(s) (s)
#endif
#define RTL_CONSTANT_STRING(s) \
{ \
    sizeof( s ) - sizeof( (s)[0] ), \
    sizeof( s ) / sizeof(_RTL_CONSTANT_STRING_type_check(s)), \
    _RTL_CONSTANT_STRING_remove_const_macro(s) \
}

//
// Interrupt Request Level (IRQL)
//

typedef UCHAR KIRQL;

typedef KIRQL* PKIRQL;

//
// Product types
//

typedef enum _NT_PRODUCT_TYPE
{
    NtProductWinNt = 1,
    NtProductLanManNt,
    NtProductServer
} NT_PRODUCT_TYPE, * PNT_PRODUCT_TYPE;

//
// the bit mask, SharedUserData->SuiteMask, is a ULONG
// so there can be a maximum of 32 entries
// in this enum.
//

typedef enum _SUITE_TYPE
{
    SmallBusiness,
    Enterprise,
    BackOffice,
    CommunicationServer,
    TerminalServer,
    SmallBusinessRestricted,
    EmbeddedNT,
    DataCenter,
    SingleUserTS,
    Personal,
    Blade,
    EmbeddedRestricted,
    SecurityAppliance,
    StorageServer,
    ComputeServer,
    WHServer,
    PhoneNT,
    MultiUserTS,
    MaxSuiteType
} SUITE_TYPE;

#endif // _NTDEF

#if defined(_KERNEL_MODE) && (WDK_NTDDI_VERSION <= NTDDI_WIN10_19H1)
typedef STRING  UTF8_STRING;
typedef PSTRING PUTF8_STRING;
#endif

typedef USHORT RTL_ATOM, * PRTL_ATOM;

typedef struct _RTL_BALANCED_NODE32
{
    union
    {
        struct _RTL_BALANCED_NODE32* POINTER_32 Children[2];
        struct
        {
            struct _RTL_BALANCED_NODE32* POINTER_32 Left;
            struct _RTL_BALANCED_NODE32* POINTER_32 Right;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

    union
    {
        UCHAR Red : 1;
        UCHAR Balance : 2;
        ULONG_PTR32 ParentValue;
    } DUMMYUNIONNAME2;
} RTL_BALANCED_NODE32, * POINTER_32 PRTL_BALANCED_NODE32;

STATIC_ASSERT(sizeof(RTL_BALANCED_NODE32) == 12);

typedef struct _RTL_RB_TREE32
{
    PRTL_BALANCED_NODE32 Root;
    PRTL_BALANCED_NODE32 Min;
} RTL_RB_TREE32, * POINTER_32 PRTL_RB_TREE32;

STATIC_ASSERT(sizeof(RTL_RB_TREE32) == 8);

#if defined(_KERNEL_MODE) && !defined(_WINDOWS_)

//
// Critical Section
//

typedef struct _RTL_CRITICAL_SECTION_DEBUG
{
    UINT16  Type;
    UINT16  CreatorBackTraceIndex;
    struct _RTL_CRITICAL_SECTION* CriticalSection;
    LIST_ENTRY ProcessLocksList;
    UINT32  EntryCount;
    UINT32  ContentionCount;
    UINT32  Flags;
    UINT16  CreatorBackTraceIndexHigh;
    UINT16  SpareWORD;
} RTL_CRITICAL_SECTION_DEBUG, * PRTL_CRITICAL_SECTION_DEBUG, RTL_RESOURCE_DEBUG, * PRTL_RESOURCE_DEBUG;

//
// These flags define the upper byte of the critical section SpinCount field
//
#define RTL_CRITICAL_SECTION_FLAG_NO_DEBUG_INFO         0x01000000
#define RTL_CRITICAL_SECTION_FLAG_DYNAMIC_SPIN          0x02000000
#define RTL_CRITICAL_SECTION_FLAG_STATIC_INIT           0x04000000
#define RTL_CRITICAL_SECTION_FLAG_RESOURCE_TYPE         0x08000000
#define RTL_CRITICAL_SECTION_FLAG_FORCE_DEBUG_INFO      0x10000000
#define RTL_CRITICAL_SECTION_ALL_FLAG_BITS              0xFF000000
#define RTL_CRITICAL_SECTION_FLAG_RESERVED              (RTL_CRITICAL_SECTION_ALL_FLAG_BITS & (~(RTL_CRITICAL_SECTION_FLAG_NO_DEBUG_INFO | RTL_CRITICAL_SECTION_FLAG_DYNAMIC_SPIN | RTL_CRITICAL_SECTION_FLAG_STATIC_INIT | RTL_CRITICAL_SECTION_FLAG_RESOURCE_TYPE | RTL_CRITICAL_SECTION_FLAG_FORCE_DEBUG_INFO)))

//
// These flags define possible values stored in the Flags field of a critsec debuginfo.
//
#define RTL_CRITICAL_SECTION_DEBUG_FLAG_STATIC_INIT     0x00000001

#pragma pack(push, 8)
typedef struct _RTL_CRITICAL_SECTION
{
    PRTL_CRITICAL_SECTION_DEBUG DebugInfo;

    //
    //  The following three fields control entering and exiting the critical
    //  section for the resource
    //

    LONG LockCount;
    LONG RecursionCount;
    HANDLE OwningThread;        // from the thread's ClientId->UniqueThread
    HANDLE LockSemaphore;
    ULONG_PTR SpinCount;        // force size on 64-bit systems when packed
} RTL_CRITICAL_SECTION, * PRTL_CRITICAL_SECTION;
#pragma pack(pop)

//
// Slim R/W lock.
//

typedef struct _RTL_SRWLOCK
{
    PVOID Ptr;
} RTL_SRWLOCK, * PRTL_SRWLOCK;
#define RTL_SRWLOCK_INIT {0}

typedef struct _RTL_CONDITION_VARIABLE
{
    PVOID Ptr;
} RTL_CONDITION_VARIABLE, * PRTL_CONDITION_VARIABLE;
#define RTL_CONDITION_VARIABLE_INIT {0}
#define RTL_CONDITION_VARIABLE_LOCKMODE_SHARED  0x1

//
// Barrier
//

typedef struct _RTL_BARRIER
{
    DWORD Reserved1;
    DWORD Reserved2;
    ULONG_PTR Reserved3[2];
    DWORD Reserved4;
    DWORD Reserved5;
} RTL_BARRIER, * PRTL_BARRIER;

#endif // _KERNEL_MODE

//
// Specific
//

#ifndef _KERNEL_MODE

typedef struct _CLIENT_ID
{
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID, * PCLIENT_ID;

#include <pshpack4.h>
typedef struct _KSYSTEM_TIME
{
    ULONG LowPart;
    LONG High1Time;
    LONG High2Time;
} KSYSTEM_TIME, * PKSYSTEM_TIME;
#include <poppack.h>

#endif // _KERNEL_MODE

//
// This isn't in NT, but it's useful.
//

typedef struct _CLIENT_ID32
{
    ULONG UniqueProcess;
    ULONG UniqueThread;
} CLIENT_ID32, * PCLIENT_ID32;

typedef struct _CLIENT_ID64
{
    ULONGLONG UniqueProcess;
    ULONGLONG UniqueThread;
} CLIENT_ID64, * PCLIENT_ID64;

typedef struct DECLSPEC_ALIGN(MEMORY_ALLOCATION_ALIGNMENT) _QUAD_PTR
{
    ULONG_PTR DoNotUseThisField1;
    ULONG_PTR DoNotUseThisField2;
} QUAD_PTR, * PQUAD_PTR;

typedef struct _LARGE_INTEGER_128
{
    LONGLONG QuadPart[2];
} LARGE_INTEGER_128, * PLARGE_INTEGER_128;


VEIL_END()

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
