# My Personal Discord Bot

is using 👇

---

# MarkWare VCMake Template 🎁
v0.0.4

### Brief Description 😊

This solution represents a **complete workflow** for **modern** C/C++ software development. It integrates technologies such as **VSCode**, **Conan**, **CMake**, **CPM.cmake**, **ModernCppStarter**, **TemplateRenamer**, **Formatters**, and more into a single functional unit. It allows you to create a **Standalone Application** and a **library** *immediately*. 🎉

### Integrated Configurations 🔧

- **VSCode** is an indispensable editor, ranking first due to its flexibility and configurability.
- **Tasks** are jobs that build a robust system using **Conan** and **CMake**.
- **CMake**, as a modern configurator with object-oriented elements, provides enormous flexibility.
- **CPM.cmake** adds simplified support for fetching packages from GitHub, ensuring an easier way to obtain such packages.
- **Conan 2**, which manages dependencies, is the cherry on top 🍒, allowing you to easily add libraries that your project may need.
- **ModernCppStarter** is a project structure proven over many years and projects for developing programs and libraries. The essence of this structure is also embedded in this project.
- **Formatters** are simple scripts that quickly reformat C/C++ and CMake files.

### Integrated tasks

```txt
                            [ for Library and Standalone at once]
    "Build 🔨",             - CMake: --build --target all
    "Rebuild 🧹⚔️⚙️🔨",       - all steps at once (clean, conan, configure, build)
    
    "Configure ⚙️",          - CMake: -S -B
    "Conan ⚔️",              - Conan: install
    "Clean 🧹",             - rm -rf respective folder
    "Install 📌",           - CMake: --build --target install
    "Licenses 📜",          - CMake: --build --target write-licenses

                            [ the same as above but splited for only Standalone or Lib ]
    "Build Standalone",     
    "Rebuild Standalone",
    "Configure Standalone",
    "Conan Standalone",
    "Clean Standalone",
    "Install Standalone",
    "Licenses Standalone",
                            
    "Build Library",
    "Rebuild Library",
    "Configure Library",
    "Conan Library",
    "Clean Library",
    "Install Library",
    "Licenses Library",
```                

### Video presentation
Automatic translated subtitles are available.

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/9koSyjwtRUA/0.jpg)](https://www.youtube.com/watch?v=9koSyjwtRUA)

### Screen shot of menu selector
<div style="text-align:center">
  <img width="773" alt="image" src="https://github.com/user-attachments/assets/edfaab22-feb2-4c69-89bc-908501e9252e" />
</div>


### My Goal 🎯

To create a project template for myself that is flexible, works out of the box, and saves me a lot of time.

### The Result of My Efforts 🚀

Is a modular and intelligently designed project structure that gives me enormous flexibility and decision-making power at every point on how the project will be configured. For others, it may take a while to get used to the project, but in return, you will be pleasantly surprised at how simple it actually is. 😄

### Project Requirements 🛠️

 - Linux OS - I'm developing this project on latest Kubuntu 24.04.1 
 - Mac OS - supposedly works out of the box ( Thanks to Sleepy Monax )
 - VSCode - https://code.visualstudio.com
 - CMake - https://cmake.org/download/
 - Python3 - https://www.python.org/downloads/
 - Conan2 - https://docs.conan.io/2/installation.html
 - Compilers - https://gcc.gnu.org, https://clang.llvm.org, ...
 - cmake-formatter - https://cmake-format.readthedocs.io/en/latest/
 - clang-formatter - https://clang.llvm.org/docs/ClangFormat.html
 - cross-compiler toolchain and a sysroot - https://crosstool-ng.github.io

### Quick Start for Debian-based Linux

#### Make changes to your Linux OS environment only if you know what you are doing!

```bash
sudo apt update && sudo apt upgrade -y
sudo apt install -y build-essential cmake curl wget git ninja-build python3 python3-pip gcc g++ clang clang-format autoconf bison flex gperf texinfo help2man gawk libtool-bin

# VSCode
wget -qO- https://code.visualstudio.com/sha/download?build=stable&os=linux-deb-x64 -O vscode.deb
sudo apt install ./vscode.deb

# Conan
pip3 install conan

# CMake formatting script
pip3 install cmake-format

# Crosstool-NG
git clone https://github.com/crosstool-ng/crosstool-ng.git
cd crosstool-ng
./bootstrap
./configure --prefix=/usr/local
make
sudo make install
cd ..

# Validate installations
echo "Validate of installations:"
cmake --version
python3 --version
conan --version
gcc --version
clang-format --version
cmake-format --version
```

### Finally, clone the MarkWare VCMake Template 💣

```bash
# clone 
git clone https://github.com/tomasmark79/MarkWareVCMake ./NameOfMyAwesomeApp
cd MarkWareVCMake/

# Start VSCode
code .
```

### TODO by Priority ✅

- 🚧 Workflow processing if Build and no Config is existing, etc. 🚧
- Extract the commands currently generated to allow working only in CLI if needed
- Port to Windows (it will likely be necessary to convert the shell script to PowerShell)
- Port to Mac (I am currently completely lost here and looking for a contributor to help me with this) 🍎
- Later, when I find that I need it, we will add testing options
- There are other possibilities like sanitizers implemented by CMake, but that will come later

### Project Documentation

I thought about how best to guide a newcomer to try this project. The simplest way is to explain everything at the level of individual parts of the project.

### Project Structure

```txt
.
└── .vscode
│   ├── c_cpp_properties.json
│   ├── keybindings.json
│   ├── launch.json
│   ├── settings.json
│   └── tasks.json
├── aarch64.cmake
├── .clang-format
├── cmake
│   ├── CPM.cmake
│   ├── Dependencies.cmake
│   ├── Modules
│   │   └── FindX11.cmake
│   └── tools.cmake
├── CMakeController.sh
├── CMakeLists.txt
├── CMakeUserPresets.json
├── conanfile.py
├── conanfile.txt
├── include
│   └── VCMLib
│       └── VCMLib.hpp
├── LICENSE
├── README.md
├── Source
│   └── VCMLib.cpp
├── Standalone
│   ├── CMakeLists.txt
│   ├── LICENSE
│   └── Source
│       └── Main.cpp
└── TemplateRenamer.sh
```

##### Project Structure Concept

The main folder contains the library, which is used by the standalone application located in the **/Standalone** folder. This setup assumes working with two separate projects: the library and the application that calls it.

##### Description of Individual Parts

```txt
└── .vscode
│   ├── c_cpp_properties.json
│   ├── keybindings.json
│   ├── launch.json
│   ├── settings.json
│   └── tasks.json
```
`c_cpp_properties.json` defines the IntelliSenseMode configuration for the C/C++ extension by Microsoft in VSCode.

`keybindings.json` is a template for setting up the keyboard shortcuts I use. This file will not work if it is only in this folder. If you want to use these keyboard shortcuts, you need to transfer the contents of this file to the system settings where a file with the same name is located.

`launch.json` is the configuration and settings for the Debugger launch process. It sets the path to the launch system of the Standalone application. Most often, it will be useful to direct GDB to `${workspaceFolder}/Build/Standalone/Native/Debug/VCMStandalone`.

`settings.json` is created automatically.

`tasks.json` defines everything related to launch tasks in VSCode. It creates a clear menu for selecting tasks and also calls the shell script `CMakeController.sh`, together forming a whole that provides comfort in controlling the configuration and building of the project.

`├── aarch64.cmake`

This is a CMake toolchain for cross-compilation. It is not primarily used in the default settings. It is here in case you want to try to force CMake to manually cross-compile directly from CMake without installing Conan 2.

`├── .clang-format`

This file defines how the formatting of C/C++ files will look throughout the project, including subfolders.

```
├── cmake
│   ├── CPM.cmake
│   ├── Dependencies.cmake
│   ├── Modules
│   │   └── FindX11.cmake
│   └── tools.cmake
```

This section contains definitions for CMake itself. Essentially, only `Dependencies.cmake` is user-editable, where I have left space for defining dependencies based on CPM.cmake packages.

Similarly, the `Modules` folder can contain the definition of CMake modules.

Other files are configuration parts of the project and should not be edited.

`├── CMakeController.sh`

This is a shell script that mediates all operations coming from VSCode tasks. It is responsible for the processes under the hood. If you look under the hood, you will find that the file structure is very readable and simple.

`├── .cmake-format`

This file defines how the formatting of *.cmake files will look throughout the project, including subfolders.

`├── CMakeLists.txt`

This main CMake file is the main file of the library itself. It is in the root of the project. In this file, you define dependencies. I definitely recommend diving deeper and reading the entire configuration file. According to the comments in the code, it is easy to find parts that may interest you.

`CMakeUserPresets.json`

Automatically generated and not important for us at this moment.

```txt
├── conanfile.py
├── conanfile.txt
```

These are configuration files for Conan 2. The text file is simpler and more straightforward, and you will usually suffice with it. The file with the `.py` extension is a more complex and dynamic version of the Conan 2 configuration file. It is up to you which version you will ultimately use. For more information on what Conan is: https://docs.conan.io/2/index.html

```txt
├── include
│   └── VCMLib
│       └── VCMLib.hpp
```

This is the main interface of the library. The header file hpp, which is included in the main application as a connection point.

`├── LICENSE`

Contains the license.

`.python-version`

Since Conan 2 is a Python application, it is necessary to have Python installed on the system. And since it is generally recommended to have virtual environment variables for different versions of Python on the system, this file specifies which version of Python will be used when running the Python script. I use the pyenv project to manage Python versions. https://github.com/pyenv/pyenv.

`├── README.md`

Contains the information you are currently reading.

```txt
├── Source
│   └── VCMLib.cpp
```

This is the main interface of the library. The implementation file cpp, which belongs to the header file with the same name.

```
├── Standalone  
│   ├── CMakeLists.txt
│   ├── LICENSE
│   └── Source
│       └── Main.cpp
```

The entire Standalone folder is a separate project. It is an application. An application that links the library, which is one level higher in this file system. It contains the same as the library. Only the configuration differs. It contains the entry C++ point in the implementation file `Main.cpp`, where the function `int main()` is located.

**It is important to understand that from the perspective of CMake configuration, this is a different project than the one that is one level higher in the file system.**

`└── TemplateRenamer.sh`

This shell script is a very powerful renamer of the entire project. After cloning the repository into your folder, you can use this script to create your own name for both the library and the application. The names must not be same.

```bash
Usage: ./TemplateRenamer.sh <old_lib_name> <new_lib_name> <old_standalone_name> <new_standalone_name>
```
  
### Code Codex

I am using 🐫amel🐫ode🐫apitals.  
One exception: No capital letter in the "include" folder is intentional!


### Acknowledgments to Industry Professionals

Use these links to get more documentation on the technologies used in my template.

https://cmake.org

https://github.com/TheLartians/ModernCppStarter

https://github.com/cpm-cmake/CPM.cmake

https://github.com/cpm-cmake/CPMLicenses.cmake.git

---

### About Me 👨‍💻

"The result of a lot of hours of incredible fun. Time seemed to stand still. The outcome is a template that takes C++ development to a whole new level. 
    
"Buy me a coffee ☕🍵 or spare some time. 🙂"

Tomáš Mark 2024

```
paypal.me/TomasMark
Bitcoin: 3JMZR6SQo65kLAxxxXKrVE7nBKrixbPgSZ
Ethereum: 0x7a6C564004EdecFf8DD9EAd8bD4Bbc5D2720BeE7
```

I look forward to seeing your contributions!

### License
I built the project primarily for myself and for my future projects. Nevertheless, if we use the project, we should adhere to the licensing policy. Therefore, I have implemented the package `CPMLicenses.cmake`, which automatically scans all source directories of your CPM.cmake dependencies and finds any file that starts with LICENSE or LICENCE, appending the content to an output file that you can use as a license disclaimer. If no license is found for a package, a warning will be issued in the output during license collection.

