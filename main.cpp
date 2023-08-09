#include <SDL2/SDL.h>
#include "src/screen.h"
#include "src/prebuilt/cube.h"
#include "src/object.h"

int main()
{
  Prebuilt::Cube mainCube(100);
  mainCube.position = { 0, 0, 700 };
  mainCube.rotation = { 20, 0, 0 };

  Prebuilt::Cube cube(50);
  cube.position = { -200, 0, 700 };

  Screen screen;
  screen.addObjectToScene(&mainCube);
  screen.addObjectToScene(&cube);

  screen.show([&cube, &mainCube] (float deltaTime) {
    mainCube.rotation.x += 45 * deltaTime;
    mainCube.rotation.y += 45 * deltaTime;
    mainCube.rotation.z += 45 * deltaTime;
  });
  screen.close();

  return 0;
}