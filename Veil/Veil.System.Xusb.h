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
// nonstandard extension used : bit field other than int
#pragma warning(disable:4214)
// 'struct_name' : structure was padded due to __declspec(align())
#pragma warning(disable:4324)
// 'enumeration': a forward declaration of an unscoped enumeration must have an
// underlying type (int assumed)
#pragma warning(disable:4471)
#endif

VEIL_BEGIN()

#if !defined(_KERNEL_MODE)

#include <xinput.h>

#define ORDINAL_XInputGetStateEx                ((LPCSTR)100)
#define ORDINAL_XInputWaitForGuideButton        ((LPCSTR)101)
#define ORDINAL_XInputCancelGuideButtonWait     ((LPCSTR)102)
#define ORDINAL_XInputPowerOffController        ((LPCSTR)103)
#define ORDINAL_XInputGetBaseBusInformation     ((LPCSTR)104)
#define ORDINAL_XInputGetCapabilitiesEx         ((LPCSTR)108)

VEIL_DECLARE_STRUCT(XINPUT_BASE_BUS_INFORMATION)
{
    WORD  VendorId;
    WORD  ProductId;
    WORD  RevisionId; // 1.1.4 That is encoded as a binary coded decimal (bcd).
    DWORD Unknown[2];
};

VEIL_DECLARE_STRUCT(XINPUT_CAPABILITIES_EX)
{
    XINPUT_CAPABILITIES Capabilities;
    XINPUT_BASE_BUS_INFORMATION BaseBusInformation;
};

#endif // !defined(_KERNEL_MODE)

//
// xusb22.sys!IOCTLs
//

#define FILE_DEVICE_XUSB        0x8000
#define IOCTL_XUSB_INDEX_BASE   0x0800

#define IOCTL_XUSB_GET_INFORMATION              /*0x80006000*/ CTL_CODE(FILE_DEVICE_XUSB, IOCTL_XUSB_INDEX_BASE + 0,    METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_XUSB_GET_CAPABILITIES             /*0x8000E004*/ CTL_CODE(FILE_DEVICE_XUSB, IOCTL_XUSB_INDEX_BASE + 1,    METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_XUSB_GET_LED_STATE                /*0x8000E008*/ CTL_CODE(FILE_DEVICE_XUSB, IOCTL_XUSB_INDEX_BASE + 2,    METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_XUSB_GET_STATE                    /*0x8000E00C*/ CTL_CODE(FILE_DEVICE_XUSB, IOCTL_XUSB_INDEX_BASE + 3,    METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_XUSB_SET_STATE                    /*0x8000A010*/ CTL_CODE(FILE_DEVICE_XUSB, IOCTL_XUSB_INDEX_BASE + 4,    METHOD_BUFFERED, FILE_WRITE_ACCESS)
#define IOCTL_XUSB_WAIT_GUIDE_BUTTON            /*0x8000E014*/ CTL_CODE(FILE_DEVICE_XUSB, IOCTL_XUSB_INDEX_BASE + 5,    METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_XUSB_GET_BATTERY_INFORMATION      /*0x8000E018*/ CTL_CODE(FILE_DEVICE_XUSB, IOCTL_XUSB_INDEX_BASE + 6,    METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_XUSB_POWER_OFF                    /*0x8000A01C*/ CTL_CODE(FILE_DEVICE_XUSB, IOCTL_XUSB_INDEX_BASE + 7,    METHOD_BUFFERED, FILE_WRITE_ACCESS)
#define IOCTL_XUSB_GET_AUDIO_DEVICE_INFORMATION /*0x8000E020*/ CTL_CODE(FILE_DEVICE_XUSB, IOCTL_XUSB_INDEX_BASE + 8,    METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_XUSB_GET_MANAGER_DRIVER           /*0x80006380*/ CTL_CODE(FILE_DEVICE_XUSB, IOCTL_XUSB_INDEX_BASE + 0xE0, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_XUSB_WAIT_FOR_INPUT               /*0x8000E3AC*/ CTL_CODE(FILE_DEVICE_XUSB, IOCTL_XUSB_INDEX_BASE + 0xEB, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_XUSB_GET_INFORMATION_EX           /*0x8000E3FC*/ CTL_CODE(FILE_DEVICE_XUSB, IOCTL_XUSB_INDEX_BASE + 0xFF, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)

#define XUSB_VERSION_1_0 ((UINT16)0x0100)
#define XUSB_VERSION_1_1 ((UINT16)0x0101)
#define XUSB_VERSION_1_2 ((UINT16)0x0102)
#define XUSB_VERSION_1_3 ((UINT16)0x0103)
#define XUSB_VERSION_1_4 ((UINT16)0x0104)

#define XUSB_VERSION     XUSB_VERSION_1_4


#include <pshpack1.h>

VEIL_DECLARE_STRUCT(XUSB_GET_INFORMATION)
{
    UINT16 Version;
    UINT8  DeviceIndex; // Child device index of bus driver
};

#include <poppack.h>

VEIL_END()

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
