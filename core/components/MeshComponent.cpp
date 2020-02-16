//
// Created by svirex on 04.02.2020.
//

#include "MeshComponent.h"
#include "../Actor.h"
#include "../Game.h"
#include "../Mesh.h"
#include "../Renderer.h"
#include "../Shader.h"
#include "../VertexArray.h"

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
    if (!activeShader) {
      activeShader = mMesh->getShader();
    }
    if (activeShader) {
      activeShader->setActive();
      activeShader->setUniform("uTransformation",
                               projection * view * mOwner->getWorldTransformation());
      activeShader->setUniform("uColor", glm::vec3(1.0f, 1.0f, 1.0f));
      VertexArray *vertexArray = mMesh->getVertexArray();
      vertexArray->setActive();
      glDrawElements(GL_TRIANGLES, vertexArray->getNumIndices(),
                     GL_UNSIGNED_INT, nullptr);
      activeShader->setUniform("uColor", glm::vec3(0.0f, 0.0f, 0.0f));
      glDrawElements(GL_LINES, vertexArray->getNumIndices(), GL_UNSIGNED_INT,
                     nullptr);
    }
  }
}
