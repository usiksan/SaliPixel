#ifndef SPCMDAREASCALE_H
#define SPCMDAREASCALE_H

#include "SpCmdArea.h"

class SpCmdAreaScale : public SpCmdArea
  {
    QPoint mScale;
  public:
    SpCmdAreaScale( QPoint s0, QPoint s1, QPoint scale );

    // SpCmd interface
  public:
    virtual void paint(SpImage &im) override;
  };

#endif // SPCMDAREASCALE_H
