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
    virtual QString stepDescription() override;
    virtual SpCmd *object(QPoint p, QColor color) override;
  };

#endif // SPMODECIRCLE_H
