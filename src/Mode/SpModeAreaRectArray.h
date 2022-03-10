#ifndef SPMODEAREARECTARRAY_H
#define SPMODEAREARECTARRAY_H

#include "SpModeArea.h"

class SpModeAreaRectArray : public SpModeArea
  {
    int mRowCount;
    int mColumnCount;
  public:
    SpModeAreaRectArray( int row, int column );

    // SpMode interface
  public:
    virtual void paint(SpImage &dest, QPoint p, QColor color) override;
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

#endif // SPMODEAREARECTARRAY_H
