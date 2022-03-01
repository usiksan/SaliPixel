#include "SpCmdFillCircle.h"

SpCmdFillCircle::SpCmdFillCircle(QPoint center, QPoint radius, QColor color) :
  SpCmdCircle( center, radius, color )
  {

  }


void SpCmdFillCircle::paint(SpImage &im)
  {
  if( mVisible )
    im.drawFillCircle( mCenter, mRadius, mColor );
  }
