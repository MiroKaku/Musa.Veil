/*
 * PROJECT:   Veil
 * FILE:      Veil.h
 * PURPOSE:   This file is part of Veil.
 *
 * LICENSE:   MIT License
 *
 * DEVELOPER: MiroKaku (kkmi04@outlook.com)
 */

#pragma once

#ifndef _VEIL_
#define _VEIL_

#ifdef __cplusplus
#ifdef VEIL_USE_SEPARATE_NAMESPACE
#define VEIL_BEGIN() namespace Veil { extern "C" {
#define VEIL_END() } }
#else
#define VEIL_BEGIN() extern "C" {
#define VEIL_END() }
#endif
#else
#ifdef VEIL_USE_SEPARATE_NAMESPACE
#define VEIL_BEGIN() namespace Veil {
#define VEIL_END() }
#else
#define VEIL_BEGIN() 
#define VEIL_END() 
#endif
#endif


#define _VEIL_STRINGIZE_(x) #x
#define _VEIL_STRINGIZE(x) _VEIL_STRINGIZE_(x)

#define _VEIL_CONCATENATE_(a, b) a ## b
#define _VEIL_CONCATENATE(a, b)  _VEIL_CONCATENATE_(a, b)


#if defined _M_IX86
#if defined _M_HYBRID
#define _VEIL_DECLARE_ALTERNATE_NAME_PREFIX "#"
#else
#define _VEIL_DECLARE_ALTERNATE_NAME_PREFIX "_"
#endif
#define _VEIL_DECLARE_ALTERNATE_NAME_PREFIX_DATA "_"
#elif defined _M_ARM64EC
#define _VEIL_DECLARE_ALTERNATE_NAME_PREFIX "#"
#define _VEIL_DECLARE_ALTERNATE_NAME_PREFIX_DATA ""
#elif defined _M_X64 || defined _M_ARM || defined _M_ARM64
#define _VEIL_DECLARE_ALTERNATE_NAME_PREFIX ""
#define _VEIL_DECLARE_ALTERNATE_NAME_PREFIX_DATA ""
#else
#error Unsupported architecture
#endif

#define _VEIL_DECLARE_ALTERNATE_NAME(name, alternate_name)  \
    __pragma(comment(linker,                                \
        "/alternatename:"                                   \
        _VEIL_DECLARE_ALTERNATE_NAME_PREFIX #name           \
        "="                                                 \
        _VEIL_DECLARE_ALTERNATE_NAME_PREFIX #alternate_name \
        ))

#define _VEIL_DECLARE_ALTERNATE_NAME_DATA(name, alternate_name)     \
    __pragma(comment(linker,                                        \
        "/alternatename:"                                           \
        _VEIL_DECLARE_ALTERNATE_NAME_PREFIX_DATA #name              \
        "="                                                         \
        _VEIL_DECLARE_ALTERNATE_NAME_PREFIX_DATA #alternate_name    \
        ))

// Fix: __imp_ is optimized away
#ifdef __cplusplus
#define _VEIL_FORCE_INCLUDE(name) \
    extern"C" __declspec(selectany) void const* const _VEIL_CONCATENATE(__forceinclude_, name) = reinterpret_cast<void const*>(&name)

#define _VEIL_FORCE_INCLUDE_RAW_SYMBOLS(name) \
    extern"C" __declspec(selectany) void const* const __identifier(_VEIL_STRINGIZE(_VEIL_CONCATENATE(__forceinclude_, name))) \
        = reinterpret_cast<void const*>(&__identifier(_VEIL_STRINGIZE(name)))
#else
#define _VEIL_FORCE_INCLUDE(name) \
    extern __declspec(selectany) void const* const _VEIL_CONCATENATE(__forceinclude_, name) = (void const*)(&name)

#define _VEIL_FORCE_INCLUDE_RAW_SYMBOLS(name)
#endif

// The _VEIL_DEFINE_IAT_SYMBOL macro provides an architecture-neutral way of
// defining IAT symbols (__imp_- or _imp__-prefixed symbols).
#ifdef _M_IX86
#define _VEIL_DEFINE_IAT_SYMBOL_MAKE_NAME(f) _VEIL_CONCATENATE(_imp__, f)
#else
#define _VEIL_DEFINE_IAT_SYMBOL_MAKE_NAME(f) _VEIL_CONCATENATE(__imp_, f)
#endif

#ifdef __cplusplus
#define _VEIL_DEFINE_IAT_SYMBOL(sym, fun) \
    extern "C" __declspec(selectany) void const* const _VEIL_DEFINE_IAT_SYMBOL_MAKE_NAME(sym) \
        = reinterpret_cast<void const*>(fun); \
    _VEIL_FORCE_INCLUDE(_VEIL_DEFINE_IAT_SYMBOL_MAKE_NAME(sym))

#define _VEIL_DEFINE_IAT_RAW_SYMBOL(sym, fun) \
    __pragma(warning(suppress:4483)) \
    extern "C" __declspec(selectany) void const* const __identifier(_VEIL_STRINGIZE(_VEIL_DEFINE_IAT_SYMBOL_MAKE_NAME(sym))) \
        = reinterpret_cast<void const*>(fun); \
    _VEIL_FORCE_INCLUDE_RAW_SYMBOLS(_VEIL_DEFINE_IAT_SYMBOL_MAKE_NAME(sym))

#else
#define _VEIL_DEFINE_IAT_SYMBOL(sym, fun) \
    extern __declspec(selectany) void const* const _VEIL_DEFINE_IAT_SYMBOL_MAKE_NAME(sym) = (void const*)(fun); \
    _VEIL_FORCE_INCLUDE(_VEIL_DEFINE_IAT_SYMBOL_MAKE_NAME(sym))

// C don't support __identifier keyword
#define _VEIL_DEFINE_IAT_RAW_SYMBOL(sym, fun)
#endif


#define VEIL_DECLARE_STRUCT(name) \
    typedef struct _VEIL_CONCATENATE(_, name) name; \
    typedef struct _VEIL_CONCATENATE(_, name) * _VEIL_CONCATENATE(P, name); \
    typedef struct _VEIL_CONCATENATE(_, name) const * _VEIL_CONCATENATE(PC, name); \
    struct _VEIL_CONCATENATE(_, name)

#define VEIL_DECLARE_STRUCT_ALIGN(name, x) \
    typedef struct _VEIL_CONCATENATE(_, name) name; \
    typedef struct _VEIL_CONCATENATE(_, name) * _VEIL_CONCATENATE(P, name); \
    typedef struct _VEIL_CONCATENATE(_, name) const * _VEIL_CONCATENATE(PC, name); \
    __declspec(align(x)) struct _VEIL_CONCATENATE(_, name)

#define VEIL_DECLARE_UNION(name) \
    typedef union _VEIL_CONCATENATE(_, name) name; \
    typedef union _VEIL_CONCATENATE(_, name) * _VEIL_CONCATENATE(P, name); \
    typedef union _VEIL_CONCATENATE(_, name) const * _VEIL_CONCATENATE(PC, name); \
    union _VEIL_CONCATENATE(_, name)


#ifndef __cplusplus
#ifndef CINTERFACE
#define CINTERFACE
#endif

#ifndef COBJMACROS
#define COBJMACROS
#endif
#endif

#ifndef __cplusplus
// This is needed to workaround C17 preprocessor errors when using legacy versions of the Windows SDK. (dmex)
#ifndef MICROSOFT_WINDOWS_WINBASE_H_DEFINE_INTERLOCKED_CPLUSPLUS_OVERLOADS
#define MICROSOFT_WINDOWS_WINBASE_H_DEFINE_INTERLOCKED_CPLUSPLUS_OVERLOADS 0
#endif
#endif


#define NTDDI_WIN6                          0x06000000      // Windows Vista
#define NTDDI_WIN6SP1                       0x06000100      // Windows Vista SP1
#define NTDDI_WIN6SP2                       0x06000200      // Windows Vista SP2
#define NTDDI_WIN6SP3                       0x06000300      // Windows Vista SP3
#define NTDDI_WIN6SP4                       0x06000400      // Windows Vista SP4

#define NTDDI_VISTA                         NTDDI_WIN6
#define NTDDI_VISTASP1                      NTDDI_WIN6SP1
#define NTDDI_VISTASP2                      NTDDI_WIN6SP2
#define NTDDI_VISTASP3                      NTDDI_WIN6SP3
#define NTDDI_VISTASP4                      NTDDI_WIN6SP4

#define NTDDI_LONGHORN                      NTDDI_VISTA     // Windows Vista

#define NTDDI_WS08                          NTDDI_WIN6SP1   // Windows Server 2008
#define NTDDI_WS08SP2                       NTDDI_WIN6SP2   // Windows Server 2008 SP2
#define NTDDI_WS08SP3                       NTDDI_WIN6SP3   // Windows Server 2008 SP3
#define NTDDI_WS08SP4                       NTDDI_WIN6SP4   // Windows Server 2008 SP4

#define NTDDI_WIN7                          0x06010000      // Windows 7
#define NTDDI_WIN8                          0x06020000      // Windows 8
#define NTDDI_WINBLUE                       0x06030000      // Windows 8.1
#define NTDDI_WINTHRESHOLD                  0x0A000000      // Windows 10.0.10240 / 1507 / Threshold 1
#define NTDDI_WIN10                         0x0A000000
#define NTDDI_WIN10_TH2                     0x0A000001      // Windows 10.0.10586 / 1511 / Threshold 2
#define NTDDI_WIN10_RS1                     0x0A000002      // Windows 10.0.14393 / 1607 / Redstone 1
#define NTDDI_WIN10_RS2                     0x0A000003      // Windows 10.0.15063 / 1703 / Redstone 2
#define NTDDI_WIN10_RS3                     0x0A000004      // Windows 10.0.16299 / 1709 / Redstone 3
#define NTDDI_WIN10_RS4                     0x0A000005      // Windows 10.0.17134 / 1803 / Redstone 4
#define NTDDI_WIN10_RS5                     0x0A000006      // Windows 10.0.17763 / 1809 / Redstone 5
#define NTDDI_WIN10_19H1                    0x0A000007      // Windows 10.0.18362 / 1903 / Titanium - 19H1
                                                            // Windows 10.0.18363 / 1909 / Titanium - 19H2
#define NTDDI_WIN10_VB                      0x0A000008      // Windows 10.0.19041 / 2004 / Vibranium
#define NTDDI_WIN10_MN                      0x0A000009      // Windows 10.0.19042 / 20H2 / Manganese
#define NTDDI_WIN10_FE                      0x0A00000A      // Windows 10.0.19043 / 21H1 / Ferrum
#define NTDDI_WIN10_CO                      0x0A00000B      // Windows 10.0.19044 / 21H2 / Cobalt
                                                            // Windows 10.0.19045 / 22H2
#define NTDDI_WIN11_CO                      NTDDI_WIN10_CO  // Windows 10.0.22000 / 21H2 / Cobalt
#define NTDDI_WIN11                         NTDDI_WIN11_CO
#define NTDDI_WIN10_NI                      0x0A00000C      // Windows 10.0.22621 / 22H2 / Nickel
#define NTDDI_WIN11_NI                      NTDDI_WIN10_NI  // Windows 10.0.22621 / 22H2 / Nickel
#define NTDDI_WIN10_CU                      0x0A00000D      // Windows 10.0.22631 / 22H2 / Copper
#define NTDDI_WIN11_CU                      NTDDI_WIN10_CU  // Windows 10.0.22631 / 23H2 / Copper

 // Fix WDK
#define NTDDI_THRESHOLD                     NTDDI_WINTHRESHOLD

#ifndef __cplusplus
#ifndef __bool_true_false_are_defined
#define __bool_true_false_are_defined 1
#define bool  _Bool
#define false 0
#define true  1
#endif
#define  nullptr NULL
#endif

#ifndef ENABLE_RTL_NUMBER_OF_V2
#define ENABLE_RTL_NUMBER_OF_V2
#endif

// Disable winternl.h
#define  _WINTERNL_

#if !defined(_KERNEL_MODE) && !defined(__KERNEL_MODE)

//
// User-Mode
//

struct IUnknown;

// This header file provides access to Win32, plus NTSTATUS values and some access mask values.

#define  WINDOWS_IGNORE_PACKING_MISMATCH
#define  UMDF_USING_NTSTATUS

#include <stdint.h>
#include <windows.h>
#include <winioctl.h>
#include <ntstatus.h>

#pragma comment(lib, "ntdll.lib")

#if _DEBUG
#define DBG _DEBUG
#endif

#else // if !defined(_KERNEL_MODE)

//
// Kernel-Mode
//

#ifndef UNICODE
#define UNICODE 1
#endif

#if __has_include(<Windows.h>)
#define _UNKNOWN_H_ // fix: Unknownbase.h and unknown.h conflict
#endif 

#include "Veil/Veil.C.stdint.h"

#pragma warning(push)
#pragma warning(disable:4324) // structure was padded due to __declspec(align())
#include <fltKernel.h>
#include <ntimage.h>
#pragma warning(pop)

#if __has_include(<Windows.h>)
#define  WIN32_LEAN_AND_MEAN
#define  _NTOS_
#define  _DEVIOCTL_
#define  _NTSECAPI_
#include "Veil/Veil.System.WinNT.h"
#include <Windows.h>
#include <Unknwn.h>
#endif

#endif // if defined(_KERNEL_MODE)


#include "Veil/Veil.System.Define.h"
#include "Veil/Veil.System.KernelCore.h"
#include "Veil/Veil.System.MemoryManager.h"
#include "Veil/Veil.System.ObjectManager.h"
#include "Veil/Veil.System.Loader.h"
#include "Veil/Veil.System.Executive.h"
#include "Veil/Veil.System.Process.h"
#include "Veil/Veil.System.Debug.h"
#include "Veil/Veil.System.IOManager.h"
#include "Veil/Veil.System.ALPC.h"
#include "Veil/Veil.System.PowerManager.h"
#include "Veil/Veil.System.ConfigurationManager.h"
#include "Veil/Veil.System.Nls.h"
#include "Veil/Veil.System.RuntimeLibrary.h"
#include "Veil/Veil.System.Security.h"
#include "Veil/Veil.System.Etw.h"
#include "Veil/Veil.System.MinCrypt.h"
#include "Veil/Veil.System.VirtualDesktop.h"
#include "Veil/Veil.System.Win32.h"
#include "Veil/Veil.System.Device.h"
#include "Veil/Veil.System.PNP.h"
#include "Veil/Veil.System.TransactionManager.h"
#include "Veil/Veil.System.VDM.h"
#include "Veil/Veil.System.Prefetcher.h"

#endif // _VEIL_
