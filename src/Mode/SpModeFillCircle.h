#ifndef SPMODEFILLCIRCLE_H
#define SPMODEFILLCIRCLE_H

#include "SpModeCircle.h"

class SpModeFillCircle : public SpModeCircle
  {
  public:
    SpModeFillCircle();

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
  };

#endif // SPMODEFILLCIRCLE_H
