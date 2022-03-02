#include "SpModeClearPoint.h"
#include "Object/SpCmdClearPoint.h"

#include <QObject>

SpModeClearPoint::SpModeClearPoint() :
  SpMode(0)
  {

  }


void SpModeClearPoint::paint(SpImage &dest, QPoint p, QColor color)
  {
  Q_UNUSED(color)
  dest.clearPixel( p );
  }

QString SpModeClearPoint::stepDescription()
  {
  return QObject::tr("Click to clear point");
  }

SpCmd *SpModeClearPoint::object(QPoint p, QColor color)
  {
  Q_UNUSED(color)
  return new SpCmdClearPoint(p);
  }
