#ifndef SPCMDAREAROUNDARRAY_H
#define SPCMDAREAROUNDARRAY_H

#include "SpCmdArea.h"

#define SP_CMD_AREA_ROUND_ARRAY QStringLiteral("AreaRoundArray")

class SpCmdAreaRoundArray : public SpCmdArea
  {
    QPoint mCenter;
    QPoint mZero;
    QPoint mAngle;
    int    mItemCount;
    bool   mDoOverride;
  public:
    SpCmdAreaRoundArray() : SpCmdArea() {}
    SpCmdAreaRoundArray( QPoint s0, QPoint s1, QPoint center, QPoint angle, int itemCount, bool doOverride );

    // SpCmd interface
  public:
    virtual void    paint(SpImage &im) override;
    virtual QString id() const override { return SP_CMD_AREA_ROUND_ARRAY; }
    virtual void    jsonWrite(SvJsonWriter &js) override;
    virtual void    jsonRead(SvJsonReader &js) override;
    virtual void    parsePoints(std::function<void (QPoint &)> parser) override;
  };

#endif // SPCMDAREAROUNDARRAY_H
