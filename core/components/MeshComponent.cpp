//
// Created by svirex on 04.02.2020.
//

#include <iostream>

#include <glm/gtx/string_cast.hpp>
#include "spdlog/spdlog.h"

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

void MeshComponent::draw(Shader *shader, const glm::mat4 &view,
                         const glm::mat4 &projection) {
  if (mMesh) {
    auto *activeShader = shader;
    if (activeShader) {
      activeShader->setActive();
      activeShader->setUniform("uViewProjection",
                               projection * view *
                                   mOwner->getWorldTransformation());
      VertexArray *vertexArray = mMesh->getVertexArray();
      vertexArray->setActive();
        glDrawElements(GL_TRIANGLES, vertexArray->getNumIndices(),
                       GL_UNSIGNED_INT, nullptr);
    }
  }
}
