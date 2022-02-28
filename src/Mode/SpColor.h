#ifndef SPCOLOR_H
#define SPCOLOR_H

#include <QColor>

#define SpColorInvalid 0
#define SpColorEmpty   1
#define SpColorSolid   2

struct SpColor {
    quint8 mMode;
    quint8 mRed;
    quint8 mGreen;
    quint8 mBlue;

    SpColor( quint8 mode = SpColorEmpty ) : mMode(mode), mRed(0), mGreen(0), mBlue(0) {}

    SpColor( QColor color ) : mMode(0), mRed(color.red()), mGreen(color.green()), mBlue(color.blue()) {}

    SpColor brightness( float br ) const;

    QColor  color() const;

    bool isValid() const { return mMode != SpColorInvalid; }

    bool isEmpty() const { return mMode == SpColorEmpty; }
  };


#endif // SPCOLOR_H
