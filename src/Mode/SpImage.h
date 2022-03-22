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

  SpImage used for drawing operations. It contains pixel acces level, image transformation functions, drawing primitives
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

    //!
    //! \brief pixelAdd Mix pixel at specified coords with specified color
    //! \param x        Pixel destignation coords
    //! \param y
    //! \param color    Color to append to current pixel color
    //!
    void    pixelAdd( int x, int y, SpColor color );

    //!
    //! \brief pixelInvert Invert color of pixel with coords
    //! \param x           Pixel coords
    //! \param y
    //!
    void    pixelInvert( int x, int y );

    //!
    //! \brief pixelClear Set pixel with specified coords to fully transparent color
    //! \param x          Pixel coords
    //! \param y
    //!
    void    pixelClear( int x, int y );

    //!
    //! \brief pixelGet Returns pixel color
    //! \param x        Pixel coords
    //! \param y
    //! \return         Pixel color
    //!
    SpColor pixelGet( int x, int y ) const;

    //!
    //! \brief pixel This is an overloaded function. Returns pixel color
    //! \param p     Pixel coords as QPoint
    //! \return      Pixel color
    //!
    SpColor pixel( QPoint p ) const { return pixelGet( p.x(), p.y() ); }



    //!
    //! \brief toImage Convert image to QImage format. This function make deep copy.
    //! \return        QImage representation of this image
    //!
    QImage  toImage() const;

    //!
    //! \brief imageSet Convert QImage format to image. This function make deep copy. Dimensions of result image are
    //!                 the same as source image
    //! \param im       QImage representation of source image
    //!
    void    imageSet( const QImage &im );

    //!
    //! \brief imagePaste      Paste QImage into current image at specified point.
    //! \param pos             Coords of insertion (top left corner of image)
    //! \param im              Image to paste
    //! \param doOverride      If it true then destignation pixels overrides with source pixels,
    //!                        if false then source pixels appended to the destignation pixels
    //! \param useTransparent  If it true then transparent pixels of source not affected to destignation
    //!                        if false then source pixels overrides destignation pixels
    //!
    void    imagePaste(QPoint pos, const QImage &im , bool doOverride, bool useTransparent);




    //!
    //! \brief clearPixel This is an overloaded function. It set pixel with specified coords to fully transparent color
    //! \param p          Pixel coord
    //!
    void    clearPixel( QPoint p );

    //!
    //! \brief clearHLine Set all pixels of horizontal line to fully transparent color
    //! \param x0         Begin of horizontal line
    //! \param x1         End of horizontal line
    //! \param y          Vertical position of line
    //!
    void    clearHLine( int x0, int x1, int y );

    //!
    //! \brief clearCircle Set all pixels of circle and fill it with fully transparent color
    //! \param center      Center of circle
    //! \param p           Point on outline of circle
    //!
    void    clearCircle( QPoint center, QPoint p );

    //!
    //! \brief clearRect Set all pixels of rectangle and fill it with fully transparent color
    //! \param a         First corner of rectangle
    //! \param b         Second corner of rectangle
    //!
    void    clearRect( QPoint a, QPoint b );




    //!
    //! \brief editArea Copy area bounded by rectangle of corners a and b into dest image
    //! \param dest     Destignation image. Its dimensions are resized to selection bounded rectangle
    //! \param a        First corner of selection bounded rectangle
    //! \param b        Second corner of selection bounded rectangle
    //! \param cut      If true then source pixels are replased with fully transparent color,
    //!                 if false then source pixels are leave untoughed
    //!
    void    editArea( SpImage &dest, QPoint a, QPoint b, bool cut );

    //!
    //! \brief editMove   Move area bounded by rectangle to trarget point
    //! \param a          Firts corner of selction bounded rectangle
    //! \param b          Second corner of selection bounded rectangle
    //! \param target     Target point of moving
    //! \param doCopy     If true then moved copy of source selected rectangle
    //!                   otherwise source place of rectangle made fully transparent
    //! \param doOverride If true then destignation rectangle fully overrided with moving selected rectangle
    //!                   otherwise moving rectangle added to existing image
    //!
    void    editMove( QPoint a, QPoint b, QPoint target, bool doCopy, bool doOverride );

    //!
    //! \brief editRotate Rotate area bouded by rectangle to defined angle around defined center
    //! \param a          Firts corner of selction bounded rectangle
    //! \param b          Second corner of selection bounded rectangle
    //! \param center     Center point of rotation
    //! \param angle      Point which define angle of rotation as angle beatween center of selected rectangle and point angle
    //! \param doCopy     If true then moved copy of source selected rectangle
    //!                   otherwise source place of rectangle made fully transparent
    //! \param doOverride If true then destignation rectangle fully overrided with moving selected rectangle
    //!                   otherwise moving rectangle added to existing image
    //!
    void    editRotate( QPoint a, QPoint b, QPoint center, QPoint angle, bool doCopy, bool doOverride );

    //!
    //! \brief editMirror Mirror area bounded by rectangle throught line difined center and angle points
    //! \param a          Firts corner of selction bounded rectangle
    //! \param b          Second corner of selection bounded rectangle
    //! \param center     Center point of mirror
    //! \param angle      Point which define second line of mirror line
    //! \param doCopy     If true then moved copy of source selected rectangle
    //!                   otherwise source place of rectangle made fully transparent
    //! \param doOverride If true then destignation rectangle fully overrided with moving selected rectangle
    //!                   otherwise moving rectangle added to existing image
    //!
    void    editMirror( QPoint a, QPoint b, QPoint center, QPoint angle, bool doCopy, bool doOverride );

    //!
    //! \brief editTransfer Perform transfer of area bounded by rectangle. Transfer operation define by transformation matrix
    //! \param a            Firts corner of selction bounded rectangle
    //! \param b            Second corner of selection bounded rectangle
    //! \param matrix       Matrix which define transformation operation
    //! \param doCopy       If true then moved copy of source selected rectangle
    //!                     otherwise source place of rectangle made fully transparent
    //! \param doOverride   If true then destignation rectangle fully overrided with moving selected rectangle
    //!                     otherwise moving rectangle added to existing image
    //!
    void    editTransfer( QPoint a, QPoint b, QTransform &matrix, bool doCopy, bool doOverride );

    //!
    //! \brief editScale Scale area bounded by rectangle
    //! \param a         Firts corner of selction bounded rectangle
    //! \param b         Second corner of selection bounded rectangle
    //! \param scale     Point defined scale factor. It define as ratio of distance a-b and a-scale
    //!
    void    editScale( QPoint a, QPoint b, QPoint scale );




    //!
    //! \brief selectionPoint Draw selection point. Selection is simple inversion of source color
    //! \param p              Place of selection point
    //!
    void    selectionPoint( QPoint p );

    //!
    //! \brief selectionLine Draw selection line. Selection is simple inversion of source color
    //! \param a             Starting point of line
    //! \param b             Ending point of line
    //!
    void    selectionLine( QPoint a, QPoint b );

    //!
    //! \brief selectionRect Draw selection rectangle. Selection is simple inversion of source color
    //! \param a             First corner of selection rectangle
    //! \param b             Second corner of selection rectangle
    //!
    void    selectionRect( QPoint a, QPoint b );



    //!
    //! \brief drawPixel Draw pixel with color. New color is added to existing color
    //! \param p         Point of pixel
    //! \param color     New color of pixel
    //!
    void    drawPixel( QPoint p, SpColor color );

    //!
    //! \brief drawLine Draw line with color. New color of line is added to existing color of image pixels
    //! \param a        Starting point of line
    //! \param b        Ending point of line
    //! \param color    Color of line
    //!
    void    drawLine( QPoint a, QPoint b, SpColor color );

    //!
    //! \brief drawHLine Draw horizontal line with color. New color of line is added to existing color of image pixels
    //! \param x0        Starting x coord of horizontal line
    //! \param x1        Ending x coord of horizontal line
    //! \param y         y coord of horizontal line
    //! \param color     Color of line
    //!
    void    drawHLine( int x0, int x1, int y, SpColor color );

    //!
    //! \brief drawVLine Draw vertical line with color. New color of line is added to existing color of image pixels
    //! \param x         x coord of vertical line
    //! \param y0        Starting y coord of vertical line
    //! \param y1        Ending y coord of vertical line
    //! \param color     Color of line
    //!
    void    drawVLine( int x, int y0, int y1, SpColor color );

    //!
    //! \brief drawRect Draw rectangle with color. Draw only contour without filling. New color of rectangles lines is added to existing color of image pixels
    //! \param a        First corner of rectangle
    //! \param b        Second corner of rectangle
    //! \param color    Color of rectangles lines
    //!
    void    drawRect( QPoint a, QPoint b, SpColor color );

    //!
    //! \brief drawFillRect Draw filled rectangle with color. New color of rectangle is added to existing color of image pixels
    //! \param a            First corner of rectangle
    //! \param b            Second corner of rectangle
    //! \param color        Color of rectangle
    //!
    void    drawFillRect( QPoint a, QPoint b, SpColor color );

    //!
    //! \brief drawCircle Draw circle with color. Draw only contour without filling. New color of circle countour is added to existing color of image pixels
    //! \param center     Center of circle
    //! \param p          Pointer on circle which define circle radius
    //! \param color      Circle contour color
    //!
    void    drawCircle( QPoint center, QPoint p, SpColor color );

    //!
    //! \brief drawFillCircle Draw filled circle with color. New color of circle is added to existing color of image pixels
    //! \param center         Center of circle
    //! \param p              Pointer on circle which define circle radius
    //! \param color          Circle color
    //!
    void    drawFillCircle( QPoint center, QPoint p, SpColor color );

    //!
    //! \brief drawArc Draw arc with color. New color of arc is added to existing color of image pixels
    //! \param center  Center of arc
    //! \param start   Start point of arc. Arc is draw from start point to end point by CW
    //! \param stop    End point of arc
    //! \param color   Arc color
    //!
    void    drawArc( QPoint center, QPoint start, QPoint stop, SpColor color );

    //!
    //! \brief drawFill Fill cloused contour with color. New color is added to existing color of image pixels
    //! \param start    Start point inside of contour
    //! \param color    Filled color
    //!
    void    drawFill( QPoint start, SpColor color );


    //!
    //! \brief center Helper functionf which calculate center point beatween two points
    //! \param p0     First point
    //! \param p1     Second point
    //! \return       Center point
    //!
    static QPoint center( QPoint p0, QPoint p1 );

    //!
    //! \brief rotate Helper function. Rotate source point to angle multiple to source angle and index
    //! \param center Center of rotation
    //! \param zero   Source point
    //! \param axiz   Point which define source angle
    //! \param index  Index of rotation angle. Destignation angle is source angle multiply to index
    //! \return       Rotated point
    //!
    static QPoint rotate( QPoint center, QPoint zero, QPoint axiz, int index );

    //!
    //! \brief distance Helper function. Calculate distance beatween p0 and p1
    //! \param p0       First point
    //! \param p1       Second point
    //! \return         Distance beatween first and second points
    //!
    static float  distance( QPoint p0, QPoint p1 );

  private:
    bool    isInside( QPoint p ) const { return p.x() >= 0 && p.x() < mWidth && p.y() >= 0 && p.y() < mHeight; }

    void    hardLine( QPoint a, QPoint b, std::function<void (int,int)> drawFunction );
  };

#endif // SPIMAGE_H
