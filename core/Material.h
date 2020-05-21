//
// Created by svirex on 17.05.2020.
//

#ifndef SANDBOX_MATERIAL_H
#define SANDBOX_MATERIAL_H

#include <string>

#include <assimp/material.h>
#include <glm/vec3.hpp>

#include "system/ObjectManager.h"

class Texture;
class ResourceManager;

class Material {
public:
  Material(ResourceManager *rm, const std::string &name,
           const aiMaterial *material);

  ~Material() noexcept = default;

//  bool setData(const aiMaterial *material);

  const glm::vec3 &getDiffuseColor() const {
    return mDiffuseColor;
  }

  bool hasDiffuseColor () const {
    return mExistDiffuseColor;
  }

  bool hasDiffuseTexture() const {
    return mExistDiffuseTexture;
  }

  bool loadToGPU();

  bool unloadFromGPU();

  void active();

  void deactivate();

  MANAGE(Material)

private:

  void processMaterial(const aiMaterial *material);

  void processDiffuseColor(const aiMaterial *material);

  void processDiffuseTexture(const aiMaterial *material);

  ResourceManager *mResourceManager = nullptr;

  std::string mName;

  glm::vec3 mDiffuseColor = glm::vec3(0.0);

  Texture *mDiffuseTexture = nullptr;

  bool mExistDiffuseColor = false;

  bool mExistDiffuseTexture = false;
};

#endif // SANDBOX_MATERIAL_H
