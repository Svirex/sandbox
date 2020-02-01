//
// Created by svirex on 27.01.2020.
//

#ifndef SANDBOX_RENDERER_H
#define SANDBOX_RENDERER_H

#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>

class Game;
class Shader;

class Renderer {
public:
  explicit Renderer(Game *game);
  ~Renderer() = default;

  bool initialize(float screenWidth, float screenHeight);

  void shutdown();

  bool loadShader(const std::string &shaderName,
                  const std::string &vertexShaderFile,
                  const std::string &fragmentShaderFile);

private:
  SDL_Window *mWindow;

  Game *mGame;

  float mScreenWidth;

  float mScreenHeight;

  SDL_GLContext mContext;

  std::unordered_map<std::string, Shader *> mShaders;
};

#endif // SANDBOX_RENDERER_H
