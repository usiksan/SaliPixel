#include "SpColor.h"

//#include <QObject>

SpColor SpColor::brightness(float br) const
  {
  SpColor color(*this);
  color.mAlpha = 255 * br;
  return color;
  }

SpColor SpColor::scale(float s) const
  {
  SpColor color(*this);
  color.mAlpha = color.mAlpha * s;
  return color;
  }



QColor SpColor::color() const
  {
  return QColor( mRed, mGreen, mBlue, mAlpha );
  }

void SpColor::append(SpColor color)
  {
  //Mix both color
  int p100 = mAlpha + color.mAlpha;
  if( p100 ) {
    mRed   = (mRed * mAlpha + color.mRed * color.mAlpha) / p100;
    mGreen = (mGreen * mAlpha + color.mGreen * color.mAlpha) / p100;
    mBlue  = (mBlue * mAlpha + color.mBlue * color.mAlpha) / p100;
    mAlpha = qBound<int>( 0, mAlpha + color.mAlpha, 255 );
    }
  }

void SpColor::invert()
  {
  mAlpha = 255;
  mRed   = 255 - mRed;
  mGreen = 255 - mGreen;
  mBlue  = 255 - mBlue;
  }
