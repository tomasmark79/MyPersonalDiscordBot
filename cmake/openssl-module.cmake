function(add_openssl)
    CPMAddPackage(
        NAME openssl
        GITHUB_REPOSITORY jimmy-park/openssl-cmake
        GIT_TAG 3.3.2
    )

    if(NOT openssl_ADDED)
        find_package(openssl REQUIRED)

        if(openssl_FOUND)
            message(STATUS "Building with system openssl")
        else()
            message(FATAL_ERROR "Downloading openssl failed and system openssl not found :(")
        endif()
    endif()
endfunction()

add_openssl()
