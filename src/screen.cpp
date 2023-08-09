#include "screen.h"
#include <iostream>
#include <string>
#include <math.h>

Screen::Screen()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(screenSizeX, screenSizeY, 0, &window, &renderer);

  // Order dependent
  refreshAspectRatio();
  refreshFov();
  refreshScreenSize();
}

void Screen::refreshAspectRatio(){
  aspectRatio = screenSizeX / screenSizeY;
}

void Screen::refreshFov()
{
  Vfov = radToDeg(2 * atan(tan(degToRad(Hfov)/2) * 1/aspectRatio));
}

void Screen::addObjectToScene(Object* object)
{
  sceneObjects.push_back(object);
}

void Screen::show(std::function<void(float deltaTime)> update = {})
{
  while (!quit)
  {
    // Verify if the close button has been pressed
    verifyScreenInput();

    // Update tick
    Uint32 startTick = SDL_GetPerformanceCounter();

    // Draw
    cleanScreen();
    renderObjects();

    // Updates the canvas to the drawing
    SDL_RenderPresent(renderer);

    // Calculates the tick
    Uint32 finishTick = SDL_GetPerformanceCounter();
    float elapsed = (finishTick - startTick) / (float)SDL_GetPerformanceFrequency();

    // Caps the frame if set to it
    if(FpsCap != 0)
      SDL_Delay(floor((1000 / FpsCap) - elapsed * 1000));

    // Recalculate time elapsed time
    Uint32 finishTickUpdated = SDL_GetPerformanceCounter();
    float trueElapsed = (finishTickUpdated - startTick) / (float)SDL_GetPerformanceFrequency();

    // Updates physics
    update(trueElapsed);

    std::cout << "Current FPS: " << std::to_string(1.0f / trueElapsed) << std::endl;
    std::cout << "Current FPS: " << std::to_string(trueElapsed) << std::endl;
  }
}

// Main loop, do the drawing here
void Screen::renderObjects()
{
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  for(Object* sceneObject : sceneObjects)
    renderObject(sceneObject);
}

void Screen::renderObject(Object* object){
  std::vector<vec2> screenVertices;
  for (vec3 vertice : object->calculateVertices())
  {
    vec3 screenProjectionPoint = projectIntoScreen(vertice);
    vec2 screenCoordinates = vScreenToScreen({screenProjectionPoint.x, screenProjectionPoint.y});

    screenVertices.push_back(screenCoordinates);
  }

  for (std::vector<int> indexes : object->edgeIndexes){
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

const float Screen::radToDeg(float rad)
{
  return rad * (180 / M_PI);
}