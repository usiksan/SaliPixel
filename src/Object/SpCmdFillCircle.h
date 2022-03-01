#ifndef SPCMDFILLCIRCLE_H
#define SPCMDFILLCIRCLE_H

#include "SpCmdCircle.h"

class SpCmdFillCircle : public SpCmdCircle
  {
  public:
    SpCmdFillCircle( QPoint center, QPoint radius, QColor color );

    // SpCmd interface
  public:
    virtual void paint(SpImage &im) override;
  };

#endif // SPCMDFILLCIRCLE_H
