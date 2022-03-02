#ifndef SPCMDAREAROTATE_H
#define SPCMDAREAROTATE_H

#include "SpCmdArea.h"

class SpCmdAreaRotate : public SpCmdArea
  {
    QPoint mCenter;
    QPoint mAngle;
    bool   mDoCopy;
    bool   mDoOverride;
  public:
    SpCmdAreaRotate( QPoint s0, QPoint s1, QPoint center, QPoint angle, bool doCopy, bool doOverride );

    // SpCmd interface
  public:
    virtual void paint(SpImage &im) override;
  };

#endif // SPCMDAREAROTATE_H
