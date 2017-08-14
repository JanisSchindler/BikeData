#ifndef MANAGER_H
#define MANAGER_H

#include <QDomElement>
#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <vector>
#include <map>

#include "tour.h"
#include "rider.h"

class Manager : public QObject
{
   Q_OBJECT

public:

  Manager(const QString path);
  ~Manager();

  // main entry point to save and load a file
  void save() const;
  void load();
  // these create new lists -> delete after use
  std::vector<const Rider*>* getRidersForTour(const Tour* tour) const;
  std::vector<const Tour*>* getToursForRider(const Rider* rider) const;

  void setRidersForTour(const QUuid tour, const std::vector<QUuid> riders);

  std::vector<const Tour*>* getTours() const;
  std::vector<const Rider*>* getRiders() const;

  Rider* addRider();
  Tour* addTour();

  void deleteRider(QUuid id);
  void deleteTour(QUuid id);

  const Rider* getRiderById(QUuid id) const;
  const Tour* getTourById(QUuid id) const;

signals:
  void ridersChanged();
  void toursChanged();

private:
  QString mPath;
  std::map<const Tour*, std::vector<const Rider*>*> mMapTours2Riders;
  std::vector<const Rider*>* mRiders;
  std::vector<const Tour*>* mTours;

  QDomElement writeMap(QDomDocument doc) const;
  void readMap(const QDomNode map);
};

#endif // MANAGER_H
