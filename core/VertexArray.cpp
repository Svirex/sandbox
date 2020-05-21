//
// Created by svirex on 04.02.2020.
//

#include "VertexArray.h"
#include "consts.h"

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

  glEnableVertexAttribArray(VERTEX_ATTRIB_POINTER_INDEX);
  glVertexAttribPointer(VERTEX_ATTRIB_POINTER_INDEX, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);

  glBindVertexArray(0);
}

VertexArray::~VertexArray() {
  glDeleteBuffers(1, &mVertexBuffer);
  glDeleteBuffers(1, &mIndexBuffer);
  glDeleteBuffers(1, &mTextureCoordsBuffer);
  glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::setActive() { glBindVertexArray(mVertexArray); }

void VertexArray::deactivate() { glBindVertexArray(0); }

size_t VertexArray::getNumIndices() { return mNumIndices; }

size_t VertexArray::getNumVertices() { return mNumVertex; }

void VertexArray::setTextureCoords(const GLfloat *textureCoords) {
  glBindVertexArray(mVertexArray);

  glGenBuffers(1, &mTextureCoordsBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, mTextureCoordsBuffer);
  glBufferData(GL_ARRAY_BUFFER, mNumVertex * 2 * sizeof(GLfloat), textureCoords,
               GL_STATIC_DRAW);

  glEnableVertexAttribArray(TEXTURE_COORDS_LAYOUT_LOCATION);
  glVertexAttribPointer(TEXTURE_COORDS_LAYOUT_LOCATION, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

  glBindVertexArray(0);
}
