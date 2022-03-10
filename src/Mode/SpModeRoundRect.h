#ifndef SPMODEROUNDRECT_H
#define SPMODEROUNDRECT_H

#include "SpMode.h"

class SpModeRoundRect : public SpMode
  {
    QPoint mFirst;
    QPoint mSecond;
  public:
    SpModeRoundRect();

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual bool left(SpCmdPtrList &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
  };

#endif // SPMODEROUNDRECT_H
