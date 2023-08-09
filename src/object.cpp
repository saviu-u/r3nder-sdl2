#include "object.h"
#include <math.h>

std::vector<vec3> Object::calculateVertices()
{
  std::vector<vec3> newVertices;

  for (vec3 point : localVertices)
    newVertices.push_back(updatedVertice(point));

  return newVertices;
}

vec3 Object::updatedVertice(vec3 point)
{
  float rotationOutput[3] = {0,0,0};
  std::vector<vec3> cachedRotationMatrix = rotationMatrix();

  for(int i = 0 ; i < 3 ; i++){
    rotationOutput[i] += point.x * cachedRotationMatrix[i].x;
    rotationOutput[i] += point.y * cachedRotationMatrix[i].y;
    rotationOutput[i] += point.z * cachedRotationMatrix[i].z;
  }

  vec3 newPoint = { rotationOutput[0], rotationOutput[1], rotationOutput[2] };

  newPoint.x += position.x;
  newPoint.y += position.y;
  newPoint.z += position.z;

  return newPoint;
}

std::vector<vec3> Object::rotationMatrix(){
  return {
    { cos(degToRad(rotation.z)) * cos(degToRad(rotation.y)), sin(degToRad(rotation.z)) * cos(degToRad(rotation.y)), - sin(degToRad(rotation.y)) },
    { cos(degToRad(rotation.z)) * sin(degToRad(rotation.y)) * sin(degToRad(rotation.x)) - sin(degToRad(rotation.z)) * cos(degToRad(rotation.x)), sin(degToRad(rotation.z)) * sin(degToRad(rotation.y)) * sin(degToRad(rotation.x)) + cos(degToRad(rotation.z)) * cos(degToRad(rotation.x)), cos(degToRad(rotation.y)) * sin(degToRad(rotation.x)) },
    { cos(degToRad(rotation.z)) * sin(degToRad(rotation.y)) * cos(degToRad(rotation.x)) + sin(degToRad(rotation.z)) * sin(degToRad(rotation.x)), sin(degToRad(rotation.z)) * sin(degToRad(rotation.y)) * cos(degToRad(rotation.x)) - cos(degToRad(rotation.z)) * sin(degToRad(rotation.x)), cos(degToRad(rotation.y)) * cos(degToRad(rotation.x)) }
  };
}

const float Object::degToRad(float angle)
{
  return angle * (M_PI / 180);
}