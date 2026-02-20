cmake_minimum_required(VERSION 3.16)

project(space_invaders C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED)

add_executable(space_invaders
    src/main.c
    src/game.c
    src/player.c
    src/enemy.c
)

target_include_directories(space_invaders PRIVATE include)

target_link_libraries(space_invaders PRIVATE SDL3::SDL3)
