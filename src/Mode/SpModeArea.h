/*
Project "Combine vector-pixel graphic editor for small image like icon"

Author
  Sibilev Alexander S.

Web
  www.saliLab.com
  www.saliLab.ru

Description
  SpModeArea base class for modes which operates with selected area.
  This base class holds first and second point of opposite corners
  of selected area.

  With global variables mDoXXX we control some behaviour of child classes
*/
#ifndef SPMODEAREA_H
#define SPMODEAREA_H

#include "SpMode.h"

class SpModeArea : public SpMode
  {
  protected:
    QPoint mFirst;  //!< First corner of selected area
    QPoint mSecond; //!< Second corner of selected area
  public:
    SpModeArea( int maxStep );

    static bool mDoCopy;     //!< If this true then image leave in source place of area, in else case source place cleared with transparent color
    static bool mDoOverride; //!< If this true then area fully overwrited previous image in new place of area, in else case area is added to previous image
    // SpMode interface
  public:
    //!
    //! \brief paint Called when contents of mode in dependence current mode step need to be paint
    //! \param dest  Destignation of image into which need to be drawen mode contents
    //! \param p     Current mouse point
    //! \param color Current selected color
    //!
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;

    //!
    //! \brief stepDescription Returns current step description for showing at status bar
    //! \return                Current step description
    //!
    virtual QString stepDescription() override;
  };

#endif // SPMODEAREA_H
