#include "SpModeAreaScale.h"
#include "Object/SpCmdAreaScale.h"

#include <QObject>

SpModeAreaScale::SpModeAreaScale() :
  SpModeArea(2)
  {

  }


void SpModeAreaScale::paint(SpImage &dest, QPoint p, QColor color)
  {
  if( mStep == 2 )
    dest.editScale( mFirst, mSecond, p );
  else
    SpModeArea::paint( dest, p, color );
  }


QString SpModeAreaScale::stepDescription()
  {
  if( mStep == 2 )
    return QObject::tr("Enter scale point");
  return SpModeArea::stepDescription();
  }




SpCmd *SpModeAreaScale::object(QPoint p, QColor color)
  {
  Q_UNUSED(color)
  return new SpCmdAreaScale( mFirst, mSecond, p );
  }
