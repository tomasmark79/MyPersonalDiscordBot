# Start of libssh2 ---------------------------------------
CPMAddPackage(
    NAME libssh2
    GITHUB_REPOSITORY libssh2/libssh2
    VERSION 1.10.0
    GIT_TAG libssh2-1.10.0
    OPTIONS "BUILD_EXAMPLES OFF" "BUILD_TESTING OFF" "ENABLE_ZLIB_COMPRESSION OFF"
)

if(libssh2_ADDED)
    add_dependencies(libssh2 OpenSSL::SSL OpenSSL::Crypto)
    set(LIBSSH2_INCLUDE_DIR ${libssh2_SOURCE_DIR}/include)
    set(LIBSSH2_LIBRARY ${libssh2_BINARY_DIR}/src/libssh2.a)
    include_directories(${LIBSSH2_INCLUDE_DIR})
    link_directories(${libssh2_BINARY_DIR}/src)
endif()
# -----------------------------------------end of libssh2