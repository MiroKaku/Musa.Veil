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

#if !defined(_KERNEL_MODE)

//
// User-Mode
//

// This header file provides access to Win32, plus NTSTATUS values and some access mask values.

#define  WINDOWS_IGNORE_PACKING_MISMATCH
#define  UMDF_USING_NTSTATUS

#include <windows.h>
#include <winioctl.h>
#include <ntstatus.h>

#pragma comment(lib, "ntdll.lib")

#if _DEBUG
#define DBG _DEBUG
#endif

#else

//
// Kernel-Mode
//

#include <fltKernel.h>
#include <ntimage.h>

#endif


#include "Veil/Veil.System.Define.h"
#include "Veil/Veil.System.KernelCore.h"
#include "Veil/Veil.System.Loader.h"
#include "Veil/Veil.System.Executive.h"
#include "Veil/Veil.System.MemoryManager.h"
#include "Veil/Veil.System.ObjectManager.h"
#include "Veil/Veil.System.Process.h"
#include "Veil/Veil.System.Debug.h"
#include "Veil/Veil.System.IOManager.h"
#include "Veil/Veil.System.ALPC.h"
#include "Veil/Veil.System.PowerManager.h"
#include "Veil/Veil.System.ConfigurationManager.h"
#include "Veil/Veil.System.RuntimeLibrary.h"
#include "Veil/Veil.System.Security.h"
#include "Veil/Veil.System.Crypt.h"
#include "Veil/Veil.System.CodeIntegrity.h"
