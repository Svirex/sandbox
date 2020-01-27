cmake_minimum_required(VERSION 3.15)
project(sandbox)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(sandbox main.cpp core/Game.cpp core/Game.h core/Renderer.cpp core/Renderer.h)

target_link_libraries(sandbox ${SDL2_LIBRARIES})