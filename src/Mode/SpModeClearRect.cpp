#include "SpModeClearRect.h"
#include "Object/SpCmdClearRect.h"

#include <QObject>

SpModeClearRect::SpModeClearRect() :
  SpMode{1}
  {

  }


void SpModeClearRect::paint(SpImage &dest, QPoint p, QColor color)
  {
  Q_UNUSED(color)
  if( mStep == 0 ) {
    mFirst = p;
    dest.clearPixel( p );
    }
  else {
    dest.clearRect( mFirst, p );
    }
  }

QString SpModeClearRect::stepDescription()
  {
  if( mStep == 0 )
    return QObject::tr("Enter first corner for clear rect");
  return QObject::tr("Enter second corner for clear rect");
  }

SpCmd *SpModeClearRect::object(QPoint p, QColor color)
  {
  Q_UNUSED(color)
  return new SpCmdClearRect( mFirst, p );
  }
