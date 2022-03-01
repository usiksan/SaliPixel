#include "SpCmdFill.h"

SpCmdFill::SpCmdFill(QPoint source, QColor color) :
  SpCmd{color},
  mSource{source}
  {

  }


void SpCmdFill::paint(SpImage &im)
  {
  if( mVisible )
    im.drawFill( mSource, mColor );
  }
