#ifndef SPCMDFILLRECT_H
#define SPCMDFILLRECT_H

#include "SpCmdRect.h"

class SpCmdFillRect : public SpCmdRect
  {
  public:
    SpCmdFillRect( QPoint f, QPoint s, QColor color );

    // SpCmd interface
  public:
    virtual void paint(SpImage &im) override;
  };

#endif // SPCMDFILLRECT_H
