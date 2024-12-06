# My Discord Bot

need huge todo for docs

This repository provides Not Just So Simple CMake project configuration for setting up and building a Discord bot server using the D++ framework. It includes a basic implementation to help you get started quickly. Unfortunately it is also my crosscompilation excercise so it could be litlle bit confusing. Sorry for now.


Project may be configured natively. 
Project may be compiled natively.

Cross-compilation is supported with attached aarch64 toolchain aarch64.cmake.
zlib is neccessary to install to aarch64-sysroot

```
rm -rf build-aarch64/
cmake -B build-aarch64/ -DCMAKE_TOOLCHAIN_FILE=aarch64.cmake

# openssl compilation is side running so from this reason we need to run make twice
cmake --build build-aarch64/ -- -j$(nproc)
```

links to sort
https://github.com/crosstool-ng/crosstool-ng/tree/crosstool-ng-1.25.0
https://cmake.org/cmake/help/book/mastering-cmake/chapter/Cross%20Compiling%20With%20CMake.html#finding-external-libraries-programs-and-other-files
https://github.com/jimmy-park/openssl-cmake
https://github.com/janbar/openssl-cmake


