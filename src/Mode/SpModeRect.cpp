#include "SpModeRect.h"

SpModeRect::SpModeRect()
  {

  }


void SpModeRect::paint(QPainter &dest, QPoint p, QColor color)
  {
  dest.setPen( color );
  if( mStep == 0 ) {
    mFirst = p;
    dest.drawPoint( mFirst );
    }
  else {
    QPoint a( mFirst.x(), p.y() );
    QPoint b( p.x(), mFirst.y() );
    dest.drawLine( mFirst, a );
    dest.drawLine( a, p );
    dest.drawLine( p, b );
    dest.drawLine( b, mFirst );
    }
  }
