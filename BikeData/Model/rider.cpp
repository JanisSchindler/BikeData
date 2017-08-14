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
  QDomNode xNode = element.elementsByTagName("ID").item(0);
  if (!xNode.isNull())
  {
    mId = QUuid(xNode.firstChild().nodeValue());
  }
  xNode = element.elementsByTagName("FirstName").item(0);
  if (!xNode.isNull())
  {
    mFirstName = xNode.firstChild().nodeValue();
  }
  xNode = element.elementsByTagName("LastName").item(0);
  if (!xNode.isNull())
  {
    mLastName = xNode.firstChild().nodeValue();
  }
  xNode = element.elementsByTagName("Birthdate").item(0);
  if (!xNode.isNull())
  {
    mBirthdate = QDate::fromString(xNode.firstChild().nodeValue()); // does this work?
  }
}

QString Rider::toString() const
{
  QString name;
  if (!mLastName.isNull())
  {
    name = mLastName;
  }
  if (!mFirstName.isNull())
  {
    if (!name.isEmpty())
    {
      name = name + ", ";
    }
    name = name + mFirstName;
  }
  return name;
}

QDomElement Rider::writeToXML(QDomDocument doc) const
{
  QDomElement xID = doc.createElement("ID");
  QDomText text = doc.createTextNode(mId.toString());
  xID.appendChild(text);

  QDomElement xFirstName = doc.createElement("FirstName");
  text = doc.createTextNode(mFirstName);
  xFirstName.appendChild(text);

  QDomElement xLastName = doc.createElement("LastName");
  text = doc.createTextNode(mLastName);
  xLastName.appendChild(text);

  QDomElement xBirthdate =doc.createElement("Birthdate");
  text = doc.createTextNode(mBirthdate.toString());
  xBirthdate.appendChild(text);

  QDomElement data = doc.createElement("Rider");
  data.setTagName("Rider");
  data.appendChild(xID);
  data.appendChild(xFirstName);
  data.appendChild(xLastName);
  data.appendChild(xBirthdate);
  return data;
}
