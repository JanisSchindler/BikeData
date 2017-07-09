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

  void SetFirstName(const QString name);
  QString GetFirstName() const;
  void SetLastName(const QString name);
  QString GetLastName() const;
  void SetBirthdate(const QDate date);
  QDate GetBirthdate() const;
  unsigned int GetAge() const;

  // IModelElement
  QUuid GetId() const;

  // IPersistence
  void LoadFromXML(const QDomNode node);
  QDomElement* WriteToXML()const;

private:
  QString mFirstName;
  QString mLastName;
  QDate mBirthdate;
  QUuid mID;
};

#endif // RIDER_H
