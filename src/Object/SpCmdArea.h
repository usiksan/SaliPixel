#ifndef SPCMDAREA_H
#define SPCMDAREA_H

#include "SpCmd.h"

class SpCmdArea : public SpCmd
  {
  protected:
    QPoint mSelect0;
    QPoint mSelect1;
  public:
    SpCmdArea() : SpCmd() {}
    SpCmdArea( QPoint s0, QPoint s1 );

    // SpCmd interface
  public:
    virtual void jsonWrite(SvJsonWriter &js) override;
    virtual void jsonRead(SvJsonReader &js) override;
  };

#endif // SPCMDAREA_H
