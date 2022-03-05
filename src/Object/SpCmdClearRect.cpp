#include "SpCmdClearRect.h"

SpCmdClearRect::SpCmdClearRect(QPoint v0, QPoint v1) :
  SpCmdRect( v0, v1, QColor{} )
  {

  }


void SpCmdClearRect::paint(SpImage &im)
  {
  if( mVisible )
    im.clearRect( mFirst, mSecond );
  }



