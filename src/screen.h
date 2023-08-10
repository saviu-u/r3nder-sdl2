#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <functional>

#include "object.h"
#include "space.h"

class Screen
{
// Methods
public:
  Screen();

  void show(const std::function<void(float deltaTime)> &update);
  void close();
  void cleanScreen();
  void addObjectToScene(Object* object);

protected:
  const vec2 vScreenToScreen(const vec2 &globalPoint);
  const vec3 projectIntoScreen(const vec3 &point);

  void verifyScreenInput();
  void renderObjects();
  void renderObject(Object* object);

private:
  void refreshScreenSize();
  void refreshFov();
  void refreshAspectRatio();
  void refreshFrameTime();
  const float degToRad(const float &angle);
  const float radToDeg(const float &rad);

// Attributes

protected:
  // SDL attributes
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;

  // Screen attributes
  float screenSizeX = 800;
  float screenSizeY = 600;

  float FpsCap = 120;
  float Hfov = 90;
  float vScreenDistance = 1; // Centimeter

  // Calculation dependent

  float frameTime;
  float Vfov;
  float aspectRatio;
  float vScreenSizeX;
  float vScreenSizeY;

  // Objects
  std::vector<Object*> sceneObjects;

  // Meta
  bool quit = 0;
};