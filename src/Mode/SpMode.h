#ifndef SPMODE_H
#define SPMODE_H

#include "SpImage.h"

class SpMode
  {
  protected:
    int mStep;
  public:
    SpMode();
    virtual ~SpMode() {}

    virtual void    paint( SpImage &dest, QPoint p, QColor color ) = 0;

    virtual bool    left() = 0;

    virtual void    right() {}

    virtual QString stepDescription() = 0;
  };

#endif // SPMODE_H
