#include "SpModeAreaRotate.h"
#include "Object/SpCmdAreaRotate.h"

#include <QObject>

SpModeAreaRotate::SpModeAreaRotate() :
  SpModeArea(3)
  {

  }



void SpModeAreaRotate::paint(SpImage &dest, QPoint p, QColor color)
  {
  if( mStep == 2 ) {
    mCenter = p;
    dest.selectionRect( mFirst, mSecond );
    dest.selectionPoint( mCenter );
    }
  else if( mStep == 3 ) {
    dest.editRotate( mFirst, mSecond, mCenter, p, mDoCopy, mDoOverride );
    }
  else SpModeArea::paint( dest, p, color );
  }



QString SpModeAreaRotate::stepDescription()
  {
  if( mStep == 2 )
    return QObject::tr("Enter center point of rotation");
  if( mStep == 3 )
    return QObject::tr("Enter angle of rotation");
  return SpModeArea::stepDescription();
  }





SpCmd *SpModeAreaRotate::object(QPoint p, QColor color)
  {
  Q_UNUSED(color)
  return new SpCmdAreaRotate( mFirst, mSecond, mCenter, p, mDoCopy, mDoOverride );
  }




bool SpModeAreaRotate::left(SpCmdList &dest, QPoint p, QColor color)
  {
  if( stepLast() && mDoCopy ) {
    dest.append( object( p, color ) );
    return true;
    }
  return SpModeArea::left( dest, p, color );
  }
