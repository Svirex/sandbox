//
// Created by svirex on 02.04.2020.
//

#ifndef SANDBOX_MOVECOMPONENT_H
#define SANDBOX_MOVECOMPONENT_H

#include "../Component.h"
#include "../system/ObjectManager.h"

class Actor;

class MoveComponent : public Component {
public:
  explicit MoveComponent(Actor *owner, int updateOrder = 10);

  void setForwardSpeed(float speed);

  void setStrafeSpeed(float speed);

  void setAngularSpeed(float speed);

  void update(float deltaTime) override;

  MANAGE(MoveComponent)

private:
  float mForwardSpeed = 0.0f;

  float mStrafeSpeed = 0.0f;

  float mAngularSpeed = 0.0f;
};

#endif // SANDBOX_MOVECOMPONENT_H
