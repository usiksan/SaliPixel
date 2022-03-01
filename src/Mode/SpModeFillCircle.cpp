#include "SpModeFillCircle.h"

SpModeFillCircle::SpModeFillCircle()
  {

  }


void SpModeFillCircle::paint(SpImage &dest, QPoint p, QColor color)
  {
  if( mStep == 0 ) {
    mCenter = p;
    dest.drawPixel( mCenter, color );
    }
  else
    dest.drawFillCircle( mCenter, p, color );
  }
