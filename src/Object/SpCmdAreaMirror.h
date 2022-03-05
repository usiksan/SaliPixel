#ifndef SPCMDAREAMIRROR_H
#define SPCMDAREAMIRROR_H

#include "SpCmdArea.h"

#define SP_CMD_AREA_MIRROR QStringLiteral("AreaMirror")

class SpCmdAreaMirror : public SpCmdArea
  {
    QPoint mMirrorLine0;
    QPoint mMirrorLine1;
    bool   mDoCopy;
    bool   mDoOverride;
  public:
    SpCmdAreaMirror() : SpCmdArea() {}
    SpCmdAreaMirror( QPoint s0, QPoint s1, QPoint line0, QPoint line1, bool doCopy, bool doOverride );

    // SpCmd interface
  public:
    virtual void    paint(SpImage &im) override;
    virtual QString id() const override { return SP_CMD_AREA_MIRROR; }
    virtual void    jsonWrite(SvJsonWriter &js) override;
    virtual void    jsonRead(SvJsonReader &js) override;
    virtual void    parsePoints(std::function<void (QPoint &)> parser) override;
  };

#endif // SPCMDAREAMIRROR_H
