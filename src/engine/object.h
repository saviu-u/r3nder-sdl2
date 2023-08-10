#pragma once

#include <vector>

#include "space.h"

class Object
{
  // Methods
public:
  const std::vector<vec3> calculateVertices();
  const vec3 updatedVertice(const vec3 point);
  const void rotateVector(vec3 &point);
  const void vectorToGlobal(vec3 &point);

protected:
  const float degToRad(float degree);

private:
  const std::vector<vec3> rotationMatrix();

  // Attributes
public:
  std::vector<vec3> localVertices;
  std::vector<std::vector<int>> edgeIndexes;

  vec3 position = {0, 0, 0};
  vec3 rotation = {0, 0, 0};

private:
  float debugFrameCount = 0;
};