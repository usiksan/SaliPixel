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
#ifndef SPWINMAIN_H
#define SPWINMAIN_H

#include "SpConfig.h"
#include "Mode/SpMode.h"

#include <QMainWindow>
#include <QMenu>
#include <QToolBar>

class SpWinEditor;


class SpWinMain : public QMainWindow
  {
    Q_OBJECT

    SpWinEditor *mEditor;
    QAction     *mActiveMode;
  public:
    SpWinMain(QWidget *parent = nullptr);
    ~SpWinMain();

  private slots:
    void fileName( const QString &fname );

    // QWidget interface
  protected:
    virtual void closeEvent(QCloseEvent *event) override;

  private:
    void addMode( QMenu *menu, QToolBar *bar, const QString &menuName, const QString &iconName, SpMode *(*modeBuilder)() );
  };
#endif // SPWINMAIN_H
