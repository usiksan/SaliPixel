#ifndef SPCMDAREAMOVE_H
#define SPCMDAREAMOVE_H

#include "SpCmdArea.h"

class SpCmdAreaMove : public SpCmdArea
  {
    QPoint mTarget;
    bool   mDoCopy;
    bool   mDoOverride;
  public:
    SpCmdAreaMove( QPoint s0, QPoint s1, QPoint t, bool doCopy, bool doOverride );

    // SpCmd interface
  public:
    virtual void paint(SpImage &im) override;
  };

#endif // SPCMDAREAMOVE_H
