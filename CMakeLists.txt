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

# OpenSSL compiled OK
CPMAddPackage(
    NAME OpenSSL
    GITHUB_REPOSITORY jimmy-park/openssl-cmake
    GIT_TAG 3.3.2
    OPTIONS ${OPENSSL_OPTIONS}
)

# Start of Opus --------------------------------------------
CPMAddPackage(
    NAME opus
    GIT_REPOSITORY https://github.com/xiph/opus.git
    GIT_TAG v1.4
    DOWNLOAD_ONLY YES # Pouze stáhne zdrojový kód, nekompiluje
    
)

if(opus_ADDED)
    # Cesta ke staženým zdrojovým kódům
    set(OPUS_SOURCE_DIR "${opus_SOURCE_DIR}")
    # Vytvoří složku pro sestavení Opus
    set(OPUS_BUILD_DIR "${CMAKE_BINARY_DIR}/_deps/opus-build")
    file(MAKE_DIRECTORY ${OPUS_BUILD_DIR})

    # Vlastní konfigurace a kompilace
    add_custom_target(
        build_opus ALL
        COMMAND ${CMAKE_COMMAND} -S ${OPUS_SOURCE_DIR} -B ${OPUS_BUILD_DIR}
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
            -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/_deps/opus-install
            -DCMAKE_BUILD_TYPE=Debug
            -DOPUS_BUILD_SHARED=ON
            -DOPUS_BUILD_STATIC=OFF
            -DCMAKE_POSITION_INDEPENDENT_CODE=ON

        COMMAND ${CMAKE_COMMAND} --build ${OPUS_BUILD_DIR}
    )

    # Zajistěte, aby váš projekt používal zkompilovanou knihovnu Opus
    include_directories(${OPUS_BUILD_DIR}/include)
    link_directories(${OPUS_BUILD_DIR}/lib)

    add_custom_command(
        TARGET build_opus
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} --install ${OPUS_BUILD_DIR} --prefix
                ${CMAKE_BINARY_DIR}/_deps/opus-install
    )

    include_directories(${CMAKE_BINARY_DIR}/_deps/opus-install/include)
    link_directories(${CMAKE_BINARY_DIR}/_deps/opus-install/lib)

endif()

set(OPUS_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/_deps/opus-install/include)
set(OPUS_LIBRARIES ${CMAKE_BINARY_DIR}/_deps/opus-install/lib/libopus.a)
set(HAVE_OPUS_OPUS_H ${CMAKE_BINARY_DIR}/_deps/opus-install/include/opus/opus.h)

# end of Opus --------------------------------------------

# libssh2 compiled OK CPMAddPackage( NAME libssh2 GITHUB_REPOSITORY libssh2/libssh2 GIT_TAG
# libssh2-1.11.1 DEPENDS "OpenSSL" OPTIONS "LINT=OFF" "CRYPTO_BACKEND=OpenSSL"
# "BUILD_STATIC_LIBS=OFF" "BUILD_SHARED_LIBS=ON" "BUILD_EXAMPLES=OFF" "BUILD_TESTING=OFF"
# "ENABLE_ZLIB_COMPRESSION=ON" ) set(LIBSSH2_LIBRARY libssh2) set(LIBSSH2_INCLUDE_DIR
# LIBSSH2_LIBRARY libssh2)

# # libpsl CPMAddPackage( NAME libpsl GITHUB_REPOSITORY rockdaboot/libpsl GIT_TAG v0.21.1 OPTIONS
# "LIBPSL_BUILD_TESTS OFF" "LIBPSL_BUILD_TOOLS OFF" ) set( LIBPSL_LIBRARY libpsl ) set(
# LIBPSL_INCLUDE_DIR LIBPSL_LIBRARY libpsl )

# # libnghttp2 CPMAddPackage( NAME nghttp2 GITHUB_REPOSITORY nghttp2/nghttp2 GIT_TAG v1.45.1 OPTIONS
# "ENABLE_LIB_ONLY ON" "ENABLE_STATIC_LIB ON" "ENABLE_SHARED_LIB OFF" "ENABLE_EXAMPLES OFF"
# "ENABLE_HPACK_TOOLS OFF" "ENABLE_APP OFF" "ENABLE_PYTHON_BINDINGS OFF" "ENABLE_H2LOAD OFF"
# "ENABLE_EV_EMBED OFF" "ENABLE_ASIO_LIB OFF" "ENABLE_CUNIT OFF" "ENABLE_WERROR OFF"
# "ENABLE_FATAL_WARNINGS OFF" "ENABLE_STATIC_CRT OFF" "ENABLE_DEBUG OFF" "ENABLE_STATIC_LIB ON"
# "ENABLE_LIB_ONLY ON" "ENABLE_SHARED_LIB OFF" "ENABLE_EXAMPLES OFF" "ENABLE_HPACK_TOOLS OFF"
# "ENABLE_APP OFF" "ENABLE_PYTHON_BINDINGS OFF" "ENABLE_H2LOAD OFF" "ENABLE_EV_EMBED OFF"
# "ENABLE_ASIO_LIB OFF" "ENABLE_CUNIT OFF" "ENABLE_WERROR OFF" "ENABLE_FATAL_WARNINGS OFF"
# "ENABLE_STATIC_CRT OFF" "ENABLE_DEBUG OFF" )

# set( NGHTTP2_LIBRARY nghttp2 )

# CPMAddPackage( NAME curl GITHUB_REPOSITORY "curl/curl" GIT_TAG "curl-8_11_0" OPTIONS
# "CURL_USE_LIBSSH2 ON" "CURL_USE_MBEDTLS OFF" "BUILD_CURL_EXE OFF" "BUILD_SHARED_LIBS OFF"
# "BUILD_TESTING OFF" )

# FetchContent_MakeAvailable(curl)

# find_package(curl) # probably with CONFIG REQUIRED target_link_libraries(${EXECUTABLE_NAME}
# PRIVATE CURL::libcurl # or CURL::libcurl_shared, or whatever is the target name )

# Přidání EmojiTools
CPMAddPackage(
    NAME EmojiTools
    GIT_TAG main
    GITHUB_REPOSITORY tomasmark79/EmojiTools
    OPTIONS "EMOJI_INSTALL YES" "CMAKE_POSITION_INDEPENDENT_CODE ON"
)

# Přidání DPP
CPMAddPackage(
    NAME DPP
    GITHUB_REPOSITORY brainboxdotcc/DPP
    VERSION 10.0.35 GIT_PROGRESS TRUE
    OPTIONS "DPP_BUILD_EXAMPLES OFF" "DPP_BUILD_TESTS OFF" "DPP_ENABLE_INSTALL ON"
)

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
     "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# Enable code coverage
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
endif()

# ---- Create library ----

# Vytvoření knihovny Note: for header-only libraries change all PUBLIC flags to INTERFACE and create
# an interface target: add_library(${PROJECT_NAME} INTERFACE)

add_library(${PROJECT_NAME} ${headers} ${sources})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_compile_options(${PROJECT_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

# Link dependencies
target_link_libraries(
    ${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto dpp EmojiTools::EmojiTools opus
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
