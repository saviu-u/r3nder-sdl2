#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <functional>

#include "object.h"
#include "space/vec.h"

class Screen
{
// Methods
public:
  Screen();

  void show(const std::function<void(double deltaTime)> &update);
  void close();
  void cleanScreen();
  void addObjectToScene(Object* object);

protected:
  const Vec2 vScreenToScreen(const Vec2 &globalPoint) const;
  const Vec3 projectIntoScreen(const Vec3 &point) const;

  void verifyScreenInput();
  void renderObjects();
  void renderObject(Object* object);

private:
  void refreshVirtualScreenSize();
  void refreshScreenAttributes();
  void refreshFov();
  void refreshAspectRatio();
  void refreshFrameTime();
  double degToRad(const double &angle) const;
  double radToDeg(const double &rad) const;

// Attributes

protected:
  // SDL attributes
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;

  // Screen attributes
  int screenSizeX = 800;
  int screenSizeY = 600;

  double FpsCap = 120;
  double Hfov = 90;
  double vScreenDistance = 1; // Centimeter

  // Calculation dependent

  double frameTime;
  double Vfov;
  double aspectRatio;
  double vScreenSizeX;
  double vScreenSizeY;

  // Objects
  std::vector<Object*> sceneObjects;

  // Meta
  bool quit = 0;
};