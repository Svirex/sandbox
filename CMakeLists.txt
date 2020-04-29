cmake_minimum_required(VERSION 3.15)
project(sandbox)

set(CMAKE_CXX_STANDARD 11)

include_directories(~/hdd/external_libs/glm/)
include_directories(~/hdd/external_libs/tinyobjloader)
include_directories(~/hdd/external_libs/spdlog/include/spdlog)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})


add_executable(sandbox main.cpp core/Game.cpp core/Game.h core/Renderer.cpp core/Renderer.h core/Actor.cpp core/Actor.h core/Component.cpp core/Component.h core/Shader.cpp core/Shader.h core/Mesh.cpp core/Mesh.h core/utils/MeshLoader.cpp core/utils/MeshLoader.h core/VertexArray.cpp core/VertexArray.h core/components/MeshComponent.cpp core/components/MeshComponent.h core/InputSystem.cpp core/InputSystem.h core/components/MoveComponent.cpp core/components/MoveComponent.h core/Math.cpp core/Math.h core/actors/FPSActor.cpp core/actors/FPSActor.h core/components/CameraComponent.cpp core/components/CameraComponent.h core/components/FPSCamera.cpp core/components/FPSCamera.h core/system/ObjectManager.cpp core/system/ObjectManager.h core/ResourceManager.cpp core/ResourceManager.h)

target_link_libraries(sandbox ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} GLEW assimp)

add_custom_command(TARGET sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders)

add_custom_command(TARGET sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)

add_definitions(-DOBJECT_MANAGER)