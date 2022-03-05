#include "SpCmdFillRect.h"

SpCmdFillRect::SpCmdFillRect(QPoint f, QPoint s, QColor color) :
  SpCmdRect( f, s, color )
  {

  }


void SpCmdFillRect::paint(SpImage &im)
  {
  if( mVisible )
    im.drawFillRect( mFirst, mSecond, mColor );
  }


