#pragma once

#include <vector>

#include "space.h"

class Object
{
  // Methods
public:
  std::vector<vec3> calculateVertices();
  vec3 updatedVertice(vec3 point);
  void debugMovement();

protected:
  const float degToRad(float degree);

private:
  std::vector<vec3> rotationMatrix();

  // Attributes

public:
  std::vector<vec3> localVertices;
  std::vector<std::vector<int>> edgeIndexes;

  vec3 position = {0, 0, 0};
  vec3 rotation = {0, 0, 0};

private:
  float debugFrameCount = 0;
};