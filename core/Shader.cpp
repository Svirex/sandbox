//
// Created by svirex on 31.01.2020.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <SDL.h>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>

#include "Shader.h"

Shader::Shader(std::string vertexCode, std::string fragmentCode)
    : mVertexCode(std::move(vertexCode)),
      mFragmentCode(std::move(fragmentCode)) {}

Shader::~Shader() { unloadFromGPU(); }

bool Shader::loadToGPU() {
  if (!compileShader(mVertexCode, GL_VERTEX_SHADER, mVertexShader) ||
      !compileShader(mFragmentCode, GL_FRAGMENT_SHADER, mFragmentShader)) {
    SDL_Log("Failed to compile shaders");
    return false;
  }

  mShaderProgram = glCreateProgram();
  glAttachShader(mShaderProgram, mVertexShader);
  glAttachShader(mShaderProgram, mFragmentShader);
  glLinkProgram(mShaderProgram);

  if (!isValidProgram(mShaderProgram)) {
    SDL_Log("Program is invalid");
    return false;
  }

//  glDeleteShader(mFragmentShader);
//  glDeleteShader(mVertexShader);

  mFragmentShader = 0;
  mVertexShader = 0;

  return true;
}

void Shader::unloadFromGPU() {
  glDeleteProgram(mShaderProgram);
  mShaderProgram = 0;
}

void Shader::getSource(std::string &vertexCode, std::string &fragmentCode) {
  auto *vertexBuff = new char[4096];
  auto *fragmentBuff = new char[4096];
  int size;
  glGetShaderSource(mVertexShader, 4096, &size, vertexBuff);
  vertexCode = std::string(vertexBuff, size);
  glGetShaderSource(mVertexShader, 4096, &size, fragmentBuff);
  fragmentCode = std::string(fragmentBuff, size);
}

void Shader::getSourceIn(std::string &vertexCode, std::string &fragmentCode) {
  vertexCode = mVertexCode;
  fragmentCode = mFragmentCode;
}

//bool Shader::load(const std::string &vertexShaderFile,
//                  const std::string &fragmentShaderFile) {
//  if (!compileShader(vertexShaderFile, GL_VERTEX_SHADER, mVertexShader) ||
//      !compileShader(fragmentShaderFile, GL_FRAGMENT_SHADER, mFragmentShader)) {
//    SDL_Log("Failed to compile shaders");
//    return false;
//  }
//
//  mShaderProgram = glCreateProgram();
//  glAttachShader(mShaderProgram, mVertexShader);
//  glAttachShader(mShaderProgram, mFragmentShader);
//  glLinkProgram(mShaderProgram);
//
//  if (!isValidProgram(mShaderProgram)) {
//    SDL_Log("Program is invalid");
//    return false;
//  }
//
//  glDeleteShader(mFragmentShader);
//  glDeleteShader(mVertexShader);
//
//  mFragmentShader = 0;
//  mVertexShader = 0;
//
//  return true;
//}

// void Shader::unload() {
//  glDeleteProgram(mShaderProgram);
//  mShaderProgram = 0;
//}

void Shader::setActive() { glUseProgram(mShaderProgram); }

bool Shader::compileShader(const std::string &shaderCode, GLenum shaderType,
                           GLuint &outShader) {
//  spdlog::debug("Shader code: {}", shaderCode);
  const char *shaderText = shaderCode.c_str();

  outShader = glCreateShader(shaderType);
  glShaderSource(outShader, 1, &(shaderText), nullptr);
  glCompileShader(outShader);

  if (!isCompiled(outShader)) {
    SDL_Log("Failed to compile shader %s", shaderCode.c_str());
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

  if (status != GL_TRUE) {
    char buffer[512];
    memset(buffer, 0, 512);
    glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
    SDL_Log("GLSL Link Status:\n%s", buffer);
    return false;
  }

  return true;
}

void Shader::setUniform(const char *uniform, const glm::mat4 &matrix) {

  GLint location = glGetUniformLocation(mShaderProgram, uniform);
  //TODO glGetUniformLocation может вернуть -1. СДелать обработку на этот случай
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    std::cout << "setUniform ERROR " << err << " " << (err == GL_INVALID_OPERATION) <<
        " " << (err == GL_INVALID_VALUE) <<
        std::endl;
  }
}

void Shader::setUniform(const char *uniform, const glm::vec3 &vector) {
  GLint location = glGetUniformLocation(mShaderProgram, uniform);
  glUniform3fv(location, 1, glm::value_ptr(vector));
}
