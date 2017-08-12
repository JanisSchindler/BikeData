#include "rider.h"

Rider::Rider(){}

Rider::~Rider(){}

void Rider::setFirstName(const QString name)
{
  mFirstName = name;
}

QString Rider::getFirstName() const
{
  return mFirstName;
}

void Rider::setLastName(const QString name)
{
  mLastName = name;
}

QString Rider::getLastName() const
{
  return mLastName;
}

void Rider::setBirthdate(const QDate date)
{
  mBirthdate = date;
}

QDate Rider::getBirthdate() const
{
  return mBirthdate;
}

unsigned int Rider::getAge() const
{
  if (!mBirthdate.isValid())
  {
    return 0;
  }
  QDate current = QDate::currentDate();
  int years = current.year() - mBirthdate.year();
  if (current.month() < mBirthdate.month() ||
      (current.month() == mBirthdate.month() && current.day() < mBirthdate.day()))
  {
    return years - 1;
  }
  return years;
}

void Rider::loadFromXML(const QDomNode node)
{
  QDomElement element = node.toElement();
  if (element.isNull())
  {
    return;
  }
  QDomNode xNode = element.elementsByTagName(QString("ID")).item(0);
  if (!xNode.isNull())
  {
    mId = QUuid(xNode.nodeValue());
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

QDomElement* Rider::writeToXML() const
{
  QDomElement* xID = new QDomElement();
  xID->setTagName(QString("ID"));
  xID->setNodeValue(mId.toString());

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
