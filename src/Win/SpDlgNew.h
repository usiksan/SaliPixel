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

    int imageWidth() const;
    int imageHeight() const;
  private:
    Ui::SpDlgNew *ui;
  };

#endif // SPDLGNEW_H
