#ifndef SPCMDARC_H
#define SPCMDARC_H

#include "SpCmd.h"

#define SP_CMD_ARC QStringLiteral("Arc")

class SpCmdArc : public SpCmd
  {
    QPoint mCenter;
    QPoint mStart;
    QPoint mStop;
  public:
    SpCmdArc() : SpCmd() {}
    SpCmdArc( QPoint center, QPoint start, QPoint stop, QColor color );

    // SpCmd interface
  public:
    virtual void    paint(SpImage &im) override;
    virtual QString id() const override { return SP_CMD_ARC; }
    virtual void    jsonWrite(SvJsonWriter &js) override;
    virtual void    jsonRead(SvJsonReader &js) override;
    virtual void    parsePoints(std::function<void (QPoint&)> parser) override;
  };

#endif // SPCMDARC_H
