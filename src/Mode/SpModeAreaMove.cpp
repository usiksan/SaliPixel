#include "SpModeAreaMove.h"

#include <QObject>

SpModeAreaMove::SpModeAreaMove() :
  SpModeArea(2)
  {

  }


void SpModeAreaMove::paint(SpImage &dest, QPoint p, QColor color)
  {
  if( mStep == 2 ) {
    dest.editMove( mFirst, mSecond, p, true, true );
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
  return nullptr;
  }
