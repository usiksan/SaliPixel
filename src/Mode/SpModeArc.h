#ifndef SPMODEARC_H
#define SPMODEARC_H

#include "SpMode.h"

class SpModeArc : public SpMode
  {
    QPoint mCenter;
    QPoint mStart;
  public:
    SpModeArc();

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
    virtual SpCmd *object(QPoint p, QColor color) override;
  };

#endif // SPMODEARC_H
