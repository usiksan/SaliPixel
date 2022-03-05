#include "SpCmdCircle.h"

SpCmdCircle::SpCmdCircle(QPoint center, QPoint radius, QColor color) :
  SpCmd{color},
  mCenter{center},
  mRadius{radius}
  {

  }


void SpCmdCircle::paint(SpImage &im)
  {
  if( mVisible )
    im.drawCircle( mCenter, mRadius, mColor );
  }



void SpCmdCircle::jsonWrite(SvJsonWriter &js)
  {
  SpCmd::jsonWrite( js );
  js.jsonPoint( "center", mCenter );
  js.jsonPoint( "radius", mRadius );
  }



void SpCmdCircle::jsonRead(SvJsonReader &js)
  {
  SpCmd::jsonRead( js );
  js.jsonPoint( "center", mCenter );
  js.jsonPoint( "radius", mRadius );
  }


void SpCmdCircle::parsePoints(std::function<void (QPoint &)> parser)
  {
  if( mVisible ) {
    parser(mCenter);
    parser(mRadius);
    }
  }
