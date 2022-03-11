#include "SpModeParallelogramm.h"
#include "Object/SpCmdLine.h"

#include <QObject>

SpModeParallelogramm::SpModeParallelogramm() :
  SpMode{2}
  {

  }


void SpModeParallelogramm::paint(SpImage &dest, QPoint p, QColor color)
  {
  if( mStep == 0 ) {
    mFirst = p;
    dest.drawPixel( mFirst, color );
    }
  else if( mStep == 1 ) {
    mSecond = p;
    dest.drawLine( mFirst, mSecond, color );
    }
  else {
    QPoint delta = p - mSecond;
    QPoint third = mFirst + delta;
    dest.drawLine( mFirst, mSecond, color );
    dest.drawLine( mSecond, p, color );
    dest.drawLine( p, third, color );
    dest.drawLine( third, mFirst, color );
    }
  }



bool SpModeParallelogramm::left(SpCmdList &dest, QPoint p, QColor color)
  {
  if( stepLast() ) {
    QPoint delta = p - mSecond;
    QPoint third = mFirst + delta;
    dest.append( new SpCmdLine( mFirst, mSecond, color ) );
    dest.append( new SpCmdLine( mSecond, p, color ) );
    dest.append( new SpCmdLine( p, third, color ) );
    dest.append( new SpCmdLine( third, mFirst, color ) );
    }

  return stepNext();
  }

QString SpModeParallelogramm::stepDescription()
  {
  if( mStep == 0 )
    return QObject::tr("Enter first point of parallelogramm");
  if( mStep == 1 )
    return QObject::tr("Enter second point of parallelogramm");
  return QObject::tr("Enter third point of parallelogramm");
  }
