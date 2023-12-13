# 面纱 (veil)

* [English](README.md)

`面纱`是 Windows 的原生 API 定义集合。采用`面纱`这个名字，寓意为揭开 Windows 的面纱，窥探隐藏在背后的面貌。

该项目包含了来自 `ntoskrnl.exe`、`ntdll.dll`、`kernelbase.dll` 的 Windows 内部未文档化的 API 定义。

该项目基于 [systeminformer/phnt](https://github.com/winsiderss/systeminformer/tree/master/phnt) 和 [Chuyu-Team/MINT](https://github.com/Chuyu-Team/MINT) 分支修改，集合两个项目的优点。

* 可以用于内核模式和用户模式。
* 支持使用 `/W4` `/WX` 选项编译。
* 适配 Windows SDK。
* API 由 Windows SDK 版本宏管理。

## 如何使用

首先，请确保您的程序使用的是最新的 Windows SDK。然后克隆项目，直接 include 即可。

```C
// 如果你不想污染全局空间的话，请包含以下宏定义
#define VEIL_USE_SEPARATE_NAMESPACE

// 第一包含顺序
#include "veil.h"
```
