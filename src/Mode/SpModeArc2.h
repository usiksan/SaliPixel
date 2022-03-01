#ifndef SPMODEARC2_H
#define SPMODEARC2_H

#include "SpMode.h"

class SpModeArc2 : public SpMode
  {
    QPoint mStart;
    QPoint mStop;
  public:
    SpModeArc2();

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual bool left() override;
    virtual void right() override;
    virtual QString stepDescription() override;

  };

#endif // SPMODEARC2_H
