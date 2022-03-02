#ifndef SPMODECLEARRECT_H
#define SPMODECLEARRECT_H

#include "SpMode.h"

class SpModeClearRect : public SpMode
  {
    QPoint mFirst;
  public:
    SpModeClearRect();

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
    virtual SpCmd *object(QPoint p, QColor color) override;
  };

#endif // SPMODECLEARRECT_H
