#include "object.h"
#include <math.h>

const std::vector<vec3> Object::calculateVertices()
{
  std::vector<vec3> newVertices;

  for (vec3 point : localVertices)
    newVertices.push_back(updatedVertice(point));

  return newVertices;
}

const vec3 Object::updatedVertice(const vec3 point)
{
  vec3 newPoint = point;

  rotateVector(newPoint);
  vectorToGlobal(newPoint);

  return newPoint;
}

const void Object::rotateVector(vec3 &point){
  std::vector<vec3> cachedRotationMatrix = rotationMatrix();
  float rotationOutput[3] = {0, 0, 0};

  for(int i = 0 ; i < 3 ; i++){
    rotationOutput[i] += point.x * cachedRotationMatrix[i].x;
    rotationOutput[i] += point.y * cachedRotationMatrix[i].y;
    rotationOutput[i] += point.z * cachedRotationMatrix[i].z;
  }

  point.x = rotationOutput[0];
  point.y = rotationOutput[1];
  point.z = rotationOutput[2];
}

const void Object::vectorToGlobal(vec3 &point){
  point.x += position.x;
  point.y += position.y;
  point.z += position.z;
}

const std::vector<vec3> Object::rotationMatrix(){
  float rad_x = degToRad(rotation.x);
  float rad_y = degToRad(rotation.y);
  float rad_z = degToRad(rotation.z);

  float sin_x = sin(rad_x);
  float cos_x = cos(rad_x);

  float sin_y = sin(rad_y);
  float cos_y = cos(rad_y);

  float sin_z = sin(rad_z);
  float cos_z = cos(rad_z);

  return {
    { cos_z * cos_y                        , sin_z * cos_y                        , - sin_y       },
    { cos_z * sin_y * sin_x - sin_z * cos_x, sin_z * sin_y * sin_x + cos_z * cos_x, cos_y * sin_x },
    { cos_z * sin_y * cos_x + sin_z * sin_x, sin_z * sin_y * cos_x - cos_z * sin_x, cos_y * cos_x }
  };
}

const float Object::degToRad(float angle)
{
  return angle * (M_PI / 180);
}