#!/bin/bash
cd /home/tomas/dev/cpp/projects/mydiscordbot/
rm -rf build/
cmake -B build/ .
cmake --build ./build/ -- -j$(nproc)
cmake --build ./build/ -- -j$(nproc)
cd standalone
rm -rf build/
cmake -B build/ .
cmake --build ./build/ -- -j$(nproc)
cmake --build ./build/ -- -j$(nproc)
