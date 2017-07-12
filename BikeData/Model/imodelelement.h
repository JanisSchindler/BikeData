#ifndef IMODELELEMENT_H
#define IMODELELEMENT_H

#include <QUuid>

class IModelElement
{
public:
  IModelElement();
  QUuid GetId() const;
  virtual ~IModelElement(){}

protected:
  QUuid mId;
};


#endif // IMODELELEMENT_H
