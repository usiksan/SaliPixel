#ifndef SPMODEEDITPOINT_H
#define SPMODEEDITPOINT_H

#include "SpMode.h"
#include "Object/SpCmd.h"
#include "Object/SpCmdList.h"


class SpModeEditPoint : public SpMode
  {
    SpCmdList      *mObjects;
    QList<QPoint*>  mSelection;
    QPoint          mSource;
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
    virtual bool     left(SpCmdList &dest, QPoint p, QColor color) override;
    virtual void     right() override;
    virtual QString  stepDescription() override;
    virtual void     init(SpCmdList &objects, QWidget *parent) override;
  };

#endif // SPMODEEDITPOINT_H
