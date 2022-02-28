/*
Project "Combine vector-pixel graphic editor"

Author
  Sibilev Alexander S.

Web
  www.saliLab.com
  www.saliLab.ru

Description
  Main application window
*/
#include "SpWinMain.h"
#include "SpWinEditor.h"

#include <QSettings>
#include <QGuiApplication>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QJsonDocument>
#include <QClipboard>
#include <QStatusBar>

SpWinMain::SpWinMain(QWidget *parent)
  : QMainWindow(parent)
  {
  mEditor = new SpWinEditor();
  setCentralWidget( mEditor );

  auto menuFile = new QMenu( tr("File") );
  //menuFile->addAction( tr("New file"), mEditor, &SpWinEditor::)
  menuFile->addAction( tr("Exit"), this, &SpWinMain::close );

  auto menuEdit = new QMenu( tr("Edit") );

  auto menuDraw = new QMenu( tr("Draw") );
  menuDraw->addAction( tr("Point"), mEditor, &SpWinEditor::cmDrawPoint );
  menuDraw->addAction( tr("Line"), mEditor, &SpWinEditor::cmDrawLine );
  menuDraw->addAction( tr("Rect"), mEditor, &SpWinEditor::cmDrawRect );

  menuBar()->addMenu( menuFile );
  menuBar()->addMenu( menuEdit );
  menuBar()->addMenu( menuDraw );

  QLabel *msg = new QLabel();
  connect( mEditor, &SpWinEditor::stepMessage, msg, &QLabel::setText );
  statusBar()->addWidget( msg );

  resize( 900, 900 );
  }




SpWinMain::~SpWinMain()
  {
  }



void SpWinMain::closeEvent(QCloseEvent *event)
  {
  //If can close editor
  if( mEditor->canClose() ) {
    event->accept();
    }
  else event->ignore();
  }
