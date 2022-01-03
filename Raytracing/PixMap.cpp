#include "PixMap.h"

const Color Pixmap::defaultColor = { 0, 0, 0 };

Pixmap::Pixmap(int width, int height) {
  m_width = width;
  m_height = height;
  m_pixels = new Color[width * height];
}

void Pixmap::set(int y, int x, Color color) {
  if (y >= m_height || x >= m_width || y < 0 || x < 0)
    return;

  m_pixels[y * m_height + x] = color;
}

const Color& Pixmap::get(int y, int x) const {
  if (y >= m_height || x >= m_width)
    return defaultColor;

  return m_pixels[y * m_height + x];
}

void Pixmap::clear() {
  for (int x = 0; x < m_width; x++) {
    for (int y = 0; y < m_height; y++) {
      m_pixels[y * m_height + x].red   = 0;
      m_pixels[y * m_height + x].green = 0;
      m_pixels[y * m_height + x].blue  = 0;
    }
  }
}