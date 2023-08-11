#pragma once

#include <vector>

#include "space/matrix.h"

class Object
{
  // Methods
public:
  const std::vector<Vec3> calculateVertices() const;

  virtual void start() {}
  virtual void update(double deltaTime) {}

protected:
  double degToRad(double degree) const;

private:
  const Matrix3 rotationMatrix() const;
  const Vec3 updatedVertice(const Vec3 point) const;
  void rotateVector(Vec3 &point) const;
  void vectorToGlobal(Vec3 &point) const;

  // Attributes
public:
  std::vector<Vec3> localVertices;
  std::vector<std::vector<int>> edgeIndexes;

  Vec3 position = {0, 0, 0};
  Vec3 rotation = {0, 0, 0};

private:
  double debugFrameCount = 0;
};