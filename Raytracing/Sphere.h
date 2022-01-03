#pragma once

#include "Primitive.h"

class Sphere : public Primitive {
public:
  Sphere(const Float3D& center, float radius, Color color) {
    m_center = center;
    m_radius = radius;
    m_color = color;
  }

  // See https://www.hochschule-bochum.de/fileadmin/public/Die-BO_Einrichtungen/Hochschulkommunikation/Presse/FAWIS/Albers_facharbeitRaytracing.pdf for reference
  float getDistance(const Ray& ray) const override {
    float a = sqr(ray.direction.x) + sqr(ray.direction.y) + sqr(ray.direction.z);
    float b = 2 * (ray.direction.x * (ray.origin.x - m_center.x) + ray.direction.y * (ray.origin.y - m_center.y) + ray.direction.z * (ray.origin.z - m_center.z));
    float c = sqr(ray.origin.x - m_center.x) + sqr(ray.origin.y - m_center.y) + sqr(ray.origin.z - m_center.z) - sqr(m_radius);
        
    float underRoot = sqr(b) - 4 * a * c;
    if (underRoot < 0) return INFINITY;

    float root = fast_sqrt(underRoot);
    float x1 = (-b - root) / (2 * a);
    if (x1 > 0.005) return x1;

    float x2 = (-b + root) / (2 * a);
    if (x2 > 0.005) return x2;    
    
    return INFINITY;
  }

  Float3D getNormal(const Float3D& point) const override {
    return (point - m_center).normalize();
  }

  Color getColor() const override { return m_color; }

private:
  Float3D m_center;
  float m_radius;
  Color m_color;
};