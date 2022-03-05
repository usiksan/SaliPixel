#ifndef SPCMDAREARECTARRAY_H
#define SPCMDAREARECTARRAY_H

#include "SpCmdArea.h"

#define SP_CMD_AREA_RECT_ARRAY QStringLiteral("AreaRectArray")

class SpCmdAreaRectArray : public SpCmdArea
  {
    QPoint mDelta;
    int    mRows;
    int    mColumns;
    bool   mDoOverride;
  public:
    SpCmdAreaRectArray() : SpCmdArea() {}
    SpCmdAreaRectArray( QPoint s0, QPoint s1, QPoint p, int rows, int columns, bool doOverride );

    // SpCmd interface
  public:
    virtual void    paint(SpImage &im) override;
    virtual QString id() const override { return SP_CMD_AREA_RECT_ARRAY; }
    virtual void    jsonWrite(SvJsonWriter &js) override;
    virtual void    jsonRead(SvJsonReader &js) override;
    virtual void    parsePoints(std::function<void (QPoint &)> parser) override;
  };

#endif // SPCMDAREARECTARRAY_H
