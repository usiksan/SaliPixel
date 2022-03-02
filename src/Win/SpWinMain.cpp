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
  menuFile->addAction( tr("New file"), mEditor, &SpWinEditor::cmFileNew );
  menuFile->addAction( tr("Save"), mEditor, &SpWinEditor::cmFileSave );
  menuFile->addAction( tr("Save as..."), mEditor, &SpWinEditor::cmFileSaveAs );
  menuFile->addAction( tr("Exit"), this, &SpWinMain::close );

  auto menuEdit = new QMenu( tr("Edit") );
  menuEdit->addAction( tr("Undo"), mEditor, &SpWinEditor::cmEditUndo );
  menuEdit->addAction( tr("Fragment move"), mEditor, &SpWinEditor::cmEditTransferMove );
  menuEdit->addAction( tr("Fragment copy"), mEditor, &SpWinEditor::cmEditTransferCopy );
  menuEdit->addAction( tr("Rotate move"), mEditor, &SpWinEditor::cmEditRotateMove );
  menuEdit->addAction( tr("Rotate copy"), mEditor, &SpWinEditor::cmEditRotateCopy );

  auto menuDraw = new QMenu( tr("Draw") );
  menuDraw->addAction( tr("Color"), mEditor, &SpWinEditor::cmDrawColor );
  menuDraw->addAction( tr("Base color"), mEditor, &SpWinEditor::cmDrawBaseColor );
  menuDraw->addSeparator();
  menuDraw->addAction( tr("Point"), mEditor, &SpWinEditor::cmDrawPoint );
  menuDraw->addAction( tr("Line"), mEditor, &SpWinEditor::cmDrawLine );
  menuDraw->addAction( tr("Rect"), mEditor, &SpWinEditor::cmDrawRect );
  menuDraw->addAction( tr("Circle"), mEditor, &SpWinEditor::cmDrawCircle );
  menuDraw->addAction( tr("Circle2"), mEditor, &SpWinEditor::cmDrawCircle2 );
  menuDraw->addAction( tr("Arc"), mEditor, &SpWinEditor::cmDrawArc );
  menuDraw->addAction( tr("Arc2"), mEditor, &SpWinEditor::cmDrawArc2 );
  menuDraw->addAction( tr("Triangle"), mEditor, &SpWinEditor::cmDrawTriangle );
  menuDraw->addSeparator();
  menuDraw->addAction( tr("Filled rect"), mEditor, &SpWinEditor::cmDrawFillRect );
  menuDraw->addAction( tr("Filled circle"), mEditor, &SpWinEditor::cmDrawFillCircle );
  menuDraw->addAction( tr("Fill area"), mEditor, &SpWinEditor::cmDrawFill );

  auto menuClear = new QMenu( tr("Erase") );
  menuClear->addAction( tr("Point"), mEditor, &SpWinEditor::cmClearPoint );
  menuClear->addAction( tr("Rect"), mEditor, &SpWinEditor::cmClearRect );
  menuClear->addAction( tr("Circle"), mEditor, &SpWinEditor::cmClearCircle );

  menuBar()->addMenu( menuFile );
  menuBar()->addMenu( menuEdit );
  menuBar()->addMenu( menuDraw );
  menuBar()->addMenu( menuClear );

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
