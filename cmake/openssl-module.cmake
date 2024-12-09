# OPENSSL MODULE
# This is a CMake module to build openssl from source
# used: native cmake configuration

function(add_openssl)
    CPMAddPackage(
        NAME openssl
        GITHUB_REPOSITORY jimmy-park/openssl-cmake
        GIT_TAG 3.3.2
        OPTIONS ${OPENSSL_OPTIONS}
    )

    if(openssl_ADDED)
        set(OPENSSL_CONFIGURE_OPTIONS "no-tests" "no-shared") 

        if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
            set(ARCHITECTURE "x86_64")
            set(TARGET_ARCHITECTURE "linux-x86_64")
        elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
            set(ARCHITECTURE "aarch64")
            set(TARGET_ARCHITECTURE "linux-aarch64")
        else()
            message(STATUS "Not tested architecture: ${CMAKE_SYSTEM_PROCESSOR}")
        endif()

        set(OPENSSL_OPTIONS
            OPENSSL_CONFIGURE_OPTIONS ${OPENSSL_CONFIGURE_OPTIONS}
            CMAKE_SYSTEM_PROCESSOR ${ARCHITECTURE}
            OPENSSL_TARGET_ARCHITECTURE ${TARGET_ARCHITECTURE}
            OPENSSL_TARGET_PROCESSOR ${ARCHITECTURE}
        )

        include_directories(${OPENSSL_INCLUDE_DIR})
        link_directories(${openssl_BINARY_DIR}/lib)

    else()
        find_package(openssl REQUIRED)

        if(openssl_FOUND)
            message(STATUS "Building with system openssl")
        else()
            message(FATAL_ERROR "Downloading openssl failed and system openssl not found :(")
        endif()
    endif()
endfunction()

# Call the function
add_openssl()
