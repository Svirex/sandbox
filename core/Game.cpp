//
// Created by svirex on 27.01.2020.
//

#include <algorithm>
#include <vector>
#include <iostream>

#include <SDL2/SDL.h>
#include <glm/ext/quaternion_trigonometric.hpp>
#include "spdlog/spdlog.h"

#include "Game.h"
#include "Renderer.h"
#include "Actor.h"
#include "components/MeshComponent.h"
#include "InputSystem.h"
#include "actors/FPSActor.h"
#include "ResourceManager.h"

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

  mInputSystem = new InputSystem();
  if (!mInputSystem->initialize()) {
    SDL_Log("Failed to initialize input system");
    delete mInputSystem;
    mInputSystem = nullptr;
    return false;
  }

  mResourceManager = new ResourceManager(this);

  if(!loadData()){
    spdlog::error("Couldn't load data");
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

void Game::shutdown() {
  unloadData();

  mRenderer->shutdown();
  delete mRenderer;

  mInputSystem->shutdown();
  delete mInputSystem;

  delete mResourceManager;

}

void Game::processInput() {
  mInputSystem->prepareForUpdate();

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      mIsRunning = false;
      break;
    }
  }

  mInputSystem->update();

  auto &state = mInputSystem->getState();
  if (state.keyboard.getKeyState(SDL_SCANCODE_ESCAPE) == EReleased) {
    mIsRunning = false;
  }

  for (auto &actor : mActors) {
    actor->processInput(state);
  }
}

void Game::updateGame() {
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
    ;

  float deltaTime = static_cast<float>(SDL_GetTicks() - mTicksCount) / 1000.0f;
  if (deltaTime > 0.05f) {
    deltaTime = 0.05f;
  }
  mTicksCount = SDL_GetTicks();

  mUpdatingActor = true;
  for (auto &actor : mActors) {
    actor->computeWorldTransformation();
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

void Game::generateOutput() {
  mRenderer->draw();
}

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

bool Game::loadData() {
  if (mRenderer) {
    mRenderer->loadShader("basicMesh", "shaders/basicMesh.vertex", "shaders/basicMesh.fragment");
    auto tree = new Actor(this);
    tree->setPosition(glm::vec3(50.0f, 0.0f, 0.0f));
    tree->setRotation(glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

    auto *tree2 = new Actor(this);
    tree2->setPosition(glm::vec3(0.0f, 100.0f, 0.0f));
    tree2->setRotation(glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

    auto *tree3 = new Actor(this);
    tree3->setPosition(glm::vec3(0.0f, 50.0f, 0.0f));
    tree3->setScale(glm::vec3(100));
    tree3->setRotation(glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
//    actor->setScale(glm::vec3(2.0f));
//    tree->setRotation(glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

    if(!mResourceManager->loadMeshesFromFile("assets/tree.obj")) {
      return false;
    }

    if(!mResourceManager->loadMeshesFromFile("assets/rock/rock.obj")) {
      return false;
    }

    std::string meshName = "SpruceTree1_Cylinder";
    auto *meshComponent = new MeshComponent(tree);
    auto *mesh = mResourceManager->getMesh(meshName);
    if(!mesh) {
      spdlog::error("Couldn't get mesh {}", meshName);
      return false;
    }
    meshComponent->setMesh(mesh);

    auto *meshComponent2 = new MeshComponent(tree2);
    mesh = mResourceManager->getMesh(meshName);
    if(!mesh) {
      spdlog::error("Couldn't get mesh {}", meshName);
      return false;
    }
    meshComponent2->setMesh(mesh);

    meshName = "rock_Mesh_rock";
    auto *meshComponent3 = new MeshComponent(tree3);
    mesh = mResourceManager->getMesh(meshName);
    if(!mesh) {
      spdlog::error("Couldn't get mesh {}", meshName);
      return false;
    }
    meshComponent3->setMesh(mesh);

    auto *player = new FPSActor(this);
    player->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

    mResourceManager->loadMeshesToGPU();

  } else {
    spdlog::error("mRenderer not init");
    return false;
  }
  return true;
}

void Game::unloadData() {
  mResourceManager->unloadMeshesFromGPU();
  while(!mActors.empty()) {
    delete mActors.back();
  }
}

Renderer *Game::getRenderer() const { return mRenderer; }
