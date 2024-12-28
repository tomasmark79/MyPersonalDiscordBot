cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

# dep: conanInstall(), CPM.cmake
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
# required by clangd clinting
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- User definition of Standalone name, and install prefix ----
# dep: CMakeController.sh
set(PROJECT_STANDALONE_NAME DiscordBotStandalone)
project(
    ${PROJECT_STANDALONE_NAME}
    LANGUAGES C CXX ASM
    DESCRIPTION "Executable template by Tomáš Mark 2024"
    HOMEPAGE_URL "https://github.com/tomasmark79")

# ---- Include guards ----
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
        FATAL_ERROR
            "In-source builds not allowed. Please make a new directory (called a Build directory) and run CMake from there."
    )
endif()

# ---- Mandatory CPMs  ----
include(../cmake/tools.cmake)
include(../cmake/CPM.cmake)
CPMAddPackage(NAME MyDiscordBot SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

CPMAddPackage(
    NAME cxxopts
    GITHUB_REPOSITORY jarro2783/cxxopts
    VERSION 3.2.1
    OPTIONS "CXXOPTS_BUILD_EXAMPLES OFF" "CXXOPTS_BUILD_TESTS OFF" "CXXOPTS_ENABLE_INSTALL OFF")

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

# ---- Create standalone executable ----
add_executable(${PROJECT_STANDALONE_NAME} ${sources})

# ---- Standalone options ----
set_target_properties(${PROJECT_STANDALONE_NAME} PROPERTIES OUTPUT_NAME
                                                            "${PROJECT_STANDALONE_NAME}")
# ---- link developed library ----
target_link_libraries(${PROJECT_STANDALONE_NAME} PRIVATE dsdotname::MyDiscordBot)

# ---- Set installation directory ----
# set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../Build/Installed/" CACHE PATH
# "Installation Directory" FORCE)
install(TARGETS ${PROJECT_STANDALONE_NAME} RUNTIME DESTINATION bin)
