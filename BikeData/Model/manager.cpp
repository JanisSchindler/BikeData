#include "manager.h"

Manager::Manager(const QString path)
{
  mPath = path;
  mRiders = new std::vector<const Rider*>();
  mTours = new std::vector<const Tour*>();
}

Manager::~Manager()
{
  for(std::vector<const Rider*>::iterator it = mRiders->begin(); it != mRiders->end(); ++it)
  {
    delete *it;
  }
  for(std::vector<const Tour*>::iterator it = mTours->begin(); it != mTours->end(); ++it)
  {
    delete *it;
  }
  delete mRiders;
  delete mTours;
}

void Manager::save() const
{
  QDomDocument doc("data");
  QDomElement* riders = new QDomElement();
  riders->setTagName(QString("Riders"));
  for(std::vector<const Rider*>::const_iterator it = mRiders->begin(); it != mRiders->end(); ++it)
  {
    // (*it) is of type Rider*
    riders->appendChild(*(*it)->writeToXML());
  }


  QDomElement* tours = new QDomElement();
  tours->setTagName(QString("Tours"));
  for(std::vector<const Tour*>::const_iterator it = mTours->begin(); it != mTours->end(); ++it)
  {
    tours->appendChild(*(*it)->writeToXML());
  }

  QDomElement root = doc.createElement(QString("Data"));
  root.setTagName(QString("Data"));
  root.appendChild(*riders);
  root.appendChild(*tours);
  root.appendChild(*writeMap());

  doc.appendChild(root);
  QFile file(mPath);
  if (!file.open(QIODevice::WriteOnly))
  {
    return;
  }
  QTextStream out(&file);
  out << doc.toString();
  file.close();
}

void Manager::load()
{
  QDomDocument doc("data");
  QFile file(mPath);
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
    rider->loadFromXML(riders.item(i));
    mRiders->push_back(rider);
  }
  QDomNodeList tours = root.elementsByTagName(QString("Tours"));
  cnt = tours.count();
  for(int i = 0; i < cnt; ++i)
  {
    Tour* tour = new Tour();
    tour->loadFromXML(tours.item(i));
    mTours->push_back(tour);
  }

  QDomNode map = root.elementsByTagName(QString("TourData")).item(0);
  readMap(map);
}

std::vector<const Rider*>* Manager::getRidersForTour(const Tour* tour) const
{
  std::vector<const Rider*>* list = new std::vector<const Rider*>();
  std::vector<const Rider*>* fromMap = mMapTours2Riders.at(tour);
  for(std::vector<const Rider*>::const_iterator it = fromMap->begin(); it != fromMap->end(); ++it)
  {
    list->push_back(*it);
  }
  return list;
}

std::vector<const Tour*>* Manager::getToursForRider(const Rider* rider) const
{
 std::vector<const Tour*>* list = new std::vector<const Tour*>();

 for(std::map<const Tour*, std::vector<const Rider*>*>::const_iterator it = mMapTours2Riders.begin();
     it != mMapTours2Riders.end(); ++it)
 {
   for(std::vector<const Rider*>::const_iterator it2 = it->second->begin(); it2 != it->second->end(); ++it2)
   {
     if ((*it2)->getId() == rider->getId())
     {
       list->push_back(it->first);
       break;
     }
   }
 }
 return list;
}

const Rider* Manager::getRiderById(QUuid id) const
{
  for(std::vector<const Rider*>::const_iterator it = mRiders->begin(); it != mRiders->end(); ++it)
  {
    if ( (*it)->getId() == id)
    {
      return *it;
    }
  }
  return NULL;
}

std::vector<const Tour*>* Manager::getTours() const
{
  return mTours;
}

std::vector<const Rider*>* Manager::getRiders() const
{
  return mRiders;
}

const Tour* Manager::getTourById(QUuid id) const
{
  for(std::vector<const Tour*>::const_iterator it = mTours->begin(); it != mTours->end(); ++it)
  {
    if ( (*it)->getId() == id)
    {
      return *it;
    }
  }
  return NULL;
}

// save in the form of Tour --> Riders (ids only)
QDomElement* Manager::writeMap() const
{
  QDomElement* map = new QDomElement();
  map->setTagName("TourData");
  for(std::map<const Tour*, std::vector<const Rider*>*>::const_iterator it= mMapTours2Riders.begin();
      it != mMapTours2Riders.end(); ++it)
  {
    QDomElement* tour = new QDomElement();
    tour->setTagName(QString("Tour"));
    tour->setAttribute(QString("id"), it->first->getId().toString());
    for(std::vector<const Rider*>::const_iterator it2 = it->second->begin(); it2 != it->second->end(); ++it)
    {
      QDomElement* member = new QDomElement();
      member->setTagName(QString("Member"));
      member->setNodeValue((*it2)->getId().toString());
      tour->appendChild(*member);
    }
    map->appendChild(*tour);
  }
  return map;
}

void Manager::readMap(const QDomNode map)
{
  if (map.isNull())
  {
    return;
  }
  QDomElement element = map.toElement();
  if (element.isNull())
  {
    return;
  }
  QDomNodeList list = element.elementsByTagName(QString("Tour"));
  int cnt = list.count();
  for (int i = 0; i < cnt; ++i)
  {
    QDomElement xTour = list.at(i).toElement();
    if(xTour.isNull())
    {
      continue;
    }
    const Tour* tour = getTourById(QUuid(xTour.attribute(QString("id"))));
    if (NULL == tour)
    {
      continue;
    }
    mMapTours2Riders[tour] = new std::vector<const Rider*>();
    QDomNodeList xMembers = xTour.elementsByTagName(QString("member"));
    int memCount = xMembers.count();
    for(int j = 0; j < memCount; ++j)
    {
      QDomElement xMember = xMembers.at(j).toElement();
      const Rider* rider = getRiderById(QUuid(xMember.nodeValue()));
      if (NULL == rider)
      {
        continue;
      }
      mMapTours2Riders[tour]->push_back(rider);
    }
  }
}
