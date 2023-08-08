#include "screen.h"

#include <math.h>

Screen::Screen(Object* object)
{
  sceneObject = object;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(screenSizeX, screenSizeY, 0, &window, &renderer);

  refreshScreenSize();
}

void Screen::show()
{
  while (!quit)
  {
    // Verify if the close button has been pressed
    verifyScreenInput();

    // Draw
    cleanScreen();
    update();

    // Updates the canvas to the drawing
    SDL_RenderPresent(renderer);
  }
}

// Main loop, do the drawing here
void Screen::update()
{
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  std::vector<vec2> screenVertices;
  for (vec3 vertice : sceneObject->calculateVertices())
  {
    vec3 screenProjectionPoint = projectIntoScreen(vertice);
    vec2 screenCoordinates = vScreenToScreen({screenProjectionPoint.x, screenProjectionPoint.y});
    // SDL_RenderDrawPointF(renderer, screenCoordinates.x, screenCoordinates.y);

    screenVertices.push_back(screenCoordinates);
  }

  for (std::vector<int> indexes : *(sceneObject->edgeIndexes)){
    vec2 start = screenVertices[indexes[0]];
    vec2 finish = screenVertices[indexes[1]];

    SDL_RenderDrawLineF(renderer, start.x, start.y, finish.x, finish.y);
  }
}

void Screen::verifyScreenInput()
{
  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
      quit = 1;
  }
}

void Screen::cleanScreen()
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void Screen::close()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Screen::refreshScreenSize()
{
  float angleTangentX = tan(degToRad(Hfov / 2));
  float angleTangentY = tan(degToRad(Vfov / 2));

  vScreenSizeX = (vScreenDistance * angleTangentX) * 2;
  vScreenSizeY = (vScreenDistance * angleTangentY) * 2;
}

const vec3 Screen::projectIntoScreen(vec3 point)
{
  float distanceFromScreenCenterX = (point.x / point.z) * vScreenDistance;
  float distanceFromScreenCenterY = (point.y / point.z) * vScreenDistance;

  return {distanceFromScreenCenterX, -distanceFromScreenCenterY, vScreenDistance};
}

// Specific tools

const vec2 Screen::vScreenToScreen(vec2 globalPoint)
{
  float localPointX = globalPoint.x + vScreenSizeX / 2;
  float localPointY = globalPoint.y + vScreenSizeY / 2;

  return {
      localPointX * screenSizeX / vScreenSizeX,
      localPointY * screenSizeY / vScreenSizeY};
}

// Tools

const float Screen::degToRad(float angle)
{
  return angle * (M_PI / 180);
}