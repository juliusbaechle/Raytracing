#pragma once

#include <qthread.h>
#include <qimage.h>
#include <qpainter.h>
#include <qmutex.h>
#include <qdebug.h>
#include "PixMap.h"

class ThreadedPainter : public QThread {
  Q_OBJECT

signals:
  void sglFinished();

public:
  ThreadedPainter(quint32 height, quint32 width)
    : m_workImage(height, width, QImage::Format::Format_RGB32)
  {
    moveToThread(this);
    start();
  }

  QImage& lastImage() { QMutexLocker l(&m_mutex); return m_finishedImage; }

  void draw(Pixmap pixels) {
    QMetaObject::invokeMethod(this, [this, pixels]() {
      m_mutex.lock();
      for (int y = 0; y < pixels.height(); y++) {
        for (int x = 0; x < pixels.width(); x++) {
          const Color& color = pixels.get(y, x);
          m_workImage.setPixel(QPoint(x, y), qRgb(color.red, color.green, color.blue));
        }
      }

      m_finishedImage = m_workImage.copy().scaled(800, 800);    
      m_mutex.unlock();

      emit sglFinished();      
    });
  }

private:
  bool m_bPainting = false;
  QMutex m_mutex;
  QImage m_finishedImage;
  QImage m_workImage;
};