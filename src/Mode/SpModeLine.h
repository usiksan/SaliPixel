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
    virtual void paint(QPainter &dest, QPoint p, QColor color) override;
    virtual bool left() override;
    virtual void right() override;
  };

#endif // SPMODELINE_H
