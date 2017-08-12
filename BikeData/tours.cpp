#include "tours.h"
#include "ui_tours.h"

Tours::Tours(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Tours)
{
  ui->setupUi(this);
}

Tours::~Tours()
{
  delete ui;
}
