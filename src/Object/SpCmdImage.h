#ifndef SPCMDIMAGE_H
#define SPCMDIMAGE_H

#include "SpCmd.h"

#define SP_CMD_IMAGE QStringLiteral("Image")

class SpCmdImage : public SpCmd
  {
    QImage mImage;
    QPoint mPoint;
  public:
    SpCmdImage() : SpCmd() {}
    SpCmdImage(QPoint pos, QImage &im );

    // SpCmd interface
  public:
    virtual void    paint(SpImage &im) override;
    virtual QString id() const override { return SP_CMD_IMAGE; }
    virtual void    jsonWrite(SvJsonWriter &js) override;
    virtual void    jsonRead(SvJsonReader &js) override;
    virtual void    parsePoints(std::function<void (QPoint &)> parser) override;
  };

#endif // SPCMDIMAGE_H
