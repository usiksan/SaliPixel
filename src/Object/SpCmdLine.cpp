#include "SpCmdLine.h"

SpCmdLine::SpCmdLine()
  {

  }


void SpCmdLine::paint(SpImage &im)
  {
  if( mVisible )
    im.drawLine( mStart, mStop, mColor );
  }
