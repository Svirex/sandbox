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
class MeshLoader;

class Mesh {
public:
  Mesh() = default;

//  Mesh(const GLfloat *vertex, size_t nVertex);

  ~Mesh();

//  bool load(const std::string &filePath, Renderer *renderer);

//  Shader *getShader() const;

  VertexArray *getVertexArray() const;

  std::vector<float> &getVertexCoordinateRef();

  std::vector<unsigned> &getVertexIndicesRef();

  bool loadToGPU();

  bool unloadFromGPU();

  MANAGE(Mesh)

private:
  VertexArray *mVertexArray = nullptr;

//  Shader *mShader = nullptr;

//  MeshLoader *mMeshLoader = nullptr;

  std::vector<float> mVertexCoordinate;

  std::vector<unsigned> mVertexIndices;
};

#endif // SANDBOX_MESH_H
