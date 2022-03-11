#ifndef SPMODETRIANGLE_H
#define SPMODETRIANGLE_H

#include "SpMode.h"

class SpModeTriangle : public SpMode
  {
    QPoint mFirst;
    QPoint mSecond;
  public:
    SpModeTriangle();

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual bool left(SpCmdList &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
  };

#endif // SPMODETRIANGLE_H
