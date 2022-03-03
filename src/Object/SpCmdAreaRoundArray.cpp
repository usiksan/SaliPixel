#include "SpCmdAreaRoundArray.h"


SpCmdAreaRoundArray::SpCmdAreaRoundArray(QPoint s0, QPoint s1, QPoint center, QPoint angle, int itemCount, bool doOverride) :
  SpCmdArea(s0,s1),
  mCenter(center),
  mAngle(angle),
  mItemCount(itemCount),
  mDoOverride(doOverride)
  {
  QRect r(s0,s1);
  mZero = r.center();
  }


void SpCmdAreaRoundArray::paint(SpImage &im)
  {
  if( mVisible ) {
    for( int i = 1; i < mItemCount; i++ ) {
      QPoint t = SpImage::rotate( mCenter, mZero, mAngle, i );
      im.editRotate( mSelect0, mSelect1, mCenter, t, true, mDoOverride );
      }
    }
  }
