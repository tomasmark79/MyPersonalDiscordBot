#!/bin/bash
clear
rm -rf build-aarch64/ 
cmake -B build-aarch64/ -DCMAKE_TOOLCHAIN_FILE=../../aarch64.cmake
cmake --build build-aarch64/ -- -j$(nproc)
