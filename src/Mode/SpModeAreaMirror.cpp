#include "SpModeAreaMirror.h"
#include "Object/SpCmdAreaMirror.h"

#include <QObject>

SpModeAreaMirror::SpModeAreaMirror() :
  SpModeArea(3)
  {

  }


void SpModeAreaMirror::paint(SpImage &dest, QPoint p, QColor color)
  {
  if( mStep == 2 ) {
    mMirrorLine = p;
    dest.selectionRect( mFirst, mSecond );
    dest.selectionPoint( mMirrorLine );
    }
  else if( mStep == 3 ) {
    dest.editMirror( mFirst, mSecond, mMirrorLine, p, mDoCopy, mDoOverride );
    }
  else SpModeArea::paint( dest, p, color );
  }



QString SpModeAreaMirror::stepDescription()
  {
  if( mStep == 2 )
    return QObject::tr("Enter start point of mirror line");
  if( mStep == 3 )
    return QObject::tr("Enter end point of mirror line");
  return SpModeArea::stepDescription();
  }



SpCmd *SpModeAreaMirror::object(QPoint p, QColor color)
  {
  Q_UNUSED(color)
  return new SpCmdAreaMirror( mFirst, mSecond, mMirrorLine, p, mDoCopy, mDoOverride );
  }


