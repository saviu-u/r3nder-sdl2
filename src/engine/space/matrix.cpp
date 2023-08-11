#include "matrix.h"

const Vec3 Matrix3::multiply(const Vec3 &vector3) const
{
  double rotationOutput[3] = {0, 0, 0};

  for(int i = 0 ; i < 3 ; i++){
    rotationOutput[i] += vector3.x * rows[i].x;
    rotationOutput[i] += vector3.y * rows[i].y;
    rotationOutput[i] += vector3.z * rows[i].z;
  }

  return { rotationOutput[0], rotationOutput[1], rotationOutput[2] };
}