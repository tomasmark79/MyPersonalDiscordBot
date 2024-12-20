# ---- Package Manager ----
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.12.0")

if(NOT PackageProject.cmake_ADDED)
    message(FATAL_ERROR "Failed to add PackageProject.cmake")
endif()

# ---- Add fmt ----
CPMAddPackage("gh:fmtlib/fmt#11.0.2")

if(NOT fmt_ADDED)
    message(FATAL_ERROR "Failed to add fmt")
endif()

# ---- Licenses ----
CPMAddPackage("gh:cpm-cmake/CPMLicenses.cmake@0.0.7")

if(NOT CPMLicenses.cmake_ADDED)
    message(FATAL_ERROR "Failed to add CPMLicenses.cmake")
else()
    cpm_licenses_create_disclaimer_target(
        write-licenses-${PROJECT_LIBRARY_NAME} "${CMAKE_CURRENT_BINARY_DIR}/third_party.txt"
        "${CPM_PACKAGES}"
    )
endif()

# ---- Add EmojiTools ----
CPMAddPackage(
    NAME EmojiToolsLib
    GITHUB_REPOSITORY tomasmark79/EmojiTools
    GIT_TAG main
    OPTIONS "EMOJI_INSTALL NO"
)

if(NOT EmojiToolsLib_ADDED)
    message(FATAL_ERROR "Failed to add EmojiTools")
else()
    target_link_libraries(${PROJECT_LIBRARY_NAME} PUBLIC EmojiToolsLib)
endif()


# Todo later
# # dpp library, native, aarch64, shared, static
# CPMAddPackage(
#     NAME dpp
#     GITHUB_REPOSITORY brainboxdotcc/DPP
#     VERSION 10.0.35 OPTIONS
#     "BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS}"
#     "BUILD_VOICE_SUPPORT ON" # need opus
#     "DPP_INSTALL OFF" "DPP_BUILD_TEST OFF" #
#     "CMAKE_POSITION_INDEPENDENT_CODE ON" # -fPIC )
# )

# if(dpp_ADDED)
#     find_package(Opus REQUIRED)
#     #add_dependencies(dpp Opus::opus)
#     #add_dependencies(dpp build-openssl) # Ensure dpp waits form wopenssl
#     target_include_directories(${PROJECT_LIBRARY_NAME} PUBLIC ${dpp_SOURCE_DIR}/include
#     )

#     install(TARGETS dppstatic EXPORT MyDiscordBotTargets)
#     install(TARGETS dpp EXPORT MyDiscordBotTargets)

#     # include dpp headers
#     target_include_directories(dpp PUBLIC ${OPUS_INSTALACE_DIR}/include) # headersfor dpp voice support - else # include <opus/opus.h> errors

#     if(${BUILD_SHARED_LIBS} STREQUAL "ON")
#         message(STATUS "Building with shared dpp and opus")
#         target_link_libraries(${PROJECT_LIBRARY_NAME} PUBLIC dpp) # dpp as shared library with # sharedopus
#     else()
#         message(STATUS "Building with static dpp and opus")
#         target_link_libraries(
#             ${PROJECT_LIBRARY_NAME} PUBLIC dppstatic) # dpp as static library with static opus -fPIC
#     endif()

#     # target_link_libraries( dpp PRIVATE ${OPENSSL_CRYPTO_LIBRARY} ${OPENSSL_SSL_LIBRARY} ) # Link
#     # mwopenssl libraries
# endif()