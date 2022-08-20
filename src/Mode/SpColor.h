/*
Project "Combine vector-pixel graphic editor for small image like icon"

Author
  Sibilev Alexander S.

Web
  www.saliLab.com
  www.saliLab.ru

Description
  Color representation - one pixel
*/
#ifndef SPCOLOR_H
#define SPCOLOR_H

#include <QColor>

//!
//! \brief The SpColor class Represent one pixel of image
//!
class SpColor {
    quint8 mAlpha; //!< Alpha channel 0-255, 0 - full transparent, 255 - solid
    quint8 mRed;   //!< Red channel 0-255
    quint8 mGreen; //!< Green channel 0-255
    quint8 mBlue;  //!< Blue channel 0-255
  public:

    //!
    //! \brief SpColor Default constructor. Builds full transparent black color
    //!
    SpColor() : mAlpha(0), mRed(0), mGreen(0), mBlue(0) {}

    //!
    //! \brief SpColor Constructor-conversion from QColor
    //! \param color   Source color
    //!
    SpColor( QColor color ) : mAlpha(color.alpha()), mRed(color.red()), mGreen(color.green()), mBlue(color.blue()) {}

    int     alpha() const { return mAlpha; }
    int     red() const { return mRed; }
    int     green() const { return mGreen; }
    int     blue() const { return mBlue; }


    //!
    //! \brief brightness Builds color with alpha channel equals br
    //! \param br         Coef for alpha 0-1.0 will produce alpha channel 0-255 accordingly
    //! \return           Color with new alpha channel
    //!
    SpColor brightness( float br ) const;

    //!
    //! \brief scale Change current alpha channel by multiply it to scale factor s and return resulting color
    //!              It make color more transparently
    //! \param s     Scale factor
    //! \return      Color with modified alpha channel
    //!
    SpColor scale( float s ) const;

    //!
    //! \brief color Convert color to QColor form
    //! \return      This color in form QColor
    //!
    QColor  color() const;

    //!
    //! \brief isEmpty Returns true if color fully transparent
    //! \return        true if color fully transparent
    //!
    bool    isEmpty() const { return mAlpha == 0; }

    //!
    //! \brief isOpacity Return true if color strong transparent. This used for filling
    //! \return          true if color strong transparent
    //!
    bool    isOpacity() const { return mAlpha < 120; }

    //!
    //! \brief append Mixes two colors: current and given
    //! \param color  Color to mix with current
    //!
    void    append( SpColor color );

    //!
    //! \brief invert Make inversion of current color
    //!
    void    invert();
  };


#endif // SPCOLOR_H
