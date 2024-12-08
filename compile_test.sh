#!/bin/bash

export PKG_CONFIG_PATH=/home/tomas/dev/cpp/projects/mydiscordbot/build-aarch64/_deps/libunistring-install/lib/pkgconfig:$PKG_CONFIG_PATH

/home/tomas/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi4-linux-gnu-gcc test_unistring.c \
-o test_unistring \
-I/home/tomas/dev/cpp/projects/mydiscordbot/build-aarch64/_deps/libunistring-install/include \
-I/home/tomas/dev/cpp/projects/mydiscordbot/include \
-L/home/tomas/dev/cpp/projects/mydiscordbot/build-aarch64/_deps/libunistring-install/lib \
-lunistring -static