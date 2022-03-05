#ifndef SPCMDAREAMOVE_H
#define SPCMDAREAMOVE_H

#include "SpCmdArea.h"

#define SP_CMD_AREA_MOVE QStringLiteral("AreaMove")

class SpCmdAreaMove : public SpCmdArea
  {
    QPoint mTarget;
    bool   mDoCopy;
    bool   mDoOverride;
  public:
    SpCmdAreaMove() : SpCmdArea() {}
    SpCmdAreaMove( QPoint s0, QPoint s1, QPoint t, bool doCopy, bool doOverride );

    // SpCmd interface
  public:
    virtual void    paint(SpImage &im) override;
    virtual QString id() const override { return SP_CMD_AREA_MOVE; }
    virtual void    jsonWrite(SvJsonWriter &js) override;
    virtual void    jsonRead(SvJsonReader &js) override;
  };

#endif // SPCMDAREAMOVE_H
