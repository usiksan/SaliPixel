#ifndef SPCMDAREA_H
#define SPCMDAREA_H

#include "SpCmd.h"

class SpCmdArea : public SpCmd
  {
  protected:
    QPoint mSelect0;
    QPoint mSelect1;
  public:
    SpCmdArea( QPoint s0, QPoint s1 );
  };

#endif // SPCMDAREA_H
