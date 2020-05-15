//
// Created by svirex on 02.04.2020.
//

#include <iostream>

#include <SDL_scancode.h>
#include <glm/gtc/constants.hpp>

#include "../Game.h"
#include "../InputSystem.h"
#include "../components/MoveComponent.h"
#include "FPSActor.h"
#include "../components/FPSCamera.h"


FPSActor::FPSActor(Game *game) : Actor(game) {
  mMoveComponent = new MoveComponent(this);
  mCamera = new FPSCamera(this);
}

void FPSActor::actorInput(const InputState &input) {
  Actor::actorInput(input);
  float forwardSpeed = 0.0f;
  float leftSpeed = 0.0f;
  if (input.keyboard.getKeyValue(SDL_SCANCODE_W)) {
    forwardSpeed += 100.0f;
  }
  if (input.keyboard.getKeyValue(SDL_SCANCODE_S)) {
    forwardSpeed -= 100.0f;
  }
  if (input.keyboard.getKeyValue(SDL_SCANCODE_A)) {
    leftSpeed += 100.0f;
  }
  if (input.keyboard.getKeyValue(SDL_SCANCODE_D)) {
    leftSpeed -= 100.0f;
  }
//  std::cout << forwardSpeed << " " << leftSpeed << std::endl;
  mMoveComponent->setForwardSpeed(forwardSpeed);
  mMoveComponent->setStrafeSpeed(leftSpeed);

  const int maxMouseSpeed = 500;
  const float maxAngularSpeed = glm::pi<float>() * 8;
  float angularSpeed = 0.0f;
  float x = input.mouse.getPosition().x;
  if (x != 0.0f) {
//    std::cout << x << std::endl;
    angularSpeed = glm::clamp<float>(x, -maxMouseSpeed, maxMouseSpeed) / maxMouseSpeed;
    angularSpeed *= maxAngularSpeed;
  }
  mMoveComponent->setAngularSpeed(angularSpeed);

  const float maxPitchSpeed = glm::pi<float>() * 8.0f;
  float y = input.mouse.getPosition().y;
  float pitchSpeed = 0.0f;
  if (y != 0.0f) {
    pitchSpeed = y / maxMouseSpeed;
    pitchSpeed *= maxPitchSpeed;
  }

  mCamera->setPitchSpeed(pitchSpeed);

}

void FPSActor::tick(float deltaTime) {
  Actor::tick(deltaTime);
}
