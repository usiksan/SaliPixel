#include "SpModeCircle.h"
#include "Object/SpCmdCircle.h"

#include <QObject>

SpModeCircle::SpModeCircle() :
  SpMode{1}
  {

  }


void SpModeCircle::paint(SpImage &dest, QPoint p, QColor color)
  {
  if( mStep == 0 ) {
    mCenter = p;
    dest.drawPixel( mCenter, color );
    }
  else
    dest.drawCircle( mCenter, p, color );
  }






QString SpModeCircle::stepDescription()
  {
  if( mStep == 0 )
    return QObject::tr("Enter circle center point");
  return QObject::tr("Enter circle radius point");
  }




SpCmd *SpModeCircle::object(QPoint p, QColor color)
  {
  return new SpCmdCircle( mCenter, p, color );
  }
