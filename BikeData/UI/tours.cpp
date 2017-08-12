#include "UI\tours.h"
#include "ui_tours.h"

Tours::Tours(Manager *manager, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Tours)
{
  ui->setupUi(this);
  mManager = manager;

  std::vector<const Tour*>* tours = mManager->getTours();
  for (std::vector<const Tour*>::const_iterator it = tours->begin(); it != tours->end(); ++it)
  {
    QListWidgetItem* item = new QListWidgetItem(ui->mListTours);
    item->setText((*it)->getTitle());
    ui->mListTours->addItem(item);
  }
  QListWidgetItem* item = new QListWidgetItem(ui->mListTours);
  item->setText(QString("add..."));
  ui->mListTours->addItem(item);
}

Tours::~Tours()
{
  delete ui;
}
