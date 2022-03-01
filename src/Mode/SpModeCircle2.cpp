#include "SpModeCircle2.h"

SpModeCircle2::SpModeCircle2() :
  SpMode{1}
  {

  }


void SpModeCircle2::paint(SpImage &dest, QPoint p, QColor color)
  {
  if( mStep == 0 ) {
    mFirst = p;
    dest.drawPixel( mFirst, color );
    }
  else
    dest.drawCircle( SpImage::center( mFirst, p ), p, color );
  }


bool SpModeCircle2::left()
  {
  if( mStep == 0 ) {
    mStep = 1;
    return false;
    }
  mStep = 0;
  return true;
  }


QString SpModeCircle2::stepDescription()
  {
  if( mStep == 0 )
    return QObject::tr("Enter first point of circle diametr");
  return QObject::tr("Enter second point of cicrle diametr");
  }

