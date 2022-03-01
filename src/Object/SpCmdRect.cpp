#include "SpCmdRect.h"

SpCmdRect::SpCmdRect()
  {

  }


void SpCmdRect::paint(SpImage &im)
  {
  if( mVisible )
    im.drawRect( mFirst, mSecond, mColor );
  }
