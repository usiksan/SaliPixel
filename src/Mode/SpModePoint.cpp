#include "SpModePoint.h"
#include "Object/SpCmdPoint.h"

#include <QObject>

SpModePoint::SpModePoint() :
  SpMode{0}
  {

  }


void SpModePoint::paint(SpImage &dest, QPoint p, QColor color)
  {
  dest.drawPixel( p, color );
  }




QString SpModePoint::stepDescription()
  {
  return QObject::tr("Enter point position");
  }




SpCmd *SpModePoint::object(QPoint p, QColor color)
  {
  return new SpCmdPoint( p, color );
  }
