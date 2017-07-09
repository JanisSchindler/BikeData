#ifndef TOUR_H
#define TOUR_H

#include <QString>
#include <QDate>
#include <QTime>


#include "imodelelement.h"
#include "ipersistence.h"


class Tour: public IModelElement, public IPersistence
{
public:
  Tour();
  ~Tour();

  // km
  void SetLength(const float length);
  float GetLength() const;
  // m
  void SetHeight(const float height);
  float GetHeight() const;

  void SetDate(const QDate date);
  QDate GetDate() const;

  void SetDuration(const QTime duration);
  QTime GetDuration() const;

  // calculated properties
  float GetAverageSpeed() const;
  float GetAverageRaise() const;

  // IModelElement
  QUuid GetId() const;
  // IPersistence
  void LoadFromXML(const QDomNode node);
  QDomElement* WriteToXML() const;

private:
  QUuid mID;
  float mLength;
  float mHeight;
  QDate mDate;
  QTime mDuration;

};

#endif // TOUR_H
