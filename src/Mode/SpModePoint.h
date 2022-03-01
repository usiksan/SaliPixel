#ifndef SPMODEPOINT_H
#define SPMODEPOINT_H

#include "SpMode.h"

class SpModePoint : public SpMode
  {
  public:
    SpModePoint();

    // SpMode interface
  public:
    virtual void paint( SpImage &dest, QPoint p, QColor color ) override;
    virtual QString stepDescription() override;
    virtual SpCmd *object(QPoint p, QColor color) override;
  };

#endif // SPMODEPOINT_H
