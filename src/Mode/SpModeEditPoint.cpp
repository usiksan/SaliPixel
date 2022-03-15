#include "SpModeEditPoint.h"

#include <QObject>

SpModeEditPoint::SpModeEditPoint() :
  SpMode(1),
  mObjects(nullptr)
  {

  }



void SpModeEditPoint::paint(SpImage &dest, QPoint p, QColor color)
  {
  Q_UNUSED(color)
  if( mStep == 1 ) {
    //Change to current all selected points
    for( auto pointPtr : qAsConst(mSelection) )
      *pointPtr = p;
    //Draw new image
    if( mObjects != nullptr )
      mObjects->paint( dest );
    }
  else
    dest.selectionPoint( p );
  }




bool SpModeEditPoint::left(SpCmdList &dest, QPoint p, QColor color)
  {
  Q_UNUSED(dest)
  Q_UNUSED(color)
  if( mStep == 0 ) {
    mStep = 1;
    //Accumulate selected points
    mSelection.clear();
    mSource = p;
    auto selector = [this] (QPoint &p) {
      if( p == mSource )
        mSelection.append( &p );
      };
    if( mObjects != nullptr )
      mObjects->parsePoints( selector );
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





void SpModeEditPoint::init(SpCmdList &objects, QWidget *parent)
  {
  Q_UNUSED(parent)
  mObjects = &objects;
  }

