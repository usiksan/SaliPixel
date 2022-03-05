#include "SpCmdAreaMove.h"

SpCmdAreaMove::SpCmdAreaMove(QPoint s0, QPoint s1, QPoint t, bool doCopy, bool doOverride) :
  SpCmdArea( s0, s1 ),
  mTarget(t),
  mDoCopy(doCopy),
  mDoOverride(doOverride)
  {

  }


void SpCmdAreaMove::paint(SpImage &im)
  {
  if( mVisible )
    im.editMove( mSelect0, mSelect1, mTarget, mDoCopy, mDoOverride );
  }



void SpCmdAreaMove::jsonWrite(SvJsonWriter &js)
  {
  SpCmdArea::jsonWrite( js );
  js.jsonPoint( "target", mTarget );
  js.jsonBool( "doCopy", mDoCopy );
  js.jsonBool( "doOverride", mDoOverride );
  }




void SpCmdAreaMove::jsonRead(SvJsonReader &js)
  {
  SpCmdArea::jsonRead( js );
  js.jsonPoint( "target", mTarget );
  js.jsonBool( "doCopy", mDoCopy );
  js.jsonBool( "doOverride", mDoOverride );
  }


void SpCmdAreaMove::parsePoints(std::function<void (QPoint &)> parser)
  {
  if( mVisible ) {
    //SpCmdArea::parsePoints( parser );
    parser( mTarget );
    }
  }
