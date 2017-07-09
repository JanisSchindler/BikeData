#ifndef IPERSISTENCE_H
#define IPERSISTENCE_H

#include <QDomElement>

class IPersistence
{
public:
  virtual void LoadFromXML(QDomNode node) = 0;
  virtual QDomElement* WriteToXML() const  = 0 ;
  virtual ~IPersistence(){}
};

#endif // IPERSISTENCE_H
