#include "prebuilt/cube.h"

namespace Prebuilt
{
  Cube::Cube(Vec3 size)
  {
    localVertices = {
      {-size.x, -size.y, -size.z},
      {-size.x, -size.y, size.z},
      {size.x, -size.y, -size.z},
      {size.x, -size.y, size.z},
      {-size.x, size.y, -size.z},
      {-size.x, size.y, size.z},
      {size.x, size.y, -size.z},
      {size.x, size.y, size.z},
  };

    edgeIndexes = {
      {0, 1}, {0, 4}, {0, 2},
      {7, 5}, {7, 3}, {7, 6},
      {5, 1}, {5, 4}, {1, 3},
      {6, 2}, {6, 4}, {2, 3}
    };
  }
}
