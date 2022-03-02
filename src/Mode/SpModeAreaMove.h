#ifndef SPMODEAREAMOVE_H
#define SPMODEAREAMOVE_H

#include "SpModeArea.h"

class SpModeAreaMove : public SpModeArea
  {
  public:
    SpModeAreaMove();

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
    virtual SpCmd *object(QPoint p, QColor color) override;
  };

#endif // SPMODEAREAMOVE_H
