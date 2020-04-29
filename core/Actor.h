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

/**
 * Класс, реализующий любой объект в мире
 */
class Actor {
public:
  /**
   * Состояние актора
   */
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

  /**
   * Обновление состояние актора
   *
   */
  void update(float deltaTime);

  void setState(State state);

  State getState() const;

  Game *getGame() const;

  /**
   * Получение матрицы трансформации в мировом пространстве
   *
   */
  glm::mat4 getWorldTransformation();

  /**
   * Пересчитать матрицу трансформации
   */
  void computeWorldTransformation();

  /**
   * Обработка ввода
   */
  void processInput(const InputState &input);

  /**
   * Обработка специфичного для актора ввода
   */
  virtual void actorInput(const InputState &input);

  glm::vec3 getForwardVector() const;

  glm::vec3 getLeftVector() const;

  MANAGE(Actor)

protected:

  /**
   * Специфичное для актора обновление состояние
   *
   * Выполняется на каждом фрейме
   *
   * @param deltaTime Дельта времени после предыдущего фрейма
   */
  virtual void tick(float deltaTime);


private:
  glm::vec3 mPosition; /// Позиция актора

  glm::quat mRotation; /// Поворот актора

  glm::vec3 mScale; /// Масштабирование

  Game *mGame; /// Указатель на объект игры

  std::vector<Component *> mComponents; /// Вектор компонент актора

  State mState; /// Состояние актора

  bool mRecomputeWorldTransformation; /// Пересчитать ли матрицу трансформации

  glm::mat4 mWorldTransformation; /// Матрица транформации актора

  /**
   * Обновление компонент актора
   *
   * @param deltaTime
   */
  void updateComponents(float deltaTime);
};

#endif // SANDBOX_ACTOR_H
