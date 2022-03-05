#ifndef SPCMDAREAROTATE_H
#define SPCMDAREAROTATE_H

#include "SpCmdArea.h"

#define SP_CMD_AREA_ROTATE QStringLiteral("AreaRotate")

class SpCmdAreaRotate : public SpCmdArea
  {
    QPoint mCenter;
    QPoint mAngle;
    bool   mDoCopy;
    bool   mDoOverride;
  public:
    SpCmdAreaRotate() : SpCmdArea() {}
    SpCmdAreaRotate( QPoint s0, QPoint s1, QPoint center, QPoint angle, bool doCopy, bool doOverride );

    // SpCmd interface
  public:
    virtual void    paint(SpImage &im) override;
    virtual QString id() const override { return SP_CMD_AREA_ROTATE; }
    virtual void    jsonWrite(SvJsonWriter &js) override;
    virtual void    jsonRead(SvJsonReader &js) override;
  };

#endif // SPCMDAREAROTATE_H
