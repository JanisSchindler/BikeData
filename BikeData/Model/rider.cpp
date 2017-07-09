#include "rider.h"

Rider::Rider()
{
  mID = QUuid::createUuid();
}

Rider::~Rider(){}

void Rider::SetFirstName(const QString name)
{
  mFirstName = name;
}

QString Rider::GetFirstName() const
{
  return mFirstName;
}

void Rider::SetLastName(const QString name)
{
  mLastName = name;
}

QString Rider::GetLastName() const
{
  return mLastName;
}

void Rider::SetBirthdate(const QDate date)
{
  mBirthdate = date;
}

QDate Rider::GetBirthdate() const
{
  return mBirthdate;
}

unsigned int Rider::GetAge() const
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

QUuid Rider::GetId() const
{
  return mID;
}

void Rider::LoadFromXML(const QDomNode node)
{
  QDomElement element = node.toElement();
  if (element.isNull())
  {
    return;
  }
  QDomNode xNode = element.elementsByTagName(QString("ID")).item(0);
  if (!xNode.isNull())
  {
    mID = QUuid(xNode.nodeValue());
  }
  xNode = element.elementsByTagName(QString("FirstName")).item(0);
  if (!xNode.isNull())
  {
    mFirstName = xNode.nodeValue();
  }
  xNode = element.elementsByTagName(QString("LastName")).item(0);
  if (!xNode.isNull())
  {
    mLastName = xNode.nodeValue();
  }
  xNode = element.elementsByTagName(QString("Birthdate")).item(0);
  if (!xNode.isNull())
  {
    mBirthdate = QDate::fromString(xNode.nodeValue()); // does this work?
  }
}

QDomElement* Rider::WriteToXML() const
{
  QDomElement* xID = new QDomElement();
  xID->setTagName(QString("ID"));
  xID->setNodeValue(mID.toString());

  QDomElement* xFirstName = new QDomElement();
  xFirstName->setTagName(QString("FirstName"));
  xFirstName->setNodeValue(mFirstName);

  QDomElement* xLastName = new QDomElement();
  xLastName->setTagName(QString("LastName"));
  xLastName->setNodeValue(mLastName);

  QDomElement* xBirthdate = new QDomElement();
  xBirthdate->setTagName(QString("Birthdate"));
  xBirthdate->setNodeValue(mBirthdate.toString());

  QDomElement* data = new QDomElement();
  data->setTagName(QString("Rider"));
  data->appendChild(*xID);
  data->appendChild(*xFirstName);
  data->appendChild(*xLastName);
  data->appendChild(*xBirthdate);
  return data;
}
