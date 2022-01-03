#pragma once

#include <stdint.h>

#define min(x, y) (x < y ? (x) : (y))
#define max(x, y) (x > y ? (x) : (y))

struct Color {
  uint8_t red   = 255;
  uint8_t green = 255;
  uint8_t blue  = 255;
  uint8_t alpha = 255;

  bool operator== (Color color) {
    if (color.red   != red  ) return false;
    if (color.green != green) return false;
    if (color.blue  != blue ) return false;
    return true;
  }

  void operator*=(float scalar) {
    red   = min(255, scalar * red  );
    green = min(255, scalar * green);
    blue  = min(255, scalar * blue );
  }

  void combine(Color color) {
    red   = ((float) color.red   + red  ) / 2;
    green = ((float) color.green + green) / 2;
    blue  = ((float) color.blue  + blue ) / 2;
  }

  void add(int16_t light) {
    red   += minMax(-red  , light, 255 - red  );
    green += minMax(-green, light, 255 - green);
    blue  += minMax(-blue , light, 255 - blue );
  }

  int minMax(int min, int value, int max) {
    if (value < min) 
      return min;
    if (value > max) 
      return max;
    return value;
  }
};

inline Color operator* (Color color, float scale) {
  return {
    (uint8_t) min(255, color.red   * scale),
    (uint8_t) min(255, color.green * scale),
    (uint8_t) min(255, color.blue  * scale)
  };
}

inline Color operator* (float scale, Color color) {
  return {
    (uint8_t) min(255, color.red   * scale),
    (uint8_t) min(255, color.green * scale),
    (uint8_t) min(255, color.blue  * scale)
  };
}

inline Color operator+ (Color c1, Color c2) {
  return {
    (uint8_t) min(255, c1.red   + c2.red  ),
    (uint8_t) min(255, c1.green + c2.green),
    (uint8_t) min(255, c1.blue  + c2.blue )
  };
}

const Color black{ 0, 0, 0 };
const Color white{ 255, 255, 255 };