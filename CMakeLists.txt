cmake_minimum_required(VERSION 3.14...3.22)

# ---- Project ----

# Note: update this to your new project's name and version
project(
    MyDiscordBot
    VERSION 1.0
    LANGUAGES C CXX ASM
)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
        FATAL_ERROR
            "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
    )
endif()

# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info

include(cmake/CPM.cmake)

# PackageProject.cmake will be used to make our target installable
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.8.0")

# Libcurl

# CPMAddPackage(
#     NAME curl
#     GITHUB_REPOSITORY "curl/curl"
#     GIT_TAG "curl-8_11_0"
#     OPTIONS
#         "CMAKE_USE_LIBSSH2 OFF"
#         "CURL_USE_MBEDTLS ON"
#         "BUILD_CURL_EXE OFF"
#         "BUILD_SHARED_LIBS OFF"
#         "BUILD_TESTING OFF"
# )

CPMAddPackage(
    NAME libcurl
    GITHUB_REPOSITORY curl/curl
    GIT_TAG "curl-8_11_0"
    OPTIONS "BUILD_CURL_EXE OFF" "BUILD_TESTING OFF" "CURL_DISABLE_FTP ON" "CURL_DISABLE_LDAP ON"
)       

# OpenSSL
# configure for aarch64
CPMAddPackage(
    NAME openssl-cmake
    URL https://github.com/jimmy-park/openssl-cmake/archive/main.tar.gz
    VERSION 3.4.0
    OPTIONS "OPENSSL_CONFIGURE_OPTIONS no-shared\\\\;no-tests"
    # PLATFORM_TARGET aarch64
)

# LibOpus
CPMAddPackage(
    NAME opus
    GITHUB_REPOSITORY xiph/opus
    VERSION 1.5.2
    OPTIONS "OPUS_INSTALL YES" "OPUS_BUILD_TESTS OFF" "OPUS_BUILD_SHARED YES"
)

# DPP brainboxdotcc
CPMAddPackage(
    NAME DPP
    GITHUB_REPOSITORY brainboxdotcc/DPP
    VERSION 10.0.35
    OPTIONS "DPP_BUILD_EXAMPLES OFF" "DPP_BUILD_TESTS OFF" "DPP_ENABLE_INSTALL ON"
    
)

# git@github.com:tomasmark79/EmojiTools.git
CPMAddPackage(
    NAME EmojiTools
    GIT_TAG main
    GITHUB_REPOSITORY tomasmark79/EmojiTools
    OPTIONS "EMOJI_INSTALL YES" # create an installable target
)

# ---- Add source files ----

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
     "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# ---- Create library ----

# Note: for header-only libraries change all PUBLIC flags to INTERFACE and create an interface
# target: add_library(${PROJECT_NAME} INTERFACE)

add_library(${PROJECT_NAME} ${headers} ${sources})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

# Link dependencies
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE dpp
            EmojiTools::EmojiTools
            opus
            OpenSSL::SSL
            OpenSSL::Crypto
            libcurl
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

# ---- Create an installable target ----
# this allows users to install and find the library via `find_package()`.

# the location where the project's version header will be placed should match the project's regular
# header paths
string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)

packageProject(
    NAME ${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    NAMESPACE ${PROJECT_NAME}
    BINARY_DIR ${PROJECT_BINARY_DIR}
    INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
    INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
    VERSION_HEADER "${VERSION_HEADER_LOCATION}"
    COMPATIBILITY SameMajorVersion
    #DEPENDENCIES "fmt 9.1.0"
)
