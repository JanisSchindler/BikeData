#ifndef IPERSISTENCE_H
#define IPERSISTENCE_H

#include <QDomElement>

class IPersistence
{
public:
  virtual void LoadFromXML(QDomElement* element) = 0;
  virtual QDomElement* WriteToXML() = 0;
  virtual ~IPersistence(){}
};

#endif // IPERSISTENCE_H
