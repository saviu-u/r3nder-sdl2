#include <SDL2/SDL.h>
#include "src/screen.h"
#include "src/prebuilt/cube.h"
#include "src/object.h"

int main()
{
  Prebuilt::Cube mainCube(10);
  mainCube.position = { 0, 0, 70 };

  Prebuilt::Cube cube(5);
  cube.position = { -20, 0, 70 };

  Screen screen;
  screen.addObjectToScene(&mainCube);
  screen.addObjectToScene(&cube);

  screen.show([&mainCube] (float deltaTime) {
    mainCube.rotation.x += 45 * deltaTime;
    mainCube.rotation.y += 45 * deltaTime;
    mainCube.rotation.z += 45 * deltaTime;
  });
  screen.close();

  return 0;
}