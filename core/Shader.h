//
// Created by svirex on 31.01.2020.
//

#ifndef SANDBOX_SHADER_H
#define SANDBOX_SHADER_H

#include <string>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include "system/ObjectManager.h"

class Shader {
public:
  Shader(std::string vertexCode, std::string fragmentCode);

  ~Shader();

//  bool load(const std::string &vertexShaderFile, const std::string &fragmentShaderFile);

//  void unload();

  void setActive();

  void setUniform(const char *uniform, const glm::mat4 &matrix);

  void setUniform(const char *uniform, const glm::vec3 &vector);

  bool loadToGPU();

  void unloadFromGPU();

  void getSource(std::string &vertexCode, std::string &fragmentCode);

  void getSourceIn(std::string &vertexCode, std::string &fragmentCode);

  MANAGE(Shader)

private:
  GLuint mVertexShader = 0;

  GLuint mFragmentShader = 0;

  GLuint mShaderProgram = 0;

  const std::string mVertexCode;

  const std::string mFragmentCode;

  bool compileShader(const std::string &shaderCode, GLenum shaderType, GLuint &outShader);

  bool isCompiled(GLuint shader);

  bool isValidProgram(GLuint program);

};

#endif // SANDBOX_SHADER_H
