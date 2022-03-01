#include "SpModeFillRect.h"
#include "Object/SpCmdFillRect.h"

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


SpCmd *SpModeFillRect::object(QPoint p, QColor color)
  {
  return new SpCmdFillRect( mFirst, p, color );
  }
