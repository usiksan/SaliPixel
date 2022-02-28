#ifndef SPIMAGE_H
#define SPIMAGE_H

#include "SpColor.h"

#include <QPoint>

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

    void    set( const SpImage &src );

    void    operator = ( const SpImage &src ) { set(src); }

    void    pixelSet( int x, int y, SpColor color );

    SpColor pixelGet( int x, int y ) const;

    void    drawPixel( QPoint p, SpColor color );

    void    drawLine( QPoint a, QPoint b, SpColor color );

    void    drawFill( QPoint start, SpColor color );
  };

#endif // SPIMAGE_H
