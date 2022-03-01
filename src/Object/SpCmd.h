#ifndef SPCMD_H
#define SPCMD_H

#include "Mode/SpImage.h"

class SpCmd
  {
  protected:
    bool   mVisible;
    QColor mColor;
  public:
    SpCmd();
    SpCmd( QColor color ) : mVisible{true}, mColor{color} {}
    virtual ~SpCmd() {}

    void setColor( QColor color ) { mColor = color; }

    virtual void paint( SpImage &im ) { Q_UNUSED(im); }
  };

using SpCmdPtr = SpCmd*;

#endif // SPCMD_H
