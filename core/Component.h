//
// Created by svirex on 30.01.2020.
//

#ifndef SANDBOX_COMPONENT_H
#define SANDBOX_COMPONENT_H

class Actor;
class InputState;

class Component {
public:
  explicit Component(Actor *owner, int updateOrder = 100);

  virtual ~Component();

  int getUpdateOrder() const;

  virtual void update(float deltaTime);

  virtual void processInput(const InputState &input);

protected:
  Actor *mOwner;

  int mUpdateOrder;
};

#endif // SANDBOX_COMPONENT_H
