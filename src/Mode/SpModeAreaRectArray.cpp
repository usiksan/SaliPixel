#include "SpModeAreaRectArray.h"
#include "Object/SpCmdAreaRectArray.h"

#include <QObject>

SpModeAreaRectArray::SpModeAreaRectArray(int row, int column) :
  SpModeArea(2),
  mRowCount(row),
  mColumnCount(column)
  {

  }


void SpModeAreaRectArray::paint(SpImage &dest, QPoint p, QColor color)
  {
  if( mStep == 2 ) {
    int dx = p.x() - mSecond.x();
    int dy = p.y() - mSecond.y();
    for( int x = 0; x < mColumnCount; x++ )
      for( int y = 0; y < mRowCount; y++ ) {
        if( x != 0 || y != 0 )
          dest.editMove( mFirst, mSecond, QPoint( mSecond.x() + dx * x, mSecond.y() + dy * y ), true, mDoOverride );
        }
    }
  else SpModeArea::paint( dest, p, color );
  }


QString SpModeAreaRectArray::stepDescription()
  {
  if( mStep == 2 )
    return QObject::tr("Enter cell array distance");
  return SpModeArea::stepDescription();
  }



SpCmd *SpModeAreaRectArray::object(QPoint p, QColor color)
  {
  Q_UNUSED(color)
  return new SpCmdAreaRectArray( mFirst, mSecond, p, mRowCount, mColumnCount, mDoOverride );
  }
