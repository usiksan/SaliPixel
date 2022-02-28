#include "SpModeLine.h"

#include <QObject>

SpModeLine::SpModeLine()
  {

  }


void SpModeLine::paint(SpImage &dest, QPoint p, QColor color)
  {
  if( mStep == 0 ) {
    mFirst = p;
    dest.drawPixel( mFirst, color );
    }
  else
    dest.drawLine( mFirst, p, color );
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


QString SpModeLine::stepDescription()
  {
  if( mStep == 0 )
    return QObject::tr("Enter first point of line");
  return QObject::tr("Enter second point of line");
  }
