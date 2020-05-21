//
// Created by svirex on 03.02.2020.
//

#include <string>
#include <vector>

#include <spdlog/spdlog.h>

#include "Mesh.h"
#include "VertexArray.h"
#include "Material.h"
#include "Shader.h"

Mesh::~Mesh() {
  delete mVertexArray;
  mVertexArray = nullptr;

  delete mShader;
  mShader = nullptr;
}

std::vector<float> &Mesh::getVertexCoordinateRef() { return mVertexCoordinate; }

std::vector<unsigned> &Mesh::getVertexIndicesRef() { return mVertexIndices; }

bool Mesh::loadToGPU() {
  if (!mVertexArray) {
    mVertexArray =
        new VertexArray(mVertexCoordinate.data(), mVertexCoordinate.size(),
                        mVertexIndices.data(), mVertexIndices.size());
    if (mHasTextureCoords) {
      mVertexArray->setTextureCoords(mTextureCoords.data());
    }
  }
  if (!mMaterial->loadToGPU()) {
    spdlog::error("Couldn't load material to GPU");
    return false;
  }

  if (!mShader->loadToGPU()) {
    spdlog::error("Couldn't load shader to GPU");
    return false;
  }
  return true;
}

bool Mesh::unloadFromGPU() {
  delete mVertexArray;
  mVertexArray = nullptr;

  mMaterial->unloadFromGPU();
  mShader->unloadFromGPU();

  return true;
}


VertexArray *Mesh::getVertexArray() const { return mVertexArray; }

std::vector<float> &Mesh::getTextureCoordsRef() { return mTextureCoords; }

void Mesh::draw() {
  mVertexArray->setActive();
  mMaterial->active();
  GLint program, sampler;
  GLint texture;
  glGetIntegerv(GL_CURRENT_PROGRAM, &program);
  glGetIntegerv(GL_SAMPLER_BINDING, &sampler);
  glGetIntegerv(GL_TEXTURE_BINDING_2D, &texture);

//  spdlog::debug("Current program {}, sampler {}, texture {}", program, sampler, texture);

  glDrawElements(GL_TRIANGLES, mVertexArray->getNumIndices(),
                 GL_UNSIGNED_INT, nullptr);

  mMaterial->deactivate();
  mVertexArray->deactivate();

}
