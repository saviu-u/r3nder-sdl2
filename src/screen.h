#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "object.h"
#include "space.h"

class Screen
{
public:
  Screen(Object* object);
  void show();
  void close();
  void cleanScreen();
  std::vector<vec3> mainObject;

protected:
  const vec2 vScreenToScreen(vec2 point);
  const vec3 projectIntoScreen(vec3 point);

  void verifyScreenInput();
  void update();

  float screenSizeX = 800;
  float screenSizeY = 600;

  float Hfov = 90;
  float Vfov = 74;

  float vScreenSizeX;
  float vScreenSizeY;

  float vScreenDistance = 1; // Centimeter

  Object* sceneObject;
  bool quit = 0;

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;

private:
  void refreshScreenSize();
  const float degToRad(float degree);
};