#include "SpModeAreaRoundArray.h"
#include "Object/SpCmdAreaRoundArray.h"

#include <QObject>

SpModeAreaRoundArray::SpModeAreaRoundArray(int itemCount) :
  SpModeArea(3),
  mItemCount(itemCount)
  {

  }


void SpModeAreaRoundArray::paint(SpImage &dest, QPoint p, QColor color)
  {
  if( mStep == 3 ) {
    QRect r(mFirst,mSecond);
    QPoint zero( r.center() );
    for( int i = 1; i < mItemCount; i++ ) {
      QPoint t = SpImage::rotate( mCenter, zero, p, i );
      dest.editRotate( mFirst, mSecond, mCenter, t, true, mDoOverride );
      }
    }
  else if( mStep == 2 ) {
    mCenter = p;
    dest.selectionRect( mFirst, mSecond );
    dest.selectionPoint( mCenter );
    }
  else SpModeArea::paint( dest, p, color );
  }


QString SpModeAreaRoundArray::stepDescription()
  {
  if( mStep == 2 )
    return QObject::tr("Enter center point of round array");
  if( mStep == 3 )
    return QObject::tr("Enter angle beatween array items");
  return SpModeArea::stepDescription();
  }



SpCmd *SpModeAreaRoundArray::object(QPoint p, QColor color)
  {
  Q_UNUSED(color)
  return new SpCmdAreaRoundArray( mFirst, mSecond, mCenter, p, mItemCount, mDoOverride );
  }
