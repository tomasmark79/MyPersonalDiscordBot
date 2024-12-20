cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# ---- (c) Tomáš Mark 2024 ----

# ---- Project namespace::name  ----
set(PROJECT_LIBRARY_NAMESPACE dsdotname)
set(PROJECT_LIBRARY_NAME MyDiscordBot)

# ---- Generate Static/Shared targets (taken by Conan too) ----
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

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

# Glob not recommended, but the simplest way for this template
file(GLOB_RECURSE headers CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
     ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

# Glob not recommended, but the simplest way for this template
file(GLOB_RECURSE sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.c
     ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp
)

# ---- Create library ----
add_library(${PROJECT_LIBRARY_NAME} ${headers} ${sources})

# ---- Library features ----
target_compile_features(${PROJECT_LIBRARY_NAME} PUBLIC cxx_std_17)

# ---- Library options
# target_compile_options(${PROJECT_LIBRARY_NAME} PRIVATE "-Wall" "-Wextra" "-Wpedantic")

# header-only libraries change all PUBLIC flags to INTERFACE and create an interface target:
# <add_library(${PROJECT_LIBRARY_NAME} INTERFACE)>
target_include_directories(
    ${PROJECT_LIBRARY_NAME}
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
           $<INSTALL_INTERFACE:include/${PROJECT_LIBRARY_NAME}-${PROJECT_VERSION}>
    PRIVATE ${PROJECT_SOURCE_DIR}/Source
    
)

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(
    ${PROJECT_LIBRARY_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->" # Strict
    # conformance
)

# ---- Init dependencies ----
include(cmake/CPM.cmake)
include(cmake/Dependencies.cmake)

# ---- Conan dependencies ----
find_package(BZip2 REQUIRED)
find_package(CURL REQUIRED)
find_package(dpp CONFIG REQUIRED)

# ---- Link dependencies ----
target_link_libraries(${PROJECT_LIBRARY_NAME} PRIVATE CURL::libcurl BZip2::BZip2 dpp::dpp)

# ---- CMake Modules ----
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules")

find_package(Threads REQUIRED)
find_package(X11 REQUIRED)

# ---- Package ----
string(TOLOWER "${PROJECT_LIBRARY_NAME}/version.h" VERSION_HEADER_LOCATION)

packageProject(
    NAME ${PROJECT_LIBRARY_NAME}
    VERSION ${PROJECT_VERSION}
    NAMESPACE ${PROJECT_LIBRARY_NAMESPACE}
    BINARY_DIR ${PROJECT_BINARY_DIR}
    INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
    INCLUDE_DESTINATION include/${PROJECT_LIBRARY_NAME}-${PROJECT_VERSION}
    VERSION_HEADER "${VERSION_HEADER_LOCATION}"
    COMPATIBILITY SameMajorVersion
    DEPENDENCIES "fmt 11.0.2"
)
