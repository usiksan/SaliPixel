/*
Project "Combine vector-pixel graphic editor for small image like icon"

Author
  Sibilev Alexander S.

Web
  www.saliLab.com
  www.saliLab.ru

Description
  SpModeClearCircle fill Circle with selected color mode. At first step we select center of circle
  at second step we define radius of circle by any point on circle
*/
#ifndef SPMODEFILLCIRCLE_H
#define SPMODEFILLCIRCLE_H

#include "SpModeCircle.h"

class SpModeFillCircle : public SpModeCircle
  {
  public:
    SpModeFillCircle();

    // SpMode interface
  public:
    //!
    //! \brief paint Called when contents of mode in dependence current mode step need to be paint
    //! \param dest  Destignation of image into which need to be drawen mode contents
    //! \param p     Current mouse point
    //! \param color Current selected color
    //!
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;

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

#endif // SPMODEFILLCIRCLE_H
