#include "SpModeFill.h"


#include <QObject>

SpModeFill::SpModeFill()
  {

  }


void SpModeFill::paint(SpImage &dest, QPoint p, QColor color)
  {
//  if( mStep == 0 )
//    dest.drawPixel( p, color );
  dest.drawFill( p, color );
  }

bool SpModeFill::left()
  {
  return true;
  }


QString SpModeFill::stepDescription()
  {
  return QObject::tr("Enter start fill point");
  }
