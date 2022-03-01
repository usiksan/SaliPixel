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
    dest.drawRect( mFirst, p, color );
    }
  }


QString SpModeRect::stepDescription()
  {
  if( mStep == 0 )
    return QObject::tr("Enter first corner of rect");
  return QObject::tr("Enter second corner of rect");
  }
