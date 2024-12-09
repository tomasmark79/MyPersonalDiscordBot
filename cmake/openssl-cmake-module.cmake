add_definitions(-DOPENSSL_API_COMPAT=0x10101000L)

function(add_openssl)
    FetchContent_Declare(
        openssl-cmake
        URL https://github.com/jimmy-park/openssl-cmake/archive/main.tar.gz
    )
    FetchContent_MakeAvailable(openssl-cmake)

    if(NOT TARGET OpenSSL::SSL)
        add_library(OpenSSL::SSL INTERFACE IMPORTED)
        set_target_properties(OpenSSL::SSL PROPERTIES INTERFACE_LINK_LIBRARIES "")
    endif()

    if(NOT TARGET OpenSSL::Crypto)
        add_library(OpenSSL::Crypto INTERFACE IMPORTED)
        set_target_properties(OpenSSL::Crypto PROPERTIES INTERFACE_LINK_LIBRARIES "")
    endif()

    if(NOT TARGET OpenSSL::applink)
        add_library(OpenSSL::applink INTERFACE IMPORTED)
        set_target_properties(OpenSSL::applink PROPERTIES INTERFACE_LINK_LIBRARIES "")
    endif()

    add_dependencies(OpenSSL::SSL openssl-cmake)
    add_dependencies(OpenSSL::Crypto openssl-cmake)
    add_dependencies(OpenSSL::applink openssl-cmake)
endfunction()

add_openssl()