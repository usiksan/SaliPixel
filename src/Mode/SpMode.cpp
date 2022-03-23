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

#include "SpMode.h"

//!
//! \brief SpMode  Constructor builds mode with predefined max step value
//! \param stepMax Max step for mode
//!
SpMode::SpMode( int stepMax ) :
  mStep{0},
  mStepMax{stepMax}
  {

  }



//!
//! \brief left  Called when left mouse button pressed. By default next step selected
//! \param dest  Current project command list
//! \param p     Mouse point where left button is pressed
//! \param color Current color
//! \return      true when new command appended to list
//!
bool SpMode::left(SpCmdList &dest, QPoint p, QColor color)
  {
  if( stepLast() ) {
    SpCmd *ptr = object( p, color );
    if( ptr != nullptr )
      dest.append( ptr );
    }
  return stepNext();
  }




//!
//! \brief right Called when right mouse button pressed. By default previous step selected
//!
void SpMode::right()
  {
  stepPrev();
  }



//!
//! \brief init    Inits mode with project command list. By default do nothing
//! \param objects Project command list
//! \param parent  Widget for show dialog for mode if need
//!
void SpMode::init(SpCmdList &objects, QWidget *parent)
  {
  Q_UNUSED(objects)
  Q_UNUSED(parent)
  }





//!
//! \brief object Build single object at last step of mode. If
//!               mode must generate more than one object then it need to be override left() function
//! \param p      Point at which last step appear
//! \param color  Current color
//! \return       Single object to insert into object list
//!
SpCmd *SpMode::object(QPoint p, QColor color)
  {
  Q_UNUSED(p)
  Q_UNUSED(color)
  return nullptr;
  }




//!
//! \brief stepNext Select next available step
//! \return         true if selected first step of mode (wrapping)
//!
bool SpMode::stepNext()
  {
  if( mStep < mStepMax ) {
    mStep++;
    return false;
    }
  mStep = 0;
  return true;
  }



//!
//! \brief stepPrev Select previous available step
//!
void SpMode::stepPrev()
  {
  if( mStep )
    mStep--;
  }
