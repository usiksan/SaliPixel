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
