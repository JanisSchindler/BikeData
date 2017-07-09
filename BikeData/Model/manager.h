#ifndef MANAGER_H
#define MANAGER_H

#include <QDomElement>
#include <QString>
#include <QFile>
#include <vector>
#include <map>

#include "tour.h"
#include "rider.h"

class Manager
{
public:

  Manager();
  ~Manager();

  // main entry point to save and load a file
  void Save(const QString fileName) const;
  void Load(const QString fileName) const;

  std::vector<const Rider*> GetRidersForTour(const Tour* tour) const;
  std::vector<const Tour*> GetToursForRider(const Rider* rider) const;


private:
  std::map<const Tour*, std::vector<const Rider*>*> mMapTours2Riders;
  std::vector<Rider*>* mRiders;
  std::vector<Tour*>* mTours;

  QDomElement* WriteMap() const;
  void ReadMap(const QDomNode map) const;
};

#endif // MANAGER_H
