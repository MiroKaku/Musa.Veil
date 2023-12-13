/*
 * PROJECT:   Veil
 * FILE:      Veil.System.VirtualDesktop.h
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


#if !defined(_KERNEL_MODE) && (NTDDI_VERSION >= NTDDI_WIN10)

#include <combaseapi.h>
#include <objectarray.h>
#include <inspectable.h>


// CLSID
//   HKEY_CLASSES_ROOT\CLSID\*
// 
// IID
//   HKEY_CLASSES_ROOT\Interface\*
// 
// Tools
//   OleViewDotNet: https://github.com/tyranid/oleviewdotnet
//   IDA: twinui.dll(10.0.10240+)/twinui.pcshell.dll(10.0.15063+), Search for "for `IVirtualDesktop'" in the name window.


// CLSID_ImmersiveShell = {C2F03A33-21F5-47FA-B4BB-156362A2F239}
DEFINE_GUID(CLSID_ImmersiveShell, 0xC2F03A33, 0x21F5, 0x47FA, 0xB4, 0xBB, 0x15, 0x63, 0x62, 0xA2, 0xF2, 0x39);

// CLSID_VirtualDesktopManager = {AA509086-5CA9-4C25-8F95-589D3C07B48A}
//DEFINE_GUID(CLSID_VirtualDesktopManager, 0xAA509086, 0x5CA9, 0x4C25, 0x8F, 0x95, 0x58, 0x9D, 0x3C, 0x07, 0xB4, 0x8A);

// 10.0.10240~10.0.22621 twinui.pcshell.dll!SID_VirtualDesktopManager = {C5E0CDCA-7B6E-41B2-9FC4-D93975CC467B}
DEFINE_GUID(CLSID_VirtualDesktopManagerInternal, 0xC5E0CDCA, 0x7B6E, 0x41B2, 0x9F, 0xC4, 0xD9, 0x39, 0x75, 0xCC, 0x46, 0x7B);

// 10.0.10240~10.0.22621 twinui.pcshell.dll!SID_VirtualDesktopNotificationService = {A501FDEC-4A09-464C-AE4E-1B9C21B84918}
DEFINE_GUID(CLSID_VirtualDesktopNotificationService, 0xA501FDEC, 0x4A09, 0x464C, 0xAE, 0x4E, 0x1B, 0x9C, 0x21, 0xB8, 0x49, 0x18);

// 10.0.18362~10.0.22621 twinui.pcshell.dll!SID_VirtualDesktopPinnedApps = {B5A399E7-1C87-46B8-88E9-FC5747B171BD}
DEFINE_GUID(CLSID_VirtualDesktopPinnedApps, 0xB5A399E7, 0x1C87, 0x46B8, 0x88, 0xE9, 0xFC, 0x57, 0x47, 0xB1, 0x71, 0xBD);


// Ignore following API's:
typedef IUnknown IApplicationView;
typedef IUnknown IApplicationViewChangeListener;
typedef IUnknown IImmersiveApplication;
typedef IUnknown IClassicWindowExternal;

typedef enum APPLICATION_VIEW_CLOAK_TYPE
{
    AVCT_NONE               = 0,
    AVCT_DEFAULT            = 1,
    AVCT_VIRTUAL_DESKTOP    = 2
} APPLICATION_VIEW_CLOAK_TYPE;

typedef enum APPLICATION_VIEW_COMPATIBILITY_POLICY
{
    AVCP_NONE                   = 0,
    AVCP_SMALL_SCREEN           = 1,
    AVCP_TABLET_SMALL_SCREEN    = 2,
    AVCP_VERY_SMALL_SCREEN      = 3,
    AVCP_HIGH_SCALE_FACTOR      = 4
} APPLICATION_VIEW_COMPATIBILITY_POLICY;

typedef enum VIRTUAL_DESKTOP_ADJACENT_DIRECTION
{
    VDAD_LEFT  = 3,
    VDAD_RIGHT = 4,
} VIRTUAL_DESKTOP_ADJACENT_DIRECTION;

typedef enum REMOVE_APPLICATION_VIEW_OPTIONS
{
    // Unknown

} REMOVE_APPLICATION_VIEW_OPTIONS;

typedef enum APPLICATION_VIEW_CHANGE
{
    // Unknown

} APPLICATION_VIEW_CHANGE;


// 10.0.10240~10.0.17134 twinui.dll/twinui.pcshell.dll
// CApplicationViewManager::CApplicationViewManager
//     const CApplicationViewManager::`vftable'{for `Microsoft::WRL::Details::Selector<..., struct Microsoft::WRL::ChainInterfaces<..., struct IApplicationViewCollection, ...
#ifndef __IApplicationViewCollection_INTERFACE_DEFINED__
#define __IApplicationViewCollection_INTERFACE_DEFINED__

/* interface IApplicationViewCollection */
/* [object][uuid] */


// 10.0.10240~10.0.17134 = "{2C08ADF0-A386-4B35-9250-0FE183476FCC}"
DEFINE_GUID(IID_IApplicationViewCollection, 0x2C08ADF0, 0xA386, 0x4B35, 0x92, 0x50, 0x0F, 0xE1, 0x83, 0x47, 0x6F, 0xCC);

#undef  INTERFACE
#define INTERFACE IApplicationViewCollection

DECLARE_INTERFACE_IID_(IApplicationViewCollection, IUnknown, "2C08ADF0-A386-4B35-9250-0FE183476FCC")
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR * __RPC_FAR * ppvObject) PURE;

    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /*** IApplicationViewCollection methods ***/
    STDMETHOD(GetViews)(THIS_
        /* [out] */ __RPC__out IObjectArray * *Views) PURE;

    STDMETHOD(GetViewsByZOrder)(THIS_
        /* [out] */ __RPC__out IObjectArray * *Views) PURE;

    STDMETHOD(GetViewsByAppUserModelId)(THIS_
        /* [in] */  __RPC__in  PWSTR AppUserModelId,
        /* [out] */ __RPC__out IObjectArray * *Views) PURE;

    STDMETHOD(GetViewForHwnd)(THIS_
        /* [in] */  __RPC__in  HWND Window,
        /* [out] */ __RPC__out IApplicationView * *View) PURE;

    STDMETHOD(GetViewForApplication)(THIS_
        /* [in] */  __RPC__in  IImmersiveApplication * Application,
        /* [out] */ __RPC__out IApplicationView * *View) PURE;

    STDMETHOD(GetViewForAppUserModelId)(THIS_
        /* [in] */  __RPC__in  PCWSTR AppUserModelId,
        /* [out] */ __RPC__out IApplicationView * *View) PURE;

    STDMETHOD(GetViewInFocus)(THIS_
        /* [out] */ __RPC__out IApplicationView * *View) PURE;

    STDMETHOD(RefreshCollection)(THIS) PURE;

    STDMETHOD(RegisterForApplicationViewChanges)(THIS_
        /* [in] */  __RPC__in  IApplicationViewChangeListener* Listener,
        /* [out] */ __RPC__out ULONG* Cookie) PURE;

    STDMETHOD(UnregisterForApplicationViewChanges)(THIS_
        /* [in] */  __RPC__in  ULONG Cookie) PURE;

    STDMETHOD(AddWin32ApplicationView)(THIS_
        /* [in] */  __RPC__in  IClassicWindowExternal* WndExt,
        /* [in] [out] */ __RPC__inout IApplicationView * *View) PURE;

    STDMETHOD(AddWinRTApplicationView)(THIS_
        /* [in] */  __RPC__in  IImmersiveApplication* Application,
        /* [in] */  __RPC__in  IUnknown * View) PURE;

    STDMETHOD(AddApplicationView)(THIS_
        /* [in] */ __RPC__in IApplicationView * View) PURE;

    STDMETHOD(RemoveApplicationView)(THIS_
        /* [in] */ __RPC__in IApplicationView * View,
        /* [in] */ __RPC__in REMOVE_APPLICATION_VIEW_OPTIONS Options) PURE;

    STDMETHOD(SetViewInFocus)(THIS_
        /* [in] */ __RPC__in IApplicationView * View) PURE;

    STDMETHOD(SetViewPendingFocus)(THIS_
        /* [in] */ __RPC__in IApplicationView * View) PURE;

    STDMETHOD(HandleWindowReplaced)(THIS_
        /* [in] */ __RPC__in HWND OldWindow,
        /* [in] */ __RPC__in HWND NewWindow) PURE;

    STDMETHOD(RaiseApplicationViewChanged)(THIS_
        /* [in] */ __RPC__in IApplicationView* View,
        /* [in] */ __RPC__in APPLICATION_VIEW_CHANGE Type,
        /* [in] */ __RPC__in IUnknown* _1) PURE;

};


#ifdef COBJMACROS

#define IApplicationViewCollection_QueryInterface(This,riid,ppvObject) \
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IApplicationViewCollection_AddRef(This)    \
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IApplicationViewCollection_Release(This)   \
    ( (This)->lpVtbl -> Release(This) ) 


#define IApplicationViewCollection_GetViews(This,Views)  \
    ( (This)->lpVtbl -> GetViews(This,Views) ) 

#define IApplicationViewCollection_GetViewsByZOrder(This,Views)   \
    ( (This)->lpVtbl -> GetViewsByZOrder(This,Views) ) 

#define IApplicationViewCollection_GetViewsByAppUserModelId(This,AppUserModelId,Views)    \
    ( (This)->lpVtbl -> GetViewsByAppUserModelId(This,AppUserModelId,Views) ) 

#define IApplicationViewCollection_GetViewForHwnd(This,Window,View)  \
    ( (This)->lpVtbl -> GetViewForHwnd(This,Window,View) ) 

#define IIApplicationViewCollection_GetViewForApplication(This,Application,View) \
    ( (This)->lpVtbl -> GetViewForApplication(This,Application,View) ) 

#define IIApplicationViewCollection_GetViewForAppUserModelId(This,AppUserModelId,View) \
    ( (This)->lpVtbl -> GetViewForAppUserModelId(This,AppUserModelId,View) ) 

#define IIApplicationViewCollection_GetViewInFocus(This,View) \
    ( (This)->lpVtbl -> GetViewInFocus(This,View) ) 

#define IIApplicationViewCollection_RefreshCollection(This) \
    ( (This)->lpVtbl -> RefreshCollection(This) ) 

#define IIApplicationViewCollection_RegisterForApplicationViewChanges(This,Listener,Cookie) \
    ( (This)->lpVtbl -> RegisterForApplicationViewChanges(This,Listener,Cookie) ) 

#define IIApplicationViewCollection_UnregisterForApplicationViewChanges(This,Cookie) \
    ( (This)->lpVtbl -> UnregisterForApplicationViewChanges(This,Cookie) ) 

#define IIApplicationViewCollection_AddWin32ApplicationView(This,WndExt,View) \
    ( (This)->lpVtbl -> AddWin32ApplicationView(This,WndExt,View) ) 

#define IIApplicationViewCollection_AddWinRTApplicationView(This,Application,View) \
    ( (This)->lpVtbl -> AddWinRTApplicationView(This,Application,View) ) 

#define IIApplicationViewCollection_AddApplicationView(This,View) \
    ( (This)->lpVtbl -> AddApplicationView(This,View) ) 

#define IIApplicationViewCollection_RemoveApplicationView(This,View) \
    ( (This)->lpVtbl -> RemoveApplicationView(This,View) ) 

#define IIApplicationViewCollection_SetViewInFocus(This,View) \
    ( (This)->lpVtbl -> SetViewInFocus(This,View) ) 

#define IIApplicationViewCollection_SetViewPendingFocus(This,View) \
    ( (This)->lpVtbl -> SetViewPendingFocus(This,View) ) 

#define IIApplicationViewCollection_HandleWindowReplaced(This,OldWindow,NewWindow) \
    ( (This)->lpVtbl -> HandleWindowReplaced(This,OldWindow,NewWindow) ) 

#define IIApplicationViewCollection_RaiseApplicationViewChanged(This,View,Type,_1) \
    ( (This)->lpVtbl -> RaiseApplicationViewChanged(This,View,Type,_1) ) 

#endif /* COBJMACROS */


#endif /* __IApplicationViewCollection_INTERFACE_DEFINED__ */


// 10.0.17763~10.0.22621 twinui.dll/twinui.pcshell.dll
// CApplicationViewManager::CApplicationViewManager
//     const CApplicationViewManager::`vftable'{for `Microsoft::WRL::Details::Selector<..., struct Microsoft::WRL::ChainInterfaces<..., struct IApplicationViewCollection, ...
#ifndef __IApplicationViewCollection2_INTERFACE_DEFINED__
#define __IApplicationViewCollection2_INTERFACE_DEFINED__

/* interface IApplicationViewCollection */
/* [object][uuid] */


// 10.0.17763~10.0.22621 = "{1841C6D7-4F9D-42C0-AF41-8747538F10E5}"
DEFINE_GUID(IID_IApplicationViewCollection2, 0x1841C6D7, 0x4F9D, 0x42C0, 0xAF, 0x41, 0x87, 0x47, 0x53, 0x8F, 0x10, 0xE5);

#undef  INTERFACE
#define INTERFACE IApplicationViewCollection2

DECLARE_INTERFACE_IID_(IApplicationViewCollection2, IUnknown, "1841C6D7-4F9D-42C0-AF41-8747538F10E5")
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR * __RPC_FAR * ppvObject) PURE;

    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /*** IApplicationViewCollection methods ***/
    STDMETHOD(GetViews)(THIS_
        /* [out] */ __RPC__out IObjectArray * *Views) PURE;

    STDMETHOD(GetViewsByZOrder)(THIS_
        /* [out] */ __RPC__out IObjectArray * *Views) PURE;

    STDMETHOD(GetViewsByAppUserModelId)(THIS_
        /* [in] */  __RPC__in  PWSTR AppUserModelId,
        /* [out] */ __RPC__out IObjectArray * *Views) PURE;

    STDMETHOD(GetViewForHwnd)(THIS_
        /* [in] */  __RPC__in  HWND Window,
        /* [out] */ __RPC__out IApplicationView * *View) PURE;

    STDMETHOD(GetViewForApplication)(THIS_
        /* [in] */  __RPC__in  IImmersiveApplication * Application,
        /* [out] */ __RPC__out IApplicationView * *View) PURE;

    STDMETHOD(GetViewForAppUserModelId)(THIS_
        /* [in] */  __RPC__in  PCWSTR AppUserModelId,
        /* [out] */ __RPC__out IApplicationView * *View) PURE;

    STDMETHOD(GetViewInFocus)(THIS_
        /* [out] */ __RPC__out IApplicationView * *View) PURE;

    STDMETHOD(TryGetLastActiveVisibleView)(THIS_
        /* [out] */ __RPC__out IApplicationView * *View) PURE;

    STDMETHOD(RefreshCollection)(THIS) PURE;

    STDMETHOD(RegisterForApplicationViewChanges)(THIS_
        /* [in] */  __RPC__in  IApplicationViewChangeListener * Listener,
        /* [out] */ __RPC__out ULONG * Cookie) PURE;

    STDMETHOD(UnregisterForApplicationViewChanges)(THIS_
        /* [in] */  __RPC__in  ULONG Cookie) PURE;

    STDMETHOD(AddWin32ApplicationView)(THIS_
        /* [in] */  __RPC__in  IClassicWindowExternal * WndExt,
        /* [in] [out] */ __RPC__inout IApplicationView * *View) PURE;

    STDMETHOD(AddWinRTApplicationView)(THIS_
        /* [in] */  __RPC__in  IImmersiveApplication * Application,
        /* [in] */  __RPC__in  IUnknown * View) PURE;

    STDMETHOD(AddApplicationView)(THIS_
        /* [in] */ __RPC__in IApplicationView * View) PURE;

    STDMETHOD(RemoveApplicationView)(THIS_
        /* [in] */ __RPC__in IApplicationView * View,
        /* [in] */ __RPC__in REMOVE_APPLICATION_VIEW_OPTIONS Options) PURE;

    STDMETHOD(SetViewInFocus)(THIS_
        /* [in] */ __RPC__in IApplicationView * View) PURE;

    STDMETHOD(SetViewPendingFocus)(THIS_
        /* [in] */ __RPC__in IApplicationView * View) PURE;

    STDMETHOD(HandleWindowReplaced)(THIS_
        /* [in] */ __RPC__in HWND OldWindow,
        /* [in] */ __RPC__in HWND NewWindow) PURE;

    STDMETHOD(RaiseApplicationViewChanged)(THIS_
        /* [in] */ __RPC__in IApplicationView * View,
        /* [in] */ __RPC__in APPLICATION_VIEW_CHANGE Type,
        /* [in] */ __RPC__in IUnknown * _1) PURE;
};


#ifdef COBJMACROS

#define IApplicationViewCollection2_QueryInterface(This,riid,ppvObject) \
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IApplicationViewCollection2_AddRef(This)    \
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IApplicationViewCollection2_Release(This)   \
    ( (This)->lpVtbl -> Release(This) ) 


#define IApplicationViewCollection2_GetViews(This,Views)  \
    ( (This)->lpVtbl -> GetViews(This,Views) ) 

#define IApplicationViewCollection2_GetViewsByZOrder(This,Views)   \
    ( (This)->lpVtbl -> GetViewsByZOrder(This,Views) ) 

#define IApplicationViewCollection2_GetViewsByAppUserModelId(This,AppUserModelId,Views)    \
    ( (This)->lpVtbl -> GetViewsByAppUserModelId(This,AppUserModelId,Views) ) 

#define IApplicationViewCollection2_GetViewForHwnd(This,Window,View)  \
    ( (This)->lpVtbl -> GetViewForHwnd(This,Window,View) ) 

#define IIApplicationViewCollection2_GetViewForApplication(This,Application,View) \
    ( (This)->lpVtbl -> GetViewForApplication(This,Application,View) ) 

#define IIApplicationViewCollection2_GetViewForAppUserModelId(This,AppUserModelId,View) \
    ( (This)->lpVtbl -> GetViewForAppUserModelId(This,AppUserModelId,View) ) 

#define IIApplicationViewCollection2_GetViewInFocus(This,View) \
    ( (This)->lpVtbl -> GetViewInFocus(This,View) ) 

#define IIApplicationViewCollection2_TryGetLastActiveVisibleView(This,View) \
    ( (This)->lpVtbl -> TryGetLastActiveVisibleView(This,View) ) 

#define IIApplicationViewCollection2_RefreshCollection(This) \
    ( (This)->lpVtbl -> RefreshCollection(This) ) 

#define IIApplicationViewCollection2_RegisterForApplicationViewChanges(This,Listener,Cookie) \
    ( (This)->lpVtbl -> RegisterForApplicationViewChanges(This,Listener,Cookie) ) 

#define IIApplicationViewCollection2_UnregisterForApplicationViewChanges(This,Cookie) \
    ( (This)->lpVtbl -> UnregisterForApplicationViewChanges(This,Cookie) ) 

#define IIApplicationViewCollection2_AddWin32ApplicationView(This,WndExt,View) \
    ( (This)->lpVtbl -> AddWin32ApplicationView(This,WndExt,View) ) 

#define IIApplicationViewCollection2_AddWinRTApplicationView(This,Application,View) \
    ( (This)->lpVtbl -> AddWinRTApplicationView(This,Application,View) ) 

#define IIApplicationViewCollection2_AddApplicationView(This,View) \
    ( (This)->lpVtbl -> AddApplicationView(This,View) ) 

#define IIApplicationViewCollection2_RemoveApplicationView(This,View) \
    ( (This)->lpVtbl -> RemoveApplicationView(This,View) ) 

#define IIApplicationViewCollection2_SetViewInFocus(This,View) \
    ( (This)->lpVtbl -> SetViewInFocus(This,View) ) 

#define IIApplicationViewCollection2_SetViewPendingFocus(This,View) \
    ( (This)->lpVtbl -> SetViewPendingFocus(This,View) ) 

#define IIApplicationViewCollection2_HandleWindowReplaced(This,OldWindow,NewWindow) \
    ( (This)->lpVtbl -> HandleWindowReplaced(This,OldWindow,NewWindow) ) 

#define IIApplicationViewCollection2_RaiseApplicationViewChanged(This,View,Type,_1) \
    ( (This)->lpVtbl -> RaiseApplicationViewChanged(This,View,Type,_1) ) 

#endif /* COBJMACROS */


#endif /* __IApplicationViewCollection2_INTERFACE_DEFINED__ */


// 10.0.10240~10.0.19045 twinui.dll/twinui.pcshell.dll
// CVirtualDesktop::CVirtualDesktop
//     const CVirtualDesktop::`vftable'{for `IVirtualDesktop'}
#ifndef __IVirtualDesktop_INTERFACE_DEFINED__
#define __IVirtualDesktop_INTERFACE_DEFINED__

/* interface IVirtualDesktop */
/* [object][uuid] */


// 10.0.10240~10.0.19045 = "{FF72FFDD-BE7E-43FC-9C03-AD81681E88E4}"
DEFINE_GUID(IID_IVirtualDesktop, 0xFF72FFDD, 0xBE7E, 0x43FC, 0x9C, 0x03, 0xAD, 0x81, 0x68, 0x1E, 0x88, 0xE4);

#undef  INTERFACE
#define INTERFACE IVirtualDesktop

DECLARE_INTERFACE_IID_(IVirtualDesktop, IUnknown, "FF72FFDD-BE7E-43FC-9C03-AD81681E88E4")
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR * __RPC_FAR * ppvObject) PURE;

    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /*** IVirtualDesktop methods ***/
    STDMETHOD(IsViewVisible)(THIS_
        /* [in] */  __RPC__in  IApplicationView * View,
        /* [out] */ __RPC__out BOOL * IsVisible) PURE;

    STDMETHOD(GetID)(THIS_
        /* [out] */ __RPC__out GUID * DesktopId) PURE;

    // 10.0.19041+
    STDMETHOD(GetName)(THIS_
        /* [out] */ __RPC__out HSTRING * Name) PURE;
};


#ifdef COBJMACROS

#define IVirtualDesktop_QueryInterface(This,riid,ppvObject) \
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVirtualDesktop_AddRef(This)    \
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVirtualDesktop_Release(This)   \
    ( (This)->lpVtbl -> Release(This) ) 


#define IVirtualDesktop_IsViewVisible(This,View,IsVisible)  \
    ( (This)->lpVtbl -> IsViewVisible(This,View,IsVisible) ) 

#define IVirtualDesktop_GetID(This,DesktopId)   \
    ( (This)->lpVtbl -> GetID(This,DesktopId) ) 

#define IVirtualDesktop_GetName(This,Name)   \
    ( (This)->lpVtbl -> GetName(This,Name) ) 

#endif /* COBJMACROS */


#endif  /* __IVirtualDesktop_INTERFACE_DEFINED__ */


// 10.0.22000~10.0.22621 twinui.pcshell.dll
// CVirtualDesktop::CVirtualDesktop
//     const CVirtualDesktop::`vftable'{for `IVirtualDesktop'}
#ifndef __IVirtualDesktop2_INTERFACE_DEFINED__
#define __IVirtualDesktop2_INTERFACE_DEFINED__

/* interface IVirtualDesktop */
/* [object][uuid] */


// 10.0.22000~10.0.22621 = "{536D3495-B208-4CC9-AE26-DE8111275BF8}"
DEFINE_GUID(IID_IVirtualDesktop2, 0x536D3495, 0xB208, 0x4CC9, 0xAE, 0x26, 0xDE, 0x81, 0x11, 0x27, 0x5B, 0xF8);

#undef  INTERFACE
#define INTERFACE IVirtualDesktop2

DECLARE_INTERFACE_IID_(IVirtualDesktop2, IUnknown, "536D3495-B208-4CC9-AE26-DE8111275BF8")
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR * __RPC_FAR * ppvObject) PURE;

    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /*** IVirtualDesktop methods ***/
    STDMETHOD(IsViewVisible)(THIS_
        /* [in] */  __RPC__in  IApplicationView * View,
        /* [out] */ __RPC__out BOOL * IsVisible) PURE;

    STDMETHOD(GetID)(THIS_
        /* [out] */ __RPC__out GUID * DesktopId) PURE;

    STDMETHOD(GetMonitor)(THIS_
        /* [out] */ __RPC__out HMONITOR * Monitor) PURE;

    STDMETHOD(GetName)(THIS_
        /* [out] */ __RPC__out HSTRING * Name) PURE;

    STDMETHOD(GetWallpaper)(THIS_
        /* [out] */ __RPC__out HSTRING * Path) PURE;

};


#ifdef COBJMACROS

#define IVirtualDesktop2_QueryInterface(This,riid,ppvObject) \
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVirtualDesktop2_AddRef(This)    \
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVirtualDesktop2_Release(This)   \
    ( (This)->lpVtbl -> Release(This) ) 


#define IVirtualDesktop2_IsViewVisible(This,View,IsVisible)  \
    ( (This)->lpVtbl -> IsViewVisible(This,View,IsVisible) ) 

#define IVirtualDesktop2_GetID(This,DesktopId)   \
    ( (This)->lpVtbl -> GetID(This,DesktopId) ) 

#define IVirtualDesktop2_GetMonitor(This,Monitor)    \
    ( (This)->lpVtbl -> GetMonitor(This,Monitor) ) 

#define IVirtualDesktop2_GetName(This,Name)  \
    ( (This)->lpVtbl -> GetName(This,Name) ) 

#define IVirtualDesktop2_GetWallpaper(This,Path) \
    ( (This)->lpVtbl -> GetWallpaper(This,Path) ) 

#endif /* COBJMACROS */


#endif  /* __IVirtualDesktop2_INTERFACE_DEFINED__ */


// 10.0.10240~10.0.10586 twinui.dll/twinui.pcshell.dll
// CVirtualDesktopManager::CVirtualDesktopManager
//     const CVirtualDesktopManager::`vftable'
#ifndef __IVirtualDesktopManagerInternal_INTERFACE_DEFINED__
#define __IVirtualDesktopManagerInternal_INTERFACE_DEFINED__

/* interface IVirtualDesktopManagerInternal */
/* [object][uuid] */


// 10.0.10240~10.0.10586 = "{AF8DA486-95BB-4460-B3B7-6E7A6B2962B5}"
DEFINE_GUID(IID_IVirtualDesktopManagerInternal, 0xAF8DA486, 0x95BB, 0x4460, 0xB3, 0xB7, 0x6E, 0x7A, 0x6B, 0x29, 0x62, 0xB5);

#undef  INTERFACE
#define INTERFACE IVirtualDesktopManagerInternal

DECLARE_INTERFACE_IID_(IVirtualDesktopManagerInternal, IUnknown, "AF8DA486-95BB-4460-B3B7-6E7A6B2962B5")
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR * __RPC_FAR * ppvObject) PURE;

    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /*** IVirtualDesktopManagerInternal methods ***/
    STDMETHOD(GetCount)(THIS_
        /* [out] */ __RPC__out UINT * Count) PURE;

    STDMETHOD(MoveViewToDesktop)(THIS_
        /* [in] */  __RPC__in  IApplicationView * View,
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop) PURE;

    STDMETHOD(CanViewMoveDesktops)(THIS_
        /* [in] */  __RPC__in  IApplicationView * View,
        /* [out] */ __RPC__out BOOL * Is) PURE;

    STDMETHOD(GetCurrentDesktop)(THIS_
        /* [out] */ __RPC__out IVirtualDesktop * *Desktop) PURE;

    STDMETHOD(GetDesktops)(THIS_
        /* [out] */ __RPC__out IObjectArray * *Desktops) PURE;

    STDMETHOD(GetAdjacentDesktop)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [in] */  __RPC__in  VIRTUAL_DESKTOP_ADJACENT_DIRECTION Direction,
        /* [out] */ __RPC__out IVirtualDesktop * *AdjacentDesktop) PURE;

    STDMETHOD(SwitchDesktop)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop) PURE;

    STDMETHOD(CreateDesktop)(THIS_
        /* [out] */ __RPC__out IVirtualDesktop * *Desktop) PURE;

    STDMETHOD(RemoveDesktop)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Remove,
        /* [out] */ __RPC__out IVirtualDesktop * *FallbackDesktop) PURE;

    STDMETHOD(FindDesktop)(THIS_
        /* [in] */  __RPC__in  REFGUID DesktopId,
        /* [out] */ __RPC__out IVirtualDesktop * *Desktop) PURE;

};


#ifdef COBJMACROS

#define IVirtualDesktopManagerInternal_QueryInterface(This,riid,ppvObject) \
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVirtualDesktopManagerInternal_AddRef(This)    \
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVirtualDesktopManagerInternal_Release(This)   \
    ( (This)->lpVtbl -> Release(This) ) 


#define IVirtualDesktopManagerInternal_GetCount(This,Count)  \
    ( (This)->lpVtbl -> GetCount(This,Count) ) 

#define IVirtualDesktopManagerInternal_MoveViewToDesktop(This,View,Desktop)   \
    ( (This)->lpVtbl -> MoveViewToDesktop(This,View,Desktop) ) 

#define IVirtualDesktopManagerInternal_CanViewMoveDesktops(This,View,Is)    \
    ( (This)->lpVtbl -> CanViewMoveDesktops(This,View,Is) ) 

#define IVirtualDesktopManagerInternal_GetCurrentDesktop(This,Desktop)  \
    ( (This)->lpVtbl -> GetCurrentDesktop(This,Desktop) ) 

#define IVirtualDesktopManagerInternal_GetDesktops(This,Desktops) \
    ( (This)->lpVtbl -> GetDesktops(This,Desktops) ) 

#define IVirtualDesktopManagerInternal_GetAdjacentDesktop(This,Desktop,Direction,AdjacentDesktop) \
    ( (This)->lpVtbl -> GetAdjacentDesktop(This,Desktop,Direction,AdjacentDesktop) ) 

#define IVirtualDesktopManagerInternal_SwitchDesktop(This,Desktop) \
    ( (This)->lpVtbl -> SwitchDesktop(This,Desktop) ) 

#define IVirtualDesktopManagerInternal_CreateDesktop(This,Desktop) \
    ( (This)->lpVtbl -> CreateDesktop(This,Desktop) ) 

#define IVirtualDesktopManagerInternal_RemoveDesktop(This,Remove,FallbackDesktop) \
    ( (This)->lpVtbl -> RemoveDesktop(This,Remove,FallbackDesktop) ) 

#define IVirtualDesktopManagerInternal_FindDesktop(This,DesktopId,Desktop) \
    ( (This)->lpVtbl -> FindDesktop(This,DesktopId,Desktop) ) 

#endif /* COBJMACROS */


#endif  /* __IVirtualDesktopManagerInternal_INTERFACE_DEFINED__ */


// 10.0.14393~10.0.19045 twinui.dll/twinui.pcshell.dll
// CVirtualDesktopManager::CVirtualDesktopManager
//     const CVirtualDesktopManager::`vftable'
#ifndef __IVirtualDesktopManagerInternal2_INTERFACE_DEFINED__
#define __IVirtualDesktopManagerInternal2_INTERFACE_DEFINED__

/* interface IVirtualDesktopManagerInternal */
/* [object][uuid] */


// 10.0.14393~10.0.19045 = "{F31574D6-B682-4CDC-BD56-1827860ABEC6}"
DEFINE_GUID(IID_IVirtualDesktopManagerInternal2, 0xF31574D6, 0xB682, 0x4CDC, 0xBD, 0x56, 0x18, 0x27, 0x86, 0x0A, 0xBE, 0xC6);

#undef  INTERFACE
#define INTERFACE IVirtualDesktopManagerInternal2

DECLARE_INTERFACE_IID_(IVirtualDesktopManagerInternal2, IUnknown, "F31574D6-B682-4CDC-BD56-1827860ABEC6")
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR * __RPC_FAR * ppvObject) PURE;

    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /*** IVirtualDesktopManagerInternal methods ***/
    STDMETHOD(GetCount)(THIS_
        /* [out] */ __RPC__out UINT * Count) PURE;

    STDMETHOD(MoveViewToDesktop)(THIS_
        /* [in] */  __RPC__in  IApplicationView * View,
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop) PURE;

    STDMETHOD(CanViewMoveDesktops)(THIS_
        /* [in] */  __RPC__in  IApplicationView * View,
        /* [out] */ __RPC__out BOOL * Is) PURE;

    STDMETHOD(GetCurrentDesktop)(THIS_
        /* [out] */ __RPC__out IVirtualDesktop * *Desktop) PURE;

    STDMETHOD(GetDesktops)(THIS_
        /* [out] */ __RPC__out IObjectArray * *Desktops) PURE;

    STDMETHOD(GetAdjacentDesktop)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [in] */  __RPC__in  VIRTUAL_DESKTOP_ADJACENT_DIRECTION Direction,
        /* [out] */ __RPC__out IVirtualDesktop * *AdjacentDesktop) PURE;

    STDMETHOD(SwitchDesktop)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop) PURE;

    STDMETHOD(CreateDesktop)(THIS_
        /* [out] */ __RPC__out IVirtualDesktop * *Desktop) PURE;

    STDMETHOD(RemoveDesktop)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Remove,
        /* [out] */ __RPC__out IVirtualDesktop * *FallbackDesktop) PURE;

    STDMETHOD(FindDesktop)(THIS_
        /* [in] */  __RPC__in  REFGUID DesktopId,
        /* [out] */ __RPC__out IVirtualDesktop * *Desktop) PURE;

    STDMETHOD(GetDesktopSwitchIncludeExcludeViews)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [out] */ __RPC__out IObjectArray**,
        /* [out] */ __RPC__out IObjectArray**) PURE;
};


#ifdef COBJMACROS

#define IVirtualDesktopManagerInternal2_QueryInterface(This,riid,ppvObject) \
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVirtualDesktopManagerInternal2_AddRef(This)    \
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVirtualDesktopManagerInternal2_Release(This)   \
    ( (This)->lpVtbl -> Release(This) ) 


#define IVirtualDesktopManagerInternal2_GetCount(This,Count)  \
    ( (This)->lpVtbl -> GetCount(This,Count) ) 

#define IVirtualDesktopManagerInternal2_MoveViewToDesktop(This,View,Desktop)   \
    ( (This)->lpVtbl -> MoveViewToDesktop(This,View,Desktop) ) 

#define IVirtualDesktopManagerInternal2_CanViewMoveDesktops(This,View,Is)    \
    ( (This)->lpVtbl -> CanViewMoveDesktops(This,View,Is) ) 

#define IVirtualDesktopManagerInternal2_GetCurrentDesktop(This,Desktop)  \
    ( (This)->lpVtbl -> GetCurrentDesktop(This,Desktop) ) 

#define IVirtualDesktopManagerInternal2_GetDesktops(This,Desktops) \
    ( (This)->lpVtbl -> GetDesktops(This,Desktops) ) 

#define IVirtualDesktopManagerInternal2_GetAdjacentDesktop(This,Desktop,Direction,AdjacentDesktop) \
    ( (This)->lpVtbl -> GetAdjacentDesktop(This,Desktop,Direction,AdjacentDesktop) ) 

#define IVirtualDesktopManagerInternal2_SwitchDesktop(This,Desktop) \
    ( (This)->lpVtbl -> SwitchDesktop(This,Desktop) ) 

#define IVirtualDesktopManagerInternal2_CreateDesktop(This,Desktop) \
    ( (This)->lpVtbl -> CreateDesktop(This,Desktop) ) 

#define IVirtualDesktopManagerInternal2_RemoveDesktop(This,Remove,FallbackDesktop) \
    ( (This)->lpVtbl -> RemoveDesktop(This,Remove,FallbackDesktop) ) 

#define IVirtualDesktopManagerInternal2_FindDesktop(This,DesktopId,Desktop) \
    ( (This)->lpVtbl -> FindDesktop(This,DesktopId,Desktop) ) 

#define IVirtualDesktopManagerInternal2_GetDesktopSwitchIncludeExcludeViews(This,Desktop,_1,_2) \
    ( (This)->lpVtbl -> GetDesktopSwitchIncludeExcludeViews(This,Desktop,_1,_2) ) 

#endif /* COBJMACROS */


#endif  /* __IVirtualDesktopManagerInternal2_INTERFACE_DEFINED__ */


// 10.0.22000~10.0.22000 twinui.pcshell.dll
// CVirtualDesktopManager::CVirtualDesktopManager
//     const CVirtualDesktopManager::`vftable'
#ifndef __IVirtualDesktopManagerInternal3_INTERFACE_DEFINED__
#define __IVirtualDesktopManagerInternal3_INTERFACE_DEFINED__

/* interface IVirtualDesktopManagerInternal */
/* [object][uuid] */


// 10.0.22000~10.0.22000 = "{B2F925B9-5A0F-4D2E-9F4D-2B1507593C10}"
DEFINE_GUID(IID_IVirtualDesktopManagerInternal3, 0xB2F925B9, 0x5A0F, 0x4D2E, 0x9F, 0x4D, 0x2B, 0x15, 0x07, 0x59, 0x3C, 0x10);

#undef  INTERFACE
#define INTERFACE IVirtualDesktopManagerInternal3

DECLARE_INTERFACE_IID_(IVirtualDesktopManagerInternal3, IUnknown, "B2F925B9-5A0F-4D2E-9F4D-2B1507593C10")
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR * __RPC_FAR * ppvObject) PURE;

    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /*** IVirtualDesktopManagerInternal methods ***/
    STDMETHOD(GetCount)(THIS_
        /* [in] */  __RPC__in  HMONITOR Monitor,
        /* [out] */ __RPC__out UINT * Count) PURE;

    STDMETHOD(MoveViewToDesktop)(THIS_
        /* [in] */  __RPC__in  IApplicationView * View,
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop) PURE;

    STDMETHOD(CanViewMoveDesktops)(THIS_
        /* [in] */  __RPC__in  IApplicationView * View,
        /* [out] */ __RPC__out BOOL * Is) PURE;

    STDMETHOD(GetCurrentDesktop)(THIS_
        /* [in] */  __RPC__in  HMONITOR Monitor,
        /* [out] */ __RPC__out IVirtualDesktop * *Desktop) PURE;

    STDMETHOD(GetDesktops)(THIS_
        /* [in] */  __RPC__in  HMONITOR Monitor,
        /* [out] */ __RPC__out IObjectArray * *Desktops) PURE;

    STDMETHOD(GetAdjacentDesktop)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [in] */  __RPC__in  VIRTUAL_DESKTOP_ADJACENT_DIRECTION Direction,
        /* [out] */ __RPC__out IVirtualDesktop * *AdjacentDesktop) PURE;

    STDMETHOD(SwitchDesktop)(THIS_
        /* [in] */  __RPC__in  HMONITOR Monitor,
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop) PURE;

    STDMETHOD(CreateDesktop)(THIS_
        /* [in] */  __RPC__in  HMONITOR Monitor,
        /* [out] */ __RPC__out IVirtualDesktop * *Desktop) PURE;

    STDMETHOD(MoveDesktop)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [in] */  __RPC__in  HMONITOR Monitor,
        /* [in] */  __RPC__in  int Index) PURE;

    STDMETHOD(RemoveDesktop)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Remove,
        /* [out] */ __RPC__out IVirtualDesktop * *FallbackDesktop) PURE;

    STDMETHOD(FindDesktop)(THIS_
        /* [in] */  __RPC__in  REFGUID DesktopId,
        /* [out] */ __RPC__out IVirtualDesktop * *Desktop) PURE;

    STDMETHOD(GetDesktopSwitchIncludeExcludeViews)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [out] */ __RPC__out IObjectArray**,
        /* [out] */ __RPC__out IObjectArray**) PURE;

    STDMETHOD(SetDesktopName)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [in] */  __RPC__in  HSTRING Name) PURE;

    STDMETHOD(SetDesktopWallpaper)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [in] */  __RPC__in  HSTRING Path) PURE;

    STDMETHOD(UpdateWallpaperPathForAllDesktops)(THIS_
        /* [in] */  __RPC__in  HSTRING Path) PURE;

    STDMETHOD(CopyDesktopState)(THIS_
        /* [in] [out] */ __RPC__inout IApplicationView * DstView,
        /* [in] */  __RPC__in IApplicationView * SrcView) PURE;

    STDMETHOD(GetDesktopIsPerMonitor)(THIS_
        /* [out] */ __RPC__out BOOL * Is) PURE;

    STDMETHOD(SetDesktopIsPerMonitor)(THIS_
        /* [in] */  __RPC__in  BOOL Is) PURE;
};


#ifdef COBJMACROS

#define IVirtualDesktopManagerInternal3_QueryInterface(This,riid,ppvObject) \
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVirtualDesktopManagerInternal3_AddRef(This)    \
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVirtualDesktopManagerInternal3_Release(This)   \
    ( (This)->lpVtbl -> Release(This) ) 


#define IVirtualDesktopManagerInternal3_GetCount(This,Monitor,Count)  \
    ( (This)->lpVtbl -> GetCount(This,Monitor,Count) ) 

#define IVirtualDesktopManagerInternal3_MoveViewToDesktop(This,View,Desktop)   \
    ( (This)->lpVtbl -> MoveViewToDesktop(This,View,Desktop) ) 

#define IVirtualDesktopManagerInternal3_CanViewMoveDesktops(This,View,Is)    \
    ( (This)->lpVtbl -> CanViewMoveDesktops(This,View,Is) ) 

#define IVirtualDesktopManagerInternal3_GetCurrentDesktop(This,Monitor,Desktop)  \
    ( (This)->lpVtbl -> GetCurrentDesktop(This,Monitor,Desktop) ) 

#define IVirtualDesktopManagerInternal3_GetDesktops(This,Monitor,Desktops) \
    ( (This)->lpVtbl -> GetDesktops(This,Monitor,Desktops) ) 

#define IVirtualDesktopManagerInternal3_GetAdjacentDesktop(This,Desktop,Direction,AdjacentDesktop) \
    ( (This)->lpVtbl -> GetAdjacentDesktop(This,Desktop,Direction,AdjacentDesktop) ) 

#define IVirtualDesktopManagerInternal3_SwitchDesktop(This,Monitor,Desktop) \
    ( (This)->lpVtbl -> SwitchDesktop(This,Monitor,Desktop) ) 

#define IVirtualDesktopManagerInternal3_CreateDesktop(This,Monitor,Desktop) \
    ( (This)->lpVtbl -> CreateDesktop(This,Monitor,Desktop) ) 

#define IVirtualDesktopManagerInternal3_MoveDesktop(This,Desktop,Monitor,Index) \
    ( (This)->lpVtbl -> MoveDesktop(This,Desktop,Monitor,Index) ) 

#define IVirtualDesktopManagerInternal3_RemoveDesktop(This,Remove,FallbackDesktop) \
    ( (This)->lpVtbl -> RemoveDesktop(This,Remove,FallbackDesktop) ) 

#define IVirtualDesktopManagerInternal3_FindDesktop(This,DesktopId,Desktop) \
    ( (This)->lpVtbl -> FindDesktop(This,DesktopId,Desktop) ) 

#define IVirtualDesktopManagerInternal3_GetDesktopSwitchIncludeExcludeViews(This,Desktop,_1,_2) \
    ( (This)->lpVtbl -> GetDesktopSwitchIncludeExcludeViews(This,Desktop,_1,_2) ) 

#define IVirtualDesktopManagerInternal3_SetDesktopName(This,Desktop,Name) \
    ( (This)->lpVtbl -> SetDesktopName(This,Desktop,Name) ) 

#define IVirtualDesktopManagerInternal3_SetDesktopWallpaper(This,Desktop,Path) \
    ( (This)->lpVtbl -> SetDesktopWallpaper(This,Desktop,Path) ) 

#define IVirtualDesktopManagerInternal3_UpdateWallpaperPathForAllDesktops(This,Path) \
    ( (This)->lpVtbl -> UpdateWallpaperPathForAllDesktops(This,Path) ) 

#define IVirtualDesktopManagerInternal3_CopyDesktopState(This,DstView,SrcView) \
    ( (This)->lpVtbl -> CopyDesktopState(This,DstView,SrcView) ) 

#define IVirtualDesktopManagerInternal3_GetDesktopIsPerMonitor(This,Is) \
    ( (This)->lpVtbl -> GetDesktopIsPerMonitor(This,Is) ) 

#define IVirtualDesktopManagerInternal3_SetDesktopIsPerMonitor(This,Is) \
    ( (This)->lpVtbl -> SetDesktopIsPerMonitor(This,Is) ) 

#endif /* COBJMACROS */


#endif  /* __IVirtualDesktopManagerInternal3_INTERFACE_DEFINED__ */


// 10.0.22621~10.0.22621 twinui.pcshell.dll
// CVirtualDesktopManager::CVirtualDesktopManager
//     const CVirtualDesktopManager::`vftable'
#ifndef __IVirtualDesktopManagerInternal4_INTERFACE_DEFINED__
#define __IVirtualDesktopManagerInternal4_INTERFACE_DEFINED__

/* interface IVirtualDesktopManagerInternal */
/* [object][uuid] */


// 10.0.22621~10.0.22621 = "{B2F925B9-5A0F-4D2E-9F4D-2B1507593C10}"
DEFINE_GUID(IID_IVirtualDesktopManagerInternal4, 0xB2F925B9, 0x5A0F, 0x4D2E, 0x9F, 0x4D, 0x2B, 0x15, 0x07, 0x59, 0x3C, 0x10);

#undef  INTERFACE
#define INTERFACE IVirtualDesktopManagerInternal4

DECLARE_INTERFACE_IID_(IVirtualDesktopManagerInternal4, IUnknown, "B2F925B9-5A0F-4D2E-9F4D-2B1507593C10")
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR * __RPC_FAR * ppvObject) PURE;

    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /*** IVirtualDesktopManagerInternal methods ***/
    STDMETHOD(GetCount)(THIS_
        /* [in] */  __RPC__in  HMONITOR Monitor,
        /* [out] */ __RPC__out UINT * Count) PURE;

    STDMETHOD(MoveViewToDesktop)(THIS_
        /* [in] */  __RPC__in  IApplicationView * View,
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop) PURE;

    STDMETHOD(CanViewMoveDesktops)(THIS_
        /* [in] */  __RPC__in  IApplicationView * View,
        /* [out] */ __RPC__out BOOL * Is) PURE;

    STDMETHOD(GetCurrentDesktop)(THIS_
        /* [in] */  __RPC__in  HMONITOR Monitor,
        /* [out] */ __RPC__out IVirtualDesktop * *Desktop) PURE;

    STDMETHOD(GetAllCurrentDesktops)(THIS_
        /* [out] */ __RPC__out IObjectArray * *Desktops) PURE;

    STDMETHOD(GetDesktops)(THIS_
        /* [in] */  __RPC__in  HMONITOR Monitor,
        /* [out] */ __RPC__out IObjectArray * *Desktops) PURE;

    STDMETHOD(GetAdjacentDesktop)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [in] */  __RPC__in  VIRTUAL_DESKTOP_ADJACENT_DIRECTION Direction,
        /* [out] */ __RPC__out IVirtualDesktop * *AdjacentDesktop) PURE;

    STDMETHOD(SwitchDesktop)(THIS_
        /* [in] */  __RPC__in  HMONITOR Monitor,
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop) PURE;

    STDMETHOD(CreateDesktop)(THIS_
        /* [in] */  __RPC__in  HMONITOR Monitor,
        /* [out] */ __RPC__out IVirtualDesktop * *Desktop) PURE;

    STDMETHOD(MoveDesktop)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [in] */  __RPC__in  HMONITOR Monitor,
        /* [in] */  __RPC__in  int Index) PURE;

    STDMETHOD(RemoveDesktop)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Remove,
        /* [out] */ __RPC__out IVirtualDesktop * *FallbackDesktop) PURE;

    STDMETHOD(FindDesktop)(THIS_
        /* [in] */  __RPC__in  REFGUID DesktopId,
        /* [out] */ __RPC__out IVirtualDesktop * *Desktop) PURE;

    STDMETHOD(GetDesktopSwitchIncludeExcludeViews)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [out] */ __RPC__out IObjectArray**,
        /* [out] */ __RPC__out IObjectArray**) PURE;

    STDMETHOD(SetDesktopName)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [in] */  __RPC__in  HSTRING Name) PURE;

    STDMETHOD(SetDesktopWallpaper)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [in] */  __RPC__in  HSTRING Path) PURE;

    STDMETHOD(UpdateWallpaperPathForAllDesktops)(THIS_
        /* [in] */  __RPC__in  HSTRING Path) PURE;

    STDMETHOD(CopyDesktopState)(THIS_
        /* [in] [out] */ __RPC__inout IApplicationView * DstView,
        /* [in] */  __RPC__in IApplicationView * SrcView) PURE;

    STDMETHOD(GetDesktopIsPerMonitor)(THIS_
        /* [out] */ __RPC__out BOOL * Is) PURE;

    STDMETHOD(SetDesktopIsPerMonitor)(THIS_
        /* [in] */  __RPC__in  BOOL Is) PURE;
};


#ifdef COBJMACROS

#define IVirtualDesktopManagerInternal4_QueryInterface(This,riid,ppvObject) \
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVirtualDesktopManagerInternal4_AddRef(This)    \
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVirtualDesktopManagerInternal4_Release(This)   \
    ( (This)->lpVtbl -> Release(This) ) 


#define IVirtualDesktopManagerInternal4_GetCount(This,Monitor,Count)  \
    ( (This)->lpVtbl -> GetCount(This,Monitor,Count) ) 

#define IVirtualDesktopManagerInternal4_MoveViewToDesktop(This,View,Desktop)   \
    ( (This)->lpVtbl -> MoveViewToDesktop(This,View,Desktop) ) 

#define IVirtualDesktopManagerInternal4_CanViewMoveDesktops(This,View,Is)    \
    ( (This)->lpVtbl -> CanViewMoveDesktops(This,View,Is) ) 

#define IVirtualDesktopManagerInternal4_GetCurrentDesktop(This,Monitor,Desktop)  \
    ( (This)->lpVtbl -> GetCurrentDesktop(This,Monitor,Desktop) ) 

#define IVirtualDesktopManagerInternal4_GetAllCurrentDesktops(This,Desktops) \
    ( (This)->lpVtbl -> GetAllCurrentDesktops(This,Desktops) ) 

#define IVirtualDesktopManagerInternal4_GetDesktops(This,Monitor,Desktops) \
    ( (This)->lpVtbl -> GetDesktops(This,Monitor,Desktops) ) 

#define IVirtualDesktopManagerInternal4_GetAdjacentDesktop(This,Desktop,Direction,AdjacentDesktop) \
    ( (This)->lpVtbl -> GetAdjacentDesktop(This,Desktop,Direction,AdjacentDesktop) ) 

#define IVirtualDesktopManagerInternal4_SwitchDesktop(This,Monitor,Desktop) \
    ( (This)->lpVtbl -> SwitchDesktop(This,Monitor,Desktop) ) 

#define IVirtualDesktopManagerInternal4_CreateDesktop(This,Monitor,Desktop) \
    ( (This)->lpVtbl -> CreateDesktop(This,Monitor,Desktop) ) 

#define IVirtualDesktopManagerInternal4_MoveDesktop(This,Desktop,Monitor,Index) \
    ( (This)->lpVtbl -> MoveDesktop(This,Desktop,Monitor,Index) ) 

#define IVirtualDesktopManagerInternal4_RemoveDesktop(This,Remove,FallbackDesktop) \
    ( (This)->lpVtbl -> RemoveDesktop(This,Remove,FallbackDesktop) ) 

#define IVirtualDesktopManagerInternal4_FindDesktop(This,DesktopId,Desktop) \
    ( (This)->lpVtbl -> FindDesktop(This,DesktopId,Desktop) ) 

#define IVirtualDesktopManagerInternal4_GetDesktopSwitchIncludeExcludeViews(This,Desktop,_1,_2) \
    ( (This)->lpVtbl -> GetDesktopSwitchIncludeExcludeViews(This,Desktop,_1,_2) ) 

#define IVirtualDesktopManagerInternal4_SetDesktopName(This,Desktop,Name) \
    ( (This)->lpVtbl -> SetDesktopName(This,Desktop,Name) ) 

#define IVirtualDesktopManagerInternal4_SetDesktopWallpaper(This,Desktop,Path) \
    ( (This)->lpVtbl -> SetDesktopWallpaper(This,Desktop,Path) ) 

#define IVirtualDesktopManagerInternal4_UpdateWallpaperPathForAllDesktops(This,Path) \
    ( (This)->lpVtbl -> UpdateWallpaperPathForAllDesktops(This,Path) ) 

#define IVirtualDesktopManagerInternal4_CopyDesktopState(This,DstView,SrcView) \
    ( (This)->lpVtbl -> CopyDesktopState(This,DstView,SrcView) ) 

#define IVirtualDesktopManagerInternal4_GetDesktopIsPerMonitor(This,Is) \
    ( (This)->lpVtbl -> GetDesktopIsPerMonitor(This,Is) ) 

#define IVirtualDesktopManagerInternal4_SetDesktopIsPerMonitor(This,Is) \
    ( (This)->lpVtbl -> SetDesktopIsPerMonitor(This,Is) ) 

#endif /* COBJMACROS */


#endif  /* __IVirtualDesktopManagerInternal4_INTERFACE_DEFINED__ */


// 10.0.10240~10.0.19045 twinui.dll/twinui.pcshell.dll
// VirtualDesktop::VirtualDesktop
//     `vftable'{for `IVirtualDesktopNotification'}
#ifndef __IVirtualDesktopNotification_INTERFACE_DEFINED__
#define __IVirtualDesktopNotification_INTERFACE_DEFINED__

/* interface IVirtualDesktopNotification */
/* [object][uuid] */


// 10.0.10240~10.0.19045 = "{C179334C-4295-40D3-BEA1-C654D965605A}"
DEFINE_GUID(IID_IVirtualDesktopNotification, 0xC179334C, 0x4295, 0x40D3, 0xBE, 0xA1, 0xC6, 0x54, 0xD9, 0x65, 0x60, 0x5A);

#undef  INTERFACE
#define INTERFACE IVirtualDesktopNotification

DECLARE_INTERFACE_IID_(IVirtualDesktopNotification, IUnknown, "C179334C-4295-40D3-BEA1-C654D965605A")
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR * __RPC_FAR * ppvObject) PURE;

    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /*** IVirtualDesktopNotification methods ***/
    STDMETHOD(VirtualDesktopCreated)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop) PURE;

    STDMETHOD(VirtualDesktopDestroyBegin)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [in] */  __RPC__in  IVirtualDesktop * FallbackDesktop) PURE;

    STDMETHOD(VirtualDesktopDestroyFailed)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [in] */  __RPC__in  IVirtualDesktop * FallbackDesktop) PURE;

    STDMETHOD(VirtualDesktopDestroyed)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [in] */  __RPC__in  IVirtualDesktop * FallbackDesktop) PURE;

    STDMETHOD(ViewVirtualDesktopChanged)(THIS_
        /* [in] */  __RPC__in  IApplicationView * View) PURE;

    STDMETHOD(CurrentVirtualDesktopChanged)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * OldDesktop,
        /* [in] */  __RPC__in  IVirtualDesktop * NewDesktop) PURE;

};


#ifdef COBJMACROS

#define IVirtualDesktopNotification_QueryInterface(This,riid,ppvObject) \
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVirtualDesktopNotification_AddRef(This)    \
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVirtualDesktopNotification_Release(This)   \
    ( (This)->lpVtbl -> Release(This) ) 


#define IVirtualDesktopNotification_VirtualDesktopCreated(This,Desktop)   \
    ( (This)->lpVtbl -> VirtualDesktopCreated(This,Desktop) ) 

#define IVirtualDesktopNotification_VirtualDesktopDestroyBegin(This,Desktop,FallbackDesktop)   \
    ( (This)->lpVtbl -> VirtualDesktopDestroyBegin(This,Desktop,FallbackDesktop) ) 

#define IVirtualDesktopNotification_VirtualDesktopDestroyFailed(This,Desktop,FallbackDesktop)   \
    ( (This)->lpVtbl -> VirtualDesktopDestroyFailed(This,Desktop,FallbackDesktop) ) 

#define IVirtualDesktopNotification_VirtualDesktopDestroyed(This,Desktop,FallbackDesktop)   \
    ( (This)->lpVtbl -> VirtualDesktopDestroyed(This,Desktop,FallbackDesktop) ) 

#define IVirtualDesktopNotification_ViewVirtualDesktopChanged(This,View)   \
    ( (This)->lpVtbl -> ViewVirtualDesktopChanged(This,View) ) 

#define IVirtualDesktopNotification_CurrentVirtualDesktopChanged(This,OldDesktop,NewDesktop)   \
    ( (This)->lpVtbl -> CurrentVirtualDesktopChanged(This,OldDesktop,NewDesktop) ) 

#endif /* COBJMACROS */


#endif  /* __IVirtualDesktopNotification_INTERFACE_DEFINED__ */


// 10.0.22000~10.0.22621 twinui.pcshell.dll
// VirtualDesktop::VirtualDesktop
//     `vftable'{for `IVirtualDesktopNotification'}
#ifndef __IVirtualDesktopNotification2_INTERFACE_DEFINED__
#define __IVirtualDesktopNotification2_INTERFACE_DEFINED__

/* interface IVirtualDesktopNotification */
/* [object][uuid] */


// 10.0.22000~10.0.22621 = "{CD403E52-DEED-4C13-B437-B98380F2B1E8}"
DEFINE_GUID(IID_IVirtualDesktopNotification2, 0xCD403E52, 0xDEED, 0x4C13, 0xB4, 0x37, 0xB9, 0x83, 0x80, 0xF2, 0xB1, 0xE8);

#undef  INTERFACE
#define INTERFACE IVirtualDesktopNotification2

DECLARE_INTERFACE_IID_(IVirtualDesktopNotification2, IUnknown, "CD403E52-DEED-4C13-B437-B98380F2B1E8")
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR * __RPC_FAR * ppvObject) PURE;

    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /*** IVirtualDesktopNotification methods ***/
    STDMETHOD(VirtualDesktopCreated)(THIS_
        /* [in] */  __RPC__in  IObjectArray*,
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop) PURE;

    STDMETHOD(VirtualDesktopDestroyBegin)(THIS_
        /* [in] */  __RPC__in  IObjectArray*,
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [in] */  __RPC__in  IVirtualDesktop * FallbackDesktop) PURE;

    STDMETHOD(VirtualDesktopDestroyFailed)(THIS_
        /* [in] */  __RPC__in  IObjectArray*,
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [in] */  __RPC__in  IVirtualDesktop * FallbackDesktop) PURE;

    STDMETHOD(VirtualDesktopDestroyed)(THIS_
        /* [in] */  __RPC__in  IObjectArray*,
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [in] */  __RPC__in  IVirtualDesktop * FallbackDesktop) PURE;

    STDMETHOD(VirtualDesktopIsPerMonitorChanged)(THIS_
        /* [in] */  __RPC__in  BOOL * Is) PURE;

    STDMETHOD(VirtualDesktopMoved)(THIS_
        /* [in] */  __RPC__in  IObjectArray*,
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [in] */  __RPC__in  UINT FromIndex,
        /* [in] */  __RPC__in  UINT ToIndex) PURE;

    STDMETHOD(VirtualDesktopNameChanged)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [in] */  __RPC__in  HSTRING Name) PURE;

    STDMETHOD(ViewVirtualDesktopChanged)(THIS_
        /* [in] */  __RPC__in  IApplicationView * View) PURE;

    STDMETHOD(CurrentVirtualDesktopChanged)(THIS_
        /* [in] */  __RPC__in  IObjectArray*,
        /* [in] */  __RPC__in  IVirtualDesktop * OldDesktop,
        /* [in] */  __RPC__in  IVirtualDesktop * NewDesktop) PURE;

    STDMETHOD(VirtualDesktopWallpaperChanged)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [in] */  __RPC__in  HSTRING Path) PURE;

};


#ifdef COBJMACROS

#define IVirtualDesktopNotification2_QueryInterface(This,riid,ppvObject) \
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVirtualDesktopNotification2_AddRef(This)    \
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVirtualDesktopNotification2_Release(This)   \
    ( (This)->lpVtbl -> Release(This) ) 


#define IVirtualDesktopNotification2_VirtualDesktopCreated(This,_1,Desktop)   \
    ( (This)->lpVtbl -> VirtualDesktopCreated(This,_1,Desktop) ) 

#define IVirtualDesktopNotification2_VirtualDesktopDestroyBegin(This,_1,Desktop,FallbackDesktop)   \
    ( (This)->lpVtbl -> VirtualDesktopDestroyBegin(This,_1,Desktop,FallbackDesktop) ) 

#define IVirtualDesktopNotification2_VirtualDesktopDestroyFailed(This,_1,Desktop,FallbackDesktop)   \
    ( (This)->lpVtbl -> VirtualDesktopDestroyFailed(This,_1,Desktop,FallbackDesktop) ) 

#define IVirtualDesktopNotification2_VirtualDesktopDestroyed(This,_1,Desktop,FallbackDesktop)   \
    ( (This)->lpVtbl -> VirtualDesktopDestroyed(This,_1,Desktop,FallbackDesktop) ) 

#define IVirtualDesktopNotification2_VirtualDesktopIsPerMonitorChanged(This,Is)   \
    ( (This)->lpVtbl -> VirtualDesktopIsPerMonitorChanged(This,Is) ) 

#define IVirtualDesktopNotification2_VirtualDesktopMoved(This,_1,Desktop,FromIndex,ToIndex)   \
    ( (This)->lpVtbl -> VirtualDesktopMoved(This,_1,Desktop,FromIndex,ToIndex) ) 

#define IVirtualDesktopNotification2_VirtualDesktopNameChanged(This,Desktop,Name)   \
    ( (This)->lpVtbl -> VirtualDesktopNameChanged(This,Desktop,Name) ) 

#define IVirtualDesktopNotification2_ViewVirtualDesktopChanged(This,View)   \
    ( (This)->lpVtbl -> ViewVirtualDesktopChanged(This,View) ) 

#define IVirtualDesktopNotification2_CurrentVirtualDesktopChanged(This,_1,OldDesktop,NewDesktop)   \
    ( (This)->lpVtbl -> CurrentVirtualDesktopChanged(This,_1,OldDesktop,NewDesktop) ) 

#define IVirtualDesktopNotification2_VirtualDesktopWallpaperChanged(This,Desktop,Path)   \
    ( (This)->lpVtbl -> VirtualDesktopWallpaperChanged(This,Desktop,Path) ) 

#endif /* COBJMACROS */


#endif  /* __IVirtualDesktopNotification2_INTERFACE_DEFINED__ */


// 10.0.10240~10.0.22621 twinui.dll/twinui.pcshell.dll
// CVirtualDesktopNotifications::Register(struct IVirtualDesktopNotification *, unsigned long *)
//     const Microsoft::WRL::RuntimeClass<..., class VirtualDesktopNotificationForwarderHelper<class CVirtualDesktopNotifications>>::`vftable'
#ifndef __IVirtualDesktopNotificationService_INTERFACE_DEFINED__
#define __IVirtualDesktopNotificationService_INTERFACE_DEFINED__

/* interface IVirtualDesktopNotificationService */
/* [object][uuid] */


// 10.0.10240~10.0.22621 = "{0CD45E71-D927-4F15-8B0A-8FEF525337BF}"
DEFINE_GUID(IID_IVirtualDesktopNotificationService, 0x0CD45E71, 0xD927, 0x4F15, 0x8B, 0x0A, 0x8F, 0xEF, 0x52, 0x53, 0x37, 0xBF);

#undef  INTERFACE
#define INTERFACE IVirtualDesktopNotificationService

DECLARE_INTERFACE_IID_(IVirtualDesktopNotificationService, IUnknown, "0CD45E71-D927-4F15-8B0A-8FEF525337BF")
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR * __RPC_FAR * ppvObject) PURE;

    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /*** IVirtualDesktopNotificationService methods ***/
    STDMETHOD(Register)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktopNotification * Notification,
        /* [out] */ __RPC__out ULONG * Cookie) PURE;

    STDMETHOD(Unregister)(THIS_
        /* [out] */ __RPC__out ULONG Cookie) PURE;

};


#ifdef COBJMACROS

#define IVirtualDesktopNotificationService_QueryInterface(This,riid,ppvObject) \
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVirtualDesktopNotificationService_AddRef(This)    \
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVirtualDesktopNotificationService_Release(This)   \
    ( (This)->lpVtbl -> Release(This) ) 


#define IVirtualDesktopNotificationService_Register(This,Notification,Cookie)  \
    ( (This)->lpVtbl -> Register(This,Notification,Cookie) ) 

#define IVirtualDesktopNotificationService_Unregister(This,Cookie)   \
    ( (This)->lpVtbl -> Unregister(This,Cookie) ) 

#endif /* COBJMACROS */


#endif  /* __IVirtualDesktopNotificationService_INTERFACE_DEFINED__ */


// 10.0.14393~10.0.22621 twinui.pcshell.dll
// VirtualPinnedAppsHandler::VirtualPinnedAppsHandler
//     const VirtualPinnedAppsHandler::`vftable'{for `Microsoft::WRL::ChainInterfaces<..., struct IVirtualDesktopPinnedApps, ...
#ifndef __IVirtualDesktopPinnedApps_INTERFACE_DEFINED__
#define __IVirtualDesktopPinnedApps_INTERFACE_DEFINED__

/* interface IVirtualDesktopPinnedApps */
/* [object][uuid] */


// 10.0.14393~10.0.22621 = "{4CE81583-1E4C-4632-A621-07A53543148F}"
DEFINE_GUID(IID_IVirtualDesktopPinnedApps, 0x4CE81583, 0x1E4C, 0x4632, 0xA6, 0x21, 0x07, 0xA5, 0x35, 0x43, 0x14, 0x8F);

#undef  INTERFACE
#define INTERFACE IVirtualDesktopPinnedApps

DECLARE_INTERFACE_IID_(IVirtualDesktopPinnedApps, IUnknown, "4CE81583-1E4C-4632-A621-07A53543148F")
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR * __RPC_FAR * ppvObject) PURE;

    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /*** IVirtualDesktopPinnedApps methods ***/
    STDMETHOD(IsAppIdPinned)(THIS_
        /* [in] */  __RPC__in  PCWSTR AppId,
        /* [out] */ __RPC__out BOOL * IsPinned) PURE;

    STDMETHOD(PinAppID)(THIS_
        /* [in] */  __RPC__in  PCWSTR AppId) PURE;

    STDMETHOD(UnpinAppID)(THIS_
        /* [in] */  __RPC__in  PCWSTR AppId) PURE;

    STDMETHOD(IsViewPinned)(THIS_
        /* [in] */  __RPC__in  IApplicationView * View,
        /* [out] */ __RPC__out BOOL * IsPinned) PURE;

    STDMETHOD(PinView)(THIS_
        /* [in] */  __RPC__in  IApplicationView * View) PURE;

    STDMETHOD(UnpinView)(THIS_
        /* [in] */  __RPC__in  IApplicationView * View) PURE;

};


#ifdef COBJMACROS

#define IVirtualDesktopPinnedApps_QueryInterface(This,riid,ppvObject) \
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVirtualDesktopPinnedApps_AddRef(This)    \
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVirtualDesktopPinnedApps_Release(This)   \
    ( (This)->lpVtbl -> Release(This) ) 


#define IVirtualDesktopPinnedApps_IsAppIdPinned(This,AppId,IsPinned)   \
    ( (This)->lpVtbl -> IsAppIdPinned(This,AppId,IsPinned) ) 

#define IVirtualDesktopPinnedApps_PinAppID(This,AppId)   \
    ( (This)->lpVtbl -> PinAppID(This,AppId) ) 

#define IVirtualDesktopPinnedApps_UnpinAppID(This,AppId)   \
    ( (This)->lpVtbl -> UnpinAppID(This,AppId) ) 

#define IVirtualDesktopPinnedApps_IsViewPinned(This,View,IsPinned)   \
    ( (This)->lpVtbl -> IsViewPinned(This,View,IsPinned) ) 

#define IVirtualDesktopPinnedApps_PinView(This,View)   \
    ( (This)->lpVtbl -> PinView(This,View) ) 

#define IVirtualDesktopPinnedApps_UnpinView(This,View)   \
    ( (This)->lpVtbl -> UnpinView(This,View) ) 

#endif /* COBJMACROS */


#endif  /* __IVirtualDesktopPinnedApps_INTERFACE_DEFINED__ */


#endif // !_KERNEL_MODE && (NTDDI_VERSION >= NTDDI_WIN10)

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
