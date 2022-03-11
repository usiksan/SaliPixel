#include "SpModeAreaMove.h"
#include "Object/SpCmdAreaMove.h"

#include <QObject>

SpModeAreaMove::SpModeAreaMove() :
  SpModeArea(2)
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


QString SpModeAreaMove::iconName() const
  {
  return QStringLiteral("editMove.png");
  }


QString SpModeAreaMove::menuName() const
  {
  return QObject::tr("Move");
  }




SpCmd *SpModeAreaMove::object(QPoint p, QColor color)
  {
  Q_UNUSED(color)
  return new SpCmdAreaMove( mFirst, mSecond, p, mDoCopy, mDoOverride );
  }
