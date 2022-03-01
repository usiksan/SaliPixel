#ifndef SPMODECIRCLE_H
#define SPMODECIRCLE_H

#include "SpMode.h"

class SpModeCircle : public SpMode
  {
  protected:
    QPoint mCenter;
  public:
    SpModeCircle();

    // SpMode interface
  public:
    virtual void paint( SpImage &dest, QPoint p, QColor color) override;
    virtual bool left() override;
    virtual void right() override;
    virtual QString stepDescription() override;
  };

#endif // SPMODECIRCLE_H
