#include "SpColor.h"

//#include <QObject>

SpColor SpColor::brightness(float br) const
  {
  SpColor color(*this);
  color.mAlpha = 255 * br;
  return color;
  }



QColor SpColor::color() const
  {
  return QColor( mRed, mGreen, mBlue, mAlpha );
  }

void SpColor::append(SpColor color)
  {
  //Mix both color
  int alpha = qMin<int>( mAlpha, 255 - color.mAlpha );
  mRed   = (mRed * alpha + color.mRed * color.mAlpha) >> 8;
  mGreen = (mGreen * alpha + color.mGreen * color.mAlpha) >> 8;
  mBlue  = (mBlue * alpha + color.mBlue * color.mAlpha) >> 8;
  mAlpha = qBound<int>( 0, alpha + color.mAlpha, 255 );
  }
