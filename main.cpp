#include "screen.h"
#include "prebuilt/cube.h"
#include "custom_cube.h"

int main()
{
  CustomCube mainCube(10);
  mainCube.position = { 0, 0, 70 };

  Prebuilt::Cube cube(5);
  cube.position = { -20, 0, 70 };

  Screen screen;
  screen.addObjectToScene(&mainCube);
  screen.addObjectToScene(&cube);

  screen.show();
  screen.close();

  return 0;
}