#ifndef RIDER_H
#define RIDER_H

#include <QString>
#include <QDate>

#include "imodelelement.h"
#include "ipersistence.h"

class Rider : public IModelElement, public IPersistence
{
public:
  Rider();
  ~Rider();

  void SetFirstName(QString name);
  QString GetFirstName();
  void SetLastName(QString name);
  QString GetLastName();
  void SetBirthdate(QDate date);
  QDate GetBirthdate();
  unsigned int GetAge();

  // IModelElement
  QUuid GetId();

  // IPersistence
  void LoadFromXML(QDomElement * element);
  QDomElement* WriteToXML();

private:
  QString mFirstName;
  QString mLastName;
  QDate mBirthdate;
  QUuid mID;
};

#endif // RIDER_H
