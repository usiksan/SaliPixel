#ifndef SPCOLOR_H
#define SPCOLOR_H

#include <QColor>

class SpColor {
    quint8 mAlpha; //!< 0 - opacity, not 0 - colored
    quint8 mRed;
    quint8 mGreen;
    quint8 mBlue;
  public:

    SpColor() : mAlpha(0), mRed(0), mGreen(0), mBlue(0) {}

    SpColor( QColor color ) : mAlpha(color.alpha()), mRed(color.red()), mGreen(color.green()), mBlue(color.blue()) {}

    SpColor brightness( float br ) const;

    SpColor scale( float s ) const;

    QColor  color() const;

    bool isEmpty() const { return mAlpha == 0; }

    bool isOpacity() const { return mAlpha < 120; }

    void append( SpColor color );

    void invert();

    int  alphaRed() const { return mRed * mAlpha; }

    int  alphaGreen() const { return mGreen * mAlpha; }

    int  alphaBlue() const { return mBlue * mAlpha; }
  };


#endif // SPCOLOR_H
