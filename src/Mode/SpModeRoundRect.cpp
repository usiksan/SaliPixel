#include "SpModeRoundRect.h"
#include "Object/SpCmdLine.h"
#include "Object/SpCmdArc.h"

#include <QObject>

SpModeRoundRect::SpModeRoundRect() :
  SpMode{2}
  {

  }


void SpModeRoundRect::paint(SpImage &dest, QPoint p, QColor color)
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
    dest.drawArc( dest.center( mSecond, p ), mSecond, p, color );
    dest.drawLine( p, third, color );
    dest.drawArc( dest.center( third, mFirst ), third, mFirst, color );
    }
  }



bool SpModeRoundRect::left(SpCmdPtrList &dest, QPoint p, QColor color)
  {
  if( stepLast() ) {
    QPoint delta = p - mSecond;
    QPoint third = mFirst + delta;
    dest.append( new SpCmdLine( mFirst, mSecond, color ) );
    dest.append( new SpCmdArc( SpImage::center( mSecond, p ), mSecond, p, color ) );
    dest.append( new SpCmdLine( p, third, color ) );
    dest.append( new SpCmdArc( SpImage::center( third, mFirst ), third, mFirst, color ) );
    }
  return stepNext();
  }



QString SpModeRoundRect::stepDescription()
  {
  if( mStep == 0 )
    return QObject::tr("Enter first point of round rect");
  if( mStep == 1 )
    return QObject::tr("Enter second point of round rect");
  return QObject::tr("Enter third point of round rect");
  }
