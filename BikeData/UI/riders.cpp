#include "UI\riders.h"
#include "ui_riders.h"

Riders::Riders(Manager *manager, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Riders)
{
  mManager = manager;
  ui->setupUi(this);


  QListWidgetItem* item = new QListWidgetItem(ui->mListRiders);
  item->setText(QString("add..."));
  ui->mListRiders->addItem(item);
}

Riders::~Riders()
{
  delete ui;
}
