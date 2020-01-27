//
// Created by svirex on 27.01.2020.
//

#ifndef SANDBOX_RENDERER_H
#define SANDBOX_RENDERER_H

#include <SDL2/SDL.h>

class Game;

class Renderer {
public:
  Renderer(Game *game);
  ~Renderer() = default;

  bool initialize(float screenWidth, float screenHeight);

  void shutdown();

private:
  SDL_Window *mWindow;

  Game *mGame;

  float mScreenWidth;

  float mScreenHeight;
};

#endif // SANDBOX_RENDERER_H
