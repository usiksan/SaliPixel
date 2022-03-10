#ifndef SPMODEPARALLELOGRAMM_H
#define SPMODEPARALLELOGRAMM_H

#include "SpMode.h"

class SpModeParallelogramm : public SpMode
  {
    QPoint mFirst;
    QPoint mSecond;
  public:
    SpModeParallelogramm();

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual bool left(SpCmdPtrList &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
  };

#endif // SPMODEPARALLELOGRAMM_H
