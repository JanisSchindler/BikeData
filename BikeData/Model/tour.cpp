#include "tour.h"

Tour::Tour(){}

Tour::~Tour(){}

void Tour::setTitle(const QString title)
{
  mTitle = title;
}

QString Tour::getTitle() const
{
  return mTitle;
}

void Tour::setLength(const float len)
{
  mLength = len;
}

float Tour::getLength() const
{
  return mLength;
}

void Tour::setHeight(const float height)
{
  mHeight = height;
}

float Tour::getHeight() const
{
  return mHeight;
}

void Tour::setDate(const QDate date)
{
  mDate = date;
}

QDate Tour::getDate() const
{
  return mDate;
}

void Tour::setDuration(const QTime duration)
{
  mDuration = duration;
}

QTime Tour::getDuration() const
{
  return mDuration;
}

float Tour::getAverageSpeed() const
{
  if (!mDuration.isValid())
  {
    return 0.0;
  }
  int durMs = mDuration.elapsed();
  // return in km / h
  return mLength / (durMs / 1000.0 / 3600);

}

float Tour::getAverageRaise() const
{
  if (mHeight < 0.0001)
  {
    return 0.0;
  }
  // return in %
  // 100 % == same distance up as forward
  return mLength * 1000 / mHeight * 100;
}

void Tour::loadFromXML(const QDomNode node)
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
  xNode = element.elementsByTagName(QString("Title")).item(0);
  if (!xNode.isNull())
  {
    mTitle = xNode.nodeValue();
  }
  xNode = element.elementsByTagName(QString("Length")).item(0);
  if (!xNode.isNull())
  {
    mLength = xNode.nodeValue().toFloat();
  }
  xNode = element.elementsByTagName(QString("Height")).item(0);
  if (!xNode.isNull())
  {
    mHeight = xNode.nodeValue().toInt();
  }
  xNode = element.elementsByTagName(QString("Date")).item(0);
  if (!xNode.isNull())
  {
    mDate = QDate::fromString(xNode.nodeValue());
  }
  xNode = element.elementsByTagName(QString("Duration")).item(0);
  if (!xNode.isNull())
  {
    mDuration = QTime::fromString(xNode.nodeValue());
  }
}

QDomElement* Tour::writeToXML() const
{
  QDomElement* xID = new QDomElement();
  xID->setTagName(QString("ID"));
  xID->setNodeValue(mId.toString());

  QDomElement* xTitle = new QDomElement();
  xTitle->setTagName(QString("Title"));
  xTitle->setNodeValue(mTitle);

  QDomElement* xLen = new QDomElement();
  xLen->setTagName(QString("Length"));
  xLen->setNodeValue(QString::number(mLength));

  QDomElement* xHeight = new QDomElement();
  xHeight->setTagName(QString("Height"));
  xHeight->setNodeValue(QString::number(mHeight));

  QDomElement* xDate = new QDomElement();
  xDate->setTagName(QString("Date"));
  xDate->setNodeValue(mDate.toString());

  QDomElement* xDuration = new QDomElement();
  xDuration->setTagName(QString("Duration"));
  xDuration->setNodeValue(mDuration.toString());

  QDomElement* data = new QDomElement();
  data->setTagName("Tour");
  data->appendChild(*xID);
  data->appendChild(*xLen);
  data->appendChild(*xHeight);
  data->appendChild(*xDate);
  data->appendChild(*xDuration);
  return data;
}
