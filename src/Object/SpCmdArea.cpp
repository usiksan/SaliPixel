#include "SpCmdArea.h"

SpCmdArea::SpCmdArea(QPoint s0, QPoint s1) :
  SpCmd(),
  mSelect0(s0),
  mSelect1(s1)
  {

  }


void SpCmdArea::jsonWrite(SvJsonWriter &js)
  {
  SpCmd::jsonWrite( js );
  js.jsonPoint( "select0", mSelect0 );
  js.jsonPoint( "select1", mSelect1 );
  }

void SpCmdArea::jsonRead(SvJsonReader &js)
  {
  SpCmd::jsonRead( js );
  js.jsonPoint( "select0", mSelect0 );
  js.jsonPoint( "select1", mSelect1 );
  }



void SpCmdArea::parsePoints(std::function<void (QPoint &)> parser)
  {
  if( mVisible ) {
    parser(mSelect0);
    parser(mSelect1);
    }
  }
