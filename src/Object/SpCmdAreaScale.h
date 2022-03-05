#ifndef SPCMDAREASCALE_H
#define SPCMDAREASCALE_H

#include "SpCmdArea.h"

#define SP_CMD_AREA_SCALE QStringLiteral("AreaScale")

class SpCmdAreaScale : public SpCmdArea
  {
    QPoint mScale;
  public:
    SpCmdAreaScale() : SpCmdArea() {}
    SpCmdAreaScale( QPoint s0, QPoint s1, QPoint scale );

    // SpCmd interface
  public:
    virtual void    paint(SpImage &im) override;
    virtual QString id() const override { return SP_CMD_AREA_SCALE; }
    virtual void    jsonWrite(SvJsonWriter &js) override;
    virtual void    jsonRead(SvJsonReader &js) override;
  };

#endif // SPCMDAREASCALE_H
