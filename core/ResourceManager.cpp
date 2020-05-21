//
// Created by svirex on 13.04.2020.
//

#include <iterator>
#include <vector>

#include "spdlog/spdlog.h"
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <SOIL/SOIL.h>

#include "Mesh.h"
#include "ResourceManager.h"
#include "Material.h"
#include "Texture.h"
#include "ShaderBuilder.h"
#include "Shader.h"

ResourceManager::ResourceManager(Game *game) : mGame(game) {
  mShaderBuilder = new ShaderBuilder(this);
}

bool ResourceManager::init() {
  if (!mShaderBuilder->init()) {
    spdlog::error("Couldn't init ShaderBuilder");
    return false;
  }
  return true;
}

bool ResourceManager::loadMeshesFromFile(const std::string &filePath) {
  const aiScene *scene = mAssimpImporter.ReadFile(
      filePath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices |
                    aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph |
                    aiProcess_RemoveRedundantMaterials);
  if (!scene) {
    spdlog::error("Couldn't read meshes from file {}: {}", filePath,
                  mAssimpImporter.GetErrorString());
    return false;
  }
  const aiNode *rootNode = scene->mRootNode;
  processNode(scene, rootNode);

  mAssimpImporter.FreeScene();

  return true;
}

ResourceManager::~ResourceManager() {
//  spdlog::debug("ResourceManager::~ResourceManager: Clear mMeshes");
  for (auto &elem : mMeshes) {
    delete elem.second;
  }
//  spdlog::debug("ResourceManager::~ResourceManager: Clear mMaterials");
  for (auto &elem : mMaterials) {
    delete elem.second;
  }
//  spdlog::debug("ResourceManager::~ResourceManager: Clear mTextures");
  for (auto &elem : mTextures) {
    delete elem.second;
  }

  delete mShaderBuilder;
}

Mesh *ResourceManager::getMesh(const std::string &meshName) {
  auto iter = mMeshes.find(meshName);
  if (iter != mMeshes.end()) {
    return iter->second;
  } else {
    return nullptr;
  }
}

void ResourceManager::processNode(const aiScene *scene, const aiNode *node) {
  for (unsigned i = 0; i < node->mNumMeshes; ++i) {
    auto *myMesh = new Mesh();
    auto &vertices = myMesh->getVertexCoordinateRef();
    auto &indices = myMesh->getVertexIndicesRef();
    auto &textureCoords = myMesh->getTextureCoordsRef();
    const unsigned meshIndex = node->mMeshes[i];
    const auto &mesh = scene->mMeshes[meshIndex];

    myMesh->setName(std::string(mesh->mName.C_Str()));

    for (unsigned j = 0; j < mesh->mNumVertices; ++j) {
      auto vertex = mesh->mVertices[j];
      vertices.push_back(vertex.x);
      vertices.push_back(vertex.y);
      vertices.push_back(vertex.z);
    }

    if (mesh->HasTextureCoords(0)) {
      myMesh->mHasTextureCoords = true;
      for (unsigned j = 0; j < mesh->mNumVertices; ++j) {
        auto &tc = mesh->mTextureCoords[0][j];
        textureCoords.push_back(tc.x);
        textureCoords.push_back(1 - tc.y);
      }
    }

    for (unsigned j = 0; j < mesh->mNumFaces; ++j) {
      auto &face = mesh->mFaces[j];
      indices.push_back(face.mIndices[0]);
      indices.push_back(face.mIndices[1]);
      indices.push_back(face.mIndices[2]);
    }

    auto materialIndex = mesh->mMaterialIndex;
    auto *meshMaterial = scene->mMaterials[materialIndex];
    aiString meshMaterialName;
    meshMaterial->Get(AI_MATKEY_NAME, meshMaterialName);
    auto *material = getMaterial(meshMaterialName.C_Str());
    if (!material) {
      material = new Material(this, meshMaterialName.C_Str(), meshMaterial);
    }

    myMesh->setMaterial(material);
    myMesh->setShader(mShaderBuilder->build(myMesh, material));



    mMeshes[std::string(mesh->mName.C_Str())] = myMesh;
  }

  for (unsigned i = 0; i < node->mNumChildren; i++) {
    const aiNode *nextNode = node->mChildren[i];
    processNode(scene, nextNode);
  }
}

void ResourceManager::showShaderCode() const {
  std::string vertexCode, fragmentCode;
  for (const auto &elem : mMeshes) {
    auto *shader = elem.second->getShader();
    shader->getSource(vertexCode, fragmentCode);
//    shader->getSourceIn(vertexCode, fragmentCode);
    std::cout << "Mesh: " << elem.first << std::endl;
    std::cout << "Vertex Code: \n" << vertexCode << std::endl;
    std::cout << "Fragment Code: \n" << fragmentCode << std::endl;
  }
}

bool ResourceManager::loadMeshesToGPU() {
  for( const auto &mesh : mMeshes) {
    if (!mesh.second->loadToGPU()) {
      return false;
    }
  }
  return true;
}

bool ResourceManager::unloadMeshesFromGPU() {
  for( const auto &mesh : mMeshes) {
    spdlog::trace("unloadFromGPU for mesh {}", mesh.first);
    mesh.second->unloadFromGPU();
  }
  return true;
}

void ResourceManager::addMaterial(const std::string &name, Material *material) {
  mMaterials[name] = material;
}

Material *ResourceManager::getMaterial(const std::string &name) {
  auto iter = mMaterials.find(name);
  if (iter != mMaterials.end()) {
    return iter->second;
  } else {
    return nullptr;
  }
}

void ResourceManager::addTexture(const std::string &filePath, Texture *texture) {
  mTextures[filePath] = texture;
}

Texture *ResourceManager::getTexture(const std::string &filePath) {
  spdlog::trace("ResourceManager::getTexture: {}", filePath);
  auto iter = mTextures.find(filePath);
  if (iter != mTextures.end()) {
    spdlog::trace("ResourceManager::getTexture {} texture finded in mTextures", filePath);
    return iter->second;
  } else {
    auto result = loadTextureFromFile(filePath);
    spdlog::trace("ResourceManager::getTexture {} texture loaded from file with result {}", filePath, result.first);
    if(result.first) {
      return result.second;
    } else {
      return nullptr;
    }
  }
}

std::pair<bool, Texture *> ResourceManager::loadTextureFromFile(const std::string &filePath) {
  int width = 0, height = 0, channels = 0;
  auto *imageData = SOIL_load_image(filePath.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);
  spdlog::debug("RloadTextureFromFile {} channels {}", filePath, channels);
  if (!imageData) {
    spdlog::error("Couldn't load texture from {}", filePath);
    return {false, nullptr};
  }
  auto *texture = new Texture(imageData, width, height);
  mTextures[filePath] = texture;
  return {true, texture};
}
