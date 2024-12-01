/*
 * PROJECT:   Veil
 * FILE:      Veil.System.Win32.h
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
typedef const LARGE_STRING* PCLARGE_STRING;

typedef struct _LARGE_ANSI_STRING
{
    ULONG Length;
    ULONG MaximumLength : 31;
    ULONG bAnsi : 1;
    KPSTR Buffer;
} LARGE_ANSI_STRING, * PLARGE_ANSI_STRING;
typedef const LARGE_ANSI_STRING* PCLARGE_ANSI_STRING;

typedef struct _LARGE_UNICODE_STRING
{
    ULONG Length;
    ULONG MaximumLength : 31;
    ULONG bAnsi : 1;
    KPWSTR Buffer;
} LARGE_UNICODE_STRING, * PLARGE_UNICODE_STRING;
typedef const LARGE_UNICODE_STRING* PCLARGE_UNICODE_STRING;

// Win32k

#if defined(_KERNEL_MODE) && !defined(_WINDOWS_)

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
    _In_ PUNICODE_STRING ClassName,     // E.g. "ToolbarWindow32"
    _In_ PUNICODE_STRING ClassNameVer,  // E.g. "6.0.22621.608!ToolbarWindow32"
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

/*
 * Extended Window Styles
 */
#if defined(_KERNEL_MODE)

#define WS_EX_DLGMODALFRAME     0x00000001L
#define WS_EX_NOPARENTNOTIFY    0x00000004L
#define WS_EX_TOPMOST           0x00000008L
#define WS_EX_ACCEPTFILES       0x00000010L
#define WS_EX_TRANSPARENT       0x00000020L

#define WS_EX_MDICHILD          0x00000040L
#define WS_EX_TOOLWINDOW        0x00000080L
#define WS_EX_WINDOWEDGE        0x00000100L
#define WS_EX_CLIENTEDGE        0x00000200L
#define WS_EX_CONTEXTHELP       0x00000400L

#define WS_EX_RIGHT             0x00001000L
#define WS_EX_LEFT              0x00000000L
#define WS_EX_RTLREADING        0x00002000L
#define WS_EX_LTRREADING        0x00000000L
#define WS_EX_LEFTSCROLLBAR     0x00004000L
#define WS_EX_RIGHTSCROLLBAR    0x00000000L

#define WS_EX_CONTROLPARENT     0x00010000L
#define WS_EX_STATICEDGE        0x00020000L
#define WS_EX_APPWINDOW         0x00040000L

#define WS_EX_OVERLAPPEDWINDOW  (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE)
#define WS_EX_PALETTEWINDOW     (WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST)

#define WS_EX_LAYERED           0x00080000
#define WS_EX_NOINHERITLAYOUT   0x00100000L // Disable inheritence of mirroring by children
#define WS_EX_NOREDIRECTIONBITMAP 0x00200000L
#define WS_EX_LAYOUTRTL         0x00400000L // Right to left mirroring

#define WS_EX_COMPOSITED        0x02000000L
#define WS_EX_NOACTIVATE        0x08000000L

#endif // _KERNEL_MODE

#define WS_EX_EXTREDIRECTED     0x01000000L
#define WS_EX_ANSICREATOR       0x80000000L

/*
 * Version macros
 */
#define VERMAX          0x9900  // ignore the version

#define VER51           0x0501
#define VER50           0x0500
#define VER40           0x0400
#define VER31           0x030A
#define VER30           0x0300

#define Is510Compat(ExpWinVer)  (LOWORD(ExpWinVer) >= VER51)
#define Is500Compat(ExpWinVer)  (LOWORD(ExpWinVer) >= VER50)
#define Is400Compat(ExpWinVer)  (LOWORD(ExpWinVer) >= VER40)
#define Is310Compat(ExpWinVer)  (LOWORD(ExpWinVer) >= VER31)
#define Is300Compat(ExpWinVer)  (LOWORD(ExpWinVer) >= VER30)

/*
 * This is used by CreateWindow() flags.
 */
#define CW_FLAGS_ANSI           0x00000001
#define CW_FLAGS_DIFFHMOD       0x80000000
#define CW_FLAGS_VERSIONCLASS   0x40000000

// https://blog.adeltax.com/window-z-order-in-windows-10/
enum ZBID
{
    ZBID_DEFAULT = 0,
    ZBID_DESKTOP = 1,
    ZBID_UIACCESS = 2,
    ZBID_IMMERSIVE_IHM = 3,
    ZBID_IMMERSIVE_NOTIFICATION = 4,
    ZBID_IMMERSIVE_APPCHROME = 5,
    ZBID_IMMERSIVE_MOGO = 6,
    ZBID_IMMERSIVE_EDGY = 7,
    ZBID_IMMERSIVE_INACTIVEMOBODY = 8,
    ZBID_IMMERSIVE_INACTIVEDOCK = 9,
    ZBID_IMMERSIVE_ACTIVEMOBODY = 10,
    ZBID_IMMERSIVE_ACTIVEDOCK = 11,
    ZBID_IMMERSIVE_BACKGROUND = 12,
    ZBID_IMMERSIVE_SEARCH = 13,
    ZBID_GENUINE_WINDOWS = 14,
    ZBID_IMMERSIVE_RESTRICTED = 15,
    ZBID_SYSTEM_TOOLS = 16,

    //Windows 10+
    ZBID_LOCK = 17,
    ZBID_ABOVELOCK_UX = 18,
};

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
    _In_ HMODULE Instance,
    _In_ LPVOID Param,
    _In_ DWORD Band,                // ZBID_xxx
    _In_ DWORD ExpWinVerAndFlags,   // CW_FLAGS_xxx | VERxx
    _In_ DWORD TypeFlags,
    _In_ HANDLE ActCtx              // PACTIVATION_CONTEXT ActivationContext
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
    _In_opt_ HWND Parent,
    _In_opt_ HWND Child,
    _In_opt_ PCUNICODE_STRING ClassName,
    _In_opt_ PCUNICODE_STRING WindowName,
    _In_opt_ DWORD Type
);

__kernel_entry W32KAPI
UINT
NTAPI
NtUserGetAtomName(
    _In_ ATOM Atom,
    _Inout_ PUNICODE_STRING AtomName
);

#if defined(_KERNEL_MODE) && !defined(_WINDOWS_)
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

#if defined(_KERNEL_MODE) && !defined(_WINDOWS_)
typedef struct tagRAWINPUTDEVICELIST
{
    HANDLE hDevice;
    DWORD  dwType;
} RAWINPUTDEVICELIST, * PRAWINPUTDEVICELIST;
#endif

__kernel_entry W32KAPI
UINT NTAPI NtUserGetRawInputDeviceList(
    _Out_writes_opt_(*NumDevices) PRAWINPUTDEVICELIST RawInputDeviceList,
    _Inout_ PUINT NumDevices,
    _In_ UINT Size
);

__kernel_entry W32KAPI
UINT NTAPI NtUserGetRawInputDeviceInfo(
    _In_opt_ HANDLE Handle,
    _In_ UINT Command,
    _Inout_updates_bytes_to_opt_(*Size, *Size) LPVOID Data,
    _Inout_ PUINT Size
);

#if defined(_KERNEL_MODE) && !defined(_WINDOWS_)
typedef struct tagRAWINPUTDEVICE
{
    USHORT usUsagePage; // Toplevel collection UsagePage
    USHORT usUsage;     // Toplevel collection Usage
    DWORD  dwFlags;
    HWND   hwndTarget;  // Target hwnd. NULL = follows keyboard focus
} RAWINPUTDEVICE, * PRAWINPUTDEVICE, * LPRAWINPUTDEVICE;

typedef CONST RAWINPUTDEVICE* PCRAWINPUTDEVICE;
#endif

__kernel_entry W32KAPI
BOOL NTAPI NtUserRegisterRawInputDevices(
    _In_reads_(NumDevices) PCRAWINPUTDEVICE RawInputDevices,
    _In_ UINT NumDevices,
    _In_ UINT Size
);

//
// GDI
//

#define GDI_MAX_HANDLE_COUNT 0xFFFF // 0x4000

#define GDI_HANDLE_INDEX_SHIFT      0
#define GDI_HANDLE_INDEX_BITS       16
#define GDI_HANDLE_INDEX_MASK       0xffff

#define GDI_HANDLE_TYPE_SHIFT       16
#define GDI_HANDLE_TYPE_BITS        5
#define GDI_HANDLE_TYPE_MASK        0x1f

#define GDI_HANDLE_ALTTYPE_SHIFT    21
#define GDI_HANDLE_ALTTYPE_BITS     2
#define GDI_HANDLE_ALTTYPE_MASK     0x3

#define GDI_HANDLE_STOCK_SHIFT      23
#define GDI_HANDLE_STOCK_BITS       1
#define GDI_HANDLE_STOCK_MASK       0x1

#define GDI_HANDLE_UNIQUE_SHIFT     24
#define GDI_HANDLE_UNIQUE_BITS      8
#define GDI_HANDLE_UNIQUE_MASK      0xff

#define GDI_HANDLE_INDEX(Handle) ((ULONG)(Handle) & GDI_HANDLE_INDEX_MASK)
#define GDI_HANDLE_TYPE(Handle) (((ULONG)(Handle) >> GDI_HANDLE_TYPE_SHIFT) & GDI_HANDLE_TYPE_MASK)
#define GDI_HANDLE_ALTTYPE(Handle) (((ULONG)(Handle) >> GDI_HANDLE_ALTTYPE_SHIFT) & GDI_HANDLE_ALTTYPE_MASK)
#define GDI_HANDLE_STOCK(Handle) (((ULONG)(Handle) >> GDI_HANDLE_STOCK_SHIFT)) & GDI_HANDLE_STOCK_MASK)

#define GDI_MAKE_HANDLE(Index, Unique) ((ULONG)(((ULONG)(Unique) << GDI_HANDLE_INDEX_BITS) | (ULONG)(Index)))

// GDI server-side types

#define GDI_DEF_TYPE            0 // invalid handle
#define GDI_DC_TYPE             1
#define GDI_DD_DIRECTDRAW_TYPE  2
#define GDI_DD_SURFACE_TYPE     3
#define GDI_RGN_TYPE            4
#define GDI_SURF_TYPE           5
#define GDI_CLIENTOBJ_TYPE      6
#define GDI_PATH_TYPE           7
#define GDI_PAL_TYPE            8
#define GDI_ICMLCS_TYPE         9
#define GDI_LFONT_TYPE          10
#define GDI_RFONT_TYPE          11
#define GDI_PFE_TYPE            12
#define GDI_PFT_TYPE            13
#define GDI_ICMCXF_TYPE         14
#define GDI_ICMDLL_TYPE         15
#define GDI_BRUSH_TYPE          16
#define GDI_PFF_TYPE            17 // unused
#define GDI_CACHE_TYPE          18 // unused
#define GDI_SPACE_TYPE          19
#define GDI_DBRUSH_TYPE         20 // unused
#define GDI_META_TYPE           21
#define GDI_EFSTATE_TYPE        22
#define GDI_BMFD_TYPE           23 // unused
#define GDI_VTFD_TYPE           24 // unused
#define GDI_TTFD_TYPE           25 // unused
#define GDI_RC_TYPE             26 // unused
#define GDI_TEMP_TYPE           27 // unused
#define GDI_DRVOBJ_TYPE         28
#define GDI_DCIOBJ_TYPE         29 // unused
#define GDI_SPOOL_TYPE          30

// GDI client-side types

#define GDI_CLIENT_TYPE_FROM_HANDLE(Handle) ((ULONG)(Handle) & ((GDI_HANDLE_ALTTYPE_MASK << GDI_HANDLE_ALTTYPE_SHIFT) | \
    (GDI_HANDLE_TYPE_MASK << GDI_HANDLE_TYPE_SHIFT)))
#define GDI_CLIENT_TYPE_FROM_UNIQUE(Unique) GDI_CLIENT_TYPE_FROM_HANDLE((ULONG)(Unique) << 16)

#define GDI_ALTTYPE_1 (1 << GDI_HANDLE_ALTTYPE_SHIFT)
#define GDI_ALTTYPE_2 (2 << GDI_HANDLE_ALTTYPE_SHIFT)
#define GDI_ALTTYPE_3 (3 << GDI_HANDLE_ALTTYPE_SHIFT)

#define GDI_CLIENT_BITMAP_TYPE (GDI_SURF_TYPE << GDI_HANDLE_TYPE_SHIFT)
#define GDI_CLIENT_BRUSH_TYPE (GDI_BRUSH_TYPE << GDI_HANDLE_TYPE_SHIFT)
#define GDI_CLIENT_CLIENTOBJ_TYPE (GDI_CLIENTOBJ_TYPE << GDI_HANDLE_TYPE_SHIFT)
#define GDI_CLIENT_DC_TYPE (GDI_DC_TYPE << GDI_HANDLE_TYPE_SHIFT)
#define GDI_CLIENT_FONT_TYPE (GDI_LFONT_TYPE << GDI_HANDLE_TYPE_SHIFT)
#define GDI_CLIENT_PALETTE_TYPE (GDI_PAL_TYPE << GDI_HANDLE_TYPE_SHIFT)
#define GDI_CLIENT_REGION_TYPE (GDI_RGN_TYPE << GDI_HANDLE_TYPE_SHIFT)

#define GDI_CLIENT_ALTDC_TYPE (GDI_CLIENT_DC_TYPE | GDI_ALTTYPE_1)
#define GDI_CLIENT_DIBSECTION_TYPE (GDI_CLIENT_BITMAP_TYPE | GDI_ALTTYPE_1)
#define GDI_CLIENT_EXTPEN_TYPE (GDI_CLIENT_BRUSH_TYPE | GDI_ALTTYPE_2)
#define GDI_CLIENT_METADC16_TYPE (GDI_CLIENT_CLIENTOBJ_TYPE | GDI_ALTTYPE_3)
#define GDI_CLIENT_METAFILE_TYPE (GDI_CLIENT_CLIENTOBJ_TYPE | GDI_ALTTYPE_2)
#define GDI_CLIENT_METAFILE16_TYPE (GDI_CLIENT_CLIENTOBJ_TYPE | GDI_ALTTYPE_1)
#define GDI_CLIENT_PEN_TYPE (GDI_CLIENT_BRUSH_TYPE | GDI_ALTTYPE_1)

typedef struct _GDI_HANDLE_ENTRY
{
    union
    {
        PVOID Object;
        PVOID NextFree;
    };
    union
    {
        struct
        {
            USHORT ProcessId;
            USHORT Lock : 1;
            USHORT Count : 15;
        };
        ULONG Value;
    } Owner;
    USHORT Unique;
    UCHAR Type;
    UCHAR Flags;
    PVOID UserPointer;
} GDI_HANDLE_ENTRY, * PGDI_HANDLE_ENTRY;

typedef struct _GDI_SHARED_MEMORY
{
    GDI_HANDLE_ENTRY Handles[GDI_MAX_HANDLE_COUNT];
} GDI_SHARED_MEMORY, * PGDI_SHARED_MEMORY;


typedef enum _WINDOWINFOCLASS
{
    WindowProcess = 0, // q: ULONG (Process ID)
    WindowRealProcess = 1, // q: ULONG (Process ID)
    WindowThread = 2, // q: ULONG (Thread ID)
    WindowActiveWindow = 3, // q: HWND
    WindowFocusWindow = 4, // q: HWND
    WindowIsHung = 5, // q: BOOLEAN
    WindowClientBase = 6, // q: PVOID
    WindowIsForegroundThread = 7, // q: BOOLEAN
    WindowDefaultImeWindow = 8, // q: HWND
    WindowDefaultInputContext = 9, // q: HIMC
} WINDOWINFOCLASS, * PWINDOWINFOCLASS;

__kernel_entry W32KAPI
ULONG_PTR
NTAPI
NtUserQueryWindow(
    _In_ HWND WindowHandle,
    _In_ WINDOWINFOCLASS WindowInfo
);

__kernel_entry W32KAPI
NTSTATUS
NTAPI
NtUserTestForInteractiveUser(
    _In_ PLUID AuthenticationId
);

__kernel_entry W32KAPI
NTSTATUS
NTAPI
NtUserCheckAccessForIntegrityLevel(
    _In_ ULONG ProcessIdFirst,
    _In_ ULONG ProcessIdSecond,
    _Out_ PBOOLEAN GrantedAccess
);

__kernel_entry W32KAPI
NTSTATUS
NTAPI
NtUserCheckProcessForClipboardAccess(
    _In_ ULONG ProcessId,
    _Out_ PULONG GrantedAccess
);

__kernel_entry W32KAPI
ULONG
NTAPI
NtUserInternalGetWindowText(
    _In_ HWND WindowHandle,
    _Out_writes_to_(cchMaxCount, return +1) LPWSTR pString,
    _In_ ULONG cchMaxCount
);

__kernel_entry W32KAPI
HICON
NTAPI
NtUserInternalGetWindowIcon(
    _In_ HWND WindowHandle,
    _In_ ULONG IconType
);

typedef enum _CONSOLECONTROL
{
    ConsoleSetVDMCursorBounds = 0, // RECT
    ConsoleNotifyConsoleApplication = 1, // CONSOLE_PROCESS_INFO
    ConsoleFullscreenSwitch = 2,
    ConsoleSetCaretInfo = 3, // CONSOLE_CARET_INFO
    ConsoleSetReserveKeys = 4,
    ConsoleSetForeground = 5, // CONSOLESETFOREGROUND
    ConsoleSetWindowOwner = 6, // CONSOLEWINDOWOWNER
    ConsoleEndTask = 7, // CONSOLEENDTASK
} CONSOLECONTROL;

#define CPI_NEWPROCESSWINDOW 0x0001

typedef struct _CONSOLE_PROCESS_INFO
{
    ULONG ProcessID;
    ULONG Flags;
} CONSOLE_PROCESS_INFO, * PCONSOLE_PROCESS_INFO;

typedef struct _CONSOLE_CARET_INFO
{
    HWND WindowHandle;
    RECT Rect;
} CONSOLE_CARET_INFO, * PCONSOLE_CARET_INFO;

typedef struct _CONSOLESETFOREGROUND
{
    HANDLE ProcessHandle;
    BOOL Foreground;
} CONSOLESETFOREGROUND, * PCONSOLESETFOREGROUND;

typedef struct _CONSOLEWINDOWOWNER
{
    HWND WindowHandle;
    ULONG ProcessId;
    ULONG ThreadId;
} CONSOLEWINDOWOWNER, * PCONSOLEWINDOWOWNER;

typedef struct _CONSOLEENDTASK
{
    HANDLE ProcessId;
    HWND WindowHandle;
    ULONG ConsoleEventCode;
    ULONG ConsoleFlags;
} CONSOLEENDTASK, * PCONSOLEENDTASK;

/**
 * Performs special kernel operations for console host applications. (win32u.dll)
 *
 * This includes reparenting the console window, allowing the console to pass foreground rights
 * on to launched console subsystem applications and terminating attached processes.
 *
 * @param Command One of the CONSOLECONTROL values indicating which console control function should be executed.
 * @param ConsoleInformation A pointer to one of the  structures specifying additional data for the requested console control function.
 * @param ConsoleInformationLength The size of the structure pointed to by the ConsoleInformation parameter.
 * @return Successful or errant status.
 */
__kernel_entry W32KAPI
NTSTATUS
NTAPI
NtUserConsoleControl(
    _In_ CONSOLECONTROL Command,
    _In_reads_bytes_(ConsoleInformationLength) PVOID ConsoleInformation,
    _In_ ULONG ConsoleInformationLength
);

#ifndef _KERNEL_MODE
/**
 * Performs special kernel operations for console host applications. (user32.dll)
 *
 * This includes reparenting the console window, allowing the console to pass foreground rights
 * on to launched console subsystem applications and terminating attached processes.
 *
 * @param Command One of the CONSOLECONTROL values indicating which console control function should be executed.
 * @param ConsoleInformation A pointer to one of the  structures specifying additional data for the requested console control function.
 * @param ConsoleInformationLength The size of the structure pointed to by the ConsoleInformation parameter.
 * @return Successful or errant status.
 */
__kernel_entry W32KAPI
NTSTATUS
NTAPI
ConsoleControl(
    _In_ CONSOLECONTROL Command,
    _In_reads_bytes_(ConsoleInformationLength) PVOID ConsoleInformation,
    _In_ ULONG ConsoleInformationLength
);
#endif


/**
 * Opens the specified window station.
 *
 * @param ObjectAttributes The name of the window station to be opened. Window station names are case-insensitive. This window station must belong to the current session.
 * @param DesiredAccess The access to the window station.
 * @return Successful or errant status.
 */
__kernel_entry W32KAPI
HWINSTA
NTAPI
NtUserOpenWindowStation(
    _In_ OBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ACCESS_MASK DesiredAccess
);

__kernel_entry W32KAPI
HWINSTA
NTAPI
NtUserCreateWindowStation(
    _In_ OBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ACCESS_MASK DesiredAccess,
    _In_opt_ HANDLE KeyboardLayoutHandle,
    _In_opt_ PVOID KeyboardLayoutOffset,
    _In_opt_ PVOID NlsTableOffset,
    _In_opt_ PVOID KeyboardDescriptor,
    _In_opt_ UNICODE_STRING LanguageIdString,
    _In_opt_ ULONG KeyboardLocale
);

__kernel_entry W32KAPI
NTSTATUS
NTAPI
NtUserBuildHwndList(
    _In_opt_ HANDLE DesktopHandle,
    _In_opt_ HWND StartWindowHandle,
    _In_opt_ LOGICAL IncludeChildren,
    _In_opt_ LOGICAL ExcludeImmersive,
    _In_opt_ ULONG ThreadId,
    _In_ ULONG HwndListInformationLength,
    _Out_writes_bytes_(HwndListInformationLength) PVOID HwndListInformation,
    _Out_ PULONG ReturnLength
);

__kernel_entry W32KAPI
NTSTATUS
NTAPI
NtUserBuildNameList(
    _In_ HWINSTA WindowStationHandle, // GetProcessWindowStation
    _In_ ULONG NameListInformationLength,
    _Out_writes_bytes_(NameListInformationLength) PVOID NameListInformation,
    _Out_opt_ PULONG ReturnLength
);

__kernel_entry W32KAPI
NTSTATUS
NTAPI
NtUserBuildPropList(
    _In_ HWINSTA WindowStationHandle,
    _In_ ULONG PropListInformationLength,
    _Out_writes_bytes_(PropListInformationLength) PVOID PropListInformation,
    _Out_opt_ PULONG ReturnLength
);

__kernel_entry W32KAPI
HWND
NTAPI
NtUserGetProcessWindowStation(
    VOID
);

__kernel_entry W32KAPI
LOGICAL
NTAPI
NtUserCloseWindowStation(
    _In_ HWINSTA WindowStationHandle
);

__kernel_entry W32KAPI
LOGICAL
NTAPI
NtUserSetProcessWindowStation(
    _In_ HWINSTA WindowStationHandle
);

NTSYSAPI
LOGICAL
NTAPI
SetWindowStationUser(
    _In_ HWINSTA WindowStationHandle,
    _In_ PLUID UserLogonId,
    _In_ PSID UserSid,
    _In_ ULONG UserSidLength
);

__kernel_entry W32KAPI
LOGICAL
NTAPI
NtUserSetWindowStationUser(
    _In_ HWINSTA WindowStationHandle,
    _In_ PLUID UserLogonId,
    _In_ PSID UserSid,
    _In_ ULONG UserSidLength
);

__kernel_entry W32KAPI
HANDLE
NTAPI
NtUserOpenDesktop(
    _In_ PCOBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG Flags,
    _In_ ACCESS_MASK DesiredAccess
);

__kernel_entry W32KAPI
LOGICAL
NTAPI
NtUserSetThreadDesktop(
    _In_ HDESK DesktopHandle
);

__kernel_entry W32KAPI
LOGICAL
NTAPI
NtUserSwitchDesktop(
    _In_ HDESK DesktopHandle,
    _In_opt_ ULONG Flags,
    _In_opt_ ULONG FadeTime
);

__kernel_entry W32KAPI
LOGICAL
NTAPI
NtUserGetIconInfo(
    _In_ HICON IconOrCursorHandle,
    _Out_ PICONINFO Iconinfo,
    _Inout_opt_ PUNICODE_STRING Name,
    _Inout_opt_ PUNICODE_STRING ResourceId,
    _Out_opt_ PULONG ColorBits,
    _In_ LOGICAL IsCursorHandle
);

__kernel_entry W32KAPI
LOGICAL
NTAPI
NtUserGetIconSize(
    _In_ HGDIOBJ IconOrCursorHandle,
    _In_ LOGICAL IsCursorHandle,
    _Out_ PULONG XX,
    _Out_ PULONG YY
);

__kernel_entry W32KAPI
HWND
NTAPI
NtUserGetForegroundWindow(
    VOID
);

__kernel_entry W32KAPI
HWND
NTAPI
NtUserSetActiveWindow(
    _In_ HWND WindowHandle
);

__kernel_entry W32KAPI
HWND
NTAPI
NtUserSetFocus(
    _In_ HWND WindowHandle
);

__kernel_entry W32KAPI
ULONG_PTR
NTAPI
NtUserGetThreadState(
    _In_ ULONG UserThreadState
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserSetWindowPlacement(
    _In_  HWND WindowHandle,
    _Inout_ const WINDOWPLACEMENT* lpwndpl
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserAttachThreadInput(
    _In_ ULONG IdAttach,
    _In_ ULONG IdAttachTo,
    _In_ BOOL Attach
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserBlockInput(
    _In_ BOOL BlockInput
);

__kernel_entry W32KAPI
BOOL
NTAPI
tUserCalculatePopupWindowPosition(
    _In_ const POINT* anchorPoint,
    _In_ const SIZE* windowSize,
    _In_ ULONG flags,
    _Inout_ RECT* excludeRect,
    _Inout_ RECT* popupWindowPosition
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserChangeWindowMessageFilterEx(
    _In_ HWND WindowHandle,
    _In_ ULONG message,
    _In_ ULONG action,
    _Inout_ PCHANGEFILTERSTRUCT pChangeFilterStruct
);

__kernel_entry W32KAPI
HWND
NTAPI
NtUserChildWindowFromPointEx(
    _In_ HWND WindowHandle,
    _In_ POINT pt,
    _In_ ULONG flags
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserClipCursor(
    _In_ const RECT* lpRect
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserCloseDesktop(
    _In_ HDESK hDesktop
);

__kernel_entry W32KAPI
LONG
NTAPI
NtUserCopyAcceleratorTable(
    _In_ HACCEL hAccelSrc,
    _In_ LPACCEL lpAccelDst,
    _In_ LONG cAccelEntries
);

__kernel_entry W32KAPI
HACCEL
NTAPI
NtUserCreateAcceleratorTable(
    _In_ LPACCEL paccel,
    _In_ LONG cAccel
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserDeleteMenu(
    _In_ HMENU hMenu,
    _In_ ULONG uPosition,
    _In_ ULONG uFlags
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserDestroyMenu(
    _In_ HMENU hMenu
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserDragDetect(
    _In_ HWND WindowHandle,
    _In_ POINT pt
);

__kernel_entry W32KAPI
ULONG
NTAPI
NtUserDragObject(
    _In_ HWND WindowHandleParent,
    _In_ HWND WindowHandleFrom,
    _In_ ULONG fmt,
    _In_ ULONG_PTR data,
    _In_ HCURSOR hcur
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserDrawAnimatedRects(
    _In_ HWND WindowHandle,
    _In_ int idAni,
    _In_ const RECT* lprcFrom,
    _In_ const RECT* lprcTo
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserEndMenu(
    VOID
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserEnumDisplayMonitors(
    _In_ HDC hdc,
    _In_ LPCRECT lprcClip,
    _In_ MONITORENUMPROC lpfnEnum,
    _In_ LPARAM dwData
);

__kernel_entry W32KAPI
HRGN
NTAPI
NtUserExcludeUpdateRgn(
    _In_ HDC hDC,
    _In_ HWND WindowHandle
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserFlashWindowEx(
    _In_ PFLASHWINFO pfwi
);

__kernel_entry W32KAPI
HWND
NTAPI
NtUserGetAncestor(
    _In_ HWND WindowHandle,
    _In_ ULONG gaFlags
);

__kernel_entry W32KAPI
ULONG
NTAPI
NtUserGetCaretBlinkTime(
    VOID
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserGetCaretPos(
    _In_ LPPOINT lpPoint
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserGetClipCursor(
    _In_ LPRECT lpRect
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserGetComboBoxInfo(
    _In_ HWND WindowHandleCombo,
    _Inout_ PCOMBOBOXINFO pcbi
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserGetCurrentInputMessageSource(
    _Inout_ INPUT_MESSAGE_SOURCE* InputMessageSource
);

__kernel_entry W32KAPI
HCURSOR
NTAPI
NtUserGetCursor();

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserGetCursorInfo(
    _In_ PCURSORINFO pci
);

__kernel_entry W32KAPI
HDC
NTAPI
NtUserGetDCEx(
    _In_ HWND WindowHandle,
    _In_ HRGN hrgnClip,
    _In_ ULONG flags
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserGetDisplayAutoRotationPreferences(
    _In_ ORIENTATION_PREFERENCE* pOrientation
);

__kernel_entry W32KAPI
ULONG
NTAPI
NtUserGetDoubleClickTime();

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserGetGUIThreadInfo(
    _In_ ULONG idThread,
    _In_ PGUITHREADINFO pgui
);

#ifndef GR_GDIOBJECTS
#define GR_GDIOBJECTS 0
#endif
#ifndef GR_USEROBJECTS
#define GR_USEROBJECTS 1
#endif
#ifndef GR_GDIOBJECTS_PEAK
#define GR_GDIOBJECTS_PEAK 2
#endif
#ifndef GR_USEROBJECTS_PEAK
#define GR_USEROBJECTS_PEAK 4
#endif

__kernel_entry W32KAPI
ULONG
NTAPI
NtUserGetGuiResources(
    _In_ HANDLE ProcessHandle,
    _In_ ULONG uiFlags
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserGetLayeredWindowAttributes(
    _In_ HWND WindowHandle,
    _In_ COLORREF* pcrKey,
    _In_ BYTE* pbAlpha,
    _In_ ULONG pdwFlags
);

__kernel_entry W32KAPI
ULONG
NTAPI
NtUserGetListBoxInfo(
    _In_ HWND WindowHandle
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserGetMenuBarInfo(
    _In_ HWND WindowHandle,
    _In_ LONG idObject,
    _In_ LONG idItem,
    _In_ PMENUBARINFO pmbi
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserGetMenuItemRect(
    _In_ HWND WindowHandle,
    _In_ HMENU hMenu,
    _In_ ULONG uItem,
    _In_ LPRECT lprcItem
);

__kernel_entry W32KAPI
LONG
NTAPI
NtUserGetMouseMovePointsEx(
    _In_ ULONG cbSize,
    _In_ LPMOUSEMOVEPOINT lppt,
    _In_ LPMOUSEMOVEPOINT lpptBuf,
    _In_ LONG nBufPoints,
    _In_ ULONG resolution
);

__kernel_entry W32KAPI
ULONG
NTAPI
NtUserGetRawInputData(
    _In_ HRAWINPUT hRawInput,
    _In_ ULONG uiCommand,
    _In_ LPVOID pData,
    _In_ PULONG pcbSize,
    _In_ ULONG cbSizeHeader
);

__kernel_entry W32KAPI
ULONG
NTAPI
NtUserGetRegisteredRawInputDevices(
    _In_ PRAWINPUTDEVICE pRawInputDevices,
    _In_ PULONG puiNumDevices,
    _In_ ULONG cbSize
);

__kernel_entry W32KAPI
HMENU
NTAPI
NtUserGetSystemMenu(
    _In_ HWND WindowHandle,
    _In_ BOOL bRevert
);

__kernel_entry W32KAPI
HDESK
NTAPI
NtUserGetThreadDesktop(
    _In_ ULONG ThreadId
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserGetTitleBarInfo(
    _In_ HWND WindowHandle,
    _In_ PTITLEBARINFO pti
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserGetObjectInformation(
    _In_ HANDLE hObj,
    _In_ LONG Index,
    _In_ PVOID vInfo,
    _In_ ULONG Length,
    _In_ PULONG LengthNeeded
);

__kernel_entry W32KAPI
HDC
NTAPI
NtUserGetWindowDC(
    _In_ HWND WindowHandle
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserGetWindowPlacement(
    _In_ HWND WindowHandle,
    _In_opt_ WINDOWPLACEMENT* lpwndpl
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserHiliteMenuItem(
    _In_ HWND WindowHandle,
    _In_ HMENU Menu,
    _In_ ULONG IDHiliteItem,
    _In_ ULONG Hilite
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserInvalidateRect(
    _In_ HWND WindowHandle,
    _In_ const RECT* Rect,
    _In_ BOOL Erase
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserInvalidateRgn(
    _In_ HWND WindowHandle,
    _In_ HRGN hRgn,
    _In_ BOOL Erase
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserIsTouchWindow(
    _In_ HWND WindowHandle,
    _In_ PULONG Flags
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserKillTimer(
    _In_ HWND WindowHandle,
    _In_ ULONG_PTR IDEvent
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserLockWorkStation(
    VOID
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserLogicalToPhysicalPoint(
    _In_ HWND WindowHandle,
    _In_ LPPOINT lpPoint
);

__kernel_entry W32KAPI
LONG
NTAPI
NtUserMenuItemFromPoint(
    _In_ HWND WindowHandle,
    _In_ HMENU hMenu,
    _In_ POINT ptScreen
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserMoveWindow(
    _In_ HWND WindowHandle,
    _In_ LONG X,
    _In_ LONG Y,
    _In_ LONG nWidth,
    _In_ LONG nHeight,
    _In_ BOOL bRepaint
);

__kernel_entry W32KAPI
HDESK
NTAPI
NtUserOpenInputDesktop(
    _In_ ULONG Flags,
    _In_ BOOL Inherit,
    _In_ ACCESS_MASK DesiredAccess
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserPhysicalToLogicalPoint(
    _In_ HWND WindowHandle,
    _In_ LPPOINT lpPoint
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserPrintWindow(
    _In_ HWND WindowHandle,
    _In_ HDC hdcBlt,
    _In_ ULONG nFlags
);

typedef enum _USERTHREADINFOCLASS USERTHREADINFOCLASS;

__kernel_entry W32KAPI
NTSTATUS
NTAPI
NtUserQueryInformationThread(
    _In_ HANDLE ThreadHandle,
    _In_ USERTHREADINFOCLASS ThreadInformationClass,
    _Out_writes_bytes_(ThreadInformationLength) PVOID ThreadInformation,
    _In_ ULONG ThreadInformationLength,
    _Out_opt_ PULONG ReturnLength
);

__kernel_entry W32KAPI
NTSTATUS
NTAPI
NtUserSetInformationThread(
    _In_ HANDLE ThreadHandle,
    _In_ USERTHREADINFOCLASS ThreadInformationClass,
    _In_reads_bytes_(ThreadInformationLength) PVOID ThreadInformation,
    _In_ ULONG ThreadInformationLength
);

__kernel_entry W32KAPI
BOOL
NTAPI
QuerySendMessage(
    _Inout_ MSG* pMsg
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserRedrawWindow(
    _In_ HWND WindowHandle,
    _In_ const PRECT lprcUpdate,
    _In_ HRGN hrgnUpdate,
    _In_ ULONG flags
);

__kernel_entry W32KAPI
HWND
NTAPI
NtUserRealChildWindowFromPoint(
    _In_ HWND WindowHandleParent,
    _In_ POINT ptParentClientCoords
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserRegisterHotKey(
    _In_ HWND WindowHandle,
    _In_ LONG id,
    _In_ ULONG fsModifiers,
    _In_ ULONG vk
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserRemoveMenu(
    _In_ HMENU hMenu,
    _In_ ULONG uPosition,
    _In_ ULONG uFlags
);

__kernel_entry W32KAPI
ULONG
NTAPI
NtUserSendInput(
    _In_ ULONG cInputs,
    _In_ LPINPUT pInputs,
    _In_ LONG cbSize
);

__kernel_entry W32KAPI
HWND
NTAPI
NtUserSetActiveWindow(
    _In_ HWND WindowHandle
);

__kernel_entry W32KAPI
HWND
NTAPI
NtUserSetCapture(
    _In_ HWND WindowHandle
);

__kernel_entry W32KAPI
ULONG_PTR
NTAPI
NtUserSetTimer(
    _In_ HWND WindowHandle,
    _In_ ULONG_PTR nIDEvent,
    _In_ ULONG uElapse,
    _In_ TIMERPROC lpTimerFunc,
    _In_ ULONG uToleranceDelay
);

__kernel_entry W32KAPI
WORD
NTAPI
NtUserSetClassWord(
    _In_ HWND WindowHandle,
    _In_ LONG nIndex,
    _In_ WORD wNewWord
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserSetCursorPos(
    _In_ LONG X,
    _In_ LONG Y
);

__kernel_entry W32KAPI
HWND
NTAPI
NtUserSetFocus(
    _In_ HWND WindowHandle
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserSetLayeredWindowAttributes(
    _In_ HWND WindowHandle,
    _In_ COLORREF crKey,
    _In_ BYTE bAlpha,
    _In_ DWORD dwFlags
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserSetProcessRestrictionExemption(
    _In_ BOOL EnableExemption
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserSetWindowPos(
    _In_ HWND WindowHandle,
    _In_ HWND WindowHandleInsertAfter,
    _In_ LONG X,
    _In_ LONG Y,
    _In_ LONG cx,
    _In_ LONG cy,
    _In_ ULONG uFlags
);

__kernel_entry W32KAPI
WORD
NTAPI
NtUserSetWindowWord(
    _In_ HWND WindowHandle,
    _In_ LONG nIndex,
    _In_ WORD wNewWord
);

__kernel_entry W32KAPI
HWND
NTAPI
NtUserShellForegroundBoostProcess(
    _In_ HANDLE ProcessHandle,
    _In_ HWND WindowHandle
);

__kernel_entry W32KAPI
ULONG
NTAPI
NtUserSetAdditionalForegroundBoostProcesses(
    _In_ HWND WindowHandle
);

__kernel_entry W32KAPI
ULONG
NTAPI
NtUserSetAdditionalPowerThrottlingProcess(
    _In_ HWND WindowHandle
);

__kernel_entry W32KAPI
LONG
NTAPI
NtUserShowCursor(
    _In_ BOOL bShow
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserShowWindow(
    _In_ HWND WindowHandle,
    _In_ LONG nCmdShow
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserShowWindowAsync(
    _In_ HWND WindowHandle,
    _In_ LONG nCmdShow
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserShutdownBlockReasonQuery(
    _In_ HWND WindowHandle,
    _Out_ LPWSTR pwszBuff,
    _Inout_ PULONG pcchBuff
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserShutdownReasonDestroy(
    _In_ HWND WindowHandle
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserTrackMouseEvent(
    _In_ LPTRACKMOUSEEVENT lpEventTrack
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserTrackPopupMenuEx(
    _In_ HMENU hMenu,
    _In_ ULONG uFlags,
    _In_ LONG x,
    _In_ LONG y,
    _In_ HWND WindowHandle,
    _In_ LPTPMPARAMS lptpm
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserUnhookWinEvent(
    _In_ HWINEVENTHOOK hWinEventHook
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserUnregisterHotKey(
    _In_ HWND WindowHandle,
    _In_ LONG id
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserUserHandleGrantAccess(
    _In_ HANDLE UserHandle,
    _In_ HANDLE Job,
    _In_ BOOL Grant
);

__kernel_entry W32KAPI
BOOL
NTAPI
NtUserValidateRect(
    _In_ HWND WindowHandle,
    _In_ const RECT* Rect
);

__kernel_entry W32KAPI
HWND
NTAPI
NtUserWindowFromDC(
    _In_ HDC hDC
);

__kernel_entry W32KAPI
HWND
NTAPI
NtUserWindowFromPhysicalPoint(
    _In_ POINT Point
);

__kernel_entry W32KAPI
HWND
NTAPI
NtUserWindowFromPoint(
    _In_ POINT Point
);

// Peb!KernelCallbackTable = user32.dll!apfnDispatch
typedef struct _KERNEL_CALLBACK_TABLE
{
    ULONG_PTR __fnCOPYDATA;
    ULONG_PTR __fnCOPYGLOBALDATA;
    ULONG_PTR __fnEMPTY1;
    ULONG_PTR __fnNCDESTROY;
    ULONG_PTR __fnDWORDOPTINLPMSG;
    ULONG_PTR __fnINOUTDRAG;
    ULONG_PTR __fnGETTEXTLENGTHS1;
    ULONG_PTR __fnINCNTOUTSTRING;
    ULONG_PTR __fnINCNTOUTSTRINGNULL;
    ULONG_PTR __fnINLPCOMPAREITEMSTRUCT;
    ULONG_PTR __fnINLPCREATESTRUCT;
    ULONG_PTR __fnINLPDELETEITEMSTRUCT;
    ULONG_PTR __fnINLPDRAWITEMSTRUCT;
    ULONG_PTR __fnPOPTINLPUINT1;
    ULONG_PTR __fnPOPTINLPUINT2;
    ULONG_PTR __fnINLPMDICREATESTRUCT;
    ULONG_PTR __fnINOUTLPMEASUREITEMSTRUCT;
    ULONG_PTR __fnINLPWINDOWPOS;
    ULONG_PTR __fnINOUTLPPOINT51;
    ULONG_PTR __fnINOUTLPSCROLLINFO;
    ULONG_PTR __fnINOUTLPRECT;
    ULONG_PTR __fnINOUTNCCALCSIZE;
    ULONG_PTR __fnINOUTLPPOINT52;
    ULONG_PTR __fnINPAINTCLIPBRD;
    ULONG_PTR __fnINSIZECLIPBRD;
    ULONG_PTR __fnINDESTROYCLIPBRD;
    ULONG_PTR __fnINSTRINGNULL1;
    ULONG_PTR __fnINSTRINGNULL2;
    ULONG_PTR __fnINDEVICECHANGE;
    ULONG_PTR __fnPOWERBROADCAST;
    ULONG_PTR __fnINLPUAHDRAWMENU1;
    ULONG_PTR __fnOPTOUTLPDWORDOPTOUTLPDWORD1;
    ULONG_PTR __fnOPTOUTLPDWORDOPTOUTLPDWORD2;
    ULONG_PTR __fnOUTDWORDINDWORD;
    ULONG_PTR __fnOUTLPRECT;
    ULONG_PTR __fnOUTSTRING;
    ULONG_PTR __fnPOPTINLPUINT3;
    ULONG_PTR __fnPOUTLPINT;
    ULONG_PTR __fnSENTDDEMSG;
    ULONG_PTR __fnINOUTSTYLECHANGE1;
    ULONG_PTR __fnHkINDWORD;
    ULONG_PTR __fnHkINLPCBTACTIVATESTRUCT;
    ULONG_PTR __fnHkINLPCBTCREATESTRUCT;
    ULONG_PTR __fnHkINLPDEBUGHOOKSTRUCT;
    ULONG_PTR __fnHkINLPMOUSEHOOKSTRUCTEX1;
    ULONG_PTR __fnHkINLPKBDLLHOOKSTRUCT;
    ULONG_PTR __fnHkINLPMSLLHOOKSTRUCT;
    ULONG_PTR __fnHkINLPMSG;
    ULONG_PTR __fnHkINLPRECT;
    ULONG_PTR __fnHkOPTINLPEVENTMSG;
    ULONG_PTR __xxxClientCallDelegateThread;
    ULONG_PTR __ClientCallDummyCallback1;
    ULONG_PTR __ClientCallDummyCallback2;
    ULONG_PTR __fnSHELLWINDOWMANAGEMENTCALLOUT;
    ULONG_PTR __fnSHELLWINDOWMANAGEMENTNOTIFY;
    ULONG_PTR __ClientCallDummyCallback3;
    ULONG_PTR __xxxClientCallDitThread;
    ULONG_PTR __xxxClientEnableMMCSS;
    ULONG_PTR __xxxClientUpdateDpi;
    ULONG_PTR __xxxClientExpandStringW;
    ULONG_PTR __ClientCopyDDEIn1;
    ULONG_PTR __ClientCopyDDEIn2;
    ULONG_PTR __ClientCopyDDEOut1;
    ULONG_PTR __ClientCopyDDEOut2;
    ULONG_PTR __ClientCopyImage;
    ULONG_PTR __ClientEventCallback;
    ULONG_PTR __ClientFindMnemChar;
    ULONG_PTR __ClientFreeDDEHandle;
    ULONG_PTR __ClientFreeLibrary;
    ULONG_PTR __ClientGetCharsetInfo;
    ULONG_PTR __ClientGetDDEFlags;
    ULONG_PTR __ClientGetDDEHookData;
    ULONG_PTR __ClientGetListboxString;
    ULONG_PTR __ClientGetMessageMPH;
    ULONG_PTR __ClientLoadImage;
    ULONG_PTR __ClientLoadLibrary;
    ULONG_PTR __ClientLoadMenu;
    ULONG_PTR __ClientLoadLocalT1Fonts;
    ULONG_PTR __ClientPSMTextOut;
    ULONG_PTR __ClientLpkDrawTextEx;
    ULONG_PTR __ClientExtTextOutW;
    ULONG_PTR __ClientGetTextExtentPointW;
    ULONG_PTR __ClientCharToWchar;
    ULONG_PTR __ClientAddFontResourceW;
    ULONG_PTR __ClientThreadSetup;
    ULONG_PTR __ClientDeliverUserApc;
    ULONG_PTR __ClientNoMemoryPopup;
    ULONG_PTR __ClientMonitorEnumProc;
    ULONG_PTR __ClientCallWinEventProc;
    ULONG_PTR __ClientWaitMessageExMPH;
    ULONG_PTR __ClientCallDummyCallback4;
    ULONG_PTR __ClientCallDummyCallback5;
    ULONG_PTR __ClientImmLoadLayout;
    ULONG_PTR __ClientImmProcessKey;
    ULONG_PTR __fnIMECONTROL;
    ULONG_PTR __fnINWPARAMDBCSCHAR;
    ULONG_PTR __fnGETTEXTLENGTHS2;
    ULONG_PTR __ClientCallDummyCallback6;
    ULONG_PTR __ClientLoadStringW;
    ULONG_PTR __ClientLoadOLE;
    ULONG_PTR __ClientRegisterDragDrop;
    ULONG_PTR __ClientRevokeDragDrop;
    ULONG_PTR __fnINOUTMENUGETOBJECT;
    ULONG_PTR __ClientPrinterThunk;
    ULONG_PTR __fnOUTLPCOMBOBOXINFO;
    ULONG_PTR __fnOUTLPSCROLLBARINFO;
    ULONG_PTR __fnINLPUAHDRAWMENU2;
    ULONG_PTR __fnINLPUAHDRAWMENUITEM;
    ULONG_PTR __fnINLPUAHDRAWMENU3;
    ULONG_PTR __fnINOUTLPUAHMEASUREMENUITEM;
    ULONG_PTR __fnINLPUAHDRAWMENU4;
    ULONG_PTR __fnOUTLPTITLEBARINFOEX;
    ULONG_PTR __fnTOUCH;
    ULONG_PTR __fnGESTURE;
    ULONG_PTR __fnPOPTINLPUINT4;
    ULONG_PTR __fnPOPTINLPUINT5;
    ULONG_PTR __xxxClientCallDefaultInputHandler;
    ULONG_PTR __fnEMPTY2;
    ULONG_PTR __ClientRimDevCallback;
    ULONG_PTR __xxxClientCallMinTouchHitTestingCallback;
    ULONG_PTR __ClientCallLocalMouseHooks;
    ULONG_PTR __xxxClientBroadcastThemeChange;
    ULONG_PTR __xxxClientCallDevCallbackSimple;
    ULONG_PTR __xxxClientAllocWindowClassExtraBytes;
    ULONG_PTR __xxxClientFreeWindowClassExtraBytes;
    ULONG_PTR __fnGETWINDOWDATA;
    ULONG_PTR __fnINOUTSTYLECHANGE2;
    ULONG_PTR __fnHkINLPMOUSEHOOKSTRUCTEX2;
    ULONG_PTR __xxxClientCallDefWindowProc;
    ULONG_PTR __fnSHELLSYNCDISPLAYCHANGED;
    ULONG_PTR __fnHkINLPCHARHOOKSTRUCT;
    ULONG_PTR __fnINTERCEPTEDWINDOWACTION;
    ULONG_PTR __xxxTooltipCallback;
    ULONG_PTR __xxxClientInitPSBInfo;
    ULONG_PTR __xxxClientDoScrollMenu;
    ULONG_PTR __xxxClientEndScroll;
    ULONG_PTR __xxxClientDrawSize;
    ULONG_PTR __xxxClientDrawScrollBar;
    ULONG_PTR __xxxClientHitTestScrollBar;
    ULONG_PTR __xxxClientTrackInit;
} KERNEL_CALLBACK_TABLE, * PKERNEL_CALLBACK_TABLE;



VEIL_END()

#pragma pop_macro("UNICODE")

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
