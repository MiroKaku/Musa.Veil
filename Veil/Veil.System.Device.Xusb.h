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

#include <usbspec.h>

#if !defined(_KERNEL_MODE)

#include <xinput.h>

// Key layout
// https://support.xbox.com/en-SG/help/hardware-network/controller/xbox-one-wireless-controller

#ifndef XINPUT_GAMEPAD_GUIDE
#define XINPUT_GAMEPAD_GUIDE 0x0400 /*Xbox button (5)*/
#endif

#define XINPUT_BUTTON_MASK_WITHOUT_GUIDE ( \
        XINPUT_GAMEPAD_A             | XINPUT_GAMEPAD_B              | XINPUT_GAMEPAD_X         | XINPUT_GAMEPAD_Y | \
        XINPUT_GAMEPAD_DPAD_UP       | XINPUT_GAMEPAD_DPAD_DOWN      | XINPUT_GAMEPAD_DPAD_LEFT | XINPUT_GAMEPAD_DPAD_RIGHT | \
        XINPUT_GAMEPAD_START         | XINPUT_GAMEPAD_BACK           | \
        XINPUT_GAMEPAD_LEFT_THUMB    | XINPUT_GAMEPAD_RIGHT_THUMB    | \
        XINPUT_GAMEPAD_LEFT_SHOULDER | XINPUT_GAMEPAD_RIGHT_SHOULDER \
    )

#define XINPUT_BUTTON_MASK  (XINPUT_BUTTON_MASK_WITHOUT_GUIDE | XINPUT_GAMEPAD_GUIDE)

VEIL_DECLARE_STRUCT(XINPUT_BASE_BUS_INFORMATION)
{
    WORD  VendorId;
    WORD  ProductId;
    WORD  RevisionId;   // 1.1.4 That is encoded as a binary coded decimal (bcd).
    DWORD Unknown1;
    DWORD Reserved;
};
C_ASSERT(sizeof(XINPUT_BASE_BUS_INFORMATION) == 16);

VEIL_DECLARE_STRUCT(XINPUT_CAPABILITIES_EX)
{
    XINPUT_CAPABILITIES Capabilities;
    XINPUT_BASE_BUS_INFORMATION BaseBusInformation;
};
C_ASSERT(sizeof(XINPUT_CAPABILITIES_EX) == 36);

VEIL_DECLARE_STRUCT(XINPUT_LISTEN_STATE)
{
    DWORD Status;
    XINPUT_STATE State;
};
C_ASSERT(sizeof(XINPUT_LISTEN_STATE) == 20);

VEIL_DECLARE_STRUCT(XINPUT_STATE_EX)
{
    XINPUT_STATE State;
    DWORD ExtraButtons;
};
C_ASSERT(sizeof(XINPUT_STATE_EX) == 20);

#define ORDINAL_XInputGetStateEx                ((LPCSTR)100)
#define ORDINAL_XInputWaitForGuideButton        ((LPCSTR)101)
#define ORDINAL_XInputCancelGuideButtonWait     ((LPCSTR)102)
#define ORDINAL_XInputPowerOffController        ((LPCSTR)103)
#define ORDINAL_XInputGetBaseBusInformation     ((LPCSTR)104)
#define ORDINAL_XInputGetCapabilitiesEx         ((LPCSTR)108)

#ifndef WIN_NOEXCEPT
    #if _MSC_VER >= 1900
        #define WIN_NOEXCEPT noexcept
    #else
        #define WIN_NOEXCEPT throw()
    #endif
#endif

DWORD WINAPI XInputGetStateEx(
    _In_  DWORD         UserIndex,              // Index of the gamer associated with the device
    _Out_ PXINPUT_STATE State                   // Receives the current state
) WIN_NOEXCEPT;

DWORD WINAPI XInputWaitForGuideButton(
    _In_  DWORD         UserIndex,              // Index of the gamer associated with the device
    _In_  DWORD         Flags,                  // Input flags that identify the device type
    _Out_ PXINPUT_LISTEN_STATE ListenState
) WIN_NOEXCEPT;

DWORD WINAPI XInputCancelGuideButtonWait(
    _In_  DWORD         UserIndex               // Index of the gamer associated with the device
) WIN_NOEXCEPT;

DWORD WINAPI XInputPowerOffController(
    _In_  DWORD         UserIndex               // Index of the gamer associated with the device
) WIN_NOEXCEPT;

DWORD WINAPI XInputGetBaseBusInformation(
    _In_  DWORD         UserIndex,              // Index of the gamer associated with the device
    _Out_ PXINPUT_BASE_BUS_INFORMATION BusInfo  // Receives the bus information
) WIN_NOEXCEPT;

DWORD WINAPI XInputGetCapabilitiesEx(
    _In_  DWORD         DeviceType,             // XINPUT_DEVTYPE_GAMEPAD
    _In_  DWORD         UserIndex,              // Index of the gamer associated with the device
    _In_  DWORD         Flags,                  // Input flags that identify the device type
    _Out_ PXINPUT_CAPABILITIES_EX Capabilities  // Receives the capabilities
) WIN_NOEXCEPT;

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


#include <pshpack1.h>

VEIL_DECLARE_STRUCT(XUSB_BASE_REQUEST)
{
    UINT16 Version;
    UINT8  DeviceIndex;
};
C_ASSERT(sizeof(XUSB_BASE_REQUEST) == 3);

VEIL_DECLARE_STRUCT(XUSB_INFORMATION)
{
    UINT16 Version;
    UINT8  DeviceIndex; // Child device index of bus driver
    UINT8  Unknown1;
    UINT16 Unknown2[2];
    UINT16 VendorId;
    UINT16 ProductId;
};
C_ASSERT(sizeof(XUSB_INFORMATION) == 12);

VEIL_DECLARE_STRUCT(XUSB_CAPABILITIES_0101)
{
    UINT16 Version;
    UINT8  Type;
    UINT8  SubType;

    // XINPUT_GAMEPAD
    UINT16 Buttons;
    UINT8  LeftTrigger;
    UINT8  RightTrigger;
    INT16  ThumbLX;
    INT16  ThumbLY;
    INT16  ThumbRX;
    INT16  ThumbRY;

    UINT16 Unknown[3];

    // XINPUT_VIBRATION
    UINT8  LeftMotorSpeed;
    UINT8  RightMotorSpeed;
};
C_ASSERT(sizeof(XUSB_CAPABILITIES_0101) == 24);

VEIL_DECLARE_STRUCT(XUSB_CAPABILITIES_0102)
{
    UINT16 Version;
    UINT8  Type;
    UINT8  SubType;
    UINT16 Flags;

    // XINPUT_BASE_BUS_INFORMATION
    UINT16 VendorId;
    UINT16 ProductId;
    UINT16 RevisionId;
    UINT32 Unknown1;    // 0x313fcfdc

    // XINPUT_GAMEPAD
    UINT16 Buttons;
    UINT8  LeftTrigger;
    UINT8  RightTrigger;
    INT16  ThumbLX;
    INT16  ThumbLY;
    INT16  ThumbRX;
    INT16  ThumbRY;

    UINT16 Unknown[3];

    // XINPUT_VIBRATION
    UINT8  LeftMotorSpeed;
    UINT8  RightMotorSpeed;
};
C_ASSERT(sizeof(XUSB_CAPABILITIES_0102) == 36);

#define XUSB_LED_OFF                ((UINT8)0)
#define XUSB_LED_BLINK              ((UINT8)1)
#define XUSB_LED_1_SWITCH_BLINK     ((UINT8)2)
#define XUSB_LED_2_SWITCH_BLINK     ((UINT8)3)
#define XUSB_LED_3_SWITCH_BLINK     ((UINT8)4)
#define XUSB_LED_4_SWITCH_BLINK     ((UINT8)5)
#define XUSB_LED_1                  ((UINT8)6)
#define XUSB_LED_2                  ((UINT8)7)
#define XUSB_LED_3                  ((UINT8)8)
#define XUSB_LED_4                  ((UINT8)9)
#define XUSB_LED_CYCLE              ((UINT8)10)
#define XUSB_LED_FAST_BLINK         ((UINT8)11)
#define XUSB_LED_SLOW_BLINK         ((UINT8)12)
#define XUSB_LED_FLIPFLOP           ((UINT8)13)
#define XUSB_LED_ALLBLINK           ((UINT8)14)

VEIL_DECLARE_STRUCT(XUSB_LED_STATE)
{
    UINT16 Version;
    UINT8  LEDState;
};
C_ASSERT(sizeof(XUSB_LED_STATE) == 3);

VEIL_DECLARE_STRUCT(XUSB_STATE_0100_REQUEST)
{
    UINT8  DeviceIndex;
};

#define XUSB_DEVICE_STATUS_CONNECTED    ((UINT8)1)
#define XUSB_DEVICE_STATUS_INACTIVE     ((UINT8)2)
#define XUSB_DEVICE_STATUS_READY        ((UINT8)3)
#define XUSB_DEVICE_STATUS_DISCONNECTED ((UINT8)5)

VEIL_DECLARE_STRUCT(XUSB_STATE_0100)
{
    UINT8  Status;
    UINT8  Unknown1;
    UINT8  InputId;
    UINT32 PacketNumber;
    UINT8  Unknown2;
    UINT16 Buttons;
    UINT8  LeftTrigger;
    UINT8  RightTrigger;
    INT16  ThumbLX;
    INT16  ThumbLY;
    INT16  ThumbRX;
    INT16  ThumbRY;
};
C_ASSERT(sizeof(XUSB_STATE_0100) == 20);

// IOCTL_XUSB_GET_STATE
// IOCTL_XUSB_WAIT_GUIDE_BUTTON
// IOCTL_XUSB_WAIT_FOR_INPUT
VEIL_DECLARE_STRUCT(XUSB_STATE_0101)
{
    UINT16 Version;
    UINT8  Status;
    UINT8  Unknown1;
    UINT8  InputId;

    UINT32 PacketNumber;
    UINT8  Unknown2;
    UINT8  Unknown3;    // 0x14
    UINT16 Buttons;
    UINT8  LeftTrigger;
    UINT8  RightTrigger;
    INT16  ThumbLX;
    INT16  ThumbLY;
    INT16  ThumbRX;
    INT16  ThumbRY;
    UINT8  Unknown[5];
    UINT8  ExtraButtons;
};
C_ASSERT(sizeof(XUSB_STATE_0101) == 29);

#define XUSB_SET_STATE_FLAG_LED         ((UINT8)0x01)
#define XUSB_SET_STATE_FLAG_VIBRATION   ((UINT8)0x02)

VEIL_DECLARE_STRUCT(XUSB_SET_STATE)
{
    UINT8  DeviceIndex;

    UINT8  LEDState;        // XUSB_SET_STATE_FLAG_LED

    UINT8  LeftMotorSpeed;  // XUSB_SET_STATE_FLAG_VIBRATION
    UINT8  RightMotorSpeed;

    UINT8  Flags;
};
C_ASSERT(sizeof(XUSB_SET_STATE) == 5);

VEIL_DECLARE_STRUCT(XUSB_BATTERY_INFORMATION_REQUEST)
{
    XUSB_BASE_REQUEST Base;
    UINT8 DeviceType;
};
C_ASSERT(sizeof(XUSB_BATTERY_INFORMATION_REQUEST) == 4);

VEIL_DECLARE_STRUCT(XUSB_BATTERY_INFORMATION)
{
    UINT16 Version;
    UINT8  BatteryType;
    UINT8  BatteryLevel;
};
C_ASSERT(sizeof(XUSB_BATTERY_INFORMATION) == 4);

VEIL_DECLARE_STRUCT(XUSB_SET_POWEROFF)
{
    UINT16 Version;
    UINT8  DeviceIndex;
};
C_ASSERT(sizeof(XUSB_SET_POWEROFF) == 3);

VEIL_DECLARE_STRUCT(XUSB_AUDIO_DEVICE_INFORMATION)
{
    // USB\VID_%04X&PID_%04X&IA_%02X, VendorId, VendorId, InputId

    UINT16 Version;
    UINT16 VendorId;
    UINT16 ProductId;
    UINT8  InputId;
};
C_ASSERT(sizeof(XUSB_AUDIO_DEVICE_INFORMATION) == 7);

VEIL_DECLARE_STRUCT(XUSB_WAIT_FOR_INPUT_REQUEST)
{
    UINT16 Version;
    UINT8  DeviceIndex;
    UINT8  Status;
};
C_ASSERT(sizeof(XUSB_WAIT_FOR_INPUT_REQUEST) == 4);

VEIL_DECLARE_STRUCT(XUSB_INFORMATION_EX_REQUEST)
{
    UINT16 Version;
    UINT8  Type;
    UINT8  Padding;

    UINT8  Unknown[32];
};
C_ASSERT(sizeof(XUSB_INFORMATION_EX_REQUEST) == 36);

VEIL_DECLARE_STRUCT(XUSB_INFORMATION_EX)
{
    UINT16 Version;
    UINT8  Invalid;
    UINT16 Length;

    // begin union

    USB_DEVICE_DESCRIPTOR UsbDeviceDescriptor;

    UINT16 VendorId;
    UINT16 ProductId;
    UINT16 RevisionId;
    UINT8  Unknown1;
    UINT32 Unknown2;
    UINT8  Unknown3[3];

    UINT8  Unknown4[912];
};
C_ASSERT(sizeof(XUSB_INFORMATION_EX) == 949);

#include <poppack.h>


VEIL_END()

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
