#include "UI\riders.h"
#include "ui_riders.h"

Riders::Riders(Manager *manager, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Riders)
{  
  ui->setupUi(this);
  mManager = manager;

  std::vector<const Rider*>* riders = mManager->getRiders();
  for(std::vector<const Rider*>::const_iterator it = riders->begin(); it != riders->end(); ++it)
  {
    IdQListWidgetItem* item = new IdQListWidgetItem(ui->mListRiders, *it);
    ui->mListRiders->addItem(item);
  }
  IdQListWidgetItem* item = new IdQListWidgetItem(ui->mListRiders, NULL);
  ui->mListRiders->addItem(item);

  // connect signals
  connect(ui->mListRiders, SIGNAL(currentRowChanged(int)), this, SLOT(onCurrentRowChanged(int)));
  connect(ui->mBtnOk, SIGNAL(pressed()), this, SLOT(onButtonOk()));
  connect(ui->mBtnCancel, SIGNAL(pressed()), this, SLOT(onButtonCancel()));
  connect(mManager, SIGNAL(toursChanged()), this, SLOT(onToursChanged()));
}

Riders::~Riders()
{
  disconnect(ui->mListRiders, SIGNAL(currentRowChanged(int)), this, SLOT(onCurrentRowChanged(int)));
  disconnect(ui->mBtnOk, SIGNAL(pressed()), this, SLOT(onButtonOk()));
  disconnect(ui->mBtnCancel, SIGNAL(pressed()), this, SLOT(onButtonCancel()));
  disconnect(mManager, SIGNAL(toursChanged()), this, SLOT(onToursChanged()));
  delete ui;
}

void Riders::setUi(const Rider* rider)
{
  IdQListWidgetItem* item = dynamic_cast<IdQListWidgetItem*> (ui->mListRiders->currentItem());
  if (NULL != item)
  {
    item->update(rider);
  }
  if (NULL == rider)
  {
    // data
    ui->mTxtBoxFirstName->setText("");
    ui->mTxtBoxLastName->setText("");
    ui->mDateEditBirthdate->setDate(QDate::currentDate());
    ui->mTxtBoxAge->setText("");
    // statistics
    ui->mTxtBoxSumKm->setText("");
    ui->mTxtBoxSumHm->setText("");
    ui->mTxtBoxSumTime->setText("");
    ui->mTxtBoxAvgRaise->setText("");
    ui->mTxtBoxAvgSpeed->setText("");
    ui->mBtnShowTours->setEnabled(false);
    return;
  }
  // use model data
  // data
  ui->mTxtBoxFirstName->setText(rider->getFirstName());
  ui->mTxtBoxLastName->setText(rider->getLastName());
  ui->mDateEditBirthdate->setDate(rider->getBirthdate());
  ui->mTxtBoxAge->setText(QString::number(rider->getAge()));
  // statistics
  // statistics, first get all tours that the rider was on
  std::vector<const Tour*>* tours = mManager->getToursForRider(rider);
  float sumKm = 0;
  Duration duration;
  int sumHght = 0;
  for (std::vector<const Tour*>::const_iterator it = tours->begin(); it != tours->end(); ++it)
  {
    sumKm += (*it)->getLength();
    sumHght += (*it)->getHeight();
    duration = duration + (*it)->getDuration();
  }
  ui->mTxtBoxSumKm->setText(QString::number(sumKm));
  ui->mTxtBoxSumHm->setText(QString::number(sumHght));
  ui->mTxtBoxSumTime->setText(duration.toString());
  ui->mTxtBoxAvgRaise->setText(sumHght > 0 ? QString::number(100 * sumHght / (sumKm * 1000), 'f', 2) : "0");
  if (sumKm > 0)
  {
    // use km / h
    ui->mTxtBoxAvgSpeed->setText(QString::number(sumKm /(duration.secs() / 3600), 'f', 2));
  }
  else
  {
    ui->mTxtBoxAvgSpeed->setText("0");
  }
  ui->mBtnShowTours->setEnabled(sumKm > 0);
  return;
}

void Riders::setModel(Rider* rider)
{
  bool create = NULL == rider;
  if (create)
  {
    // create a new one
    rider = mManager->addRider();
  }
  rider->setBirthdate(ui->mDateEditBirthdate->date());
  rider->setFirstName(ui->mTxtBoxFirstName->text());
  rider->setLastName(ui->mTxtBoxLastName->text());

  if (create)
  {
    // add to listbox
    IdQListWidgetItem* item = new IdQListWidgetItem(rider);
    ui->mListRiders->insertItem(ui->mListRiders->count() - 1, item);
  }
  setUi(rider);
}

// set data of the current element
void Riders::onCurrentRowChanged(int currentRow)
{
  IdQListWidgetItem* item = dynamic_cast<IdQListWidgetItem*> (ui->mListRiders->item(currentRow));
  if (NULL == item)
  {
    return;
  }
  QUuid id = item->getElementId();
  if (id.isNull())
  {
    setUi(NULL);
  }
  setUi(mManager->getRiderById(id));
}

void Riders::onButtonOk()
{
  IdQListWidgetItem* item = dynamic_cast<IdQListWidgetItem*> (ui->mListRiders->currentItem());
  if (NULL == item)
  {
    return;
  }
  QUuid id = item->getElementId();
  if (id.isNull())
  {
    setModel(NULL);
    return;
  }
  // remove const in cast
  setModel(const_cast<Rider*>(mManager->getRiderById(id)));
}

void Riders::onButtonCancel()
{
  IdQListWidgetItem* item = dynamic_cast<IdQListWidgetItem*> (ui->mListRiders->currentItem());
  if (NULL == item)
  {
    return;
  }
  QUuid id = item->getElementId();
  if (id.isNull())
  {
    setUi(NULL);
    return;
  }
  setUi(mManager->getRiderById(id));
}

void Riders::onToursChanged()
{

}
