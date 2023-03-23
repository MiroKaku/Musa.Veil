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

#pragma push_macro("UNICODE")
#ifndef UNICODE
#define UNICODE 1
#endif

#include <windef.h>

VEIL_BEGIN()

// Types

#ifndef W32KAPI
#define W32KAPI  DECLSPEC_ADDRSAFE
#endif

// Pointers in shared memory need to be 64-bit for user32 on 64-bit kernel
#if defined(_X86_)

#define KPTR_MODIFIER __ptr64

typedef void*    __ptr64        KERNEL_PVOID;
typedef unsigned __int64        KERNEL_UINT_PTR;
typedef __int64                 KERNEL_INT_PTR;
typedef unsigned __int64        KERNEL_ULONG_PTR;
typedef __int64                 KERNEL_LONG_PTR;

#define KHANDLE_NULL            NULL

#ifdef STRICT
    typedef void* KPTR_MODIFIER KHANDLE;
    #define DECLARE_KHANDLE(name) typedef struct name##__ * KPTR_MODIFIER K ## name
#else
    typedef KERNEL_PVOID        KHANDLE;
    #define DECLARE_KHANDLE(name) typedef KHANDLE K ## name
#endif

#else // !_X86_

#define KPTR_MODIFIER

typedef PVOID                   KERNEL_PVOID;
typedef UINT_PTR                KERNEL_UINT_PTR;
typedef INT_PTR                 KERNEL_INT_PTR;
typedef ULONG_PTR               KERNEL_ULONG_PTR;
typedef LONG_PTR                KERNEL_LONG_PTR;

#define KHANDLE_NULL            NULL

#define DECLARE_KHANDLE(name) typedef name K ## name
typedef HANDLE                  KHANDLE;

#endif // _X86_

typedef BYTE*               KPTR_MODIFIER   KPBYTE;
typedef WORD*               KPTR_MODIFIER   KPWORD;
typedef INT*                KPTR_MODIFIER   KPINT;
typedef DWORD*              KPTR_MODIFIER   KPDWORD;
typedef ULONG_PTR*          KPTR_MODIFIER   KPULONG_PTR;
typedef KERNEL_ULONG_PTR*   KPTR_MODIFIER   KPKERNEL_ULONG_PTR;
typedef WCHAR*              KPTR_MODIFIER   KLPWSTR;
typedef WCHAR*              KPTR_MODIFIER   KPWSTR;
typedef CHAR*               KPTR_MODIFIER   KLPSTR;
typedef CHAR*               KPTR_MODIFIER   KPSTR;

#if defined(_X86_)

#define KERNEL_INT_PTR_TO_INT_PTR(i)     ((INT)(i))
#define KERNEL_ULONG_PTR_TO_ULONG_PTR(u) ((ULONG)(u))
#define KPBYTE_TO_PBYTE(p)               ((PBYTE)(KERNEL_ULONG_PTR)(p))
#define KPVOID_TO_PVOID(p)               ((PVOID)(KERNEL_ULONG_PTR)(p))
#define KPWSTR_TO_PWSTR(p)               ((PWSTR)(KERNEL_ULONG_PTR)(p))
#define KHANDLE_TO_HANDLE(h)             ((HANDLE)(KERNEL_ULONG_PTR)(h))

#else // !_X86_

#define KERNEL_INT_PTR_TO_INT_PTR(i)     (i)
#define KERNEL_ULONG_PTR_TO_ULONG_PTR(u) (u)
#define KPBYTE_TO_PBYTE(p)               (p)
#define KPVOID_TO_PVOID(p)               (p)
#define KPWSTR_TO_PWSTR(p)               (p)
#define KHANDLE_TO_HANDLE(h)             (h)

#endif // _X86_

// Strings

//
// Strings are counted 16-bit character strings. If they are
// NULL terminated, Length does not include trailing NULL.
//
typedef struct _LARGE_STRING
{
    ULONG Length;
    ULONG MaximumLength : 31;
    ULONG bAnsi : 1;
    KERNEL_PVOID Buffer;
} LARGE_STRING, * PLARGE_STRING;

typedef struct _LARGE_ANSI_STRING
{
    ULONG Length;
    ULONG MaximumLength : 31;
    ULONG bAnsi : 1;
    KPSTR Buffer;
} LARGE_ANSI_STRING, * PLARGE_ANSI_STRING;

typedef struct _LARGE_UNICODE_STRING
{
    ULONG Length;
    ULONG MaximumLength : 31;
    ULONG bAnsi : 1;
    KPWSTR Buffer;
} LARGE_UNICODE_STRING, * PLARGE_UNICODE_STRING;

// Win32k

#if defined(_KERNEL_MODE)

typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

typedef struct tagWNDCLASSEXA
{
    UINT        cbSize;
    /* Win 3.x */
    UINT        style;
    WNDPROC     lpfnWndProc;
    int         cbClsExtra;
    int         cbWndExtra;
    HINSTANCE   hInstance;
    HICON       hIcon;
    HCURSOR     hCursor;
    HBRUSH      hbrBackground;
    LPCSTR      lpszMenuName;
    LPCSTR      lpszClassName;
    /* Win 4.0 */
    HICON       hIconSm;
} WNDCLASSEXA, * PWNDCLASSEXA, NEAR* NPWNDCLASSEXA, FAR* LPWNDCLASSEXA;
typedef struct tagWNDCLASSEXW
{
    UINT        cbSize;
    /* Win 3.x */
    UINT        style;
    WNDPROC     lpfnWndProc;
    int         cbClsExtra;
    int         cbWndExtra;
    HINSTANCE   hInstance;
    HICON       hIcon;
    HCURSOR     hCursor;
    HBRUSH      hbrBackground;
    LPCWSTR     lpszMenuName;
    LPCWSTR     lpszClassName;
    /* Win 4.0 */
    HICON       hIconSm;
} WNDCLASSEXW, * PWNDCLASSEXW, NEAR* NPWNDCLASSEXW, FAR* LPWNDCLASSEXW;
#ifdef UNICODE
typedef WNDCLASSEXW   WNDCLASSEX;
typedef PWNDCLASSEXW  PWNDCLASSEX;
typedef NPWNDCLASSEXW NPWNDCLASSEX;
typedef LPWNDCLASSEXW LPWNDCLASSEX;
#else
typedef WNDCLASSEXA   WNDCLASSEX;
typedef PWNDCLASSEXA  PWNDCLASSEX;
typedef NPWNDCLASSEXA NPWNDCLASSEX;
typedef LPWNDCLASSEXA LPWNDCLASSEX;
#endif // UNICODE
#endif // _KERNEL_MODE

/*
 * Class Menu names structure. For performance reasons (GetClassInfo) we
 * keep two client side copies of wndcls.lpszMenu and another kernel side
 * copy. This structure is used to pass menu names info between client and
 * kernel.
 */
typedef struct tagCLSMENUNAME
{
    KLPSTR              ClientAnsiMenuName;
    KLPWSTR             ClientUnicodeMenuName;
    PUNICODE_STRING     MenuName;
} CLSMENUNAME, * PCLSMENUNAME;

__kernel_entry W32KAPI
ATOM
NTAPI
NtUserRegisterClassExWOW(
    _In_ WNDCLASSEX* WndClass,
    _In_ PUNICODE_STRING ClassName,
    _In_ PUNICODE_STRING ClassNameVer,
    _In_ PCLSMENUNAME ClassMenuName,
    _In_ WORD  FnId, // FNID_xxxx
    _In_ DWORD Flags,
    _In_opt_ LPDWORD WOWStuff
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserUnregisterClass(
    _In_ PUNICODE_STRING ClassName,
    _In_ HINSTANCE Instance,
    _Out_ PCLSMENUNAME ClassMenuName
);

__kernel_entry W32KAPI
HWND
NTAPI
NtUserCreateWindowEx(
    _In_ DWORD ExStyle,
    _In_ PLARGE_STRING NVClassName,
    _In_ PLARGE_STRING ClassName,
    _In_opt_ PLARGE_STRING WindowName,
    _In_ DWORD Style,
    _In_ INT X,
    _In_ INT Y,
    _In_ INT Width,
    _In_ INT Height,
    _In_ HWND Parent,
    _In_ HMENU Menu,
    _In_ HANDLE Module,
    _In_ LPVOID Param,
    _In_ DWORD Flags,
    _In_ /*PACTIVATION_CONTEXT*/ PVOID ActCtx,
    _In_ PVOID Unknown1,
    _In_ PVOID Unknown2
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserDestroyWindow(
    _In_ HWND Window
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserGetClassInfoEx(
    _In_opt_ HINSTANCE Instance,
    _In_ PUNICODE_STRING ClassName,
    _Inout_ LPWNDCLASSEXW WndClass,
    _Out_ LPWSTR* MenuName,
    _In_ BOOL Ansi
);

__kernel_entry W32KAPI
INT
NTAPI
NtUserGetClassName(
    _In_ HWND Window,
    _In_ BOOL Real,
    _Inout_ PUNICODE_STRING ClassName
);

__kernel_entry W32KAPI
HWND
NTAPI
NtUserFindWindowEx(
    _In_ HWND Parent,
    _In_ HWND Child,
    _In_ PUNICODE_STRING ClassName,
    _In_ PUNICODE_STRING WindowName,
    _In_opt_ DWORD Type
);

__kernel_entry W32KAPI
UINT
NTAPI
NtUserGetAtomName(
    _In_ ATOM Atom,
    _Inout_ PUNICODE_STRING AtomName
);

#if defined(_KERNEL_MODE)
typedef struct tagPAINTSTRUCT {
    HDC         hdc;
    BOOL        fErase;
    RECT        rcPaint;
    BOOL        fRestore;
    BOOL        fIncUpdate;
    BYTE        rgbReserved[32];
} PAINTSTRUCT, * PPAINTSTRUCT, * NPPAINTSTRUCT, * LPPAINTSTRUCT;
#endif

__kernel_entry W32KAPI
HDC
NTAPI
NtUserBeginPaint(
    _In_  HWND Window,
    _Out_ PAINTSTRUCT* Paint
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserEndPaint(
    _In_  HWND Window,
    _In_  const PAINTSTRUCT* Paint
);

VEIL_END()

#pragma pop_macro("UNICODE")

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
