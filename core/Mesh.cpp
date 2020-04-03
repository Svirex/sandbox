//
// Created by svirex on 03.02.2020.
//

#include <vector>
#include <string>

#include "Mesh.h"
#include "utils/MeshLoader.h"
#include "VertexArray.h"
#include "Renderer.h"

const std::string SHADER_NAME = "basicMesh";

//Mesh::Mesh(): mVertexArray(nullptr), mShader(nullptr) {}

Mesh::~Mesh() {
  delete mVertexArray;
  mVertexArray = nullptr;

  delete mMeshLoader;
  mMeshLoader = nullptr;
}

bool Mesh::load(const std::string &filePath, Renderer *renderer) {
  if (!mMeshLoader) {
    mMeshLoader = new MeshLoader();
  }
  std::vector<GLfloat> vertex;
  std::vector<GLuint> indices;
  if(!mMeshLoader->load(filePath, vertex, indices)) {
    return false;
  }
  mVertexArray = new VertexArray(vertex.data(), vertex.size(), indices.data(), indices.size());
  mShader = renderer->getShader(SHADER_NAME);
  return true;
}

Shader *Mesh::getShader() const { return mShader; }

VertexArray *Mesh::getVertexArray() const { return mVertexArray; }
