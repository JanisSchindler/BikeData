#ifndef DURATION_H
#define DURATION_H

#include <QString>
#include <QTime>

class Duration
{
public:
  Duration();
  Duration(const QString string);
  Duration(const QTime time);

  Duration operator+(const Duration other);

  bool isValid() const;
  QString toString() const;
  QTime toTime() const;

  long secs() const;

private:
  bool mIsValid;
  long mSecs;
  int str2num(const QStringRef string);
};

#endif // DURATION_H
