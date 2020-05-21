//
// Created by svirex on 03.02.2020.
//

#ifndef SANDBOX_MESH_H
#define SANDBOX_MESH_H

#include <string>
#include <vector>

#include <GL/glew.h>

#include "system/ObjectManager.h"

class Renderer;
class VertexArray;
class Shader;
// class MeshLoader;
class Material;
class ResourceManager;

class Mesh {
public:
  friend class ResourceManager;

  Mesh() = default;

  //  Mesh(const GLfloat *vertex, size_t nVertex);

  ~Mesh();

  //  bool load(const std::string &filePath, Renderer *renderer);

  //  Shader *getShader() const;

  VertexArray *getVertexArray() const;

  std::vector<float> &getVertexCoordinateRef();

  std::vector<unsigned> &getVertexIndicesRef();

  std::vector<float> &getTextureCoordsRef();

  bool loadToGPU();

  bool unloadFromGPU();

  bool hasTextureCoords() const { return mHasTextureCoords; }

  void setMaterial(Material *material) { mMaterial = material; }

  void setShader(Shader *shader) { mShader = shader; }

  Shader *getShader() const {
    return mShader;
  }

  void draw();

  void setName(const std::string &name) {
    mName = name;
  }

  const std::string &getName() const {
    return mName;
  }

  MANAGE(Mesh)

private:
  VertexArray *mVertexArray = nullptr;

  Shader *mShader = nullptr;

  //  MeshLoader *mMeshLoader = nullptr;

  std::vector<float> mVertexCoordinate;

  std::vector<unsigned> mVertexIndices;

  std::vector<float> mTextureCoords;

  bool mHasTextureCoords = false;

  Material *mMaterial = nullptr;

  std::string mName;
};

#endif // SANDBOX_MESH_H
