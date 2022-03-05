#include "SpCmdClearCircle.h"

SpCmdClearCircle::SpCmdClearCircle(QPoint center, QPoint p) :
  SpCmdCircle( center, p, QColor{} )
  {

  }


void SpCmdClearCircle::paint(SpImage &im)
  {
  if( mVisible )
    im.clearCircle( mCenter, mRadius );
  }



