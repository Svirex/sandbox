cmake_minimum_required(VERSION 3.15)
project(sandbox)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)


add_subdirectory(third_party/assimp-5.0.1)
add_subdirectory(third_party/SDL2-2.0.12)
add_subdirectory(third_party/freeglut-3.2.1)
add_subdirectory(third_party/glew-cmake-master)
add_subdirectory(third_party/SOIL)


include_directories(
        third_party/SDL2-2.0.12/include
        third_party/glew-cmake-master/include
        third_party/glm
        third_party/spdlog/include
        third_party/SOIL
)



include_directories(shaders)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SOIL_TARGET_INCLUDE_DIR})


add_executable(sandbox
        main.cpp
        core/Game.cpp
        core/Game.h
        core/Renderer.cpp
        core/Renderer.h
        core/Actor.cpp
        core/Actor.h
        core/Component.cpp
        core/Component.h
        core/Shader.cpp
        core/Shader.h
        core/Mesh.cpp
        core/Mesh.h
#        core/utils/MeshLoader.cpp
#        core/utils/MeshLoader.h
        core/VertexArray.cpp
        core/VertexArray.h
        core/components/MeshComponent.cpp
        core/components/MeshComponent.h
        core/InputSystem.cpp
        core/InputSystem.h
        core/components/MoveComponent.cpp
        core/components/MoveComponent.h
        core/Math.cpp core/Math.h
        core/actors/FPSActor.cpp
        core/actors/FPSActor.h
        core/components/CameraComponent.cpp
        core/components/CameraComponent.h
        core/components/FPSCamera.cpp
        core/components/FPSCamera.h
        core/system/ObjectManager.cpp
        core/system/ObjectManager.h
        core/ResourceManager.cpp
        core/ResourceManager.h core/Texture.cpp core/Texture.h core/Material.cpp core/Material.h core/consts.h core/ShaderBuilder.cpp core/ShaderBuilder.h)


target_link_libraries(sandbox ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} assimp SDL2 libglew_shared soil)

add_custom_command(TARGET sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders)

add_custom_command(TARGET sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)

add_definitions(-DOBJECT_MANAGER)