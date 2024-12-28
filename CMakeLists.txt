cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

# dep: conanInstall(), CPM.cmake
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

# required by clangd clinting
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- User definition of Library name, namespace, and install prefix ----
# dep: CMakeController.sh
set(PROJECT_LIBRARY_NAMESPACE dsdotname)
set(PROJECT_LIBRARY_NAME MyDiscordBot)
project(
    ${PROJECT_LIBRARY_NAME}
    VERSION 0.0.1
    LANGUAGES C CXX ASM
    DESCRIPTION "library template Copyright (c) 2024 TomasMark [at] digitalspace.name"
    HOMEPAGE_URL "https://github.com/tomasmark79")

# ---- Include guards ----
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
        FATAL_ERROR
            "In-source builds not allowed. Please make a new directory (called a Build directory) and run CMake from there."
    )
endif()

# ---- Mandatory CPMs  ----
include(cmake/tools.cmake)
include(cmake/CPM.cmake)
CPMAddPackage("gh:fmtlib/fmt#11.0.2")
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.12.0")
CPMAddPackage("gh:cpm-cmake/CPMLicenses.cmake@0.0.7")

# ---- Optional CPMs  ----
# CPMAddPackage("gh:nlohmann/json@3.11.3")
CPMAddPackage("gh:tomasmark79/EmojiTools#main")

# put CPM.license target after all packages have been added
cpm_licenses_create_disclaimer_target(write-licenses "${CMAKE_CURRENT_BINARY_DIR}/third_party.txt"
                                      "${CPM_PACKAGES}")

# ---- CMake modules path ----
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

# ---- System Libraries example ----
find_package(Threads REQUIRED)
# find_package(X11 REQUIRED)

# ---- Conan dependencies example ----
find_package(BZip2 REQUIRED)
find_package(CURL REQUIRED)
find_package(dpp CONFIG REQUIRED)

# Glob not recommended, but the simplest way for this template
file(
    GLOB_RECURSE
    headers
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hxx)

# Glob not recommended, but the simplest way for this template
file(
    GLOB_RECURSE
    sources
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cxx)

# ---- Create library ----
add_library(${PROJECT_LIBRARY_NAME} ${headers} ${sources})

# ---- Library features ----
target_compile_features(${PROJECT_LIBRARY_NAME} PUBLIC cxx_std_17)

# header-only libraries change all PUBLIC flags to INTERFACE and create an interface target:
# <add_library(${PROJECT_LIBRARY_NAME} INTERFACE)>
target_include_directories(
    ${PROJECT_LIBRARY_NAME}
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
           $<INSTALL_INTERFACE:include/${PROJECT_LIBRARY_NAME}-${PROJECT_VERSION}>
    PRIVATE ${PROJECT_SOURCE_DIR}/Source # for headers in Source folder
    # PRIVATE ${nlohmann_json_SOURCE_DIR}/include # by CPM.cmake for nlohmann/json.hpp
)

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(
    ${PROJECT_LIBRARY_NAME}
    PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/W4;/permissive->>"
           "$<$<NOT:$<COMPILE_LANG_AND_ID:CXX,MSVC>>:-Wall;-Wextra;-Wpedantic>")

# ---- Link libraries ----
target_link_libraries(
    ${PROJECT_LIBRARY_NAME} PUBLIC Threads::Threads dsdotname::EmojiTools BZip2::BZip2 CURL::libcurl dpp::dpp
    # Conan dependencies example 
)

# ---- Packaging ----
string(TOLOWER "${PROJECT_LIBRARY_NAME}" PROJECT_LIBRARY_NAME_LOWER)

packageProject(
    # the name of the target to export
    NAME ${PROJECT_LIBRARY_NAME}
    # the version of the target to export
    VERSION ${PROJECT_VERSION}
    # a temporary directory to create the config files
    BINARY_DIR ${PROJECT_BINARY_DIR}
    # location of the target's public headers
    INCLUDE_DIR "/include"
    # should match the target's INSTALL_INTERFACE include directory
    INCLUDE_DESTINATION include/${PROJECT_LIBRARY_NAME_LOWER}-${PROJECT_VERSION}
    # (optional) option to install only header files with matching pattern
    INCLUDE_HEADER_PATTERN "*.h"
    # semicolon separated list of the project's dependencies
    DEPENDENCIES "fmt#11.0.2;CPMLicenses.cmake@0.0.7;json@3.11.3;EmojiTools@0.0.1"
    # (optional) create a header containing the version info Note: that the path to headers should
    # be lowercase
    VERSION_HEADER "${PROJECT_LIBRARY_NAME_LOWER}/version.h"
    # (optional) create a export header using GenerateExportHeader module
    EXPORT_HEADER "${PROJECT_LIBRARY_NAME_LOWER}/export.h"
    # (optional) install your library with a namespace (Note: do NOT add extra '::')
    NAMESPACE ${PROJECT_LIBRARY_NAMESPACE}
    # (optional) define the project's version compatibility, defaults to `AnyNewerVersion` supported
    # values: `AnyNewerVersion|SameMajorVersion|SameMinorVersion|ExactVersion`
    COMPATIBILITY AnyNewerVersion
    # (optional) option to disable the versioning of install destinations
    DISABLE_VERSION_SUFFIX YES
    # (optional) option to ignore target architecture for pack age resolution defaults to YES for
    # header only (i.e. INTERFACE) libraries
    ARCH_INDEPENDENT YES
    # (optional) option to generate CPack variables
    CPACK YES)

# ---- Set installation directory ----
# set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/Build/Installed/" CACHE PATH "Installation
# Directory" FORCE)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_LIBRARY_NAME} DESTINATION include/)
