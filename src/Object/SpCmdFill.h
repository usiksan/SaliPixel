#ifndef SPCMDFILL_H
#define SPCMDFILL_H

#include "SpCmd.h"

class SpCmdFill : public SpCmd
  {
    QPoint mSource;
  public:
    SpCmdFill( QPoint source, QColor color );

    // SpCmd interface
  public:
    virtual void paint(SpImage &im) override;
  };

#endif // SPCMDFILL_H
