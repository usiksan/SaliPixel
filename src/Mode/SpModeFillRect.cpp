#include "SpModeFillRect.h"

SpModeFillRect::SpModeFillRect()
  {

  }


void SpModeFillRect::paint(SpImage &dest, QPoint p, QColor color)
  {
  if( mStep == 0 ) {
    mFirst = p;
    dest.drawPixel( mFirst, color );
    }
  else
    dest.drawFillRect( mFirst, p, color );
  }
