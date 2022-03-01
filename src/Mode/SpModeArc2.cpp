#include "SpModeArc2.h"
#include "Object/SpCmdArc.h"

#include <QDebug>

SpModeArc2::SpModeArc2() :
  SpMode{2}
  {

  }


void SpModeArc2::paint(SpImage &dest, QPoint p, QColor color)
  {
  if( mStep == 0 ) {
    mStart = p;
    dest.drawPixel( mStart, color );
    }
  else if( mStep == 1 ) {
    mStop = p;
    dest.drawArc( SpImage::center( mStart, mStop ), mStart, mStop, color );
    }
  else {
    QPoint center( SpImage::center( mStart, mStop ) );
    auto radius = SpImage::distance( center, p );
    float dx = mStop.x() == mStart.x() ? 0.1 : mStop.x() - mStart.x();
    float dy = mStop.y() == mStart.y() ? 0.1 : mStop.y() - mStart.y();
    float pdx = p.x() == mStart.x() ? 0.1 : p.x() - mStart.x();
    float pdy = p.y() == mStart.y() ? 0.1 : p.y() - mStart.y();
    if( qAbs(dx) < qAbs(dy) ) {
      float k = dx / dy;
      float pk = pdx / pdy;
      //qDebug() << "1" << dx << dy << k << pdx << pdy << pk;
      if( k < pk )
        radius = -radius;
      center.rx() += radius;
      center.ry() -= radius * k;
      }
    else {
      float k = dy / dx;
      float pk = pdy / pdx;
      //qDebug() << "2" << dx << dy << k << pdx << pdy << pk;
      if( k < pk )
        radius = -radius;
      center.rx() += radius * k;
      center.ry() -= radius;
      }
    mCenter = center;
    dest.drawArc( center, mStart, mStop, color );
    }
  }




QString SpModeArc2::stepDescription()
  {
  if( mStep == 0 )
    return QObject::tr("Enter arc start point");
  if( mStep == 1 )
    return QObject::tr("Enter arc stop point");
  return QObject::tr("Enter arc center point");
  }



SpCmd *SpModeArc2::object(QPoint p, QColor color)
  {
  Q_UNUSED(p)
  return new SpCmdArc( mCenter, mStart, mStop, color );
  }
