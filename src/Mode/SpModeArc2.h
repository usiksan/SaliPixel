#ifndef SPMODEARC2_H
#define SPMODEARC2_H

#include "SpMode.h"

class SpModeArc2 : public SpMode
  {
    QPoint mCenter;
    QPoint mStart;
    QPoint mStop;
  public:
    SpModeArc2();

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
    virtual SpCmd *object(QPoint p, QColor color) override;
  };

#endif // SPMODEARC2_H
