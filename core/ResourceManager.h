//
// Created by svirex on 13.04.2020.
//

#ifndef SANDBOX_RESOURCEMANAGER_H
#define SANDBOX_RESOURCEMANAGER_H

#include <unordered_map>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include "system/ObjectManager.h"

class Game;
class Mesh;

class ResourceManager {
public:
  explicit ResourceManager(Game *game);

  ~ResourceManager();

  bool loadMeshesFromFile(const std::string &filePath);

  Mesh *getMesh(const std::string &meshName);

  bool loadMeshesToGPU(); //TODO сделать возможность передачи списка названия мешей, которые надо загрузить

  bool unloadMeshesFromGPU();

  MANAGE(ResourceManager)

private:
  Assimp::Importer mAssimpImporter;

  Game *mGame;

  std::unordered_map<std::string, Mesh *> mMeshes;

  void processNode(const aiScene *scene, const aiNode *node);
};

#endif // SANDBOX_RESOURCEMANAGER_H
