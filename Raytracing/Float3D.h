#pragma once

#include "OwnMath.h"

class Float3D {
public:
  float x;
  float y;
  float z;

public:  
  Float3D cross(const Float3D& triplet) const;
  float dot(const Float3D& triplet) const;
  float dot(float scalar) const;

  Float3D operator+ (const Float3D& triplet) const;
  Float3D operator- (const Float3D& triplet) const;

  void operator+= (const Float3D& triplet);
  void operator-= (const Float3D& triplet);

  void operator*= (float scalar);
  void operator/= (float scalar);

  Float3D turnX(float rad) const;
  Float3D turnY(float rad) const;
  Float3D turnZ(float rad) const;

  float angleTo(const Float3D& v);

  Float3D& normalize();
  float length() const;
  float invLength() const;
};

struct Float2D {
  float x;
  float y;
};

struct Ray {
  Float3D origin;
  Float3D direction;
};

Float3D operator* (float scalar, const Float3D& v);
Float3D operator* (const Float3D& v, float scalar);
Float3D operator/ (const Float3D& v, float scalar);

const Float3D xAxis{ 1, 0, 0 };
const Float3D yAxis{ 0, 1, 0 };
const Float3D zAxis{ 0, 0, 1 };