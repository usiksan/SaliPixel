#ifndef SPCMDFILLRECT_H
#define SPCMDFILLRECT_H

#include "SpCmdRect.h"

#define SP_CMD_FILL_RECT QStringLiteral("FillRect")

class SpCmdFillRect : public SpCmdRect
  {
  public:
    SpCmdFillRect() : SpCmdRect() {}
    SpCmdFillRect( QPoint f, QPoint s, QColor color );

    // SpCmd interface
  public:
    virtual void    paint(SpImage &im) override;
    virtual QString id() const override { return SP_CMD_FILL_RECT; }
  };

#endif // SPCMDFILLRECT_H
