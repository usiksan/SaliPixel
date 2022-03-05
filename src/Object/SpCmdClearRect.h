#ifndef SPCMDCLEARRECT_H
#define SPCMDCLEARRECT_H

#include "SpCmdRect.h"

#define SP_CMD_CLEAR_RECT QStringLiteral("ClearRect")

class SpCmdClearRect : public SpCmdRect
  {
  public:
    SpCmdClearRect() : SpCmdRect() {}
    SpCmdClearRect( QPoint v0, QPoint v1 );

    // SpCmd interface
  public:
    virtual void    paint(SpImage &im) override;
    virtual QString id() const override { return SP_CMD_CLEAR_RECT; }
  };

#endif // SPCMDCLEARRECT_H
