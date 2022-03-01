#include "SpColor.h"


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
