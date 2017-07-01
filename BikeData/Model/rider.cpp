#include "rider.h"

Rider::Rider()
{
  mID = QUuid::createUuid();
}

Rider::~Rider(){}

void Rider::SetFirstName(QString name)
{
  mFirstName = name;
}

QString Rider::GetFirstName()
{
  return mFirstName;
}

void Rider::SetLastName(QString name)
{
  mLastName = name;
}

QString Rider::GetLastName()
{
  return mLastName;
}

void Rider::SetBirthdate(QDate date)
{
  mBirthdate = date;
}

QDate Rider::GetBirthdate()
{
  return mBirthdate;
}

unsigned int Rider::GetAge()
{
  QDate current = QDate::currentDate();
  int years = current.year() - mBirthdate.year();
  if (current.month() < mBirthdate.month() ||
      (current.month() == mBirthdate.month() && current.day() < mBirthdate.day()))
  {
    return years - 1;
  }
  return years;
}

QUuid Rider::GetId()
{
  return mID;
}

void Rider::LoadFromXML(QDomElement *element)
{

}

QDomElement* Rider::WriteToXML()
{
  return NULL;
}
