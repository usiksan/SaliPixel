#ifndef SPCMDLINE_H
#define SPCMDLINE_H

#include "SpCmd.h"

#define SP_CMD_LINE QStringLiteral("Line")

class SpCmdLine : public SpCmd
  {
    QPoint mStart;
    QPoint mStop;
  public:
    SpCmdLine();
    SpCmdLine( QPoint ps, QPoint pe, QColor color ) : SpCmd{color}, mStart{ps}, mStop{pe} {}

    // SpCmd interface
  public:
    virtual void    paint(SpImage &im) override;
    virtual QString id() const override { return SP_CMD_LINE; }
    virtual void    jsonWrite(SvJsonWriter &js) override;
    virtual void    jsonRead(SvJsonReader &js) override;
  };

#endif // SPCMDLINE_H
