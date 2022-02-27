#include "SpWinEditor.h"
#include "Mode/SpMode.h"
#include "Mode/SpModePoint.h"
#include "Mode/SpModeLine.h"
#include "Mode/SpModeRect.h"

#include <QPainter>
#include <QMouseEvent>

SpWinEditor::SpWinEditor(QWidget *parent) :
  QWidget{parent},
  //mWork{32,32,QImage::Format_ARGB32},
  mImage{32,32,QImage::Format_ARGB32},
  mMode{nullptr},
  mColor{Qt::black}
  {
  mImage.fill( Qt::white );
  mWork = mImage;

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
      auto pixel = mWork.pixel( x, y );
      painter.setPen( QColor(pixel) );
      painter.setBrush( QBrush( pixel ) );
      painter.drawRect( x * 20, y * 20, 20, 20 );
      }

  //Icon miniature
  painter.drawImage( width() - mWork.width(), 0, mWork );

  //Grid
  painter.setPen( Qt::lightGray );
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
  if( event->button() == Qt::LeftButton ) {
    if( mPoint != div20( event->pos() ) )
      mouseMoveEvent( event );
    if( mMode != nullptr && mMode->left() ) {
      //Append to undo
      if( mUndo.count() >= 30 )
        mUndo.pop_front();
      mUndo.push_back( mImage );
      //Apply current
      mImage = mWork;
      }
    }
  else if( event->button() == Qt::RightButton ) {
    if( mMode != nullptr )
      mMode->right();
    }
  }




void SpWinEditor::mouseMoveEvent(QMouseEvent *event)
  {
  mPoint = div20( event->pos() );
  mWork = mImage;
  if( mMode != nullptr ) {
    QPainter wp( &mWork );
    //wp.setRenderHint( QPainter::Antialiasing, true );
    mMode->paint( wp, mPoint, mColor );
    update();
    }
  }
