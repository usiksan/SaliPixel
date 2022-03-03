#ifndef SPMODEAREAROUNDARRAY_H
#define SPMODEAREAROUNDARRAY_H

#include "SpModeArea.h"

class SpModeAreaRoundArray : public SpModeArea
  {
    QPoint mCenter;
    int    mItemCount;
  public:
    SpModeAreaRoundArray(int itemCount);

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
    virtual SpCmd *object(QPoint p, QColor color) override;
  };

#endif // SPMODEAREAROUNDARRAY_H
