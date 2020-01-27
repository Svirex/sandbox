//
// Created by svirex on 27.01.2020.
//

#ifndef SANDBOX_GAME_H
#define SANDBOX_GAME_H

class Renderer;

class Game {
public:

  Game();

  bool initialize();

  void runLoop();

  void shutdown();

private:

  void processInput();

  void updateGame();

  void generateOutput();

  bool mIsRunning;

  bool mUpdatingActor;

  Renderer *mRenderer;
};

#endif // SANDBOX_GAME_H
