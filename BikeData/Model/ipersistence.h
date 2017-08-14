#ifndef IPERSISTENCE_H
#define IPERSISTENCE_H

#include <QDomElement>

class IPersistence
{
public:
  virtual void loadFromXML(QDomNode node) = 0;
  virtual QDomElement writeToXML(QDomDocument doc) const  = 0 ;
  virtual ~IPersistence(){}
};

#endif // IPERSISTENCE_H
