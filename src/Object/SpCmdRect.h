#ifndef SPCMDRECT_H
#define SPCMDRECT_H

#include "SpCmd.h"

#define SP_CMD_RECT QStringLiteral("Rect")

class SpCmdRect : public SpCmd
  {
  protected:
    QPoint mFirst;
    QPoint mSecond;
  public:
    SpCmdRect();
    SpCmdRect( QPoint f, QPoint s, QColor color ) : SpCmd{color}, mFirst{f}, mSecond{s} {}


    // SpCmd interface
  public:
    virtual void    paint(SpImage &im) override;
    virtual QString id() const override { return SP_CMD_RECT; }
    virtual void    jsonWrite(SvJsonWriter &js) override;
    virtual void    jsonRead(SvJsonReader &js) override;
  };

#endif // SPCMDRECT_H
