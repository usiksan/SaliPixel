#include "SpCmdAreaScale.h"

SpCmdAreaScale::SpCmdAreaScale(QPoint s0, QPoint s1, QPoint scale) :
  SpCmdArea(s0,s1),
  mScale(scale)
  {

  }


void SpCmdAreaScale::paint(SpImage &im)
  {
  if( mVisible )
    im.editScale( mSelect0, mSelect1, mScale );
  }



void SpCmdAreaScale::jsonWrite(SvJsonWriter &js)
  {
  SpCmdArea::jsonWrite( js );
  js.jsonPoint( "scale", mScale );
  }



void SpCmdAreaScale::jsonRead(SvJsonReader &js)
  {
  SpCmdArea::jsonRead( js );
  js.jsonPoint( "scale", mScale );
  }


void SpCmdAreaScale::parsePoints(std::function<void (QPoint &)> parser)
  {
  if( mVisible )
    parser(mScale);
  }
