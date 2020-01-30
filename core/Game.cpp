//
// Created by svirex on 27.01.2020.
//

#include <algorithm>
#include <vector>

#include <SDL2/SDL.h>

#include "Game.h"
#include "Renderer.h"
#include "Actor.h"

Game::Game()
    : mIsRunning(false), mUpdatingActor(false), mRenderer(nullptr),
      mTicksCount(0) {}

bool Game::initialize() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
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
  while (mIsRunning) {
    processInput();
    updateGame();
    generateOutput();
  }
}

void Game::shutdown() { mRenderer->shutdown(); }

void Game::processInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      mIsRunning = false;
      break;
    }
  }
}

void Game::updateGame() {
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
    ;

  float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
  if (deltaTime > 0.05f) {
    deltaTime = 0.05f;
  }
  mTicksCount = SDL_GetTicks();

  mUpdatingActor = true;
  for (auto &actor : mActors) {
    actor->update(deltaTime);
  }
  mUpdatingActor = false;

  for (auto &actor : mPendingActors) {
    mActors.emplace_back(actor);
  }
  mPendingActors.clear();

  std::vector<Actor *> deadActors;
  for (auto &actor : mActors) {
    if (actor->getState() == Actor::EDead) {
      deadActors.emplace_back(actor);
    }
  }
  while (!deadActors.empty()) {
    delete deadActors.back();
  }
}

void Game::generateOutput() {}

void Game::addActor(Actor *actor) {
  if(mUpdatingActor) {
    mPendingActors.emplace_back(actor);
  } else {
    mActors.emplace_back(actor);
  }
}
void Game::removeActor(Actor *actor) {
  auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
  if (iter != mPendingActors.end()) {
    std::iter_swap(iter, --mPendingActors.end());
    mPendingActors.pop_back();
  }
  iter = std::find(mActors.begin(), mActors.end(), actor);
  if (iter != mActors.end()) {
    std::iter_swap(iter, --mActors.end());
    mActors.pop_back();
  }
}
