/*
Project "Combine vector-pixel graphic editor for small image like icon"

Author
  Sibilev Alexander S.

Web
  www.saliLab.com
  www.saliLab.ru

Description
  SpMode base class for all edit and drawing modes

  Each mode represents one operation, for example drawing line
  Each operation can consists from on to more steps. For example,
  drawing line consists from two steps: at first step need to enter
  start point of line at second step need to enter end point of line.
*/
#ifndef SPMODE_H
#define SPMODE_H

#include "SpImage.h"
#include "Object/SpCmd.h"
#include "Object/SpCmdList.h"

class QWidget;

class SpMode
  {
  protected:
    int mStep;    //!< Current step index
    int mStepMax; //!< Max step for mode. Each mode has own count of steps
  public:
    //!
    //! \brief SpMode  Constructor builds mode with predefined max step value
    //! \param stepMax Max step for mode
    //!
    SpMode( int stepMax );
    virtual ~SpMode() {}

    //!
    //! \brief showPoints Some modes allow deal with end points of figures. For such modes this function must return true
    //! \return           true for modes which deal with end points of figures and false for others
    //!
    virtual bool    showPoints() const { return false; }

    //!
    //! \brief paint Called when contents of mode in dependence current mode step need to be paint
    //! \param dest  Destignation of image into which need to be drawen mode contents
    //! \param p     Current mouse point
    //! \param color Current selected color
    //!
    virtual void    paint( SpImage &dest, QPoint p, QColor color ) = 0;

    //!
    //! \brief left  Called when left mouse button pressed. By default next step selected
    //! \param dest  Current project command list
    //! \param p     Mouse point where left button is pressed
    //! \param color Current color
    //! \return      true when new command appended to list
    //!
    virtual bool    left( SpCmdList &dest, QPoint p, QColor color );

    //!
    //! \brief right Called when right mouse button pressed. By default previous step selected
    //!
    virtual void    right();

    //!
    //! \brief stepDescription Returns current step description for showing at status bar
    //! \return                Current step description
    //!
    virtual QString stepDescription() = 0;

    //!
    //! \brief stepReset Jump to first step of mode
    //!
    void            stepReset() { mStep = 0; }

    //!
    //! \brief init    Inits mode with project command list. By default do nothing
    //! \param objects Project command list
    //! \param parent  Widget for show dialog for mode if need
    //!
    virtual void    init( SpCmdList &objects, QWidget *parent );

  protected:

    //!
    //! \brief object Build single object at last step of mode. If
    //!               mode must generate more than one object then it need to be override left() function
    //! \param p      Point at which last step appear
    //! \param color  Current color
    //! \return       Single object to insert into object list
    //!
    virtual SpCmd  *object( QPoint p, QColor color );

    //!
    //! \brief stepLast Return true if current step is last step
    //! \return         true if current step is last step
    //!
    bool            stepLast() const { return mStep == mStepMax; }

    //!
    //! \brief stepNext Select next available step
    //! \return         true if selected first step of mode (wrapping)
    //!
    bool            stepNext();

    //!
    //! \brief stepPrev Select previous available step
    //!
    void            stepPrev();
  };

#endif // SPMODE_H
