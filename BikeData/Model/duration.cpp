#include "duration.h"

Duration::Duration()
{
  mSecs = 0;
}

Duration::Duration(const QString string)
{
  mIsValid = false;
  mSecs = 0;
  // we support 2 formats for now: DD:HH:MM and HH:MM
  int first = string.indexOf(":");
  if (first < 0)
  {
    return;
  }
  mIsValid = true;
  int second = string.indexOf(":", first + 1);
  if (second < 0)
  {
    // first format
    QStringRef h(&string, 0, first);
    QStringRef m(&string, first + 1, string.length() - first - 1);
    mSecs += str2num(m) * 60;
    mSecs += str2num(h) * 60 * 60;
  }
  else
  {
    // second format
    QStringRef d(&string, 0, first - 1);
    QStringRef h(&string, first, second - first - 1);
    QStringRef m(&string, second, string.length() - second - 1);
    mSecs += str2num(m) * 60;
    mSecs += str2num(h) * 60 * 60;
    mSecs += str2num(d) * 60 * 60 * 24;
  }
}

Duration::Duration(const QTime time)
{
  mSecs = 0;
  if (!time.isValid())
  {
    mIsValid = false;
    return;
  }
  mIsValid = true;
  mSecs += time.second();
  mSecs += time.minute() * 60;
  mSecs += time.hour() * 60 * 60;
}

Duration Duration::operator +(const Duration other)
{
  if (!mIsValid || !other.isValid())
  {
    mSecs += other.secs();
  }
  return *this;
}

bool Duration::isValid() const
{
  return mIsValid;
}

QString Duration::toString() const
{
  int days = mSecs / (60*60*24);
  int remainder = mSecs - (days * 60*60*24);
  int hours = remainder / (60*60);
  remainder -= (hours * 60*60);
  int mins =  remainder % 60;
  // arg:
  // (number, fillWdith, base, fillChar) <-- fillChar has to be QChar else the overloading does not work
  if (days > 0)
  {
    return QString("%L1:%L2:%L3").arg(days, 2, 10, QChar('0')).arg(hours, 2, 10, QChar('0')).arg(mins, 2, 10, QChar('0'));
  }
  else
  {
    return QString("%L1:%L2").arg(hours, 2, 10, QChar('0')).arg(mins, 2, 10, QChar('0'));
  }
}

QTime Duration::toTime() const
{
  QTime t(0,0,0,0);
  t = t.addSecs(mSecs);
  return t;
}

long Duration::secs() const
{
  return mSecs;
}

int Duration::str2num(const QStringRef string)
{
  bool ok;
  int value = string.toInt(&ok);
  if (!ok)
  {
    mIsValid = false;
  }
  return value;
}
