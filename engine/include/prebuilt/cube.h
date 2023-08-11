#pragma once

#include "object.h"

namespace Prebuilt {
  class Cube : public Object{
    public:
    Cube(Vec3 size);
    Cube(double size) : Cube({ size, size, size }) {};
  };
};