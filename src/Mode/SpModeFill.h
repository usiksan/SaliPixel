#ifndef SPMODEFILL_H
#define SPMODEFILL_H

#include "SpMode.h"

class SpModeFill : public SpMode
  {
  public:
    SpModeFill();

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual bool left() override;
    virtual QString stepDescription() override;
  };

#endif // SPMODEFILL_H
