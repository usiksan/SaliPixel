#ifndef SPMODEPOINT_H
#define SPMODEPOINT_H

#include "SpMode.h"

class SpModePoint : public SpMode
  {
  public:
    SpModePoint();

    // SpMode interface
  public:
    virtual void paint(QPainter &dest, QPoint p, QColor color ) override;
    virtual bool left() override;
  };

#endif // SPMODEPOINT_H
