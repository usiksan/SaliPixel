#ifndef SPMODELINE_H
#define SPMODELINE_H

#include "SpMode.h"

class SpModeLine : public SpMode
  {
  protected:
    QPoint mFirst;
  public:
    SpModeLine();

    // SpMode interface
  public:
    virtual void paint( SpImage &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
    virtual SpCmd *object(QPoint p, QColor color) override;
  };

#endif // SPMODELINE_H
