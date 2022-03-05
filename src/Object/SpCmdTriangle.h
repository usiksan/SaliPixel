#ifndef SPCMDTRIANGLE_H
#define SPCMDTRIANGLE_H

#include "SpCmd.h"

#define SP_CMD_TRIANGLE QStringLiteral("Triangle")

class SpCmdTriangle : public SpCmd
  {
    QPoint mVertex0;
    QPoint mVertex1;
    QPoint mVertex2;
  public:
    SpCmdTriangle() : SpCmd() {}
    SpCmdTriangle( QPoint vertex0, QPoint vertex1, QPoint vertex2, QColor color );

    // SpCmd interface
  public:
    virtual void    paint(SpImage &im) override;
    virtual QString id() const override { return SP_CMD_TRIANGLE; }
    virtual void    jsonWrite(SvJsonWriter &js) override;
    virtual void    jsonRead(SvJsonReader &js) override;
    virtual void    parsePoints(std::function<void (QPoint &)> parser) override;
  };

#endif // SPCMDTRIANGLE_H
