#ifndef IMODELELEMENT_H
#define IMODELELEMENT_H

#include <QUuid>

class IModelElement
{
public:
  IModelElement();
  QUuid getId() const;
  // this is e.g. used by IdQWidgetListItem
  virtual QString toString() const = 0 ;
  virtual ~IModelElement(){}

protected:
  QUuid mId;
};


#endif // IMODELELEMENT_H
