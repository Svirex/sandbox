//
// Created by svirex on 31.01.2020.
//

#include <SDL2/SDL.h>
#include <fstream>
#include <sstream>

#include "Shader.h"

Shader::Shader() : mVertexShader(0), mFragmentShader(0), mShaderProgram(0) {}

bool Shader::load(const std::string &vertexShaderFile,
                  const std::string &fragmentShaderFile) {
  if (!compileShader(vertexShaderFile, GL_VERTEX_SHADER, mVertexShader) ||
      !compileShader(fragmentShaderFile, GL_FRAGMENT_SHADER, mFragmentShader)) {
    return false;
  }

  mShaderProgram = glCreateProgram();
  glAttachShader(mShaderProgram, mVertexShader);
  glAttachShader(mShaderProgram, mFragmentShader);
  glLinkProgram(mShaderProgram);

  if (!isValidProgram(mShaderProgram)) {
    return false;
  }

  glDeleteShader(mFragmentShader);
  glDeleteShader(mVertexShader);

  return true;
}

void Shader::unload() {
  glDeleteProgram(mShaderProgram);
}

void Shader::setActive() {
  glUseProgram(mShaderProgram);
}

bool Shader::compileShader(const std::string &filePath, GLenum shaderType,
                           GLuint &outShader) {
  std::ifstream shaderFile(filePath);
  if (shaderFile) {
    std::stringstream sstream;
    sstream << shaderFile.rdbuf();
    std::string shader = sstream.str();
    const char *shaderText = shader.c_str();

    outShader = glCreateShader(shaderType);
    glShaderSource(outShader, 1, &(shaderText), nullptr);
    glCompileShader(outShader);

    if (!isCompiled(outShader)) {
      SDL_Log("Failed to compile shader %s", filePath.c_str());
      return false;
    }

  } else {
    return false;
  }
  return true;
}

bool Shader::isCompiled(GLuint shader) {
  GLint status;

  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

  if (status != GL_TRUE) {
    char buffer[512];
    memset(buffer, 0, 512);
    glGetShaderInfoLog(shader, 511, nullptr, buffer);
    SDL_Log("GLSL Compile Failed:\n%s", buffer);
    return false;
  }

  return true;
}

bool Shader::isValidProgram(GLuint program) {
  GLint status;

  glGetProgramiv(program, GL_LINK_STATUS, &status);

  if (status != GL_TRUE)
  {
    char buffer[512];
    memset(buffer, 0, 512);
    glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
    SDL_Log("GLSL Link Status:\n%s", buffer);
    return false;
  }

  return true;
}
