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



void SpCmdTriangle::jsonWrite(SvJsonWriter &js)
  {
  SpCmd::jsonWrite( js );
  js.jsonPoint( "vertext0", mVertex0 );
  js.jsonPoint( "vertext1", mVertex1 );
  js.jsonPoint( "vertext2", mVertex2 );
  }




void SpCmdTriangle::jsonRead(SvJsonReader &js)
  {
  SpCmd::jsonRead( js );
  js.jsonPoint( "vertext0", mVertex0 );
  js.jsonPoint( "vertext1", mVertex1 );
  js.jsonPoint( "vertext2", mVertex2 );
  }
