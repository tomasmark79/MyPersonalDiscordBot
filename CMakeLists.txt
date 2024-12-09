cmake_minimum_required(VERSION 3.14...3.22)

# cross compile command
# clear && rm -rf build-aarch64/ && cmake -B build-aarch64/ -DCMAKE_TOOLCHAIN_FILE=../aarch64.cmake
# cmake --build build-aarch64/ -- -j$(nproc)

# ---- Project ----
project(
    MyDiscordBotProject
    VERSION 0.0.2
    LANGUAGES C CXX ASM
)

set(CMAKE_BUILD_TYPE Debug)

# ---- Include guards ----
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR
        "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
    )
endif()

# ---- Compiler flags ----
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-deprecated-declarations")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")

# ---- Dependencies ----
include(cmake/CPM.cmake)
include(cmake/openssl-module.cmake)
include(cmake/libiconv-module.cmake)
include(cmake/libssh2-module.cmake)

CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.12.0")

# ---- Create library ----
file(GLOB_RECURSE headers CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
)

add_library(MyDiscordBotLib ${headers} ${sources})
set_target_properties(MyDiscordBotLib PROPERTIES
    CXX_STANDARD 17
)

target_compile_options(MyDiscordBotLib PUBLIC
    "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->" # Strict conformance
)

# libiconv
add_dependencies(MyDiscordBotLib build_libiconv)
target_include_directories(MyDiscordBotLib PRIVATE ${LIBICONV_INCLUDE_DIR})
target_link_libraries(MyDiscordBotLib PRIVATE ${LIBICONV_LIBRARY})

# libssh2
add_dependencies(MyDiscordBotLib build_libssh2)
target_include_directories(MyDiscordBotLib PRIVATE ${LIBSSH2_INCLUDE_DIR})
target_link_libraries(MyDiscordBotLib PRIVATE ${LIBSSH2_LIBRARY})

# dpp
CPMAddPackage(
    NAME dpp
    GITHUB_REPOSITORY brainboxdotcc/DPP
    VERSION 10.0.35
    OPTIONS
    "BUILD_SHARED_LIBS ON" # OFF = hpke issues
    "BUILD_VOICE_SUPPORT ON"
    "DPP_INSTALL ON"
    "DPP_BUILD_TEST OFF"
)
if(dpp_ADDED)
    add_dependencies(dpp OpenSSL::SSL OpenSSL::Crypto)
    target_include_directories(MyDiscordBotLib PUBLIC ${dpp_SOURCE_DIR}/include)
    target_link_libraries(MyDiscordBotLib PRIVATE dpp)
endif()

# EmojiTools
CPMAddPackage(
    NAME EmojiTools
    GIT_TAG main
    GITHUB_REPOSITORY tomasmark79/EmojiTools
    OPTIONS "EMOJI_INSTALL YES" # create an installable target
)
if(EmojiTools_ADDED)
    target_include_directories(MyDiscordBotLib PRIVATE ${EmojiTools_SOURCE_DIR}/include)
    target_link_libraries(MyDiscordBotLib PRIVATE EmojiTools::EmojiTools)
endif()

# self headers
target_include_directories(
    MyDiscordBotLib PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/MyDiscordBotLib-${PROJECT_VERSION}>
)

string(TOLOWER "MyDiscordBotLib/version.h" VERSION_HEADER_LOCATION)

packageProject(
    NAME MyDiscordBotLib
    VERSION ${PROJECT_VERSION}
    NAMESPACE MyDiscordBotLib
    BINARY_DIR ${PROJECT_BINARY_DIR}
    INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
    INCLUDE_DESTINATION include/MyDiscordBotLib-${PROJECT_VERSION}
    VERSION_HEADER "${VERSION_HEADER_LOCATION}"
    COMPATIBILITY SameMajorVersion
)

# include(cmake/opus-module.cmake)

# Start of libunistring ----------------------------------
# CPMAddPackage(
# NAME libunistring
# URL https://ftp.gnu.org/gnu/libunistring/libunistring-1.3.tar.gz
# DOWNLOAD_ONLY YES
# )
# if(libunistring_ADDED)
# set(LIBUNISTRING_SOURCE_DIR ${libunistring_SOURCE_DIR})
# set(LIBUNISTRING_BUILD_DIR ${libunistring_BINARY_DIR})
# set(LIBUNISTRING_INSTALL_DIR ${CMAKE_BINARY_DIR}/_deps/libunistring-install)
# file(MAKE_DIRECTORY ${LIBUNISTRING_BUILD_DIR})

# # Run the configuration step during the CMake configuration phase
# execute_process(
# COMMAND ./configure --host=${CMAKE_SYSTEM_PROCESSOR} CC=${CMAKE_C_COMPILER} CXX=${CMAKE_CXX_COMPILER} CPP=${CPP_CMD} CXXCPP=${CXXCPP_CMD} --prefix=${LIBUNISTRING_INSTALL_DIR}
# WORKING_DIRECTORY ${LIBUNISTRING_SOURCE_DIR}
# )

# add_custom_target(
# build_libunistring ALL
# COMMAND $$MAKE -j$$(nproc) -C ${LIBUNISTRING_SOURCE_DIR} && $$MAKE -C ${LIBUNISTRING_SOURCE_DIR} install
# )

# set(LIBUNISTRING_INCLUDE_DIR ${LIBUNISTRING_INSTALL_DIR}/include)
# set(LIBUNISTRING_LIBRARY ${LIBUNISTRING_INSTALL_DIR}/lib/libunistring.a)
# set(LIBUNISTRING_SHARED_LIBRARY ${LIBUNISTRING_INSTALL_DIR}/lib/libunistring.so)
# include_directories(${LIBUNISTRING_INSTALL_DIR}/include)
# link_directories(${LIBUNISTRING_INSTALL_DIR}/lib)
# endif()

# end of libunistring ------------------------------------

# # Start of libpsl ----------------------------------------
# CPMAddPackage(
# NAME libpsl
# URL https://github.com/rockdaboot/libpsl/releases/download/0.21.5/libpsl-0.21.5.tar.gz
# VERSION 0.21.5
# GIT_TAG 0.21.5
# OPTIONS "BUILD_SHARED_LIBS OFF" "BUILD_TOOLS OFF" "BUILD_TESTS OFF"
# )

# if(   libpsl_ADDED)
# set(LIBPSL_SOURCE_DIR ${libpsl_SOURCE_DIR})
# set(LIBPSL_BUILD_DIR ${libpsl_BINARY_DIR})
# set(LIBPSL_INSTALL_DIR ${CMAKE_BINARY_DIR}/_deps/libpsl-install)
# file(MAKE_DIRECTORY ${LIBPSL_BUILD_DIR})

# # Define helper variables for CPP and CXXCPP
# set(CPP_CMD "${CMAKE_C_COMPILER} -E")
# set(CXXCPP_CMD "${CMAKE_CXX_COMPILER} -E")

# # Set PKG_CONFIG_PATH to include libunistring
# set(ENV{PKG_CONFIG_PATH} "${LIBUNISTRING_INSTALL_DIR}/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")

# add_custom_target(
# configure_libpsl
# COMMAND ./configure --host=${CMAKE_SYSTEM_PROCESSOR} CC=${CMAKE_C_COMPILER} CXX=${CMAKE_CXX_COMPILER} --prefix=${LIBPSL_INSTALL_DIR} LDFLAGS=-L${LIBUNISTRING_INSTALL_DIR}/lib CPPFLAGS=-I${LIBUNISTRING_INSTALL_DIR}/include
# WORKING_DIRECTORY ${LIBPSL_SOURCE_DIR}
# )

# add_custom_target(
# build_libpsl ALL
# COMMAND $$MAKE -j$$(nproc) -C ${LIBPSL_SOURCE_DIR}
# COMMAND $$MAKE -C ${LIBPSL_SOURCE_DIR} install
# WORKING_DIRECTORY ${LIBPSL_SOURCE_DIR}
# )

# add_dependencies(configure_libpsl build_libunistring)
# add_dependencies(build_libpsl configure_libpsl)

# set(LIBPSL_INCLUDE_DIR ${LIBPSL_INSTALL_DIR}/include)
# set(LIBPSL_LIBRARY ${LIBPSL_INSTALL_DIR}/lib/libpsl.a)
# include_directories(${LIBPSL_INCLUDE_DIR})
# link_directories(${LIBPSL_INSTALL_DIR}/lib)

# message(STATUS "libpsl will be configured with PKG_CONFIG_PATH=${LIBUNISTRING_INSTALL_DIR}/lib/pkgconfig")
# message(STATUS "libpsl will be configured with LDFLAGS=-L${LIBUNISTRING_INSTALL_DIR}/lib")
# message(STATUS "libpsl will be configured with CPPFLAGS=-I${LIBUNISTRING_INSTALL_DIR}/include")
# endif()

# end of libpsl ------------------------------------------

# set(NGHTTP2_INCLUDE_DIR ${CMAKE_SYSROOT}/usr/include)
# set(NGHTTP2_LIBRARY ${CMAKE_SYSROOT}/usr/lib/libnghttp2.a)

# Start of curl -------------------------------------------

# CPMAddPackage(
# NAME curl
# GIT_REPOSITORY https://github.com/curl/curl.git
# GIT_TAG curl-8_4_0
# OPTIONS
# "BUILD_CURL_EXE OFF"
# "BUILD_SHARED_LIBS OFF"
# "CURL_DISABLE_TESTS ON"
# "CMAKE_USE_OPENSSL ON"
# "CURL_ZLIB OFF"
# "CURL_DISABLE_LDAP ON"
# "CURL_DISABLE_RTSP ON"
# "CURL_DISABLE_DICT ON"
# "CURL_DISABLE_FILE ON"
# "CURL_DISABLE_TELNET ON"
# "CURL_DISABLE_TFTP ON"
# "CURL_DISABLE_POP3 ON"
# "CURL_DISABLE_IMAP ON"
# "CURL_DISABLE_SMTP ON"
# "CURL_DISABLE_SMB ON"
# "CURL_DISABLE_MQTT ON"
# "CURL_DISABLE_GOPHER ON"
# )
