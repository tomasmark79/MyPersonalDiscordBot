cmake_minimum_required(VERSION 3.14...3.22)

# ---- Project ----

project(
    MyDiscordBot
    VERSION 1.0
    LANGUAGES C CXX ASM
)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
        FATAL_ERROR
            "In-source builds nejsou povoleny. Vytvořte nový adresář (build directory) a spusťte CMake odtud."
    )
endif()

# Include CPM.cmake jednou
include(cmake/CPM.cmake)

# PackageProject.cmake
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.12.0")


# Detect the target architecture
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    set(OPENSSL_OPTIONS "OPENSSL_CONFIGURE_OPTIONS no-tests" "CMAKE_SYSTEM_PROCESSOR x86_64"
                        "OPENSSL_TARGET_ARCHITECTURE linux-x86_64" "OPENSSL_TARGET_PROCESSOR x86_64")
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
    set(OPENSSL_OPTIONS "OPENSSL_CONFIGURE_OPTIONS no-tests" "CMAKE_SYSTEM_PROCESSOR aarch64"
                        "OPENSSL_TARGET_ARCHITECTURE linux-aarch64" "OPENSSL_TARGET_PROCESSOR aarch64")
else()
    message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

# Přidání OpenSSL
# URL https://github.com/jimmy-park/openssl-cmake/archive/main.tar.gz
CPMAddPackage(
    NAME OpenSSL
    GITHUB_REPOSITORY jimmy-park/openssl-cmake
    GIT_TAG 3.3.2
    OPTIONS ${OPENSSL_OPTIONS}
)

# Přidání DPP
CPMAddPackage(
    NAME DPP
    GITHUB_REPOSITORY brainboxdotcc/DPP
    VERSION 10.0.35 GIT_PROGRESS TRUE
    OPTIONS "DPP_BUILD_EXAMPLES OFF" "DPP_BUILD_TESTS OFF" "DPP_ENABLE_INSTALL ON"
    DEPENDS "OpenSSL"
)

# Přidání EmojiTools
CPMAddPackage(
    NAME EmojiTools
    GIT_TAG main
    GITHUB_REPOSITORY tomasmark79/EmojiTools
    OPTIONS "EMOJI_INSTALL YES"
)

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
     "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# ---- Create library ----

# Vytvoření knihovny
# Note: for header-only libraries change all PUBLIC flags to INTERFACE and create an interface
# target: add_library(${PROJECT_NAME} INTERFACE)

add_library(${PROJECT_NAME} ${headers} ${sources})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_compile_options(${PROJECT_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

# Link dependencies
target_link_libraries(
    ${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto dpp EmojiTools::EmojiTools 
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
)

