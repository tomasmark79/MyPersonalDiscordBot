set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Cesty ke crosskompilátoru
set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)
set(CMAKE_LINKER aarch64-linux-gnu-ld)

# Rootfs pro knihovny a hlavičky
set(CMAKE_SYSROOT /home/tomas/rpi-rootfs)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Architektura
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=armv8-a --sysroot=${CMAKE_SYSROOT}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv8-a --sysroot=${CMAKE_SYSROOT}")
