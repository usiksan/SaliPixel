#ifndef SPMODEAREAROUNDARRAY_H
#define SPMODEAREAROUNDARRAY_H

#include "SpModeArea.h"

class SpModeAreaRoundArray : public SpModeArea
  {
    QPoint mCenter;
    int    mItemCount;
  public:
    SpModeAreaRoundArray();

    // SpMode interface
  public:
    //!
    //! \brief paint Called when contents of mode in dependence current mode step need to be paint
    //! \param dest  Destignation of image into which need to be drawen mode contents
    //! \param p     Current mouse point
    //! \param color Current selected color
    //!
    virtual void    paint(SpImage &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
    virtual void init(SpCmdList &objects, QWidget *parent) override;

    // SpMode interface
  protected:
    //!
    //! \brief object Build single object at last step of mode. If
    //!               mode must generate more than one object then it need to be override left() function
    //! \param p      Point at which last step appear
    //! \param color  Current color
    //! \return       Single object to insert into object list
    //!
    virtual SpCmd  *object(QPoint p, QColor color) override;
  };

#endif // SPMODEAREAROUNDARRAY_H
