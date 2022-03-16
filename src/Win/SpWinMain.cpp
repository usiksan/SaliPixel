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
#include "Mode/SpModePasteFile.h"


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
  toolBar->addAction( menuEdit->addAction( QIcon( QStringLiteral(":/pic/editUndo.png")), tr("Undo"), mEditor, &SpWinEditor::cmEditUndo ) );
  menuEdit->addSeparator();
  auto copy = menuEdit->addAction( QIcon( QStringLiteral(":/pic/editCopy.png")), tr("Copy or move") );
  toolBar->addAction( copy );
  copy->setCheckable(true);
  connect( copy, &QAction::toggled, mEditor, &SpWinEditor::cmEditCopyToggle );
  auto over = menuEdit->addAction( tr("Do override") );
  over->setCheckable(true);
  connect( over, &QAction::toggled, mEditor, &SpWinEditor::cmEditOverrideToggle );

  toolBar->addSeparator();
  addMode( menuEdit, toolBar, tr("Move"),            QStringLiteral("editMove.png"), [] () -> SpMode* { return new SpModeAreaMove(); } );
  addMode( menuEdit, toolBar, tr("Rotate"),          QStringLiteral("editRotate.png"), [] () -> SpMode* { return new SpModeAreaRotate(); } );
  addMode( menuEdit, toolBar, tr("Mirror"),          QStringLiteral("editMirror.png"), [] () -> SpMode* { return new SpModeAreaMirror(); } );
  addMode( menuEdit, toolBar, tr("Rectangle array"), QStringLiteral("editRectArray.png"), [] () -> SpMode* { return new SpModeAreaRectArray(); } );
  addMode( menuEdit, toolBar, tr("Round array"),     QStringLiteral("editRoundArray.png"), [] () -> SpMode* { return new SpModeAreaRoundArray(); } );
  addMode( menuEdit, toolBar, tr("Scale"),           QStringLiteral("editScale.png"), [] () -> SpMode* { return new SpModeAreaScale(); } );
  menuEdit->addSeparator();
  addMode( menuEdit, toolBar, tr("Move vertex point"), QStringLiteral("editMoveVertex.png"), [] () -> SpMode* { return new SpModeEditPoint(); } );
  menuEdit->addSeparator();
  addMode( menuEdit, toolBar, tr("Paste file..."),     QStringLiteral("editPasteFile.png"), [] () -> SpMode* { return new SpModePasteFile(); } );

  toolBar = new QToolBar( tr("SaliPixel draw tool bar"), this );
  addToolBar( Qt::LeftToolBarArea, toolBar );
  auto menuDraw = new QMenu( tr("Draw") );
  toolBar->addAction( menuDraw->addAction( QIcon( QStringLiteral(":/pic/colors.png")), tr("Color"), mEditor, &SpWinEditor::cmDrawColor ) );
  menuDraw->addAction( tr("Base color"), mEditor, &SpWinEditor::cmDrawBaseColor );
  menuDraw->addSeparator();
  addMode( menuDraw, toolBar, tr("Point"),           QStringLiteral("drawPoint.png"), [] () -> SpMode* { return new SpModePoint(); } );
  addMode( menuDraw, toolBar, tr("Line"),            QStringLiteral("drawLine.png"), [] () -> SpMode* { return new SpModeLine(); } );
  addMode( menuDraw, toolBar, tr("Rect"),            QStringLiteral("drawRect.png"), [] () -> SpMode* { return new SpModeRect(); } );
  addMode( menuDraw, toolBar, tr("Circle"),          QStringLiteral("drawCircle.png"), [] () -> SpMode* { return new SpModeCircle(); } );
  addMode( menuDraw, toolBar, tr("Circle 2"),        QStringLiteral("drawCircle2.png"), [] () -> SpMode* { return new SpModeCircle2(); } );
  addMode( menuDraw, toolBar, tr("Arc"),             QStringLiteral("drawArc.png"), [] () -> SpMode* { return new SpModeArc(); } );
  addMode( menuDraw, toolBar, tr("Arc 2"),           QStringLiteral("drawArc2.png"), [] () -> SpMode* { return new SpModeArc2(); } );
  addMode( menuDraw, toolBar, tr("Triangle"),        QStringLiteral("drawTriangle.png"), [] () -> SpMode* { return new SpModeTriangle(); } );
  addMode( menuDraw, toolBar, tr("Parallelogramm"),  QStringLiteral("drawParallelogramm.png"), [] () -> SpMode* { return new SpModeParallelogramm(); } );
  addMode( menuDraw, toolBar, tr("Round rect"),      QStringLiteral("drawRoundRect.png"), [] () -> SpMode* { return new SpModeRoundRect(); } );
  menuDraw->addSeparator();
  addMode( menuDraw, toolBar, tr("Filled rect"),     QStringLiteral("drawFilledRect.png"), [] () -> SpMode* { return new SpModeFillRect(); } );
  addMode( menuDraw, toolBar, tr("Filled circle"),   QStringLiteral("drawFilledCircle.png"), [] () -> SpMode* { return new SpModeFillCircle(); } );
  addMode( menuDraw, toolBar, tr("Fill area"),       QStringLiteral("drawFillArea.png"), [] () -> SpMode* { return new SpModeFill(); } );

  auto menuClear = new QMenu( tr("Erase") );
  toolBar->addSeparator();
  addMode( menuClear, toolBar, tr("Point"),  QStringLiteral("erasePoint.png"), [] () -> SpMode* { return new SpModeClearPoint(); } );
  addMode( menuClear, toolBar, tr("Rect"),   QStringLiteral("eraseRect.png"), [] () -> SpMode* { return new SpModeClearRect(); } );
  addMode( menuClear, toolBar, tr("Circle"), QStringLiteral("eraseCircle.png"), [] () -> SpMode* { return new SpModeClearCircle(); } );

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




void SpWinMain::addMode(QMenu *menu, QToolBar *bar, const QString &menuName, const QString &iconName, SpMode *(*modeBuilder)())
  {
  QAction *action = menu->addAction( QIcon( QStringLiteral(":/pic/") + iconName ), menuName );
  action->setCheckable( true );
  connect( action, &QAction::triggered, this, [this, modeBuilder, action] () {
    mEditor->setMode( modeBuilder() );
    if( mActiveMode != nullptr )
      mActiveMode->setChecked(false);
    mActiveMode = action;
    mActiveMode->setChecked(true);
    });

  if( bar )
    bar->addAction( action );
  }



