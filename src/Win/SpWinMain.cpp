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
  menuFile->addAction( tr("Open..."), mEditor, &SpWinEditor::cmFileOpen );
  menuFile->addAction( tr("Save"), mEditor, &SpWinEditor::cmFileSave );
  menuFile->addAction( tr("Save as..."), mEditor, &SpWinEditor::cmFileSaveAs );
  menuFile->addSeparator();
  menuFile->addAction( tr("Export to png"), mEditor, &SpWinEditor::cmFileExport );
  menuFile->addSeparator();
  menuFile->addAction( tr("Exit"), this, &SpWinMain::close );

  auto menuEdit = new QMenu( tr("Edit") );
  menuEdit->addAction( tr("Undo"), mEditor, &SpWinEditor::cmEditUndo );
  menuEdit->addSeparator();
  auto copy = menuEdit->addAction( tr("Copy or move") );
  copy->setCheckable(true);
  connect( copy, &QAction::toggled, mEditor, &SpWinEditor::cmEditCopyToggle );
  auto over = menuEdit->addAction( tr("Do override") );
  over->setCheckable(true);
  connect( over, &QAction::toggled, mEditor, &SpWinEditor::cmEditOverrideToggle );
  menuEdit->addAction( tr("Move"), mEditor, &SpWinEditor::cmEditMove );
  menuEdit->addAction( tr("Rotate"), mEditor, &SpWinEditor::cmEditRotate );
  menuEdit->addAction( tr("Mirror"), mEditor, &SpWinEditor::cmEditMirror );
  menuEdit->addAction( tr("Rectangle array"), mEditor, &SpWinEditor::cmEditRectArray );
  menuEdit->addAction( tr("Round array"), mEditor, &SpWinEditor::cmEditRoundArray );
  menuEdit->addAction( tr("Scale"), mEditor, &SpWinEditor::cmEditScale );
  menuEdit->addSeparator();
  menuEdit->addAction( tr("Move vertex point"), mEditor, &SpWinEditor::cmEditMovePoint );

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
  menuDraw->addAction( tr("Parallelogramm"), mEditor, &SpWinEditor::cmDrawParallelogramm );
  menuDraw->addAction( tr("Round rect"), mEditor, &SpWinEditor::cmDrawRoundRect );
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
