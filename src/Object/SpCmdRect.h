#ifndef SPCMDRECT_H
#define SPCMDRECT_H

#include "SpCmd.h"

class SpCmdRect : public SpCmd
  {
  protected:
    QPoint mFirst;
    QPoint mSecond;
  public:
    SpCmdRect();
    SpCmdRect( QPoint f, QPoint s, QColor color ) : SpCmd{color}, mFirst{f}, mSecond{s} {}


    // SpCmd interface
  public:
    virtual void paint(SpImage &im) override;
  };

#endif // SPCMDRECT_H
