#include "SpWinEditor.h"
#include "Mode/SpMode.h"
#include "Mode/SpModePoint.h"
#include "Mode/SpModeLine.h"
#include "Mode/SpModeRect.h"

#include <QPainter>
#include <QMouseEvent>

SpWinEditor::SpWinEditor(QWidget *parent) :
  QWidget{parent},
  mMode{nullptr},
  mColor{Qt::black}
  {
  mImage.resize( 32, 32 );
  mWork.set( mImage );

  setMouseTracking(true);
  }




bool SpWinEditor::canClose()
  {
  return true;
  }




void SpWinEditor::setMode(SpMode *md)
  {
  if( mMode != nullptr )
    delete mMode;
  mMode = md;
  if( mMode != nullptr )
    emit stepMessage( mMode->stepDescription() );
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
      painter.drawRect( x * 20, y * 20, 20, 20 );
      }
//  for( int x = 0; x < mWork.width(); x++ )
//    for( int y = 0; y < mWork.height(); y++ ) {
//      auto pixel = mWork.pixel( x, y );
//      painter.setPen( QColor(pixel) );
//      painter.setBrush( QBrush( pixel ) );
//      painter.drawRect( x * 20, y * 20, 20, 20 );
//      }

  //Icon miniature
  //painter.drawImage( width() - mWork.width(), 0, mWork );

  //Grid
  painter.setPen( Qt::gray );
  int h = mWork.height() * 20;
  //Vertical lines
  for( int x = 0; x < mWork.width(); x++ )
    painter.drawLine( x * 20, 0, x * 20, h );
  //Horizontal lines
  int w = mWork.width() * 20;
  for( int y = 0; y < mWork.height(); y++ )
    painter.drawLine( 0, y * 20, w, y * 20 );

  }


QPoint div20( QPoint p )
  {
  return QPoint( p.x() / 20, p.y() / 20 );
  }


void SpWinEditor::mousePressEvent(QMouseEvent *event)
  {
  //Nothing done if no any mode
  if( mMode == nullptr )
    return;

  if( event->button() == Qt::LeftButton ) {
    if( mPoint != div20( event->pos() ) )
      mouseMoveEvent( event );
    if( mMode->left() ) {
      //Append to undo
//      if( mUndo.count() >= 30 )
//        mUndo.pop_front();
//      mUndo.push_back( mImage );
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
