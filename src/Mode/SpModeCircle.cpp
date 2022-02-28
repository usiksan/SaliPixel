#include "SpModeCircle.h"

#include <QObject>

SpModeCircle::SpModeCircle()
  {

  }


void SpModeCircle::paint(SpImage &dest, QPoint p, QColor color)
  {
//  dest.setPen( color );
//  if( mStep == 0 ) {
//    mCenter = p;
//    dest.drawPoint( mCenter );
//    }
//  else {
//    double dx = p.x() - mCenter.x();
//    double dy = p.y() - mCenter.y();
//    double distance = sqrt( dx * dx + dy * dy );
//    int radius = distance;
//    dest.drawEllipse( mCenter.x() - radius, mCenter.y() - radius, radius * 2, radius * 2 );
//    }
  }

bool SpModeCircle::left()
  {
  if( mStep == 0 ) {
    mStep = 1;
    return false;
    }
  mStep = 0;
  return true;
  }




void SpModeCircle::right()
  {
  mStep = 0;
  }



QString SpModeCircle::stepDescription()
  {
  if( mStep == 0 )
    return QObject::tr("Enter circle center point");
  return QObject::tr("Enter circle radius point");
  }
