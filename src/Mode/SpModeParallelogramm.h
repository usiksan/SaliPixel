/*
Project "Combine vector-pixel graphic editor for small image like icon"

Author
  Sibilev Alexander S.

Web
  www.saliLab.com
  www.saliLab.ru

Description
  SpModeParallelogramm parallelogramm drawing mode. At first step we define first corner of parallelogramm
  at second step we define second corner of parallelogramm at third step we define third corner of parallelogramm
*/
#ifndef SPMODEPARALLELOGRAMM_H
#define SPMODEPARALLELOGRAMM_H

#include "SpMode.h"

class SpModeParallelogramm : public SpMode
  {
    QPoint mFirst;  //!< First point of parallelogramm
    QPoint mSecond; //!< Second point of parallolgramm
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

    //!
    //! \brief left  Called when left mouse button pressed. By default next step selected
    //! \param dest  Current project command list
    //! \param p     Mouse point where left button is pressed
    //! \param color Current color
    //! \return      true when new command appended to list
    //!
    virtual bool    left(SpCmdList &dest, QPoint p, QColor color) override;

    //!
    //! \brief stepDescription Returns current step description for showing at status bar
    //! \return                Current step description
    //!
    virtual QString stepDescription() override;
  };

#endif // SPMODEPARALLELOGRAMM_H
