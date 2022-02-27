#ifndef SPMODE_H
#define SPMODE_H

#include <QPainter>

class SpMode
  {
  protected:
    int mStep;
  public:
    SpMode();
    virtual ~SpMode() {}

    virtual void paint( QPainter &dest, QPoint p, QColor color ) = 0;

    virtual bool left() = 0;

    virtual void right() {}
  };

#endif // SPMODE_H
