# rpi4-toolchain.cmake

# Set system name and processor
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Define sysroot
set(CMAKE_SYSROOT /home/tomas/rpi-rootfs)

# Specify cross-compilers
set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)
set(CMAKE_ASM_COMPILER aarch64-linux-gnu-as)
set(CMAKE_LINKER aarch64-linux-gnu-ld)

# Add architecture definitions without duplication
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=armv8-a --sysroot=${CMAKE_SYSROOT} -D__aarch64__ -D__ARM_ARCH__=8")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv8-a --sysroot=${CMAKE_SYSROOT} -D__aarch64__ -D__ARM_ARCH__=8")
#set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -march=armv8-a --sysroot=${CMAKE_SYSROOT} -Wa,-mimplicit-it=thumb")

# Set CMake find modes
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Enable ASM language
# enable_language(ASM)