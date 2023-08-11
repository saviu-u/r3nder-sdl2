#include "prebuilt/cube.h"

class CustomCube : public Prebuilt::Cube
{
  using Cube::Cube;

public:
  void update(double deltaTime) override;
};
