//
// Created by svirex on 04.02.2020.
//

#ifndef SANDBOX_VERTEXARRAY_H
#define SANDBOX_VERTEXARRAY_H

#include <GL/glew.h>

#include "system/ObjectManager.h"

class VertexArray {
public:
  VertexArray(const GLfloat *vertex, size_t nVertex, const GLuint *indices, size_t nIndices);


  ~VertexArray();

  void setActive();

  void deactivate();

  size_t getNumIndices();

  size_t getNumVertices();

  void setTextureCoords(const GLfloat *textureCoords);

  MANAGE(VertexArray)

private:
  GLuint mVertexArray = 0;

  GLuint mVertexBuffer = 0;

  GLuint mIndexBuffer = 0;

  GLuint mTextureCoordsBuffer = 0;

  size_t mNumVertex = 0;

  size_t mNumIndices = 0;
};

#endif // SANDBOX_VERTEXARRAY_H
