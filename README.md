# rewritting of MyDiscordBot project is in progress

# MarkWare VCMake 😎

VSCode CMake Modern C/C++ Template 🚀

### Quick Start

https://github.com/user-attachments/assets/a4ea71f7-7e01-4d77-a4cb-1dbc4ab33088

```bash
sudo apt-get update
sudo apt-get install build-essential manpages-dev
git clone https://github.com/tomasmark79/MarkWareVCMake
cd MarkWareVCMake/
code .
```

In workspace ./Standalone/Source/Main.cpp:

```cpp
#include <VCMLib/VCMLib.hpp>
#include <vcmlib/version.h>

#include <iostream>

// Start here
// 👉 ./ProjectRenamer.sh <old_lib_name> <new_lib_name> <old_standalone_name> <new_standalone_name>
// 👉 build 🔨 your new standalone app CTRL + ALT + N

// Description
// It is the first file that gets compiled and linked into the final executable.
// This is the main entry point for the standalone application.
// It includes the VCMLib header file and creates an instance of the VCMLib class.

auto main(int argc, char **argv) -> int
{
    VCMLib Lib;
    std::cout << "Version: " << VCMLIB_VERSION << std::endl;

    return 0;
}
```

### Project Overview
A project that takes the best ideas from worlds like VSCode, CMake, CPM, ModernAppStarter, and C++.

### This C++ template consists of two projects:
- A C++ library
- A C++ application that links with the library
  
**Together, they form one solution.**

### Briefly about the template
This project structure offers exceptional capabilities and flexibility, combining the best features from multiple sources. New components, additional libraries, and more can be easily integrated. It is a modern C++ project with a CMake configurator, maintaining compatibility to link with C if necessary. The template is configured with CMake and enhanced with the CPM Packaging System, allowing us to leverage modern project management capabilities in C/C++.

One of the key features of this template is its preparation for cross-compilation with support for Raspberry Pi 4. For cross-compilation, you will need to build your own toolchain.

Another important feature of this template is its built-in build system and CMake control, integrated into VSCode. The instructions are included in the template and are very straightforward. Simply clone the repository from GitHub into a folder, open it in VSCode, and compile with the native compiler immediately. Everything can be set up within minutes.

I look forward to seeing your contributions!

Currently, only Linux is supported. As soon as I get to Windows or Mac, or someone contributes, we will create extensions for these OS as well.

### Implemented Features ✅Project renamer

- CMake modules
- Native code debug 🐞
- Native compilation
- Cro- ss compilation
- Configuration
- Build
- Install
- Test
- Lint whole project
- Clang-format for the whole project
- CMake-format for the whole project

### ToDo
- Tests

### Rules
- FileNamesAndFoldersWithCapitalsIsGoodPractice
- No rules, only freedom

### Configuration ⚙️

#### Properties

Cache for CPM headers required in project

`.vscode/c_cpp_properties.json`

#### Implemented Tasks 🛠️

A major part of a lightweight yet robust CMake toolchain mechanism

`.vscode/tasks.json`

#### Debugger configuration 🐞

Debug Targets. You should to edit path to your Standalone target

`.vscode/launch.json`

#### ToolChain helper 🔧

Cross Compile Helper for CMake ToolChain selection

`cmake_configure.sh`

#### Keyboard shortcuts giving the comfort to this project ⌨️

- Ctrl+Alt+  C  configure Lib
- Ctrl+Alt+  S  configure Standalone

- Ctrl+Alt+  B  **build** Lib
- Ctrl+Alt+  N  **build** Standalone

- Ctrl+Alt+  L  clean Lib
- Ctrl+Alt+  K  clean Standalone

- Ctrl+Alt+  I  install Lib
- Ctrl+Alt+  J  install Standalone

- Ctrl+Alt+  T  test Lib
- Ctrl+Alt+  U  test Standalone

- Ctrl+Alt+  R  lint
- Ctrl+Alt+  F  format
- Ctrl+Alt+  M  cmake-format

`~/.config/Code/User/keybindings.json`

### Thanks 🙏

*to all the awesome people who share the same mindset as me*

### and thanks to those 🌟

GitHub CoPilot
https://github.com

Kitware - CMake
https://cmake.org

VSCode IDE
https://code.visualstudio.com/license

Modern Cpp Starter
https://github.com/TheLartians/ModernCppStarter

Copyright (c) 2019-2022 Lars Melchior and contributors
https://github.com/cpm-cmake/CPM.cmake

### About me 👨‍💻

"The result of hundreds of hours (two weeks straight) of incredible fun. Time seemed to stand still. The outcome is a template that takes C++ development to a whole new level.
    
"Buy me a coffee ☕🍵 or spare some time. 🙂"

```
paypal.me/TomasMark
Bitcoin: 3JMZR6SQo65kLAxxxXKrVE7nBKrixbPgSZ
Ethereum: 0x7a6C564004EdecFf8DD9EAd8bD4Bbc5D2720BeE7
```

Thank you, Tomáš Mark.
