#include "SpCmdClearRect.h"

SpCmdClearRect::SpCmdClearRect(QPoint v0, QPoint v1) :
  SpCmd(),
  mVertex0(v0),
  mVertex1(v1)
  {

  }


void SpCmdClearRect::paint(SpImage &im)
  {
  if( mVisible )
    im.clearRect( mVertex0, mVertex1 );
  }
