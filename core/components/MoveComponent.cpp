//
// Created by svirex on 02.04.2020.
//
#include <iostream>

#include "../Actor.h"
#include "../Math.h"
#include "MoveComponent.h"

MoveComponent::MoveComponent(Actor *owner, int updateOrder)
    : Component(owner, updateOrder) {}

void MoveComponent::setForwardSpeed(float speed) { mForwardSpeed = speed; }

void MoveComponent::setStrafeSpeed(float speed) { mStrafeSpeed = speed; }

void MoveComponent::setAngularSpeed(float speed) { mAngularSpeed = speed; }

void MoveComponent::update(float deltaTime) {
  Component::update(deltaTime);
  //  std::cout << "MoveComponent::update" << std::endl;
  if (!Math::nearZero(mAngularSpeed)) {
    auto rotation = mOwner->getRotation();
    float angle = mAngularSpeed * deltaTime;
    auto inc = glm::angleAxis(-angle, glm::vec3(0.0f, 0.0f, 1.0f));
    mOwner->setRotation(inc * rotation);
  }
  if (!Math::nearZero(mForwardSpeed) || !Math::nearZero(mStrafeSpeed)) {
    auto position = mOwner->getPosition();
    //    std::cout << "OLD POSITION: x=" << position.x
    //              << "y=" << position.y
    //              << "z=" << position.z
    //              << std::endl;
    position += mOwner->getForwardVector() * mForwardSpeed * deltaTime;
    position += mOwner->getLeftVector() * mStrafeSpeed * deltaTime;
    //    std::cout << "NEW POSITION: x=" << position.x
    //              << "y=" << position.y
    //              << "z=" << position.z
    //              << std::endl;
    mOwner->setPosition(position);
  }
}
