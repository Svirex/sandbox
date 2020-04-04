//
// Created by svirex on 02.04.2020.
//

#ifndef SANDBOX_CAMERACOMPONENT_H
#define SANDBOX_CAMERACOMPONENT_H

#include <glm/mat4x4.hpp>

#include "../Component.h"
#include "../system/ObjectManager.h"

class Actor;

class CameraComponent: public Component {
public:
  CameraComponent(Actor *owner, int updateOrder = 200);

  MANAGE(CameraComponent)

protected:
  void setViewMatrix(const glm::mat4 &view);
};

#endif // SANDBOX_CAMERACOMPONENT_H
