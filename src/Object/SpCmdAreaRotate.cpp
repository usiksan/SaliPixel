#include "SpCmdAreaRotate.h"

SpCmdAreaRotate::SpCmdAreaRotate(QPoint s0, QPoint s1, QPoint center, QPoint angle, bool doCopy, bool doOverride) :
  SpCmdArea(s0,s1),
  mCenter(center),
  mAngle(angle),
  mDoCopy(doCopy),
  mDoOverride(doOverride)
  {

  }


void SpCmdAreaRotate::paint(SpImage &im)
  {
  if( mVisible )
    im.editRotate( mSelect0, mSelect1, mCenter, mAngle, mDoCopy, mDoOverride );
  }



void SpCmdAreaRotate::jsonWrite(SvJsonWriter &js)
  {
  SpCmdArea::jsonWrite( js );
  js.jsonPoint( "center", mCenter );
  js.jsonPoint( "angle", mAngle );
  js.jsonBool( "doCopy", mDoCopy );
  js.jsonBool( "doOverride", mDoOverride );
  }




void SpCmdAreaRotate::jsonRead(SvJsonReader &js)
  {
  SpCmdArea::jsonRead( js );
  js.jsonPoint( "center", mCenter );
  js.jsonPoint( "angle", mAngle );
  js.jsonBool( "doCopy", mDoCopy );
  js.jsonBool( "doOverride", mDoOverride );
  }


void SpCmdAreaRotate::parsePoints(std::function<void (QPoint &)> parser)
  {
  if( mVisible ) {
    parser(mCenter);
    parser(mAngle);
    }
  }
