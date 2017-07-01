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
  void SetLength(float length);
  float GetLength();
  // m
  void SetHeight(float height);
  float GetHeight();

  void SetDate(QDate date);
  QDate GetDate();

  void SetDuration(QTime duration);
  QTime GetDuration();

  // calculated properties
  float GetAverageSpeed();
  float GetAverageRaise();

  // IModelElement
  QUuid GetId();
  // IPersistence
  void LoadFromXML(QDomElement * element);
  QDomElement* WriteToXML();

private:
  QUuid mId;
  float mLength;
  float mHeight;
  QDate mDate;
  QTime mDuration;

};

#endif // TOUR_H
