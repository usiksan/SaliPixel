#include "SpImage.h"

#include <cmath>

inline int   ipart(float x) { return int(floorf(x)); }
inline float fpart(float x) { return x - floorf(x); }
inline float rfpart(float x) { return 1 - fpart(x); }


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
    return SpColor{};

  return mArea[ x + y * mWidth ];
  }



QImage SpImage::toImage() const
  {
  QImage im( mWidth, mHeight, QImage::Format_ARGB32 );
  for( int x = 0; x < mWidth; x++ )
    for( int y = 0; y < mHeight; y++ )
      im.setPixelColor( x, y, pixelGet(x,y).color() );
  return im;
  }



void SpImage::drawPixel(QPoint p, SpColor color)
  {
  pixelSet( p.x(), p.y(), color );
  }





void SpImage::drawLine(QPoint a, QPoint b, SpColor color)
  {
  int x0(a.x()), x1(b.x()), y0(a.y()), y1(b.y());

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
  const float xend = roundf(x0);
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
  const float xend = roundf(x1);
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




void SpImage::drawHLine(int x0, int x1, int y, SpColor color)
  {
  if( x1 < x0 )
    qSwap( x0, x1 );
  while( x0 <= x1 )
    pixelSet( x0++, y, color );
  }

void SpImage::drawVLine(int x, int y0, int y1, SpColor color)
  {
  if( y1 < y0 )
    qSwap( y0, y1 );
  while( y0 <= y1 )
    pixelSet( x, y0++, color );
  }




void SpImage::drawRect(QPoint a, QPoint b, SpColor color)
  {
  drawHLine( a.x(), b.x(), a.y(), color );
  drawHLine( a.x(), b.x(), b.y(), color );
  drawVLine( a.x(), a.y(), b.y(), color );
  drawVLine( b.x(), a.y(), b.y(), color );
  }


static void pixelSet4( SpImage *im, int x, int y, int deltax, int deltay, SpColor color )
  {
  im->pixelSet( x + deltax, y + deltay, color );
  im->pixelSet( x - deltax, y + deltay, color );
  im->pixelSet( x + deltax, y - deltay, color );
  im->pixelSet( x - deltax, y - deltay, color );
  }


static float arcAngle( int cx, int cy, int px, int py )
  {
  return atan2f( py - cy, px - cx );
  }

static float arcAngle( QPoint center, QPoint p )
  {
  return arcAngle( center.x(), center.y(), p.x(), p.y() );
  }


static bool angleHit( float startAngle, float sweepAngle, int cx, int cy, int px, int py )
  {
  float angle = arcAngle( cx, cy, px, py );
  if( startAngle > sweepAngle )
    return angle > startAngle || angle < sweepAngle;
  return angle > startAngle && angle < sweepAngle;
  }

static void pixelSet8( SpImage *im, int x, int y, int deltax0, int deltax1, int deltay0, int deltay1, SpColor color0, SpColor color1, float startAngle, float sweepAngle )
  {
  if( angleHit( startAngle, sweepAngle, x, y, x + deltax0, y + deltay0 ) ) {
    im->pixelSet( x + deltax0, y + deltay0, color0 );
    im->pixelSet( x + deltax1, y + deltay1, color1 );
    }
  if( angleHit( startAngle, sweepAngle, x, y, x - deltax0, y + deltay0 ) ) {
    im->pixelSet( x - deltax0, y + deltay0, color0 );
    im->pixelSet( x - deltax1, y + deltay1, color1 );
    }
  if( angleHit( startAngle, sweepAngle, x, y, x + deltax0, y - deltay0 ) ) {
    im->pixelSet( x + deltax0, y - deltay0, color0 );
    im->pixelSet( x + deltax1, y - deltay1, color1 );
    }
  if( angleHit( startAngle, sweepAngle, x, y, x - deltax0, y - deltay0 ) ) {
    im->pixelSet( x - deltax0, y - deltay0, color0 );
    im->pixelSet( x - deltax1, y - deltay1, color1 );
    }
  }


float distance( QPoint a, QPoint b )
  {
  float dx = a.x() - b.x();
  float dy = a.y() - b.y();
  return sqrtf( dx * dx + dy * dy );
  }

void SpImage::drawCircle(QPoint center, QPoint p, SpColor color)
  {
  float radius = distance( center, p );
  if( radius < 1.0 )
    return;

  float radiusX = radius;
  float radiusY = radius;
  float radiusX2 = radiusX * radiusX;
  float radiusY2 = radiusY * radiusY;

  float quarter = roundf(radiusX2 / sqrtf(radiusX2 + radiusY2));
  for( int x = 0; x <= quarter; x++ ) {
    float fy = radiusY * sqrtf(1 - x * x / radiusX2);
    int y = ipart(fy);

    pixelSet4( this, center.x(), center.y(), x, y, color.brightness( fpart(fy) ) );
    pixelSet4( this, center.x(), center.y(), x, y - 1, color.brightness( rfpart(fy) ) );
    }

  quarter = roundf(radiusY2 / sqrtf(radiusX2 + radiusY2));
  for( int y = 0; y <= quarter; y++ ) {
    float fx = radiusX * sqrtf( 1 - y * y / radiusY2 );
    int x = ipart(fx);

    pixelSet4( this, center.x(), center.y(), x, y, color.brightness( fpart(fx) ) );
    pixelSet4( this, center.x(), center.y(), x - 1, y, color.brightness( rfpart(fx) ) );
    }

  // R - радиус, X1, Y1 - координаты центра
//  int x = 0;
//  int y = radius;
//  int delta = 1 - 2 * radius;
//  int error = 0;
//  while (y >= x) {
//    pixelSet( center.x() + x, center.y() + y, color );
//    pixelSet( center.x() + x, center.y() - y, color );
//    pixelSet( center.x() - x, center.y() + y, color );
//    pixelSet( center.x() - x, center.y() - y, color );
//    pixelSet( center.x() + y, center.y() + x, color );
//    pixelSet( center.x() + y, center.y() - x, color );
//    pixelSet( center.x() - y, center.y() + x, color );
//    pixelSet( center.x() - y, center.y() - x, color );
//    error = 2 * (delta + y) - 1;
//    if( (delta < 0) && (error <= 0) ) {
//      delta += 2 * ++x + 1;
//      continue;
//      }
//    if( (delta > 0) && (error > 0) ) {
//      delta -= 2 * --y + 1;
//      continue;
//      }
//    delta += 2 * (++x - --y);
  //    }
  }





void SpImage::drawArc(QPoint center, QPoint start, QPoint stop, SpColor color)
  {
  float radius = distance( center, start );
  if( radius < 1.0 )
    return;

  float startAngle = arcAngle( center, start );
  float sweepAngle = arcAngle( center, stop );

  float radiusX = radius;
  float radiusY = radius;
  float radiusX2 = radiusX * radiusX;
  float radiusY2 = radiusY * radiusY;

  float quarter = roundf(radiusX2 / sqrtf(radiusX2 + radiusY2));
  for( int x = 0; x <= quarter; x++ ) {
    float fy = radiusY * sqrtf(1 - x * x / radiusX2);
    int y = ipart(fy);

    pixelSet8( this, center.x(), center.y(), x, x, y, y - 1, color.brightness( fpart(fy) ), color.brightness( rfpart(fy) ), startAngle, sweepAngle );
    }

  quarter = roundf(radiusY2 / sqrtf(radiusX2 + radiusY2));
  for( int y = 0; y <= quarter; y++ ) {
    float fx = radiusX * sqrtf( 1 - y * y / radiusY2 );
    int x = ipart(fx);

    pixelSet8( this, center.x(), center.y(), x, x - 1, y, y, color.brightness( fpart(fx) ), color.brightness( rfpart(fx) ), startAngle, sweepAngle );
    }
  }



void SpImage::drawArc(QPoint center, int radius, float startAngle, float sweepAngle, SpColor color)
  {
  startAngle = fabsf( startAngle );
  sweepAngle = fabsf( sweepAngle );

  if( startAngle >= M_PI * 2 ) startAngle = 0;
  if( sweepAngle > M_PI * 2 ) sweepAngle = M_PI * 2;
  if( startAngle + sweepAngle > M_PI * 2 ) {
    drawArc( center, radius, 0, startAngle + sweepAngle - M_PI * 2, color );
    sweepAngle = M_PI * 2 - startAngle;
    }

  int x = 0;
  int y = radius;

  int gap = 0;

  int delta = (2 - 2 * radius);
  float angle;
  while( y >= 0 ) {
    angle = arcAngle( center, QPoint( center.x() + x, center.y() - y ) );
    if( (angle >= startAngle) && (angle <= startAngle + sweepAngle) ) {
      if( 0 <= angle && angle <= M_PI_2 )
        pixelSet( center.x() + x, center.y() - y, color );
      }

    angle = arcAngle( center, QPoint( center.x() + x, center.y() + y ) );
    if( (angle >= startAngle) && (angle <= startAngle + sweepAngle) ) {
      if( M_PI_2 < angle && angle <= M_PI )
        pixelSet( center.x() + x, center.y() + y, color );
      }

    angle = arcAngle( center, QPoint( center.x() - x, center.y() + y ) );
    if( (angle >= startAngle) && (angle <= startAngle + sweepAngle) ) {
      if( M_PI < angle && angle <= M_PI_2 * 3 )
        pixelSet( center.x() - x, center.y() + y, color );
        }

    angle = arcAngle( center, QPoint( center.x() - x, center.y() - y ) );
    if( (angle >= startAngle) && (angle <= startAngle + sweepAngle) ) {
      if( M_PI_2 * 3 < angle && angle <= M_PI * 2 )
        pixelSet( center.x() - x, center.y() - y, color );
        }
    gap = 2 * (delta + y) - 1;
    if( delta < 0 && gap <= 0 ) {
      x++;
      delta += 2 * x + 1;
      continue;
      }

    if( delta > 0 && gap > 0 ) {
      y--;
      delta -= 2 * y + 1;
      continue;
      }

    x++;
    delta += 2 * (x - y);
    y--;
    }
  }
