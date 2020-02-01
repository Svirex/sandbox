//
// Created by svirex on 27.01.2020.
//

#include <GL/glew.h>

#include "Game.h"
#include "Renderer.h"
#include "Shader.h"

Renderer::Renderer(Game *game)
    : mWindow(nullptr), mGame(game), mContext(nullptr) {}

bool Renderer::initialize(float screenWidth, float screenHeight) {
  mScreenWidth = screenWidth;
  mScreenHeight = screenHeight;

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

  mWindow = SDL_CreateWindow("Sandbox", 100, 100, static_cast<int>(screenWidth),
                             static_cast<int>(screenHeight), SDL_WINDOW_OPENGL);
  if (!mWindow) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return false;
  }

  mContext = SDL_GL_CreateContext(mWindow);

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

void Renderer::shutdown() {
  for (auto &shader : mShaders) {
    shader.second->unload();
  }
  SDL_GL_DeleteContext(mContext);
  SDL_DestroyWindow(mWindow);
}


