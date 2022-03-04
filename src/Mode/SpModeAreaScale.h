#ifndef SPMODEAREASCALE_H
#define SPMODEAREASCALE_H

#include "SpModeArea.h"

class SpModeAreaScale : public SpModeArea
  {
  public:
    SpModeAreaScale();

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
    virtual SpCmd *object(QPoint p, QColor color) override;
  };

#endif // SPMODEAREASCALE_H
