#ifndef SPCMDPOINT_H
#define SPCMDPOINT_H

#include "SpCmd.h"

#define SP_CMD_POINT QStringLiteral("Point")

class SpCmdPoint : public SpCmd
  {
  protected:
    QPoint mPoint;
  public:
    SpCmdPoint();
    SpCmdPoint( QPoint p, QColor color ) : SpCmd{color}, mPoint{p} {}

    // SpCmd interface
  public:
    virtual void    paint(SpImage &im) override;
    virtual QString id() const override { return SP_CMD_POINT; }
    virtual void    jsonWrite(SvJsonWriter &js) override;
    virtual void    jsonRead(SvJsonReader &js) override;
  };

#endif // SPCMDPOINT_H
