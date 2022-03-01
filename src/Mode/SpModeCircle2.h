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
    virtual QString stepDescription() override;
    virtual SpCmd *object(QPoint p, QColor color) override;
  };

#endif // SPMODECIRCLE2_H
