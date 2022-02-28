#include "SpModePoint.h"

#include <QObject>

SpModePoint::SpModePoint()
  {

  }


void SpModePoint::paint(SpImage &dest, QPoint p, QColor color)
  {
  dest.drawPixel( p, color );
  }



bool SpModePoint::left()
  {
  return true;
  }


QString SpModePoint::stepDescription()
  {
  return QObject::tr("Enter point position");
  }
