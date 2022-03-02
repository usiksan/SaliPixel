#include "SpModeAreaMove.h"
#include "Object/SpCmdAreaMove.h"

#include <QObject>

SpModeAreaMove::SpModeAreaMove(bool doCopy, bool doOverride) :
  SpModeArea(2),
  mDoCopy(doCopy),
  mDoOverride(doOverride)
  {

  }


void SpModeAreaMove::paint(SpImage &dest, QPoint p, QColor color)
  {
  if( mStep == 2 ) {
    dest.editMove( mFirst, mSecond, p, mDoCopy, mDoOverride );
    }
  else SpModeArea::paint( dest, p, color );
  }


QString SpModeAreaMove::stepDescription()
  {
  if( mStep == 2 )
    return QObject::tr("Enter new position of fragment");
  return SpModeArea::stepDescription();
  }



SpCmd *SpModeAreaMove::object(QPoint p, QColor color)
  {
  Q_UNUSED(color)
  return new SpCmdAreaMove( mFirst, mSecond, p, mDoCopy, mDoOverride );
  }
