#include "SpCmdTriangle.h"

SpCmdTriangle::SpCmdTriangle(QPoint vertex0, QPoint vertex1, QPoint vertex2, QColor color) :
  SpCmd{color},
  mVertex0{vertex0},
  mVertex1{vertex1},
  mVertex2{vertex2}
  {

  }


void SpCmdTriangle::paint(SpImage &im)
  {
  if( mVisible ) {
    im.drawLine( mVertex0, mVertex1, mColor );
    im.drawLine( mVertex1, mVertex2, mColor );
    im.drawLine( mVertex2, mVertex0, mColor );
    }
  }
