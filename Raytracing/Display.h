#pragma once

#include "PixMap.h"

class Display {
public:
  virtual void show(const Pixmap& matrix) = 0;
};