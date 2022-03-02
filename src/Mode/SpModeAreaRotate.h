#ifndef SPMODEAREAROTATE_H
#define SPMODEAREAROTATE_H

#include "SpModeArea.h"

class SpModeAreaRotate : public SpModeArea
  {
    QPoint mCenter;
    bool   mDoCopy;
    bool   mDoOverride;
  public:
    SpModeAreaRotate( bool doCopy, bool doOverride );

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
    virtual SpCmd *object(QPoint p, QColor color) override;
    virtual bool left() override;
  };

#endif // SPMODEAREAROTATE_H
