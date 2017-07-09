#include "manager.h"

Manager::Manager()
{
  mRiders = new std::vector<Rider*>();
  mTours = new std::vector<Tour*>();
}

Manager::~Manager()
{
  // TODO: delete elements!
  delete mRiders;
  delete mTours;
}

void Manager::Save(const QString fileName) const
{

}

void Manager::Load(const QString fileName) const
{
  QDomDocument doc("data");
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly))
  {
    return;
  }
  if (!doc.setContent(&file))
  {
    {
      file.close();
      return;
    }
  }
  file.close();
  QDomElement root = doc.firstChild().toElement();
  QDomNodeList riders = root.elementsByTagName(QString("Riders"));
  int cnt = riders.count();
  for (int i = 0; i < cnt; ++i)
  {
    Rider* rider = new Rider();
    rider->LoadFromXML(riders.item(i));
    mRiders->push_back(rider);
  }
  QDomNodeList tours = root.elementsByTagName(QString("Tours"));
  cnt = tours.count();
  for(int i = 0; i < cnt; ++i)
  {
    Tour* tour = new Tour();
    tour->LoadFromXML(tours.item(i));
    mTours->push_back(tour);
  }

  QDomNode map = root.elementsByTagName(QString("TourData")).item(0);
  ReadMap(map);
}

std::vector<const Rider*> Manager::GetRidersForTour(const Tour* tour) const
{

}

std::vector<const Tour*> Manager::GetToursForRider(const Rider* Rider) const
{

}

// save in the form of Tour --> Riders (ids only)
QDomElement* Manager::WriteMap() const
{
  return NULL;
}

void Manager::ReadMap(const QDomNode map) const
{
  if (map.isNull())
  {
    return;
  }
}
