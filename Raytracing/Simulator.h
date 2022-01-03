#ifndef SIMU__H__
#define SIMU__H__

#include <qmainwindow.h>
#include <qbitmap.h>
#include "ThreadedPainter.h"
#include "Display.h"

class Simulator : public QWidget, public Display {
public:
  Simulator(uint16_t width, uint16_t height);

  void show(const Pixmap& matrix) override;

protected:
  void paintEvent(QPaintEvent* event) override;
  
private:
  ThreadedPainter m_painter;
  QImage m_workImage;
};

#endif