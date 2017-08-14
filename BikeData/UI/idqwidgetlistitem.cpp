#include "idqwidgetlistitem.h"

IdQListWidgetItem::IdQListWidgetItem(QListWidget *view, const IModelElement* element)
 : QListWidgetItem(view)
{
  if (NULL == element)
  {
    setText("add...");
    QFont f = font();
    f.setItalic(true);
    setFont(f);
    return;
  }
  mElementId = element->getId();
  setText(element->toString());
}

IdQListWidgetItem::IdQListWidgetItem(const IModelElement* element)
{
  mElementId = element->getId();
  setText(element->toString());
}

void IdQListWidgetItem::update(const IModelElement* element)
{
  if (NULL != element && element->getId() == mElementId)
  {
    setText(element->toString());
  }
}

QUuid IdQListWidgetItem::getElementId() const
{
  return mElementId;
}
