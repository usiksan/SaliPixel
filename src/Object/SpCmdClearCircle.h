#ifndef SPCMDCLEARCIRCLE_H
#define SPCMDCLEARCIRCLE_H

#include "SpCmdCircle.h"

#define SP_CMD_CLEAR_CIRCLE QStringLiteral("ClearCircle")

class SpCmdClearCircle : public SpCmdCircle
  {
  public:
    SpCmdClearCircle() : SpCmdCircle() {}
    SpCmdClearCircle( QPoint center, QPoint p );

    // SpCmd interface
  public:
    virtual void    paint(SpImage &im) override;
    virtual QString id() const override { return SP_CMD_CLEAR_CIRCLE; }
  };

#endif // SPCMDCLEARCIRCLE_H
