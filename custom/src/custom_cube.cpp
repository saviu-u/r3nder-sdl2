#include "custom_cube.h"

void CustomCube::update(double deltaTime) {
  rotation.x += 45 * deltaTime;
  rotation.y += 45 * deltaTime;
  rotation.z += 45 * deltaTime;
}