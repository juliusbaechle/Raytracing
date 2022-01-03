#pragma once

#include "Primitive.h"

class Fragment : public Primitive {
public:
  Fragment(Float3D vectorA, Float3D vectorAtoB, Float3D vectorAtoC, bool a_bIsTriangle, Color color) {
    m_A = vectorA;
    m_AtoB = vectorAtoB;
    m_AtoC = vectorAtoC;
    m_bTriangle = a_bIsTriangle;
    m_color = color;
  }
  
  // See https://www.uni-koblenz.de/~cg/Studienarbeiten/janmueller.pdf for reference
  float getDistance(const Ray& ray) const override {
    Float3D crossC = ray.direction.cross(m_AtoC);
    float det = 1.0f / crossC.dot(m_AtoB);

    Float3D AO = ray.origin - m_A;
    Float3D crossB = AO.cross(m_AtoB);

    double u = det * crossC.dot(AO);
    double v = det * crossB.dot(ray.direction);

    bool bValid;
    if (m_bTriangle)
      bValid = (u >= 0) && (v >= 0) && (u + v <= 1);
    else
      bValid = (u >= 0) && (u <= 1) && (v >= 0) && (v <= 1);

    if (bValid) {
      float t = det * crossB.dot(m_AtoC);
      return t > 0.0001f ? t : INFINITY;
    } else {
      return INFINITY;
    }
  }

  Color getColor() const override { return m_color; }

  Float3D getNormal(const Float3D& point) const override {
    return m_AtoB.cross(m_AtoC).normalize();
  }

private:
  Float3D m_A;
  Float3D m_AtoB;
  Float3D m_AtoC;
  bool m_bTriangle;
  Color m_color;
};