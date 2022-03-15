#include "SpModeAreaRectArray.h"
#include "Object/SpCmdAreaRectArray.h"
#include "Win/SpDlgNew.h"

#include <QObject>

SpModeAreaRectArray::SpModeAreaRectArray() :
  SpModeArea(2),
  mRowCount(2),
  mColumnCount(2)
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



void SpModeAreaRectArray::init(SpCmdList &objects, QWidget *parent)
  {
  Q_UNUSED(objects)
  SpDlgNew dlgDim(parent);
  dlgDim.setup( QObject::tr("Enter array dimesions"), QObject::tr("Column count:"), QObject::tr("Row count:"), 2, 2 );
  if( dlgDim.exec() ) {
    mColumnCount = qBound( 1, dlgDim.valueWidth(), 32);
    mRowCount    = qBound( 1, dlgDim.valueHeight(), 32 );
    }
  }





SpCmd *SpModeAreaRectArray::object(QPoint p, QColor color)
  {
  Q_UNUSED(color)
  return new SpCmdAreaRectArray( mFirst, mSecond, p, mRowCount, mColumnCount, mDoOverride );
  }

