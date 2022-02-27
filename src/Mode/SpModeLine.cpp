#include "SpModeLine.h"

SpModeLine::SpModeLine()
  {

  }


void SpModeLine::paint(QPainter &dest, QPoint p, QColor color)
  {
  dest.setPen( color );
  if( mStep == 0 ) {
    mFirst = p;
    dest.drawPoint( mFirst );
    }
  else
    dest.drawLine( mFirst, p );
  }




bool SpModeLine::left()
  {
  if( mStep == 0 ) {
    mStep = 1;
    return false;
    }
  mStep = 0;
  return true;
  }



void SpModeLine::right()
  {
  mStep = 0;
  }
