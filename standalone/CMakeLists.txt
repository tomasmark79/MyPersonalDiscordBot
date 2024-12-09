cmake_minimum_required(VERSION 3.14...3.22)

project(MyDiscordBotStandalone LANGUAGES C CXX)

# --- Import tools ----
include(../cmake/tools.cmake)

# ---- Dependencies ----
include(../cmake/CPM.cmake)

CPMAddPackage(
    NAME MyDiscordBotLib
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..
)

# ---- Create standalone executable ----
file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_executable(MyDiscordBotStandalone ${sources})

set_target_properties(
     MyDiscordBotStandalone PROPERTIES CXX_STANDARD 17 OUTPUT_NAME "MyDiscordBotStandalone"
)

target_link_libraries(MyDiscordBotStandalone MyDiscordBotLib::MyDiscordBotLib)

if(CMAKE_CROSSCOMPILING)
    add_custom_command(
        TARGET MyDiscordBotStandalone
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Running remote-push.sh..."
        COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/../push-artifacts.sh
        COMMENT "Spouštění remote-push.sh po úspěšném sestavení"
    )
endif()
