#include "SpMode.h"

SpMode::SpMode( int stepMax ) :
  mStep{0},
  mStepMax{stepMax}
  {

  }



bool SpMode::left(SpCmdList &dest, QPoint p, QColor color)
  {
  if( stepLast() ) {
    SpCmd *ptr = object( p, color );
    if( ptr != nullptr )
      dest.append( ptr );
    }
  return stepNext();
  }




void SpMode::right()
  {
  stepPrev();
  }



void SpMode::init(SpCmdList &objects, QWidget *parent)
  {
  Q_UNUSED(objects)
  Q_UNUSED(parent)
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
