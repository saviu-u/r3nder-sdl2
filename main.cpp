#include <SDL2/SDL.h>
#include "src/screen.h"
#include "src/object.h"

int main()
{
  std::vector<vec3> cubeVertices = {
      {-100, -100, -100},
      {-100, -100, 100},
      {100, -100, -100},
      {100, -100, 100},
      {-100, 100, -100},
      {-100, 100, 100},
      {100, 100, -100},
      {100, 100, 100},
  };
  std::vector<std::vector<int>> edgeIndexes = {
      {0, 1}, {0, 4}, {0, 2},
      {7, 5}, {7, 3}, {7, 6},
      {5, 1}, {5, 4}, {1, 3},
      {6, 2}, {6, 4}, {2, 3}
  };

  Object object;
  object.localVertices = &cubeVertices;
  object.edgeIndexes = &edgeIndexes;



  Screen screen(&object);
   


  screen.show();
  screen.close();
  
 

  return 0;
}