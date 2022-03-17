/*
Project "Combine vector-pixel graphic editor for small image like icon"

Author
  Sibilev Alexander S.

Web
  www.saliLab.com
  www.saliLab.ru

Description
  SpImage - internal representation of pixel image

  Image contains of SpColor pixels
*/
#ifndef SPIMAGE_H
#define SPIMAGE_H

#include "SpColor.h"

#include <QPoint>
#include <QImage>
#include <QTransform>
#include <functional>

//!
//! \brief The SpImage class SpColor pixel image
//!
class SpImage
  {
    int      mWidth;  //!< Width of image in pixels
    int      mHeight; //!< Height of image in pixels
    SpColor *mArea;   //!< Pixels array. It is one-dimensional internal representation.
                      //!  Two-dimensional access is throught pixelXXX functions

  public:
    //!
    //! \brief SpImage Builds empty image
    //!
    SpImage();

    //!
    //! \brief SpImage Builds copy of src image. It perform deep copy
    //! \param src     Source image
    //!
    SpImage( const SpImage &src ) : mWidth{0}, mHeight{0}, mArea{nullptr} { set(src); }

    ~SpImage();


    //!
    //! \brief width Returns width of image
    //! \return      Width of image
    //!
    int     width() const { return mWidth; }

    //!
    //! \brief height Returns height of image
    //! \return       Height of image
    //!
    int     height() const { return mHeight; }


    //!
    //! \brief resize Resize image to new dimensionals
    //! \param w      New width of image
    //! \param h      New height of image
    //!
    void    resize( int w, int h );

    //!
    //! \brief clear Make all pixels of image fully transparent color
    //!
    void    clear();

    //!
    //! \brief set Set current image as copy of source image including dimensions
    //! \param src Source image
    //!
    void    set( const SpImage &src );

    //!
    //! \brief operator = Overloading operator as set function
    //! \param src        Source image
    //!
    void    operator = ( const SpImage &src ) { set(src); }



    //!
    //! \brief pixelSet Set pixel at specified coords with specified color. New color is override previous color.
    //! \param x        Pixel destignation coords
    //! \param y
    //! \param color    New color of pixel
    //!
    void    pixelSet( int x, int y, SpColor color );

    void    pixelAdd( int x, int y, SpColor color );

    void    pixelInvert( int x, int y );

    void    pixelClear( int x, int y );

    SpColor pixelGet( int x, int y ) const;

    SpColor pixel( QPoint p ) const { return pixelGet( p.x(), p.y() ); }



    QImage  toImage() const;

    void    imageSet( const QImage &im );

    void    imagePaste(QPoint pos, const QImage &im , bool doOverride, bool useTransparent);


    void    clearPixel( QPoint p );

    void    clearHLine( int x0, int x1, int y );

    void    clearCircle( QPoint center, QPoint p );

    void    clearRect( QPoint a, QPoint b );


    void    editArea( SpImage &dest, QPoint a, QPoint b, bool cut );

    void    editMove( QPoint a, QPoint b, QPoint target, bool doCopy, bool doOverride );

    void    editRotate( QPoint a, QPoint b, QPoint center, QPoint angle, bool doCopy, bool doOverride );

    void    editMirror( QPoint a, QPoint b, QPoint center, QPoint angle, bool doCopy, bool doOverride );

    void    editTransfer( QPoint a, QPoint b, QTransform &matrix, bool doCopy, bool doOverride );

    void    editScale( QPoint a, QPoint b, QPoint scale );


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
