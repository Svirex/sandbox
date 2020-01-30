//
// Created by svirex on 28.01.2020.
//

#include <algorithm>

#include "Actor.h"
#include "Component.h"
#include "Game.h"

Actor::Actor(Game *game)
    : mPosition(glm::vec3(0.0f)), mRotation(glm::identity<glm::quat>()),
      mScale(1.0f), mGame(game), mState(EActive) {
  mGame->addActor(this);
}

Actor::~Actor() {
  mGame->removeActor(this);
  while (!mComponents.empty()) {
    delete mComponents.back();
  }
}

void Actor::setPosition(glm::vec3 &position) { mPosition = position; }

void Actor::setRotation(glm::quat &rotation) { mRotation = rotation; }

void Actor::setScale(float scale) { mScale = scale; }

void Actor::addComponent(Component *component) {
  int order = component->getUpdateOrder();
  auto iter = std::find_if(
      mComponents.begin(), mComponents.end(),
      [order](Component *comp) { return order < comp->getUpdateOrder(); });
  if (iter != mComponents.end()) {
    mComponents.insert(iter, component);
  }
}

void Actor::removeComponent(Component *component) {
  auto iter = std::find(mComponents.begin(), mComponents.end(), component);
  if (iter != mComponents.end()) {
    mComponents.erase(iter);
  }
}

void Actor::update(float deltaTime) {
  if (mState == EActive) {
    updateComponents(deltaTime);
    tick(deltaTime);
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
