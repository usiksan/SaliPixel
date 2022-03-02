#ifndef SPCMDCLEARPOINT_H
#define SPCMDCLEARPOINT_H

#include "SpCmd.h"

class SpCmdClearPoint : public SpCmd
  {
    QPoint mPoint;
  public:
    SpCmdClearPoint( QPoint p );

    // SpCmd interface
  public:
    virtual void paint(SpImage &im) override;
  };

#endif // SPCMDCLEARPOINT_H
