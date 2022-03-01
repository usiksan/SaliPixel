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
    virtual bool left() override;
    virtual void right() override;
    virtual QString stepDescription() override;
  };

#endif // SPMODEARC_H
