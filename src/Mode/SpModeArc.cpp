#include "SpModeArc.h"

#include <QObject>

SpModeArc::SpModeArc()
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



bool SpModeArc::left()
  {
  if( mStep < 2 ) {
    mStep++;
    return false;
    }
  mStep = 0;
  return true;
  }



void SpModeArc::right()
  {
  if( mStep )
    mStep--;
  }



QString SpModeArc::stepDescription()
  {
  if( mStep == 0 )
    return QObject::tr("Enter arc center point");
  if( mStep == 1 )
    return QObject::tr("Enter arc start point");
  return QObject::tr("Enter arc end point");
  }
