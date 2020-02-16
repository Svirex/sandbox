//
// Created by svirex on 03.02.2020.
//

#ifndef SANDBOX_MESH_H
#define SANDBOX_MESH_H

#include <string>


class Renderer;
class VertexArray;
class Shader;

class Mesh {
public:
  Mesh();

  bool load(const std::string &filePath, Renderer *renderer);

  Shader *getShader() const;

  VertexArray *getVertexArray() const;

private:
  VertexArray *mVertexArray;

  Shader *mShader;
};

#endif // SANDBOX_MESH_H
