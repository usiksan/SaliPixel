#include "SpModeFillCircle.h"
#include "Object/SpCmdFillCircle.h"

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


SpCmd *SpModeFillCircle::object(QPoint p, QColor color)
  {
  return new SpCmdFillCircle( mCenter, p, color );
  }
