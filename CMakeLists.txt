cmake_minimum_required(VERSION 3.0.0)
project(pacman VERSION 0.0.1)

include(CTest)
enable_testing()

find_package(SDL2 REQUIRED)
include_directories(pacman ${SDL2_INCLUDE_DIRS})
file(GLOB SOURCES
    src/*.h
    src/*.cpp
    src/lib/*.h
    src/lib/*.cpp
)

add_executable(pacman ${SOURCES})
target_link_libraries(pacman ${SDL2_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
