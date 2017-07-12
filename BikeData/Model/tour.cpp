#include "tour.h"

Tour::Tour(){}

Tour::~Tour(){}

void Tour::SetLength(const float len)
{
  mLength = len;
}

float Tour::GetLength() const
{
  return mLength;
}

void Tour::SetHeight(const float height)
{
  mHeight = height;
}

float Tour::GetHeight() const
{
  return mHeight;
}

void Tour::SetDate(const QDate date)
{
  mDate = date;
}

QDate Tour::GetDate() const
{
  return mDate;
}

void Tour::SetDuration(const QTime duration)
{
  mDuration = duration;
}

QTime Tour::GetDuration() const
{
  return mDuration;
}

float Tour::GetAverageSpeed() const
{
  int durMs = mDuration.elapsed();
  // return in km / h
  return mLength / (durMs / 1000.0 / 3600);
}

float Tour::GetAverageRaise() const
{
  // return in %
  // 100 % == same distance up as forward
  return mLength * 1000 / mHeight * 100;
}

void Tour::LoadFromXML(const QDomNode node)
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

QDomElement* Tour::WriteToXML() const
{
  QDomElement* xID = new QDomElement();
  xID->setTagName(QString("ID"));
  xID->setNodeValue(mId.toString());

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
