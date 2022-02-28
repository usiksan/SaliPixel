#include "SpColor.h"


SpColor SpColor::brightness(float br) const
  {
  SpColor color(SpColorSolid);
  color.mRed   = mRed * br;
  color.mGreen = mGreen * br;
  color.mBlue  = mBlue  * br;
  return color;
  }



QColor SpColor::color() const
  {
  return QColor( mRed, mGreen, mBlue );
  }
