//
// Created by svirex on 02.04.2020.
//

#include <glm/gtc/epsilon.hpp>
#include <glm/ext/quaternion_common.hpp>

#include "Math.h"

bool Math::nearZero(glm::vec3 &vec) {
  return glm::all(
      glm::epsilonEqual(vec, glm::vec3(0.0f, 0.0f, 0.0f),0.001f)
      );
}

bool Math::nearZero(float value) {
  return glm::epsilonEqual(value, 0.0f, 0.001f);
}

glm::vec3 Math::transform(const glm::vec3 &vec, const glm::quat &quat) {
  return quat * vec * glm::conjugate(quat);
}
