#ifndef SPCMDAREAMIRROR_H
#define SPCMDAREAMIRROR_H

#include "SpCmdArea.h"

class SpCmdAreaMirror : public SpCmdArea
  {
    QPoint mMirrorLine0;
    QPoint mMirrorLine1;
    bool   mDoCopy;
    bool   mDoOverride;
  public:
    SpCmdAreaMirror( QPoint s0, QPoint s1, QPoint line0, QPoint line1, bool doCopy, bool doOverride );

    // SpCmd interface
  public:
    virtual void paint(SpImage &im) override;
  };

#endif // SPCMDAREAMIRROR_H
