#include "Scene.h"
#include <qdebug.h>

Color Scene::getColor(const Ray& ray) const {
  Intersection intersection = nextIntersection(ray);
  return colorAt(Ray(ray), intersection);
}

Color Scene::colorAt(Ray& ray, Intersection& intersection) const {
  if (intersection.distance == INFINITY)
    return { 20, 20, 20 };

  if (intersection.primitive->reflective) {
    ray = { intersection.position, ray.direction - 2 * (ray.direction.dot(intersection.normal)) * intersection.normal };
    intersection = nextIntersection(ray);
    return colorAt(ray, intersection);
  }
  else if (intersection.primitive->transparent) {
    float a1, n1ToN2;
    if (ray.direction.dot(intersection.normal) < 0) {
      a1 = ray.direction.angleTo(-1 * intersection.normal);
      n1ToN2 = 1 / 1.5; // Übergang von Luft in Glas
    } else {
      a1 = ray.direction.angleTo(intersection.normal);
      n1ToN2 = 1.5 / 1; // Übergang von Glas in Luft
    }

    float a2 = asin(min(n1ToN2 * sin(a1), 1.0));
    Float3D direction = n1ToN2 * ray.direction - (cos(a2) - n1ToN2 * cos(a1)) * intersection.normal;
    Ray transmissedRay{ intersection.position, direction.normalize() };
    Color transmissedColor = colorAt(transmissedRay, nextIntersection(transmissedRay));

    if (n1ToN2 < 1.0) {
      Ray reflectedRay{ intersection.position, ray.direction - 2 * (ray.direction.dot(intersection.normal)) * intersection.normal };
      Color reflectedColor = colorAt(reflectedRay, nextIntersection(reflectedRay));
      float fresnelCoeff = sqr(sin(a1 - a2) / sin(a1 + a2));
      return fresnelCoeff * reflectedColor + (1 - fresnelCoeff) * transmissedColor;
    } else {
      return transmissedColor;
    }   
  } else {
    float lightIntensity = getLightAt(intersection);
    return intersection.primitive->getColor() * lightIntensity;
  }
}

float Scene::getLightAt(const Intersection& point) const {
  if (point.primitive == m_lightSource->primitive)
    return 1.0f;

  Ray shadowRay{ point.position, m_lightSource->position - point.position };

  if (nextIntersection(shadowRay).primitive == m_lightSource->primitive) {
    shadowRay.direction.normalize();
    return abs(shadowRay.direction.dot(point.normal));
  }

  return 0.0f;
}

Intersection Scene::nextIntersection(const Ray& ray) const {
  Intersection intersection;
  intersection.distance = INFINITY;
  intersection.primitive = nullptr;

  for each(Primitive* const primitive in m_objects) {
    float distance = primitive->getDistance(ray);

    if (distance < intersection.distance) {
      intersection.distance = distance;
      intersection.primitive = primitive;
    }
  }

  if (!intersection.primitive)
    return intersection;

  intersection.position = ray.origin + intersection.distance * ray.direction;
  intersection.normal = intersection.primitive->getNormal(intersection.position);
  return intersection;
}