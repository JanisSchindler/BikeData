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

void Tour::setDuration(const Duration duration)
{
  mDuration = duration;
}

Duration Tour::getDuration() const
{
  return mDuration;
}

float Tour::getAverageSpeed() const
{
  if (!mDuration.isValid())
  {
    return 0.0;
  }
  return mLength / ((float)mDuration.secs() / 3600.0f);
}

float Tour::getAverageRaise() const
{
  if (mHeight < 0.0001)
  {
    return 0.0;
  }
  // return in %
  // 100 % == same distance up as forward
  return 100 * (mHeight / (mLength * 1000.0));
}

QString Tour::toString() const
{
  return mTitle;
}

void Tour::loadFromXML(const QDomNode node)
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
  xNode = element.elementsByTagName("Title").item(0);
  if (!xNode.isNull())
  {
    mTitle = xNode.firstChild().nodeValue();
  }
  xNode = element.elementsByTagName("Length").item(0);
  if (!xNode.isNull())
  {
    mLength = xNode.firstChild().nodeValue().toFloat();
  }
  xNode = element.elementsByTagName("Height").item(0);
  if (!xNode.isNull())
  {
    mHeight = xNode.firstChild().nodeValue().toInt();
  }
  xNode = element.elementsByTagName("Date").item(0);
  if (!xNode.isNull())
  {
    mDate = QDate::fromString(xNode.firstChild().nodeValue());
  }
  xNode = element.elementsByTagName("Duration").item(0);
  if (!xNode.isNull())
  {
    mDuration = Duration(xNode.firstChild().nodeValue());
  }
}

QDomElement Tour::writeToXML(QDomDocument doc) const
{
  QDomElement xID = doc.createElement("ID");
  QDomText text = doc.createTextNode(mId.toString());
  xID.appendChild(text);

  QDomElement xTitle = doc.createElement("Title");
  text = doc.createTextNode(mTitle);
  xTitle.appendChild(text);

  QDomElement xLen = doc.createElement("Length");
  text = doc.createTextNode(QString::number(mLength));
  xLen.appendChild(text);

  QDomElement xHeight = doc.createElement("Height");
  text = doc.createTextNode(QString::number(mHeight));
  xHeight.appendChild(text);

  QDomElement xDate = doc.createElement("Date");
  text = doc.createTextNode(mDate.toString());
  xDate.appendChild(text);

  QDomElement xDuration = doc.createElement("Duration");
  text = doc.createTextNode(mDuration.toString());
  xDuration.appendChild(text);

  QDomElement data = doc.createElement("Tour");
  data.setTagName("Tour");  
  data.appendChild(xID);
  data.appendChild(xTitle);
  data.appendChild(xLen);
  data.appendChild(xHeight);
  data.appendChild(xDate);
  data.appendChild(xDuration);
  return data;
}
