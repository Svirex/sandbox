//
// Created by svirex on 27.01.2020.
//

#include <algorithm>
#include <iostream>

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Game.h"
#include "Renderer.h"
#include "Shader.h"
#include "Mesh.h"
#include "components/MeshComponent.h"

Renderer::Renderer(Game *game)
    : mWindow(nullptr), mGame(game), mContext(nullptr) {
  mView = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
                      glm::vec3(0.0f, 0.0f, 1.0f));
//  mView = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
  mProjection = glm::perspective(glm::radians(45.0f), 1024.0f / 768.0f, 0.1f, 1000.0f);
}

bool Renderer::initialize(float screenWidth, float screenHeight) {
  mScreenWidth = screenWidth;
  mScreenHeight = screenHeight;

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);


  mWindow = SDL_CreateWindow("Sandbox", 100, 100, static_cast<int>(mScreenWidth),
                             static_cast<int>(mScreenHeight), SDL_WINDOW_OPENGL);
  if (!mWindow) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return false;
  }

  mContext = SDL_GL_CreateContext(mWindow);

//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // Initialize GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    SDL_Log("Failed to initialize GLEW.");
    return false;
  }

  glGetError();

  return true;
}

bool Renderer::loadShader(const std::string &shaderName,
                          const std::string &vertexShaderFile,
                          const std::string &fragmentShaderFile) {
  auto *shader = new Shader();
  if (!shader->load(vertexShaderFile, fragmentShaderFile)) {
    delete shader;
    return false;
  }

  mShaders[shaderName] = shader;

  return true;
}

Shader *Renderer::getShader(const std::string &shaderName) {
  auto iter = mShaders.find(shaderName);
  if(iter != mShaders.end()) {
    return iter->second;
  }
  return nullptr;
}

void Renderer::shutdown() {
  for (auto &shader : mShaders) {
    shader.second->unload();
    delete shader.second;
  }

  for (auto &mesh: mMeshes) {
    delete mesh.second;
  }
  SDL_GL_DeleteContext(mContext);
  SDL_DestroyWindow(mWindow);
}

//void Renderer::addMesh(std::string &fileName, Mesh *mesh) {
//  mMeshes[]
//}

Mesh *Renderer::getMesh(const std::string &filePath) {
  Mesh *mesh = nullptr;
  auto iter = mMeshes.find(filePath);
  if(iter != mMeshes.end()) {
    mesh = iter->second;
  } else {
    mesh = new Mesh();
    if(mesh->load(filePath, this)) {
      mMeshes.emplace(filePath, mesh);
    } else {
      delete mesh;
      mesh = nullptr;
    }
  }
  return mesh;
}

void Renderer::addMeshComponent(MeshComponent *meshComponent) {
  mMeshComponents.emplace_back(meshComponent);
}
void Renderer::removeMeshComponent(MeshComponent *meshComponent) {
  auto iter = std::find(mMeshComponents.begin(), mMeshComponents.end(), meshComponent);
  if (iter != mMeshComponents.end()) {
    mMeshComponents.erase(iter);
  }
}

void Renderer::draw() {
  glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  for (auto &meshComponent : mMeshComponents) {
    meshComponent->draw(nullptr, mView, mProjection);
  }

  glDisable(GL_DEPTH_TEST);
  SDL_GL_SwapWindow(mWindow);
}

void Renderer::setViewMatrix(const glm::mat4 &view) {
  mView = view;
//  std::cout << "Renderer::setViewMatrix" << glm::to_string(mView[3]) << std::endl;
}
