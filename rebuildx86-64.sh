#!/bin/bash

# x86-64
rm -rf ./build/x86-64/
cmake -B ./build/x86-64/ .
cmake --build ./build/x86-64/ -- -j"$(nproc)"

# # aarch64
# rm -rf ./build/aarch64/
# cmake -B ./build/aarch64/ . -DCMAKE_TOOLCHAIN_FILE=./aarch64.cmake
# cmake --build ./build/aarch64/ -- -j"$(nproc)"
