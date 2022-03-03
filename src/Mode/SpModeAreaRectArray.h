#ifndef SPMODEAREARECTARRAY_H
#define SPMODEAREARECTARRAY_H

#include "SpModeArea.h"

class SpModeAreaRectArray : public SpModeArea
  {
    int mRowCount;
    int mColumnCount;
  public:
    SpModeAreaRectArray( int row, int column );

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
    virtual SpCmd *object(QPoint p, QColor color) override;
  };

#endif // SPMODEAREARECTARRAY_H
