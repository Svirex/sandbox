//
// Created by svirex on 13.04.2020.
//

#ifndef SANDBOX_RESOURCEMANAGER_H
#define SANDBOX_RESOURCEMANAGER_H

#include <unordered_map>
#include <string>
#include <utility>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include "system/ObjectManager.h"

class Game;
class Mesh;
class Material;
class Texture;
class ShaderBuilder;

class ResourceManager {
public:
  explicit ResourceManager(Game *game);

  ~ResourceManager();

  bool loadMeshesFromFile(const std::string &filePath);

  Mesh *getMesh(const std::string &meshName);

  /***
   * Loading data to the GPU after loading all data from the disk
   *
   * @return
   */
  bool loadMeshesToGPU(); //TODO сделать возможность передачи списка названия мешей, которые надо загрузить

  bool unloadMeshesFromGPU();

  void addMaterial(const std::string &name, Material *material);

  Material *getMaterial(const std::string &name);

  void addTexture(const std::string &filePath, Texture *texture);

  Texture *getTexture(const std::string &filePath);

  bool init();

  void showShaderCode() const;

  MANAGE(ResourceManager)

private:

  std::pair<bool, Texture *> loadTextureFromFile(const std::string &filePath);

  Assimp::Importer mAssimpImporter;

  Game *mGame;

  std::unordered_map<std::string, Mesh *> mMeshes;

  std::unordered_map<std::string, Texture *> mTextures;

  std::unordered_map<std::string, Material *> mMaterials;

  void processNode(const aiScene *scene, const aiNode *node);

  ShaderBuilder *mShaderBuilder = nullptr;
};

#endif // SANDBOX_RESOURCEMANAGER_H
