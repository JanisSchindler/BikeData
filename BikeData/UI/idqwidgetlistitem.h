#ifndef IDWIDGETITEM_H
#define IDWIDGETITEM_H

#include <QListWidgetItem>
#include <QUuid>
#include "Model/imodelelement.h"

class IdQListWidgetItem : public QListWidgetItem
{
public:
  IdQListWidgetItem(QListWidget *view, const IModelElement* element);
  IdQListWidgetItem(const IModelElement* element);
  void update(const IModelElement* element);
  QUuid getElementId() const;

private:
  QUuid mElementId;
};

#endif // IDWIDGETITEM_H
