# [Musa.Veil](https://github.com/MiroKaku/Musa.Veil)

[![Actions Status](https://github.com/MiroKaku/Musa.Veil/workflows/CI/badge.svg)](https://github.com/MiroKaku/Musa.Veil/actions)
[![LICENSE](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/MiroKaku/Musa.Veil/blob/main/LICENSE)
[![Downloads](https://img.shields.io/nuget/dt/Musa.Veil?logo=NuGet&logoColor=blue)](https://www.nuget.org/packages/Musa.Veil/)

* [简体中文](https://github.com/MiroKaku/Musa.Veil/blob/main/README.zh-CN.md)

`Musa.Veil` is a collection of Native API definitions for Windows. The name "Veil" signifies lifting the veil of Windows to reveal what lies beneath.

This project contains the definitions for the Windows internal undocumented API from `ntoskrnl.exe`, `ntdll.dll`, `kernelbase.dll`.

This project is a fork based on [systeminformer/phnt](https://github.com/winsiderss/systeminformer/tree/master/phnt) and [Chuyu-Team/MINT](https://github.com/Chuyu-Team/MINT), combining the strengths of both.

- Both user-mode and kernel-mode are supported.
- Compiling using the `/W4` `/WX` option is supported.
- Optimized for the Windows SDK.
- The API is managed by Windows SDK version macros.

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

First, make sure that your program is using the latest Windows SDK.
Then clone this repository and add the include path to your project.

### Method 3 (CMake FetchContent)

```cmake
include(FetchContent)

FetchContent_Declare(
    Musa.Veil
    GIT_REPOSITORY https://github.com/MiroKaku/Musa.Veil.git
    GIT_TAG main
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Musa.Veil)

add_library(Musa.Veil INTERFACE)
target_include_directories(Musa.Veil INTERFACE "${musa.veil_SOURCE_DIR}")

# Link to your target
target_link_libraries(YourTarget PRIVATE Musa.Veil)
```

## Advanced Usage

```C
// If you want to use a separate namespace, define the following macro.
#define VEIL_USE_SEPARATE_NAMESPACE

// Include Veil.h before any other headers
#include "Veil.h"
```
