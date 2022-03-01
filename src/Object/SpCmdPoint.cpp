#include "SpCmdPoint.h"

SpCmdPoint::SpCmdPoint()
  {

  }


void SpCmdPoint::paint(SpImage &im)
  {
  if( mVisible )
    im.drawPixel( mPoint, mColor );
  }
