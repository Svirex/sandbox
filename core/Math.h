//
// Created by svirex on 02.04.2020.
//

#ifndef SANDBOX_MATH_H
#define SANDBOX_MATH_H

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

class Math {
public:
  static bool nearZero(glm::vec3 &vec);

  static bool nearZero(float value);

  static glm::vec3 transform(const glm::vec3 &vec, const glm::quat &quat);
};

#endif // SANDBOX_MATH_H
