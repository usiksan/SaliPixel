#ifndef SPCMDCIRCLE_H
#define SPCMDCIRCLE_H

#include "SpCmd.h"

#define SP_CMD_CIRCLE QStringLiteral("Circle")

class SpCmdCircle : public SpCmd
  {
  protected:
    QPoint mCenter;
    QPoint mRadius;
  public:
    SpCmdCircle() : SpCmd() {}
    SpCmdCircle( QPoint center, QPoint radius, QColor color );

    // SpCmd interface
  public:
    virtual void    paint(SpImage &im) override;
    virtual QString id() const override { return SP_CMD_CIRCLE; }
    virtual void    jsonWrite(SvJsonWriter &js) override;
    virtual void    jsonRead(SvJsonReader &js) override;
  };

#endif // SPCMDCIRCLE_H
