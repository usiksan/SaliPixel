#include "SpCmdRect.h"

SpCmdRect::SpCmdRect()
  {

  }


void SpCmdRect::paint(SpImage &im)
  {
  if( mVisible )
    im.drawRect( mFirst, mSecond, mColor );
  }



void SpCmdRect::jsonWrite(SvJsonWriter &js)
  {
  SpCmd::jsonWrite( js );
  js.jsonPoint( "first", mFirst );
  js.jsonPoint( "second", mSecond );
  }



void SpCmdRect::jsonRead(SvJsonReader &js)
  {
  SpCmd::jsonRead( js );
  js.jsonPoint( "first", mFirst );
  js.jsonPoint( "second", mSecond );
  }


void SpCmdRect::parsePoints(std::function<void (QPoint &)> parser)
  {
  if( mVisible ) {
    parser(mFirst);
    parser(mSecond);
    }
  }
