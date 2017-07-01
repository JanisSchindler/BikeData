#include "tour.h"

Tour::Tour()
{
  mId = QUuid::createUuid();
}

Tour::~Tour(){}

void Tour::SetLength(float len)
{
  mLength = len;
}

float Tour::GetLength()
{
  return mLength;
}

void Tour::SetHeight(float height)
{
  mHeight = height;
}

float Tour::GetHeight()
{
  return mHeight;
}

void Tour::SetDate(QDate date)
{
  mDate = date;
}

QDate Tour::GetDate()
{
  return mDate;
}

void Tour::SetDuration(QTime duration)
{
  mDuration = duration;
}

QTime Tour::GetDuration()
{
  return mDuration;
}

float Tour::GetAverageSpeed()
{
  int durMs = mDuration.elapsed();
  // return in km / h
  return mLength / (durMs / 1000.0 / 3600);
}

float Tour::GetAverageRaise()
{
  // return in %
  // 100 % == same distance up as forward
  return mLength * 1000 / mHeight * 100;
}

QUuid Tour::GetId()
{
  return mId;
}

void Tour::LoadFromXML(QDomElement* element)
{

}

QDomElement* Tour::WriteToXML()
{
  return NULL;
}
