#include "SpCmdAreaRectArray.h"

SpCmdAreaRectArray::SpCmdAreaRectArray( QPoint s0, QPoint s1, QPoint p, int rows, int columns, bool doOverride ) :
  SpCmdArea(s0,s1),
  mDelta(s1 - p),
  mRows(rows),
  mColumns(columns),
  mDoOverride(doOverride)
  {

  }


void SpCmdAreaRectArray::paint(SpImage &im)
  {
  if( mVisible ) {
    for( int x = 0; x < mColumns; x++ )
      for( int y = 0; y < mRows; y++ ) {
        if( x != 0 || y != 0 )
          im.editMove( mSelect0, mSelect1, QPoint( mSelect1.x() + mDelta.x() * x, mSelect1.y() + mDelta.y() * y ), true, mDoOverride );
        }
    }
  }
