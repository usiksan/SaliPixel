#include "SpCmdLine.h"

SpCmdLine::SpCmdLine()
  {

  }


void SpCmdLine::paint(SpImage &im)
  {
  if( mVisible )
    im.drawLine( mStart, mStop, mColor );
  }



void SpCmdLine::jsonWrite(SvJsonWriter &js)
  {
  SpCmd::jsonWrite( js );
  js.jsonPoint( "start", mStart );
  js.jsonPoint( "stop", mStop );
  }




void SpCmdLine::jsonRead(SvJsonReader &js)
  {
  SpCmd::jsonRead( js );
  js.jsonPoint( "start", mStart );
  js.jsonPoint( "stop", mStop );
  }
