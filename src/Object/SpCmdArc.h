#ifndef SPCMDARC_H
#define SPCMDARC_H

#include "SpCmd.h"

class SpCmdArc : public SpCmd
  {
    QPoint mCenter;
    QPoint mStart;
    QPoint mStop;
  public:
    SpCmdArc( QPoint center, QPoint start, QPoint stop, QColor color );

    // SpCmd interface
  public:
    virtual void paint(SpImage &im) override;
  };

#endif // SPCMDARC_H
