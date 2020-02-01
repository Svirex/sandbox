//
// Created by svirex on 31.01.2020.
//

#ifndef SANDBOX_SHADER_H
#define SANDBOX_SHADER_H

#include <string>

#include <GL/glew.h>

class Shader {
public:
  Shader();

  ~Shader() = default;

  bool load(const std::string &vertexShaderFile, const std::string &fragmentShaderFile);

  void unload();

  void setActive();

private:
  GLuint mVertexShader;

  GLuint mFragmentShader;

  GLuint mShaderProgram;

  bool compileShader(const std::string &filePath, GLenum shaderType, GLuint &outShader);

  bool isCompiled(GLuint shader);

  bool isValidProgram(GLuint program);
};

#endif // SANDBOX_SHADER_H
