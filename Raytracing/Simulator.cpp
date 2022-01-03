#include "Simulator.h"
#include <qpainter.h>
#include <qdebug.h>
#include <qevent.h>
#include <qthread.h>

#define PIXEL_SIZE 10

Simulator::Simulator(uint16_t width, uint16_t height) 
  : m_painter(width, height)
{
  QWidget::show();
  setWindowTitle("Display Simulator");
  setFixedSize(800, 800);
  QObject::connect(&m_painter, &ThreadedPainter::sglFinished, this, (void(QWidget::*)()) &QWidget::repaint);
}

void Simulator::show(const Pixmap& pixels) {
  m_painter.draw(pixels);
}

void Simulator::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.beginNativePainting();
  painter.drawImage(QPoint(0, 0), m_painter.lastImage());
  painter.endNativePainting();  
}