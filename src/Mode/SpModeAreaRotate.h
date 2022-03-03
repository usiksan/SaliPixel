#ifndef SPMODEAREAROTATE_H
#define SPMODEAREAROTATE_H

#include "SpModeArea.h"

class SpModeAreaRotate : public SpModeArea
  {
    QPoint mCenter;
  public:
    SpModeAreaRotate();

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
    virtual SpCmd *object(QPoint p, QColor color) override;
    virtual bool left() override;
  };

#endif // SPMODEAREAROTATE_H
