#include "SpModePoint.h"

SpModePoint::SpModePoint()
  {

  }


void SpModePoint::paint(QPainter &dest, QPoint p, QColor color)
  {
  dest.setPen(color);
  dest.drawPoint(p);
  }



bool SpModePoint::left()
  {
  return true;
  }
