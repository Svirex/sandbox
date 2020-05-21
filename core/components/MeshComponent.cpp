//
// Created by svirex on 04.02.2020.
//

#include <iostream>

#include "spdlog/spdlog.h"
#include <glm/gtx/string_cast.hpp>

#include "../Actor.h"
#include "../Game.h"
#include "../Mesh.h"
#include "../Renderer.h"
#include "../Shader.h"
#include "../VertexArray.h"
#include "MeshComponent.h"

MeshComponent::MeshComponent(Actor *owner) : Component(owner), mMesh(nullptr) {
  mOwner->getGame()->getRenderer()->addMeshComponent(this);
}

MeshComponent::~MeshComponent() {
  mOwner->getGame()->getRenderer()->removeMeshComponent(this);
}

void MeshComponent::setMesh(Mesh *mesh) { mMesh = mesh; }

void MeshComponent::draw(const glm::mat4 &view, const glm::mat4 &projection) {
  if (mMesh) {
//    spdlog::trace("Draw {} mesh", mMesh->getName());
    auto *shader = mMesh->getShader();
    if (shader) {
      shader->setActive();
      shader->setUniform("uViewProjection",
                         projection * view * mOwner->getWorldTransformation());
      mMesh->draw();
    }
  }
}
