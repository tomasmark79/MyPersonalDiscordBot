# My Discord Bot

This repository provides a simple CMake project configuration for setting up and building a Discord bot server using the D++ framework. It includes a basic implementation to help you get started quickly.


crosscompilation toolchain for rpi4
```
cmake -B build-aarch64/ -DCMAKE_TOOLCHAIN_FILE=aarch64.cmake -DCMAKE_VERBOSE_MAKEFILE=ON
cmake --build build-aarch64/ -- -j16
```