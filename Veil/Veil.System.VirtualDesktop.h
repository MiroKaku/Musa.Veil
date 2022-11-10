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

#define COBJMACROS

#if !defined(_KERNEL_MODE) && (NTDDI_VERSION >= NTDDI_WIN10)

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
//   IDA: Search for "for `IVirtualDesktop'" in the name window.


// CLSID_ImmersiveShell = {C2F03A33-21F5-47FA-B4BB-156362A2F239}
DEFINE_GUID(CLSID_ImmersiveShell, 0xC2F03A33, 0x21F5, 0x47FA, 0xB4, 0xBB, 0x15, 0x63, 0x62, 0xA2, 0xF2, 0x39);

// CLSID_VirtualDesktopManager = {AA509086-5CA9-4C25-8F95-589D3C07B48A}
//DEFINE_GUID(CLSID_VirtualDesktopManager, 0xAA509086, 0x5CA9, 0x4C25, 0x8F, 0x95, 0x58, 0x9D, 0x3C, 0x07, 0xB4, 0x8A);

// 10.0.22000 twinui.pcshell.dll!SID_VirtualDesktopManager = {C5E0CDCA-7B6E-41B2-9FC4-D93975CC467B}
DEFINE_GUID(CLSID_VirtualDesktopManagerInternal, 0xC5E0CDCA, 0x7B6E, 0x41B2, 0x9F, 0xC4, 0xD9, 0x39, 0x75, 0xCC, 0x46, 0x7B);

// 10.0.22000 twinui.pcshell.dll!SID_VirtualDesktopPinnedApps = {B5A399E7-1C87-46B8-88E9-FC5747B171BD}
DEFINE_GUID(CLSID_VirtualDesktopPinnedApps, 0xB5A399E7, 0x1C87, 0x46B8, 0x88, 0xE9, 0xFC, 0x57, 0x47, 0xB1, 0x71, 0xBD);

// 10.0.22000 twinui.pcshell.dll!SID_VirtualNotificationService = {A501FDEC-4A09-464C-AE4E-1B9C21B84918}
DEFINE_GUID(CLSID_VirtualNotificationService, 0xA501FDEC, 0x4A09, 0x464C, 0xAE, 0x4E, 0x1B, 0x9C, 0x21, 0xB8, 0x49, 0x18);


// Ignore following API's:
typedef IUnknown IImmersiveApplication;
typedef IUnknown IClassicWindowExternal;
typedef IUnknown IApplicationViewChangeListener;


// CWinRTApplicationView::CWinRTApplicationView
//     const CWinRTApplicationView::`vftable'{for `IApplicationView'}

#ifndef __IApplicationView_INTERFACE_DEFINED__
#define __IApplicationView_INTERFACE_DEFINED__

enum APPLICATION_VIEW_CLOAK_TYPE
{
    AVCT_NONE = 0,
    AVCT_DEFAULT = 1,
    AVCT_VIRTUAL_DESKTOP = 2
};

enum APPLICATION_VIEW_COMPATIBILITY_POLICY
{
    AVCP_NONE = 0,
    AVCP_SMALL_SCREEN = 1,
    AVCP_TABLET_SMALL_SCREEN = 2,
    AVCP_VERY_SMALL_SCREEN = 3,
    AVCP_HIGH_SCALE_FACTOR = 4
};

/* interface IApplicationView */
/* [object][uuid] */


DEFINE_GUID(IID_IApplicationView, 0x372E1D3B, 0x38D3, 0x42E4, 0xA1, 0x5B, 0x8A, 0xB2, 0xB1, 0x78, 0xF5, 0x13);

DECLARE_INTERFACE_IID_(IApplicationView, IInspectable, "372E1D3B-38D3-42E4-A15B-8AB2B178F513")
{
    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_
        /* [in] */ REFIID riid,
        /* [iid_is][out] */ _COM_Outptr_ void __RPC_FAR * __RPC_FAR * ppvObject) PURE;

    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /*** IInspectable methods ***/
    STDMETHOD(GetIids)(THIS_
        /* [out] */ __RPC__out ULONG * iidCount,
        /* [size_is][size_is][out] */ __RPC__deref_out_ecount_full_opt(*iidCount) IID * *iids) PURE;

    STDMETHOD(GetRuntimeClassName)(THIS_
        /* [out] */ __RPC__deref_out_opt HSTRING * className) PURE;

    STDMETHOD(GetTrustLevel)(THIS_
        /* [out] */ __RPC__out TrustLevel * trustLevel) PURE;

    /*** IApplicationView methods ***/
    STDMETHOD(SetFocus)(THIS) PURE;
    STDMETHOD(SwitchTo)(THIS) PURE;

    // ...
};


#ifdef COBJMACROS

#define IApplicationView_QueryInterface(This,riid,ppvObject) \
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IApplicationView_AddRef(This)    \
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IApplicationView_Release(This)   \
    ( (This)->lpVtbl -> Release(This) ) 


#define IApplicationView_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define IApplicationView_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define IApplicationView_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define IApplicationView_SetFocus(This)   \
    ( (This)->lpVtbl -> SetFocus(This) ) 

#define IApplicationView_SwitchTo(This)   \
    ( (This)->lpVtbl -> SwitchTo(This) ) 

#endif /* COBJMACROS */


#endif /* __IApplicationView_INTERFACE_DEFINED__ */


// CApplicationViewManager::CApplicationViewManager
//     const CApplicationViewManager::`vftable'{for `IApplicationViewCollection`}

#ifndef __IApplicationViewCollection_INTERFACE_DEFINED__
#define __IApplicationViewCollection_INTERFACE_DEFINED__

/* interface IApplicationViewCollection */
/* [object][uuid] */


DEFINE_GUID(IID_IApplicationViewCollection, 0x1841C6D7, 0x4F9D, 0x42C0, 0xAF, 0x41, 0x87, 0x47, 0x53, 0x8F, 0x10, 0xE5);

DECLARE_INTERFACE_IID_(IApplicationViewCollection, IUnknown, "1841C6D7-4F9D-42C0-AF41-8747538F10E5")
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
        /* [out] */ __RPC__out DWORD Cookie) PURE;

    STDMETHOD(UnregisterForApplicationViewChanges)(THIS_
        /* [in] */  __RPC__in  DWORD Cookie) PURE;

    // ...
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

#define IIApplicationViewCollection_TryGetLastActiveVisibleView(This,View) \
    ( (This)->lpVtbl -> TryGetLastActiveVisibleView(This,View) ) 

#define IIApplicationViewCollection_RefreshCollection(This) \
    ( (This)->lpVtbl -> RefreshCollection(This) ) 

#define IIApplicationViewCollection_RegisterForApplicationViewChanges(This,Listener,Cookie) \
    ( (This)->lpVtbl -> RegisterForApplicationViewChanges(This,Listener,Cookie) ) 

#define IIApplicationViewCollection_UnregisterForApplicationViewChanges(This,Cookie) \
    ( (This)->lpVtbl -> UnregisterForApplicationViewChanges(This,Cookie) ) 

#endif /* COBJMACROS */


#endif /* __IApplicationViewCollection_INTERFACE_DEFINED__ */


// CVirtualDesktop::CVirtualDesktop
//     const CVirtualDesktop::`vftable'{for `IVirtualDesktop'}

#ifndef __IVirtualDesktop_INTERFACE_DEFINED__
#define __IVirtualDesktop_INTERFACE_DEFINED__

/* interface IVirtualDesktop */
/* [object][uuid] */


DEFINE_GUID(IID_IVirtualDesktop, 0x536D3495, 0xB208, 0x4CC9, 0xAE, 0x26, 0xDE, 0x81, 0x11, 0x27, 0x5B, 0xF8);

DECLARE_INTERFACE_IID_(IVirtualDesktop, IUnknown, "536D3495-B208-4CC9-AE26-DE8111275BF8")
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

#define IVirtualDesktop_GetMonitor(This,Monitor)    \
    ( (This)->lpVtbl -> GetMonitor(This,Monitor) ) 

#define IVirtualDesktop_GetName(This,Name)  \
    ( (This)->lpVtbl -> GetName(This,Name) ) 

#define IVirtualDesktop_GetWallpaper(This,Path) \
    ( (This)->lpVtbl -> GetWallpaper(This,Path) ) 

#endif /* COBJMACROS */


#endif  /* __IVirtualDesktop_INTERFACE_DEFINED__ */


// CApplicationViewManager::CApplicationViewManager
//     const CApplicationViewManager::`vftable'{for `IVirtualDesktopManagerInternal'}

#ifndef __IVirtualDesktopManagerInternal_INTERFACE_DEFINED__
#define __IVirtualDesktopManagerInternal_INTERFACE_DEFINED__

enum AdjacentDirection
{
    AdjacentDirection_Left  = 3,
    AdjacentDirection_Right = 4
};

/* interface IVirtualDesktopManagerInternal */
/* [object][uuid] */


DEFINE_GUID(IID_IVirtualDesktopManagerInternal, 0xb2f925b9, 0x5a0f, 0x4d2e, 0x9f, 0x4d, 0x2b, 0x15, 0x07, 0x59, 0x3c, 0x10);

DECLARE_INTERFACE_IID_(IVirtualDesktopManagerInternal, IUnknown, "B2F925B9-5A0F-4D2E-9F4D-2B1507593C10")
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
        /* [in] */  __RPC__in  IApplicationView* View,
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop) PURE;

    STDMETHOD(CanViewMoveDesktops)(THIS_
        /* [in] */  __RPC__in  IApplicationView* View,
        /* [out] */ __RPC__out BOOL* Is) PURE;

    STDMETHOD(GetCurrentDesktop)(THIS_
        /* [in] */  __RPC__in  HMONITOR Monitor,
        /* [out] */ __RPC__out IVirtualDesktop * *Desktop) PURE;

    STDMETHOD(GetDesktops)(THIS_
        /* [in] */  __RPC__in  HMONITOR Monitor,
        /* [out] */ __RPC__out IObjectArray * *Desktops) PURE;

    STDMETHOD(GetAdjacentDesktop)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop* Desktop,
        /* [in] */  __RPC__in  AdjacentDirection Direction,
        /* [out] */ __RPC__out IVirtualDesktop * * AdjacentDesktop) PURE;

    STDMETHOD(SwitchDesktop)(THIS_
        /* [in] */  __RPC__in  HMONITOR Monitor,
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop) PURE;

    STDMETHOD(CreateDesktop)(THIS_
        /* [in] */  __RPC__in  HMONITOR Monitor,
        /* [out] */ __RPC__out IVirtualDesktop * * Desktop) PURE;

    STDMETHOD(MoveDesktop)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [in] */  __RPC__in  HMONITOR Monitor,
        /* [in] */  __RPC__in  int Index) PURE;

    STDMETHOD(RemoveDesktop)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Remove,
        /* [out] */ __RPC__out IVirtualDesktop * * FallbackDesktop) PURE;

    STDMETHOD(FindDesktop)(THIS_
        /* [in] */  __RPC__in  REFGUID DesktopId,
        /* [out] */ __RPC__out IVirtualDesktop * *Desktop) PURE;

    STDMETHOD(GetDesktopSwitchIncludeExcludeViews)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop* Desktop,
        /* [out] */ __RPC__out IObjectArray**,
        /* [out] */ __RPC__out IObjectArray**) PURE;

    STDMETHOD(SetDesktopName)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop* Desktop,
        /* [in] */  __RPC__in  HSTRING Name) PURE;

    STDMETHOD(SetDesktopWallpaper)(THIS_
        /* [in] */  __RPC__in  IVirtualDesktop * Desktop,
        /* [in] */  __RPC__in  HSTRING Path) PURE;

    STDMETHOD(UpdateWallpaperPathForAllDesktops)(THIS_
        /* [in] */  __RPC__in  HSTRING Path) PURE;

    STDMETHOD(CopyDesktopState)(THIS_
        /* [in] [out] */ __RPC__inout IApplicationView* DstView,
        /* [in] */  __RPC__in IApplicationView* SrcView) PURE;

    STDMETHOD(GetDesktopIsPerMonitor)(THIS_
        /* [out] */ __RPC__out BOOL* Is) PURE;

    STDMETHOD(SetDesktopIsPerMonitor)(THIS_
        /* [in] */  __RPC__in  BOOL Is) PURE;
};


#ifdef COBJMACROS

#define IVirtualDesktopManagerInternal_QueryInterface(This,riid,ppvObject) \
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVirtualDesktopManagerInternal_AddRef(This)    \
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVirtualDesktopManagerInternal_Release(This)   \
    ( (This)->lpVtbl -> Release(This) ) 


#define IVirtualDesktopManagerInternal_GetCount(This,Monitor,Count)  \
    ( (This)->lpVtbl -> GetCount(This,Monitor,Count) ) 

#define IVirtualDesktopManagerInternal_MoveViewToDesktop(This,View,Desktop)   \
    ( (This)->lpVtbl -> MoveViewToDesktop(This,View,Desktop) ) 

#define IVirtualDesktopManagerInternal_CanViewMoveDesktops(This,View,Is)    \
    ( (This)->lpVtbl -> CanViewMoveDesktops(This,View,Is) ) 

#define IVirtualDesktopManagerInternal_GetCurrentDesktop(This,Monitor,Desktop)  \
    ( (This)->lpVtbl -> GetCurrentDesktop(This,Monitor,Desktop) ) 

#define IVirtualDesktopManagerInternal_GetDesktops(This,Monitor,Desktops) \
    ( (This)->lpVtbl -> GetDesktops(This,Monitor,Desktops) ) 

#define IVirtualDesktopManagerInternal_GetAdjacentDesktop(This,Desktop,Direction,AdjacentDesktop) \
    ( (This)->lpVtbl -> GetAdjacentDesktop(This,Desktop,Direction,AdjacentDesktop) ) 

#define IVirtualDesktopManagerInternal_SwitchDesktop(This,Monitor,Desktop) \
    ( (This)->lpVtbl -> SwitchDesktop(This,Monitor,Desktop) ) 

#define IVirtualDesktopManagerInternal_CreateDesktop(This,Monitor,Desktop) \
    ( (This)->lpVtbl -> CreateDesktop(This,Monitor,Desktop) ) 

#define IVirtualDesktopManagerInternal_MoveDesktop(This,Desktop,Monitor,Index) \
    ( (This)->lpVtbl -> MoveDesktop(This,Desktop,Monitor,Index) ) 

#define IVirtualDesktopManagerInternal_RemoveDesktop(This,Remove,FallbackDesktop) \
    ( (This)->lpVtbl -> RemoveDesktop(This,Remove,FallbackDesktop) ) 

#define IVirtualDesktopManagerInternal_FindDesktop(This,DesktopId,Desktop) \
    ( (This)->lpVtbl -> FindDesktop(This,DesktopId,Desktop) ) 

#define IVirtualDesktopManagerInternal_GetDesktopSwitchIncludeExcludeViews(This,Desktop,_1,_2) \
    ( (This)->lpVtbl -> GetDesktopSwitchIncludeExcludeViews(This,Desktop,_1,_2) ) 

#define IVirtualDesktopManagerInternal_SetDesktopName(This,Desktop,Name) \
    ( (This)->lpVtbl -> SetDesktopName(This,Desktop,Name) ) 

#define IVirtualDesktopManagerInternal_SetDesktopWallpaper(This,Desktop,Path) \
    ( (This)->lpVtbl -> SetDesktopWallpaper(This,Desktop,Path) ) 

#define IVirtualDesktopManagerInternal_UpdateWallpaperPathForAllDesktops(This,Path) \
    ( (This)->lpVtbl -> UpdateWallpaperPathForAllDesktops(This,Path) ) 

#define IVirtualDesktopManagerInternal_CopyDesktopState(This,DstView,SrcView) \
    ( (This)->lpVtbl -> CopyDesktopState(This,DstView,SrcView) ) 

#define IVirtualDesktopManagerInternal_GetDesktopIsPerMonitor(This,Is) \
    ( (This)->lpVtbl -> GetDesktopIsPerMonitor(This,Is) ) 

#define IVirtualDesktopManagerInternal_SetDesktopIsPerMonitor(This,Is) \
    ( (This)->lpVtbl -> SetDesktopIsPerMonitor(This,Is) ) 

#endif /* COBJMACROS */


#endif  /* __IVirtualDesktopManagerInternal_INTERFACE_DEFINED__ */


// VirtualPinnedAppsHandler::VirtualPinnedAppsHandler
//     const VirtualPinnedAppsHandler::`vftable'{for `IVirtualDesktopPinnedApps`}

#ifndef __IVirtualDesktopPinnedApps_INTERFACE_DEFINED__
#define __IVirtualDesktopPinnedApps_INTERFACE_DEFINED__

/* interface IVirtualDesktopPinnedApps */
/* [object][uuid] */


DEFINE_GUID(IID_IVirtualDesktopPinnedApps, 0x4CE81583, 0x1E4C, 0x4632, 0xA6, 0x21, 0x07, 0xA5, 0x35, 0x43, 0x14, 0x8F);

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
        /* [out] */ __RPC__out BOOL* IsPinned) PURE;

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


// VirtualDesktop::VirtualDesktop
//     const VirtualDesktopNotificationBase<IVirtualDesktopNotification>::`vftable'

#ifndef __IVirtualDesktopNotification_INTERFACE_DEFINED__
#define __IVirtualDesktopNotification_INTERFACE_DEFINED__

/* interface IVirtualDesktopNotification */
/* [object][uuid] */


DEFINE_GUID(IID_IVirtualDesktopNotification, 0xCD403E52, 0xDEED, 0x4C13, 0xB4, 0x37, 0xB9, 0x83, 0x80, 0xF2, 0xB1, 0xE8);

DECLARE_INTERFACE_IID_(IVirtualDesktopNotification, IUnknown, "CD403E52-DEED-4C13-B437-B98380F2B1E8")
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

#define IVirtualDesktopNotification_QueryInterface(This,riid,ppvObject) \
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVirtualDesktopNotification_AddRef(This)    \
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVirtualDesktopNotification_Release(This)   \
    ( (This)->lpVtbl -> Release(This) ) 


#define IVirtualDesktopNotification_VirtualDesktopCreated(This,_1,Desktop)   \
    ( (This)->lpVtbl -> VirtualDesktopCreated(This,_1,Desktop) ) 

#define IVirtualDesktopNotification_VirtualDesktopDestroyBegin(This,_1,Desktop,FallbackDesktop)   \
    ( (This)->lpVtbl -> VirtualDesktopDestroyBegin(This,_1,Desktop,FallbackDesktop) ) 

#define IVirtualDesktopNotification_VirtualDesktopDestroyFailed(This,_1,Desktop,FallbackDesktop)   \
    ( (This)->lpVtbl -> VirtualDesktopDestroyFailed(This,_1,Desktop,FallbackDesktop) ) 

#define IVirtualDesktopNotification_VirtualDesktopDestroyed(This,_1,Desktop,FallbackDesktop)   \
    ( (This)->lpVtbl -> VirtualDesktopDestroyed(This,_1,Desktop,FallbackDesktop) ) 

#define IVirtualDesktopNotification_VirtualDesktopIsPerMonitorChanged(This,Is)   \
    ( (This)->lpVtbl -> VirtualDesktopIsPerMonitorChanged(This,Is) ) 

#define IVirtualDesktopNotification_VirtualDesktopMoved(This,_1,Desktop,FromIndex,ToIndex)   \
    ( (This)->lpVtbl -> VirtualDesktopMoved(This,_1,Desktop,FromIndex,ToIndex) ) 

#define IVirtualDesktopNotification_VirtualDesktopNameChanged(This,Desktop,Name)   \
    ( (This)->lpVtbl -> VirtualDesktopNameChanged(This,Desktop,Name) ) 

#define IVirtualDesktopNotification_ViewVirtualDesktopChanged(This,View)   \
    ( (This)->lpVtbl -> ViewVirtualDesktopChanged(This,View) ) 

#define IVirtualDesktopNotification_CurrentVirtualDesktopChanged(This,_1,OldDesktop,NewDesktop)   \
    ( (This)->lpVtbl -> CurrentVirtualDesktopChanged(This,_1,OldDesktop,NewDesktop) ) 

#define IVirtualDesktopNotification_VirtualDesktopWallpaperChanged(This,Desktop,Path)   \
    ( (This)->lpVtbl -> VirtualDesktopWallpaperChanged(This,Desktop,Path) ) 


#endif /* COBJMACROS */


#endif  /* __IVirtualDesktopNotification_INTERFACE_DEFINED__ */


// CVirtualDesktopNotifications::Register(struct IVirtualDesktopNotification *, unsigned long *)
//     

#ifndef __IVirtualDesktopNotificationService_INTERFACE_DEFINED__
#define __IVirtualDesktopNotificationService_INTERFACE_DEFINED__

/* interface IVirtualDesktopNotificationService */
/* [object][uuid] */


DEFINE_GUID(IID_IVirtualDesktopNotificationService, 0x0CD45E71, 0xD927, 0x4F15, 0x8B, 0x0A, 0x8F, 0xEF, 0x52, 0x53, 0x37, 0xBF);

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
        /* [in] */  __RPC__in  IVirtualDesktopNotification* Notification,
        /* [out] */ __RPC__out ULONG * Cookie) PURE;

    STDMETHOD(Unregister)(THIS_
        /* [out] */ __RPC__out ULONG Cookie) PURE;

};


#ifdef COBJMACROS

#define IVirtualDesktop_QueryInterface(This,riid,ppvObject) \
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IVirtualDesktop_AddRef(This)    \
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IVirtualDesktop_Release(This)   \
    ( (This)->lpVtbl -> Release(This) ) 


#define IVirtualDesktopNotificationService_Register(This,Notification,Cookie)  \
    ( (This)->lpVtbl -> Register(This,Notification,Cookie) ) 

#define IVirtualDesktopNotificationService_Unregister(This,Cookie)   \
    ( (This)->lpVtbl -> Unregister(This,Cookie) ) 


#endif /* COBJMACROS */


#endif  /* __IVirtualDesktopNotificationService_INTERFACE_DEFINED__ */



#endif // !_KERNEL_MODE && (NTDDI_VERSION >= NTDDI_WIN10)

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
