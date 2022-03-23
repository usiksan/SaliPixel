#ifndef SPMODEAREA_H
#define SPMODEAREA_H

#include "SpMode.h"

class SpModeArea : public SpMode
  {
  protected:
    QPoint mFirst;
    QPoint mSecond;
  public:
    SpModeArea( int maxStep );

    static bool mDoCopy;
    static bool mDoOverride;
    // SpMode interface
  public:
    //!
    //! \brief paint Called when contents of mode in dependence current mode step need to be paint
    //! \param dest  Destignation of image into which need to be drawen mode contents
    //! \param p     Current mouse point
    //! \param color Current selected color
    //!
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
  };

#endif // SPMODEAREA_H
