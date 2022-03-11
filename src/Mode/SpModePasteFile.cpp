#include "SpConfig.h"
#include "SpModePasteFile.h"
#include "Object/SpCmdImage.h"


#include <QObject>
#include <QFileDialog>

SpModePasteFile::SpModePasteFile() :
  SpMode(0)
  {

  }




void SpModePasteFile::paint(SpImage &dest, QPoint p, QColor color)
  {
  Q_UNUSED(color)
  dest.imagePaste( p, mImage );
  }



bool SpModePasteFile::left(SpCmdList &dest, QPoint p, QColor color)
  {
  }



QString SpModePasteFile::stepDescription()
  {
  }



void SpModePasteFile::init(SpCmdList &objects, QWidget *parent)
  {
  Q_UNUSED(objects)
  mImage = QImage( 2, 2, QImage::Format_ARGB32 );
  mImage.fill( QColor(0,0,0,0) );
  QString fname = QFileDialog::getOpenFileName( parent, QObject::tr("Enter file name for paste"), QString{}, QStringLiteral("Image files (*.png); SaliPixel files (*%1)").arg( QStringLiteral(SP_EXTENSION)));
  if( !fname.isEmpty() ) {
    if( fname.endsWith(QStringLiteral(SP_EXTENSION)) ) {
      QFile file(fname);
      SpCmdList objs;
      if( objs.fileLoad( fname ) ) {
        SpImage im;
        objs.paint( im );
        mImage = im.toImage();
        }
      }
    }
  }




QString SpModePasteFile::iconName() const
  {
  return QStringLiteral("editPasteFile.png");
  }



QString SpModePasteFile::menuName() const
  {
  return QObject::tr("Paste file...");
  }




SpCmd *SpModePasteFile::object(QPoint p, QColor color)
  {
  Q_UNUSED(color)
  return new SpCmdImage( p, mImage );
  }
