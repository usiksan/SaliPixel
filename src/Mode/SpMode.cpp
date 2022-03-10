#include "SpMode.h"

SpMode::SpMode( int stepMax ) :
  mStep{0},
  mStepMax{stepMax}
  {

  }



bool SpMode::left(SpCmdPtrList &dest, QPoint p, QColor color)
  {
  if( stepLast() ) {
    SpCmd *ptr = object( p, color );
    if( ptr != nullptr )
      dest.append( ptr );
    }
  Q_UNUSED(dest)
  return stepNext();
  }




void SpMode::right()
  {
  stepPrev();
  }




SpCmd *SpMode::object(QPoint p, QColor color)
  {
  Q_UNUSED(p)
  Q_UNUSED(color)
  return nullptr;
  }




bool SpMode::stepNext()
  {
  if( mStep < mStepMax ) {
    mStep++;
    return false;
    }
  mStep = 0;
  return true;
  }



void SpMode::stepPrev()
  {
  if( mStep )
    mStep--;
  }
