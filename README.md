# [Musa.Veil](https://github.com/MiroKaku/Veil)

[![Actions Status](https://github.com/MiroKaku/Veil/workflows/Build/badge.svg)](https://github.com/MiroKaku/Veil/actions)
[![LICENSE](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/MiroKaku/Veil/blob/main/LICENSE)
[![Downloads](https://img.shields.io/nuget/dt/Musa.Veil?logo=NuGet&logoColor=blue)](https://www.nuget.org/packages/Musa.Veil/)

* [简体中文](https://github.com/MiroKaku/Veil/blob/main/README.zh-CN.md)

`Musa.Veil` is a collection of Native API definitions for Windows. Take the name `Veil`, which means to lift the veil of Windows and spy on the face hidden behind.

This project contains the definitions for the Windows internal undocumented API from `ntoskrnl.exe`, `ntdll.dll`, `kernelbase.dll`.

This project is based on the [systeminformer/phnt](https://github.com/winsiderss/systeminformer/tree/master/phnt) and [Chuyu-Team/MINT](https://github.com/Chuyu-Team/MINT) fork modifications, combining the advantages of the two projects.

* Both user-mode and kernel-mode are supported.
* Compiling using the /W4 /WX option is supported.
* Optimized for the Windows SDK.
* The API is managed by Windows SDK version macros.

## How to use

### Method 1 (recommended)

Right click on the project, select "Manage NuGet Packages".
Search for `Musa.Veil`, choose the version that suits you, and then click "Install".

Or

If your project template uses [Mile.Project.Windows](https://github.com/ProjectMile/Mile.Project.Windows), you can add the following code directly to your `.vcxproj` file:

```XML
  <ItemGroup>
    <PackageReference Include="Musa.Veil">
      <!-- Expected version -->
      <Version>1.0.0</Version>
    </PackageReference>
  </ItemGroup>
```

### Method 2

First make sure that your program is using the latest Windows SDK.
Then clone and include it.

### CMake FetchContent

```
include(FetchContent)

FetchContent_Declare(
    Musa.Veil
    GIT_REPOSITORY https://github.com/redbg/Musa.Veil.git
    GIT_TAG main
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Musa.Veil)

add_library(Musa.Veil INTERFACE)
target_include_directories(Musa.Veil INTERFACE "${musa.veil_SOURCE_DIR}")
```

## Other

```C
// If you wonder to use separate namespace, please define the following macro.
#define VEIL_USE_SEPARATE_NAMESPACE

// First inclusion order
#include "Veil.h"
```

## Acknowledgements

Thanks to [JetBrains](https://www.jetbrains.com/?from=meesong) for providing free licenses such as [Resharper C++](https://www.jetbrains.com/resharper-cpp/?from=meesong) for my open-source projects.

[<img src="https://resources.jetbrains.com/storage/products/company/brand/logos/ReSharperCPP_icon.png" alt="ReSharper C++ logo." width=200>](https://www.jetbrains.com/?from=meesong)

