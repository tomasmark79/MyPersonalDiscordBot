# LIBSSH2 MODULE
# This is a CMake module to build libssh2 from source
# used: native cmake configuration

function(add_libssh2)
    CPMAddPackage(
        NAME libssh2
        GITHUB_REPOSITORY libssh2/libssh2
        GIT_TAG libssh2-1.11.1
        OPTIONS "BUILD_EXAMPLES OFF" "BUILD_TESTING OFF" "ENABLE_ZLIB_COMPRESSION OFF"
    )

    # wait for openssl to be built
    if(libssh2_ADDED)
        add_custom_target(build_libssh2 DEPENDS ${LIBSSH2_LIBRARY})
        add_dependencies(build_libssh2 OpenSSL::SSL OpenSSL::Crypto OpenSSL::applink)
        set(LIBSSH2_INCLUDE_DIR ${libssh2_SOURCE_DIR}/include)
        set(LIBSSH2_LIBRARY ${libssh2_BINARY_DIR}/src/libssh2.a)

        include_directories(${LIBSSH2_INCLUDE_DIR})
        link_directories(${libssh2_BINARY_DIR}/src)

    else()
        find_package(libssh2 REQUIRED)

        if(libssh2_FOUND)
            message(STATUS "Building with system libssh2")
        else()
            message(FATAL_ERROR "Downloading libssh2 failed and system libssh2 not found :(")
        endif()
    endif()
endfunction()

add_libssh2()
