# madler/zlib
CPMAddPackage(
    NAME zlib
    GITHUB_REPOSITORY madler/zlib
    GIT_TAG v1.3.1
    OPTIONS "CMAKE_POSITION_INDEPENDENT_CODE ON" # -fPIC is needed for static linking
)

if(zlib_ADDED)
    add_custom_target(build_zlib DEPENDS ${ZLIB_LIBRARY})
    include_directories(${ZLIB_INCLUDE_DIR})
    link_directories(${zlib_BINARY_DIR})
    set(ZLIB_LIBRARY ${zlib_BINARY_DIR}/libz.a)

else()
    find_package(zlib REQUIRED)

    if(zlib_FOUND)
        message(STATUS "Building with system zlib")
    else()
        message(FATAL_ERROR "Downloading zlib failed and system zlib not found :(")
    endif()
endif()
