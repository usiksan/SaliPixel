#include "SpModeRect.h"

#include <QObject>

SpModeRect::SpModeRect()
  {

  }


void SpModeRect::paint(SpImage &dest, QPoint p, QColor color)
  {
  if( mStep == 0 ) {
    mFirst = p;
    dest.drawPixel( mFirst, color );
    }
  else {
    QPoint a( mFirst.x(), p.y() );
    QPoint b( p.x(), mFirst.y() );
    dest.drawLine( mFirst, a, color );
    dest.drawLine( a, p, color );
    dest.drawLine( p, b, color );
    dest.drawLine( b, mFirst, color );
    }
  }


QString SpModeRect::stepDescription()
  {
  if( mStep == 0 )
    return QObject::tr("Enter first corner of rect");
  return QObject::tr("Enter second corner of rect");
  }
