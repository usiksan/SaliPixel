#ifndef SPMODEFILLRECT_H
#define SPMODEFILLRECT_H

#include "SpModeRect.h"

class SpModeFillRect : public SpModeRect
  {
  public:
    SpModeFillRect();

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
  };

#endif // SPMODEFILLRECT_H
