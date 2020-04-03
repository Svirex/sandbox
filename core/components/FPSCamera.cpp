//
// Created by svirex on 02.04.2020.
//

#include <iostream>

#include <glm/gtx/string_cast.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>

#include "FPSCamera.h"
#include "../Actor.h"
#include "../Math.h"
//#include <glm/gtc/matrix_transform.hpp>

FPSCamera::FPSCamera(Actor *owner) : CameraComponent(owner) {}

void FPSCamera::update(float deltaTime) {
  Component::update(deltaTime);

  mPitch += mPitchSpeed * deltaTime;
  mPitch = glm::clamp(mPitch, -mMaxPitch, mMaxPitch);
  auto quat = glm::angleAxis(mPitch, mOwner->getLeftVector());

  auto viewForward = Math::transform(mOwner->getForwardVector(), quat);

  auto eye = mOwner->getPosition();
  auto center = eye + viewForward * 100.0f;
  auto up = glm::vec3(0.0f, 0.0f, 1.0f);
  auto view = glm::lookAt(eye, center, up);
  setViewMatrix(view);
}

void FPSCamera::setPitchSpeed(float speed) { mPitchSpeed = speed; }
