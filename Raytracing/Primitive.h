#pragma once

#include "Float3D.h"
#include "Color.h"

class Primitive {
public:
  virtual float getDistance(const Ray& ray) const = 0;
  virtual Color getColor() const = 0;
  virtual Float3D getNormal(const Float3D& point) const = 0;

public:
  bool reflective = false;
  bool transparent = false;
};