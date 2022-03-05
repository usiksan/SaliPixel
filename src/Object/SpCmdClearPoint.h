#ifndef SPCMDCLEARPOINT_H
#define SPCMDCLEARPOINT_H

#include "SpCmdPoint.h"

#define SP_CMD_CLEAR_POINT QStringLiteral("ClearPoint")

class SpCmdClearPoint : public SpCmdPoint
  {
  public:
    SpCmdClearPoint() : SpCmdPoint() {}
    SpCmdClearPoint( QPoint p );

    // SpCmd interface
  public:
    virtual void    paint(SpImage &im) override;
    virtual QString id() const override { return SP_CMD_CLEAR_POINT; }
  };

#endif // SPCMDCLEARPOINT_H
