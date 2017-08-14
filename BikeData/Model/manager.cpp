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
  // it seems all elements must be created from existing ones with the exclusion of the document
  QDomDocument doc("data");

  QDomElement root = doc.createElement("Data");
  root.setTagName("Data");

  QDomElement riders = doc.createElement("Riders");
  riders.setTagName("Riders");
  for(std::vector<const Rider*>::const_iterator it = mRiders->begin(); it != mRiders->end(); ++it)
  {
    // (*it) is of type Rider*
    riders.appendChild((*it)->writeToXML(doc));
  }
  QDomElement tours = doc.createElement("Tours");
  tours.setTagName("Tours");
  for(std::vector<const Tour*>::const_iterator it = mTours->begin(); it != mTours->end(); ++it)
  {
    tours.appendChild((*it)->writeToXML(doc));
  }

  root.appendChild(riders);
  root.appendChild(tours);
  root.appendChild(writeMap(doc));
  // add root element
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
  QDomNodeList riders = root.firstChildElement(QString("Riders")).elementsByTagName(QString("Rider"));
  int cnt = riders.count();
  for (int i = 0; i < cnt; ++i)
  {
    Rider* rider = new Rider();
    rider->loadFromXML(riders.item(i));
    mRiders->push_back(rider);
  }
  QDomNodeList tours = root.firstChildElement(QString("Tours")).elementsByTagName(QString("Tour"));
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
  std::map<const Tour*, std::vector<const Rider*>*>::const_iterator found = mMapTours2Riders.find(tour);
  if (found == mMapTours2Riders.end())
  {
    // not yet in map -> return empty list
    return list;
  }
  std::vector<const Rider*>* fromMap = mMapTours2Riders.at(tour);
  for(std::vector<const Rider*>::const_iterator it = fromMap->begin(); it != fromMap->end(); ++it)
  {
    list->push_back(*it);
  }
  return list;
}

Rider* Manager::addRider()
{
  Rider* rider = new Rider();
  mRiders->push_back(rider);
  emit ridersChanged();
  return rider;
}

Tour* Manager::addTour()
{
  Tour* tour = new Tour();
  mTours->push_back(tour);
  emit toursChanged();
  return tour;
}

void Manager::deleteRider(QUuid id)
{
  std::vector<const Rider*>::iterator it;
  for(it = mRiders->begin(); it != mRiders->end(); ++it)
  {
    if ( (*it)->getId() == id)
    {
      break;
    }
  }
  // it now either points to the tour we want to delete or the end of the vector
  if (it == mRiders->end())
  {
    return;
  }
  // TODO: remove from map
  mRiders->erase(it);
  delete *it;
  emit ridersChanged();
}

void Manager::deleteTour(QUuid id)
{
  std::vector<const Tour*>::iterator it;
  for(it = mTours->begin(); it != mTours->end(); ++it)
  {
    if ( (*it)->getId() == id)
    {
      break;
    }
  }
  // it now either points to the tour we want to delete or the end of the vector
  if (it == mTours->end())
  {
    return;
  }
  // TODO: remove from map
  mTours->erase(it);
  delete *it;
  emit toursChanged();
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

void Manager::setRidersForTour(const QUuid tour, const std::vector<QUuid> ridersNew)
{
  for(std::map<const Tour*, std::vector<const Rider*>*>::const_iterator it = mMapTours2Riders.begin();
      it != mMapTours2Riders.end(); ++it)
  {
    if(it->first->getId() != tour)
    {
      continue;
    }
    std::vector<const Rider*>* riders = it->second;
    riders->clear();
    for(std::vector<QUuid>::const_iterator it2 = ridersNew.begin(); it2 != ridersNew.end(); ++it2)
    {
      const Rider* rider = getRiderById(*it2);
      if (NULL == rider)
      {
        continue;
      }
      riders->push_back(rider);
    }
    return;
  }
  // not found => add new vector and try again
  const Tour* t = getTourById(tour);
  if (NULL == t)
  {
    return;
  }
  mMapTours2Riders[t] = new std::vector<const Rider*>();
  setRidersForTour(tour, ridersNew);
}


std::vector<const Tour*>* Manager::getTours() const
{
  return mTours;
}

std::vector<const Rider*>* Manager::getRiders() const
{
  return mRiders;
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


const Tour* Manager::getTourById(const QUuid id) const
{
  for(std::vector<const Tour*>::const_iterator it = mTours->begin(); it != mTours->end(); ++it)
  {
    if ((*it)->getId() == id)
    {
      return *it;
    }
  }
  return NULL;
}

// save in the form of Tour --> Riders (ids only)
QDomElement Manager::writeMap(QDomDocument doc) const
{
  QDomElement map = doc.createElement("TourData");
  map.setTagName("TourData");
  QDomText text;
  for(std::map<const Tour*, std::vector<const Rider*>*>::const_iterator it= mMapTours2Riders.begin();
      it != mMapTours2Riders.end(); ++it)
  {
    QDomElement tour = doc.createElement("Tour");
    tour.setTagName("Tour");
    tour.setAttribute("id", it->first->getId().toString());
    for(std::vector<const Rider*>::const_iterator it2 = it->second->begin(); it2 != it->second->end(); ++it2)
    {
      QDomElement member = doc.createElement("Member");
      member.setTagName("Member");
      text = doc.createTextNode((*it2)->getId().toString());
      member.appendChild(text);
      tour.appendChild(member);
    }
    map.appendChild(tour);
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
  QDomNodeList list = element.elementsByTagName("Tour");
  int cnt = list.count();
  for (int i = 0; i < cnt; ++i)
  {
    QDomElement xTour = list.at(i).toElement();
    if(xTour.isNull())
    {
      continue;
    }
    const Tour* tour = getTourById(QUuid(xTour.attribute("id")));
    if (NULL == tour)
    {
      continue;
    }
    mMapTours2Riders[tour] = new std::vector<const Rider*>();
    QDomNodeList xMembers = xTour.elementsByTagName("Member");
    int memCount = xMembers.count();
    for(int j = 0; j < memCount; ++j)
    {
      QDomElement xMember = xMembers.at(j).toElement();
      const Rider* rider = getRiderById(QUuid(xMember.firstChild().nodeValue()));
      if (NULL == rider)
      {
        continue;
      }
      mMapTours2Riders[tour]->push_back(rider);
    }
  }
}
