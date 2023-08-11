#include "src/engine/screen.h"
#include "src/engine/prebuilt/cube.h"
#include "src/engine/object.h"

int main()
{
  Prebuilt::Cube mainCube(10);
  mainCube.position = { 0, 0, 70 };

  Prebuilt::Cube cube(5);
  cube.position = { -20, 0, 70 };

  Screen screen;
  screen.addObjectToScene(&mainCube);
  screen.addObjectToScene(&cube);

  screen.show([&mainCube] (double deltaTime) {
    mainCube.rotation.x += 45 * deltaTime;
    mainCube.rotation.y += 45 * deltaTime;
    mainCube.rotation.z += 45 * deltaTime;
  });
  screen.close();

  return 0;
}