#include "Camera.h"
#include <qdebug.h>

PerspectiveCamera::PerspectiveCamera(Float3D pointOfView, Float2D resolution)
: m_pixmap(resolution.x, resolution.y)
{
  m_pixmap.clear();
  m_pointOfView = pointOfView;
  m_resolution = resolution;
  updateViewport();
}

void PerspectiveCamera::render(const Scene& scene) {
  for (int y = 0; y < m_resolution.y; y++) {
    for (int x = 0; x < m_resolution.x; x++) {
      Ray ray = createRay(x, y);
      m_pixmap.set(y, x, scene.getColor(ray));
    }
  }
}

Ray PerspectiveCamera::createRay(uint16_t x, uint16_t y) {
  Float3D direction = m_vectorPA;
  direction += x * m_vectorX;
  direction += y * m_vectorY;  
  direction.normalize();

  return Ray{ m_pointOfView, direction };
}

void PerspectiveCamera::updateViewport() {
  m_vectorX = yAxis.turnZ(m_angleZ) * (1/m_pixelPerUnit);
  m_vectorY = zAxis.turnY(m_angleY).turnZ(m_angleZ) * (-1/m_pixelPerUnit);
  Float3D pToCenter = (m_focalLenght * sqr(m_pixelPerUnit)) * m_vectorX.cross(m_vectorY);
  m_vectorPA = pToCenter - ((m_resolution.x - 1)/2) * m_vectorX - ((m_resolution.y - 1)/2) * m_vectorY;
}