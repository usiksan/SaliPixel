/*
Project "Combine vector-pixel graphic editor for small image like icon"

Author
  Sibilev Alexander S.

Web
  www.saliLab.com
  www.saliLab.ru

Description
  SpModeEditPoint this mode allow transfer some key point of drawing figures (see SpCmd ierarhy) and so
  change its geometry and position. At first we select points to transfer by point on it at second
  we transfer selected points to new place
*/
#ifndef SPMODEEDITPOINT_H
#define SPMODEEDITPOINT_H

#include "SpMode.h"
#include "Object/SpCmd.h"
#include "Object/SpCmdList.h"


class SpModeEditPoint : public SpMode
  {
    SpCmdList      *mObjects;   //!< List of all drawing figures of project
    QList<QPoint*>  mSelection; //!< List of selected points
    QPoint          mSource;    //!< Source point from which made transfer
  public:
    SpModeEditPoint();

    // SpMode interface
  public:
    virtual bool     showPoints() const override { return true; }
    //!
    //! \brief paint Called when contents of mode in dependence current mode step need to be paint
    //! \param dest  Destignation of image into which need to be drawen mode contents
    //! \param p     Current mouse point
    //! \param color Current selected color
    //!
    virtual void     paint(SpImage &dest, QPoint p, QColor color) override;

    //!
    //! \brief left  Called when left mouse button pressed. By default next step selected
    //! \param dest  Current project command list
    //! \param p     Mouse point where left button is pressed
    //! \param color Current color
    //! \return      true when new command appended to list
    //!
    virtual bool     left(SpCmdList &dest, QPoint p, QColor color) override;

    //!
    //! \brief right Called when right mouse button pressed. By default previous step selected
    //!
    virtual void     right() override;

    //!
    //! \brief stepDescription Returns current step description for showing at status bar
    //! \return                Current step description
    //!
    virtual QString  stepDescription() override;

    //!
    //! \brief init    Inits mode with project command list. By default do nothing
    //! \param objects Project command list
    //! \param parent  Widget for show dialog for mode if need
    //!
    virtual void     init(SpCmdList &objects, QWidget *parent) override;
  };

#endif // SPMODEEDITPOINT_H
