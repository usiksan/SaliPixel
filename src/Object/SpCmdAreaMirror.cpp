#include "SpCmdAreaMirror.h"

SpCmdAreaMirror::SpCmdAreaMirror(QPoint s0, QPoint s1, QPoint line0, QPoint line1, bool doCopy, bool doOverride) :
  SpCmdArea(s0,s1),
  mMirrorLine0(line0),
  mMirrorLine1(line1),
  mDoCopy(doCopy),
  mDoOverride(doOverride)
  {

  }


void SpCmdAreaMirror::paint(SpImage &im)
  {
  if( mVisible )
    im.editMirror( mSelect0, mSelect1, mMirrorLine0, mMirrorLine1, mDoCopy, mDoOverride );
  }




void SpCmdAreaMirror::jsonWrite(SvJsonWriter &js)
  {
  SpCmdArea::jsonWrite( js );
  js.jsonPoint( "mirrorLine0", mMirrorLine0 );
  js.jsonPoint( "mirrorLine1", mMirrorLine1 );
  js.jsonBool( "doCopy", mDoCopy );
  js.jsonBool( "doOverride", mDoOverride );
  }



void SpCmdAreaMirror::jsonRead(SvJsonReader &js)
  {
  SpCmdArea::jsonRead( js );
  js.jsonPoint( "mirrorLine0", mMirrorLine0 );
  js.jsonPoint( "mirrorLine1", mMirrorLine1 );
  js.jsonBool( "doCopy", mDoCopy );
  js.jsonBool( "doOverride", mDoOverride );
  }


void SpCmdAreaMirror::parsePoints(std::function<void (QPoint &)> parser)
  {
  if( mVisible ) {
    //SpCmdArea::parsePoints( parser );
    parser( mMirrorLine0 );
    parser( mMirrorLine1 );
    }
  }
