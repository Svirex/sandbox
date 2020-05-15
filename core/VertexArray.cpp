//
// Created by svirex on 04.02.2020.
//

#include "VertexArray.h"

VertexArray::VertexArray(const GLfloat *vertex, size_t nVertex,
                         const GLuint *indices, size_t nIndices)
    : mNumVertex(nVertex), mNumIndices(nIndices) {
  glGenVertexArrays(1, &mVertexArray);
  glBindVertexArray(mVertexArray);

  glGenBuffers(1, &mVertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, mNumVertex * 3 * sizeof(GLfloat), vertex,
               GL_STATIC_DRAW);

  glGenBuffers(1, &mIndexBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, mNumIndices * sizeof(GLuint), indices,
               GL_STATIC_DRAW);

  glEnableVertexAttribArray(10);
  glVertexAttribPointer(10, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);

  ++mLastAttribPointerNum;

//  glEnableVertexAttribArray(1);
//  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
//                        reinterpret_cast<void *>(sizeof(GLfloat) * 3));

  glBindVertexArray(0);
}

VertexArray::~VertexArray() {
  glDeleteBuffers(1, &mVertexBuffer);
  glDeleteBuffers(1, &mIndexBuffer);
  glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::setActive() { glBindVertexArray(mVertexArray); }

size_t VertexArray::getNumIndices() { return mNumIndices; }

size_t VertexArray::getNumVertices() { return mNumVertex; }
