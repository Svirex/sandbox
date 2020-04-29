//
// Created by svirex on 03.02.2020.
//

#include <string>
#include <vector>

#include "Mesh.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "utils/MeshLoader.h"

const std::string SHADER_NAME = "basicMesh";

Mesh::~Mesh() {
  delete mVertexArray;
  mVertexArray = nullptr;

}

std::vector<float> &Mesh::getVertexCoordinateRef() { return mVertexCoordinate; }

std::vector<unsigned> &Mesh::getVertexIndicesRef() { return mVertexIndices; }

bool Mesh::loadToGPU() {
  if (!mVertexArray) {
    mVertexArray =
        new VertexArray(mVertexCoordinate.data(), mVertexCoordinate.size(),
                        mVertexIndices.data(), mVertexIndices.size());
  }
  return true;
}

bool Mesh::unloadFromGPU() {
  delete mVertexArray;
  mVertexArray = nullptr;
  return true;
}


VertexArray *Mesh::getVertexArray() const { return mVertexArray; }
