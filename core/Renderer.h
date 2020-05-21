//
// Created by svirex on 27.01.2020.
//

#ifndef SANDBOX_RENDERER_H
#define SANDBOX_RENDERER_H

#include <string>
#include <unordered_map>
#include <vector>

#include <SDL.h>
#include <glm/mat4x4.hpp>

#include "system/ObjectManager.h"

class Game;
class Shader;
class Mesh;
class MeshComponent;

class Renderer {
public:
  explicit Renderer(Game *game);

  ~Renderer() = default;

  bool initialize(float screenWidth, float screenHeight);

  void shutdown();

//  bool loadShader(const std::string &shaderName,
//                  const std::string &vertexShaderFile,
//                  const std::string &fragmentShaderFile);

//  void addMesh(std::string &fileName, Mesh *mesh);
//  Mesh *getMesh(const std::string &filePath);

  void addMeshComponent(MeshComponent *meshComponent);

  void removeMeshComponent(MeshComponent *meshComponent);

//  Shader *getShader(const std::string &shaderName);

  void draw();

  void setViewMatrix(const glm::mat4 &view);

  MANAGE(Renderer)

private:
  SDL_Window *mWindow = nullptr;

  Game *mGame = nullptr;

  float mScreenWidth = 0.0f;

  float mScreenHeight = 0.0f;

  SDL_GLContext mContext;

//  std::unordered_map<std::string, Shader *> mShaders;

//  std::unordered_map<std::string, Mesh *> mMeshes;

  std::vector<MeshComponent *> mMeshComponents;

  glm::mat4 mProjection;

  glm::mat4 mView;

};

#endif // SANDBOX_RENDERER_H
