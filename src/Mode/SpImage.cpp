#include "SpImage.h"

#include <cmath>

SpImage::SpImage() :
  mWidth{0},
  mHeight{0},
  mArea{nullptr}
  {

  }

SpImage::~SpImage()
  {
  if( mArea != nullptr )
    delete mArea;
  }

void SpImage::resize(int w, int h)
  {
  if( mArea != nullptr )
    delete mArea;

  mWidth = w;
  mHeight = h;
  mArea = new SpColor[mWidth * mHeight];
  }



void SpImage::set(const SpImage &src)
  {
  if( mWidth != src.width() || mHeight != src.height() )
    resize( src.width(), src.height() );

  int size = mWidth * mHeight;
  for( int i = 0; i < size; i++ )
    mArea[i] = src.mArea[i];
  }



void SpImage::pixelSet(int x, int y, SpColor color)
  {
  if( x < 0 || x >= mWidth || y < 0 || y >= mHeight )
    return;

  mArea[ x + y * mWidth ] = color;
  }



SpColor SpImage::pixelGet(int x, int y) const
  {
  if( x < 0 || x >= mWidth || y < 0 || y >= mHeight )
    return SpColor( SpColorInvalid );

  return mArea[ x + y * mWidth ];
  }



void SpImage::drawPixel(QPoint p, SpColor color)
  {
  pixelSet( p.x(), p.y(), color );
  }





void SpImage::drawLine(QPoint a, QPoint b, SpColor color)
  {
  int x0(a.x()), x1(b.x()), y0(a.y()), y1(b.y());
  auto ipart = [](float x) -> int {return int(std::floor(x));};
  auto round = [](float x) -> float {return std::round(x);};
  auto fpart = [](float x) -> float {return x - std::floor(x);};
  auto rfpart = [=](float x) -> float {return 1 - fpart(x);};

  const bool steep = abs(y1 - y0) > abs(x1 - x0);
  if( steep ) {
    std::swap(x0,y0);
    std::swap(x1,y1);
    }
  if( x0 > x1 ) {
    std::swap(x0,x1);
    std::swap(y0,y1);
    }

  const float dx = x1 - x0;
  const float dy = y1 - y0;
  const float gradient = (dx == 0) ? 1 : dy/dx;

  int xpx11;
  float intery;
  {
  const float xend = round(x0);
  const float yend = y0 + gradient * (xend - x0);
  const float xgap = rfpart(x0 + 0.5);
  xpx11 = int(xend);
  const int ypx11 = ipart(yend);
  if( steep ) {
    pixelSet( ypx11,     xpx11, color.brightness( rfpart(yend) * xgap ) );
    pixelSet( ypx11 + 1, xpx11, color.brightness( fpart(yend) * xgap) );
    }
  else {
    pixelSet( xpx11, ypx11,     color.brightness( rfpart(yend) * xgap) );
    pixelSet( xpx11, ypx11 + 1, color.brightness( fpart(yend) * xgap) );
    }
  intery = yend + gradient;
  }

  int xpx12;
  {
  const float xend = round(x1);
  const float yend = y1 + gradient * (xend - x1);
  const float xgap = rfpart(x1 + 0.5);
  xpx12 = int(xend);
  const int ypx12 = ipart(yend);
  if( steep ) {
    pixelSet( ypx12,     xpx12, color.brightness( rfpart(yend) * xgap) );
    pixelSet( ypx12 + 1, xpx12, color.brightness( fpart(yend) * xgap) );
    }
  else {
    pixelSet( xpx12, ypx12,     color.brightness( rfpart(yend) * xgap) );
    pixelSet( xpx12, ypx12 + 1, color.brightness( fpart(yend) * xgap) );
    }
  }

  if( steep ) {
    for (int x = xpx11 + 1; x < xpx12; x++) {
      pixelSet( ipart(intery),     x, color.brightness( rfpart(intery) ) );
      pixelSet( ipart(intery) + 1, x, color.brightness( fpart(intery) ) );
      intery += gradient;
      }
    }
  else {
    for (int x = xpx11 + 1; x < xpx12; x++) {
      pixelSet( x, ipart(intery),     color.brightness( rfpart(intery) ) );
      pixelSet( x, ipart(intery) + 1, color.brightness( fpart(intery) ) );
      intery += gradient;
      }
    }

  }
