#include "SpCmdPoint.h"

SpCmdPoint::SpCmdPoint()
  {

  }


void SpCmdPoint::paint(SpImage &im)
  {
  if( mVisible )
    im.drawPixel( mPoint, mColor );
  }



void SpCmdPoint::jsonWrite(SvJsonWriter &js)
  {
  SpCmd::jsonWrite( js );
  js.jsonPoint( "point", mPoint );
  }




void SpCmdPoint::jsonRead(SvJsonReader &js)
  {
  SpCmd::jsonRead( js );
  js.jsonPoint( "point", mPoint );
  }
