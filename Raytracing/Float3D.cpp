#include "Float3D.h"
#include <assert.h>

float Float3D::length() const {
  return fast_sqrt(sqr(x) + sqr(y) + sqr(z));
}

float Float3D::invLength() const {
  return fast_rsqrt(sqr(x) + sqr(y) + sqr(z));
}

Float3D& Float3D::normalize() {
  float inv = fast_rsqrt(sqr(x) + sqr(y) + sqr(z));
  x *= inv;
  y *= inv;
  z *= inv;
  return *this;
}

Float3D Float3D::cross(const Float3D& triplet) const {
  return {
    y * triplet.z - z * triplet.y,
    z * triplet.x - x * triplet.z,
    x * triplet.y - y * triplet.x,
  };
}

float Float3D::dot(const Float3D& triplet) const {
  return triplet.x * x + triplet.y * y + triplet.z * z;
}

float Float3D::dot(float scalar) const {
  return scalar * x + scalar * y + scalar * z;
}

Float3D Float3D::operator+ (const Float3D& triplet) const {
  return {
    x + triplet.x,
    y + triplet.y,
    z + triplet.z,
  };
}

Float3D Float3D::operator- (const Float3D& triplet) const {
  return {
    x - triplet.x,
    y - triplet.y,
    z - triplet.z,
  };
}

void Float3D::operator+= (const Float3D& triplet) {
  x += triplet.x;
  y += triplet.y;
  z += triplet.z;
}

void Float3D::operator-= (const Float3D& triplet) {
  x -= triplet.x;
  y -= triplet.y;
  z -= triplet.z;
}

void Float3D::operator*= (float scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
}

void Float3D::operator/= (float scalar) {
  x /= scalar;
  y /= scalar;
  z /= scalar;
}

Float3D Float3D::turnX(float rad) const {
  float sin = sinf(rad);
  float cos = cosf(rad);

  return {
    x,
    cos * y - sin * z,
    sin * y + cos * z
  };
}

Float3D Float3D::turnY(float rad) const {
  float sin = sinf(rad);
  float cos = cosf(rad);

  return {
    cos * x + sin * z,
    y,
    -sin * x + cos * z
  };
}

Float3D Float3D::turnZ(float rad) const {
  float sin = sinf(rad);
  float cos = cosf(rad);

  return {
    cos * x - sin * y,
    sin * x + cos * y,
    z
  };
}

float Float3D::angleTo(const Float3D& v) {
  float dotProduct = dot(v);
  dotProduct *= invLength();
  dotProduct *= v.invLength();
  if (dotProduct < -1.0) dotProduct = -1.0;
  if (dotProduct > 1.0) dotProduct = 1.0;
  return acos(dotProduct);
}

Float3D operator* (float scalar, const Float3D& v) {
  return { 
    scalar * v.x, 
    scalar * v.y, 
    scalar * v.z 
  };
}

Float3D operator* (const Float3D& v, float scalar) {
  return { 
    scalar * v.x, 
    scalar * v.y, 
    scalar * v.z 
  };
}

Float3D operator/ (const Float3D& v, float scalar) {
  return { 
    scalar / v.x, 
    scalar / v.y, 
    scalar / v.z 
  };
}