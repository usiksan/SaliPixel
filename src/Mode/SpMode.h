#ifndef SPMODE_H
#define SPMODE_H

#include "SpImage.h"

class SpCmd;

class SpMode
  {
  protected:
    int mStep;
    int mStepMax;
  public:
    SpMode( int stepMax );
    virtual ~SpMode() {}

    virtual bool    showPoints() const { return false; }

    virtual void    paint( SpImage &dest, QPoint p, QColor color ) = 0;

    virtual bool    left();

    virtual void    right();

    virtual QString stepDescription() = 0;

    virtual SpCmd  *object( QPoint p, QColor color ) { Q_UNUSED(p) Q_UNUSED(color) return nullptr; }

    void            reset() { mStep = 0; }
  };

#endif // SPMODE_H
