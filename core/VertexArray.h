//
// Created by svirex on 04.02.2020.
//

#ifndef SANDBOX_VERTEXARRAY_H
#define SANDBOX_VERTEXARRAY_H

#include <GL/glew.h>

class VertexArray {
public:
  VertexArray(const GLfloat *vertex, size_t nVertex, const GLuint *indices, size_t nIndices);

  ~VertexArray();

  void setActive();

  size_t getNumIndices();

private:
  GLuint mVertexArray;

  GLuint mVertexBuffer;

  GLuint mIndexBuffer;

  size_t mNumVertex;

  size_t mNumIndices;
};

#endif // SANDBOX_VERTEXARRAY_H
