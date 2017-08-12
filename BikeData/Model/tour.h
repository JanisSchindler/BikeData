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

  void setTitle(const QString title);
  QString getTitle() const;

  // km
  void setLength(const float length);
  float getLength() const;
  // m
  void setHeight(const float height);
  float getHeight() const;

  void setDate(const QDate date);
  QDate getDate() const;

  void setDuration(const QTime duration);
  QTime getDuration() const;

  // calculated properties
  float getAverageSpeed() const;
  float getAverageRaise() const;

  // IPersistence
  void loadFromXML(const QDomNode node);
  QDomElement* writeToXML() const;

private:
  QString mTitle;
  float mLength;
  float mHeight;
  QDate mDate;
  QTime mDuration;

};

#endif // TOUR_H
