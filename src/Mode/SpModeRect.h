#ifndef SPMODERECT_H
#define SPMODERECT_H

#include "SpModeLine.h"

class SpModeRect : public SpModeLine
  {
  public:
    SpModeRect();

    // SpMode interface
  public:
    virtual void paint(QPainter &dest, QPoint p, QColor color) override;
  };

#endif // SPMODERECT_H
