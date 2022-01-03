#pragma once

#include "Color.h"

class Pixmap {
public:
  Pixmap(int width, int height);

  void set(int y, int x, Color color);
  const Color& get(int y, int x) const;

  void clear();

  int height() const { return m_height; }
  int width() const { return m_width; }

private:
  static const Color defaultColor;
  Color* m_pixels = nullptr;
  int m_height = 0;
  int m_width = 0;
};