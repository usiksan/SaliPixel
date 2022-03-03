#ifndef SPDLGNEW_H
#define SPDLGNEW_H

#include <QDialog>

namespace Ui {
  class SpDlgNew;
}

class SpDlgNew : public QDialog
  {
    Q_OBJECT

  public:
    explicit SpDlgNew(QWidget *parent = nullptr);
    ~SpDlgNew();

    void setup( const QString &titleDlg, const QString &titleWidth, const QString &titleHeight, int defWidth, int defHeight );

    int  imageWidth() const;
    int  imageHeight() const;

    int  valueWidth() const;
    int  valueHeight() const;
  private:
    Ui::SpDlgNew *ui;
  };

#endif // SPDLGNEW_H
