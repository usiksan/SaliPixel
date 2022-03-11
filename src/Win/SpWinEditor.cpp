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

#include <QPainter>
#include <QMouseEvent>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>

SpWinEditor::SpWinEditor(QWidget *parent) :
  QWidget{parent},
  mMode{new SpModeIdle{} },
  mColor{Qt::black},
  mScale{20},
  mDirty{false}
  {
  mImage.resize( 32, 32 );
  mWork.set( mImage );

  setMouseTracking(true);
  }




bool SpWinEditor::canClose()
  {
  if( mDirty ) {
    int res = QMessageBox::question( this, tr("Warning!"), tr("Image changes not saved! Save?") );
    if( res == QMessageBox::No )
      return true;
    if( res == QMessageBox::Yes ) {
      cmFileSave();
      return !mDirty;
      }
    return false;
    }
  return true;
  }




void SpWinEditor::setMode(SpMode *md)
  {
  if( mMode != nullptr )
    delete mMode;
  mMode = md;
  if( mMode != nullptr )
    emit stepMessage( mMode->stepDescription() );
  update();
  }


void SpWinEditor::clear()
  {
  mPath.clear();
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
      mDirty = false;
      mImage.resize( dlgNew.imageWidth(), dlgNew.imageHeight() );
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
  else {
    mObjects.fileSave(mPath);
    }
  }



void SpWinEditor::cmFileSaveAs()
  {
  QString newPath = QFileDialog::getSaveFileName( this, tr("Enter file name for salipixel"), QString{}, QStringLiteral("SaliPixel files (*%1)").arg( QStringLiteral(SP_EXTENSION)) );
  if( !newPath.isEmpty() ) {
    if( newPath.endsWith( QStringLiteral(SP_EXTENSION) ) )
      mPath = newPath;
    else
      mPath = newPath + QStringLiteral(SP_EXTENSION);
    cmFileSave();
    }
  }




void SpWinEditor::cmFileExport()
  {
  QString newPath = QFileDialog::getSaveFileName( this, tr("Enter file name for image"), QString{}, QStringLiteral("PNG files (*.png)") );
  if( !newPath.isEmpty() ) {
    if( !newPath.endsWith( QStringLiteral(".png") ) )
      newPath.append( QStringLiteral(".png") );
    mImage.toImage().save( newPath );
    }
  }



void SpWinEditor::cmEditUndo()
  {
  mObjects.undo();
  if( mMode != nullptr )
    mMode->stepReset();
  mDirty = true;
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




void SpWinEditor::cmEditMove()
  {
  setMode( new SpModeAreaMove() );
  }


void SpWinEditor::cmEditRotate()
  {
  setMode( new SpModeAreaRotate() );
  }

void SpWinEditor::cmEditMirror()
  {
  setMode( new SpModeAreaMirror() );
  }

void SpWinEditor::cmEditRectArray()
  {
  SpDlgNew dlgDim(this);
  dlgDim.setup( tr("Enter array dimesions"), tr("Column count:"), tr("Row count:"), 2, 2 );
  if( dlgDim.exec() ) {
    setMode( new SpModeAreaRectArray( qBound( 1, dlgDim.valueWidth(), 32), qBound( 1, dlgDim.valueHeight(), 32 ) ) );
    }
  }



void SpWinEditor::cmEditRoundArray()
  {
  bool ok = true;
  int items = QInputDialog::getInt( this, tr("Enter round item count"), tr("Round item count:"), 2, 1, 100, 1, &ok );
  if( ok )
    setMode( new SpModeAreaRoundArray(items) );
  }



void SpWinEditor::cmEditScale()
  {
  setMode( new SpModeAreaScale() );
  }



void SpWinEditor::cmEditInsert()
  {

  }

void SpWinEditor::cmEditMovePoint()
  {
  setMode( new SpModeEditPoint( mObjects ) );
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




void SpWinEditor::cmDrawPoint()
  {
  setMode( new SpModePoint() );
  }

void SpWinEditor::cmDrawLine()
  {
  setMode( new SpModeLine() );
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
      mDirty = true;
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
  qDebug() << "delta" << delta;
  mScale = qBound( 1, mScale - delta, 32 );
  update();
  }
