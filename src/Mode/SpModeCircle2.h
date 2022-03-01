#ifndef SPMODECIRCLE2_H
#define SPMODECIRCLE2_H

#include "SpModeCircle.h"

class SpModeCircle2 : public SpMode
  {
    QPoint mFirst;
  public:
    SpModeCircle2();

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual bool left() override;
    virtual QString stepDescription() override;

  };

#endif // SPMODECIRCLE2_H
