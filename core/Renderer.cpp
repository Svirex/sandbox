//
// Created by svirex on 27.01.2020.
//

#include "Renderer.h"
#include "Game.h"

Renderer::Renderer(Game *game) : mWindow(nullptr), mGame(game) {}

bool Renderer::initialize(float screenWidth, float screenHeight) {
  mScreenWidth = screenWidth;
  mScreenHeight = screenHeight;

  mWindow = SDL_CreateWindow("Sandbox", 100, 100, static_cast<int>(screenWidth),
                             static_cast<int>(screenHeight), 0);
  if (!mWindow) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return false;
  }

  return true;
}

void Renderer::shutdown() {
  SDL_DestroyWindow(mWindow);
}
