#include "SpCmdArc.h"

SpCmdArc::SpCmdArc(QPoint center, QPoint start, QPoint stop, QColor color) :
  SpCmd(color),
  mCenter(center),
  mStart(start),
  mStop(stop)
  {

  }


void SpCmdArc::paint(SpImage &im)
  {
  im.drawArc( mCenter, mStart, mStop, mColor );
  }



void SpCmdArc::jsonWrite(SvJsonWriter &js)
  {
  SpCmd::jsonWrite( js );
  js.jsonPoint( "center", mCenter );
  js.jsonPoint( "start", mStart );
  js.jsonPoint( "stop", mStop );
  }



void SpCmdArc::jsonRead(SvJsonReader &js)
  {
  SpCmd::jsonRead( js );
  js.jsonPoint( "center", mCenter );
  js.jsonPoint( "start", mStart );
  js.jsonPoint( "stop", mStop );
  }
