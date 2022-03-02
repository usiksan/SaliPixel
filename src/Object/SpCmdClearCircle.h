#ifndef SPCMDCLEARCIRCLE_H
#define SPCMDCLEARCIRCLE_H

#include "SpCmd.h"

class SpCmdClearCircle : public SpCmd
  {
    QPoint mCenter;
    QPoint mPoint;
  public:
    SpCmdClearCircle( QPoint center, QPoint p );

    // SpCmd interface
  public:
    virtual void paint(SpImage &im) override;
  };

#endif // SPCMDCLEARCIRCLE_H
