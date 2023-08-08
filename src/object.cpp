#include "object.h"
#include <math.h>

std::vector<vec3> Object::calculateVertices()
{
  std::vector<vec3> newVertices;

  for (vec3 point : *localVertices)
  {
    newVertices.push_back(updatedVertice(point));
  }

  debugMovement();

  return newVertices;
}

vec3 Object::updatedVertice(vec3 point)
{
  return {
      point.x + position.x,
      point.y + position.y,
      point.z + position.z};
}

void Object::debugMovement(){
  debugFrameCount += 1/10000.0f; // This is an approximation, this depends on your processor

  // Changes the position into a sin wave and cosine wave
  position = {
    sin(debugFrameCount) * 50,
    cos(debugFrameCount) * 50,
    0
  };
}