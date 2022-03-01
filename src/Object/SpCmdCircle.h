#ifndef SPCMDCIRCLE_H
#define SPCMDCIRCLE_H

#include "SpCmd.h"

class SpCmdCircle : public SpCmd
  {
  protected:
    QPoint mCenter;
    QPoint mRadius;
  public:
    SpCmdCircle( QPoint center, QPoint radius, QColor color );

    // SpCmd interface
  public:
    virtual void paint(SpImage &im) override;
  };

#endif // SPCMDCIRCLE_H
