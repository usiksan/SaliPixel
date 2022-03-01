#include "SpModeTriangle.h"

SpModeTriangle::SpModeTriangle()
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

bool SpModeTriangle::left()
  {
  if( mStep < 2 ) {
    mStep++;
    return false;
    }
  mStep = 0;
  return true;
  }

void SpModeTriangle::right()
  {
  if( mStep )
    mStep--;
  }

QString SpModeTriangle::stepDescription()
  {
  if( mStep == 0 )
    return QObject::tr("Enter first triangle vertex");
  if( mStep == 1 )
    return QObject::tr("Enter second triangle vertex");
  return QObject::tr("Enter third triangle vertex");
  }
