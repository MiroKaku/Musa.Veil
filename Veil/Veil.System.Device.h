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

#include <initguid.h>

VEIL_BEGIN()

//
// Device VendorId(VID) & ProductId(PID)
//

// Microsoft
#define DEVICE_VID_MICROSOFT        ((UINT16)0x045E)
#define DEVICE_PID_XUSB             ((UINT16)0x028E)    /* Xbox 360 Wired Common Controller */
#define DEVICE_PID_XUSB_WIRELESS    ((UINT16)0x0719)    /* Xbox 360 Wireless Common Controller Reciever */

// Rapoo
#define DEVICE_VID_RAPOO            ((UINT16)0x0079)
#define DEVICE_PID_RAPOO_XUSB       ((UINT16)0x188E)

//
// Device Setup Classes
// C:\Windows\System32\migration\pnpmig.inf
// https://learn.microsoft.com/en-us/windows-hardware/drivers/install/system-defined-device-setup-classes-available-to-vendors
//

// System Container Devices
// Class = SystemContainer
// ClassGuid = {00000000-0000-0000-FFFF-FFFFFFFFFFFF}
DEFINE_GUID(GUID_DEVCLASS_SYSTEM_CONTAINER, 0x00000000, 0x0000, 0x0000, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff);

#define GUID_DEVCLASS_SYSTEM_CONTAINER_STRING L"{00000000-0000-0000-ffff-ffffffffffff}"

// Adapter
// Class = Adapter
// ClassGuid = {4d36e964-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_ADAPTER, 0x4d36e964, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_ADAPTER_STRING L"{4d36e964-e325-11ce-bfc1-08002be10318}"

// CD-ROM Drives
// Class = CDROM
// ClassGuid = {4d36e965-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_CDROM, 0x4d36e965, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_CDROM_STRING L"{4d36e965-e325-11ce-bfc1-08002be10318}"

// Computer
// Class = Computer
// ClassGuid = {4d36e966-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_COMPUTER, 0x4d36e966, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_COMPUTER_STRING L"{4d36e966-e325-11ce-bfc1-08002be10318}"

// Disk Drives
// Class = DiskDrive
// ClassGuid = {4d36e967-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_DISK_DRIVE, 0x4d36e967, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_DISK_DRIVE_STRING L"{4d36e967-e325-11ce-bfc1-08002be10318}"

// Display Adapters
// Class = Display
// ClassGuid = {4d36e968-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_DISPLAY, 0x4d36e968, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_DISPLAY_STRING L"{4d36e968-e325-11ce-bfc1-08002be10318}"

// Floppy Disk Controllers
// Class = FDC
// ClassGuid = {4d36e969-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_FLOPPY_DISK, 0x4d36e969, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_FLOPPY_DISK_STRING L"{4d36e969-e325-11ce-bfc1-08002be10318}"

// Hard Disk Controllers
// Class = HDC
// ClassGuid = {4d36e96a-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_HARD_DISK, 0xd45b1c18, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_HARD_DISK_STRING L"{4d36e96a-e325-11ce-bfc1-08002be10318}"

// Keyboard
// Class = Keyboard
// ClassGuid = {4d36e96b-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_KEYBOARD, 0x4d36e96b, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_KEYBOARD_STRING L"{4d36e96b-e325-11ce-bfc1-08002be10318}"

// Multimedia
// Class = Media
// ClassGuid = {4d36e96c-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_MEDIA, 0x4d36e96c, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_MEDIA_STRING L"{4d36e96c-e325-11ce-bfc1-08002be10318}"

// Modem
// Class = Modem
// ClassGuid = {4d36e96d-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_MODEM, 0x4d36e96d, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_MODEM_STRING L"{4d36e96d-e325-11ce-bfc1-08002be10318}"

// Monitor
// Class = Monitor
// ClassGuid = {4d36e96e-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_MONITOR, 0x4d36e96e, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_MONITOR_STRING L"{4d36e96e-e325-11ce-bfc1-08002be10318}"

// Mouse
// Class = Mouse
// ClassGuid = {4d36e96f-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_MOUSE, 0x4d36e96f, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_MOUSE_STRING L"{4d36e96f-e325-11ce-bfc1-08002be10318}"

// Memory Technology Driver
// Class = MTD
// ClassGuid = {4d36e970-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_MTD, 0x4d36e970, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_MTD_STRING L"{4d36e970-e325-11ce-bfc1-08002be10318}"

// Multifunction Devices
// Class = Multifunction
// ClassGuid = {4d36e971-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_MULTIFUNCTION, 0x4d36e971, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_MULTIFUNCTION_STRING L"{4d36e971-e325-11ce-bfc1-08002be10318}"

// Network Adapter
// Class = Net
// ClassGuid = {4d36e972-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_NET, 0x4d36e972, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_NET_STRING L"{4d36e972-e325-11ce-bfc1-08002be10318}"

// Network Client
// Class = NetClient
// ClassGuid = {4d36e973-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_NET_CLIENT, 0x4d36e973, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_NET_CLIENT_STRING L"{4d36e973-e325-11ce-bfc1-08002be10318}"

// Network Service
// Class = NetService
// ClassGuid = {4d36e974-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_NET_SERVICE, 0x4d36e974, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_NET_SERVICE_STRING L"{4d36e974-e325-11ce-bfc1-08002be10318}"

// Network Transport
// Class = NetTrans
// ClassGuid = {4d36e975-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_NET_TRANSPORT, 0x4d36e975, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_NET_TRANSPORT_STRING L"{4d36e975-e325-11ce-bfc1-08002be10318}"

// No driver
// Class = NoDriver
// ClassGuid = {4d36e976-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_NO_DRIVER, 0x4d36e976, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_NO_DRIVER_STRING L"{4d36e976-e325-11ce-bfc1-08002be10318}"

// PCMCIA Adapters
// Class = PCMCIA
// ClassGuid = {4d36e977-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_PCMCIA, 0x4d36e977, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_PCMCIA_STRING L"{4d36e977-e325-11ce-bfc1-08002be10318}"

// Ports (COM & LPT ports)
// Class = Ports
// ClassGuid = {4d36e978-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_PORTS, 0x4d36e978, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_PORTS_STRING L"{4d36e978-e325-11ce-bfc1-08002be10318}"

// Printers
// Class = Printer
// ClassGuid = {4d36e979-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_PRINTER, 0x4d36e979, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_PRINTER_STRING L"{4d36e979-e325-11ce-bfc1-08002be10318}"

// Printer Upgrade
// Class = PrinterUpgrade
// ClassGuid = {4d36e97a-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_PRINTER_UPGRADE, 0x4d36e97a, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_PRINTER_UPGRADE_STRING L"{4d36e97a-e325-11ce-bfc1-08002be10318}"

// SCSI and RAID Controllers
// Class = SCSIAdapter
// ClassGuid = {4d36e97b-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_SCSI_ADAPTER, 0x4d36e97b, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_SCSI_ADAPTER_STRING L"{4d36e97b-e325-11ce-bfc1-08002be10318}"

// Sound
// Class = Sound
// ClassGuid = {4d36e97c-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_SOUND, 0x4d36e97c, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_SOUND_STRING L"{4d36e97c-e325-11ce-bfc1-08002be10318}"

// System Devices
// Class = System
// ClassGuid = {4d36e97d-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_SYSTEM, 0x4d36e97d, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_SYSTEM_STRING L"{4d36e97d-e325-11ce-bfc1-08002be10318}"

// Other Devices
// Class = Unknown
// ClassGuid = {4d36e97e-e325-11ce-bfc1-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_UNKNOWN, 0x4d36e97e, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_UNKNOWN_STRING L"{4d36e97e-e325-11ce-bfc1-08002be10318}"

// IEEE 1394 Host Bus Controller
// Class = 1394
// ClassGuid = {6bdd1fc1-810f-11d0-bec7-08002be2092f}
DEFINE_GUID(GUID_DEVCLASS_IEEE1394, 0x6bdd1fc1, 0x810f, 0x11d0, 0xbe, 0xc7, 0x08, 0x00, 0x2b, 0xe2, 0x09, 0x2f);

#define GUID_DEVCLASS_IEEE1394_STRING L"{6bdd1fc1-810f-11d0-bec7-08002be2092f}"

// Decoders
// Class = Decoder
// ClassGuid = {6bdd1fc2-810f-11d0-bec7-08002be2092f}
DEFINE_GUID(GUID_DEVCLASS_DECODERS, 0x6bdd1fc2, 0x810f, 0x11d0, 0xbe, 0xc7, 0x08, 0x00, 0x2b, 0xe2, 0x09, 0x2f);

#define GUID_DEVCLASS_DECODERS_STRING L"{6bdd1fc2-810f-11d0-bec7-08002be2092f}"

// IrDA Devices
// Class = Infrared
// ClassGuid = {6bdd1fc5-810f-11d0-bec7-08002be2092f}
DEFINE_GUID(GUID_DEVCLASS_INFRARED, 0x6bdd1fc5, 0x810f, 0x11d0, 0xbe, 0xc7, 0x08, 0x00, 0x2b, 0xe2, 0x09, 0x2f);

#define GUID_DEVCLASS_INFRARED_STRING L"{6bdd1fc5-810f-11d0-bec7-08002be2092f}"

// Imaging Device
// Class = Image
// ClassGuid = {6bdd1fc6-810f-11d0-bec7-08002be2092f}
DEFINE_GUID(GUID_DEVCLASS_IMAGE, 0x6bdd1fc6, 0x810f, 0x11d0, 0xbe, 0xc7, 0x08, 0x00, 0x2b, 0xe2, 0x09, 0x2f);

#define GUID_DEVCLASS_IMAGE_STRING L"{6bdd1fc6-810f-11d0-bec7-08002be2092f}"

// Storage Volumes
// Class = Volume
// ClassGuid = {71a27cdd-812a-11d0-bec7-08002be2092f}
DEFINE_GUID(GUID_DEVCLASS_VOLUME, 0x71a27cdd, 0x812a, 0x11d0, 0xbe, 0xc7, 0x08, 0x00, 0x2b, 0xe2, 0x09, 0x2f);

#define GUID_DEVCLASS_VOLUME_STRING L"{71a27cdd-812a-11d0-bec7-08002be2092f}"

// Multiport Serial Adapters
// Class = MultiportSerial
// ClassGuid = {50906cb8-ba12-11d1-bf5d-0000f805f530}
DEFINE_GUID(GUID_DEVCLASS_MULTIPORT_SERIAL, 0x50906cb8, 0xba12, 0x11d1, 0xbf, 0x5d, 0x00, 0x00, 0xf8, 0x05, 0xf5, 0x30);

#define GUID_DEVCLASS_MULTIPORT_SERIAL_STRING L"{50906cb8-ba12-11d1-bf5d-0000f805f530}"

// Smart Card Readers
// Class = SmartCardReader
// ClassGuid = {50dd5230-ba8a-11d1-bf5d-0000f805f530}
DEFINE_GUID(GUID_DEVCLASS_SMART_CARD_READER, 0x50dd5230, 0xba8a, 0x11d1, 0xbf, 0x5d, 0x00, 0x00, 0xf8, 0x05, 0xf5, 0x30);

#define GUID_DEVCLASS_SMART_CARD_READER_STRING L"{50dd5230-ba8a-11d1-bf5d-0000f805f530}"

// APM
// Class = APMSupport
// ClassGuid = {d45b1c18-c8fa-11d1-9f77-0000f805f530}
DEFINE_GUID(GUID_DEVCLASS_APM, 0xd45b1c18, 0xc8fa, 0x11d1, 0x9f, 0x77, 0x00, 0x00, 0xf8, 0x05, 0xf5, 0x30);

#define GUID_DEVCLASS_APM_STRING L"{d45b1c18-c8fa-11d1-9f77-0000f805f530}"

// Host-side IEEE 1394 Kernel Debugger Support
// Class = 1394Debug
// ClassGuid = {66f250d6-7801-4a64-b139-eea80a450b24}
DEFINE_GUID(GUID_DEVCLASS_1394DEBUG, 0x66f250d6, 0x7801, 0x4a64, 0xb1, 0x39, 0xee, 0xa8, 0x0a, 0x45, 0x0b, 0x24);

#define GUID_DEVCLASS_1394DEBUG_STRING L"{66f250d6-7801-4a64-b139-eea80a450b24}"

// IEEE 1394 IP Network Enumerator
// Class = Enum1394
// ClassGuid = {c459df55-db08-11d1-b009-00a0c9081ff6}
DEFINE_GUID(GUID_DEVCLASS_ENUM_1394, 0xc459df55, 0xdb08, 0x11d1, 0xb0, 0x09, 0x00, 0xa0, 0xc9, 0x08, 0x1f, 0xf6);

#define GUID_DEVCLASS_ENUM_1394_STRING L"{c459df55-db08-11d1-b009-00a0c9081ff6}"

// Non-Plug and Play Drivers
// Class = LegacyDriver
// ClassGuid = {8ecc055d-047f-11d1-a537-0000f8753ed1}
DEFINE_GUID(GUID_DEVCLASS_LEGACY_DRIVER, 0x8ecc055d, 0x047f, 0x11d1, 0xa5, 0x37, 0x00, 0x00, 0xf8, 0x75, 0x3e, 0xd1);

#define GUID_DEVCLASS_LEGACY_DRIVER_STRING L"{8ecc055d-047f-11d1-a537-0000f8753ed1}"

// Print Queue
// Class = PrintQueue
// ClassGuid = {1ed2bbf9-11f0-4084-b21f-ad83a8e6dcdc}
DEFINE_GUID(GUID_DEVCLASS_PRINTE_QUEUE, 0x1ed2bbf9, 0x11f0, 0x4084, 0xb2, 0x1f, 0xad, 0x83, 0xa8, 0xe6, 0xdc, 0xdc);

#define GUID_DEVCLASS_PRINTE_QUEUE_STRING L"{1ed2bbf9-11f0-4084-b21f-ad83a8e6dcdc}"

// Software Device
// Class = SoftwareDevice
// ClassGuid = {62f9c741-b25a-46ce-b54c-9bccce08b6f2}
DEFINE_GUID(GUID_DEVCLASS_SOFTWARE_DEVICE, 0x62f9c741, 0xb25a, 0x46ce, 0xb5, 0x4c, 0x9b, 0xcc, 0xce, 0x08, 0xb6, 0xf2);

#define GUID_DEVCLASS_SOFTWARE_DEVICE_STRING L"{62f9c741-b25a-46ce-b54c-9bccce08b6f2}"

// Audio Endpoint
// Class = AudioEndpoint
// ClassGuid = {c166523c-fe0c-4a94-a586-f1a80cfbbf3e}
DEFINE_GUID(GUID_DEVCLASS_AUDIO_ENDPOINT, 0xc166523c, 0xfe0c, 0x4a94, 0xa5, 0x86, 0xf1, 0xa8, 0x0c, 0xfb, 0xbf, 0x3e);

#define GUID_DEVCLASS_AUDIO_ENDPOINT_STRING L"{c166523c-fe0c-4a94-a586-f1a80cfbbf3e}"

// Storage Volume Snapshots
// Class = VolumeSnapshot
// ClassGuid = {533c5b84-ec70-11d2-9505-00c04f79deaf}
DEFINE_GUID(GUID_DEVCLASS_VOLUME_SNAPSHOT, 0x533c5b84, 0xec70, 0x11d2, 0x95, 0x05, 0x00, 0xc0, 0x4f, 0x79, 0xde, 0xaf);

#define GUID_DEVCLASS_VOLUME_SNAPSHOT_STRING L"{533c5b84-ec70-11d2-9505-00c04f79deaf}"

// USB Bus Devices (hubs and host controllers)
// Class = USB
// ClassGuid = {36fc9e60-c465-11cf-8056-444553540000}
DEFINE_GUID(GUID_DEVCLASS_USB, 0x36fc9e60, 0xc465, 0x11cf, 0x80, 0x56, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

#define GUID_DEVCLASS_USB_STRING L"{36fc9e60-c465-11cf-8056-444553540000}"

// Audio Processing Objects (APOs)
// Class = AudioProcessingObject
// ClassGuid = {5989fce8-9cd0-467d-8a6a-5419e31529d4}
DEFINE_GUID(GUID_DEVCLASS_APO, 0x5989fce8, 0x9cd0, 0x467d, 0x8a, 0x6a, 0x54, 0x19, 0xe3, 0x15, 0x29, 0xd4);

#define GUID_DEVCLASS_APO_STRING L"{5989fce8-9cd0-467d-8a6a-5419e31529d4}"

// Battery Devices
// Class = Battery
// ClassGuid = {72631e54-78a4-11d0-bcf7-00aa00b7b32a}
DEFINE_GUID(GUID_DEVCLASS_BATTERY, 0x72631e54, 0x78a4, 0x11d0, 0xbc, 0xf7, 0x00, 0xaa, 0x00, 0xb7, 0xb3, 0x2a);

#define GUID_DEVCLASS_BATTERY_STRING L"{72631e54-78a4-11d0-bcf7-00aa00b7b32a}"

// Biometric Device
// Class = Biometric
// ClassGuid = {53d29ef7-377c-4d14-864b-eb3a85769359}
DEFINE_GUID(GUID_DEVCLASS_BIOMETRIC, 0x53d29ef7, 0x377c, 0x4d14, 0x86, 0x4b, 0xeb, 0x3a, 0x85, 0x76, 0x93, 0x59);

#define GUID_DEVCLASS_BIOMETRIC_STRING L"{53d29ef7-377c-4d14-864b-eb3a85769359}"

// Bluetooth Devices
// Class = Bluetooth
// ClassGuid = {e0cbf06c-cd8b-4647-bb8a-263b43f0f974}
DEFINE_GUID(GUID_DEVCLASS_BLUETOOTH, 0xe0cbf06c, 0xcd8b, 0x4647, 0xbb, 0x8a, 0x26, 0x3b, 0x43, 0xf0, 0xf9, 0x74);

#define GUID_DEVCLASS_BLUETOOTH_STRING L"{e0cbf06c-cd8b-4647-bb8a-263b43f0f974}"

// Camera Device
// Class = Camera
// ClassGuid = {ca3e7ab9-b4c3-4ae6-8251-579ef933890f}
DEFINE_GUID(GUID_DEVCLASS_CAMERA, 0xca3e7ab9, 0xb4c3, 0x4ae6, 0x82, 0x51, 0x57, 0x9e, 0xf9, 0x33, 0x89, 0x0f);

#define GUID_DEVCLASS_CAMERA_STRING L"{ca3e7ab9-b4c3-4ae6-8251-579ef933890f}"

// Extension INF
// Class = Extension
// ClassGuid = {e2f84ce7-8efa-411c-aa69-97454ca4cb57}
DEFINE_GUID(GUID_DEVCLASS_EXTENSION, 0xe2f84ce7, 0x8efa, 0x411c, 0xaa, 0x69, 0x97, 0x45, 0x4c, 0xa4, 0xcb, 0x57);

#define GUID_DEVCLASS_EXTENSION_STRING L"{e2f84ce7-8efa-411c-aa69-97454ca4cb57}"

// Human Interface Devices (HID)
// Class = HIDClass
// ClassGuid = {745a17a0-74d3-11d0-b6fe-00a0c90f57da}
DEFINE_GUID(GUID_DEVCLASS_HID, 0x745a17a0, 0x74d3, 0x11d0, 0xb6, 0xfe, 0x00, 0xa0, 0xc9, 0x0f, 0x57, 0xda);

#define GUID_DEVCLASS_HID_STRING L"{745a17a0-74d3-11d0-b6fe-00a0c90f57da}"

// IEEE 1284.4 Devices
// Class = Dot4
// ClassGuid = {48721b56-6795-11d2-b1a8-0080c72e74a2}
DEFINE_GUID(GUID_DEVCLASS_IEEE1284_DOT4, 0x48721b56, 0x6795, 0x11d2, 0xb1, 0xa8, 0x00, 0x80, 0xc7, 0x2e, 0x74, 0xa2);

#define GUID_DEVCLASS_IEEE1284_DOT4_STRING L"{48721b56-6795-11d2-b1a8-0080c72e74a2}"

// IEEE 1284.4 Print Functions
// Class = Dot4Print
// ClassGuid = {49ce6ac8-6f86-11d2-b1e5-0080c72e74a2}
DEFINE_GUID(GUID_DEVCLASS_IEEE1284_DOT4_PRINT, 0x49ce6ac8, 0x6f86, 0x11d2, 0xb1, 0xe5, 0x00, 0x80, 0xc7, 0x2e, 0x74, 0xa2);

#define GUID_DEVCLASS_IEEE1284_DOT4_PRINT_STRING L"{49ce6ac8-6f86-11d2-b1e5-0080c72e74a2}"

// IEEE 1394 Devices That Support the 61883 Protocol
// Class = 61883
// ClassGuid = {7ebefbc0-3200-11d2-b4c2-00a0c9697d07}
DEFINE_GUID(GUID_DEVCLASS_IEEE1394_61883, 0x7ebefbc0, 0x3200, 0x11d2, 0xb4, 0xc2, 0x00, 0xa0, 0xc9, 0x69, 0x7d, 0x07);

#define GUID_DEVCLASS_IEEE1394_61883_STRING L"{7ebefbc0-3200-11d2-b4c2-00a0c9697d07}"

// IEEE 1394 Devices That Support the AVC Protocol
// Class = AVC
// ClassGuid = {c06ff265-ae09-48f0-812c-16753d7cba83}
DEFINE_GUID(GUID_DEVCLASS_IEEE1394_AVC, 0xc06ff265, 0xae09, 0x48f0, 0x81, 0x2c, 0x16, 0x75, 0x3d, 0x7c, 0xba, 0x83);

#define GUID_DEVCLASS_IEEE1394_AVC_STRING L"{c06ff265-ae09-48f0-812c-16753d7cba83}"

// IEEE 1394 Devices That Support the SBP2 Protocol
// Class = SBP2
// ClassGuid = {d48179be-ec20-11d1-b6b8-00c04fa372a7}
DEFINE_GUID(GUID_DEVCLASS_IEEE1394_SBP2, 0xd48179be, 0xec20, 0x11d1, 0xb6, 0xb8, 0x00, 0xc0, 0x4f, 0xa3, 0x72, 0xa7);

#define GUID_DEVCLASS_IEEE1394_SBP2_STRING L"{d48179be-ec20-11d1-b6b8-00c04fa372a7}"

// Printers, Bus-specific class drivers
// Class = PNPPrinters
// ClassGuid = {4658ee7e-f050-11d1-b6bd-00c04fa372a7}
DEFINE_GUID(GUID_DEVCLASS_PNP_PRINTERS, 0x4658ee7e, 0xf050, 0x11d1, 0xb6, 0xbd, 0x00, 0xc0, 0x4f, 0xa3, 0x72, 0xa7);

#define GUID_DEVCLASS_PNP_PRINTERS_STRING L"{4658ee7e-f050-11d1-b6bd-00c04fa372a7}"

// Media Changers
// Class = MediumChanger
// ClassGuid = {ce5939ae-ebde-11d0-b181-0000f8753ec4}
DEFINE_GUID(GUID_DEVCLASS_MEDIUM_CHANGER, 0xce5939ae, 0xebde, 0x11d0, 0xb1, 0x81, 0x00, 0x00, 0xf8, 0x75, 0x3e, 0xc4);

#define GUID_DEVCLASS_MEDIUM_CHANGER_STRING L"{ce5939ae-ebde-11d0-b181-0000f8753ec4}"

// PCI SSL Accelerator
// Class = SecurityAccelerator
// ClassGuid = {268c95a1-edfe-11d3-95c3-0010dc4050a5}
DEFINE_GUID(GUID_DEVCLASS_SECURITY_ACCELERATOR, 0x268c95a1, 0xedfe, 0x11d3, 0x95, 0xc3, 0x00, 0x10, 0xdc, 0x40, 0x50, 0xa5);

#define GUID_DEVCLASS_SECURITY_ACCELERATOR_STRING L"{268c95a1-edfe-11d3-95c3-0010dc4050a5}"

// Processors
// Class = Processor
// ClassGuid = {50127dc3-0f36-415e-a6cc-4cb3be910b65}
DEFINE_GUID(GUID_DEVCLASS_PROCESSOR, 0x50127dc3, 0x0f36, 0x415e, 0xa6, 0xcc, 0x4c, 0xb3, 0xbe, 0x91, 0x0b, 0x65);

#define GUID_DEVCLASS_PROCESSOR_STRING L"{50127dc3-0f36-415e-a6cc-4cb3be910b65}"

// Security Devices
// Class = SecurityDevices
// ClassGuid = {d94ee5d8-d189-4994-83d2-f68d7d41b0e6}
DEFINE_GUID(GUID_DEVCLASS_SECURITY_DEVICES, 0xd94ee5d8, 0xd189, 0x4994, 0x83, 0xd2, 0xf6, 0x8d, 0x7d, 0x41, 0xb0, 0xe6);

#define GUID_DEVCLASS_SECURITY_DEVICES_STRING L"{d94ee5d8-d189-4994-83d2-f68d7d41b0e6}"

// Sensors
// Class = Sensor
// ClassGuid = {5175d334-c371-4806-b3ba-71fd53c9258d}
DEFINE_GUID(GUID_DEVCLASS_SENSOR, 0x5175d334, 0xc371, 0x4806, 0xb3, 0xba, 0x71, 0xfd, 0x53, 0xc9, 0x25, 0x8d);

#define GUID_DEVCLASS_SENSOR_STRING L"{5175d334-c371-4806-b3ba-71fd53c9258d}"

// Software Component
// Class = SoftwareComponent
// ClassGuid = {5c4c3332-344d-483c-8739-259e934c9cc8}
DEFINE_GUID(GUID_DEVCLASS_SOFTWARE_COMPONENT, 0x5c4c3332, 0x344d, 0x483c, 0x87, 0x39, 0x25, 0x9e, 0x93, 0x4c, 0x9c, 0xc8);

#define GUID_DEVCLASS_SOFTWARE_COMPONENT_STRING L"{5c4c3332-344d-483c-8739-259e934c9cc8}"

// Tape Drives
// Class = TapeDrive
// ClassGuid = {6d807884-7d21-11cf-801c-08002be10318}
DEFINE_GUID(GUID_DEVCLASS_TAPE_DRIVE, 0x6d807884, 0x7d21, 0x11cf, 0x80, 0x1c, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);

#define GUID_DEVCLASS_TAPE_DRIVE_STRING L"{6d807884-7d21-11cf-801c-08002be10318}"

// USB Device
// Class = USBDevice
// ClassGuid = {88bae032-5a81-49f0-bc3d-a4ff138216d6}
DEFINE_GUID(GUID_DEVCLASS_USB_DEVICE, 0x88BAE032, 0x5A81, 0x49f0, 0xbc, 0x3d, 0xa4, 0xff, 0x13, 0x82, 0x16, 0xd6);

#define GUID_DEVCLASS_USB_DEVICE_STRING L"{88bae032-5a81-49f0-bc3d-a4ff138216d6}"

// Windows CE USB ActiveSync Devices
// Class = WCEUSBS
// ClassGuid = {25dbce51-6c8f-4a72-8a6d-b54c2b4fc835}
DEFINE_GUID(GUID_DEVCLASS_WCEUSBS, 0x25dbce51, 0x6c8f, 0x4a72, 0x8a, 0x6d, 0xb5, 0x4c, 0x2b, 0x4f, 0xc8, 0x35);

#define GUID_DEVCLASS_WCEUSBS_STRING L"{25dbce51-6c8f-4a72-8a6d-b54c2b4fc835}"

// Windows Portable Devices (WPD)
// Class = WPD
// ClassGuid = {eec5ad98-8080-425f-922a-dabf3de3f69a}
DEFINE_GUID(GUID_DEVCLASS_WPD, 0xeec5ad98, 0x8080, 0x425f, 0x92, 0x2a, 0xda, 0xbf, 0x3d, 0xe3, 0xf6, 0x9a);

#define GUID_DEVCLASS_WPD_STRING L"{eec5ad98-8080-425f-922a-dabf3de3f69a}"

// XNA Composite (xusb22) - Microsoft Xbox Wireless Controller
// Class = XnaComposite
// ClassGuid = {d61ca365-5af4-4486-998b-9db4734c6ca3}
DEFINE_GUID(GUID_DEVCLASS_XNA, 0xd61ca365, 0x5af4, 0x4486, 0x99, 0x8b, 0x9d, 0xb4, 0x73, 0x4c, 0x6c, 0xa3);

#define GUID_DEVCLASS_XNA_STRING L"{d61ca365-5af4-4486-998b-9db4734c6ca3}"

// Xbox Composite (xb1usb) - Microsoft Xbox One Controller
// Class = XboxComposite
// ClassGuid = {05f5cfe2-4733-4950-a6bb-07aad01a3a84}
DEFINE_GUID(GUID_DEVCLASS_XBOX, 0x05f5cfe2, 0x4733, 0x4950, 0xa6, 0xbb, 0x07, 0xaa, 0xd0, 0x1a, 0x3a, 0x84);

#define GUID_DEVCLASS_XBOX_STRING L"{05f5cfe2-4733-4950-a6bb-07aad01a3a84}"

//
// Device Interface Classes
//

// HID Interface
// Class = GUID_DEVINTERFACE_HID (hidclass.h)
// ClassGuid = {4d1e55b2-f16f-11cf-88cb-001111000030}

#define GUID_DEVINTERFACE_HID_STRING L"{4d1e55b2-f16f-11cf-88cb-001111000030}"

// XNA Interface
// Class = GUID_DEVINTERFACE_XNA
// ClassGuid = {ec87f1e3-c13b-4100-b5f7-8b84d54260cb}
DEFINE_GUID(XUSB_INTERFACE_CLASS_GUID, 0xEC87F1E3, 0xC13B, 0x4100, 0xB5, 0xF7, 0x8B, 0x84, 0xD5, 0x42, 0x60, 0xCB);
#define GUID_DEVINTERFACE_XNA XUSB_INTERFACE_CLASS_GUID

#define GUID_DEVINTERFACE_XNA_STRING L"{ec87f1e3-c13b-4100-b5f7-8b84d54260cb}"


VEIL_END()

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

#include "Veil/Veil.System.Device.Xusb.h"
