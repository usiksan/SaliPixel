#ifndef SPCMDAREAROUNDARRAY_H
#define SPCMDAREAROUNDARRAY_H

#include "SpCmdArea.h"

class SpCmdAreaRoundArray : public SpCmdArea
  {
    QPoint mCenter;
    QPoint mZero;
    QPoint mAngle;
    int    mItemCount;
    bool   mDoOverride;
  public:
    SpCmdAreaRoundArray( QPoint s0, QPoint s1, QPoint center, QPoint angle, int itemCount, bool doOverride );

    // SpCmd interface
  public:
    virtual void paint(SpImage &im) override;
  };

#endif // SPCMDAREAROUNDARRAY_H
