#include "SpModeLine.h"
#include "Object/SpCmdLine.h"

#include <QObject>

SpModeLine::SpModeLine() :
  SpMode{1}
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





QString SpModeLine::stepDescription()
  {
  if( mStep == 0 )
    return QObject::tr("Enter first point of line");
  return QObject::tr("Enter second point of line");
  }


SpCmd *SpModeLine::object(QPoint p, QColor color)
  {
  return new SpCmdLine( mFirst, p, color );
  }
