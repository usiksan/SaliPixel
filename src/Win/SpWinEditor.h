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
#include "Object/SpCmdList.h"
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
    SpCmdList        mObjects;
    SpMode          *mMode;
    QColor           mColor;
    QPoint           mPoint;
    QString          mPath;
    int              mScale;
    bool             mStaticMode;
  public:
    explicit SpWinEditor(QWidget *parent = nullptr);
    ~SpWinEditor() { clear(); }

    bool   canClose();

    void   setMode(SpMode *md , bool staticMode = false );

  private:

    void   clear();

    QPoint div20( QPoint p ) const;

    void   repaintObjects();

  signals:
    void stepMessage( const QString msg );

    void fileName( const QString &fname );

  public slots:
    void cmFileNew();
    void cmFileOpen();
    void cmFileSave();
    void cmFileSaveAs();
    void cmFileExport();

    void cmEditUndo();
    void cmEditCopyToggle( bool state );
    void cmEditOverrideToggle( bool state );

    void cmEditInsert();
    void cmEditMovePoint();
    void cmEditPasteFile();

    void cmDrawColor();
    void cmDrawBaseColor();
    void cmDrawPoint();
    void cmDrawLine();
    void cmDrawRect();
    void cmDrawArc();
    void cmDrawArc2();
    void cmDrawCircle();
    void cmDrawCircle2();
    void cmDrawTriangle();
    void cmDrawParallelogramm();
    void cmDrawRoundRect();
    void cmDrawFillRect();
    void cmDrawFillCircle();
    void cmDrawFill();

    void cmClearPoint();
    void cmClearRect();
    void cmClearCircle();

//    void cmEdit

    // QWidget interface
  protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;
  };

#endif // SPWINEDITOR_H
