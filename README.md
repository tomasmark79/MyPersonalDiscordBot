# MarkWare VCMake Template

### Modern, Configurable Project Template for C and C++

Author: **Tomáš Mark**  
Version: **0.0.11**

[![Ubuntu](https://github.com/tomasmark79/MarkWareVCMake/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/tomasmark79/MarkWareVCMake/actions/workflows/ubuntu.yml)
[![MacOS](https://github.com/tomasmark79/MarkWareVCMake/actions/workflows/macos.yml/badge.svg)](https://github.com/tomasmark79/MarkWareVCMake/actions/workflows/macos.yml)
[![Windows](https://github.com/tomasmark79/MarkWareVCMake/actions/workflows/windows.yml/badge.svg)](https://github.com/tomasmark79/MarkWareVCMake/actions/workflows/windows.yml)
---

<img width="189" alt="image" src="https://github.com/user-attachments/assets/df0f7209-aaec-4c51-a434-4455344e0d57" />

---

## Introduction

🌟🌟🌟  

The **MarkWare VCMake Template** provides a modern solution for C and C++ development by combining **application** and **library** workflows within a single configurable template. Designed for developers who value efficiency and modern tools, it simplifies project initialization while adhering to industry best practices. Built with **Modern CMake**, **Conan 2**, and **VSCode** integration, this template is an essential starting point for your next project.  

🌟🌟🌟

---

## Key Features

✨✨✨  
- **Quick Start**: Minimal setup required, ready to use immediately after cloning.  
- **Modern Standards**: Supports best practices for C and C++ development.  
- **Native Debugging**: Step-by-step debugging directly on Linux.  
- **Cross-Platform**: Runs natively on Linux 🐧, macOS 🍏, and Windows 🪟.
- **Cross-Compilation**: Easily target multiple architectures.  
- **Highly Customizable**: Modular structure tailored to your specific project needs.  

✨✨✨

---

## Integrated Tools and Configurations

### Development Tools

🌐🌐🌐  

- **Visual Studio Code**: Preconfigured for seamless development.  
  [https://code.visualstudio.com/](https://code.visualstudio.com/)
- **Modern CMake**: Advanced configuration and build management.  
  [https://cmake.org/download/](https://cmake.org/download/)
- **Pyenv**: Simplifies Python version management.  
  [https://github.com/pyenv/pyenv](https://github.com/pyenv/pyenv)
- **Python 3**: Integrated for scripting and automation.  
  [https://www.python.org/downloads/](https://www.python.org/downloads/)
- **Conan 2**: Simplifies dependency management.  
  [https://docs.conan.io](https://docs.conan.io)
- **ModernCppStarter**: Inspired by industry best practices for initializing C++ projects.  
  [https://github.com/TheLartians/ModernCppStarter](https://github.com/TheLartians/ModernCppStarter)
- **GitHub Action Workflows**: Actively monitors the source code status across all major platforms.
   [https://github.com/tomasmark79/MarkWareVCMake/actions](https://github.com/tomasmark79/MarkWareVCMake/actions)


🌐🌐🌐

### Additional Integrations

- **CPM.cmake**: Lightweight dependency management as the add-in if neccessary.  
  [https://github.com/cpm-cmake/CPM.cmake](https://github.com/cpm-cmake/CPM.cmake)  
- **CPM.license**: Automates third-party license management.  
  [https://github.com/cpm-cmake/CPMLicenses.cmake](https://github.com/cpm-cmake/CPMLicenses.cmake)
- **Formatters**: Preconfigured for consistent code formatting.  
  - [Clang Format](https://clang.llvm.org/docs/ClangFormat.html)  
  - [CMake Format](https://cmake-format.readthedocs.io/en/latest/) 
   

**Note:**
Combining Conan 2 and CPM.cmake is generally not recommended, but it is not prohibited either. If you approach the dependency management concept with Conan 2 as the primary dependency manager and CPM.cmake as a supplementary dependency manager, everything will be fine. Just make sure to watch out for conflicts.

🗡️🗡️🗡️

---

## Development Environment Setup

⚙️⚙️⚙️

### Linux 🐧 and macOS 🍏


1. Update system packages:
   ```bash
   sudo apt update && sudo apt upgrade -y
   sudo apt install cmake python3-pip curl git libssl-dev \
   libbz2-dev libcurses-ocaml-dev build-essential gdb libffi-dev \
   libsqlite3-dev liblzma-dev libreadline-dev libtk-img-dev
   ```

2. Install and configure **Pyenv**:
   ```bash
   curl https://pyenv.run | bash
   pyenv install 3.9.2
   pyenv virtualenv 3.9.2 env392
   pip install --upgrade pip
   ```

3. Install **Conan**:
   ```bash
   pip install conan
   conan profile detect --force
   ```  

### Windows native 🪟

1. Install and configure **Pyenv** for Windows:
   [Powershell Installation Steps](https://github.com/pyenv-win/pyenv-win/blob/master/docs/installation.md#powershell)  
    ```powershell
    pyenv install 3.9.2
    pyenv global 3.9.2
    pyenv local 3.9.2
    pip install --upgrade pip
    ```
3. Install **Conan**:
    ```powershell
    pip install conan
    conan profile detect --force
    ```  

### Windows 🪟 via WSL 🐧

1. Enable WSL and install Debian:
   ```powershell
   wsl --install
   wsl --list --online
   wsl --install Debian
   wsl --set-default-version 2
   shutdown /r
   ```
2. Install required VSCode extensions:
   - `ms-vscode-remote.remote-wsl`
   - `ms-vscode.cpptools`  
3. Connect to WSL and open the project in VSCode
   ```bash
   code .
   ```

---


## Quick Start

🚀🚀🚀  
1. Clone the template:
   ```bash
   git clone https://github.com/tomasmark79/MarkWareVCMake
   cd MarkWareVCMake/
   ```
2. Rename components:
   ```bash
   python SolutionRenamer.py VCMLib MyLibrary VCMStandalone MyStandalone
   ```
3. Open the project in VSCode:
   ```bash
   code .
   ```
4. File SolutionUpgrader.py can update the template files from the repository that you choose. More information inside the script.

From this point, you have a fully functional solution for developing Linux binaries, regardless of the host platform. 
 
🚀🚀🚀

---

## Preconfigured Architectures

🌍🌍🌍  

- `Default` (automatic system default compiler toolchain selection)  
- `x86_64-unknown-linux-gnu` (requires cross-compilation toolchain)  
- `x86_64-w64-mingw32` (requires cross-compilation toolchain)  
- `aarch64-linux-gnu` (requires cross-compilation toolchain)  

Je jednoduché přidat novou architekturu.

🌍🌍🌍

---

## Build Types

🏗️🏗️🏗️  
- `Debug`
- `Release`
- `RelWithDebInfo`
- `MinSizeRel`  

🏗️🏗️🏗️

---

## Project Structure

📂📂📂  

```txt
.
├── cmake
│   ├── Modules
│   │   └── FindX11.cmake
│   ├── CPM.cmake
│   └── tools.cmake
├── .github
│   └── workflows
│       ├── install.yml
│       ├── macos.yml
│       ├── ubuntu.yml
│       └── windows.yml
├── include
│   └── VCMLib
│       └── VCMLib.hpp
├── Source
│   └── VCMLib.cpp
├── Standalone
│   ├── Source
│   │   └── Main.cpp
│   ├── CMakeLists.txt
│   └── LICENSE
├── Utilities
│   ├── CMakeToolChains
│   │   ├── aarch64-linux-gnu.cmake
│   │   ├── x86_64-unknown-linux-gnu.cmake
│   │   └── x86_64-w64-mingw32.cmake
│   ├── ConanProfiles
│   │   ├── aarch64-linux-gnu
│   │   ├── x86_64-unknown-linux-gnu
│   │   └── x86_64-w64-mingw32
│   └── AboutThisFolder.md
├── .vscode
│   ├── c_cpp_properties.json
│   ├── keybindings.json
│   ├── launch.json
│   ├── settings.json
│   └── tasks.json
├── .clang-format
├── .cmake-format
├── CMakeLists.txt
├── conanfile.py
├── .gitattributes
├── .gitignore
├── LICENSE
├── .python-version
├── README.md
├── SolutionController.py
├── SolutionRenamer.py
└── SolutionUpgrade.py
```  

📂📂📂

---

## Implemented VSCode Tasks

### Task Menu (Shift + F7)  

🛠️🛠️🛠️  

| Task Menu             | Description                             |
|-----------------------|-----------------------------------------|
| **Zero to Hero**      | Clean → Conan → Configure → Build       |
| **Clean**             | Removes the entire build folder         |
| **Conan**             | Builds Conan dependencies               |
| **Configure**         | Configures CMake                        |
| **Build**             | Builds the project                      |
| **Collect Licenses**  | Gathers licenses from CPM dependencies  |
| **Install Artefacts** | Installs to `/Build/Installed/`         |
| **Release Artefacts** | Tarballs to `/Build/Artefacts/`         |
| **Conan graph.html**  | Create html output of dependencies      |
| **Lint C/C++**        | C/C++ files diagnostics                 |
| **Format C/C++**      | Formatting for C/C++ files              | 
| **Format CMake**      | Formatting for CMake files              |

| Special Task Menu     | Description                             |
|-----------------------|-----------------------------------------|
| **Permutate All Tasks**  | Executes all task scenarios (testing purpose) |

### Key Shortcuts

- **F5**: Start debugging.
- **F7**: Build native debug configuration.
- **Shift + F7**: Task Menu
- **Shift + Ctrl + S**: Special Task Menu
- **Ctrl + Alt + M**: Format all CMake files.
- **Ctrl + Alt + F**: Format all C++ files.
- **Ctrl + Alt + L**: Lint all C++ files.
- **Ctrl + Shift + Alt + B**: Run ShellCheck on bash scripts.  

🧮

---

## Command Line

Of course, the recommended approach is to control the project workflow using the recommended method through tasks and menus in VSCode.

For completeness and troubleshooting, I also present the command line commands here, which can be used at any time as needed.


#### **Native** default build Debug 

```bash
Remove: Build/Library/default/Debug
Remove: Build/Standalone/default/Debug
conan install "/home/tomas/dev/cpp/projects/MarkWareVCMake" --output-folder="Build/Library/default/Debug" --build=missing --profile=default --settings=build_type=Debug -o *:shared=False
conan install "/home/tomas/dev/cpp/projects/MarkWareVCMake" --output-folder="Build/Standalone/default/Debug" --build=missing --profile=default --settings=build_type=Debug -o *:shared=False
source "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Library/default/Debug/conanbuild.sh" && cmake -S "." -B "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Library/default/Debug" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Install/default/Debug"
cmake -S "." -B "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Library/default/Debug" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Install/default/Debug"
source "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Standalone/default/Debug/conanbuild.sh" && cmake -S "./Standalone" -B "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Standalone/default/Debug" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Install/default/Debug"
cmake -S "./Standalone" -B "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Standalone/default/Debug" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Install/default/Debug"
cmake --build "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Library/default/Debug" -j 16
cmake --build "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Standalone/default/Debug" -j 16
cmake --build "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Library/default/Debug" --target write-licenses -j 16
cmake --build "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Standalone/default/Debug" --target write-licenses -j 16
cmake --build "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Library/default/Debug" --target install -j 16
cmake --build "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Standalone/default/Debug" --target install -j 16
```

#### Release **Cross** build to **x86_64-w64-mingw32** 

```bash
Remove: Build/Library/x86_64-w64-mingw32/Release
Remove: Build/Standalone/x86_64-w64-mingw32/Release
conan install "/home/tomas/dev/cpp/projects/MarkWareVCMake" --output-folder="Build/Library/x86_64-w64-mingw32/Release" --build=missing --profile=x86_64-w64-mingw32 --settings=build_type=Release -o *:shared=False
conan install "/home/tomas/dev/cpp/projects/MarkWareVCMake" --output-folder="Build/Standalone/x86_64-w64-mingw32/Release" --build=missing --profile=x86_64-w64-mingw32 --settings=build_type=Release -o *:shared=False
source "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Library/x86_64-w64-mingw32/Release/conanbuild.sh" && cmake -S "." -B "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Library/x86_64-w64-mingw32/Release" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Install/x86_64-w64-mingw32/Release"
cmake -S "." -B "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Library/x86_64-w64-mingw32/Release" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Install/x86_64-w64-mingw32/Release"
source "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Standalone/x86_64-w64-mingw32/Release/conanbuild.sh" && cmake -S "./Standalone" -B "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Standalone/x86_64-w64-mingw32/Release" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Install/x86_64-w64-mingw32/Release"
cmake -S "./Standalone" -B "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Standalone/x86_64-w64-mingw32/Release" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Install/x86_64-w64-mingw32/Release"
cmake --build "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Library/x86_64-w64-mingw32/Release" -j 16
cmake --build "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Standalone/x86_64-w64-mingw32/Release" -j 16
cmake --build "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Library/x86_64-w64-mingw32/Release" --target write-licenses -j 16
cmake --build "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Standalone/x86_64-w64-mingw32/Release" --target write-licenses -j 16
cmake --build "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Library/x86_64-w64-mingw32/Release" --target install -j 16
cmake --build "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Standalone/x86_64-w64-mingw32/Release" --target install -j 16
```

####  MinSizeRel **Cross** build to **aarch64-linux-gnu**

```bash
Remove: Build/Library/aarch64-linux-gnu/MinSizeRel
Remove: Build/Standalone/aarch64-linux-gnu/MinSizeRel
conan install "/home/tomas/dev/cpp/projects/MarkWareVCMake" --output-folder="Build/Library/aarch64-linux-gnu/MinSizeRel" --build=missing --profile=aarch64-linux-gnu --settings=build_type=MinSizeRel -o *:shared=False
conan install "/home/tomas/dev/cpp/projects/MarkWareVCMake" --output-folder="Build/Standalone/aarch64-linux-gnu/MinSizeRel" --build=missing --profile=aarch64-linux-gnu --settings=build_type=MinSizeRel -o *:shared=False
source "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Library/aarch64-linux-gnu/MinSizeRel/conanbuild.sh" && cmake -S "." -B "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Library/aarch64-linux-gnu/MinSizeRel" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=MinSizeRel -DCMAKE_INSTALL_PREFIX="/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Install/aarch64-linux-gnu/MinSizeRel"
cmake -S "." -B "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Library/aarch64-linux-gnu/MinSizeRel" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=MinSizeRel -DCMAKE_INSTALL_PREFIX="/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Install/aarch64-linux-gnu/MinSizeRel"
source "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Standalone/aarch64-linux-gnu/MinSizeRel/conanbuild.sh" && cmake -S "./Standalone" -B "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Standalone/aarch64-linux-gnu/MinSizeRel" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=MinSizeRel -DCMAKE_INSTALL_PREFIX="/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Install/aarch64-linux-gnu/MinSizeRel"
cmake -S "./Standalone" -B "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Standalone/aarch64-linux-gnu/MinSizeRel" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=MinSizeRel -DCMAKE_INSTALL_PREFIX="/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Install/aarch64-linux-gnu/MinSizeRel"
cmake --build "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Library/aarch64-linux-gnu/MinSizeRel" -j 16
cmake --build "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Standalone/aarch64-linux-gnu/MinSizeRel" -j 16
cmake --build "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Library/aarch64-linux-gnu/MinSizeRel" --target write-licenses -j 16
cmake --build "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Standalone/aarch64-linux-gnu/MinSizeRel" --target write-licenses -j 16
cmake --build "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Library/aarch64-linux-gnu/MinSizeRel" --target install -j 16
cmake --build "/home/tomas/dev/cpp/projects/MarkWareVCMake/Build/Standalone/aarch64-linux-gnu/MinSizeRel" --target install -j 16
```





---

### Comparison Overview to Similar Templates
|                                             | MarkWareVCMake                         | ModernCppStarter | cmake_template                    |
|---------------------------------------------|----------------------------------------|------------------|-----------------|
| Minimal setup required                      | yes                                    | yes              | yes             |
| Supports best practices + Modern CMake      | yes                                    | yes              | yes             |
| Stanadlone->Library concept                 | yes                                    | yes              | yes             |
| Highly Customizable                         | yes                                    | yes              | yes             |
| Github workflow with badges                 | yes                                    | yes              | not sure        |
| PackageProject.cmake                        | yes                                    | author           | no              |
| Dependency solution CPM.cmake integrated    | yes                                    | author           | no              |
| CPM.license integrated                      | yes                                    | author           | no              |
| CPM.tools integrated                        | yes                                    | author           | no              |
| LintC, clang-format, cmake-format           | VSCode Tasks + shortcuts + cli         | only cli         | no              |
| Solution Renamer                            | yes                                    | no               | no              |
| Dependency solution by Conan                | yes, wrapped by tasks in VSCode        | no               | no              |
| CMake generators by Conan preconfigured     | yes                                    | no               | no              |
| Cross-Compilation preconfigured             | yes, require toolchain                 | no               | no              |
| Cross-Compilation targets preconfigured     | linux, windows, raspberry pi 4/5       | no               | no              |
| VSCode CMake controller                     | yes                                    | no               | no              |
| VSCode Tasks via Menu and Shortcuts         | yes                                    | no               | no              |
| Clean                                       | Removes the entire build folder        | no               | no              |
| Conan                                       | Builds Conan dependencies              | no               | no              |
| Configure                                   | Configures CMake                       | only cli         | only cli        |
| Build                                       | Builds the project                     | only cli         | only cli        |
| Collect Licenses                            | Gathers licenses from CPM dependencies | no               | no              |
| Install Artefacts                           | Installs to /Build/Installed/          | no               | no              |
| Release Artefacts                           | Tarballs to /Build/Artefacts/          | no               | no              |
| Lint C/C++                                  | C/C++ files diagnostics                | only cli         | only cli        |
| Format C/C++                                | Recursive formatting for C/C++ files   | only cli         | only cli        |
| Format CMake                                | Recursive formatting for CMake files   | only cli         | only cli        |
| Permutate All Tasks                         | Executes all task scenarios (testing)  | no               | no              |
| Loging runned commands                      | yes, to file                           | no               | no              |
| C/C++ tests                                 | not yet                                | yes              | yes             |
| Doxygen                                     | not yet                                | yes              | no              |

---

## License

This template is licensed under MIT License.  
