#ifndef SPMODEEDITPOINT_H
#define SPMODEEDITPOINT_H

#include "SpMode.h"
#include "Object/SpCmd.h"


class SpModeEditPoint : public SpMode
  {
    SpCmdPtrList   &mObjects;
    QList<QPoint*>  mSelection;
    QPoint          mSource;
  public:
    SpModeEditPoint( SpCmdPtrList &objs );

    // SpMode interface
  public:
    virtual bool     showPoints() const override { return true; }
    virtual void     paint(SpImage &dest, QPoint p, QColor color) override;
    virtual bool     left() override;
    virtual void     right() override;
    virtual QString  stepDescription() override;
  };

#endif // SPMODEEDITPOINT_H