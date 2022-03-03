#ifndef SPMODEAREAMIRROR_H
#define SPMODEAREAMIRROR_H

#include "SpModeArea.h"

class SpModeAreaMirror : public SpModeArea
  {
    QPoint mMirrorLine;
  public:
    SpModeAreaMirror();

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
    virtual SpCmd *object(QPoint p, QColor color) override;
  };

#endif // SPMODEAREAMIRROR_H
