#ifndef SPMODEPOINT_H
#define SPMODEPOINT_H

#include "SpMode.h"

class SpModePoint : public SpMode
  {
  public:
    SpModePoint();

    // SpMode interface
  public:
    virtual void paint( SpImage &dest, QPoint p, QColor color ) override;
    virtual bool left() override;
    virtual QString stepDescription() override;
  };

#endif // SPMODEPOINT_H
