cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# ---- Project attributes ----
set(PROJECT_LIBRARY_NAMESPACE name.digitalspace.www)
set(PROJECT_LIBRARY_NAME MyDiscordBotLib) # for change use ./ProjectRenamer.sh

# ---- Project ----
project(
    ${PROJECT_LIBRARY_NAME}
    VERSION 0.0.1
    LANGUAGES C CXX ASM
)

# ---- Include guards ----
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
        FATAL_ERROR
        "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
    )
endif()

# ---- Modules ----
# more cmake modules - https://cmake.org/cmake/help/v3.28/manual/cmake-modules.7.html
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules")

# ---- Dependencies ----
include(cmake/CPM.cmake)

# PackageProject.cmake will be used to make our target installable
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.12.0")
CPMAddPackage("gh:fmtlib/fmt#11.0.2")

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.hpp
)
file(GLOB_RECURSE sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp
)

# ---- Create library ----

# Note: for header-only libraries change all PUBLIC flags to INTERFACE and create an interface
# target: add_library(${PROJECT_LIBRARY_NAME} INTERFACE)
add_library(${PROJECT_LIBRARY_NAME} ${headers} ${sources})
set_target_properties(${PROJECT_LIBRARY_NAME} PROPERTIES CXX_STANDARD 17)

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(
    ${PROJECT_LIBRARY_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->" # Strict conformance
)

# EmojiTools
CPMAddPackage(
    NAME EmojiTools
    GIT_TAG main
    GITHUB_REPOSITORY tomasmark79/EmojiTools
    OPTIONS "EMOJI_INSTALL YES" # create an installable target
)

if(EmojiTools_ADDED)
    # target_include_directories(MarkWareVCMakeLibrary PRIVATE ${EmojiTools_SOURCE_DIR}/include)
    target_link_libraries(${PROJECT_LIBRARY_NAME} PRIVATE EmojiTools::EmojiTools)
endif()

# self headers
target_include_directories(
    ${PROJECT_LIBRARY_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Include>
    $<INSTALL_INTERFACE:Include/${PROJECT_LIBRARY_NAME}-${PROJECT_VERSION}>
)

CPMAddPackage(
    NAME openssl
    GITHUB_REPOSITORY jimmy-park/openssl-cmake
    GIT_TAG 3.4.0
)
if(openssl_ADDED)   
else()
    find_package(openssl REQUIRED)
    if(openssl_FOUND)
        message(STATUS "Building with system openssl")
    else()
        message(FATAL_ERROR "Downloading openssl failed and system openssl not found :(")
    endif()
endif()

CPMAddPackage(
    NAME dpp
    GITHUB_REPOSITORY brainboxdotcc/DPP
    VERSION 10.0.35
    OPTIONS "BUILD_SHARED_LIBS ON" # OFF = hpke issues
    "BUILD_VOICE_SUPPORT ON" "DPP_INSTALL ON" "DPP_BUILD_TEST OFF"
)

if(dpp_ADDED)
    add_dependencies(dpp OpenSSL::SSL OpenSSL::Crypto OpenSSL::applink)
    target_include_directories(${PROJECT_LIBRARY_NAME} PUBLIC ${dpp_SOURCE_DIR}/include)
    message(STATUS "dpp_ADDED: ${dpp_ADDED}")
    message(STATUS "dpp_SOURCE_DIR: ${dpp_SOURCE_DIR}")
    message(STATUS "dpp_BINARY_DIR: ${dpp_BINARY_DIR}")
    target_link_libraries(MyDiscordBotLib PUBLIC dpp)
endif()

# ---- Package ----
string(TOLOWER "${PROJECT_LIBRARY_NAME}/version.h" VERSION_HEADER_LOCATION)

packageProject(
    NAME ${PROJECT_LIBRARY_NAME}
    VERSION ${PROJECT_VERSION}
    NAMESPACE ${PROJECT_LIBRARY_NAMESPACE}
    BINARY_DIR ${PROJECT_BINARY_DIR}
    INCLUDE_DIR ${PROJECT_SOURCE_DIR}/Include
    INCLUDE_DESTINATION Include/${PROJECT_LIBRARY_NAME}-${PROJECT_VERSION}
    VERSION_HEADER "${VERSION_HEADER_LOCATION}"
    COMPATIBILITY SameMajorVersion
    DEPENDENCIES "fmt 11.0.2"
)
