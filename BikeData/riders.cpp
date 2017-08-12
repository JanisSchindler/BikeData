#include "riders.h"
#include "ui_riders.h"

Riders::Riders(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Riders)
{
  ui->setupUi(this);
}

Riders::~Riders()
{
  delete ui;
}
