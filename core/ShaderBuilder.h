//
// Created by svirex on 18.05.2020.
//

#ifndef SANDBOX_SHADERBUILDER_H
#define SANDBOX_SHADERBUILDER_H

#include <string>

#include "system/ObjectManager.h"

class Material;
class Shader;
class ResourceManager;
class Mesh;

class ShaderBuilder {
public:
  explicit ShaderBuilder(ResourceManager *rm);

  bool init();

  Shader *build(const Mesh *mesh, const Material *material);

  MANAGE(ShaderBuilder)

private:
  std::string loadShaderFile(const std::string &filePath);

  void buildVertexShaderCode(const Mesh *mesh, const Material *material, std::stringstream &vertexCode);

  void buildFragmentShaderCode(const Mesh *mesh, const Material *material, std::stringstream &fragmentCode);

  ResourceManager *mResourceManager;
  std::string mBasicVertexShaderCode;
  std::string mBasicFragmentShaderCode;
};

#endif // SANDBOX_SHADERBUILDER_H
