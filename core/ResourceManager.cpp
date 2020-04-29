//
// Created by svirex on 13.04.2020.
//

#include <iterator>
#include <vector>

#include "spdlog/spdlog.h"
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "Mesh.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager(Game *game) : mGame(game) {}

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
  for (auto &elem : mMeshes) {
    delete elem.second;
  }
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
    std::vector<float> &vertices = myMesh->getVertexCoordinateRef();
    std::vector<unsigned> &indices = myMesh->getVertexIndicesRef();
    const unsigned meshIndex = node->mMeshes[i];
    const auto &mesh = scene->mMeshes[meshIndex];
    for (unsigned j = 0; j < mesh->mNumVertices; ++j) {
      auto vertex = mesh->mVertices[j];
      vertices.push_back(vertex.x);
      vertices.push_back(vertex.y);
      vertices.push_back(vertex.z);
    }
    for (unsigned j = 0; j < mesh->mNumFaces; ++j) {
      auto &face = mesh->mFaces[j];
      indices.push_back(face.mIndices[0]);
      indices.push_back(face.mIndices[1]);
      indices.push_back(face.mIndices[2]);
    }
    mMeshes[std::string(mesh->mName.C_Str())] = myMesh;
  }

  for (unsigned i = 0; i < node->mNumChildren; i++) {
    const aiNode *nextNode = node->mChildren[i];
    processNode(scene, nextNode);
  }
}

bool ResourceManager::loadMeshesToGPU() {
  for( const auto &mesh : mMeshes) {
    mesh.second->loadToGPU();
  }
  return true;
}

bool ResourceManager::unloadMeshesFromGPU() {
  for( const auto &mesh : mMeshes) {
    mesh.second->unloadFromGPU();
  }
  return true;
}
