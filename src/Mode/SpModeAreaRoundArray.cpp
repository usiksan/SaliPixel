#include "SpModeAreaRoundArray.h"
#include "Object/SpCmdAreaRoundArray.h"

#include <QObject>
#include <QInputDialog>

SpModeAreaRoundArray::SpModeAreaRoundArray() :
  SpModeArea(3),
  mItemCount(2)
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



void SpModeAreaRoundArray::init(SpCmdList &objects, QWidget *parent)
  {
  Q_UNUSED(objects)
  bool ok = true;
  int items = QInputDialog::getInt( parent, QObject::tr("Enter round item count"), QObject::tr("Round item count:"), 2, 1, 100, 1, &ok );
  if( ok )
    mItemCount = items;
  else
    mItemCount = 2;
  }



SpCmd *SpModeAreaRoundArray::object(QPoint p, QColor color)
  {
  Q_UNUSED(color)
  return new SpCmdAreaRoundArray( mFirst, mSecond, mCenter, p, mItemCount, mDoOverride );
  }


