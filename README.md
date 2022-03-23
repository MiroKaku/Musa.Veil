# veil

* [简体中文](README.Zh-CN.md)

`veil` is a collection of Native API definitions for Windows. Take the name `veil`, which means to lift the veil of Windows and spy on the face hidden behind.

This project contains the definitions for the Windows internal undocumented API from `ntdll.dll`, `samlib.dll` and `winsta.dll`.

This project is based on the [processhacker/phnt](https://github.com/processhacker/phnt) and [Chuyu-Team/MINT](https://github.com/Chuyu-Team/MINT) fork modifications, combining the advantages of the two projects.

* Both user-mode and kernel-mode are supported.
* Compiling using the /W4 /WX option is supported.
* Optimized for the Windows SDK.
* The API is managed by Windows SDK version macros.

## How to use

First make sure that your program is using the latest Windows SDK.
Then clone and include it.

```C
// If you wonder to use separate namespace, please define the following macro.
#define VEIL_USE_SEPARATE_NAMESPACE

#include "veil.h"
```
