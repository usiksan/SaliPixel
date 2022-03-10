#ifndef SPMODE_H
#define SPMODE_H

#include "SpImage.h"
#include "Object/SpCmd.h"

class SpCmd;

class SpMode
  {
  protected:
    int mStep;
    int mStepMax;
  public:
    SpMode( int stepMax );
    virtual ~SpMode() {}

    virtual bool    showPoints() const { return false; }

    virtual void    paint( SpImage &dest, QPoint p, QColor color ) = 0;

    virtual bool    left( SpCmdPtrList &dest, QPoint p, QColor color );

    virtual void    right();

    virtual QString stepDescription() = 0;

    void            stepReset() { mStep = 0; }

  protected:

    //!
    //! \brief object Build single object at last step of mode. If
    //!               mode must generate more than one object then it need to be override left() function
    //! \param p      Point at which last step appear
    //! \param color  Current color
    //! \return       Single object to insert into object list
    //!
    virtual SpCmd  *object( QPoint p, QColor color );

    bool            stepLast() const { return mStep == mStepMax; }

    bool            stepNext();

    void            stepPrev();
  };

#endif // SPMODE_H
