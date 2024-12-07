cmake_minimum_required(VERSION 3.14...3.22)

# ---- Project ----
project(
    MyDiscordBot
    VERSION 0.0.1
    LANGUAGES C CXX ASM
)

# ---- Include guards ----
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR
        "In-source builds nejsou povoleny. Vytvořte nový adresář (build directory) a spusťte CMake odtud."
    )
endif()

# Include of CPM.cmake -----------------------------------
include(cmake/CPM.cmake)

# Start of PackageProject.cmake --------------------------
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.12.0")

# end of PackageProject.cmake ----------------------------

# Start of OpenSSL ---------------------------------------
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    set(OPENSSL_OPTIONS
        "OPENSSL_CONFIGURE_OPTIONS no-tests" "CMAKE_SYSTEM_PROCESSOR x86_64"
        "OPENSSL_TARGET_ARCHITECTURE linux-x86_64" "OPENSSL_TARGET_PROCESSOR x86_64"
    )
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
    set(OPENSSL_OPTIONS
        "OPENSSL_CONFIGURE_OPTIONS no-tests" "CMAKE_SYSTEM_PROCESSOR aarch64"
        "OPENSSL_TARGET_ARCHITECTURE linux-aarch64" "OPENSSL_TARGET_PROCESSOR aarch64"
    )
else()
    message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

CPMAddPackage(
    NAME OpenSSL
    GITHUB_REPOSITORY jimmy-park/openssl-cmake
    GIT_TAG 3.3.2
    OPTIONS ${OPENSSL_OPTIONS}
)

# end of OpenSSL -----------------------------------------

# Start of Opus ------------------------------------------
if(NOT CMAKE_CROSSCOMPILING)
    message(STATUS "Native compiling detected")
    find_library(OPUS_LIBRARIES opus)
else()
    message(STATUS "Cross-compiling detected")
    CPMAddPackage(
        NAME opus
        GIT_REPOSITORY https://github.com/xiph/opus.git
        GIT_TAG v1.4
        DOWNLOAD_ONLY YES
    )

    if(opus_ADDED)
        set(OPUS_SOURCE_DIR ${opus_SOURCE_DIR})
        set(OPUS_BUILD_DIR ${opus_BINARY_DIR})
        set(OPUS_INSTALL_DIR ${CMAKE_BINARY_DIR}/_deps/opus-install)
        file(MAKE_DIRECTORY ${OPUS_BUILD_DIR})
        add_custom_target(
            build_opus ALL
            COMMAND
            ${CMAKE_COMMAND} -S ${OPUS_SOURCE_DIR} -B ${OPUS_BUILD_DIR}
            -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
            -DCMAKE_INSTALL_PREFIX=${OPUS_INSTALL_DIR} -DCMAKE_BUILD_TYPE=Debug
            -DCMAKE_POSITION_INDEPENDENT_CODE=ON
            COMMAND ${CMAKE_COMMAND} --build ${OPUS_BUILD_DIR}
        )
        add_custom_command(
            TARGET build_opus
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} --install ${OPUS_BUILD_DIR} --prefix ${OPUS_INSTALL_DIR}
        )
        include_directories(${OPUS_INSTALL_DIR}/include)
        link_directories(${OPUS_INSTALL_DIR}/lib)
    endif()

    set(OPUS_INCLUDE_DIRS ${OPUS_INSTALL_DIR}/include)
    set(OPUS_LIBRARIES ${OPUS_INSTALL_DIR}/lib/libopus.a)
    set(HAVE_OPUS_OPUS_H ${OPUS_INCLUDE_DIRS}/opus/opus.h)
endif()

# end of Opus --------------------------------------------

# Start of DPP -------------------------------------------
CPMAddPackage(
    NAME dpp
    GITHUB_REPOSITORY brainboxdotcc/DPP
    VERSION 10.0.35 GIT_PROGRESS TRUE
    OPTIONS "DPP_BUILD_EXAMPLES OFF" "DPP_BUILD_TESTS OFF" "DPP_ENABLE_INSTALL ON"
)

# Start of libssh2 ---------------------------------------
CPMAddPackage(
    NAME libssh2
    GITHUB_REPOSITORY libssh2/libssh2
    VERSION 1.10.0
    GIT_TAG libssh2-1.10.0
    OPTIONS "BUILD_EXAMPLES OFF" "BUILD_TESTING OFF" "ENABLE_ZLIB_COMPRESSION OFF"
)

if(libssh2_ADDED)
    set(LIBSSH2_INCLUDE_DIR ${libssh2_SOURCE_DIR}/include)
    set(LIBSSH2_LIBRARY ${libssh2_BINARY_DIR}/src/libssh2.a)
    include_directories(${LIBSSH2_INCLUDE_DIR})
    link_directories(${libssh2_BINARY_DIR}/src)
endif()

# end of libssh2 -----------------------------------------

# Přidání EmojiTools
CPMAddPackage(
    NAME EmojiTools
    GIT_TAG main
    GITHUB_REPOSITORY tomasmark79/EmojiTools
    OPTIONS "EMOJI_INSTALL YES"
    "CMAKE_POSITION_INDEPENDENT_CODE ON"
    set
    (OPUS_INCLUDE_DIRS ${OPUS_cpm_SOURCE_DIR}/include)
    set
    (OPUS_LIBRARIES ${OPUS_cpm_BINARY_DIR}/libopus.a)
    set
    (HAVE_OPUS_OPUS_H ${OPUS_INCLUDE_DIRS}/opus/opus.h)
)

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# Enable code coverage if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX) set(CMAKE_CXX_FLAGS
# "${CMAKE_CXX_FLAGS} --coverage") set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage") endif()

# ---- Create library ----

# Vytvoření knihovny Note: for header-only libraries change all PUBLIC flags to INTERFACE and create
# an interface target: add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME} ${headers} ${sources})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_compile_options(${PROJECT_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

# Link dependencies
target_link_libraries(
    ${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto dpp EmojiTools::EmojiTools opus libssh2
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
