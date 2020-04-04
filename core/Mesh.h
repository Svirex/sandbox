//
// Created by svirex on 03.02.2020.
//

#ifndef SANDBOX_MESH_H
#define SANDBOX_MESH_H

#include <string>

#include "system/ObjectManager.h"


class Renderer;
class VertexArray;
class Shader;
class MeshLoader;

class Mesh {
public:
  Mesh() = default;

  ~Mesh();

  bool load(const std::string &filePath, Renderer *renderer);

  Shader *getShader() const;

  VertexArray *getVertexArray() const;

  MANAGE(Mesh)

private:
  VertexArray *mVertexArray = nullptr;

  Shader *mShader = nullptr;

  MeshLoader *mMeshLoader = nullptr;
};

#endif // SANDBOX_MESH_H
