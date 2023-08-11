#pragma once

#include <vector>
#include "vec.h"

class Matrix3
{
  public:
  // constructor
  Matrix3(Vec3 first, Vec3 second, Vec3 third) : rows{ first, second, third } {}

  // methods
  const Vec3 multiply(const Vec3 &vector3) const;

  // attributes
  Vec3 rows[3];
};