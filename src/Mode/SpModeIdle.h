#ifndef SPMODEIDLE_H
#define SPMODEIDLE_H

#include "SpMode.h"

class SpModeIdle : public SpMode
  {
  public:
    SpModeIdle();

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual bool left(SpCmdPtrList &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
  };

#endif // SPMODEIDLE_H
