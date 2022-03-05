#include "SpModeEditPoint.h"

#include <QObject>

SpModeEditPoint::SpModeEditPoint(SpCmdPtrList &objs) :
  SpMode(1),
  mObjects(objs)
  {

  }



void SpModeEditPoint::paint(SpImage &dest, QPoint p, QColor color)
  {
  Q_UNUSED(color)
  if( mStep == 1 ) {
    dest.clear();
    //Change to current all selected points
    for( auto pointPtr : qAsConst(mSelection) )
      *pointPtr = p;
    //Draw new image
    for( auto ptr : qAsConst(mObjects) )
      ptr->paint( dest );
    }
  else {
    mSource = p;
    dest.selectionPoint( p );
    }
  }


bool SpModeEditPoint::left()
  {
  if( mStep == 0 ) {
    mStep = 1;
    //Accumulate selected points
    mSelection.clear();
    auto selector = [this] (QPoint &p) {
      if( p == mSource )
        mSelection.append( &p );
      };
    for( auto ptr : qAsConst(mObjects) )
      ptr->parsePoints( selector );
    return false;
    }
  mStep = 0;
  return true;
  }



void SpModeEditPoint::right()
  {
  if( mStep == 1 ) {
    for( auto pointPtr : qAsConst(mSelection) )
      *pointPtr = mSource;
    mStep = 0;
    }
  }



QString SpModeEditPoint::stepDescription()
  {
  if( mStep == 0 )
    return QObject::tr("Select point to move");
  return QObject::tr("Move selected point");
  }




