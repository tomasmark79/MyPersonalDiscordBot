# commands
# $ rm -rf build-aarch64/
# $ cmake -B build-aarch64/ -DCMAKE_TOOLCHAIN_FILE=aarch64.cmake
# $ cmake --build build-aarch64/ -- -j16


# Set system name and processor
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Define sysroot
set(CMAKE_SYSROOT /home/tomas/rpi-rootfs/)

# Specify cross-compilers v14
set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)
set(CMAKE_ASM_COMPILER aarch64-linux-gnu-as)
set(CMAKE_LINKER aarch64-linux-gnu-ld)

# where is the CMAKE_FIND_ROOT_PATH target environment located
set(CMAKE_FIND_ROOT_PATH ${CMAKE_SYSROOT})

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)


message(STATUS "Using sysroot: ${CMAKE_SYSROOT}")
message(STATUS "Using C compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Using C++ compiler: ${CMAKE_CXX_COMPILER}")

