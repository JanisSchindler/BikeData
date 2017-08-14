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

  void setFirstName(const QString name);
  QString getFirstName() const;
  void setLastName(const QString name);
  QString getLastName() const;
  void setBirthdate(const QDate date);
  QDate getBirthdate() const;
  unsigned int getAge() const;

  QString toString() const;

  // IPersistence
  void loadFromXML(const QDomNode node);
  QDomElement writeToXML(QDomDocument doc) const;

private:
  QString mFirstName;
  QString mLastName;
  QDate mBirthdate;
};

#endif // RIDER_H
