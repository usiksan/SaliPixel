#include "SpModeFill.h"
#include "Object/SpCmdFill.h"

#include <QObject>

SpModeFill::SpModeFill() :
  SpMode{0}
  {

  }


void SpModeFill::paint(SpImage &dest, QPoint p, QColor color)
  {
//  if( mStep == 0 )
//    dest.drawPixel( p, color );
  dest.drawFill( p, color );
  }



QString SpModeFill::stepDescription()
  {
  return QObject::tr("Enter start fill point");
  }


SpCmd *SpModeFill::object(QPoint p, QColor color)
  {
  return new SpCmdFill( p, color );
  }
