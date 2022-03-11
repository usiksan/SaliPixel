#include "SpImage.h"

#include <QStack>
//#include <QDebug>
#include <cmath>

inline int   ipart(float x) { return int(floorf(x)); }
inline float fpart(float x) { return x - floorf(x); }
inline float rfpart(float x) { return 1 - fpart(x); }




static void pixelSet4( SpImage *im, int x, int y, int deltax, int deltay, SpColor color )
  {
  im->pixelAdd( x + deltax, y + deltay, color );
  im->pixelAdd( x - deltax, y + deltay, color );
  im->pixelAdd( x + deltax, y - deltay, color );
  im->pixelAdd( x - deltax, y - deltay, color );
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
    im->pixelAdd( x + deltax0, y + deltay0, color0 );
    im->pixelAdd( x + deltax1, y + deltay1, color1 );
    }
  if( angleHit( startAngle, sweepAngle, x, y, x - deltax0, y + deltay0 ) ) {
    im->pixelAdd( x - deltax0, y + deltay0, color0 );
    im->pixelAdd( x - deltax1, y + deltay1, color1 );
    }
  if( angleHit( startAngle, sweepAngle, x, y, x + deltax0, y - deltay0 ) ) {
    im->pixelAdd( x + deltax0, y - deltay0, color0 );
    im->pixelAdd( x + deltax1, y - deltay1, color1 );
    }
  if( angleHit( startAngle, sweepAngle, x, y, x - deltax0, y - deltay0 ) ) {
    im->pixelAdd( x - deltax0, y - deltay0, color0 );
    im->pixelAdd( x - deltax1, y - deltay1, color1 );
    }
  }



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
  //Check invalid size
  if( w <= 0 || h <= 0 )
    return;

  if( mArea != nullptr )
    delete mArea;

  mWidth = w;
  mHeight = h;
  mArea = new SpColor[mWidth * mHeight];
  }



void SpImage::clear()
  {
  SpColor color;
  int size = mWidth * mHeight;
  for( int i = 0; i < size; i++ )
    mArea[i] = color;
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



void SpImage::pixelAdd(int x, int y, SpColor color)
  {
  if( x < 0 || x >= mWidth || y < 0 || y >= mHeight )
    return;

  mArea[ x + y * mWidth ].append( color );
  }



void SpImage::pixelInvert(int x, int y)
  {
  if( x < 0 || x >= mWidth || y < 0 || y >= mHeight )
    return;

  mArea[ x + y * mWidth ].invert();
  }




void SpImage::pixelClear(int x, int y)
  {
  pixelSet( x, y, SpColor() );
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



void SpImage::imageSet(const QImage &im)
  {
  if( im.width() <= 0 || im.height() <= 0 )
    return;
  resize( im.width(), im.height() );
  imagePaste( QPoint(), im );
  }



void SpImage::imagePaste(QPoint pos, const QImage &im)
  {
  for( int x = 0; x < im.width(); x++ )
    for( int y = 0; y < im.height(); y++ )
      pixelSet( pos.x() + x, pos.y() + y, SpColor( im.pixelColor(x,y) )  );
  }



void SpImage::clearPixel(QPoint p)
  {
  pixelClear( p.x(), p.y() );
  }



void SpImage::clearHLine(int x0, int x1, int y)
  {
  if( x1 < x0 )
    qSwap( x0, x1 );
  while( x0 <= x1 )
    pixelClear( x0++, y );
  }

void SpImage::clearCircle(QPoint center, QPoint p)
  {
  // R - радиус, X1, Y1 - координаты центра
  int x = 0;
  int y = distance( center, p );
  int delta = 1 - 2 * y;
  int error = 0;
  while( y >= x ) {
    clearHLine( center.x() - x, center.x() + x, center.y() + y );
    clearHLine( center.x() - x, center.x() + x, center.y() - y );
    clearHLine( center.x() - y, center.x() + y, center.y() + x );
    clearHLine( center.x() - y, center.x() + y, center.y() - x );
    error = 2 * (delta + y) - 1;
    if( (delta < 0) && (error <= 0) ) {
      delta += 2 * ++x + 1;
      continue;
      }
    if( (delta > 0) && (error > 0) ) {
      delta -= 2 * --y + 1;
      continue;
      }
    delta += 2 * (++x - --y);
    }
  }



void SpImage::clearRect(QPoint a, QPoint b)
  {
  int x0(a.x()), x1(b.x()), y0(a.y()), y1(b.y());
  if( x1 < x0 )
    qSwap( x0, x1 );
  if( y1 < y0 )
    qSwap( y0, y1 );
  while( y0 <= y1 )
    clearHLine( x0, x1, y0++ );
  }

void SpImage::editArea(SpImage &dest, QPoint a, QPoint b, bool cut)
  {
  int x0(a.x()), x1(b.x()), y0(a.y()), y1(b.y());
  if( x1 < x0 )
    qSwap( x0, x1 );
  if( y1 < y0 )
    qSwap( y0, y1 );
  dest.resize( x1 - x0 + 1, y1 - y0 + 1 );
  for( int x = 0; x < dest.width(); x++ )
    for( int y = 0; y < dest.height(); y++ ) {
      dest.pixelSet( x, y, pixelGet( x0 + x, y0 + y ) );
      if( cut )
        pixelClear( x0 + x, y0 + y );
      }
  }


void SpImage::editMove(QPoint a, QPoint b, QPoint target, bool doCopy, bool doOverride)
  {
  QTransform move( QTransform::fromTranslate( -target.x() + qMax( 0, b.x() - a.x() ), -target.y() + qMax( 0, b.y() - a.y() ) ) );
  editTransfer( a, b, move, doCopy, doOverride );
  }



void SpImage::editRotate(QPoint a, QPoint b, QPoint center, QPoint angle, bool doCopy, bool doOverride)
  {
  QRect r(a,b);
  float zero = arcAngle( center, r.center() );
  QTransform rotate( QTransform::fromTranslate( -center.x(), -center.y() ) );
  float ang = arcAngle( center, angle ) - zero;
  rotate *= QTransform::fromScale(1.0,1.0).rotateRadians( -ang );
  rotate *= QTransform::fromTranslate( center.x() - qMin(a.x(),b.x()), center.y() - qMin(a.y(),b.y()) );
  editTransfer( a, b, rotate, doCopy, doOverride );
  }



void SpImage::editMirror(QPoint a, QPoint b, QPoint center, QPoint angle, bool doCopy, bool doOverride)
  {
  QTransform mirror( QTransform::fromTranslate( -center.x(), -center.y() ) );
  float ang = arcAngle( center, angle ) + M_PI_2;
  mirror *= QTransform::fromScale(1.0,1.0).rotateRadians( -ang );
  mirror *= QTransform::fromScale( -1.0, 1.0 );
  mirror *= QTransform::fromScale(1.0,1.0).rotateRadians( ang );
  mirror *= QTransform::fromTranslate( center.x() - qMin(a.x(),b.x()), center.y() - qMin(a.y(),b.y()) );
  editTransfer( a, b, mirror, doCopy, doOverride );
  }



void SpImage::editTransfer(QPoint a, QPoint b, QTransform &matrix, bool doCopy, bool doOverride)
  {
  //Copy selected
  SpImage area;
  editArea( area, a, b, !doCopy );

  for( int x = 0; x < mWidth; x++ )
    for( int y = 0; y < mHeight; y++ ) {
      QPointF p = matrix.map( QPointF(x,y) );
      //Get 4 point for smooth
      int x0 = ipart( p.x() );
      int x1 = x0 + 1;
      int y0 = ipart( p.y() );
      int y1 = y0 + 1;
      SpColor color = area.pixelGet( x0, y0 ).scale( rfpart(p.x()) * rfpart(p.y()) );
      SpColor color1 = area.pixelGet( x1, y0 ).scale( fpart(p.x()) * rfpart(p.y()) );
      SpColor color2 = area.pixelGet( x0, y1 ).scale( rfpart(p.x()) * fpart(p.y()) );
      SpColor color3 = area.pixelGet( x1, y1 ).scale( fpart(p.x()) * fpart(p.y()) );
      //SpColor color = area.pixel( matrix.map(QPoint(x,y)) );
      color.append( color1 );
      color.append( color2 );
      color.append( color3 );
//      color.mRed   = qBound( 0, (color.alphaRed() + color1.alphaRed() + color2.alphaRed() + color3.alphaRed()) / 255, 255 );
//      color.mGreen = qBound( 0, (color.alphaGreen() + color1.alphaGreen() + color2.alphaGreen() + color3.alphaGreen()) / 255, 255 );
//      color.mBlue  = qBound( 0, (color.alphaBlue() + color1.alphaBlue() + color2.alphaBlue() + color3.alphaBlue()) / 255, 255 );
//      color.mAlpha = color.mAlpha + color1.mAlpha + color2.mAlpha + color3.mAlpha;
      if( !color.isEmpty() ) {
        if( doOverride ) pixelSet( x, y, color );
        else             pixelAdd( x, y, color );
        }
      }
  }




void SpImage::editScale(QPoint a, QPoint b, QPoint scale)
  {
  //Copy selected
  SpImage area;
  editArea( area, a, b, true );
  int w = qAbs( scale.x() - a.x() );
  int h = qAbs( scale.y() - a.y() );

  if( w != 0 && h != 0 ) {
    QImage scaled = area.toImage().scaled( w, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );

    QPoint dest( qMin(a.x(), scale.x()), qMin(a.y(), scale.y()) );
    imagePaste( dest, scaled );
    }

  }



void SpImage::selectionPoint(QPoint p)
  {
  pixelInvert(p.x(), p.y());
  }



void SpImage::selectionLine(QPoint a, QPoint b)
  {
  hardLine( a, b, [this] (int x, int y) { pixelInvert(x,y); });
  }



void SpImage::selectionRect(QPoint a, QPoint b)
  {
  int x0(a.x()), y0(a.y()), x1(b.x()), y1(b.y());
  if( x1 < x0 )
    qSwap( x0, x1 );
  if( y1 < y0 )
    qSwap( y0, y1 );
  //Top line
  for( int x = x0; x < x1; x++ )
    pixelInvert( x, y0 );
  //Right line
  for( int y = y0; y < y1; y++ )
    pixelInvert( x1, y );
  //Bottom line
  for( int x = x1; x > x0; x-- )
    pixelInvert( x, y1 );
  //Left line
  for( int y = y1; y > y0; y-- )
    pixelInvert( x0, y );
  }



void SpImage::drawPixel(QPoint p, SpColor color)
  {
  pixelAdd( p.x(), p.y(), color );
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
    pixelAdd( ypx11,     xpx11, color.brightness( rfpart(yend) * xgap ) );
    pixelAdd( ypx11 + 1, xpx11, color.brightness( fpart(yend) * xgap) );
    }
  else {
    pixelAdd( xpx11, ypx11,     color.brightness( rfpart(yend) * xgap) );
    pixelAdd( xpx11, ypx11 + 1, color.brightness( fpart(yend) * xgap) );
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
    pixelAdd( ypx12,     xpx12, color.brightness( rfpart(yend) * xgap) );
    pixelAdd( ypx12 + 1, xpx12, color.brightness( fpart(yend) * xgap) );
    }
  else {
    pixelAdd( xpx12, ypx12,     color.brightness( rfpart(yend) * xgap) );
    pixelAdd( xpx12, ypx12 + 1, color.brightness( fpart(yend) * xgap) );
    }
  }

  if( steep ) {
    for (int x = xpx11 + 1; x < xpx12; x++) {
      pixelAdd( ipart(intery),     x, color.brightness( rfpart(intery) ) );
      pixelAdd( ipart(intery) + 1, x, color.brightness( fpart(intery) ) );
      intery += gradient;
      }
    }
  else {
    for (int x = xpx11 + 1; x < xpx12; x++) {
      pixelAdd( x, ipart(intery),     color.brightness( rfpart(intery) ) );
      pixelAdd( x, ipart(intery) + 1, color.brightness( fpart(intery) ) );
      intery += gradient;
      }
    }

  }




void SpImage::drawHLine(int x0, int x1, int y, SpColor color)
  {
  if( x1 < x0 )
    qSwap( x0, x1 );
  while( x0 <= x1 )
    pixelAdd( x0++, y, color );
  }

void SpImage::drawVLine(int x, int y0, int y1, SpColor color)
  {
  if( y1 < y0 )
    qSwap( y0, y1 );
  while( y0 <= y1 )
    pixelAdd( x, y0++, color );
  }




void SpImage::drawRect(QPoint a, QPoint b, SpColor color)
  {
  drawHLine( a.x(), b.x(), a.y(), color );
  drawHLine( a.x(), b.x(), b.y(), color );
  drawVLine( a.x(), a.y(), b.y(), color );
  drawVLine( b.x(), a.y(), b.y(), color );
  }

void SpImage::drawFillRect(QPoint a, QPoint b, SpColor color)
  {
  int x0(a.x()), x1(b.x()), y0(a.y()), y1(b.y());
  if( x1 < x0 )
    qSwap( x0, x1 );
  if( y1 < y0 )
    qSwap( y0, y1 );
  while( x0 <= x1 )
    drawVLine( x0++, y0, y1, color );
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
  }




void SpImage::drawFillCircle(QPoint center, QPoint p, SpColor color)
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
    drawHLine( center.x() - x, center.x() + x, center.y() + (y - 1), color );
    drawHLine( center.x() - x, center.x() + x, center.y() - (y - 1), color );
    }

  quarter = roundf(radiusY2 / sqrtf(radiusX2 + radiusY2));
  for( int y = 0; y <= quarter; y++ ) {
    float fx = radiusX * sqrtf( 1 - y * y / radiusY2 );
    int x = ipart(fx);

    pixelSet4( this, center.x(), center.y(), x, y, color.brightness( fpart(fx) ) );
    x--;
    drawHLine( center.x() - x, center.x() + x, center.y() + y, color );
    drawHLine( center.x() - x, center.x() + x, center.y() - y, color );
    }
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




void SpImage::drawFill(QPoint start, SpColor color)
  {
  QStack<QPoint> points;
  if( isInside(start) )
    points.append( start );
  while( points.count() ) {
    start = points.pop();
    if( pixel(start).isOpacity() ) {
      drawPixel( start, color );
      start.rx()++;
      if( isInside(start) && pixel(start).isOpacity() ) points.append(start);
      start.rx() -= 2;
      if( isInside(start) && pixel(start).isOpacity() ) points.append(start);
      start.rx()++;
      start.ry()++;
      if( isInside(start) && pixel(start).isOpacity() ) points.append(start);
      start.ry() -= 2;
      if( isInside(start) && pixel(start).isOpacity() ) points.append(start);
      }
    }
  }



QPoint SpImage::center(QPoint p0, QPoint p1)
  {
  return QPoint( (p0.x() + p1.x()) / 2, (p0.y() + p1.y()) / 2 );
  }




QPoint SpImage::rotate(QPoint center, QPoint zero, QPoint axiz, int index)
  {
  float zeroAng  = arcAngle( center, zero );
  float angleStep = arcAngle( center, axiz ) - zeroAng;
  angleStep *= index;
  QTransform mat( QTransform::fromTranslate( -center.x(), -center.y() ) );
  mat *= QTransform::fromScale(1.0,1.0).rotateRadians( angleStep );
  mat *= QTransform::fromTranslate( center.x(), center.y() );
  return mat.map( zero );
  }




float SpImage::distance(QPoint p0, QPoint p1)
  {
  float dx = p0.x() - p1.x();
  float dy = p0.y() - p1.y();
  return sqrtf( dx * dx + dy * dy );
  }




void SpImage::hardLine(QPoint a, QPoint b, std::function<void (int,int)> drawFunction )
  {
  int x0(a.x()), y0(a.y()), x1(b.x()), y1(b.y());
  bool steep = qAbs(y1 - y0) > qAbs(x1 - x0);
  if( steep ) {
    //Change x<->y
    qSwap( x0, y0 );
    qSwap( x1, y1 );
    }
  if( x0 > x1 ) {
    qSwap( x0, x1 );
    qSwap( y0, y1 );
    }
  int deltax = qAbs(x1 - x0);
  int deltay = qAbs(y1 - y0);
  int error = deltax / 2;
  int ystep = (y0 < y1) ? 1 : -1; //Grow direction for Y
  int y = y0;
  if( steep ) {
    //Draw by Y
    for( int x = x0; x <= x1; x++ ) {
      drawFunction( y, x );
      error -= deltay;
      if( error < 0 ) {
        y += ystep;
        error += deltax;
        }
      }
    }
  else {
    //Draw by X
    for( int x = x0; x <= x1; x++ ) {
      drawFunction( x, y );
      error -= deltay;
      if( error < 0 ) {
        y += ystep;
        error += deltax;
        }
      }
    }
  }



