#!/bin/bash


# x86_64
rm -rf ./standalone/AMD_x86_64/
cmake -B ./standalone/AMD_x86_64/ .
cmake --build ./standalone/AMD_x86_64/ -- -j"$(nproc)"

# aarch64
rm -rf ./standalone/aarch64/
cmake -B ./standalone/aarch64/ . -DCMAKE_TOOLCHAIN_FILE=./aarch64.cmake
cmake --build ./standalone/aarch64/ -- -j"$(nproc)"
