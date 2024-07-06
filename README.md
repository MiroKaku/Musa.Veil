# [Mi.Veil](https://github.com/mirokaku/Veil)

[![Actions Status](https://github.com/MiroKaku/Veil/workflows/build/badge.svg)](https://github.com/MiroKaku/Veil/actions)
[![LICENSE](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/MiroKaku/Veil/blob/main/LICENSE)
[![nuget](https://img.shields.io/nuget/v/Mi.Veil)](https://www.nuget.org/packages/Mi.Veil/)

* [简体中文](https://github.com/MiroKaku/Veil/blob/main/README.zh-CN.md)

`Mi.Veil` is a collection of Native API definitions for Windows. Take the name `Veil`, which means to lift the veil of Windows and spy on the face hidden behind.

This project contains the definitions for the Windows internal undocumented API from `ntoskrnl.exe`, `ntdll.dll`, `kernelbase.dll`.

This project is based on the [systeminformer/phnt](https://github.com/winsiderss/systeminformer/tree/master/phnt) and [Chuyu-Team/MINT](https://github.com/Chuyu-Team/MINT) fork modifications, combining the advantages of the two projects.

* Both user-mode and kernel-mode are supported.
* Compiling using the /W4 /WX option is supported.
* Optimized for the Windows SDK.
* The API is managed by Windows SDK version macros.

## How to use

### Method 1 (recommended)

Right click on the project, select "Manage NuGet Packages".
Search for `Mi.Veil`, choose the version that suits you, and then click "Install".

### Method 2

First make sure that your program is using the latest Windows SDK.
Then clone and include it.

## Other

```C
// If you wonder to use separate namespace, please define the following macro.
#define VEIL_USE_SEPARATE_NAMESPACE

// First inclusion order
#include "Veil.h"
```
