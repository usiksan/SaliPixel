#include "SpConfig.h"
#include "SpWinEditor.h"
#include "SpDlgNew.h"
#include "Mode/SpMode.h"
#include "Mode/SpModeIdle.h"
#include "Mode/SpModePoint.h"
#include "Mode/SpModeLine.h"
#include "Mode/SpModeRect.h"
#include "Mode/SpModeCircle.h"
#include "Mode/SpModeCircle2.h"
#include "Mode/SpModeArc.h"
#include "Mode/SpModeArc2.h"
#include "Mode/SpModeTriangle.h"
#include "Mode/SpModeParallelogramm.h"
#include "Mode/SpModeRoundRect.h"
#include "Mode/SpModeFillRect.h"
#include "Mode/SpModeFillCircle.h"
#include "Mode/SpModeFill.h"

#include "Mode/SpModeClearPoint.h"
#include "Mode/SpModeClearRect.h"
#include "Mode/SpModeClearCircle.h"

#include "Mode/SpModeAreaMove.h"
#include "Mode/SpModeAreaRotate.h"
#include "Mode/SpModeAreaMirror.h"
#include "Mode/SpModeAreaRectArray.h"
#include "Mode/SpModeAreaRoundArray.h"
#include "Mode/SpModeAreaScale.h"

#include "Mode/SpModeEditPoint.h"
#include "Mode/SpModePasteFile.h"

#include <QPainter>
#include <QMouseEvent>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>

SpWinEditor::SpWinEditor(QWidget *parent) :
  QWidget{parent},
  mMode{ new SpModeIdle{} },
  mColor{Qt::black},
  mScale{20}
  {
  mImage.resize( 32, 32 );
  mWork.set( mImage );

  setMouseTracking(true);
  }




bool SpWinEditor::canClose()
  {
  if( mObjects.isDirty() ) {
    int res = QMessageBox::question( this, tr("Warning!"), tr("Image changes not saved! Save?") );
    if( res == QMessageBox::No )
      return true;
    if( res == QMessageBox::Yes ) {
      cmFileSave();
      return !mObjects.isDirty();
      }
    return false;
    }
  return true;
  }







void SpWinEditor::setMode( SpMode *md )
  {
  if( mMode != nullptr )
    delete mMode;
  mMode = md;
  if( mMode != nullptr ) {
    emit stepMessage( mMode->stepDescription() );
    mMode->init( mObjects, this );
    }
  update();
  }




void SpWinEditor::clear()
  {
  mPath.clear();
  emit fileName( mPath );
  mObjects.clear();
  if( mMode ) mMode->stepReset();
  mImage.clear();
  mWork = mImage;
  }




QPoint SpWinEditor::div20(QPoint p) const
  {
  return QPoint( p.x() / mScale, p.y() / mScale );
  }




void SpWinEditor::repaintObjects()
  {
  mObjects.paint( mImage );
  mWork = mImage;
  }




void SpWinEditor::cmFileNew()
  {
  if( canClose() ) {
    SpDlgNew dlgNew(this);
    if( dlgNew.exec() ) {
      mImage.resize( dlgNew.imageWidth(), dlgNew.imageHeight() );
      mObjects.setup( dlgNew.imageWidth(), dlgNew.imageHeight() );
      clear();
      update();
      }
    }
  }




void SpWinEditor::cmFileOpen()
  {
  if( canClose() ) {
    QString newPath = QFileDialog::getOpenFileName( this, tr("Enter file name for salipixel"), QString{}, QStringLiteral("SaliPixel files (*%1)").arg( QStringLiteral(SP_EXTENSION)) );
    if( !newPath.isEmpty() ) {
      if( mObjects.fileLoad(newPath) ) {
        mPath = newPath;
        emit fileName( mPath );
        repaintObjects();
        update();
        }
      }
    }
  }



void SpWinEditor::cmFileSave()
  {
  if( mPath.isEmpty() )
    cmFileSaveAs();
  else
    mObjects.fileSave(mPath);
  }



void SpWinEditor::cmFileSaveAs()
  {
  QString newPath = QFileDialog::getSaveFileName( this, tr("Enter file name for salipixel"), QString{}, QStringLiteral("SaliPixel files (*%1)").arg( QStringLiteral(SP_EXTENSION)) );
  if( !newPath.isEmpty() ) {
    if( newPath.endsWith( QStringLiteral(SP_EXTENSION) ) )
      mPath = newPath;
    else
      mPath = newPath + QStringLiteral(SP_EXTENSION);
    emit fileName( mPath );
    cmFileSave();
    }
  }




void SpWinEditor::cmFileExportPng()
  {
  QString defFile;
  QString extension( SP_EXTENSION );
  if( mPath.endsWith( extension ) ) {
    defFile = mPath.left( mPath.length() - extension.length() );
    defFile.append( ".png" );
    }
  QString newPath = QFileDialog::getSaveFileName( this, tr("Enter file name for image"), defFile, QStringLiteral("PNG files (*.png)") );
  if( !newPath.isEmpty() ) {
    if( !newPath.endsWith( QStringLiteral(".png") ) )
      newPath.append( QStringLiteral(".png") );
    mImage.toImage().save( newPath );
    }
  }




void SpWinEditor::cmFileExportCpp()
  {
  QString defFile;
  QString extension( SP_EXTENSION );
  if( mPath.endsWith( extension ) ) {
    defFile = mPath.left( mPath.length() - extension.length() );
    defFile.append( ".h" );
    }
  QString newPath = QFileDialog::getSaveFileName( this, tr("Enter file name for C header"), defFile, QStringLiteral("C header files (*.h)") );
  if( !newPath.isEmpty() ) {
    if( !newPath.endsWith( QStringLiteral(".h") ) )
      newPath.append( QStringLiteral(".h") );
    //Conversion to text cpp
    //Image convertor to internal storage format used in embedded systems to display on tft
    //
    //Image is packed into array of 16-bit unsigned ints.
    //First two values in array - width and height of image
    //Next are pixels of image line by line from left to right
    //
    //Here we convert image into h file to include into source code of embedded system
    quint16 buf[512*512];

    //Формат цвета rgb565
    #define SvRgb565( r, g, b) ( ((b) << 8) | ((r) << 3) | ((g) >> 3) | (((g) << 13) & 0xe000) )
    #define svColorTransparent 0x2000
    #define svColorGreenNoTransparent 0x4000

    //Образовать имя для целевого файла
    QFile dest(newPath);
    if( dest.open(QIODevice::WriteOnly) ) {
      //Записать размеры
      int w = mImage.width();
      int h = mImage.height();
      if( w <= 0 || w > 512 || h <= 0 || h > 512 ) {
        QMessageBox::warning( this, tr("Error!"), tr("Wrong size of picture, max 512x512 but it %1x%2").arg(w).arg(h) );
        return;
        }
      buf[0] = w;
      buf[1] = h;
      int i = 2;
      for( int y = 0; y < h; y++ )
        for( int x = 0; x < w; x++ ) {
          //Получим пиксель
          SpColor pixel = mImage.pixelGet( x, y );
          //Выделим цвета пикселя
          int red   = pixel.red() * pixel.alpha() / 255;
          int green = pixel.green() * pixel.alpha() / 255;
          int blue  = pixel.blue() * pixel.alpha() / 255;
          if( pixel.alpha() <= 120 )
            //Прозрачный пиксель, записать прозрачный цвет
            buf[i++] = svColorTransparent;
          else {
            //Пиксель непрозрачный
            //Упаковать пиксель в формат rgb565
            quint16 rgb565 = SvRgb565( red >> 3, green >> 2, blue >> 3 );
            //Проверим, чтобы результирующий цвет не попал в разряд прозрачных
            if( rgb565 == svColorTransparent )
              rgb565 = svColorGreenNoTransparent;
            buf[i++] = rgb565;
            }
          }
      //Буфер заполнен
      //Вывести таблицей по 16 значений
      QTextStream out( &dest );
      for( int k = 0; k < i; k++ ) {
        if( k ) out << QStringLiteral(",\n");
        out << QString("0x%1").arg( buf[k], 4, 16, QChar('0') );
        }
      }
    }
  }



void SpWinEditor::cmEditUndo()
  {
  mObjects.undo();
  if( mMode != nullptr )
    mMode->stepReset();
  repaintObjects();
  update();
  }



void SpWinEditor::cmEditCopyToggle(bool state)
  {
  SpModeArea::mDoCopy = state;
  update();
  }

void SpWinEditor::cmEditOverrideToggle(bool state)
  {
  SpModeArea::mDoOverride = state;
  update();
  }











void SpWinEditor::cmEditInsert()
  {

  }




void SpWinEditor::cmDrawColor()
  {
  mColor = QColorDialog::getColor( mColor, this, tr("Select draw color") );
  update();
  }



void SpWinEditor::cmDrawBaseColor()
  {
  QColor clr = QColorDialog::getColor( mColor, this, tr("Select draw color") );
  if( clr.isValid() ) {
    mImage.clear();
    mObjects.forEach( [this, clr] ( SpCmd *ptr ) {
      ptr->setColor( clr );
      ptr->paint( mImage );
      });
    mWork = mImage;
    update();
    }
  }





void SpWinEditor::cmDrawRect()
  {
  setMode( new SpModeRect() );
  }

void SpWinEditor::cmDrawArc()
  {
  setMode( new SpModeArc() );
  }

void SpWinEditor::cmDrawArc2()
  {
  setMode( new SpModeArc2() );
  }

void SpWinEditor::cmDrawCircle()
  {
  setMode( new SpModeCircle() );
  }

void SpWinEditor::cmDrawCircle2()
  {
  setMode( new SpModeCircle2() );
  }

void SpWinEditor::cmDrawTriangle()
  {
  setMode( new SpModeTriangle() );
  }

void SpWinEditor::cmDrawParallelogramm()
  {
  setMode( new SpModeParallelogramm() );
  }

void SpWinEditor::cmDrawRoundRect()
  {
  setMode( new SpModeRoundRect() );
  }

void SpWinEditor::cmDrawFillRect()
  {
  setMode( new SpModeFillRect() );
  }

void SpWinEditor::cmDrawFillCircle()
  {
  setMode( new SpModeFillCircle() );
  }

void SpWinEditor::cmDrawFill()
  {
  setMode( new SpModeFill() );
  }

void SpWinEditor::cmClearPoint()
  {
  setMode( new SpModeClearPoint() );
  }

void SpWinEditor::cmClearRect()
  {
  setMode( new SpModeClearRect() );
  }

void SpWinEditor::cmClearCircle()
  {
  setMode( new SpModeClearCircle{} );
  }





void SpWinEditor::paintEvent(QPaintEvent *event)
  {
  Q_UNUSED(event)
  QPainter painter(this);

  //Content
  for( int x = 0; x < mWork.width(); x++ )
    for( int y = 0; y < mWork.height(); y++ ) {
      auto pixel = mWork.pixelGet( x, y );
      QColor color;
      if( pixel.isEmpty() )
        color = y & 1 ? (x & 1 ? Qt::white : Qt::lightGray) : (x & 1 ? Qt::lightGray : Qt::white);
      else
        color = pixel.color();
      painter.setPen( color );
      painter.setBrush( QBrush( color ) );
      painter.drawRect( x * mScale, y * mScale, mScale, mScale );
      }

  //Icon miniature
  painter.drawImage( width() - mWork.width(), 0, mWork.toImage() );

  //Draw current color
  painter.setBrush( QBrush( mColor ) );
  painter.drawRect( width() - 32, height() - 32, 32, 32 );

  //Draw cmd points
  if( mMode != nullptr && mMode->showPoints() && mScale >= 4 ) {
    int scale(mScale);
    auto drawer = [&painter,scale] ( QPoint &p ) {
      painter.drawEllipse( p.x() * scale + 2, p.y() * scale + 2, scale - 2, scale - 2 );
      };
    painter.setPen( QColor(Qt::red) );
    painter.setBrush( QColor(Qt::green) );
    mObjects.parsePoints( drawer );
    }

  //Grid
  if( mScale >= 3 ) {
    painter.setPen( Qt::gray );
    int h = mWork.height() * mScale;
    //Vertical lines
    for( int x = 0; x <= mWork.width(); x++ )
      painter.drawLine( x * mScale, 0, x * mScale, h );
    //Horizontal lines
    int w = mWork.width() * mScale;
    for( int y = 0; y <= mWork.height(); y++ )
      painter.drawLine( 0, y * mScale, w, y * mScale );

    //x4 lines
    painter.setPen( Qt::blue );
    for( int x = 4; x < mWork.width(); x += 4 )
      painter.drawLine( x * mScale, 0, x * mScale, h );
    for( int y = 4; y <= mWork.height(); y += 4 )
      painter.drawLine( 0, y * mScale, w, y * mScale );

    }



  }




void SpWinEditor::mousePressEvent(QMouseEvent *event)
  {
  //Nothing done if no any mode
  if( mMode == nullptr )
    return;

  if( event->button() == Qt::LeftButton ) {
    if( QRect( width() - 32, height() - 32, 32, 32 ).contains( event->pos() ) ) {
      cmDrawColor();
      return;
      }
    if( mPoint != div20( event->pos() ) )
      mouseMoveEvent( event );
    if( mMode->left( mObjects, mPoint, mColor ) ) {
      //Apply current
      mImage.set( mWork );
      }
    }
  else if( event->button() == Qt::RightButton ) {
    mMode->right();
    }

  //Setup new step message after button clicked
  emit stepMessage( mMode->stepDescription() );
  }




void SpWinEditor::mouseMoveEvent(QMouseEvent *event)
  {
  mPoint = div20( event->pos() );
  mWork.set( mImage );
  if( mMode != nullptr ) {
    mMode->paint( mWork, mPoint, mColor );
    update();
    }
  }


void SpWinEditor::wheelEvent(QWheelEvent *event)
  {
  int delta = event->angleDelta().y() / 120;
  //qDebug() << "delta" << delta;
  mScale = qBound( 1, mScale - delta, 32 );
  update();
  }
