cmake_minimum_required(VERSION 3.14...3.22)

project(GreeterStandalone LANGUAGES CXX)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(
  GITHUB_REPOSITORY jarro2783/cxxopts
  VERSION 3.0.0
  OPTIONS "CXXOPTS_BUILD_EXAMPLES NO" "CXXOPTS_BUILD_TESTS NO" "CXXOPTS_ENABLE_INSTALL YES"
)

# DPP brainboxdotcc
CPMAddPackage(
    NAME DPP
    GITHUB_REPOSITORY brainboxdotcc/DPP
    VERSION 10.0.35
    OPTIONS "DPP_BUILD_EXAMPLES OFF" "DPP_BUILD_TESTS OFF" "DPP_ENABLE_INSTALL ON"
)

# git@github.com:tomasmark79/EmojiTools.git
CPMAddPackage(
  NAME EmojiTools
  GIT_TAG main
  GITHUB_REPOSITORY tomasmark79/EmojiTools
  OPTIONS "EMOJI_INSTALL YES" # create an installable target
)

CPMAddPackage(NAME Greeter SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

# ---- Create standalone executable ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_executable(${PROJECT_NAME} ${sources})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 OUTPUT_NAME "Greeter")

target_link_libraries(${PROJECT_NAME} Greeter::Greeter cxxopts dpp EmojiTools::EmojiTools)
