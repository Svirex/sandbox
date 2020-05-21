//
// Created by svirex on 16.05.2020.
//

#ifndef SANDBOX_TEXTURE_H
#define SANDBOX_TEXTURE_H

#include <GL/glew.h>

#include "system/ObjectManager.h"

class Texture {
public:

  explicit Texture(unsigned char *data, size_t width, size_t height);

  ~Texture();

  bool loadToGPU();

  bool unloadFromGPU();

  bool bind(size_t unit) const;

  void unbind(size_t unit) const;

  MANAGE(Texture)

private:
  unsigned char *mData = nullptr;

  size_t mWidth = 0;

  size_t mHeight = 0;

  GLuint mGLTexture = 0;

  GLuint mSampler = 0;

  GLenum mType = GL_TEXTURE_2D;
};

#endif // SANDBOX_TEXTURE_H
