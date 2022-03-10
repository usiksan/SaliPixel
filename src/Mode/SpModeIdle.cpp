#include "SpModeIdle.h"

#include <QObject>

SpModeIdle::SpModeIdle() :
  SpMode{0}
  {

  }


void SpModeIdle::paint(SpImage &dest, QPoint p, QColor color)
  {
  Q_UNUSED(dest)
  Q_UNUSED(p)
  Q_UNUSED(color)
  }



bool SpModeIdle::left(SpCmdPtrList &dest, QPoint p, QColor color)
  {
  Q_UNUSED(dest)
  Q_UNUSED(p)
  Q_UNUSED(color)
  return false;
  }




QString SpModeIdle::stepDescription()
  {
  return QObject::tr("Select drawing mode");
  }


