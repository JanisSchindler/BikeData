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
    IdQListWidgetItem* item = new IdQListWidgetItem(ui->mListTours, *it);
    ui->mListTours->addItem(item);
  }
  // new line
  IdQListWidgetItem* item = new IdQListWidgetItem(ui->mListTours, NULL);
  ui->mListTours->addItem(item);
  initRiderList();
  // connect signals
  connect(ui->mListTours, SIGNAL(currentRowChanged(int)), this, SLOT(onCurrentRowChanged(int)));
  connect(ui->mBtnOk, SIGNAL(pressed()), this, SLOT(onButtonOk()));
  connect(ui->mBtnCancel, SIGNAL(pressed()), this, SLOT(onButtonCancel()));
  connect(mManager, SIGNAL(ridersChanged()), this, SLOT(onRidersChanged()));
}

Tours::~Tours()
{
  disconnect(ui->mListTours, SIGNAL(currentRowChanged(int)), this, SLOT(onCurrentRowChanged(int)));
  disconnect(ui->mBtnOk, SIGNAL(pressed()), this, SLOT(onButtonOk()));
  disconnect(ui->mBtnCancel, SIGNAL(pressed()), this, SLOT(onButtonCancel()));
  disconnect(mManager, SIGNAL(ridersChanged()), this, SLOT(onRidersChanged()));
  delete ui;
}

void Tours::initRiderList()
{
  ui->mListRiders->clear();
  std::vector<const Rider*>* riders = mManager->getRiders();
  for(std::vector<const Rider*>::const_iterator it = riders->begin(); it != riders->end(); ++it)
  {
    IdQListWidgetItem* item = new IdQListWidgetItem(ui->mListRiders, *it);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
    item->setCheckState(Qt::Unchecked); // AND initialize check state
    ui->mListRiders->addItem(item);
  }
}

void Tours::setUi(const Tour* tour)
{
  IdQListWidgetItem* item = dynamic_cast<IdQListWidgetItem*> (ui->mListTours->currentItem());
  if (NULL != item)
  {
    item->update(tour);
  }
  // reset all check boxes in the list
  for (int i = 0; i < ui->mListRiders->count(); ++i)
  {
    QListWidgetItem* item = ui->mListRiders->item(i);
    item->setCheckState(Qt::Unchecked);
  }
  if (NULL == tour)
  {
    // data
    ui->mDateEditDate->setDate(QDate::currentDate());
    ui->mTimeEditDur->setTime(QTime(0,0,0,0));
    ui->mTxtBoxDistance->setText("0");
    ui->mTxtBoxHeight->setText("0");
    ui->mTxtBoxRaise->setText("0");
    ui->mTxtBoxSpeed->setText("0");
    ui->mTxtBoxTitle->setText("");

    return;
  }
  // use model data
  // data
  ui->mDateEditDate->setDate(tour->getDate());
  ui->mTimeEditDur->setTime(tour->getDuration().toTime());
  ui->mTxtBoxDistance->setText(QString::number(tour->getLength()));
  ui->mTxtBoxHeight->setText(QString::number(tour->getHeight()));
  ui->mTxtBoxRaise->setText(QString::number(tour->getAverageRaise(), 'f', 2));
  ui->mTxtBoxSpeed->setText(QString::number(tour->getAverageSpeed(), 'f', 2));
  ui->mTxtBoxTitle->setText(tour->getTitle());

  std::vector<const Rider*>* riders = mManager->getRidersForTour(tour);
  for (int i = 0; i < ui->mListRiders->count(); ++i)
  {
    IdQListWidgetItem* item = dynamic_cast<IdQListWidgetItem*>(ui->mListRiders->item(i));
    if (NULL == item)
    {
      continue;
    }
    for (std::vector<const Rider*>::const_iterator it = riders->begin(); it != riders->end(); ++it)
    {
      if ( (*it)->getId() == item->getElementId())
      {
        item->setCheckState(Qt::Checked);
      }
    }
  }
  delete riders;
  return;
}

void Tours::setModel(Tour* tour)
{
  bool create = NULL == tour;
  if (create)
  {
    // create a new one
    tour = mManager->addTour();
  }
  tour->setDate(ui->mDateEditDate->date());
  tour->setTitle(ui->mTxtBoxTitle->text());
  tour->setLength(ui->mTxtBoxDistance->text().toFloat()); // validation?
  tour->setHeight(ui->mTxtBoxHeight->text().toFloat());
  tour->setDuration(Duration(ui->mTimeEditDur->time()));

  // add riders
  std::vector<QUuid> riders;
  for(int i = 0; i < ui->mListRiders->count(); ++i)
  {
    IdQListWidgetItem* item = dynamic_cast<IdQListWidgetItem*> (ui->mListRiders->item(i));
    if (NULL == item)
    {
      continue;
    }
    if (item->checkState() == Qt::Checked)
    {
      riders.push_back(item->getElementId());
    }
  }
  mManager->setRidersForTour(tour->getId(), riders);

  if (create)
  {
    // add to listbox
    IdQListWidgetItem* item = new IdQListWidgetItem(tour);
    ui->mListTours->insertItem(ui->mListTours->count() - 1, item);
  }
  setUi(tour);
}

// set data of the current element
void Tours::onCurrentRowChanged(int currentRow)
{
  IdQListWidgetItem* item = dynamic_cast<IdQListWidgetItem*> (ui->mListTours->item(currentRow));
  if (NULL == item)
  {
    return;
  }
  QUuid id = item->getElementId();
  if (id.isNull())
  {
    setUi(NULL);
  }
  setUi(mManager->getTourById(id));
}

void Tours::onButtonOk()
{
  IdQListWidgetItem* item = dynamic_cast<IdQListWidgetItem*> (ui->mListTours->currentItem());
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
  setModel(const_cast<Tour*>(mManager->getTourById(id)));
}

void Tours::onButtonCancel()
{
  IdQListWidgetItem* item = dynamic_cast<IdQListWidgetItem*> (ui->mListTours->currentItem());
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
  setUi(mManager->getTourById(id));
}

void Tours::onRidersChanged()
{
  initRiderList();
}
