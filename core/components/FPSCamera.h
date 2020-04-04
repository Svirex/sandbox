//
// Created by svirex on 02.04.2020.
//

#ifndef SANDBOX_FPSCAMERA_H
#define SANDBOX_FPSCAMERA_H

#include <glm/gtc/constants.hpp>

#include "CameraComponent.h"
#include "../system/ObjectManager.h"

class Actor;

class FPSCamera : public CameraComponent {
public:
  explicit FPSCamera(Actor *owner);

  void update(float deltaTime) override;

  void setPitchSpeed(float speed);

  MANAGE(FPSCamera)

private:

  float mMaxPitch = glm::pi<float>() / 3.0f;

  float mPitch = 0.0f;

  float mPitchSpeed = 0.0f;
};

#endif // SANDBOX_FPSCAMERA_H
