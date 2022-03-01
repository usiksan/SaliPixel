#include "SpModeCircle.h"

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



bool SpModeCircle::left()
  {
  if( mStep == 0 ) {
    mStep = 1;
    return false;
    }
  mStep = 0;
  return true;
  }




void SpModeCircle::right()
  {
  mStep = 0;
  }



QString SpModeCircle::stepDescription()
  {
  if( mStep == 0 )
    return QObject::tr("Enter circle center point");
  return QObject::tr("Enter circle radius point");
  }
