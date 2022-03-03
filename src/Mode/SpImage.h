#ifndef SPIMAGE_H
#define SPIMAGE_H

#include "SpColor.h"

#include <QPoint>
#include <QImage>
#include <QTransform>
#include <functional>

class SpImage
  {
    int      mWidth;
    int      mHeight;
    SpColor *mArea;

  public:
    SpImage();
    SpImage( const SpImage &src ) : mWidth{0}, mHeight{0}, mArea{nullptr} { set(src); }
    ~SpImage();


    int     width() const { return mWidth; }

    int     height() const { return mHeight; }


    void    resize( int w, int h );

    void    clear();

    void    set( const SpImage &src );

    void    operator = ( const SpImage &src ) { set(src); }


    void    pixelSet( int x, int y, SpColor color );

    void    pixelAdd( int x, int y, SpColor color );

    void    pixelInvert( int x, int y );

    void    pixelClear( int x, int y );

    SpColor pixelGet( int x, int y ) const;

    SpColor pixel( QPoint p ) const { return pixelGet( p.x(), p.y() ); }



    QImage  toImage() const;


    void    clearPixel( QPoint p );

    void    clearHLine( int x0, int x1, int y );

    void    clearCircle( QPoint center, QPoint p );

    void    clearRect( QPoint a, QPoint b );


    void    editArea( SpImage &dest, QPoint a, QPoint b, bool cut );

    void    editMove( QPoint a, QPoint b, QPoint target, bool doCopy, bool doOverride );

    void    editRotate( QPoint a, QPoint b, QPoint center, QPoint angle, bool doCopy, bool doOverride );

    void    editMirror( QPoint a, QPoint b, QPoint center, QPoint angle, bool doCopy, bool doOverride );

    void    editTransfer( QPoint a, QPoint b, QTransform &matrix, bool doCopy, bool doOverride );


    void    selectionPoint( QPoint p );

    void    selectionLine( QPoint a, QPoint b );

    void    selectionRect( QPoint a, QPoint b );


    void    drawPixel( QPoint p, SpColor color );

    void    drawLine( QPoint a, QPoint b, SpColor color );

    void    drawHLine( int x0, int x1, int y, SpColor color );

    void    drawVLine( int x, int y0, int y1, SpColor color );

    void    drawRect( QPoint a, QPoint b, SpColor color );

    void    drawFillRect( QPoint a, QPoint b, SpColor color );

    void    drawCircle( QPoint center, QPoint p, SpColor color );

    void    drawFillCircle( QPoint center, QPoint p, SpColor color );

    void    drawArc( QPoint center, QPoint start, QPoint stop, SpColor color );

    void    drawFill( QPoint start, SpColor color );


    static QPoint center( QPoint p0, QPoint p1 );

    static QPoint rotate( QPoint center, QPoint zero, QPoint axiz, int index );

    static float  distance( QPoint p0, QPoint p1 );

  private:
    bool    isInside( QPoint p ) const { return p.x() >= 0 && p.x() < mWidth && p.y() >= 0 && p.y() < mHeight; }

    void    hardLine( QPoint a, QPoint b, std::function<void (int,int)> drawFunction );
  };

#endif // SPIMAGE_H
