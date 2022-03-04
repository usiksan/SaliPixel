#include "SpCmdAreaScale.h"

SpCmdAreaScale::SpCmdAreaScale(QPoint s0, QPoint s1, QPoint scale) :
  SpCmdArea(s0,s1),
  mScale(scale)
  {

  }


void SpCmdAreaScale::paint(SpImage &im)
  {
  if( mVisible )
    im.editScale( mSelect0, mSelect1, mScale );
  }
