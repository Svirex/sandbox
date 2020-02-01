cmake_minimum_required(VERSION 3.15)
project(sandbox)

set(CMAKE_CXX_STANDARD 11)

include_directories(~/hdd/external_libs/glm/)
include_directories(~/hdd/external_libs/tinyobjloader)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})



add_executable(sandbox main.cpp core/Game.cpp core/Game.h core/Renderer.cpp core/Renderer.h core/Actor.cpp core/Actor.h core/Component.cpp core/Component.h core/Shader.cpp core/Shader.h)

target_link_libraries(sandbox ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} GLEW)

add_custom_command(TARGET sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders)