#include "SpMode.h"

SpMode::SpMode( int stepMax ) :
  mStep{0},
  mStepMax{stepMax}
  {

  }

bool SpMode::left()
  {
  if( mStep < mStepMax ) {
    mStep++;
    return false;
    }
  mStep = 0;
  return true;
  }

void SpMode::right()
  {
  if( mStep )
    mStep--;
  }
