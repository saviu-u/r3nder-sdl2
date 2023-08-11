#include "screen.h"
#include <string>
#include <math.h>

Screen::Screen()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(screenSizeX, screenSizeY, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE, &window, &renderer);

  // Order dependent
  refreshFrameTime();
  refreshScreenAttributes();
}

void Screen::addObjectToScene(Object* object)
{
  sceneObjects.push_back(object);
  object->start();
}

void Screen::show()
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
    double elapsed = (finishTick - startTick) / (double)SDL_GetPerformanceFrequency();

    // Caps the frame if set to it
    if(FpsCap != 0){
      double elaspedMs = elapsed * 1000;
      int64_t framesSkiped = floor(frameTime - elaspedMs);

      if (framesSkiped > 0)
        SDL_Delay(framesSkiped);
    }

    // Recalculate time elapsed time
    Uint32 finishTickUpdated = SDL_GetPerformanceCounter();
    double trueElapsed = (finishTickUpdated - startTick) / (double)SDL_GetPerformanceFrequency();

    // Updates physics
    updateObjects(trueElapsed);
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

// protected

void Screen::verifyScreenInput()
{
  while (SDL_PollEvent(&event))
  {
    switch(event.type){
      case SDL_WINDOWEVENT:
        switch(event.window.event){
          case SDL_WINDOWEVENT_SIZE_CHANGED:
            SDL_GetWindowSize(window, &screenSizeX, &screenSizeY);
            refreshScreenAttributes();
            break;
        }
        break;
      case SDL_QUIT:
        quit = 1;
        break;
    }
  }
}

void Screen::renderObjects()
{
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  for(Object* sceneObject : sceneObjects)
    renderObject(sceneObject);
}

void Screen::renderObject(Object* object){
  std::vector<Vec2> screenVertices;
  for (Vec3 vertice : object->calculateVertices())
  {
    Vec3 screenProjectionPoint = projectIntoScreen(vertice);
    Vec2 screenCoordinates = vScreenToScreen({screenProjectionPoint.x, screenProjectionPoint.y});

    screenVertices.push_back(screenCoordinates);
  }

  for (std::vector<int> indexes : object->edgeIndexes){
    Vec2 start = screenVertices[indexes[0]];
    Vec2 finish = screenVertices[indexes[1]];

    SDL_RenderDrawLineF(renderer, start.x, start.y, finish.x, finish.y);
  }
}

void Screen::updateObjects(double deltaTime){
  for(Object* sceneObject : sceneObjects)
    sceneObject->update(deltaTime);
}

// private

void Screen::refreshFrameTime(){
  frameTime = 1000 / FpsCap;
}

void Screen::refreshScreenAttributes(){
  refreshAspectRatio();
  refreshFov();
  refreshVirtualScreenSize();
}

void Screen::refreshAspectRatio(){
  aspectRatio = (double) screenSizeX / screenSizeY;
}

void Screen::refreshFov()
{
  Vfov = radToDeg(2 * atan(tan(degToRad(Hfov)/2) * 1/aspectRatio));
}

void Screen::refreshVirtualScreenSize()
{
  double angleTangentX = tan(degToRad(Hfov / 2));
  double angleTangentY = tan(degToRad(Vfov / 2));

  vScreenSizeX = (vScreenDistance * angleTangentX) * 2;
  vScreenSizeY = (vScreenDistance * angleTangentY) * 2;
}

// // Specific tools

const Vec2 Screen::vScreenToScreen(const Vec2 &globalPoint) const
{
  double localPointX = globalPoint.x + vScreenSizeX / 2;
  double localPointY = globalPoint.y + vScreenSizeY / 2;

  return {
      localPointX * screenSizeX / vScreenSizeX,
      localPointY * screenSizeY / vScreenSizeY};
}

const Vec3 Screen::projectIntoScreen(const Vec3 &point) const
{
  double distanceFromScreenCenterX = (point.x / point.z) * vScreenDistance;
  double distanceFromScreenCenterY = (point.y / point.z) * vScreenDistance;

  return {distanceFromScreenCenterX, -distanceFromScreenCenterY, vScreenDistance};
}

// // Tools

double Screen::degToRad(const double &angle) const
{
  return angle * (M_PI / 180);
}

double Screen::radToDeg(const double &rad) const
{
  return rad * (180 / M_PI);
}