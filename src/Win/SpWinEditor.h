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
#ifndef SPWINEDITOR_H
#define SPWINEDITOR_H

#include "Mode/SpImage.h"

#include <QWidget>
#include <QImage>
#include <QVector>

class SpMode;

#define UNDO_SIZE 20

class SpWinEditor : public QWidget
  {
    Q_OBJECT

    SpImage          mWork;
    SpImage          mImage;
    //SpImage          mUndo[UNDO_SIZE];
    //int              mUndoCount;
    SpMode          *mMode;
    QColor           mColor;
    QPoint           mPoint;
  public:
    explicit SpWinEditor(QWidget *parent = nullptr);

    bool canClose();

  private:
    void setMode( SpMode *md );

  signals:
    void stepMessage( const QString msg );

  public slots:
//    void cmFileNew();
//    void cmFileSave();
//    void cmFileSaveAs();
//    void cmFileExport();

    void cmDrawPoint();
    void cmDrawLine();
    void cmDrawRect();
//    void cmObjArc();
//    void cmObjCircle();

//    void cmEdit

    // QWidget interface
  protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
  };

#endif // SPWINEDITOR_H
