#pragma once

#include "Primitive.h"
#include "Color.h"
#include <qlist.h>

struct LightSource {
  Primitive* primitive;
  Float3D position;
};

struct Intersection {
  float distance;
  Float3D position;
  Float3D normal;
  Primitive* primitive;
};

class Scene {
public:
  void addObject(Primitive* primitive) { m_objects << primitive; }
  void setLightSource(LightSource* lightSource) { m_objects << lightSource->primitive; m_lightSource = lightSource; }

  Color getColor(const Ray& ray) const;

private:
  float getLightAt(const Intersection& intersetion) const;
  Intersection nextIntersection(const Ray& ray) const;
  Color colorAt(Ray& ray, Intersection& intersection) const;

private:
  QList<Primitive*> m_objects;
  LightSource* m_lightSource = Q_NULLPTR;
};