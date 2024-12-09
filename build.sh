#!/bin/bash


# x86_64
rm -rf ./build/AMD_x86_64/
cmake -B ./build/AMD_x86_64/ .
cmake --build ./build/AMD_x86_64/ -- -j"$(nproc)"

# aarch64
rm -rf ./build/aarch64/
cmake -B ./build/aarch64/ . -DCMAKE_TOOLCHAIN_FILE=./aarch64.cmake
cmake --build ./build/aarch64/ -- -j"$(nproc)"
