#include "SpModeTriangle.h"
#include "Object/SpCmdLine.h"

SpModeTriangle::SpModeTriangle() :
  SpMode{2}
  {

  }


void SpModeTriangle::paint(SpImage &dest, QPoint p, QColor color)
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
    dest.drawLine( mFirst, mSecond, color );
    dest.drawLine( mFirst, p, color );
    dest.drawLine( mSecond, p, color );
    }
  }




QString SpModeTriangle::stepDescription()
  {
  if( mStep == 0 )
    return QObject::tr("Enter first triangle vertex");
  if( mStep == 1 )
    return QObject::tr("Enter second triangle vertex");
  return QObject::tr("Enter third triangle vertex");
  }




bool SpModeTriangle::left(SpCmdList &dest, QPoint p, QColor color)
  {
  if( stepLast() ) {
    dest.append( new SpCmdLine( mFirst, mSecond, color ) );
    dest.append( new SpCmdLine( mFirst, p, color ) );
    dest.append( new SpCmdLine( mSecond, p, color ) );
    }
  return stepNext();
  }
