#ifndef SPMODECLEARCIRCLE_H
#define SPMODECLEARCIRCLE_H

#include "SpMode.h"

class SpModeClearCircle : public SpMode
  {
    QPoint mCenter;
  public:
    SpModeClearCircle();

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
    virtual SpCmd *object(QPoint p, QColor color) override;
  };

#endif // SPMODECLEARCIRCLE_H
