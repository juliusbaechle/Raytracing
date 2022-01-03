#pragma once

#include "Float3D.h"
#include "PixMap.h"
#include "Scene.h"

class Camera {
public:
  virtual void render(const Scene& scene) = 0;
  virtual const Pixmap& picture() const = 0;
};

class PerspectiveCamera : public Camera {
public:
  PerspectiveCamera(Float3D pointOfView, Float2D resolution);
  void render(const Scene& scene) override;
  const Pixmap& picture() const override { return m_pixmap; };

public:
  Float3D pointOfView() const { return m_pointOfView; }
  void setPointOfView(Float3D pointOfView) { m_pointOfView = pointOfView; }

  Float2D resolution() const { return m_resolution; }
  void setResolution(Float2D resolution) { m_resolution = resolution; updateViewport(); }

  float pixelPerUnit() const { return m_pixelPerUnit; }
  void setPixelPerUnit(float pixelPerUnit) { m_pixelPerUnit = pixelPerUnit; updateViewport(); }

  float angleAroundVertical() const { return m_angleZ; }
  void setAngleAroundVertical(float angleZ) { m_angleZ = angleZ; updateViewport();}

  float angleToHorizontal() const { return m_angleY; }
  void setAngleToHorizontal(float angleY) { m_angleY = angleY; updateViewport(); }

  float focalLength() const { return m_focalLenght; }
  void setFocalLength(float focalLength) { m_focalLenght = focalLength; updateViewport(); }

private:
  Ray createRay(uint16_t x, uint16_t y);
  void updateViewport();

private:
  Pixmap m_pixmap;

  Float3D m_pointOfView;
  Float3D m_vectorPA;
  Float3D m_vectorX;
  Float3D m_vectorY;

  Float2D m_resolution;
  float m_pixelPerUnit = 200; // Pixel pro Einheit in Szene
  float m_angleZ = 0.0;
  float m_angleY = 0.0;
  float m_focalLenght = 4;
};