# Start of OpenSSL ---------------------------------------

# Suppress -Wdeprecated-declarations warning
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-deprecated-declarations")

set(OPENSSL_CONFIGURE_OPTIONS "no-tests")

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    set(ARCHITECTURE "x86_64")
    set(TARGET_ARCHITECTURE "linux-x86_64")
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
    set(ARCHITECTURE "aarch64")
    set(TARGET_ARCHITECTURE "linux-aarch64")
else()
    message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif()

set(OPENSSL_OPTIONS
    "OPENSSL_CONFIGURE_OPTIONS ${OPENSSL_CONFIGURE_OPTIONS}"
    "CMAKE_SYSTEM_PROCESSOR ${ARCHITECTURE}"
    "OPENSSL_TARGET_ARCHITECTURE ${TARGET_ARCHITECTURE}"
    "OPENSSL_TARGET_PROCESSOR ${ARCHITECTURE}"
)

CPMAddPackage(
    NAME OpenSSL
    GITHUB_REPOSITORY jimmy-park/openssl-cmake
    GIT_TAG 3.3.2
    OPTIONS ${OPENSSL_OPTIONS}
)

# ----------------------------------------- end of OpenSSL
