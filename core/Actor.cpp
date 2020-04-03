//
// Created by svirex on 28.01.2020.
//

#include <algorithm>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Actor.h"
#include "Component.h"
#include "Game.h"

Actor::Actor(Game *game)
    : mPosition(glm::vec3(0.0f)), mRotation(glm::identity<glm::quat>()),
      mScale(glm::vec3(1.0f)), mGame(game), mState(EActive),
      mRecomputeWorldTransformation(false),
      mWorldTransformation(glm::identity<glm::mat4>()) {
  mGame->addActor(this);
}

Actor::~Actor() {
  mGame->removeActor(this);
  while (!mComponents.empty()) {
    delete mComponents.back();
  }
}

void Actor::setPosition(const glm::vec3 &position) {
  mPosition = position;
  mRecomputeWorldTransformation = true;
}

void Actor::setRotation(const glm::quat &rotation) {
  mRotation = rotation;
  mRecomputeWorldTransformation = true;
}

void Actor::setScale(const glm::vec3 &scale) {
  mScale = scale;
  mRecomputeWorldTransformation = true;
}

void Actor::addComponent(Component *component) {
  int order = component->getUpdateOrder();
  auto iter = std::find_if(
      mComponents.begin(), mComponents.end(),
      [order](Component *comp) { return order < comp->getUpdateOrder(); });
  mComponents.insert(iter, component);
}

void Actor::removeComponent(Component *component) {
  auto iter = std::find(mComponents.begin(), mComponents.end(), component);
  if (iter != mComponents.end()) {
    mComponents.erase(iter);
  }
}

void Actor::update(float deltaTime) {
  if (mState == EActive) {
    computeWorldTransformation();
    updateComponents(deltaTime);
    tick(deltaTime);
    computeWorldTransformation();
  }
}

void Actor::tick(float deltaTime) {}

void Actor::updateComponents(float deltaTime) {
  for (auto &comp : mComponents) {
    comp->update(deltaTime);
  }
}

void Actor::setState(Actor::State state) { mState = state; }

Actor::State Actor::getState() const { return mState; }

Game *Actor::getGame() const { return mGame; }

glm::mat4 Actor::getWorldTransformation() {
  if (mRecomputeWorldTransformation) {
//    std::cout << "recompute Actor::getWorldTransformation" << std::endl;
    mWorldTransformation = glm::translate(mPosition) *
                           glm::mat4_cast(mRotation) * glm::scale(mScale);
  }
  return mWorldTransformation;
}

void Actor::processInput(const InputState &input) {
  if (mState == EActive) {
    for (auto &comp : mComponents) {
      comp->processInput(input);
    }
  }

  actorInput(input);
}

void Actor::actorInput(const InputState &input) {}

const glm::vec3 &Actor::getPosition() const { return mPosition; }

glm::vec3 Actor::getForwardVector() const {
  return glm::mat3_cast(mRotation) * glm::vec3(1.0f, 0.0f, 0.0f);
}

glm::vec3 Actor::getLeftVector() const {
  return glm::mat3_cast(mRotation) * glm::vec3(0.0f, 1.0f, 0.0f);
}

void Actor::computeWorldTransformation() {
  if (mRecomputeWorldTransformation) {
    mRecomputeWorldTransformation = false;
    mWorldTransformation = glm::translate(mPosition) *
                           glm::mat4_cast(mRotation) * glm::scale(mScale);
  }
}

const glm::quat &Actor::getRotation() const { return mRotation; }
