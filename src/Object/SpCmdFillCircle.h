#ifndef SPCMDFILLCIRCLE_H
#define SPCMDFILLCIRCLE_H

#include "SpCmdCircle.h"

#define SP_CMD_FILL_CIRCLE QStringLiteral("FillCircle")

class SpCmdFillCircle : public SpCmdCircle
  {
  public:
    SpCmdFillCircle() : SpCmdCircle() {}
    SpCmdFillCircle( QPoint center, QPoint radius, QColor color );

    // SpCmd interface
  public:
    virtual void    paint(SpImage &im) override;
    virtual QString id() const override { return SP_CMD_FILL_CIRCLE; }
  };

#endif // SPCMDFILLCIRCLE_H
