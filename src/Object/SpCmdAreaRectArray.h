#ifndef SPCMDAREARECTARRAY_H
#define SPCMDAREARECTARRAY_H

#include "SpCmdArea.h"

class SpCmdAreaRectArray : public SpCmdArea
  {
    QPoint mDelta;
    int    mRows;
    int    mColumns;
    bool   mDoOverride;
  public:
    SpCmdAreaRectArray( QPoint s0, QPoint s1, QPoint p, int rows, int columns, bool doOverride );

    // SpCmd interface
  public:
    virtual void paint(SpImage &im) override;
  };

#endif // SPCMDAREARECTARRAY_H
