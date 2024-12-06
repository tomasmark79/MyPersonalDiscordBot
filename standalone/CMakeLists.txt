cmake_minimum_required(VERSION 3.14...3.22)

project(MyDiscordBotStandalone LANGUAGES C CXX ASM)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(NAME MyDiscordBot SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

# ---- Create standalone executable ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_executable(${PROJECT_NAME} ${sources})

set_target_properties(
    ${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 OUTPUT_NAME "MyDiscordBotStandalone"
)

target_link_libraries(${PROJECT_NAME} MyDiscordBot::MyDiscordBot)

if(CMAKE_CROSSCOMPILING)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Running copybuild.sh..."
        COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/copybuild.sh
        COMMENT "Spouštění copybuild.sh po úspěšném sestavení"
    )
endif()
