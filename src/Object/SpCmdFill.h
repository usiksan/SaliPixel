#ifndef SPCMDFILL_H
#define SPCMDFILL_H

#include "SpCmd.h"

#define SP_CMD_FILL QStringLiteral("Fill")

class SpCmdFill : public SpCmd
  {
    QPoint mSource;
  public:
    SpCmdFill() : SpCmd() {}
    SpCmdFill( QPoint source, QColor color );

    // SpCmd interface
  public:
    virtual void    paint(SpImage &im) override;
    virtual QString id() const override { return SP_CMD_FILL; }
    virtual void    jsonWrite(SvJsonWriter &js) override;
    virtual void    jsonRead(SvJsonReader &js) override;
  };

#endif // SPCMDFILL_H
