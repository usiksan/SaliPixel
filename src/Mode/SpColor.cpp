/*
Project "Combine vector-pixel graphic editor for small image like icon"

Author
  Sibilev Alexander S.

Web
  www.saliLab.com
  www.saliLab.ru

Description
  Color representation - one pixel
*/
#include "SpColor.h"



//!
//! \brief brightness Builds color with alpha channel equals br
//! \param br         Coef for alpha 0-1.0 will produce alpha channel 0-255 accordingly
//! \return           Color with new alpha channel
//!
SpColor SpColor::brightness(float br) const
  {
  SpColor color(*this);
  color.mAlpha = 255 * br;
  return color;
  }




//!
//! \brief scale Change current alpha channel by multiply it to scale factor s and return resulting color
//!              It make color more transparently
//! \param s     Scale factor
//! \return      Color with modified alpha channel
//!
SpColor SpColor::scale(float s) const
  {
  SpColor color(*this);
  color.mAlpha = color.mAlpha * s;
  return color;
  }



//!
//! \brief color Convert color to QColor form
//! \return      This color in form QColor
//!
QColor SpColor::color() const
  {
  return QColor( mRed, mGreen, mBlue, mAlpha );
  }





//!
//! \brief append Mixes two colors: current and given
//! \param color  Color to mix with current
//!
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



//!
//! \brief invert Make inversion of current color
//!
void SpColor::invert()
  {
  mAlpha = 255;
  mRed   = 255 - mRed;
  mGreen = 255 - mGreen;
  mBlue  = 255 - mBlue;
  }
