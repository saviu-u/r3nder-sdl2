#pragma once

#include <vector>

#include "space.h"

class Object{
  public:
  std::vector<vec3> calculateVertices();
  vec3 updatedVertice(vec3 point);
  void debugMovement();

  std::vector<vec3>* localVertices;
  std::vector<std::vector<int>>* edgeIndexes;
  vec3 position = { 0, 0, 0 };

  private:
  float debugFrameCount = 0;
};