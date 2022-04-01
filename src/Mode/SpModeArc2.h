/*
Project "Combine vector-pixel graphic editor for small image like icon"

Author
  Sibilev Alexander S.

Web
  www.saliLab.com
  www.saliLab.ru

Description
  SpModeArc2 arc drawing mode. Arc drawn throught first point of arc, end point of arc and center of
  arc which define radius of arc.
*/
#ifndef SPMODEARC2_H
#define SPMODEARC2_H

#include "SpMode.h"

class SpModeArc2 : public SpMode
  {
    QPoint mCenter; //!< Center point of arc
    QPoint mStart;  //!< Start of arc
    QPoint mStop;   //!< End of arc
  public:
    SpModeArc2();

    // SpMode interface
  public:
    //!
    //! \brief paint Called when contents of mode in dependence current mode step need to be paint
    //! \param dest  Destignation of image into which need to be drawen mode contents
    //! \param p     Current mouse point
    //! \param color Current selected color
    //!
    virtual void    paint(SpImage &dest, QPoint p, QColor color) override;

    //!
    //! \brief stepDescription Returns current step description for showing at status bar
    //! \return                Current step description
    //!
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

#endif // SPMODEARC2_H
