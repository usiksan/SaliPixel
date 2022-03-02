#include "SpModeClearCircle.h"
#include "Object/SpCmdClearCircle.h"

#include <QObject>

SpModeClearCircle::SpModeClearCircle() :
  SpMode{1}
  {

  }


void SpModeClearCircle::paint(SpImage &dest, QPoint p, QColor color)
  {
  Q_UNUSED(color)
  if( mStep == 0 ) {
    mCenter = p;
    dest.clearPixel( mCenter );
    }
  else
    dest.clearCircle( mCenter, p );
  }

QString SpModeClearCircle::stepDescription()
  {
  if( mStep == 0 )
    return QObject::tr("Enter clear circle center point");
  return QObject::tr("Enter clear circle radius point");
  }

SpCmd *SpModeClearCircle::object(QPoint p, QColor color)
  {
  Q_UNUSED(color)
  return new SpCmdClearCircle( mCenter, p );
  }
