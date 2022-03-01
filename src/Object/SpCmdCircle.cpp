#include "SpCmdCircle.h"

SpCmdCircle::SpCmdCircle(QPoint center, QPoint radius, QColor color) :
  SpCmd{color},
  mCenter{center},
  mRadius{radius}
  {

  }


void SpCmdCircle::paint(SpImage &im)
  {
  if( mVisible )
    im.drawCircle( mCenter, mRadius, mColor );
  }
