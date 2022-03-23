#ifndef SPMODEPARALLELOGRAMM_H
#define SPMODEPARALLELOGRAMM_H

#include "SpMode.h"

class SpModeParallelogramm : public SpMode
  {
    QPoint mFirst;
    QPoint mSecond;
  public:
    SpModeParallelogramm();

    // SpMode interface
  public:
    //!
    //! \brief paint Called when contents of mode in dependence current mode step need to be paint
    //! \param dest  Destignation of image into which need to be drawen mode contents
    //! \param p     Current mouse point
    //! \param color Current selected color
    //!
    virtual void    paint(SpImage &dest, QPoint p, QColor color) override;
    virtual bool left(SpCmdList &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
  };

#endif // SPMODEPARALLELOGRAMM_H
