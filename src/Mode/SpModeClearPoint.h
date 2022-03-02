#ifndef SPMODECLEARPOINT_H
#define SPMODECLEARPOINT_H

#include "SpMode.h"

class SpModeClearPoint : public SpMode
  {
  public:
    SpModeClearPoint();

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
    virtual SpCmd *object(QPoint p, QColor color) override;
  };

#endif // SPMODECLEARPOINT_H
