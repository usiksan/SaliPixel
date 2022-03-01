#ifndef SPCMDPOINT_H
#define SPCMDPOINT_H

#include "SpCmd.h"

class SpCmdPoint : public SpCmd
  {
    QPoint mPoint;
  public:
    SpCmdPoint();
    SpCmdPoint( QPoint p, QColor color ) : SpCmd{color}, mPoint{p} {}

    // SpCmd interface
  public:
    virtual void paint(SpImage &im) override;
  };

#endif // SPCMDPOINT_H
