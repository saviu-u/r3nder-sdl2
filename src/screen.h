#include <SDL2/SDL.h>

class Screen
{
  public:
  Screen();
  void show();
  void cleanScreen();
  void verifyScreenInput();

  private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;
  bool quit = 0;
};