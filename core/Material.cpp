//
// Created by svirex on 17.05.2020.
//

#include "spdlog/spdlog.h"

#include "Material.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "consts.h"

Material::Material(ResourceManager *rm, const std::string &name,
                   const aiMaterial *material)
    : mResourceManager(rm) {
  mName = name;
  mResourceManager->addMaterial(mName, this);
  processMaterial(material);
}

void Material::processMaterial(const aiMaterial *material) {
  processDiffuseColor(material);
  processDiffuseTexture(material);
}

void Material::processDiffuseColor(const aiMaterial *material) {
  aiColor3D diffuse;
  material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
  mDiffuseColor = glm::vec3(diffuse.r, diffuse.g, diffuse.b);
  mExistDiffuseColor = true;
}

void Material::processDiffuseTexture(const aiMaterial *material) {
  if (aiGetMaterialTextureCount(material, aiTextureType_DIFFUSE) > 0) {
    aiString textureDiffuse;
    material->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), textureDiffuse);
    mDiffuseTexture = mResourceManager->getTexture(textureDiffuse.C_Str());
    mExistDiffuseTexture = true;
  }
}

bool Material::loadToGPU() {
  if (mDiffuseTexture) {
    if (!mDiffuseTexture->loadToGPU()) {
      spdlog::error("Couldn't load diffuse texture to GPU");
      return false;
    }
  }

  return true;
}

bool Material::unloadFromGPU() {
  if (mDiffuseTexture) {
    mDiffuseTexture->unloadFromGPU();
  }
  return true;
}

void Material::active() {
  if (mDiffuseTexture) {
    mDiffuseTexture->bind(DIFFUSE_TEXTURE_LAYOUT_BINDING);
  }
}

void Material::deactivate() {
  if (mDiffuseTexture) {
    mDiffuseTexture->unbind(DIFFUSE_TEXTURE_LAYOUT_BINDING);
  }
}
