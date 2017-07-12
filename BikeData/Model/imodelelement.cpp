#include "imodelelement.h"

IModelElement::IModelElement()
{
  mId = QUuid::createUuid();
}

QUuid IModelElement::GetId() const
{
  return mId;
}
