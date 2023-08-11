#include "object.h"
#include <math.h>

const std::vector<Vec3> Object::calculateVertices() const
{
  std::vector<Vec3> newVertices;

  for (Vec3 point : localVertices)
    newVertices.push_back(updatedVertice(point));

  return newVertices;
}

const Vec3 Object::updatedVertice(const Vec3 point) const
{
  Vec3 newPoint = point;

  rotateVector(newPoint);
  vectorToGlobal(newPoint);

  return newPoint;
}

void Object::rotateVector(Vec3 &point) const {
  point = rotationMatrix().multiply(point);
}

void Object::vectorToGlobal(Vec3 &point) const {
  point.x += position.x;
  point.y += position.y;
  point.z += position.z;
}

const Matrix3 Object::rotationMatrix() const {
  double rad_x = degToRad(rotation.x);
  double rad_y = degToRad(rotation.y);
  double rad_z = degToRad(rotation.z);

  double sin_x = sin(rad_x);
  double cos_x = cos(rad_x);

  double sin_y = sin(rad_y);
  double cos_y = cos(rad_y);

  double sin_z = sin(rad_z);
  double cos_z = cos(rad_z);

  return Matrix3({
    { cos_z * cos_y                        , sin_z * cos_y                        , - sin_y       },
    { cos_z * sin_y * sin_x - sin_z * cos_x, sin_z * sin_y * sin_x + cos_z * cos_x, cos_y * sin_x },
    { cos_z * sin_y * cos_x + sin_z * sin_x, sin_z * sin_y * cos_x - cos_z * sin_x, cos_y * cos_x }
  });
}

double Object::degToRad(double angle) const
{
  return angle * (M_PI / 180);
}