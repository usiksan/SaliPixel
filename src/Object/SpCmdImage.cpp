#include "SpCmdImage.h"

SpCmdImage::SpCmdImage(QPoint pos, QImage &im) :
  SpCmd(),
  mImage(im),
  mPoint(pos)
  {

  }


void SpCmdImage::paint(SpImage &im)
  {
  im.imagePaste( mPoint - QPoint( mImage.width() / 2, mImage.height() / 2 ), mImage, false );
  }



void SpCmdImage::jsonWrite(SvJsonWriter &js)
  {
  SpCmd::jsonWrite( js );
  int w = mImage.width();
  int h = mImage.height();
  js.jsonInt( "width", w );
  js.jsonInt( "height", h );
  QList<int> im;
  for( int x = 0; x < w; x++ )
    for( int y = 0; y < h; y++ ) {
      QColor c = mImage.pixelColor( x, y );
      im.append( c.alpha() );
      im.append( c.red() );
      im.append( c.green() );
      im.append( c.blue() );
      }
  js.jsonListInt( "image", im );
  }



void SpCmdImage::jsonRead(SvJsonReader &js)
  {
  SpCmd::jsonRead( js );
  int w,h;
  js.jsonInt( "width", w );
  js.jsonInt( "height", h );
  QList<int> im;
  js.jsonListInt( "image", im );
  mImage = QImage( w, h, QImage::Format_ARGB32 );
  int index = 0;
  for( int x = 0; x < w; x++ )
    for( int y = 0; y < h; y++ ) {
      int alpha = im.at(index++);
      int red   = im.at(index++);
      int green = im.at(index++);
      int blue  = im.at(index++);
      mImage.setPixelColor( x, y, QColor( red, green, blue, alpha ) );
      }
  }



void SpCmdImage::parsePoints(std::function<void (QPoint &)> parser)
  {
  parser( mPoint );
  }
