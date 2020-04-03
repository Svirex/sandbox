//
// Created by svirex on 02.04.2020.
//

#ifndef SANDBOX_FPSACTOR_H
#define SANDBOX_FPSACTOR_H

#include "../Actor.h"

class MoveComponent;
class Game;
class FPSCamera;

class FPSActor : public Actor {
public:
  explicit FPSActor(Game *game);

  void actorInput(const InputState &input) override;
protected:
  void tick(float deltaTime) override;

private:
  MoveComponent *mMoveComponent = nullptr;
  FPSCamera *mCamera = nullptr;
};

#endif // SANDBOX_FPSACTOR_H
