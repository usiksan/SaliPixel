#ifndef SPMODEIDLE_H
#define SPMODEIDLE_H

#include "SpMode.h"

class SpModeIdle : public SpMode
  {
  public:
    SpModeIdle();

    // SpMode interface
  public:
    //!
    //! \brief paint Called when contents of mode in dependence current mode step need to be paint
    //! \param dest  Destignation of image into which need to be drawen mode contents
    //! \param p     Current mouse point
    //! \param color Current selected color
    //!
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual bool left(SpCmdList &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
  };

#endif // SPMODEIDLE_H
