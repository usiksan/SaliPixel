#ifndef SPMODEAREAMOVE_H
#define SPMODEAREAMOVE_H

#include "SpModeArea.h"

class SpModeAreaMove : public SpModeArea
  {
    bool mDoCopy;
    bool mDoOverride;
  public:
    SpModeAreaMove( bool doCopy, bool doOverride );

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
    virtual SpCmd *object(QPoint p, QColor color) override;
  };

#endif // SPMODEAREAMOVE_H
