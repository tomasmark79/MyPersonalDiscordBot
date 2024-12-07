#!/bin/bash
cd /home/tomas/dev/cpp/projects/mydiscordbot/
rm -rf build-aarch64/
cmake -B build-aarch64/ -DCMAKE_TOOLCHAIN_FILE=../aarch64.cmake
cmake --build build-aarch64/ -- -j$(nproc)
cmake --build build-aarch64/ -- -j$(nproc)
cd standalone
rm -rf build-aarch64/
cmake -B build-aarch64/ -DCMAKE_TOOLCHAIN_FILE=../../aarch64.cmake
cmake --build build-aarch64/ -- -j$(nproc)
cmake --build build-aarch64/ -- -j$(nproc)
