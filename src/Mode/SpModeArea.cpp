#include "SpModeArea.h"

#include <QObject>

bool SpModeArea::mDoCopy;
bool SpModeArea::mDoOverride;

SpModeArea::SpModeArea(int maxStep) :
  SpMode(maxStep)
  {

  }



void SpModeArea::paint(SpImage &dest, QPoint p, QColor color)
  {
  Q_UNUSED(color)
  if( mStep == 0 ) {
    mFirst = p;
    dest.selectionPoint( p );
    }
  else if( mStep == 1 ) {
    mSecond = p;
    dest.selectionRect( mFirst, mSecond );
    }
  }




QString SpModeArea::stepDescription()
  {
  if( mStep == 0 )
    return QObject::tr("Enter first corner of selection");
  return QObject::tr("Enter second corner of selection");
  }
