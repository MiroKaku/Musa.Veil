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

NTSYSCALLAPI
ULONG_PTR
NTAPI
NtUserQueryWindow(
    _In_ HWND WindowHandle,
    _In_ WINDOWINFOCLASS WindowInfo
);

NTSYSCALLAPI
NTSTATUS
NTAPI
NtUserTestForInteractiveUser(
    _In_ PLUID AuthenticationId
);

NTSYSCALLAPI
NTSTATUS
NTAPI
NtUserCheckAccessForIntegrityLevel(
    _In_ ULONG ProcessIdFirst,
    _In_ ULONG ProcessIdSecond,
    _Out_ PBOOLEAN GrantedAccess
);

NTSYSCALLAPI
NTSTATUS
NTAPI
NtUserCheckProcessForClipboardAccess(
    _In_ ULONG ProcessId,
    _Out_ PULONG GrantedAccess
);

NTSYSCALLAPI
ULONG
NTAPI
NtUserInternalGetWindowText(
    _In_ HWND WindowHandle,
    _Out_writes_to_(cchMaxCount, return +1) LPWSTR pString,
    _In_ ULONG cchMaxCount
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
NTSYSCALLAPI
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
NTSYSCALLAPI
NTSTATUS
NTAPI
ConsoleControl(
    _In_ CONSOLECONTROL Command,
    _In_reads_bytes_(ConsoleInformationLength) PVOID ConsoleInformation,
    _In_ ULONG ConsoleInformationLength
);
#endif



VEIL_END()

#pragma pop_macro("UNICODE")

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
