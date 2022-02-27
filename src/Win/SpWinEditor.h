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

#include <QWidget>
#include <QImage>
#include <QVector>

class SpMode;

class SpWinEditor : public QWidget
  {
    Q_OBJECT

    QImage          mWork;
    QImage          mImage;
    QVector<QImage> mUndo;
    SpMode         *mMode;
    QColor          mColor;
    QPoint          mPoint;
  public:
    explicit SpWinEditor(QWidget *parent = nullptr);

    bool canClose();

  private:
    void setMode( SpMode *md );
  signals:

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
