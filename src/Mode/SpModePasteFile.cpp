#include "SpConfig.h"
#include "SpModePasteFile.h"
#include "SpModeArea.h"
#include "Object/SpCmdImage.h"


#include <QObject>
#include <QFileDialog>

SpModePasteFile::SpModePasteFile() :
  SpMode(0),
  mImage( 8, 8, QImage::Format_ARGB32 )
  {

  }




void SpModePasteFile::paint(SpImage &dest, QPoint p, QColor color)
  {
  Q_UNUSED(color)
  dest.imagePaste( p - QPoint( mImage.width() / 2, mImage.height() / 2 ), mImage, SpModeArea::mDoOverride, true );
  }





QString SpModePasteFile::stepDescription()
  {
  return QObject::tr("Enter position to paste fragment");
  }





void SpModePasteFile::init(SpCmdList &objects, QWidget *parent)
  {
  Q_UNUSED(objects)
  mImage = QImage( 8, 8, QImage::Format_ARGB32 );
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





SpCmd *SpModePasteFile::object(QPoint p, QColor color)
  {
  Q_UNUSED(color)
  return new SpCmdImage( p, mImage, SpModeArea::mDoOverride );
  }
