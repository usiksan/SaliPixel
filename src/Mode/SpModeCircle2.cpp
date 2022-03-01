#include "SpModeCircle2.h"
#include "Object/SpCmdCircle.h"

SpModeCircle2::SpModeCircle2() :
  SpMode{1}
  {

  }


void SpModeCircle2::paint(SpImage &dest, QPoint p, QColor color)
  {
  if( mStep == 0 ) {
    mFirst = p;
    dest.drawPixel( mFirst, color );
    }
  else
    dest.drawCircle( SpImage::center( mFirst, p ), p, color );
  }




QString SpModeCircle2::stepDescription()
  {
  if( mStep == 0 )
    return QObject::tr("Enter first point of circle diametr");
  return QObject::tr("Enter second point of cicrle diametr");
  }



SpCmd *SpModeCircle2::object(QPoint p, QColor color)
  {
  return new SpCmdCircle( SpImage::center( mFirst, p ), p, color );
  }
