#ifndef SPMODEPASTEFILE_H
#define SPMODEPASTEFILE_H

#include "SpMode.h"

class SpModePasteFile : public SpMode
  {
    QImage mImage; //!< Image to paste
  public:
    SpModePasteFile();

    // SpMode interface
  public:
    //!
    //! \brief paint Called when contents of mode in dependence current mode step need to be paint
    //! \param dest  Destignation of image into which need to be drawen mode contents
    //! \param p     Current mouse point
    //! \param color Current selected color
    //!
    virtual void    paint(SpImage &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
    virtual void    init(SpCmdList &objects, QWidget *parent) override;

    // SpMode interface
  protected:
    virtual SpCmd *object(QPoint p, QColor color) override;
  };

#endif // SPMODEPASTEFILE_H
