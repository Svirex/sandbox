//
// Created by svirex on 16.05.2020.
//

#include "Texture.h"

Texture::Texture(unsigned char *data, size_t width, size_t height)
    : mData(data), mWidth(width), mHeight(height) {}

Texture::~Texture() {
  unloadFromGPU();
  delete [] mData;
}

bool Texture::loadToGPU() {
  GLenum err;
  glCreateTextures(mType, 1, &mGLTexture);
  while ((err = glGetError()) != GL_NO_ERROR) {
    std::cout << "Texture::loadToGPU glCreateTextures ERROR " << err << " " << (err == GL_INVALID_OPERATION) <<
              " " << (err == GL_INVALID_VALUE) <<
              " " << (err == GL_INVALID_ENUM) <<
              std::endl;
  }
  glTextureStorage2D(mGLTexture, 1, GL_RGB8, mWidth, mHeight);
  while ((err = glGetError()) != GL_NO_ERROR) {
    std::cout << "Texture::loadToGPU glTextureStorage2D ERROR " << err << " " << (err == GL_INVALID_OPERATION) <<
              " " << (err == GL_INVALID_VALUE) <<
              " " << (err == GL_INVALID_ENUM) <<
              std::endl;
  }
  glTextureSubImage2D(mGLTexture, 0, 0, 0, mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, mData);

  while ((err = glGetError()) != GL_NO_ERROR) {
    std::cout << "Texture::loadToGPU glTextureSubImage2D ERROR " << err << " " << (err == GL_INVALID_OPERATION) <<
              " " << (err == GL_INVALID_VALUE) <<
              " " << (err == GL_INVALID_ENUM) <<
              std::endl;
  }
  glTextureParameteri(mGLTexture, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(mGLTexture, GL_TEXTURE_WRAP_T, GL_REPEAT);
  return true;
}

bool Texture::unloadFromGPU() {
  glDeleteTextures(1, &mGLTexture);
  return true;
}

bool Texture::bind(size_t unit) const {
  glBindTextureUnit(unit, mGLTexture);
  return true;
}

void Texture::unbind(size_t unit) const {
  glBindTextureUnit(unit, 0);
}
