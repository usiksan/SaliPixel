#include "SpDlgNew.h"
#include "ui_SpDlgNew.h"

SpDlgNew::SpDlgNew(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SpDlgNew)
  {
  ui->setupUi(this);
  ui->mWidth->setText("32");
  ui->mHeight->setText("32");
  }

SpDlgNew::~SpDlgNew()
  {
  delete ui;
  }

int SpDlgNew::imageWidth() const
  {
  return qBound( 16, ui->mWidth->text().toInt(), 512 );
  }

int SpDlgNew::imageHeight() const
  {
  return qBound( 16, ui->mHeight->text().toInt(), 512 );
  }
