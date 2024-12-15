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
include(cmake/madler-zlib.cmake)
include(cmake/libiconv.cmake)

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
# native - tested
# aarch64 - tested
CPMAddPackage(
    NAME EmojiToolsLib
    GIT_TAG main
    GITHUB_REPOSITORY tomasmark79/EmojiTools
    OPTIONS "EMOJI_INSTALL NO" # create an installable target
)

if(EmojiToolsLib_ADDED)
    target_link_libraries(${PROJECT_LIBRARY_NAME} PRIVATE name.digitalspace.www::EmojiToolsLib)
endif()

# self headers
target_include_directories(
    ${PROJECT_LIBRARY_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Include>
    $<INSTALL_INTERFACE:Include/${PROJECT_LIBRARY_NAME}-${PROJECT_VERSION}>
)

# openssl - openssl-cmake
# native - tested
# aarch64 - tested
CPMAddPackage(
    NAME openssl
    GITHUB_REPOSITORY jimmy-park/openssl-cmake
    GIT_TAG 3.4.0
    OPTIONS "OPENSSL_CONFIGURE_OPTIONS no-shared\\\\;no-tests" "BUILD_SHARED_LIBS OFF"
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

# xiph/opus
# native - tested
# aarch64 - tested
CPMAddPackage(
    NAME opus
    GITHUB_REPOSITORY xiph/opus
    GIT_TAG v1.5.2
    OPTIONS
    "OPUS_BUILD_SHARED_LIBRARY ON"
    "OPUS_BUILD_PROGRAMS OFF"
    "OPUS_BUILD_TESTING OFF"
    "CMAKE_INDEPENDENT_VARIABLES ON"
)

if(opus_ADDED)
    set(OPUS_INSTALACE_DIR ${opus_SOURCE_DIR}/opus-install) 

    set(OPUS_INCLUDE_DIRS ${OPUS_INSTALACE_DIR}/include) # for dpp voice support
    set(HAVE_OPUS_OPUS_H ${OPUS_INSTALACE_DIR}/include/opus/opus.h) # for dpp voice support
    set(OPUS_SHARED_LIBRARY ${OPUS_INSTALACE_DIR}/lib/libopus.so) # for dpp voice support
    set(OPUS_LIBRARIES ${OPUS_INSTALACE_DIR}/lib) # for dpp voice support

    message(STATUS "Debug ${OPUS_INSTALACE_DIR}") # .cache/CPM/opus/65aae5875a39f28127ba1291a9b942f8bb9ce310/opus-install
    message(STATUS "Debug ${opus_SOURCE_DIR}") # .cache/CPM/opus/65aae5875a39f28127ba1291a9b942f8bb9ce310
    message(STATUS "Debug ${opus_BINARY_DIR}") # ./Build/Aarch64/Standalone/Debug/_deps/opus-build
    message(STATUS "Debug ${CMAKE_CURRENT_SOURCE_DIR}") # /MyDiscordBot
    message(STATUS "Debug ${CMAKE_CURRENT_BINARY_DIR}") # /MyDiscordBot/Build/Aarch64/Standalone/Debug/_deps/mydiscordbotlib-build

    # Nastavení instalačního adresáře
    set_target_properties(opus PROPERTIES
        CMAKE_INSTALL_PREFIX ${opus_BINARY_DIR}
    )

    # install
    install(TARGETS opus
        ARCHIVE DESTINATION ${OPUS_INSTALACE_DIR}/lib
        LIBRARY DESTINATION ${OPUS_INSTALACE_DIR}/lib
        RUNTIME DESTINATION ${OPUS_INSTALACE_DIR}/bin
        INCLUDES DESTINATION ${OPUS_INSTALACE_DIR}/include
    )

    # install
    add_custom_target(opus_install ALL
        COMMAND ${CMAKE_COMMAND} --install ${opus_BINARY_DIR} --prefix ${OPUS_INSTALACE_DIR}
    )

    #
    add_dependencies(opus_install opus)

    target_link_libraries(${PROJECT_LIBRARY_NAME} PUBLIC ${OPUS_INSTALACE_DIR}/lib/libopus.a)
    target_include_directories(${PROJECT_LIBRARY_NAME} PUBLIC ${OPUS_INSTALACE_DIR}/include)
endif()

# dpp
# native - tested
# aarch64 - tested
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

    target_include_directories(dpp PUBLIC ${OPUS_INSTALACE_DIR}/include) # for dpp voice support - else #include <opus/opus.h> errors

    # target_link_libraries(MyDiscordBotLib PUBLIC dpp opus) # opus for dpp voice support with shared opus
    target_link_libraries(MyDiscordBotLib PUBLIC dpp opus) # opus for dpp voice support with static opus - need -fPIC
endif()

# libssh2
# native - tested
# aarch64 - tested
CPMAddPackage(
    NAME libssh2
    GITHUB_REPOSITORY libssh2/libssh2
    GIT_TAG libssh2-1.11.1
    OPTIONS "BUILD_EXAMPLES OFF" "BUILD_TESTING OFF" "ENABLE_ZLIB_COMPRESSION OFF"
)

if(libssh2_ADDED)
    set(LIBSSH2_LIBRARY ${libssh2_BINARY_DIR}/src/libssh2.a)
    set(LIBSSH2_INCLUDE_DIR ${libssh2_SOURCE_DIR}/include)
endif()

# # libunistring
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

# #libpsl
# CPMAddPackage(
# NAME libpsl
# GITHUB_REPOSITORY rockdaboot/libpsl
# GIT_TAG v0.21.2
# OPTIONS "LIBPSL_INSTALL ON"
# )

# # NGHTTP2
# CPMAddPackage(
# NAME nghttp2
# GITHUB_REPOSITORY nghttp2/nghttp2
# GIT_TAG v1.45.1
# OPTIONS "ENABLE_ASIO_LIB OFF" "ENABLE_EXAMPLES OFF" "ENABLE_HPACK_TOOLS OFF"
# "ENABLE_APP OFF" "ENABLE_H2LOAD OFF" "ENABLE_HPACK_ENC OFF" "ENABLE_HPACK_DEC OFF"
# "ENABLE_EV_EMBED OFF" "ENABLE_STATIC_LIB ON" "ENABLE_SHARED_LIB OFF"
# )

# Could NOT find NGHTTP2 (missing: NGHTTP2_INCLUDE_DIR NGHTTP2_LIBRARY) (found version "1.59.0")
# Could NOT find Libpsl (missing: LIBPSL_INCLUDE_DIR LIBPSL_LIBRARY) (found version "0.21.2")
# -- Could NOT find Libev (missing: LIBEV_LIBRARY LIBEV_INCLUDE_DIR) (Required is at least version "4.11")
# -- Could NOT find Libcares (missing: LIBCARES_LIBRARY LIBCARES_INCLUDE_DIR) (Required is at least version "1.7.5")
# -- Found ZLIB: /home/tomas/x-tools/aarch64-rpi4-linux-gnu/aarch64-rpi4-linux-gnu/sysroot/usr/lib/libz.so (found suitable version "1.2.13", minimum required is "1.2.3")
# -- Could NOT find Libngtcp2 (missing: LIBNGTCP2_LIBRARY LIBNGTCP2_INCLUDE_DIR) (Required is at least version "0.0.0")
# -- Could NOT find Libngtcp2_crypto_openssl (missing: LIBNGTCP2_CRYPTO_OPENSSL_LIBRARY LIBNGTCP2_CRYPTO_OPENSSL_INCLUDE_DIR) (Required is at least version "0.0.0")
# -- Could NOT find Libnghttp3 (missing: LIBNGHTTP3_LIBRARY LIBNGHTTP3_INCLUDE_DIR) (Required is at least version "0.0.0")
# -- Could NOT find Libbpf (missing: LIBBPF_LIBRARY LIBBPF_INCLUDE_DIR) (Required is at least version "0.4.0")
# -- Could NOT find Systemd (missing: SYSTEMD_INCLUDE_DIRS SYSTEMD_LIBRARIES) (Required is at least version "209")
# -- Could NOT find Jansson (missing: JANSSON_LIBRARY JANSSON_INCLUDE_DIR) (Required is at least version "2.5")
# -- Could NOT find Libevent (missing: LIBEVENT_LIBEVENT_LIBRARY LIBEVENT_OPENSSL_LIBRARY LIBEVENT_INCLUDE_DIR libevent openssl) (Required is at least version "2.0.8")
# -- Could NOT find PythonLibs (missing: PYTHON_LIBRARIES PYTHON_INCLUDE_DIRS)
# -- Could NOT find LibXml2 (missing: LIBXML2_LIBRARY LIBXML2_INCLUDE_DIR) (Required is at least version "2.6.26")
# -- Could NOT find Jemalloc (missing: JEMALLOC_LIBRARY JEMALLOC_INCLUDE_DIR)
# -- Could NOT find PythonLibs (missing: PYTHON_LIBRARIES PYTHON_INCLUDE_DIRS)
# -- Could NOT find LibXml2 (missing: LIBXML2_LIBRARY LIBXML2_INCLUDE_DIR) (Required is at least version "2.6.26")
# -- Could NOT find Jemalloc (missing: JEMALLOC_LIBRARY JEMALLOC_INCLUDE_DIR)
# -- Could NOT find CUnit (missing: CUNIT_LIBRARY CUNIT_INCLUDE_DIR) (Required is at least version "2.1")

# # curl
# CPMAddPackage(
# NAME curl
# GITHUB_REPOSITORY curl/curl
# GIT_TAG curl-8_11_1
# OPTIONS "CURL_INSTALL OFF"
# )

# if(curl_ADDED)
# add_dependencies(dpp OpenSSL::SSL OpenSSL::Crypto OpenSSL::applink)
# endif()

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

# # ---- Install ----
# include(GNUInstallDirs)
# install(
# TARGETS dpp
# EXPORT ${PROJECT_LIBRARY_NAME}Targets
# LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
# ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
# RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# INCLUDES
# DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_LIBRARY_NAME}-${PROJECT_VERSION}
# )