//
// Created by svirex on 04.02.2020.
//

#ifndef SANDBOX_MESHCOMPONENT_H
#define SANDBOX_MESHCOMPONENT_H

#include <glm/mat4x4.hpp>

#include "../Component.h"
#include "../system/ObjectManager.h"


class Mesh;
class Shader;

class MeshComponent : public Component {
public:
  explicit MeshComponent(Actor *owner);

  ~MeshComponent() override;

  void setMesh(Mesh *mesh);

  void draw(const glm::mat4 &view, const glm::mat4 &projection);

  MANAGE(MeshComponent)

private:
  Mesh *mMesh;
};

#endif // SANDBOX_MESHCOMPONENT_H
