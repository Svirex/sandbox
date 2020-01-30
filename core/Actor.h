//
// Created by svirex on 28.01.2020.
//

#ifndef SANDBOX_ACTOR_H
#define SANDBOX_ACTOR_H

#include <vector>

#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>

class Game;
class Component;

class Actor {
public:
  enum State {
    EActive,
    EPaused,
    EDead
  };

  explicit Actor(Game *game);

  virtual ~Actor();

  void setPosition(glm::vec3 &position);

  void setRotation(glm::quat &rotation);

  void setScale(float scale);

  void addComponent(Component *component);

  void removeComponent(Component *component);

  void update(float deltaTime);

  void setState(State state);

  State getState() const;

protected:
  virtual void tick(float deltaTime);


private:
  glm::vec3 mPosition;

  glm::quat mRotation;

  float mScale;

  Game *mGame;

  std::vector<Component *> mComponents;

  State mState;

  void updateComponents(float deltaTime);
};

#endif // SANDBOX_ACTOR_H
