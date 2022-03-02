#include "SpCmdClearPoint.h"

SpCmdClearPoint::SpCmdClearPoint( QPoint p ) :
  SpCmd(),
  mPoint(p)
  {

  }


void SpCmdClearPoint::paint(SpImage &im)
  {
  if( mVisible )
    im.clearPixel( mPoint );
  }
