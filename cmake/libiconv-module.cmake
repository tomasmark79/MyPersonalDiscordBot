function(add_libiconv)
    CPMAddPackage(
        NAME libiconv
        URL https://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.17.tar.gz
        DOWNLOAD_ONLY YES
    )

    if(libiconv_ADDED)
        set(LIBICONV_SOURCE_DIR ${libiconv_SOURCE_DIR})
        set(LIBICONV_INSTALL_DIR ${CMAKE_BINARY_DIR}/_deps/libiconv-install)
        set(LIBICONV_BUILD_DIR ${libiconv_BINARY_DIR})

        file(MAKE_DIRECTORY ${LIBICONV_BUILD_DIR})

        if(CMAKE_CROSSCOMPILING)
            add_custom_command(
                OUTPUT ${LIBICONV_INSTALL_DIR}/lib/libiconv.a
                COMMAND ./configure
                --host=${CROSS_HOST}
                --prefix=${LIBICONV_INSTALL_DIR}
                --enable-shared
                --enable-static
                CC=${CMAKE_C_COMPILER}
                CXX=${CMAKE_CXX_COMPILER}
                CPP=${CMAKE_C_COMPILER}\ -E
                CXXCPP=${CMAKE_CXX_COMPILER}\ -E
                COMMAND ${CMAKE_MAKE_PROGRAM} -j$(nproc)
                COMMAND ${CMAKE_MAKE_PROGRAM} install
                WORKING_DIRECTORY ${LIBICONV_SOURCE_DIR}
                COMMENT "CrossBuild libiconv downloaded from the internet"

            )
        else() # Native build
            add_custom_command(
                OUTPUT ${LIBICONV_INSTALL_DIR}/lib/libiconv.a
                COMMAND ./configure
                --prefix=${LIBICONV_INSTALL_DIR}
                --enable-shared
                --enable-static
                COMMAND ${CMAKE_MAKE_PROGRAM} -j$$(nproc)
                COMMAND ${CMAKE_MAKE_PROGRAM} install
                WORKING_DIRECTORY ${LIBICONV_SOURCE_DIR}
                COMMENT "Building libiconv downloaded from the internet"
            )
        endif()

        add_custom_target(build_libiconv DEPENDS ${LIBICONV_INSTALL_DIR}/lib/libiconv.a)

        set(LIBICONV_INCLUDE_DIR ${LIBICONV_INSTALL_DIR}/include)
        set(LIBICONV_LIBRARY ${LIBICONV_INSTALL_DIR}/lib/libiconv.a)
        set(LIBICONV_SHARED_LIBRARY ${LIBICONV_INSTALL_DIR}/lib/libiconv.so)

        include_directories(${LIBICONV_INCLUDE_DIR})
        link_directories(${LIBICONV_INSTALL_DIR}/lib)

    else()
        find_package(Iconv REQUIRED)

        if(Iconv_FOUND)
            message(STATUS "Building libiconv from sysroot")
        else()
            message(FATAL_ERROR "Downloading libiconv failed and system libiconv not found :(")
        endif()
    endif()
endfunction()

# Call the function
add_libiconv()
