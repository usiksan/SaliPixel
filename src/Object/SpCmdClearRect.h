#ifndef SPCMDCLEARRECT_H
#define SPCMDCLEARRECT_H

#include "SpCmd.h"

class SpCmdClearRect : public SpCmd
  {
    QPoint mVertex0;
    QPoint mVertex1;
  public:
    SpCmdClearRect( QPoint v0, QPoint v1 );

    // SpCmd interface
  public:
    virtual void paint(SpImage &im) override;
  };

#endif // SPCMDCLEARRECT_H
