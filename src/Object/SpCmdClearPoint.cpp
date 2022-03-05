#include "SpCmdClearPoint.h"

SpCmdClearPoint::SpCmdClearPoint( QPoint p ) :
  SpCmdPoint( p, QColor{} )
  {

  }


void SpCmdClearPoint::paint(SpImage &im)
  {
  if( mVisible )
    im.clearPixel( mPoint );
  }



