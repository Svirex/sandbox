//
// Created by svirex on 02.04.2020.
//

#include <iostream>

#include "CameraComponent.h"
#include "../Actor.h"
#include "../Renderer.h"
#include "../Game.h"

CameraComponent::CameraComponent(Actor *owner, int updateOrder) : Component(owner, updateOrder) {

}

void CameraComponent::setViewMatrix(const glm::mat4 &view) {
  auto *renderer = mOwner->getGame()->getRenderer();
  renderer->setViewMatrix(view);
//  std::cout << "CameraComponent::setViewMatrix" << std::endl;
}
