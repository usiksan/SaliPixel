/*
Project "Combine vector-pixel graphic editor for small image like icon"

Author
  Sibilev Alexander S.

Web
  www.saliLab.com
  www.saliLab.ru

Description
  SpModeAreaMirror mirror area mode. Selected area mirrored regarding auxiliary mirror line
*/
#ifndef SPMODEAREAMIRROR_H
#define SPMODEAREAMIRROR_H

#include "SpModeArea.h"

class SpModeAreaMirror : public SpModeArea
  {
    QPoint mMirrorLine; //!< First point of mirror line regarding which image mirrored
  public:
    SpModeAreaMirror();

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

#endif // SPMODEAREAMIRROR_H
