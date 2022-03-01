#ifndef SPCOLOR_H
#define SPCOLOR_H

#include <QColor>

struct SpColor {
    quint8 mAlpha;
    quint8 mRed;
    quint8 mGreen;
    quint8 mBlue;

    SpColor() : mAlpha(0), mRed(0), mGreen(0), mBlue(0) {}

    SpColor( QColor color ) : mAlpha(color.alpha()), mRed(color.red()), mGreen(color.green()), mBlue(color.blue()) {}

    SpColor brightness( float br ) const;

    QColor  color() const;

    bool isEmpty() const { return mAlpha == 0; }

    bool isOpacity() const { return mAlpha < 120; }

    void append( SpColor color );
  };


#endif // SPCOLOR_H
