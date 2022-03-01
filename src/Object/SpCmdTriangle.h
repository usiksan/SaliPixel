#ifndef SPCMDTRIANGLE_H
#define SPCMDTRIANGLE_H

#include "SpCmd.h"

class SpCmdTriangle : public SpCmd
  {
    QPoint mVertex0;
    QPoint mVertex1;
    QPoint mVertex2;
  public:
    SpCmdTriangle( QPoint vertex0, QPoint vertex1, QPoint vertex2, QColor color );

    // SpCmd interface
  public:
    virtual void paint(SpImage &im) override;
  };

#endif // SPCMDTRIANGLE_H
