#include "imodelelement.h"

IModelElement::IModelElement()
{
  mId = QUuid::createUuid();
}

QUuid IModelElement::getId() const
{
  return mId;
}
