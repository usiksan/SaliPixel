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
    virtual void    paint(SpImage &dest, QPoint p, QColor color) override;
    virtual QString stepDescription() override;
    virtual void init(SpCmdList &objects, QWidget *parent) override;
    virtual QString iconName() const override;
    virtual QString menuName() const override;

    // SpMode interface
  protected:
    virtual SpCmd *object(QPoint p, QColor color) override;
  };

#endif // SPMODEPASTEFILE_H
