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

#include <QMainWindow>

class SpWinEditor;

class SpWinMain : public QMainWindow
  {
    Q_OBJECT

    SpWinEditor *mEditor;
  public:
    SpWinMain(QWidget *parent = nullptr);
    ~SpWinMain();


    // QWidget interface
  protected:
    virtual void closeEvent(QCloseEvent *event) override;
  };
#endif // SPWINMAIN_H
