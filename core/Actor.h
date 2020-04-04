//
// Created by svirex on 28.01.2020.
//

#ifndef SANDBOX_ACTOR_H
#define SANDBOX_ACTOR_H

#include <vector>

#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "system/ObjectManager.h"

class Game;
class Component;
class InputState;

class Actor {
public:
  enum State {
    EActive,
    EPaused,
    EDead
  };

  explicit Actor(Game *game);

  virtual ~Actor();

  void setPosition(const glm::vec3 &position);

  const glm::vec3 &getPosition() const;

  void setRotation(const glm::quat &rotation);

  void setScale(const glm::vec3 &scale);

  const glm::quat &getRotation() const;

  void addComponent(Component *component);

  void removeComponent(Component *component);

  void update(float deltaTime);

  void setState(State state);

  State getState() const;

  Game *getGame() const;

  glm::mat4 getWorldTransformation();

  void computeWorldTransformation();

  void processInput(const InputState &input);

  virtual void actorInput(const InputState &input);

  glm::vec3 getForwardVector() const;

  glm::vec3 getLeftVector() const;

  MANAGE(Actor)

protected:
  virtual void tick(float deltaTime);


private:
  glm::vec3 mPosition;

  glm::quat mRotation;

  glm::vec3 mScale;

  Game *mGame;

  std::vector<Component *> mComponents;

  State mState;

  void updateComponents(float deltaTime);

  bool mRecomputeWorldTransformation;

  glm::mat4 mWorldTransformation;
};

#endif // SANDBOX_ACTOR_H
