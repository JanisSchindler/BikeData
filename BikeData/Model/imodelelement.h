#ifndef IMODELELEMENT_H
#define IMODELELEMENT_H

#include <QUuid>

class IModelElement
{
public:
  virtual QUuid GetId() const = 0;
  virtual ~IModelElement(){}
};


#endif // IMODELELEMENT_H
