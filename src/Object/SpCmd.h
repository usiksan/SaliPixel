#ifndef SPCMD_H
#define SPCMD_H

#include "Mode/SpImage.h"
#include "SvLib/SvJsonIO.h"

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

    virtual void    paint( SpImage &im ) { Q_UNUSED(im); }

    virtual QString id() const = 0;

    virtual void    jsonWrite( SvJsonWriter &js );

    virtual void    jsonRead( SvJsonReader &js );

    static SpCmd   *build( SvJsonReader &js );
  };

using SpCmdPtr = SpCmd*;

#endif // SPCMD_H
