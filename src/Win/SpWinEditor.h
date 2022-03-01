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

#include "Object/SpCmd.h"
#include "Mode/SpImage.h"

#include <QWidget>
#include <QImage>
#include <QList>

class SpMode;

#define UNDO_SIZE 20

class SpWinEditor : public QWidget
  {
    Q_OBJECT

    SpImage          mWork;
    SpImage          mImage;
    QList<SpCmdPtr>  mObjects;
    SpMode          *mMode;
    QColor           mColor;
    QPoint           mPoint;
    QString          mPath;
    bool             mDirty;
  public:
    explicit SpWinEditor(QWidget *parent = nullptr);
    ~SpWinEditor() { clear(); }

    bool canClose();

  private:
    void setMode( SpMode *md );

    void clear();

  signals:
    void stepMessage( const QString msg );

  public slots:
    void cmFileNew();
    void cmFileSave();
    void cmFileSaveAs();
//    void cmFileExport();

    void cmEditUndo();

    void cmDrawColor();
    void cmDrawPoint();
    void cmDrawLine();
    void cmDrawRect();
    void cmDrawArc();
    void cmDrawArc2();
    void cmDrawCircle();
    void cmDrawCircle2();
    void cmDrawTriangle();
    void cmDrawFillRect();
    void cmDrawFillCircle();
    void cmDrawFill();

//    void cmEdit

    // QWidget interface
  protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
  };

#endif // SPWINEDITOR_H
