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

#include <windef.h>

VEIL_BEGIN()

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


__kernel_entry
HDC
NTAPI
NtUserBeginPaint(
    _In_  HWND Window,
    _Out_ PAINTSTRUCT* Paint
);

__kernel_entry
BOOL
NTAPI
NtUserEndPaint(
    _In_  HWND Window,
    _In_  const PAINTSTRUCT* Paint
);


VEIL_END()

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
