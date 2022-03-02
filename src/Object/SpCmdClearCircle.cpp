#include "SpCmdClearCircle.h"

SpCmdClearCircle::SpCmdClearCircle(QPoint center, QPoint p) :
  SpCmd(),
  mCenter(center),
  mPoint(p)
  {

  }


void SpCmdClearCircle::paint(SpImage &im)
  {
  if( mVisible )
    im.clearCircle( mCenter, mPoint );
  }
