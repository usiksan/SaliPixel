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

void SpDlgNew::setup(const QString &titleDlg, const QString &titleWidth, const QString &titleHeight, int defWidth, int defHeight)
  {
  setWindowTitle(titleDlg);
  ui->mLabelWidth->setText(titleWidth);
  ui->mLabelHeight->setText(titleHeight);
  ui->mWidth->setText( QString::number(defWidth) );
  ui->mHeight->setText( QString::number(defHeight) );
  }

int SpDlgNew::imageWidth() const
  {
  return qBound( 16, ui->mWidth->text().toInt(), 512 );
  }

int SpDlgNew::imageHeight() const
  {
  return qBound( 16, ui->mHeight->text().toInt(), 512 );
  }

int SpDlgNew::valueWidth() const
  {
  return ui->mWidth->text().toInt();
  }

int SpDlgNew::valueHeight() const
  {
  return ui->mHeight->text().toInt();
  }
