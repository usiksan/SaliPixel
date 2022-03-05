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



void SpCmdFill::jsonWrite(SvJsonWriter &js)
  {
  SpCmd::jsonWrite( js );
  js.jsonPoint( "source", mSource );
  }



void SpCmdFill::jsonRead(SvJsonReader &js)
  {
  SpCmd::jsonRead( js );
  js.jsonPoint( "source", mSource );
  }
