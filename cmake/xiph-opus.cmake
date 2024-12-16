# xiph/opus native - tested aarch64 - tested
CPMAddPackage(
    NAME opus
    GITHUB_REPOSITORY xiph/opus
    GIT_TAG v1.5.2
    OPTIONS "OPUS_BUILD_SHARED_LIBRARY ${BUILD_SHARED_LIBS}" # switching only here
    "OPUS_BUILD_PROGRAMS OFF" "OPUS_BUILD_TESTING OFF"
    "CMAKE_POSITION_INDEPENDENT_CODE ON" # -fPIC
)

if(opus_ADDED)
    set(OPUS_INSTALACE_DIR ${opus_SOURCE_DIR}/opus-install)

    set(OPUS_INCLUDE_DIRS ${OPUS_INSTALACE_DIR}/include) # for dpp voice support
    set(HAVE_OPUS_OPUS_H ${OPUS_INSTALACE_DIR}/include/opus/opus.h) # for dpp voice support
    set(OPUS_SHARED_LIBRARY ${OPUS_INSTALACE_DIR}/lib/libopus.so) # for dpp voice support
    set(OPUS_LIBRARIES ${OPUS_INSTALACE_DIR}/lib/libopus.a) # for dpp voice support

    message(STATUS "Debug ${OPUS_INSTALACE_DIR}"
    ) # .cache/CPM/opus/65aae5875a39f28127ba1291a9b942f8bb9ce310/opus-install
    message(STATUS "Debug ${opus_SOURCE_DIR}"
    ) # .cache/CPM/opus/65aae5875a39f28127ba1291a9b942f8bb9ce310
    message(STATUS "Debug ${opus_BINARY_DIR}") # ./Build/Aarch64/Standalone/Debug/_deps/opus-build
    message(STATUS "Debug ${CMAKE_CURRENT_SOURCE_DIR}") # /MyDiscordBot
    message(STATUS "Debug ${CMAKE_CURRENT_BINARY_DIR}"
    ) # /MyDiscordBot/Build/Aarch64/Standalone/Debug/_deps/mydiscordbotlib-build

    # Nastavení instalačního adresáře
    set_target_properties(opus PROPERTIES CMAKE_INSTALL_PREFIX ${OPUS_INSTALACE_DIR})

    # install
    install(
        TARGETS opus
        ARCHIVE DESTINATION ${OPUS_INSTALACE_DIR}/lib
        LIBRARY DESTINATION ${OPUS_INSTALACE_DIR}/lib
        RUNTIME DESTINATION ${OPUS_INSTALACE_DIR}/bin
        INCLUDES
        DESTINATION ${OPUS_INSTALACE_DIR}/include
    )

    # install
    add_custom_target(
        opus_install ALL COMMAND ${CMAKE_COMMAND} --install ${opus_BINARY_DIR} --prefix
        ${OPUS_INSTALACE_DIR}
    )

    # install after build opus
    add_dependencies(opus_install opus)

    target_link_libraries(${PROJECT_LIBRARY_NAME} PUBLIC ${OPUS_INSTALACE_DIR}/lib/libopus.a)

    target_include_directories(${PROJECT_LIBRARY_NAME} PUBLIC ${OPUS_INSTALACE_DIR}/include)
endif()
