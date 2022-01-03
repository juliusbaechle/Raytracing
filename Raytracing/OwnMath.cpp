#include "Math.h"

// See https://www.youtube.com/watch?v=p8u_k2LIZyo for reference
float fast_rsqrt(float x) {
  long i;
  float x2, y;
  const float threehalfs = 1.5f;
  
  x2 = x * 0.5f;
  y = x;
  i = *(long*)&y;
  i = 0x5F3759DF - (i >> 1);
  y = *(float*)&i;
  y = y * (threehalfs - x2 * y * y);
  
  return y;
}

float fast_sqrt(float x) {
  return 1 / fast_rsqrt(x);
}