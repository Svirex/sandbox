//
// Created by svirex on 27.01.2020.
//

#ifndef SANDBOX_GAME_H
#define SANDBOX_GAME_H

#include <vector>
#include <SDL2/SDL.h>

class Renderer;
class Actor;
class InputSystem;
class ResourceManager;

class Game {
public:
  Game();

  bool initialize();

  void runLoop();

  void shutdown();

  void addActor(Actor *actor);

  void removeActor(Actor *actor);

  Renderer *getRenderer() const;

private:
  bool loadData();

  void unloadData();

  void processInput();

  void updateGame();

  void generateOutput();

  bool mIsRunning;

  bool mUpdatingActor;

  Renderer *mRenderer = nullptr;

  std::vector<Actor *> mActors;

  std::vector<Actor *> mPendingActors;

  Uint32 mTicksCount;

  InputSystem *mInputSystem = nullptr;

  ResourceManager *mResourceManager = nullptr;
};

#endif // SANDBOX_GAME_H
