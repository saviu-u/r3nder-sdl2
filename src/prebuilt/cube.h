#pragma once

#include "../object.h"

namespace Prebuilt {
  class Cube : public Object{
    public:
    Cube(vec3 size);
    Cube(float size) : Cube({ size, size, size }) {};
  };
};