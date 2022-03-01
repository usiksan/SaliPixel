#ifndef SPCMDLINE_H
#define SPCMDLINE_H

#include "SpCmd.h"

class SpCmdLine : public SpCmd
  {
    QPoint mStart;
    QPoint mStop;
  public:
    SpCmdLine();
    SpCmdLine( QPoint ps, QPoint pe, QColor color ) : SpCmd{color}, mStart{ps}, mStop{pe} {}

    // SpCmd interface
  public:
    virtual void paint(SpImage &im) override;
  };

#endif // SPCMDLINE_H
