cmake_minimum_required(VERSION 3.0.0)
project(pacman VERSION 0.0.1)

include(CTest)
enable_testing()

find_package(SDL2 REQUIRED)
include_directories(pacman ${SDL2_INCLUDE_DIRS})
set(SOURCES
    src/character.cpp
    src/character.h
    src/display.cpp
    src/display.h
    src/game.cpp
    src/game.h
    src/game_map.cpp
    src/game_map.h
    src/LibCB/Error.h
    src/main.cpp
    src/playable_character.cpp
    src/playable_character.h
)

add_executable(pacman ${SOURCES})
target_link_libraries(pacman ${SDL2_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
