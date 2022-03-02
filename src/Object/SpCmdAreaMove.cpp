#include "SpCmdAreaMove.h"

SpCmdAreaMove::SpCmdAreaMove(QPoint s0, QPoint s1, QPoint t, bool doCopy, bool doOverride) :
  SpCmdArea( s0, s1 ),
  mTarget(t),
  mDoCopy(doCopy),
  mDoOverride(doOverride)
  {

  }


void SpCmdAreaMove::paint(SpImage &im)
  {
  if( mVisible )
    im.editMove( mSelect0, mSelect1, mTarget, mDoCopy, mDoOverride );
  }
