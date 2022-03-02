#ifndef SPMODEAREA_H
#define SPMODEAREA_H

#include "SpMode.h"

class SpModeArea : public SpMode
  {
  protected:
    QPoint mFirst;
    QPoint mSecond;
  public:
    SpModeArea( int maxStep );

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
  };

#endif // SPMODEAREA_H
