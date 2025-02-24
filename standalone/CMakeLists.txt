cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
cmake_policy(SET CMP0091 NEW)

#+-+-+-+-+-+-+-+-+-+-+
#|s|t|a|n|d|a|l|o|n|e|
#+-+-+-+-+-+-+-+-+-+-+

# === shared libraries
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
# === runtime
include(../cmake/mw-runtime.cmake)
option(USE_STATIC_RUNTIME "Link against static runtime libraries" OFF)
# === sanitizer
include(../cmake/mw-sanitizer.cmake)
option(SANITIZE_ADDRESS "Enable Address sanitizer" OFF)
option(SANITIZE_UNDEFINED "Enable Undefined Behavior sanitizer" OFF)
option(SANITIZE_THREAD "Enable Thread sanitizer" OFF)
option(SANITIZE_MEMORY "Enable Memory sanitizer" OFF)
# === hardening
include(../cmake/mw-hardening.cmake)
option(ENABLE_HARDENING "Enable security hardening options" OFF)
# === ipo
include(../cmake/mw-ipo.cmake)
option(ENABLE_IPO "Enable Interprocedural Optimization" OFF)
# === ccache
include(../cmake/ccache.cmake)
option(ENABLE_CCACHE "Enable ccache" ON)

# Linting C/C++ code
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ==============================================================================
# Project attributes
# ==============================================================================
set(STANDALONE_NAME DiscordBotStandalone)
string(TOLOWER "${STANDALONE_NAME}" STANDALONE_NAME_LOWER)
set(STANDALONE_NAMESPACE dsdotname)
project(
    ${STANDALONE_NAME}
    LANGUAGES C CXX ASM
    DESCRIPTION "template Copyright (c) 2024 TomasMark [at] digitalspace.name"
    HOMEPAGE_URL "https://github.com/tomasmark79")

# ---- Include guards ----
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed.
            Please make a new directory (called a Build directory) and run CMake from there.")
endif()

# ==============================================================================
# System / Conan dependencies
# ==============================================================================
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

# ==============================================================================
# CPM.cmake dependencies - take care conflicts
# ==============================================================================
include(../cmake/CPM.cmake)
CPMAddPackage(NAME MyDiscordBot SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
cpm_licenses_create_disclaimer_target(
    write-licenses-${STANDALONE_NAME}
    "${CMAKE_CURRENT_BINARY_DIR}/${STANDALONE_NAME}_third_party.txt" "${CPM_PACKAGES}")

# ==============================================================================
# Source and header files Glob not recommended, but the simplest way for this template
# ==============================================================================
file(
    GLOB_RECURSE
    headers
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hxx)
file(
    GLOB_RECURSE
    sources
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cxx)

# ==============================================================================
# Create target
# ==============================================================================
add_executable(${STANDALONE_NAME} ${sources})

apply_ccache(${STANDALONE_NAME})
apply_hardening(${STANDALONE_NAME})
apply_sanitizers(${STANDALONE_NAME})

# ==============================================================================
# Set compile properties
# ==============================================================================
set_target_properties(${STANDALONE_NAME} PROPERTIES OUTPUT_NAME "${STANDALONE_NAME}")

# ==============================================================================
# Set linking
# ==============================================================================
target_link_libraries(${STANDALONE_NAME} PRIVATE dsdotname::MyDiscordBot)

# ==============================================================================
# Add missing installation exports
# ==============================================================================
install(TARGETS ${STANDALONE_NAME} RUNTIME DESTINATION bin)
