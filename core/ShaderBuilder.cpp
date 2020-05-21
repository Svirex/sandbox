//
// Created by svirex on 18.05.2020.
//

#include <fstream>
#include <sstream>

#include "ShaderBuilder.h"

#include "ResourceManager.h"
#include "Material.h"
#include "Shader.h"
#include "consts.h"
#include "Mesh.h"

ShaderBuilder::ShaderBuilder(ResourceManager *rm): mResourceManager(rm) {}

bool ShaderBuilder::init() {
  mBasicVertexShaderCode = loadShaderFile(BASIC_VERTEX_SHADER_PATH);
  if (mBasicVertexShaderCode.empty()) {
    return false;
  }
  mBasicFragmentShaderCode = loadShaderFile(BASIC_FRAGMENT_SHADER_PATH);
  if (mBasicFragmentShaderCode.empty()) {
    return false;
  }

  return true;
}

std::string ShaderBuilder::loadShaderFile(const std::string &filePath) {
  std::ifstream file(filePath);
  if(file) {
    std::stringstream sstream;
    sstream << file.rdbuf();
    return sstream.str();
  } else {
    return std::string();
  }
}

Shader *ShaderBuilder::build(const Mesh *mesh, const Material *material) {
  std::stringstream vertexShaderCode;
  std::stringstream fragmentShaderCode;
  vertexShaderCode << "#version 450\n";
  fragmentShaderCode << "#version 450\n";

  buildVertexShaderCode(mesh, material, vertexShaderCode);
  buildFragmentShaderCode(mesh, material, fragmentShaderCode);

  vertexShaderCode << mBasicVertexShaderCode;
  fragmentShaderCode << mBasicFragmentShaderCode;

  return new Shader(vertexShaderCode.str(), fragmentShaderCode.str());
}

void ShaderBuilder::buildVertexShaderCode(const Mesh *mesh, const Material *material,
                                          std::stringstream &vertexCode) {
  if (mesh->hasTextureCoords()) {
    vertexCode << "#define HAS_TEXTURE_COORD\n";
    vertexCode << "#define TEXTURE_COORDS_LAYOUT_LOCATION " << TEXTURE_COORDS_LAYOUT_LOCATION << "\n";
  }
}
void ShaderBuilder::buildFragmentShaderCode(const Mesh *mesh, const Material *material,
                                            std::stringstream &fragmentCode) {
  if (mesh->hasTextureCoords()) {
    fragmentCode << "#define HAS_TEXTURE_COORD\n";
  }
  if (material->hasDiffuseColor()) {
    auto &color = material->getDiffuseColor();
    fragmentCode << "#define HAS_DIFFUSE_COLOR\n";
    fragmentCode <<
        "#define DIFFUSE_COLOR_VECTOR vec4(" <<
        color.x << "," << color.y << "," << color.z <<
        ", 1.0)\n";

  }
  if (material->hasDiffuseTexture()) {
    fragmentCode << "#define HAS_DIFFUSE_TEXTURE\n";
    fragmentCode << "#define DIFFUSE_TEXTURE_LAYOUT_BINDING " << DIFFUSE_TEXTURE_LAYOUT_BINDING << "\n";
  }
}
