//
// Created by svirex on 27.01.2020.
//

#include <SDL2/SDL.h>

#include "Game.h"
#include "Renderer.h"

Game::Game(): mIsRunning(false), mUpdatingActor(false), mRenderer(nullptr) {}

bool Game::initialize() {
  if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
  {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return false;
  }

  mRenderer = new Renderer(this);
  if (!mRenderer->initialize(1024.0f, 768.0f)) {
    SDL_Log("Failed to initialize renderer");
    delete mRenderer;
    mRenderer = nullptr;
    return false;
  }
  return true;
}

void Game::runLoop() {
  mIsRunning = true;
  while(mIsRunning) {
    processInput();
    updateGame();
    generateOutput();
  }
}

void Game::shutdown() {
  mRenderer->shutdown();
}

void Game::processInput() {
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        mIsRunning = false;
        break;
    }
  }
}

void Game::updateGame() {}

void Game::generateOutput() {}
