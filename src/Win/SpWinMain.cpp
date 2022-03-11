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
#include "SpConfig.h"
#include "SpWinMain.h"
#include "SpWinEditor.h"

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


#include <QSettings>
#include <QGuiApplication>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QCloseEvent>
#include <QFileInfo>
#include <QMessageBox>
#include <QDesktopServices>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QJsonDocument>
#include <QClipboard>
#include <QStatusBar>

SpWinMain::SpWinMain(QWidget *parent) :
  QMainWindow(parent),
  mActiveMode(nullptr)
  {
  mEditor = new SpWinEditor();
  setCentralWidget( mEditor );

  //When file name changed
  connect( mEditor, &SpWinEditor::fileName, this, &SpWinMain::fileName );
  fileName( QString{} );

  QToolBar *toolBar = new QToolBar( tr("SaliPixel tool bar"), this );
  addToolBar( toolBar );

  auto menuFile = new QMenu( tr("File") );
  toolBar->addAction( menuFile->addAction( QIcon( QStringLiteral(":/pic/fileNew.png")), tr("New file"), mEditor, &SpWinEditor::cmFileNew ) );
  toolBar->addAction( menuFile->addAction( QIcon( QStringLiteral(":/pic/fileOpen.png")), tr("Open..."), mEditor, &SpWinEditor::cmFileOpen ) );
  toolBar->addAction( menuFile->addAction( QIcon( QStringLiteral(":/pic/fileSave.png")), tr("Save"), mEditor, &SpWinEditor::cmFileSave ) );
  toolBar->addAction( menuFile->addAction( QIcon( QStringLiteral(":/pic/fileSaveAs.png")), tr("Save as..."), mEditor, &SpWinEditor::cmFileSaveAs ) );
  menuFile->addSeparator();
  menuFile->addAction( tr("Export to png"), mEditor, &SpWinEditor::cmFileExport );
  menuFile->addSeparator();
  menuFile->addAction( tr("Exit"), this, &SpWinMain::close );
  toolBar->addSeparator();

  auto menuEdit = new QMenu( tr("Edit") );
  menuEdit->addAction( tr("Undo"), mEditor, &SpWinEditor::cmEditUndo );
  menuEdit->addSeparator();
  auto copy = menuEdit->addAction( tr("Copy or move") );
  copy->setCheckable(true);
  connect( copy, &QAction::toggled, mEditor, &SpWinEditor::cmEditCopyToggle );
  auto over = menuEdit->addAction( tr("Do override") );
  over->setCheckable(true);
  connect( over, &QAction::toggled, mEditor, &SpWinEditor::cmEditOverrideToggle );
  toolBar->addSeparator();
  addMode( new SpModeAreaMove(), menuEdit, toolBar );
  addMode( new SpModeAreaRotate(), menuEdit, toolBar );
  addMode( new SpModeAreaMirror(), menuEdit, toolBar );
  addMode( new SpModeAreaRectArray(), menuEdit, toolBar );
  menuEdit->addAction( tr("Round array"), mEditor, &SpWinEditor::cmEditRoundArray );
  menuEdit->addAction( tr("Scale"), mEditor, &SpWinEditor::cmEditScale );
  menuEdit->addSeparator();
  menuEdit->addAction( tr("Move vertex point"), mEditor, &SpWinEditor::cmEditMovePoint );
  menuEdit->addSeparator();
  menuEdit->addAction( tr("Paste file"), mEditor, &SpWinEditor::cmEditPasteFile );

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



void SpWinMain::fileName(const QString &fname)
  {
  QString name( "noname" );
  if( !fname.isEmpty() ) {
    QFileInfo info(fname);
    name = info.fileName();
    }
  setWindowTitle( tr("SaliPixel v%1.%2 [%3]").arg(SP_VERSION_MAJOR).arg(SP_VERSION_MINOR).arg(name) );
  }



void SpWinMain::closeEvent(QCloseEvent *event)
  {
  //If can close editor
  if( mEditor->canClose() ) {
    event->accept();
    }
  else event->ignore();
  }



void SpWinMain::addMode(SpMode *mode, QMenu *menu, QToolBar *bar)
  {
  QAction *action = menu->addAction( QIcon( QStringLiteral(":/pic/") + mode->iconName()), mode->menuName() );
  action->setCheckable( true );
  connect( action, &QAction::triggered, this, [this, mode, action] () {
    mEditor->setMode( mode, true );
    if( mActiveMode != nullptr )
      mActiveMode->setChecked(false);
    mActiveMode = action;
    mActiveMode->setChecked(true);
    });

  if( bar )
    bar->addAction( action );
  }
