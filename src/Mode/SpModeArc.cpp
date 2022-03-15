#include "SpModeArc.h"
#include "Object/SpCmdArc.h"

#include <QObject>

SpModeArc::SpModeArc() :
  SpMode(2)
  {

  }


void SpModeArc::paint(SpImage &dest, QPoint p, QColor color)
  {
  if( mStep == 0 ) {
    mCenter = p;
    dest.drawPixel( mCenter, color );
    }
  else if( mStep == 1 ) {
    mStart = p;
    dest.drawLine( mCenter, mStart, color );
    }
  else
    dest.drawArc( mCenter, mStart, p, color );
  }





QString SpModeArc::stepDescription()
  {
  if( mStep == 0 )
    return QObject::tr("Enter arc center point");
  if( mStep == 1 )
    return QObject::tr("Enter arc start point");
  return QObject::tr("Enter arc end point");
  }






SpCmd *SpModeArc::object(QPoint p, QColor color)
  {
  return new SpCmdArc( mCenter, mStart, p, color );
  }

