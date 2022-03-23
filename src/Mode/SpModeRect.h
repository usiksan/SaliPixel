#ifndef SPMODERECT_H
#define SPMODERECT_H

#include "SpModeLine.h"

class SpModeRect : public SpModeLine
  {
  public:
    SpModeRect();

    // SpMode interface
  public:
    //!
    //! \brief paint Called when contents of mode in dependence current mode step need to be paint
    //! \param dest  Destignation of image into which need to be drawen mode contents
    //! \param p     Current mouse point
    //! \param color Current selected color
    //!
    virtual void    paint( SpImage &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;

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

#endif // SPMODERECT_H
